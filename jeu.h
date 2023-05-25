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
#define FLOWERREQ 1
#define MINERALREQ1 1
#define MINERALREQ2 15
#define FISHREQ 1
#define MIN_MAX 5
#define SEC_MAX 0

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
  long starttimestamp;
  int min;
  int sec;
  int end;
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

void init(void* pUserData, Screen* pScreen);
void event(void* pUserData, Screen* pScreen, Event* pEvt);

int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);

void draw(void* pUserData, Screen* pScreen);
void init_model(Model* pModel);
void drawText(Screen* pScreen, int x, int y, const char* text, int color);
void draw_game_map(Screen* pScreen, Model* pModel);
void draw_player_health(Screen* pScreen, Model* pModel);
void draw_quest_text(Screen* pScreen, Model* pModel, char* buffer1, char* buffer2, char* buffer3, char* buffer4);
void draw_inventory(Screen* pScreen, Model* pModel, char* buffer3, char* buffer4, char* buffer5, char* buffer6, char* buffer7);
void draw_inventory_counts(Screen* pScreen, Model* pModel, char* buffer3, char* buffer4, char* buffer5, char* buffer6, char* buffer7);
void draw_divider_lines(Screen* pScreen);
void draw_timer(Screen* pScreen, Model* pModel, char* buffer9, char* buffer10);
void draw_score(Screen* pScreen, Model* pModel, char* buffer8);
void draw_ui(Screen* pScreen, Model* pModel);

void finish(void* pUserData);
