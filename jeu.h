#include "inc/libGameRGR2.h"
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE  256
#define CAMERA_SIZE 21

typedef struct{
  char *name;
  int brk ;
  int take ;
  int push ;
  int go_through;
} Surface;


typedef struct{
  int x;
  int y;
  int arrow_position;
  int game_status;
  float map[100][100];
  int seed;
  Surface map2[100][100];
} Model;



typedef struct{
	int flower_num;
	int have_pickaxe;
	int item_1;

} Inv;

typedef struct{
	float health_point;
	Inv inventory;
	int quest_advancement;
} Player;





typedef struct{
	int ad;
	float health_point;
	char* weapon;
} Mob;




void initialize_permutation_table(int permutation[]);
void initialize_gradient_table(double gradient[TABLE_SIZE][2]);
double dot_product(double x1, double y1, double x2, double y2);
double smoothstep(double t);
double noise(double x, double y, int permutation[], double gradient[TABLE_SIZE][2]);
void replaceWithBiomes(float tab[100][100], Surface map[100][100]);
void replaceWithBiomes2(Surface map[100][100]);

void menu(Screen* pScreen, Event* pEvt, Model* pModel);
void draw_menu(Screen* pScreen, Model* pModel, int id, char status);

void event(void* pUserData, Screen* pScreen, Event* pEvt);
int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw(void* pUserData, Screen* pScreen);
void finish(void* pUserData);
