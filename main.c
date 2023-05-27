//export LD_LIBRARY_PATH=lib
#include "game.h"

void init(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	//Player's inventory and health when spawned
	pModel->p1.health_point=3;
	pModel->p1.quest_advancement=0;
	pModel->p1.inventory.flower_num=0;
        pModel->p1.inventory.fish_num=0;
        pModel->p1.inventory.ore_mineral=0;
	pModel->p1.inventory.have_pickaxe=0;
	pModel->p1.inventory.have_sword=0;
	pModel->score=0;
	pModel->crate_score=0;
	
	//
	pModel->sec= 0;
        pModel->min= 0;
        pModel->elapsed=0;
        pModel->secglob= 0;
    
    //
        pModel->seed=time(NULL);
    
	//Player's coordinates when spawned	
	pModel->x = SIZEMAP/2;
	pModel->y = SIZEMAP/2;
	pModel->cam_x = pModel->x-CAMERA_SIZE/2;
	pModel->cam_y = pModel->y-CAMERA_SIZE/2;
	pModel->x_farmer = 0;
	pModel->y_farmer = 0;
	
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
	else if(pModel->end==1){
	}
	else{
		//player going down
		if(pEvt->code == KEY_S_LOWER||pEvt->code == KEY_S){
		 //movement with crate
			if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y+1].id==8 && pModel->map2[pModel->x][pModel->y+2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y+2];
	  				pModel->map2[pModel->x][pModel->y+2]=pModel->map2[pModel->x][pModel->y+1];
	  				pModel->map2[pModel->x][pModel->y+1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y++;
	  				pModel->cam_y++;
	  				pModel->score+=1;
	  		}
	  		//movement 
			else if(pModel->cam_y<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x][pModel->y+1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->y++;
	  			pModel->cam_y++;
	  		}
	  		//movement with map border and crate
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x][pModel->y+1].id==8 && pModel->map2[pModel->x][pModel->y+2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y+2];
	  				pModel->map2[pModel->x][pModel->y+2]=pModel->map2[pModel->x][pModel->y+1];
	  				pModel->map2[pModel->x][pModel->y+1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y++;
	  			        pModel->score+=1;
	  		}
	  		//movement with map border
	  		else if(pModel->y<SIZEMAP - 1 && pModel->map2[pModel->x][pModel->y+1].go_through ){
				pModel->y++;
			}
			//interaction with monster
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
			//movement with crate
			if(pModel->cam_y>0 && pModel->map2[pModel->x][pModel->y-1].id==8 && pModel->map2[pModel->x][pModel->y-2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y-2];
	  				pModel->map2[pModel->x][pModel->y-2]=pModel->map2[pModel->x][pModel->y-1];
	  				pModel->map2[pModel->x][pModel->y-1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y--;
	  				pModel->cam_y--;
	  				pModel->score+=1;
	  		}
	  		//movement
			else if(pModel->cam_y>0 && pModel->map2[pModel->x][pModel->y-1].go_through  && (pModel->y - pModel->cam_y) == CAMERA_SIZE/2 ){	
	  			pModel->y--;
	  			pModel->cam_y--;
	  		}
	  		//movement with map border and crate
	  		else if(pModel->y>0 && pModel->map2[pModel->x][pModel->y-1].id==8 && pModel->map2[pModel->x][pModel->y-2].go_through){
	  				pModel->temp2=pModel->map2[pModel->x][pModel->y-2];
	  				pModel->map2[pModel->x][pModel->y-2]=pModel->map2[pModel->x][pModel->y-1];
	  				pModel->map2[pModel->x][pModel->y-1]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->y--;
	  				pModel->score+=1;
	  		}
	  		//movement with map border
	  		else if(pModel->y>0 && pModel->map2[pModel->x][pModel->y-1].go_through ){
				pModel->y--;
			}
			
			//interaction with monster
			if(pModel->map2[pModel->x][pModel->y].id==10 && pModel->p1.health_point>0 ){
				if( pModel->p1.inventory.have_sword){
					pModel->map2[pModel->x][pModel->y].name="🌱";
					pModel->map2[pModel->x][pModel->y].take=1;
					pModel->score+=150;
				}
				else{
					//lost 1 hp
					pModel->p1.health_point--;
				}
			}
		}
		//player going right
		if(pEvt->code == KEY_D_LOWER ||pEvt->code == KEY_D ){
			//movement with crate
			if(pModel->cam_x<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  				pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  				pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x++;
	  				pModel->cam_x++;
	  				pModel->score+=1;
	  		}
	  		//movement
			else if(pModel->cam_x<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x+1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2 ){	
	  			pModel->x++;
	  			pModel->cam_x++;
	  		}
	  		//movement with map border 
	  		else if(pModel->x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].go_through ){
				pModel->x++;
			}
			//border and crate
	  		else if(pModel->x<SIZEMAP - 2){
	  		  if(pModel->x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  				pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  				pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x++;
	  				pModel->crate_score+=1;
	  		  }
	  		}
			//interaction with monster
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
			//movement with crate
			if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
	  				pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x-1][pModel->y];
	  				pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x--;
	  				pModel->cam_x--;
	  				pModel->score+=1;
	  		}
	  		//movement
			else if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2){
	  			pModel->x--;
	  			pModel->cam_x--;
	  		}
	  		//movement with map border 
	  		else if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].go_through ){
				pModel->x--;
			}
			//movement with map border and crate
	  		else if(pModel->x>1){
	  		  if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
	  				pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
	  				pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x-1][pModel->y];
	  				pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	  				pModel->temp1=pModel->temp2;
	  				pModel->x--;
	  				pModel->crate_score+=1;
	  		  }
	  		}
			//interaction with monster
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
			//take flower
			if(pModel->map2[pModel->x][pModel->y].id==1 && pModel->p1.inventory.flower_num<10 && pModel->map2[pModel->x][pModel->y].take){
				pModel->map2[pModel->x][pModel->y].name="🍂";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.flower_num++;
				pModel->score+=20;
			}
			//take fish
			if(pModel->map2[pModel->x][pModel->y].id==7 && pModel->p1.inventory.fish_num<3 && pModel->map2[pModel->x][pModel->y].take){
				pModel->map2[pModel->x][pModel->y].name="💧";
				pModel->map2[pModel->x][pModel->y].take=0;
				pModel->p1.inventory.fish_num++;
				pModel->score+=50;
			}
			//check npc
			if(pModel->map2[pModel->x][pModel->y].id==5 ){
				//quest 1
				if(pModel->p1.quest_advancement==0){
					if(pModel->map2[pModel->x][pModel->y].npc1.flower_num<FLOWERREQ){
						//give flowers to npc
						while(pModel->p1.inventory.flower_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.flower_num<FLOWERREQ){
							pModel->map2[pModel->x][pModel->y].npc1.flower_num++;
							pModel->p1.inventory.flower_num--;
						}
						//advanced in quest
						if(pModel->map2[pModel->x][pModel->y].npc1.flower_num==FLOWERREQ){
							pModel->p1.quest_advancement++;
							pModel->p1.inventory.have_pickaxe=1;
							pModel->score+=1000;
						}
					}
					
				}
				//quest 2
				if(pModel->p1.quest_advancement==1){
					if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ1){
						//give minerals to npc
						while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ1){					
							pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
							pModel->p1.inventory.ore_mineral--;
						}
						//advanced in quest and you can swim
						if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral==MINERALREQ1){
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
				//quest 3
				if(pModel->p1.quest_advancement==2){
					if(pModel->map2[pModel->x][pModel->y].npc1.fish_num<FISHREQ){
						//give fish to npc
						while(pModel->p1.inventory.fish_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.fish_num<FISHREQ){
							pModel->map2[pModel->x][pModel->y].npc1.fish_num++;
							pModel->p1.inventory.fish_num--;
						}
						//quest advanced
						if(pModel->map2[pModel->x][pModel->y].npc1.fish_num==FISHREQ){
							pModel->score+=1000;
							pModel->p1.quest_advancement++;
							
						}
					}
			      }
						
			}
			//quest forger
			if(pModel->map2[pModel->x][pModel->y].id==9){
				if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ2){
					//give minerals to npc
					while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ2){
							pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
							pModel->p1.inventory.ore_mineral--;
					}
					//give you sword
					if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral==5){
						pModel->p1.inventory.have_sword=1;
						pModel->score+=1000;
					}
				}
			
					
					
			}
		}
		if(pEvt->code ==  KEY_A_LOWER ||pEvt->code == KEY_A){
			//break rock
			if(pModel->map2[pModel->x][pModel->y-1].brk && pModel->p1.inventory.ore_mineral<5 && pModel->p1.inventory.have_pickaxe){
				pModel->map2[pModel->x][pModel->y-1].name="💨";
				pModel->map2[pModel->x][pModel->y-1].go_through=1;
				pModel->map2[pModel->x][pModel->y-1].brk=0;
				pModel->p1.inventory.ore_mineral++;
				pModel->score+=30;
			}
		}
		if(pEvt->code == KEY_M_LOWER){
			//save
			saveModel(pModel, "save.bin");
		}					
	}
	
	clear();
}

