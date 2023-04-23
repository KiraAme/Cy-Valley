#include "inc/libGameRGR2.h"

typedef struct{
  int x;
  int y;
  int arrow_position;
} Model;


void init(void* pUserData, Screen* pScreen){
  Model* pModel = (Model*)pUserData;
  pModel->x = 15;
  pModel->y = 15;
  pModel->arrow_position = 6;
  setColorPair(1, 11, 0);
  setColorPair(2, 7, 0);
}

void event(void* pUserData, Screen* pScreen, Event* pEvt){
  Model* pModel = (Model*)pUserData;
  if(pEvt->code == KEY_ARROW_DOWN){
  	if(pModel->arrow_position < 17){
  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
  		pModel->arrow_position+=6;
  	}
  }
  if(pEvt->code == KEY_ARROW_UP){
  	if(pModel->arrow_position > 6){
  		drawText(pScreen, 2, pModel->arrow_position, " ", 0);
  		pModel->arrow_position-=6;
  	}
  }
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
	for(int k=5; k<18; k+=6){
		if(k+1 == pModel->arrow_position){
			id = 1;
		}
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
	drawText(pScreen, 16, 6, "Play", 1);
	drawText(pScreen, 14, 12, "Settings", 0);
	drawText(pScreen, 16, 18, "Quit", 0);
	drawText(pScreen, 2, pModel->arrow_position, "➡️", 0);
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
  

  
  gameLoop(createGame(50, 50, &model, &cb, 0));
  
  return 0; 
}
