#include "jeu.h"

void init(void* pUserData, Screen* pScreen){
  Model* pModel = (Model*)pUserData;
  //Memory allocation of map and map2 2D array
  pModel->map = (float**)malloc(SIZEMAP*sizeof(float*)); 
  for (int i=0; i<SIZEMAP; i++) { 
         pModel->map[i] = (float*)malloc(SIZEMAP*sizeof(float)); 
  } 
  
  pModel->map2 = (Surface**)malloc(SIZEMAP*sizeof(Surface*)); 
  for (int i=0; i<SIZEMAP; i++) { 
         pModel->map2[i] = (Surface*)malloc(SIZEMAP*sizeof(Surface)); 
  }
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
  //
  pModel->sec= 0;
  pModel->min= 0;
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
