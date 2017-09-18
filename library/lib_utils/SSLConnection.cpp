#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <egt_lib/debug/egt_debug.h>

#include "SSLConnection.h"

#include <iostream>
#include <string>
#include <egt_lib/debug/egt_debug.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>


#ifndef OPENSSL_VERSION_NUMBER
	#define OPENSSL_VERSION_NUMBER 1
#endif // !OPENSSL_VERSION_NUMBER

#define C4C_RET_NULL(p,r,t) if (NULL==(p)) { eCDebug(LOG_CATEGORY_SSL) << t; return (r); }
#define C4C_RET_ERR(e,r,t) if (-1==(e)) {  eCDebug(LOG_CATEGORY_SSL) << t; return (r); }
//#define C4C_RET_SSL(e,r) if (-1==(e)) { ERR_print_errors_fp(stderr); return (r); }
#define C4C_RET_SSL(e,r) if (-1==(e)) { eCDebug(LOG_CATEGORY_SSL) << "errno=" << r; return (r); }

using namespace egt;

SSLConnection::SSLConnection()
	: m_hSock(-1)
	, m_ctx(NULL)
	, m_ssl(NULL)
	, m_meth(NULL)
	, m_bIpV6(false) {

}

SSLConnection::~SSLConnection() {

	Disconnect();
}

SSLConnection::Status SSLConnection::Connect(const char* pszAddr, int nPort, const char* pszPEMFile, const char* pszCAFile /*= NULL*/, const char* pszEth /*= "eth0"*/) {

    int err;

	C4C_RET_NULL(pszAddr, eSSL_NO_IPADDRESS, "Invalid ip address!");
	m_strEth = pszEth;

	/* Load encryption & hashing algorithms for the SSL program */
	SSL_library_init(); //@note: this function is not thread safe

	/* Load the error strings for SSL & CRYPTO APIs */
	SSL_load_error_strings(); //@note: this function is not thread safe

	/* Create an SSL_METHOD structure (choose an SSL/TLS protocol version) */
	m_meth = TLSv1_client_method();

	/* Create an SSL_CTX structure */
	m_ctx = SSL_CTX_new(m_meth);
	C4C_RET_NULL(m_ctx, eSSL_CREATE_SSLCTX_FAILED, "Failed to create SSL context!");

	eCDebug(LOG_CATEGORY_SSL) << "SSL version = " << OPENSSL_VERSION_NUMBER << ", CTX timeout = " << SSL_CTX_get_timeout(m_ctx) << " seconds";

	/* Load the client certificate into the SSL_CTX structure */
	if (SSL_CTX_use_certificate_file(m_ctx, pszPEMFile, SSL_FILETYPE_PEM) <= 0) {
		eCDebug(LOG_CATEGORY_SSL) << "Failed to load certificate!";
		C4C_RET_SSL(-1, eSSL_LOAD_CERT_FAILED);
	}

	/* Load the private-key corresponding to the client certificate */
	if (SSL_CTX_use_PrivateKey_file(m_ctx, pszPEMFile, SSL_FILETYPE_PEM) <= 0) {
		eCDebug(LOG_CATEGORY_SSL) << "Failed to load private key!";
		C4C_RET_SSL(-1, eSSL_PKEY_FAILED);
	}

	/* Check if the client certificate and private-key matches */
	if (!SSL_CTX_check_private_key(m_ctx)) {
		eCDebug(LOG_CATEGORY_SSL) << "Private key does not match the certificate public key";
		C4C_RET_SSL(-1, eSSL_PKEY_NOTMATCHED);
	}

	/* Load the RSA CA certificate into the SSL_CTX structure */
	/* This will allow this client to verify the server's     */
	/* certificate.                                           */
	if (NULL != pszCAFile) if (strlen(pszCAFile) > 0) {

		if (!SSL_CTX_load_verify_locations(m_ctx, pszCAFile, NULL)) {
			eCDebug(LOG_CATEGORY_SSL) << "Failed to load CA!";
			C4C_RET_SSL(-1, eSSL_CA_FAILED);
		}

		/* Set flag in context to require peer (server) certificate */
		/* verification */

		SSL_CTX_set_verify(m_ctx,SSL_VERIFY_PEER,NULL);

		SSL_CTX_set_verify_depth(m_ctx,1);
	}

	m_bIpV6 = IsValidIpV6(pszAddr);
	if (! m_bIpV6) {

		/* Set up a TCP socket */
		m_hSock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);       
		if (m_hSock < 0) {
			C4C_RET_ERR(-1, eSSL_SOCKET_FAILED, "Failed to open socket!")
		}

		fcntl(m_hSock, F_SETFL, O_NONBLOCK);  // set to non-blocking
        fcntl(m_hSock, F_SETFL, O_ASYNC);     // set to asynchronous I/O

		// int set = 1;  // instead of the SIGPIPE signal being generated, EPIPE will be returned
		// setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));

		int set = 1;  // instead of signals being generated, EPIPE will be returned
		setsockopt(m_hSock, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));

		sockaddr_in server_addr;
		memset (&server_addr, '\0', sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(nPort);  /* Server Port number */
		server_addr.sin_addr.s_addr = inet_addr(pszAddr); /* Server IP */

		/* Establish a TCP/IP connection to the SSL client */
        SetSocketTimeout(SOCKET_CONNECTION_TIMEOUT_IN_SECONDS); // avoid connect() hang up
		err = connect(m_hSock, (sockaddr*) &server_addr, sizeof(server_addr)); 
		C4C_RET_ERR(err, eSSL_SRVCONNECT_FAILED, "Failed to connect to server!")

	} else {
		
		Status stat = OpenV6Socket (pszAddr, nPort);
		if (eSSL_OK != stat) {
			C4C_RET_ERR(-1, stat, "Failed to open ipv6 socket!")
		}
	}

	eCDebug(LOG_CATEGORY_SSL) << "Open socket " << m_hSock << " succeeded";

	/* An SSL structure is created */
	m_ssl = SSL_new (m_ctx);
	C4C_RET_NULL(m_ssl, eSSL_CREATE_SSL_FAILED, "Failed to create SSL structure!");

	/* Assign the socket into the SSL structure (SSL and socket without BIO) */
	SSL_set_fd(m_ssl, m_hSock);

    SetSocketTimeout( SSL_CONNECT_TIMEOUT_IN_SECONDS ); // avoid SSL_connect() hang up

    /* Perform SSL Handshake on the SSL client */
	err = SSL_connect(m_ssl);
	eCDebug(LOG_CATEGORY_SSL) << "SSL_connect failed, errno=" << errno << " - " << strerror(errno);

	C4C_RET_ERR(err, eSSL_HANDSHAKE_FAILED, "Failed to handshake with server!")

	SetSocketLockless(); // set again asynchronous non-blocking mode

	/* Informational output (optional) */
	eCDebug(LOG_CATEGORY_SSL) << "SSL connection using " << SSL_get_cipher (m_ssl);

	return eSSL_OK;
}

