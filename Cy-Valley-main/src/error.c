#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "libGameRGR2.h"

void rageQuit(const char* fname,
              const int   lineno,
              const char* fxname,
              const int   errorCode,
              const char* format, ...){
    // List of arguments
    va_list args;
    // display information (if format string is ok)
    fputs("--------------------\n", stderr);
    if(format != NULL){
        // Start retrieving arguments
        va_start(args, format );
        fputs("[ERROR] ", stderr);
        vfprintf(stderr, format, args );       
        // Clean up list
        va_end  (args);
    }
    fputs("\n", stderr);
    fprintf(stderr, "File     : '%s'\n", fname );
    fprintf(stderr, "Function : '%s( )'\n", fxname);
    fprintf(stderr, "Line     :  %d \n", lineno);
    fprintf (stderr, "\nProgram exited with code (%d).\n", errorCode);
    fputs("--------------------\n", stderr);
    fflush(stderr);    
    exit(errorCode);
}

void debug(const char* format, ...){
    // List of arguments
    va_list args;
    // only write to stderr if format is ok
    if(format == NULL){
        RAGE_QUIT(1, "'format' string pointer is NULL !\n");    
    }
    // Start retrieving arguments
    va_start(args, format );
    fputs("[DEBUG] ", stderr);
    vfprintf(stderr, format, args );       
    // Clean up list
    va_end  (args);
    fflush(stderr);    
}

