#include "inc/libGameRGR2.h"
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#define TABLE_SIZE  256
#define CAMERA_SIZE 31
#define SIZEMAP 100


typedef struct{
	int is_npc;
	int flower_num;
	int ore_mineral;
	int fish_num;
}Npc;

typedef struct{
  char *name;
  int brk ;
  int take ;
  int push ;
  int go_through;
  Npc npc1;
  int id;
} Surface;

typedef struct{
	int flower_num;
	int have_pickaxe;
	int have_sword;
	int ore_mineral;
	int fish_num;

} Inv;

typedef struct{
	int health_point;
	Inv inventory;
	int quest_advancement;
} Player;
typedef struct{
  int x;
  int y;
  int cam_x;
  int cam_y;
  int arrow_position;
  int game_status;
  Player p1;
  float map[SIZEMAP][SIZEMAP];
  int seed;
  Surface map2[SIZEMAP][SIZEMAP];
  int score;
  Surface temp1;
  Surface temp2;
} Model;












void initialize_permutation_table(int permutation[]);
void initialize_gradient_table(double gradient[TABLE_SIZE][2]);
double dot_product(double x1, double y1, double x2, double y2);
double smoothstep(double t);
double noise(double x, double y, int permutation[], double gradient[TABLE_SIZE][2]);
void replaceWithBiomes(float tab[SIZEMAP][SIZEMAP], Surface map[SIZEMAP][SIZEMAP]);
void replaceWithBiomes2(Surface map[SIZEMAP][SIZEMAP]);

void menu(Screen* pScreen, Event* pEvt, Model* pModel);
void draw_menu(Screen* pScreen, Model* pModel, int id, char status);

void event(void* pUserData, Screen* pScreen, Event* pEvt);
int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw(void* pUserData, Screen* pScreen);
void finish(void* pUserData);
