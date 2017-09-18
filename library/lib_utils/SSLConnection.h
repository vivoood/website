// SSLConnection.h ----------------------------------------------------------------------

#ifndef _SSLCONNECTION_H_
#define _SSLCONNECTION_H_

#include <string>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/**
 egt namespace.
 */
namespace egt {

/**
 SSLConnection class.
  
 General purpose ssl connection
 */
class SSLConnection {
 
public:

	/** constructor */
	SSLConnection();

	/** virtual destructor */
	virtual ~SSLConnection();

	enum Status {

		eSSL_OK,
		eSSL_TIMEOUT,
		eSSL_NOTINT,
		eSSL_CREATE_SSLCTX_FAILED,
		eSSL_CREATE_SSL_FAILED,
		eSSL_LOAD_CERT_FAILED,
		eSSL_PKEY_FAILED,
		eSSL_PKEY_NOTMATCHED,
		eSSL_CA_FAILED,
		eSSL_READ_FAILED,
		eSSL_WRITE_FAILED,
		eSSL_SHUTDOWN_FAILED,
		eSSL_CLOSE_FAILED,
		eSSL_SOCKET_FAILED,
		eSSL_HANDSHAKE_FAILED,
		eSSL_SRVCERT_FAILED,
		eSSL_SRVCONNECT_FAILED,
		eSSL_NO_IPADDRESS,
		eSSL_NO_CABLE,
		eSSL_LAST
	};

    enum {
        SOCKET_CONNECTION_TIMEOUT_IN_SECONDS= 1,
        SSL_CONNECT_TIMEOUT_IN_SECONDS= 12
    };

	/**
	* Connect
	* @param pszAddr - address
	* @param nPort - port
	* @param pszPEMFile - certificate file
	* @param pszCAFile - certificate authority file
	* @param pszEth - hw interface
	* @return Status
	*/
	Status Connect(const char* pszAddr, int nPort, const char* pszPEMFile, const char* pszCAFile = NULL, const char* pszEth = "eth0");

	/**
	* Open ipv6 socket
	* @param pszAddr - address
	* @param nPort - port
	* @return Status
	*/
	Status OpenV6Socket(const char* pszAddr, int nPort);

	/**
	* Read bytes
	* @param pBuf - buffer
	* @param nSize (in/out) - buffer size / read bytes
	* @param bBlocking - blocking mode flag
	* @return Status
	*/
	Status Read(void* pBuf, int& nSize, bool bBlocking = true);

	/**
	* Write bytes
	* @param pBuf - buffer
	* @param nSize (in/out) - buffer size / written bytes
	* @return Status
	*/
	Status Write(const void* pBuf, int& nSize);

	/**
	* Dump info about server/client certificates
	* @return Status
	*/
	Status ShowServerCert();

	/**
	* Disconnect
	* @return Status
	*/
	Status Disconnect();

	/**
	* Check the address
	* @return true when the address is ipv6
	*/
	bool IsIpV6() const;

	/**
	* Check if the connection
	* @return true when the connection is open
	*/
	bool IsOpen() const;

	std::string GetPeerCertHash();
    
    /**
     * @return true if ssl is nullptr
     */
    bool IsSslNullPtr();
    

private:

	void SetSocketTimeout(unsigned uSeconds);

	void SetSocketLockless();

	static bool IsValidIpV6(const char* pszAddr);

private:
  
	int         m_hSock;
	SSL_CTX*    m_ctx;
	SSL*        m_ssl;
	const SSL_METHOD* m_meth;
	bool        m_bIpV6;
	std::string m_strEth;
};

} // namespace egt
	
#endif // _SSLCONNECTION_H_

