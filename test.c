//export LD_LIBRARY_PATH=lib
#include "jeu.h"

void init(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	//Player's inventory and health when spawned
	pModel->p1.health_point=3;
	pModel->p1.quest_advancement=0;
	pModel->p1.inventory.flower_num=0;
	pModel->p1.inventory.have_pickaxe=0;
	pModel->p1.inventory.have_sword=0;
	//Player's coordinates when spawned	
	pModel->x = SIZEMAP/2;
	pModel->y = SIZEMAP/2;
	pModel->cam_x = pModel->x-10;
	pModel->cam_y = pModel->y-10;
	//farmer init
	Surface farmer;
	farmer.name="👨‍🌾";
	farmer.brk=0;
	farmer.take=0;
	farmer.push=0;
	farmer.go_through=1;
	farmer.npc1.is_npc=1;
	farmer.npc1.flower_num=0;
	farmer.id=5;
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
	for(i=0; i<SIZEMAP; i++){
		for(j=0; j<SIZEMAP; j++){
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
	while(pModel->map2[pModel->x][pModel->y].go_through!=1){ 
		//debug("+");
		pModel->map2[pModel->x][pModel->y++];
		pModel->map2[pModel->x][pModel->cam_y++];
	}
	pModel->map2[pModel->x-1][pModel->y]=farmer;
	
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);	
	}
	else{
		if(pEvt->code == KEY_S_LOWER){
			if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y+1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->y++;
	  			pModel->cam_y++;
	  		}
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x][pModel->y+1].go_through ){
				pModel->y++;
			}
		}
		if(pEvt->code == KEY_Z_LOWER){
			if(pModel->cam_y>0 && pModel->map2[pModel->x][pModel->y-1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){
	  			pModel->y--;
	  			pModel->cam_y--;
	  		}
	  		else if(pModel->y>0 && pModel->map2[pModel->x][pModel->y-1].go_through ){
				pModel->y--;
			}
		}
		if(pEvt->code == KEY_D_LOWER){
			if(pModel->cam_x<SIZEMAP - CAMERA_SIZE && pModel->map2[pModel->x+1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2  ){	
	  			pModel->x++;
	  			pModel->cam_x++;
	  		}
	  		else if(pModel->x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].go_through ){
				pModel->x++;
			}
			
		}
		if(pEvt->code == KEY_Q_LOWER){
			if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2  ){
	  			pModel->x--;
	  			pModel->cam_x--;
	  		}
	  		else if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].go_through ){
				pModel->x--;
			}
		}
		if(pEvt->code == KEY_E_LOWER){
			if(pModel->map2[pModel->x][pModel->y].id==1 && pModel->p1.inventory.flower_num<10){
				pModel->map2[pModel->x][pModel->y].name="🍂";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.flower_num++;
			}
			if(pModel->map2[pModel->x][pModel->y].id==7 && pModel->p1.inventory.fish_num<3){
				pModel->map2[pModel->x][pModel->y].name="💧";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.fish_num++;
			}
			if(pModel->map2[pModel->x][pModel->y].npc1.is_npc ){
				if(pModel->p1.quest_advancement==0){
					if(pModel->map2[pModel->x][pModel->y].npc1.flower_num<20){
						while(pModel->p1.inventory.flower_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.flower_num<=20){
							pModel->map2[pModel->x][pModel->y].npc1.flower_num++;
							pModel->p1.inventory.flower_num--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.flower_num>=20){
						pModel->p1.quest_advancement++;
						pModel->p1.inventory.have_pickaxe=1;
						}
					}
					
				}
				if(pModel->p1.quest_advancement==1){
					if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<10){
						while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<=10){
							pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
							pModel->p1.inventory.ore_mineral--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral>=10){
							pModel->p1.quest_advancement++;
							for(int i=0;i<SIZEMAP;i++){
								for(int j=0;j<SIZEMAP;j++){
									if(pModel->map2[i][j].id==3 || pModel->map2[i][j].id==7){
										pModel->map2[i][j].go_through=1;	
									}
								}			
							}				
						}
					}
				}
				if(pModel->p1.quest_advancement==2){
					if(pModel->map2[pModel->x][pModel->y].npc1.fish_num<9){
						while(pModel->p1.inventory.fish_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.fish_num<=15){
							pModel->map2[pModel->x][pModel->y].npc1.fish_num++;
							pModel->p1.inventory.fish_num--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.fish_num>=9){
							pModel->p1.quest_advancement++;
						}
					}
			      }
						
			}
		}
		if(pEvt->code ==  KEY_A_LOWER){
			if(pModel->map2[pModel->x][pModel->y-1].brk && pModel->p1.inventory.ore_mineral<5 && pModel->p1.inventory.have_pickaxe){
				pModel->map2[pModel->x][pModel->y-1].name="💨";
				pModel->map2[pModel->x][pModel->y-1].go_through=1;
				pModel->map2[pModel->x][pModel->y-1].brk=0;
				pModel->p1.inventory.ore_mineral++;
			}
		}
		if(pEvt->code == KEY_R_LOWER){
			if(pModel->x][pModel->y-1].push pModel->x-1][pModel->y].push && pModel || pModel->x][pModel->y+1].push || pModel->x+1][pModel->y].push){
				if(pModel->map2[pModel->x][pModel->y-2].go_through==0 || pModel->map2[pModel->x-2][pModel->y].go_through==0 || pModel->map2[pModel->x][pModel->y+2].go_through==0 || pModel->map2[pModel->x+2][pModel->y].go_through==0){
					if(pEvt->code == KEY_Z_LOWER){
						if(pModel->cam_y>0 && pModel->map2[pModel->x][pModel->y-1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){
							(pModel->map2[pModel->x][pModel->y].id==8
						}
						(pModel->map2[pModel->x][pModel->y].id==8				
						
					}
				}
			
			}
		
		}				
				
	}
	
	clear();
}

