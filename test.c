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
	
	//map creation
	srand(time(NULL));
	pModel->seed = rand();
	srand(pModel->seed);
	initialize_permutation_table();
	initialize_gradient_table();
	double i, j;
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			pModel->map[(int)i][(int)j] = (int)noise(i/15, j/15);
			/*if(i%2==0){
				pModel->map2[i][j]="💧";
			}
			else if(j%2==0){
				pModel->map2[i][j]="🌱";
			}
			else{
				pModel->map2[i][j]="⏳";
			}*/
		}
	}
	replaceWithBiomes(pModel->map, pModel->map2);
	replaceWithBiomes2(pModel->map2);
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);
	}
	else{
		if(pEvt->code == KEY_ARROW_DOWN){
			if(pModel->y<80){
	  			pModel->y++;
	  		}
		}
		if(pEvt->code == KEY_ARROW_UP){
			if(pModel->y>0){
	  			pModel->y--;
	  		}
		}
		if(pEvt->code == KEY_ARROW_RIGHT){
			if(pModel->x<80){
	  			pModel->x++;
	  		}
			
		}
		if(pEvt->code == KEY_ARROW_LEFT){
			if(pModel->x>0){
	  			pModel->x--;
	  		}
		}
	}
	clear();
}

int update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
	
	return 0;
}

void draw(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	int id = 2;
	if(pModel->game_status!=5){
		draw_menu(pScreen, pModel, id, pModel->game_status);
	}
	else{
		for(int i=1; i<20; i++){
			for(int j=1; j<20; j++){
				if(i==10 && j==10){
				drawText(pScreen, i, j, "🐰", 0);
				}
				else{
					drawText(pScreen, i, j, pModel->map2[i-1+pModel->x][j-1+pModel->y], 0);
				}
				
			}
		}
	}
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
	
	
	
	gameLoop(createGame(100, 100, &model, &cb, 0));
	  
	return 0; 
}
