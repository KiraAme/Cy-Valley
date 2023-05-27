#include "inc/libGameRGR2.h"
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE  256
#define CAMERA_SIZE 21
#define SIZEMAP 200
#define FLOWERREQ 40
#define MINERALREQ1 20
#define MINERALREQ2 25
#define FISHREQ 15
#define MIN_MAX 10
#define SEC_MAX 0
#define SCORE_LIMIT 10000
#define CRATE_SCORELIM 1000

typedef struct{ //npc structure
	int is_npc;
	int flower_num;
	int ore_mineral;
	int fish_num;
}Npc;

typedef struct{ //Surface structure
  char *name;
  int brk ;
  int take ;
  int push ;
  int go_through;
  Npc npc1;
  int id;
} Surface;

typedef struct{ // Inventory structure
	int flower_num;
	int have_pickaxe;
	int have_sword;
	int ore_mineral;
	int fish_num;

} Inv;

typedef struct{ //Player strcture
	int health_point;
	Inv inventory;
	int quest_advancement;
} Player;

typedef struct{ //Game's model structure
  int x;
  int y;
  int cam_x;
  int cam_y;
  int arrow_position;
  int game_status;
  Player p1;
  long starttimestamp;
  float **map;
  int seed;
  Surface **map2;
  int score;
  Surface temp1;
  Surface temp2;
  int min;
  int sec;
  int end;
  int x_farmer;
  int y_farmer;
  int crate_score;
  int elapsed;
  int secglob;
} Model;


//Calling functions .c files
void initialize_permutation_table(int permutation[]);
void initialize_gradient_table(double gradient[TABLE_SIZE][2]);
double dot_product(double x1, double y1, double x2, double y2);
double smoothstep(double t);
double noise(double x, double y, int permutation[], double gradient[TABLE_SIZE][2]);
void replaceWithBiomes(float **tab, Surface **map);
void replaceWithBiomes2(Surface **map);
void create_map(Model *pModel);

void menu(Screen* pScreen, Event* pEvt, Model* pModel);
void draw_menu(Screen* pScreen, Model* pModel, int id, char status);

void event(void* pUserData, Screen* pScreen, Event* pEvt);
int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw(void* pUserData, Screen* pScreen);
void finish(void* pUserData);

void saveModel(Model *model, char *filename);
void loadModel(Model *model, char *filename);
