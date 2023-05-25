//export LD_LIBRARY_PATH=lib
#include "jeu.h"



int main() {
	Model model;
	Callbacks cb;
	cb.cbInit= init;        
	cb.cbEvent= event;        
	cb.cbUpdate= update;
	cb.cbDraw= draw;
	cb.cbFinish= finish;
	
	
	
	gameLoop(createGame(130, 50, &model, &cb, 0));
	  
	return 0; 
}
