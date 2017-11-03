#include <iostream>
#include <unistd.h>
#include <sstream>

using namespace std;

pid_t GetPIDbyName ( char* ps_name )
{
    FILE *fp;
    char *cmd= ( char* ) calloc ( 1,200 );
    sprintf ( cmd,"pidof %s",ps_name );
    fp=popen ( cmd,"r" );
    fread ( cmd,1,200,fp );
    fclose ( fp );
    return atoi ( cmd );
}

int main ( int argc, char **argv )
{

    if ( argc != 2 )
    {
        cout << "Deamon: there isn't a process! " << "argc = " << argc << endl;
        return 0;
    }

    int cnt = 0;
    int argId = argc - 1;
    cout << "Deamon: started for {" << argv[argId] << "} process" << endl;

    if ( fork() == 0 )
    {
        while ( 1 )
        {
            if ( GetPIDbyName ( argv[argId] ) == 0 )
            {
                ++cnt;
                system ( "./autorun.sh" );
                cout << "#" << cnt << ") Deamon: process {" << argv[argId] << "} is starting" << endl;
            }
            sleep ( 1 );
        }
    }

    return 0;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
