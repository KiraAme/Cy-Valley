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
	//
	pModel->temp1.name="🌱";
	pModel->temp1.brk=0;
	pModel->temp1.take=1;
	pModel->temp1.push=0;
	pModel->temp1.go_through=1;
	pModel->temp1.npc1.is_npc=0;
	pModel->temp1.npc1.flower_num=0;
	pModel->temp1.id=1;
	//Player's coordinates when spawned	
	pModel->x = SIZEMAP/2;
	pModel->y = SIZEMAP/2;
	pModel->cam_x = pModel->x-CAMERA_SIZE/2;
	pModel->cam_y = pModel->y-CAMERA_SIZE/2;
	//farmer init
	Surface farmer;
	farmer.name="👨‍🌾";
	farmer.brk=0;
	farmer.take=0;
	farmer.push=0;
	farmer.go_through=1;
	farmer.npc1.is_npc=1;
	farmer.npc1.flower_num=0;
	farmer.npc1.fish_num=0;
	farmer.npc1.ore_mineral=0;
	farmer.id=5;
	//forger init
	Surface forger;
	forger.name="👷‍♂️";
	forger.brk=0;
	forger.push=0;
	forger.take=1;
	forger.go_through=1;
	forger.npc1.is_npc=1;
	forger.npc1.ore_mineral=0;
	forger.id=9;
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
	pModel->map2[pModel->x+1][pModel->y]=forger;
	
	
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);	
	}
	else{
		//hp loss
		
		//player going down
		if(pEvt->code == KEY_S_LOWER||pEvt->code == KEY_S){
			if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y+1].id==8 && pModel->map2[pModel->x][pModel->y+2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y+2];
	  				pModel->map2[pModel->x][pModel->y+2]=pModel->map2[pModel->x][pModel->y+1];
	  				pModel->map2[pModel->x][pModel->y+1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y++;
	  				pModel->cam_y++;
	  		}
			else if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y+1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->y++;
	  			pModel->cam_y++;
	  		}
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x][pModel->y+1].id==8 && pModel->map2[pModel->x][pModel->y+2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y+2];
	  				pModel->map2[pModel->x][pModel->y+2]=pModel->map2[pModel->x][pModel->y+1];
	  				pModel->map2[pModel->x][pModel->y+1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y++;
	  		}
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x][pModel->y+1].go_through ){
				pModel->y++;
			}
			if(pModel->map2[pModel->x][pModel->y].id==10 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
			
		
		}
		//player going up
		if(pEvt->code == KEY_Z_LOWER||pEvt->code == KEY_Z){
			if(pModel->cam_y>0 && pModel->map2[pModel->x][pModel->y-1].id==8 && pModel->map2[pModel->x][pModel->y-2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y-2];
	  				pModel->map2[pModel->x][pModel->y-2]=pModel->map2[pModel->x][pModel->y-1];
	  				pModel->map2[pModel->x][pModel->y-1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y--;
	  				pModel->cam_y--;
	  		}
			else if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y-	1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->y--;
	  			pModel->cam_y--;
	  		}
	  		else if(pModel->y>0 && pModel->map2[pModel->x][pModel->y-1].id==8 && pModel->map2[pModel->x][pModel->y-2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y-2];
	  				pModel->map2[pModel->x][pModel->y-2]=pModel->map2[pModel->x][pModel->y-1];
	  				pModel->map2[pModel->x][pModel->y-1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y--;
	  		}
	  		//check if player is on a side of the map
	  		else if(pModel->y>0 && pModel->map2[pModel->x][pModel->y-1].go_through ){
				pModel->y--;
			}
			if(pModel->map2[pModel->x][pModel->y].id==8 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
			if(pModel->map2[pModel->x][pModel->y].id==10 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
		}
		//player going right
		if(pEvt->code == KEY_D_LOWER ||pEvt->code == KEY_D ){
			if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  				pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  				pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x++;
	  				pModel->cam_x++;
	  		}
			else if(pModel->cam_x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->x++;
	  			pModel->cam_x++;
	  		}
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  				pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  				pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x++;
	  		}
			if(pModel->map2[pModel->x][pModel->y].id==8 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
			if(pModel->map2[pModel->x][pModel->y].id==10 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
			
		}
		//player going left
		if(pEvt->code == KEY_Q_LOWER||pEvt->code == KEY_Q){
			if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
	  				pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x-1][pModel->y];
	  				pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x--;
	  				pModel->cam_x--;
	  		}
			else if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->x--;
	  			pModel->cam_x--;
	  		}
	  		else if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
	  				pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  				pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x--;
	  		}	
			if(pModel->map2[pModel->x][pModel->y].id==8 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
			if(pModel->map2[pModel->x][pModel->y].id==10 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					pModel->p1.health_point--;
				}
			}
		}
		if(pEvt->code == KEY_E_LOWER||pEvt->code == KEY_E){
			if(pModel->map2[pModel->x][pModel->y].id==1 && pModel->p1.inventory.flower_num<10 && pModel->map2[pModel->x][pModel->y].take){
				pModel->map2[pModel->x][pModel->y].name="🍂";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.flower_num++;
				pModel->score+=20;
			}
			if(pModel->map2[pModel->x][pModel->y].id==7 && pModel->p1.inventory.fish_num<3 && pModel->map2[pModel->x][pModel->y].take){
				pModel->map2[pModel->x][pModel->y].name="💧";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.fish_num++;
				pModel->score+=50;
			}
			if(pModel->map2[pModel->x][pModel->y].id==5 ){
				if(pModel->p1.quest_advancement==0){
					if(pModel->map2[pModel->x][pModel->y].npc1.flower_num<20){
						while(pModel->p1.inventory.flower_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.flower_num<=20){
							pModel->map2[pModel->x][pModel->y].npc1.flower_num++;
							pModel->p1.inventory.flower_num--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.flower_num==20){
						pModel->p1.quest_advancement++;
						pModel->p1.inventory.have_pickaxe=1;
						pModel->score+=1000;
						}
					}
					
				}
				if(pModel->p1.quest_advancement==1){
					if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<10){
						while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<=10){
						
							pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
							pModel->p1.inventory.ore_mineral--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral==10){
							pModel->p1.quest_advancement++;
							for(int i=0;i<SIZEMAP;i++){
								for(int j=0;j<SIZEMAP;j++){
									if(pModel->map2[i][j].id==3 || pModel->map2[i][j].id==7){
										pModel->map2[i][j].go_through=1;
										
									}
								}			
							}
							pModel->score+=1000;				
						}
					}
				}
				if(pModel->p1.quest_advancement==2){
					if(pModel->map2[pModel->x][pModel->y].npc1.fish_num<9){
						debug("+");
						while(pModel->p1.inventory.fish_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.fish_num<=9){
							debug("+");
							pModel->map2[pModel->x][pModel->y].npc1.fish_num++;
							pModel->p1.inventory.fish_num--;
						}
						if(pModel->map2[pModel->x][pModel->y].npc1.fish_num==9){
							pModel->score+=1000;
							pModel->p1.quest_advancement++;
							
						}
					}
			      }
						
			}
			if(pModel->map2[pModel->x][pModel->y].id==9){
				if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<5){
					while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<=20){
							pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
							pModel->p1.inventory.ore_mineral--;
					}
					if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral==5){
						pModel->p1.inventory.have_sword=1;
						pModel->score+=1000;
					}
				}
			
					
					
			}
		}
		if(pEvt->code ==  KEY_A_LOWER ||pEvt->code == KEY_A){
			if(pModel->map2[pModel->x][pModel->y-1].brk && pModel->p1.inventory.ore_mineral<5 && pModel->p1.inventory.have_pickaxe){
				pModel->map2[pModel->x][pModel->y-1].name="💨";
				pModel->map2[pModel->x][pModel->y-1].go_through=1;
				pModel->map2[pModel->x][pModel->y-1].brk=0;
				pModel->p1.inventory.ore_mineral++;
				pModel->score+=30;
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
	char buffer[4];
	char buffer2[4];
	char buffer3[4];
	char buffer4[4];
	char buffer5[4];
	char buffer6[4];
	char buffer7[4];
	char buffer8[5];
	sprintf(buffer,"%d",pModel->x);
	sprintf(buffer2,"%d",pModel->y);
	sprintf(buffer3,"%d",pModel->p1.inventory.flower_num);
	sprintf(buffer4,"%d",pModel->p1.inventory.have_pickaxe);
	sprintf(buffer5,"%d",pModel->p1.inventory.have_sword);
	sprintf(buffer6,"%d",pModel->p1.inventory.ore_mineral);
	sprintf(buffer7,"%d",pModel->p1.inventory.fish_num);
	sprintf(buffer8,"%d",pModel->score);
	if(pModel->game_status!=5){
		draw_menu(pScreen, pModel, id, pModel->game_status);
	}
	else if(pModel->p1.quest_advancement==3){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you completed all quests !",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
	}
	else if( pModel->score>=10000){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you reached the limit of the score !",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
	}
	else if(pModel->p1.health_point==0){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"You died (noobz)",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
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
		for(int i=0; i<pModel->p1.health_point*3;i=i+3){
			drawText(pScreen, 0+i,44 ,"❤️",0);
		}
		if(pModel->map2[pModel->x][pModel->y].id==5){
			if(pModel->p1.quest_advancement==0){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me 20 flowers and i'll give you a pickaxe", 0);
			}
			if(pModel->p1.quest_advancement==1){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me 10 minerals and i'll give you the power of going in the water", 0);
			}
			if(pModel->p1.quest_advancement==2){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me 9 fishes and you'll be blessed by the forest", 0);
			}	
		}
		if(pModel->map2[pModel->x][pModel->y].id==9){
			if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<5){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me 20 minerals and i'll forge you the best sword ever made", 0);
			}
			else{
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE + 10, "thank you little rabbit here's your sword", 0);
			}
		}	
		drawText(pScreen,0,48,"x=",0);
		drawText(pScreen,0,49,"y=",0);
		drawText(pScreen,2,48,buffer,0);
		drawText(pScreen,2,49,buffer2,0);
		drawText(pScreen,0,0,"Your score=",0);
		drawText(pScreen,18,0,buffer8,0);
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
			drawText(pScreen, (pScreen->width-CAMERA_SIZE)/2 + CAMERA_SIZE*2+9,i+(pScreen->height-CAMERA_SIZE)/2,"|", 0);
		}
		for(int i=0; i<=20; i+=4){
			drawLine(pScreen, (pScreen->width-CAMERA_SIZE)/2+CAMERA_SIZE+1,(pScreen->height-CAMERA_SIZE)/2+i,9,'-',0);
		}
		//drawLine(pScreen, (pScreen->width-CAMERA_SIZE)/2+CAMERA_SIZE*2+1,(pScreen->height-CAMERA_SIZE)/2+CAMERA_SIZE-1,9,'-',0); 
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
	
	
	
	gameLoop(createGame(130, 50, &model, &cb, 0));
	  
	return 0; 
}
