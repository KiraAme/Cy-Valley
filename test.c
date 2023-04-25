#include "inc/libGameRGR2.h"

#define MSIZE 100
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
	/*for(int k=5; k<18; k+=6){
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
	drawText(pScreen, 2, pModel->arrow_position, "➡️", 0);*/
	///
	srand(time(NULL));
	int map[MSIZE][MSIZE];  //matrix : rock (20%) = 0; grass (35%) = 1; trees (5%) = 2; dirt  (25%) = 3; flowers (10%)= 4; (i changed the proba just to test smthg)
	for(int n=0; n<MSIZE; n++){
	  for(int m=0; m<MSIZE; m++){
	  int num = rand()%100;
	    if(num<65){
	      map[n][m]=1;
	    }
	    else if(num<75){
	      map[n][m]=3;
	    }
	    else if(num<80){
	      map[n][m]=0;
	    }
	    else if(num<90){
	      map[n][m]=4;
	    }
	    else if(num<95){
	      map[n][m]=2;
	    }
	  }
	}
	for(pModel->x=0; pModel->x<MSIZE; pModel->x++){
	  for(pModel->y; pModel->y<MSIZE; pModel->y++){
	    printf("%d", map[pModel->x][pModel->y]);
	  }
	  printf("\n");
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
  

  
  gameLoop(createGame(50, 50, &model, &cb, 0));
  
  return 0; 
}
