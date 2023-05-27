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

    fclose(file);
}
