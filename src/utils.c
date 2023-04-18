#include <sys/time.h>
#include <string.h>

#include "libGameRGR2.h"

unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 

void checkGame(GameData* pGame, int errCode){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    // Check params
    if(pGame == NULL){
        RAGE_QUIT(errCode, "Game data pointer NULL !\n");
    }
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    // Check internal pointers
    if(pScr == NULL){
        RAGE_QUIT(errCode+1, "Game screen pointer NULL !\n");
    }
    if(pDat == NULL){
        RAGE_QUIT(errCode+2, "Game user data pointer NULL !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(errCode+3, "Game user callback pointer NULL !\n");
    }    
}

int checkEvent(GameData* pGame){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    Event      evt;
    int        ch = ERR+1;
    long       value = KEY_NONE;
    int        size  = 0;
    int        flag  = 0;
    // Check params
    checkGame(pGame, 3000);
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    
    // Get all key values from the stdin
    // Some keys generate several bytes
    while( (ch=getch()) != ERR ){  
        value = (value<<8) | ch;
        flag  = 0;
        size++;
        // ASCII flag
        flag |= (((size==1) && (value!=EXT_ESC)) || ((size==2) && (value!=EXT_CSI))) && (value>=0) && (value<=127);        
        // SPECIAL1 flag2
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_SPEC1);        
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_SPEC2);        
        // CSI flag
        flag |= (size==3) && ((value & 0xFFFF00    ) == EXT_CSI) && (value != HDR_FN1) && (value != HDR_FN2); 
        // SS3 flag
        flag |= (size==3) && ((value & 0xFFFF00    ) == EXT_SS3); 
        // FUNCTION flags
        flag |= (size==5) && ((value & 0xFFFFFF00FF) == EXT_FN1); 
        flag |= (size==5) && ((value & 0xFFFFFF00FF) == EXT_FN2); 
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_FN3); 
        
        //* // DEBUG
        debug("|%3d| => [%0p]\n", ch, value); 
        if( flag ){
            debug("===>>>\n");
        } 
        // END DEBUG */
        
        // Send event to user code
        if( flag ){
            evt.code = value;
            pCb->cbEvent(pDat, pScr, &evt);            
            //value    = KEY_NONE;
            //size     = 0;
        }
    }
    
    // ESCAPE flag : exit request
    if( (size==1) && (value == EXT_ESC) ){
        return 1;
    }
    else{
        return 0;
    }
}


//-----------------------------------------
// DRAW
//-----------------------------------------
void setColor(unsigned char id, unsigned char r, unsigned char g, unsigned char b){
    int rr = (1000*r)/255;
    int gg = (1000*g)/255;
    int bb = (1000*b)/255;
    init_color(id, rr, gg, bb);
}
void setColorPair(unsigned char id, unsigned char txtId, unsigned char backId){
    init_pair(id, txtId, backId);
}
void drawText(Screen* pScr, int x, int y, char* pText, int clrId){
    // Local buffer to copy string
    char pWrite[256] = {0};
    if(pText == NULL){
        RAGE_QUIT(50, "Text pointer NULL !\n");
    }
    if(pScr == NULL){
        RAGE_QUIT(51, "Screen pointer NULL !\n");
    }
    // TODO issue when trying to print the trailing chars of a string started on the left edge of the screen !!
    // TODO issue when printing an emoji : when reaching the right border of the screen
    if(x>=0 && y>=0 && x<pScr->width && y<pScr->height){
        move(y, x);
        attron(COLOR_PAIR(clrId));
        // limit the size of the string in order to avoid printing outside the edges
        int sz  = pScr->width - x;
        int len = strlen(pText);
        if(sz > len+1){
            sz = len;
        }
        if(len > 255){
            RAGE_QUIT(52, "pText string exceeds 255 chars !\n");            
        } 
        strcpy(pWrite, pText);
        pWrite[sz] = '\0';        
        printw(pWrite);
        //attroff(COLOR_PAIR(clrId));
    }
}
void drawLine(Screen* pScr, int x, int y, int w, char ch, int clrId){
    if(pScr == NULL){
        RAGE_QUIT(60, "Screen pointer NULL !\n");
    }
    move(y, x);
    attron(COLOR_PAIR(clrId));
    for(int dx=0; dx<w && (x+dx)<pScr->width; dx++){
        if(x+dx >= 0){
            mvaddch(y, x+dx, ch);    
        }
    }    
}




