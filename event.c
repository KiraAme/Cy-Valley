#include "game.h"
void event2(void* pUserData, Screen* pScreen, Event* pEvt){
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
