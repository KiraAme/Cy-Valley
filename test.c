#include "inc/libGameRGR2.h"

#define MSIZE 100

typedef struct{
  int x;
  int y;
  int arrow_position;
} Model;

double perlin(double x, double y){  //Algo du bruit de Perlin
  int n= (int)x + (int)y*57;
  n = (n << 13) ^ n;
  return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
  /*for(int x = 0; x<MSIZE; x++){
    for(int y=0; y<MSIZE; y++){
      printf("%-4d", (int)(noise[x][y] * 100));
    }
    printf("\n");
  }*/
}

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
	int map[MSIZE][MSIZE];  //matrix : rock (20%) = 1; grass (35%) = 0; trees (5%) = 3; dirt  (25%) = 2; flowers (10%)= 4; (i changed the proba just to test smthg); s = surfaces

	 const char* SURFACE_TYPES[] = {  //énumération pour stocker les 5 surfaces
	   "🪨",
	   "🌱",
	   "🌳",
	   "🏜️",
	   "🌷"
	 };
	 double SURFACE_PROBABILITIES[] = { //proba des 5 surfaces (j'ai changé les proba juste pour un test)
	   0.25,
	   0.25,
	   0.2,
	   0.2,
	   0.1
	 };
	//génération de la map
	 for(int x=0; x<MSIZE; x++){
	   for(int y=0; y<MSIZE; y++){
	     double noise = perlin(x / (double)MSIZE, y / (double)MSIZE); //calcul bruit de Perlin
	     int surface_type = -1;
	     double prob_sum = 0.0;
	     for(int i=0; i<sizeof(SURFACE_PROBABILITIES) / sizeof(double); i++){
	       prob_sum += SURFACE_PROBABILITIES[i];
	       if (noise < prob_sum){
	         surface_type = i;
	         break;
	       }
	     }
	     if (surface_type == -1){
	       surface_type = sizeof(SURFACE_PROBABILITIES) / sizeof(double) - 1;
	     }
	     map[x][y] = surface_type;
	   }
	 }
	//Affichage de la map
	 for (int y=0; y<MSIZE; y++){
	   for(int x=0; x<MSIZE; x++){
	     printf("%-7s", SURFACE_TYPES[map[x][y]]);
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
