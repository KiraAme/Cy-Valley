#include "jeu.h"

void saveModel(Model *model, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fwrite(model, sizeof(Model), 1, file);

    fclose(file);
}

void loadModel(Model *model, char *filename) {
	clear();
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de chargement.\n");
        return;
    }

    fread(model, sizeof(Model), 1, file);
    
    create_map(model);
    if(model->p1.quest_advancement==2){
      for(int i=0;i<SIZEMAP;i++){
	  for(int j=0;j<SIZEMAP;j++){
		  if(model->map2[i][j].id==3 || model->map2[i][j].id==7){
			  model->map2[i][j].go_through=1;
										
		  }
	  }			
      }
    }
    fclose(file);
}
