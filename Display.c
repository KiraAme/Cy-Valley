#include "jeu.h"


void draw(void* pUserData, Screen* pScreen){
    Model* pModel = (Model*)pUserData;
    int id = 2;
    char buffer[4];
    char buffer2[4];
    char buffer3[4];
    char buffer4[4];
    char buffer5[4];
    char buffer6[4];
    char buffer7[4];
    char buffer8[5];
    char buffer9[20];
    char buffer10[20];
    char buffer11[5];
    char buffer12[5];
    char buffer13[5];
    char buffer14[5];
    long display_timestamp = time(NULL);
    int elapsed = display_timestamp - pModel->starttimestamp;
    pModel->sec = elapsed % 60;
    pModel->min = elapsed / 60;

    if (pModel->min == 0 && pModel->sec == 0) {
        clear();
    }

    if (pModel->game_status != 5) {
        draw_menu(pScreen, pModel, id, pModel->game_status);
    } else if (pModel->p1.quest_advancement == 3) {
        draw_completed_quests(pScreen, pModel, buffer8);
        pModel->end = 1;
    } else if (pModel->score >= 10000) {
        draw_max_score_reached(pScreen, pModel, buffer8);
        pModel->end = 1;
    } else if (pModel->p1.health_point == 0) {
        draw_player_died(pScreen, pModel, buffer8);
        pModel->end = 1;
    } else if (pModel->min >= MIN_MAX && pModel->sec >= SEC_MAX) {
        draw_time_running_out(pScreen, pModel, buffer8);
        pModel->end = 1;
    } else {
        draw_game_map(pScreen, pModel);
        draw_player_health(pScreen, pModel);
        draw_quest_text(pScreen, pModel, buffer11, buffer12, buffer14, buffer13);
        draw_timer(pScreen, pModel, buffer9, buffer10);
        draw_player_position(pScreen, pModel, buffer, buffer2);
        draw_score(pScreen, pModel, buffer8);
        draw_inventory_icons(pScreen, pModel);
        draw_inventory_counts(pScreen, pModel, buffer3, buffer4, buffer5, buffer6, buffer7);
        draw_divider_lines(pScreen);
    }
}

void draw_completed_quests(Screen* pScreen, Model* pModel, char* buffer8) {
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2, "GG you completed all quests !", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2 + 10, "Your final score =", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 19, (pScreen->height - CAMERA_SIZE) / 2 + 10, buffer8, 0);
}

void draw_max_score_reached(Screen* pScreen, Model* pModel, char* buffer8) {
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2, "GG you reached the limit of the score !", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2 + 10, "Your final score =", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 19, (pScreen->height - CAMERA_SIZE) / 2 + 10, buffer8, 0);
}

void draw_player_died(Screen* pScreen, Model* pModel, char* buffer8) {
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2, "YOU DIED (insert dark souls death sound)", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2 + 10, "Your final score =", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 19, (pScreen->height - CAMERA_SIZE) / 2 + 10, buffer8, 0);
}

