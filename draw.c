#include "game.h"
void draw2(void* pUserData, Screen* pScreen){
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
	char buffer11[15];
	char buffer12[15];
	char buffer13[15];
	char buffer14[15];
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
			        int flowerupd=FLOWERREQ-pModel->map2[pModel->x][pModel->y].npc1.flower_num;
			        sprintf(buffer11,"%d",flowerupd);
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer11, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " flowers and i'll give you a pickaxe", 0);
				}
			if(pModel->p1.quest_advancement==1){
			        int mineralq1upd=MINERALREQ1-pModel->map2[pModel->x][pModel->y].npc1.ore_mineral;
			        sprintf(buffer12,"%d",mineralq1upd);
			        drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer12, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " minerals and i'll give you the power of going in the water", 0);
			}
			if(pModel->p1.quest_advancement==2){
			        int fishupd=FISHREQ-pModel->map2[pModel->x][pModel->y].npc1.fish_num;
			        sprintf(buffer14,"%d",fishupd);
				drawText(pScreen, CAMERA_SIZE,CAMERA_SIZE+10, "bring me ", 0);
				drawText(pScreen, CAMERA_SIZE+9,CAMERA_SIZE+10, buffer14, 0);
				drawText(pScreen, CAMERA_SIZE+11,CAMERA_SIZE+10, " fishes and you will be blessed by the forest", 0);
			}	
		}
		//test npc forger
		if(pModel->map2[pModel->x][pModel->y].id==9){
			if(pModel->map2[pModel->x][pModel->y].npc1.ore_mineral<MINERALREQ2){
			        int mineralq2upd=MINERALREQ2-pModel->map2[pModel->x][pModel->y].npc1.ore_mineral;
			        sprintf(buffer13,"%d",mineralq2upd);
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
