#include "jeu.h"

void event(void* pUserData, Screen* pScreen, Event* pEvt){
	Model* pModel = (Model*)pUserData;
	if(pModel->game_status!=5){
		menu(pScreen, pEvt, pModel);	
	}
	else if(pModel->end==1){
	}
	else{
	        handlePlayerMov(pModel, pEvt);
       }
    clear();
}

void handlePlayerMov(Model *pModel,Event* pEvt){
        if(pEvt->code == KEY_S_LOWER || pEvt->code == KEY_Z){
                handlePlayerDown(pModel);
        }
        if(pEvt->code == KEY_Z_LOWER||pEvt->code == KEY_Z){
                handlePlayerUp(pModel);
        }
        if(pEvt->code == KEY_D_LOWER ||pEvt->code == KEY_D){
                handlePlayerRight(pModel);
        }
        if(pEvt->code == KEY_Q_LOWER||pEvt->code == KEY_Q){
                handlePlayerLeft(pModel);
        }
        if(pEvt->code == KEY_E_LOWER||pEvt->code == KEY_E){
                handlePlayerInteraction(pModel);
        }
        if(pEvt->code ==  KEY_A_LOWER ||pEvt->code == KEY_A){
                handlePlayerA(pModel);
        }
}
void handlePlayerDown(Model *pModel){
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
//UP
void handlePlayerUp(Model* pModel){
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


//RIGHT
void handlePlayerRight(Model *pModel){
        if(pModel->cam_x<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	        pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  	pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  	pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  	pModel->temp1=pModel->temp2;
	  	pModel->x++;
	  	pModel->cam_x++;
	        pModel->score+=1;
        }
	else if(pModel->cam_x<(SIZEMAP - CAMERA_SIZE) && pModel->map2[pModel->x+1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2 ){	
	        pModel->x++;
	  	pModel->cam_x++;
        }
        else if(pModel->x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].id==8 && pModel->map2[pModel->x+2][pModel->y].go_through){
	        pModel->temp2=pModel->map2[pModel->x+2][pModel->y];
	  	pModel->map2[pModel->x+2][pModel->y]=pModel->map2[pModel->x+1][pModel->y];
	  	pModel->map2[pModel->x+1][pModel->y]=pModel->temp1;
	  	pModel->temp1=pModel->temp2;
	  	pModel->x++;
	  	pModel->score+=1;
	}
        else if(pModel->x<SIZEMAP - 1 && pModel->map2[pModel->x+1][pModel->y].go_through ){
	        pModel->x++;
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

void handlePlayerLeft(Model *pModel){
        if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
	      pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
              pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x-1][pModel->y];
	      pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	      pModel->temp1=pModel->temp2;
	      pModel->x--;
	      pModel->cam_x--;
	      pModel->score+=1;
        }
        else if(pModel->cam_x>0 && pModel->map2[pModel->x-1][pModel->y].go_through  && (pModel->x - pModel->cam_x) == CAMERA_SIZE/2  ){
                pModel->x--;
	  	pModel->cam_x--;
        }
	else if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].id==8 && pModel->map2[pModel->x-2][pModel->y].go_through){
                pModel->temp2=pModel->map2[pModel->x-2][pModel->y];
	  	pModel->map2[pModel->x-2][pModel->y]=pModel->map2[pModel->x-1][pModel->y];
	  	pModel->map2[pModel->x-1][pModel->y]=pModel->temp1;
	  	pModel->temp1=pModel->temp2;
	  	pModel->x--;
	  	pModel->score+=1;
        }
	else if(pModel->x>0 && pModel->map2[pModel->x-1][pModel->y].go_through ){
	        pModel->x--;
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

		
	      
void handlePlayerInteraction(Model *pModel){
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
		        if(pModel->map2[pModel->x][pModel->y].npc1.flower_num<FLOWERREQ){
			        while(pModel->p1.inventory.flower_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.flower_num<FLOWERREQ){
				        pModel->map2[pModel->x][pModel->y].npc1.flower_num++;
					pModel->p1.inventory.flower_num--;
				}
				if(pModel->map2[pModel->x][pModel->y].npc1.flower_num==FLOWERREQ){
					pModel->p1.quest_advancement++;
					pModel->p1.inventory.have_pickaxe=1;
					pModel->score+=1000;
				}
			}		
		}
		if(pModel->p1.quest_advancement==1){
		        if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ1){
			        while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ1){					
				        pModel->map2[pModel->x][pModel->y].npc1.ore_mineral++;
					pModel->p1.inventory.ore_mineral--;
				}
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
		if(pModel->p1.quest_advancement==2){
		        if(pModel->map2[pModel->x][pModel->y].npc1.fish_num<FISHREQ){
			        debug("+");
				while(pModel->p1.inventory.fish_num!=0 && pModel->map2[pModel->x][pModel->y].npc1.fish_num<FISHREQ){
			                debug("+");
					pModel->map2[pModel->x][pModel->y].npc1.fish_num++;
					pModel->p1.inventory.fish_num--;
				}
				if(pModel->map2[pModel->x][pModel->y].npc1.fish_num==FISHREQ){
				        pModel->score+=1000;
					pModel->p1.quest_advancement++;
							
				}
		        }
		}
						
	}
        if(pModel->map2[pModel->x][pModel->y].id==9){
	        if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ2){
		        while(pModel->p1.inventory.ore_mineral!=0 && pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ2){
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

void handlePlayerA(Model *pModel){
        if(pModel->map2[pModel->x][pModel->y-1].brk && pModel->p1.inventory.ore_mineral<5 && pModel->p1.inventory.have_pickaxe){
	        pModel->map2[pModel->x][pModel->y-1].name="💨";
		pModel->map2[pModel->x][pModel->y-1].go_through=1;
		pModel->map2[pModel->x][pModel->y-1].brk=0;
	        pModel->p1.inventory.ore_mineral++;
		pModel->score+=30;
	}
}
			
      //  clear();