#ifdef EGT_USE_GETADDRINFO
SSLConnection::Status SSLConnection::OpenV6Socket(const char* pszAddr, int nPort) {

	Status status = eSSL_SOCKET_FAILED;
	int err;
	addrinfo hints;
	addrinfo* servinfo = NULL;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
	hints.ai_socktype = SOCK_STREAM;

	char szPort[BUFSIZ];
	sprintf(szPort, "%d", nPort);
	err = getaddrinfo(pszAddr, szPort, &hints, &servinfo); // get address info
	if (0 == err) {
		// TODO: check the all list of addresses
		// Set up a TCP socket for the first in the list
		m_hSock = socket (servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	} else {
		eCDebug(LOG_CATEGORY_SSL) << "getaddrinfo() returned " << err << " - " << gai_strerror(err);
	}

	if (0 > m_hSock) {
		if (0 != errno) {
			eCDebug(LOG_CATEGORY_SSL) << "socket() failed, errno=" << errno << " - " << strerror(errno);
		}
	} else if (0 == err) {

		fcntl(m_hSock, F_SETFL, O_NONBLOCK);  // set to non-blocking
		fcntl(m_hSock, F_SETFL, O_ASYNC);     // set to asynchronous I/O
		int set = 1;  // instead of signals being generated, EPIPE will be returned
		setsockopt(m_hSock, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));

		// Establish a TCP/IP connection
        SetSocketTimeout( SOCKET_CONNECTION_TIMEOUT_IN_SECONDS ); // avoid connect() hang up
		err = connect(m_hSock, servinfo->ai_addr, servinfo->ai_addrlen);
		if (0 == err) {
			status = eSSL_OK;
		} else { // err == -1 according to documentation
			status = eSSL_SRVCONNECT_FAILED;
			eCDebug(LOG_CATEGORY_SSL) << "Failed to connect to server! Error: " << strerror(errno);
		}
	}

	freeaddrinfo(servinfo); // all done with this structure

	return status;
}

