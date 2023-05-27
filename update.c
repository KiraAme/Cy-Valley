#include "game.h"
int update2(void* pUserData, Screen* pScreen, unsigned long deltaTime){
        Model* pModel = (Model*)pUserData;
        //time start when a game is launch
        if(pModel->game_status==5){
        	//timer
		    pModel->elapsed+=1;
		    if(pModel->elapsed==100){
		        pModel->secglob+=1;
		        pModel->elapsed=0;
		    }
		}

		pModel->sec = pModel->secglob%60;
        pModel->min=pModel->secglob/60;
	return 0;   	
}
