//export LD_LIBRARY_PATH=lib
#include "jeu.h"

void init(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	
	//Player's coordinates when spawned	
	pModel->x = 50;
	pModel->y = 50;
	pModel->x_cam = pModel->x-9;
	pModel->y_cam = pModel->y-9;
	
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
	int permutation[TABLE_SIZE];
	double gradient[TABLE_SIZE][2];
	
	srand(time(NULL));
	pModel->seed = rand();
	srand(pModel->seed);
	
	initialize_permutation_table(permutation);
	initialize_gradient_table(gradient);
	
	double i, j;
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			pModel->map[(int)i][(int)j] = (int)noise(i/15, j/15, permutation, gradient);
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
	while(pModel->map2[10+pModel->x][10+pModel->y].go_through!=1){ 
		//debug("+");
		pModel->map2[10+pModel->x][10+pModel->y++];
	}
	
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);	
	}
	else{
		if(pEvt->code == KEY_ARROW_DOWN){
			if(pModel->y_cam<80 && pModel->map2[pModel->x][pModel->y+1].go_through){	
	  			pModel->y_cam++;
	  			pModel->y++;		
	  		}
	  		else if( pModel->y_cam==80 && pModel->y<=100 && pModel->map2[pModel->x][pModel->y+1].go_through){
	  			pModel->y++;
	  		}
		}
		if(pEvt->code == KEY_ARROW_UP){
			if(pModel->y_cam>0 && pModel->map2[pModel->x][pModel->y-1].go_through){
	  			pModel->y_cam--;
	  			pModel->y--;
	  		}
	  		else if( pModel->y_cam==0 && pModel->y>=0 && pModel->map2[pModel->x][pModel->y+1].go_through){
	  			pModel->y--;
	  		}
		}
		if(pEvt->code == KEY_ARROW_RIGHT){
			if(pModel->x_cam<80 && pModel->map2[pModel->x+1][pModel->y].go_through){
	  			pModel->x_cam++;
	  			pModel->x++;
	  		}
	  		else if( pModel->x_cam==80 && pModel->x<=100 && pModel->map2[pModel->x+1][pModel->y].go_through){
	  			pModel->x++;
	  		}
			
		}
		if(pEvt->code == KEY_ARROW_LEFT){
			if(pModel->x_cam>0 && pModel->map2[pModel->x-1][pModel->y].go_through){
	  			pModel->x_cam--;
	  			pModel->x--;
	  		}
	  		else if( pModel->x_cam==0 && pModel->x>=0 && pModel->map2[pModel->x-1][pModel->y].go_through){
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
		for(int i=0; i<CAMERA_SIZE; i++){
			for(int j=0; j<CAMERA_SIZE; j++){
				int i2 = i + (pScreen->width-CAMERA_SIZE)/2 + pModel->x - pModel->x_cam - 10;
				int j2 = j + (pScreen->height-CAMERA_SIZE)/2 +  pModel->y - pModel->y_cam - 10;
				if(i==CAMERA_SIZE/2 && j==CAMERA_SIZE/2){
					drawText(pScreen, i2, j2, "🐰", 0);
				}
				else{
					drawText(pScreen, i2, j2, pModel->map2[i+pModel->x][j+pModel->y].name, 0);
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
	
	
	
	gameLoop(createGame(100, 50, &model, &cb, 0));
	  
	return 0; 
}