#else //EGT_USE_GETADDRINFO
SSLConnection::Status SSLConnection::OpenV6Socket(const char* pszAddr, int nPort) {

	int err;

	/* Set up a TCP socket */
	m_hSock = socket (PF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (m_hSock < 0) {
		C4C_RET_ERR(-1, eSSL_SOCKET_FAILED, "Failed to open ipv6 socket!")
	}

	fcntl(m_hSock, F_SETFL, O_NONBLOCK);  // set to non-blocking
	fcntl(m_hSock, F_SETFL, O_ASYNC);     // set to asynchronous I/O

	// int set = 1;  // instead of the SIGPIPE signal being generated, EPIPE will be returned
	// setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));

	int set = 1;  // instead of signals being generated, EPIPE will be returned
	setsockopt(m_hSock, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));

	sockaddr_in6 server_addr;
	memset (&server_addr, 0, sizeof(server_addr));
	inet_pton(AF_INET6, pszAddr, &(server_addr.sin6_addr)); // Server IP
	server_addr.sin6_port = htons(nPort);  // Server Port number
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_scope_id = if_nametoindex(m_strEth.c_str());

	/* Establish a TCP/IP connection to the SSL client */
    SetSocketTimeout( SOCKET_CONNECTION_TIMEOUT_IN_SECONDS ); // avoid connect() hang up
	err = connect(m_hSock, (sockaddr*) &server_addr, sizeof(server_addr));
	C4C_RET_ERR(err, eSSL_SRVCONNECT_FAILED, "Failed to connect to ipv6 server!")

	return eSSL_OK;
}
#endif //EGT_USE_GETADDRINFO

SSLConnection::Status SSLConnection::Read(void* pBuf, int& nSize, bool bBlocking /*= true*/) {

	C4C_RET_NULL(m_ssl, eSSL_NOTINT, "SSL is not initialized!")

	if (!bBlocking) {

		fd_set rfd;
		FD_ZERO(&rfd);
		FD_SET(m_hSock, &rfd);
		timeval tv = { 0 };
		select(m_hSock+1, &rfd, 0, 0, &tv);
		if (!FD_ISSET(m_hSock, &rfd)) {
			nSize = 0;
			return eSSL_OK;
		}
	}

	/* Receive data from the SSL server */
	int err = SSL_read(m_ssl, pBuf, nSize);                     

	if (err > 0) {

		nSize = err; // number of bytes actually read

	} else {
		nSize = SSL_get_error(m_ssl, err);
//		eCDebug(LOG_CATEGORY_SSL) << "SSL read failed, size: " << nSize;
        C4C_RET_SSL(-1, eSSL_READ_FAILED);
	}

	return eSSL_OK;
}

SSLConnection::Status SSLConnection::Write(const void* pBuf, int& nSize) {

	C4C_RET_NULL(m_ssl, eSSL_NOTINT, "SSL is not initialized!")

	/* Send data to the SSL server */
	int err = SSL_write(m_ssl, pBuf, nSize);  

	if (err > 0) {

		nSize = err; // number of bytes actually written

	} else {

		nSize = SSL_get_error(m_ssl, err);

		std::string errStr;
		switch (nSize)
		{
			case SSL_ERROR_NONE:
			errStr = "SSL_ERROR_NONE";
			break;
			case SSL_ERROR_ZERO_RETURN:
			errStr = "SSL_ERROR_ZERO_RETURN";
			break;
			case SSL_ERROR_WANT_READ:
			errStr = "SSL_ERROR_WANT_READ";
			break;
			case SSL_ERROR_WANT_WRITE:
			errStr = "SSL_ERROR_WANT_WRITE";
			break;
			case SSL_ERROR_WANT_CONNECT:
			errStr = "SSL_ERROR_WANT_CONNECT";
			break;
			case SSL_ERROR_WANT_ACCEPT:
			errStr = "SSL_ERROR_WANT_ACCEPT";
			break;
			case SSL_ERROR_WANT_X509_LOOKUP:
			errStr = "SSL_ERROR_WANT_X509_LOOKUP";
			break;
			case SSL_ERROR_SYSCALL:
			errStr = std::string("SSL_ERROR_SYSCALL ") + std::to_string(errno);

			break;
			case SSL_ERROR_SSL:
			errStr = "SSL_ERROR_SSL";
			break;
		}

		eCDebug(LOG_CATEGORY_SSL) << "SSL write failed, SSL_get_error: " << errStr;
		C4C_RET_SSL(-1, eSSL_WRITE_FAILED);
	}

	return eSSL_OK;
}

SSLConnection::Status SSLConnection::ShowServerCert() {

	Status status = eSSL_OK;

	C4C_RET_NULL(m_ssl, eSSL_NOTINT, "SSL is not initialized!")

	/* Get the server's certificate (optional) */
	/*
	X509 *psrvCert = SSL_get_peer_certificate (m_ssl);    

	if (psrvCert != NULL)
	{
		char szName[BUFSIZ];
		memset(szName, 0, sizeof(szName));
		eCDebugf(LOG_CATEGORY_SSL, "Server certificate:\n");

		X509_NAME_oneline(X509_get_subject_name(psrvCert), szName, sizeof(szName) - 1);
		eCDebugf(LOG_CATEGORY_SSL, "\t subject: %s\n", szName);

		X509_NAME_oneline(X509_get_issuer_name(psrvCert), szName, sizeof(szName) - 1);
		eCDebugf(LOG_CATEGORY_SSL, "\t issuer: %s\n", szName);

		X509_free (psrvCert);

	} else {

		eCDebugf(LOG_CATEGORY_SSL, "The SSL server does not have certificate.\n");
		status = eSSL_SRVCERT_FAILED;
	}
	*/

	return status;
}