void draw_time_running_out(Screen* pScreen, Model* pModel, char* buffer8) {
    clear();
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2, "Time is ruuniiiiing ouuut", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2 + 10, "Your final score =", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 19, (pScreen->height - CAMERA_SIZE) / 2 + 10, buffer8, 0);
}
// Dessiner la carte de jeu
void draw_game_map(Screen* pScreen, Model* pModel) {
    for (int i = 0; i < CAMERA_SIZE; i++) {
        for (int j = 0; j < CAMERA_SIZE; j++) {
            int dif_x = pModel->x - pModel->cam_x - CAMERA_SIZE / 2;
            int dif_y = pModel->y - pModel->cam_y - CAMERA_SIZE / 2;
            int i2 = i + (pScreen->width - CAMERA_SIZE) / 2;
            int j2 = j + (pScreen->height - CAMERA_SIZE) / 2;
            if (i == CAMERA_SIZE / 2 + dif_x && j == CAMERA_SIZE / 2 + dif_y) {
                drawText(pScreen, i2, j2, "🐰", 0);
            } else {
                drawText(pScreen, i2, j2, pModel->map2[i + pModel->cam_x][j + pModel->cam_y].name, 0);
            }
        }
    }
}
// Dessiner points de vie du joueur
void draw_player_health(Screen* pScreen, Model* pModel) {
    for (int i = 0; i < pModel->p1.health_point * 3; i = i + 3) {
        drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + i, 44, "❤️", 0);
    }
}
// Dessiner les textes de quête
void draw_quest_text(Screen* pScreen, Model* pModel, char* buffer11, char* buffer12, char* buffer14, char* buffer13) {
    if (pModel->map2[pModel->x][pModel->y].id == 5) {
        if (pModel->p1.quest_advancement == 0) {
            drawText(pScreen, CAMERA_SIZE, CAMERA_SIZE + 10, "bring me ", 0);
            drawText(pScreen, CAMERA_SIZE + 9, CAMERA_SIZE + 10, buffer11, 0);
            drawText(pScreen, CAMERA_SIZE + 11, CAMERA_SIZE + 10, " flowers and i'll give you a pickaxe", 0);
        }
        if (pModel->p1.quest_advancement == 1) {
            drawText(pScreen, CAMERA_SIZE, CAMERA_SIZE + 10, "bring me ", 0);
            drawText(pScreen, CAMERA_SIZE + 9, CAMERA_SIZE + 10, buffer12, 0);
            drawText(pScreen, CAMERA_SIZE + 11, CAMERA_SIZE + 10, " minerals and i'll give you the power of going in the water", 0);
        }
        if (pModel->p1.quest_advancement == 2) {
            drawText(pScreen, CAMERA_SIZE, CAMERA_SIZE + 10, "bring me ", 0);
            drawText(pScreen, CAMERA_SIZE + 9, CAMERA_SIZE + 10, buffer14, 0);
            drawText(pScreen, CAMERA_SIZE + 11, CAMERA_SIZE + 10, " fishes and you will be blessed by the forest", 0);
        }
    }
    if (pModel->map2[pModel->x][pModel->y].id == 9) {
        if (pModel->map2[pModel->x][pModel->y].npc1.ore_mineral < 5) {
            drawText(pScreen, CAMERA_SIZE, CAMERA_SIZE + 10, "bring me ", 0);
            drawText(pScreen, CAMERA_SIZE + 9, CAMERA_SIZE + 10, buffer13, 0);
            drawText(pScreen, CAMERA_SIZE + 11, CAMERA_SIZE + 10, " minerals and I'll give you the best sword ever made", 0);
        } else {
            drawText(pScreen, CAMERA_SIZE, CAMERA_SIZE + 10, "thank you little rabbit here's your sword", 0);
        }
    }
}
// Fonction pour dessiner l'inventaire du joueur
void draw_inventory(Screen* pScreen, Model* pModel, char* buffer3, char* buffer4, char* buffer5, char* buffer6, char* buffer7) {
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 2, 2 + (pScreen->height - CAMERA_SIZE) / 2, "🌼 ", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 2, 6 + (pScreen->height - CAMERA_SIZE) / 2, "⛏️ ", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 2, 10 + (pScreen->height - CAMERA_SIZE) / 2, "⚔️ ", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 2, 14 + (pScreen->height - CAMERA_SIZE) / 2, "💎 ", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 2, 18 + (pScreen->height - CAMERA_SIZE) / 2, "🐟 ", 0);

    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 7, 2 + (pScreen->height - CAMERA_SIZE) / 2, buffer3, 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 7, 6 + (pScreen->height - CAMERA_SIZE) / 2, buffer4, 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 7, 10 + (pScreen->height - CAMERA_SIZE) / 2, buffer5, 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 7, 14 + (pScreen->height - CAMERA_SIZE) / 2, buffer6, 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE + 7, 18 + (pScreen->height - CAMERA_SIZE) / 2, buffer7, 0);
}
// Pour dessiner les compteurs d'inventaire du joueur
void draw_inventory_counts(Screen* pScreen, Model* pModel, char* buffer3, char* buffer4, char* buffer5, char* buffer6, char* buffer7) {
    sprintf(buffer3, "%d", pModel->p1.flower);
    sprintf(buffer4, "%d", pModel->p1.pickaxe);
    sprintf(buffer5, "%d", pModel->p1.sword);
    sprintf(buffer6, "%d", pModel->p1.ore_mineral);
    sprintf(buffer7, "%d", pModel->p1.fish);
    draw_inventory(pScreen, pModel, buffer3, buffer4, buffer5, buffer6, buffer7);
}
// Pour dessiner les lignes de séparation
void draw_divider_lines(Screen* pScreen) {
    for (int i = 0; i < CAMERA_SIZE; i++) {
        drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + CAMERA_SIZE, (pScreen->height - CAMERA_SIZE) / 2 + i, "|", 0);
    }
    for (int i = 0; i < CAMERA_SIZE + 1; i++) {
        drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + i, (pScreen->height - CAMERA_SIZE) / 2 + CAMERA_SIZE, "-", 0);
    }
}
// Dessiner le chronomètre
void draw_timer(Screen* pScreen, Model* pModel, char* buffer9, char* buffer10) {
    sprintf(buffer9, "%02d", pModel->min);
    sprintf(buffer10, "%02d", pModel->sec);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2, (pScreen->height - CAMERA_SIZE) / 2 - 2, "TIME:", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 5, (pScreen->height - CAMERA_SIZE) / 2 - 2, buffer9, 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 8, (pScreen->height - CAMERA_SIZE) / 2 - 2, ":", 0);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 9, (pScreen->height - CAMERA_SIZE) / 2 - 2, buffer10, 0);
}
// Pour dessiner le score du joueur
void draw_score(Screen* pScreen, Model* pModel, char* buffer8) {
    sprintf(buffer8, "%d", pModel->score);
    drawText(pScreen, (pScreen->width - CAMERA_SIZE) / 2 + 19, (pScreen->height - CAMERA_SIZE) / 2 + 10, buffer8, 0);
}
// Pour dessiner l'interface utilisateur complète
void draw_ui(Screen* pScreen, Model* pModel) {
    char buffer8[20];
    char buffer9[3];
    char buffer10[3];
    char buffer11[3];
    char buffer12[3];
    char buffer13[3];
    char buffer14[3];
    draw_game_map(pScreen, pModel);
    draw_player_health(pScreen, pModel);
    draw_quest_text(pScreen, pModel, buffer11, buffer12, buffer14, buffer13);
    draw_inventory_counts(pScreen, pModel, buffer3, buffer4, buffer5, buffer6, buffer7);
    draw_divider_lines(pScreen);
    draw_timer(pScreen, pModel, buffer9, buffer10);
    draw_score(pScreen, pModel, buffer8);
}