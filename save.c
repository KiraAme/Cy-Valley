#include "game.h"

void saveModel(Model *model, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
	
	//save model
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
	
	//load model
    fread(model, sizeof(Model), 1, file);
    
    //recreate the map with the seed
    create_map(model);
    for(int i=0;i<SIZEMAP;i++){
	for(int j=0;j<SIZEMAP;j++){
		if(pModel->map2[i][j].id==3 || pModel->map2[i][j].id==7){
			pModel->map2[i][j].go_through=1;
										
		}
	}			
    }
    fclose(file);
}
