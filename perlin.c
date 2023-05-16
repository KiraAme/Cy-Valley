#include "jeu.h"

void initialize_permutation_table(int permutation[]){
    int i, j, tmp;

    // Fill the permutation table with values from 0 to 255
    for (i = 0; i < TABLE_SIZE; i++) {
        permutation[i] = i;
    }

    // Shuffle the permutation table using the Fisher-Yates algorithm
    for (i = TABLE_SIZE - 1; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = tmp;
    }
}

void initialize_gradient_table(double gradient[TABLE_SIZE][2]){
    int i;

    for (i = 0; i < TABLE_SIZE; i++) {
        // Generate a random vector with a length of 1
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;
        double length = sqrt(x * x + y * y);
        gradient[i][0] = x / length;
        gradient[i][1] = y / length;
    }
}

double dot_product(double x1, double y1, double x2, double y2){
    return x1 * x2 + y1 * y2;
}

double smoothstep(double t){
    return t * t * (3 - 2 * t);
}

double noise(double x, double y, int permutation[], double gradient[TABLE_SIZE][2]){
    int x0 = floor(x);
    int x1 = x0 + 1;
    int y0 = floor(y);
    int y1 = y0 + 1;

    // Determine the four corners of the square in the grid
    int i00 = permutation[(x0 + permutation[y0 % TABLE_SIZE]) % TABLE_SIZE];
    int i01 = permutation[(x0 + permutation[y1 % TABLE_SIZE]) % TABLE_SIZE];
    int i10 = permutation[(x1 + permutation[y0 % TABLE_SIZE]) % TABLE_SIZE];
    int i11 = permutation[(x1 + permutation[y1 % TABLE_SIZE]) % TABLE_SIZE];

    // Calculate the vectors from the corners to the point in the grid
    double dx0 = x - x0;
    double dy0 = y - y0;
    double dx1 = x - x1;
    double dy1 = y - y1;

    // Calculate the dot products of the vectors and the gradients
    double dot00 = dot_product(dx0, dy0, gradient[i00][0], gradient[i00][1]);
    double dot01 = dot_product(dx0, dy1, gradient[i01][0], gradient[i01][1]);
    double dot10 = dot_product(dx1, dy0, gradient[i10][0], gradient[i10][1]);
    double dot11 = dot_product(dx1, dy1, gradient[i11][0], gradient[i11][1]);

    // Interpolate the dot products using smoothstep
    double u = smoothstep(dx0);
    double v = smoothstep(dy0);
    double a = dot00 + u * (dot10 - dot00);
    double b = dot01 + u * (dot11 - dot01);
    double c = a + v * (b - a);

    // Clamp the result to the range [0

	double result = fmin(fmax(c, 0), 1);

	return result * 15; // Scale the result to the range [0, 15]
}


void replaceWithBiomes(float tab[SIZEMAP][SIZEMAP], Surface map[SIZEMAP][SIZEMAP]){
	Surface plain;
	Surface beach;
	Surface lake;
	plain.name="🌱";
	plain.brk=0;
	plain.take=1;
	plain.push=0;
	plain.go_through=1;
	beach.name="⏳";
	beach.brk=0;
	beach.take=0;
	beach.push=0;
	beach.go_through=1;
	lake.name="💧";
	lake.brk=0;
	lake.take=0;
	lake.push=0;
	lake.go_through=0;
	for(int i = 0; i < SIZEMAP; i++){
		for (int j = 0; j < SIZEMAP; j++){
			if(tab[i][j] == 0) {
				map[i][j] = plain; // Plain
			}
			else if(tab[i][j] == 1 || tab[i][j] == 2) {
				map[i][j] = beach; // Beach
			}
			else{
				map[i][j] = lake; // Lake
			}
		}
	}
}

void replaceWithBiomes2(Surface map[SIZEMAP][SIZEMAP]){
	Surface plain;
	Surface beach;
	Surface lake;
	Surface rock;
	plain.name="🌱";
	plain.brk=0;
	plain.take=1;
	plain.push=0;
	plain.go_through=1;
	beach.name="⏳";
	beach.brk=0;
	beach.take=0;
	beach.push=0;
	beach.go_through=1;
	lake.name="💧";
	lake.brk=0;
	lake.take=0;
	lake.push=0;
	lake.go_through=0;
	rock.name="🪨";
	rock.brk=1;
	rock.take=0;
	rock.push=0;
	rock.go_through=0;
	for(int i = 0; i < SIZEMAP; i++){
		for (int j = 0; j < SIZEMAP; j++){
			if((map[i][j].name == "🌱" || map[i][j].name == "⏳") && (rand() % SIZEMAP < 5)){
				map[i][j] = rock; // Plain
			}
		}
	}
}