int update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
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
void draw(void* pUserData, Screen* pScreen){
	Model* pModel = (Model*)pUserData;
	int id = 2;
	//transform number of items in string to draw
	char buffer[4];
	char buffer2[4];
	char buffer3[4];
	char buffer4[4];
	char buffer5[4];
	char buffer6[4];
	char buffer7[4];
	char buffer8[5];
	char buffer9[20];
	char buffer10[20];
	char buffer11[5];
	char buffer12[5];
	char buffer13[5];
	char buffer14[5];
	sprintf(buffer,"%d",pModel->x);
	sprintf(buffer2,"%d",pModel->y);
	sprintf(buffer3,"%d",pModel->p1.inventory.flower_num);
	sprintf(buffer4,"%d",pModel->p1.inventory.have_pickaxe);
	sprintf(buffer5,"%d",pModel->p1.inventory.have_sword);
	sprintf(buffer6,"%d",pModel->p1.inventory.ore_mineral);
	sprintf(buffer7,"%d",pModel->p1.inventory.fish_num);
	sprintf(buffer8,"%d",pModel->score);
	sprintf(buffer9,"%d",pModel->sec);
	sprintf(buffer10,"%d",pModel->min);
	sprintf(buffer11,"%d",FLOWERREQ);
	sprintf(buffer12,"%d",MINERALREQ1);
	sprintf(buffer13,"%d",MINERALREQ2);
	sprintf(buffer14,"%d",FISHREQ);
        if(pModel->min==0 && pModel->sec==0){
                clear();
        }
        
	if(pModel->game_status!=5){
		//draw the menu
		draw_menu(pScreen, pModel, id, pModel->game_status);
	}
	//end quest
	else if(pModel->p1.quest_advancement==3){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you completed all quests !",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
		pModel->end=1;
	}
	//end crate
	else if( pModel->crate_score>=CRATE_SCORELIM){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you moved a crate a looooooooooooooooot of time!",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
		pModel->end=1;
	}
	//end score
	else if( pModel->score>=SCORE_LIMIT){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"GG you reached the limit of the score !",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
		pModel->end=1;
	}
	//end hp
	else if(pModel->p1.health_point==0){
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"YOU DIED (insert dark souls death sound)",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
		pModel->end=1;
	}
	//end time
	else if(pModel->min>=MIN_MAX && pModel->sec>=SEC_MAX){
	        clear();
	        drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2,"Time is ruuniiiiing ouuut",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2,(pScreen->height-CAMERA_SIZE)/2+10,"Your final score =",0);
		drawText(pScreen,(pScreen->width-CAMERA_SIZE)/2+19,(pScreen->height-CAMERA_SIZE)/2+10,buffer8,0);
		pModel->end=1;
	}
	else{
		//map drawing
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
		//health drawing
		for(int i=0; i<pModel->p1.health_point*3;i=i+3){
			drawText(pScreen,0+i,3,"❤️",0);
		}
		//text npc farmer
		if(pModel->map2[pModel->x][pModel->y].id==5){
			if(pModel->p1.quest_advancement==0){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer11, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " flowers and i'll give you a pickaxe", 0);
				}
			if(pModel->p1.quest_advancement==1){
			        drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer12, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " minerals and i'll give you the power of going in the water", 0);
			}
			if(pModel->p1.quest_advancement==2){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer14, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " fishes and you will be blessed by the forest", 0);
			}	
		}
		//test npc forger
		if(pModel->map2[pModel->x][pModel->y].id==9){
			if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<5){
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer13, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " minerals and I'll give you the best sword ever made", 0);
			}
			else{
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE + 10, "thank you little rabbit here's your sword", 0);
			}
		}
		//coordonate,score and inventory drawing
		drawText(pScreen,0,30,buffer10,0);
		drawText(pScreen,1,30,":",0);
		drawText(pScreen,3,30,buffer9,0);
		drawText(pScreen,0,1,"x=",0);
		drawText(pScreen,0,2,"y=",0);
		drawText(pScreen,2,1,buffer,0);
		drawText(pScreen,2,2,buffer2,0);
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
	
	
	
	gameLoop(createGame(100, 40, &model, &cb, 0));
	

	  
	return 0; 
}		
				
