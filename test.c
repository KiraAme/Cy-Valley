#include "inc/libGameRGR2.h"

typedef struct{
  int x;
  int y;
} Model;




void Init (void* pUserData, Screen* pScreen){
  Model* pModel = (*Model)pUserData;
}
void Event (void* pUserData, Screen* pScreen, Event* pEvt){
  Model* pModel = (*Model)pUserData;
}
int Update (void* pUserData, Screen* pScreen, unsigned long deltaTime){
  
  return 0;
}
void Draw (void* pUserData, Screen* pScreen){
  
}
void Finish (void* pUserData){
  
}






int main() {
  Model model;
  Callbacks cb;
  cb->cbInit= Init;        
  cb->cbEvent= Event;        
  cb->cbUpdate= Update;
  cb->cbDraw= Draw;
  cb->cbFinish= Finish;
  
  
  createGame(10, 30, &model, &cb, 0);
  
  
  
  return 0; 
}
