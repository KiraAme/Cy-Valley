#include "inc/libGameRGR2.h"
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int x;
  int y;
  int arrow_position;
  int game_status;
  float map[100][100];
  int seed;
  char *map2[100][100];
} Model;


void initialize_permutation_table();
void initialize_gradient_table();
double dot_product(double x1, double y1, double x2, double y2);
double smoothstep(double t);
double noise(double x, double y);
void replaceWithBiomes(float tab[100][100], char *map[100][100]);
void replaceWithBiomes2(char *map[100][100]);

void menu(Screen* pScreen, Event* pEvt, Model* pModel);
void draw_menu(Screen* pScreen, Model* pModel, int id, char status);

void event(void* pUserData, Screen* pScreen, Event* pEvt);
int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw(void* pUserData, Screen* pScreen);
void finish(void* pUserData);