SSLConnection::Status SSLConnection::Disconnect() {

	int errSSL = 0;
	/* Shutdown the client side of the SSL connection */
	if (NULL != m_ssl) errSSL = SSL_shutdown(m_ssl);
	//C4C_RET_SSL(err, eSSL_SHUTDOWN_FAILED);

	int errSock = 0;
	/* Terminate communication on a socket */
	if (m_hSock >= 0) errSock = close(m_hSock);
	//C4C_RET_SSL(err, eSSL_CLOSE_FAILED);
	eCDebug(LOG_CATEGORY_SSL) << "Close socket " << m_hSock;
	m_hSock = -1;

	/* Free the SSL structure */
	if (NULL != m_ssl) SSL_free(m_ssl);
	m_ssl = NULL;

	/* Free the SSL_CTX structure */
	if (NULL != m_ctx) SSL_CTX_free(m_ctx);
	m_ctx = NULL;

	C4C_RET_SSL(errSSL, eSSL_SHUTDOWN_FAILED);
	C4C_RET_SSL(errSock, eSSL_CLOSE_FAILED);
	return eSSL_OK;
}
	
bool SSLConnection::IsIpV6() const {

	return m_bIpV6;
}

bool SSLConnection::IsOpen() const {

	return (m_hSock >= 0);
}

bool SSLConnection::IsValidIpV6(const char* pszAddr) { 
	// TODO: use regexp
	return (strlen(pszAddr) > 0) && !( strstr (pszAddr,".") != NULL && isdigit(pszAddr[0]) );
}

void SSLConnection::SetSocketTimeout(unsigned uSeconds) { 

	struct timeval tv = { 0 };
	tv.tv_sec = uSeconds;
	setsockopt(m_hSock, SOL_SOCKET, SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
	setsockopt(m_hSock, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
}

void SSLConnection::SetSocketLockless() { 

	fcntl(m_hSock, F_SETFL, O_NONBLOCK);  // set to non-blocking
	fcntl(m_hSock, F_SETFL, O_ASYNC);     // set to asynchronous I/O
}

bool egt::SSLConnection::IsSslNullPtr()
{
    return m_ssl == nullptr ? true : false;
}

unsigned char *simple_digest(std::string alg, char *buf, unsigned int len, unsigned int *olen)
{
    const EVP_MD *m;
    EVP_MD_CTX *ctx;
    unsigned char *ret;
    OpenSSL_add_all_digests();
    if (!(m = EVP_get_digestbyname(alg.c_str()))) {
        return NULL;
    }
    if (!(ret = (unsigned char *)malloc(EVP_MAX_MD_SIZE))) {
        return NULL;
    }
	ctx = EVP_MD_CTX_create();
    EVP_DigestInit(ctx, m);
    EVP_DigestUpdate(ctx, buf, len);
    EVP_DigestFinal(ctx, ret, olen);
	EVP_MD_CTX_destroy(ctx);
    return ret;
}

std::string SSLConnection::GetPeerCertHash()
{
	std::string hash;
	if (!m_ssl)
	{
		return hash;
	}

	unsigned int ServerCertHashLen = 0;
	unsigned char* ServerCertHash;

    X509* cert;

    if (!(cert = SSL_get_peer_certificate(m_ssl)))
	{
		return hash;
	}

    BIO* bio;
    BUF_MEM* server_cert_buf_mem;

    /* Create a read/write BIO */
    if(!(bio = BIO_new(BIO_s_mem())))
	{
		return hash;
	}

    i2d_X509_bio(bio, cert);

    BIO_get_mem_ptr(bio, &server_cert_buf_mem);

    ServerCertHash = simple_digest("sha1", server_cert_buf_mem->data, server_cert_buf_mem->length, &ServerCertHashLen);

    BIO_free(bio);
    X509_free(cert);

	std::vector<char> hashBuff;
	hashBuff.resize(ServerCertHashLen*2 + 1);

	for (unsigned i = 0; i < ServerCertHashLen; i++)
	{
		sprintf(&hashBuff[i*2],"%02x", ServerCertHash[i]);
	}

    hash = std::string(hashBuff.begin(), (hashBuff.end() - 1));
	hashBuff.clear();
	free(ServerCertHash);

	return hash;
}
