//export LD_LIBRARY_PATH=lib
#include "jeu.h"

void init(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	
	//Player's coordinates when spawned	
	pModel->x = 15;
	pModel->y = 15;
	
	//The y arrow's coordinates 
	pModel->arrow_position = 6;
	
	//Initialisation of colors id
	setColor(1, 255, 255, 0);
	setColor(2, 255, 255, 255);
	setColorPair(1, 1, 0);
	setColorPair(2, 2, 0);
	
	//Game status (1 = Main menu, 2 = Settings, 3 = Load menu, 4 = New game or load, 5 = Game)
	pModel->game_status = 1;
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);
	}
	/*switch(pModel->game_status){
		case 1:
			menu(pScreen, pEvt, pModel);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			menu(pScreen, pEvt, pModel);
			break;
		case 5:
	}*/
}

int update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
	
	return 0;
}

void draw(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	int id = 2;
	/*for(int i=10; i<21; i++){
		for(int j=10; j<21; j++){
			if(i==15 && j==15){
				drawText(pScreen, i, j, "🐰", 0);
			}
			else{
				drawText(pScreen, i, j, "🌱", 0);
			}
		}	
	}*/
	draw_menu(pScreen, pModel, id, pModel->game_status);
}

void finish(void* pUserData){
	
}


int main() {
	Model model;
	Callbacks cb;
	cb.cbInit= init;        
	cb.cbEvent= event;        
	cb.cbUpdate= update;
	cb.cbDraw= draw;
	cb.cbFinish= finish;
	
	
	
	gameLoop(createGame(200, 200, &model, &cb, 0));
	  
	return 0; 
}
