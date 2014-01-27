#include <cstdlib>
#include <ctime>
#include <string>

#include "main.h"
#include "clients/CommandClient.h"
#include "clients/StreamingClient.h"
#include "gui/tools/Allegro.h"

char initSecurity(int argc, char** argv) {
    #ifdef DEBUG_JUPITER
        char* initLog = (char*) "--- Jupiter security initialization ---" ;
        Log(LOG_INFO, initLog) ;
    #endif

    // Check parameters
    if (argc != 3) {
	    printf("Bad calling arguments. Usage : %s keysFilePath counterFilePath\n", argv[0]) ;
	    return -1 ;
    }

    char* keysFilePath ;
    char* counterFilePath ;
    keysFilePath = argv[1] ;
    counterFilePath = argv[2] ;

    // Initialize security subsystem
    switch (SecurityClientInit(keysFilePath, counterFilePath)) {
        case 0:
		    printf("Security subsystem successfully initialized.\n") ;
		    break ;

	    case 1:
		    printf("Error : can't find security keys file.\n") ;
		    return -1 ;

	    case 2:
		    printf("Error : can't find security anti replay counter file.\n") ;
		    return -1 ;
    }

    return 0 ;
}

int main(int argc, char** argv) {
    char successSecurity = initSecurity(argc, argv) ;

    if (successSecurity == 0) {
        srand(time(0)) ;

//        CommandClient::getInstance() ;
        Allegro::getInstance() ;
        StreamingClient* sc = StreamingClient::getInstance() ;
        sc -> start() ;

        Allegro::getInstance() -> run() ;
    }

    return successSecurity ;
}
