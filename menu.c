#include "jeu.h"

void menu(Screen* pScreen, Event* pEvt, Model* pModel){
	if(pEvt->code == KEY_ARROW_DOWN){
	  	if(pModel->arrow_position < 17){
	  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
	  		pModel->arrow_position+=6;
	  	}
	}
	if(pEvt->code == KEY_ARROW_UP){
		if(pModel->arrow_position > 6){
	  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
	  		pModel->arrow_position-=6;
	  	}
	  }
	if(pEvt->code == KEY_RETURN){
		switch(pModel->arrow_position){
			case 6:
				pModel->game_status = 1;
				break;
			case 12:
				pModel->game_status = 2;
				break;
			default:
				kill(getpid(), SIGINT);
				break;
		}
	}
}
