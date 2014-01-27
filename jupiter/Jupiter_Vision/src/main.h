#ifndef __JUPITER__MAIN_MODULE__
#define __JUPITER__MAIN_MODULE__

extern "C" {
    #include <Log.h>
    #include <Security_Client.h>
}

/** @brief  Initialize the security module. */
char initSecurity(int argc, char** argv) ;

/** @brief  Start of the program. */
int main(int argc, char** argv) ;

#endif
