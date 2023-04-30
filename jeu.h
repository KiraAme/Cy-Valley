#include "inc/libGameRGR2.h"
#include <signal.h>
#include <unistd.h>

typedef struct{
  int x;
  int y;
  int arrow_position;
  int game_status;
} Model;

void menu(Screen* pScreen, Event* pEvt, Model* pModel);
void draw_menu(Screen* pScreen, Model* pModel, int id, char status);

void event(void* pUserData, Screen* pScreen, Event* pEvt);
int update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw(void* pUserData, Screen* pScreen);
void finish(void* pUserData);
