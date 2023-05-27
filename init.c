#include "game.h"

void init2(void* pUserData, Screen* pScreen){
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
