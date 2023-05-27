#include "game.h"

void menu(Screen* pScreen, Event* pEvt, Model* pModel){
	//To scroll down in the menu
	if(pEvt->code == KEY_S_LOWER || pEvt->code == KEY_S){
	  	if(pModel->arrow_position < 17 && pModel->game_status!=2){
	  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
	  		pModel->arrow_position+=6;
	  	}
	}
	//To move up the menu
	if(pEvt->code == KEY_Z_LOWER || pEvt->code == KEY_Z){
		if(pModel->arrow_position > 6 && pModel->game_status!=2){
	  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
	  		pModel->arrow_position-=6;
	  	}
	  }
	//To select in the menu
	if(pEvt->code == KEY_E_LOWER || pEvt->code == KEY_E){
		clear();
		switch(pModel->arrow_position){
			case 6:
				if(pModel->game_status == 1){
					pModel->game_status = 4; //Display New game
				}
				else{
					//map creation
					create_map(pModel);
					pModel->game_status = 5;
					
				}
				break;
			case 12:
				if(pModel->game_status == 1){
					pModel->game_status = 2; //Go to Setting
				}
				else{ // To get back a the last game if it was saved before
					loadModel(pModel, "save.bin");
					
				}		
				break;
			case 18:
				if(pModel->game_status==1){ //If we select back or quit
					kill(getpid(), SIGINT);
				}
				pModel->game_status=1;
				break;
			case 24: //We can't go any lower
				break;
			case 30:
				pModel->game_status = 1; //Main menu
		}
		//drawText(pScreen, 2, pModel->arrow_position, " ", 0);
		if(pModel->game_status == 2){
			pModel->arrow_position=30;
		}
		else{
			pModel->arrow_position=6;
		}
	}
}

void draw_menu(Screen* pScreen, Model* pModel, int id, char status){
	for(int k=5; k<18; k+=6){
		if(k+1 == pModel->arrow_position){
			id = 1;
		}
		//To draw the menu
		drawText(pScreen, 5, k, "|", id);
		drawText(pScreen, 5, k+1, "|", 0);
		drawText(pScreen, 5, k+2, "|", 0);
		drawLine(pScreen, 6, k-1, 25, '-', 0);
		drawLine(pScreen, 6, k+3, 25, '-', 0);
		drawText(pScreen, 31, k, "|", 0);
		drawText(pScreen, 31, k+1, "|", 0);
		drawText(pScreen, 31, k+2, "|", 0);
		if(k+1 == pModel->arrow_position){
			id = 2;
		}
	}

	switch(status){
		case 1:
			//Display the different choice of the menu
			drawText(pScreen, 16, 6, "Play", 1);
			drawText(pScreen, 14, 12, "Settings", 0);
			drawText(pScreen, 16, 18, "Quit", 0);
			break;
		case 2:
			for(int k=23; k<30; k+=6){
				if(k+1 == pModel->arrow_position){
					id = 1;
				}
				//Drawing the 2nd menu
				drawText(pScreen, 5, k, "|", id);
				drawText(pScreen, 5, k+1, "|", 0);
				drawText(pScreen, 5, k+2, "|", 0);
				drawLine(pScreen, 6, k-1, 25, '-', 0);
				drawLine(pScreen, 6, k+3, 25, '-', 0);
				drawText(pScreen, 31, k, "|", 0);
				drawText(pScreen, 31, k+1, "|", 0);
				drawText(pScreen, 31, k+2, "|", 0);
				if(k+1 == pModel->arrow_position){
					id = 2;
				}
			}
			//Drawing the setting menu
			for(int k=5; k<18; k+=6){
				drawText(pScreen, 33, k, "|", id);
				drawText(pScreen, 33, k+1, "|", 0);
				drawText(pScreen, 33, k+2, "|", 0);
				drawLine(pScreen, 34, k-1, 25, '-', 0);
				drawLine(pScreen, 34, k+3, 25, '-', 0);
				drawText(pScreen, 59, k, "|", 0);
				drawText(pScreen, 59, k+1, "|", 0);
				drawText(pScreen, 59, k+2, "|", 0);
			}
			//Setting menu
			drawText(pScreen, 14, 6, "Up : Z", 1);
			drawText(pScreen, 13, 12, "Down : S", 0);
			drawText(pScreen, 13, 18, "Right : D", 0);
			drawText(pScreen, 13, 24, "Left : Q", 0);
			drawText(pScreen, 16, 30, "Back", 0);
			drawText(pScreen, 41, 6, "Break : A", 0);
			drawText(pScreen, 40, 12, "Interact : E", 0);
			drawText(pScreen, 41, 18, "Save : M", 0);
			break;
		case 4:
			//Display the second menu interface
			drawText(pScreen, 14, 6, "New game", 1);
			drawText(pScreen, 14, 12, "Load game", 0);
			drawText(pScreen, 16, 18, "Back", 0);
			break;
	}
	drawText(pScreen, 2, pModel->arrow_position, "➡️", 0); //Drawing the arrow to be able to select the different menu's option
}
