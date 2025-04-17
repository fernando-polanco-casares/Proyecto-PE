#include <stdio.h>
#include <string.h>

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

char cube[6][3][3];
const char* cara_nombres[] = {"Frente", "Atrás", "Izquierda", "Derecha", "Superior", "Inferior"};
const char colores[] = {'R', 'O', 'G', 'B', 'W', 'Y'};

void inicializar_cubo() {
    for(int cara = 0; cara < 6; cara++) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cube[cara][i][j] = colores[cara];
            }
        }
    }
}

void mostrar_cara(int cara) {
    printf("%s:\n", cara_nombres[cara]);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%c ", cube[cara][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void mostrar_cubo() {
    mostrar_cara(UP);
    mostrar_cara(FRONT);
    mostrar_cara(DOWN);
    mostrar_cara(LEFT);
    mostrar_cara(RIGHT);
    mostrar_cara(BACK);
}

void rotar_cara(int cara) {
    char temp[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            temp[i][j] = cube[cara][2-j][i];
        }
    }
    memcpy(cube[cara], temp, sizeof(temp));
}

// Rotación de la cara Front(F)
void rotar_frente_clockwise() {
    rotar_cara(FRONT);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][2][i];
    
    for(int i = 0; i < 3; i++) cube[UP][2][i] = cube[LEFT][2-i][2];
    for(int i = 0; i < 3; i++) cube[LEFT][2-i][2] = cube[DOWN][0][i];
    for(int i = 0; i < 3; i++) cube[DOWN][0][i] = cube[RIGHT][i][0];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][0] = temp[2-i];
}

// Rotación de la cara Right (R)
void rotar_derecha_clockwise() {
    rotar_cara(RIGHT);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][2];
    
    for(int i = 0; i < 3; i++) cube[UP][i][2] = cube[FRONT][i][2];
    for(int i = 0; i < 3; i++) cube[FRONT][i][2] = cube[DOWN][i][2];
    for(int i = 0; i < 3; i++) cube[DOWN][i][2] = cube[BACK][2-i][0];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][0] = temp[i];
}

// Rotación de la cara Left (L)
void rotar_izquierda_clockwise() {
    rotar_cara(LEFT);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][0];
    
    for(int i = 0; i < 3; i++) cube[UP][i][0] = cube[BACK][2-i][2];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][2] = cube[DOWN][i][0];
    for(int i = 0; i < 3; i++) cube[DOWN][i][0] = cube[FRONT][i][0];
    for(int i = 0; i < 3; i++) cube[FRONT][i][0] = temp[i];
}

// Rotación de la cara Up (U)
void rotar_superior_clockwise() {
    rotar_cara(UP);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][0][i];
    
    for(int i = 0; i < 3; i++) cube[FRONT][0][i] = cube[RIGHT][0][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][0][i] = cube[BACK][0][i];
    for(int i = 0; i < 3; i++) cube[BACK][0][i] = cube[LEFT][0][i];
    for(int i = 0; i < 3; i++) cube[LEFT][0][i] = temp[i];
}

// Rotación de la cara Down (D)
void rotar_inferior_clockwise() {
    rotar_cara(DOWN);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][2][i];
    
    for(int i = 0; i < 3; i++) cube[FRONT][2][i] = cube[LEFT][2][i];
    for(int i = 0; i < 3; i++) cube[LEFT][2][i] = cube[BACK][2][i];
    for(int i = 0; i < 3; i++) cube[BACK][2][i] = cube[RIGHT][2][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][2][i] = temp[i];
}

// Rotación de la cara Back (B)
void rotar_atras_clockwise() {
    rotar_cara(BACK);
    
    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][0][i];
    
    for(int i = 0; i < 3; i++) cube[UP][0][i] = cube[RIGHT][i][2];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][2] = cube[DOWN][2][2-i];
    for(int i = 0; i < 3; i++) cube[DOWN][2][2-i] = cube[LEFT][2-i][0];
    for(int i = 0; i < 3; i++) cube[LEFT][2-i][0] = temp[i];
}

void manejar_movimiento(char movimiento) {
    switch(movimiento) {
        case 'F': rotar_frente_clockwise(); break;
        case 'R': rotar_derecha_clockwise(); break;
        case 'L': rotar_izquierda_clockwise(); break;
        case 'U': rotar_superior_clockwise(); break;
        case 'D': rotar_inferior_clockwise(); break;
        case 'B': rotar_atras_clockwise(); break;
        default: printf("Movimiento no válido\n");
    }
}

int main() {
    inicializar_cubo();
    char entrada[10];
    
    while(1) {
        mostrar_cubo();
        printf("Introduce un movimiento (F, R, L, U, D, B) o 'Q' para salir: ");
        scanf("%s", entrada);
        
        if(entrada[0] == 'Q') break;
        
        for(int i = 0; i < strlen(entrada); i++) {
            manejar_movimiento(entrada[i]);
        }
    }
    
    return 0;
}