int update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
	char a[10];
	sprintf(a, "%d", deltaTime/1000, 0);
	drawText(pScreen, 10, 1, a, 0);
	return 0;   	
}
void draw(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	int id = 2;
	
	char buffer[4];
	char buffer2[4];
	char buffer3[4];
	char buffer4[4];
	char buffer5[4];
	char buffer6[4];
	char buffer7[4];
	sprintf(buffer,"%d",pModel->x);
	sprintf(buffer2,"%d",pModel->y);
	sprintf(buffer3,"%d",pModel->p1.inventory.flower_num);
	sprintf(buffer4,"%d",pModel->p1.inventory.have_pickaxe);
	sprintf(buffer5,"%d",pModel->p1.inventory.have_sword);
	sprintf(buffer6,"%d",pModel->p1.inventory.ore_mineral);
	sprintf(buffer7,"%d",pModel->p1.inventory.fish_num);
	
	if(pModel->game_status!=5){
		draw_menu(pScreen, pModel, id, pModel->game_status);
	}
	else if(pModel->p1.quest_advancement==3){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you completed all quests !",0);
	}
	else{
		
		for(int i=0; i<CAMERA_SIZE; i++){
			for(int j=0; j<CAMERA_SIZE; j++){
				int dif_x = pModel->x - pModel->cam_x - CAMERA_SIZE/2;
				int dif_y = pModel->y - pModel->cam_y - CAMERA_SIZE/2;
				int i2 = i + (pScreen->width-CAMERA_SIZE)/2;
				int j2 = j + (pScreen->height-CAMERA_SIZE)/2;
				if(i==CAMERA_SIZE/2 + dif_x && j==CAMERA_SIZE/2 + dif_y){
					drawText(pScreen, i2, j2, "🐰", 0);
				
				}
				else{
					drawText(pScreen, i2, j2, pModel->map2[i+pModel->cam_x][j+pModel->cam_y].name, 0);
				}
			}
		}
		drawText(pScreen,0,48,"x=",0);
		drawText(pScreen,0,49,"y=",0);
		drawText(pScreen,2,48,buffer,0);
		drawText(pScreen,2,49,buffer2,0);
		
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+2, 2+(pScreen->height-CAMERA_SIZE)/2,"🌼 ", 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+2, 6+(pScreen->height-CAMERA_SIZE)/2,"⛏️ ", 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+2, 10+(pScreen->height-CAMERA_SIZE)/2,"⚔️ ", 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+2, 14+(pScreen->height-CAMERA_SIZE)/2,"💎 ", 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+2, 18+(pScreen->height-CAMERA_SIZE)/2,"🐟 ", 0);
		
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+6, 2+(pScreen->height-CAMERA_SIZE)/2,buffer3, 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+6, 6+(pScreen->height-CAMERA_SIZE)/2,buffer4, 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+6, 10+(pScreen->height-CAMERA_SIZE)/2,buffer5, 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+6, 14+(pScreen->height-CAMERA_SIZE)/2,buffer6, 0);
		drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE+6, 18+(pScreen->height-CAMERA_SIZE)/2,buffer7, 0);


		for(int i=0;i<CAMERA_SIZE;i++){
			drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE, i+(pScreen->height-CAMERA_SIZE)/2,"|", 0);
			drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE*2+CAMERA_SIZE/2,i+(pScreen->height-CAMERA_SIZE)/2,"|", 0);
		}
		for(int i=0; i<=20; i+=4){
			drawLine(pScreen, (pScreen->width-CAMERA_SIZE)/2+CAMERA_SIZE+1,(pScreen->height-CAMERA_SIZE)/2+i,9,'-',0);
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
