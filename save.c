#include "jeu.h"

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

    fclose(file);
}
