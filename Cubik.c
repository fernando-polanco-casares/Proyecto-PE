#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5


char cube[6][3][3];
const char* cara_nombres[] = {"Frente", "Atrás", "Izquierda", "Derecha", "Superior", "Inferior"};
const char colores[] = {'R', 'O', 'G', 'B', 'W', 'Y'};
int contador_movimientos = 0;

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


void rotar_cara_clockwise(int cara) {
    char temp[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            temp[i][j] = cube[cara][2-j][i];
        }
    }
    memcpy(cube[cara], temp, sizeof(temp));
}

void rotar_cara_counterclockwise(int cara) {
    char temp[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            temp[i][j] = cube[cara][j][2-i];
        }
    }
    memcpy(cube[cara], temp, sizeof(temp));
}

// Rotaciones para la cara Frontal
void rotar_frente_clockwise() {
    rotar_cara_clockwise(FRONT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][2][i];

    for(int i = 0; i < 3; i++) cube[UP][2][i] = cube[LEFT][2-i][2];
    for(int i = 0; i < 3; i++) cube[LEFT][2-i][2] = cube[DOWN][0][i];
    for(int i = 0; i < 3; i++) cube[DOWN][0][i] = cube[RIGHT][i][0];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][0] = temp[2-i];
}

void rotar_frente_counterclockwise() {
    rotar_cara_counterclockwise(FRONT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][2][i];

    for(int i = 0; i < 3; i++) cube[UP][2][i] = cube[RIGHT][i][0];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][0] = cube[DOWN][0][2-i];
    for(int i = 0; i < 3; i++) cube[DOWN][0][i] = cube[LEFT][2-i][2];
    for(int i = 0; i < 3; i++) cube[LEFT][i][2] = temp[2-i];
}

// Rotaciones para la cara Derecha
void rotar_derecha_clockwise() {
    rotar_cara_clockwise(RIGHT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][2];

    for(int i = 0; i < 3; i++) cube[UP][i][2] = cube[FRONT][i][2];
    for(int i = 0; i < 3; i++) cube[FRONT][i][2] = cube[DOWN][i][2];
    for(int i = 0; i < 3; i++) cube[DOWN][i][2] = cube[BACK][2-i][0];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][0] = temp[i];
}

void rotar_derecha_counterclockwise() {
    rotar_cara_counterclockwise(RIGHT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][2];

    for(int i = 0; i < 3; i++) cube[UP][i][2] = cube[BACK][2-i][0];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][0] = cube[DOWN][i][2];
    for(int i = 0; i < 3; i++) cube[DOWN][i][2] = cube[FRONT][i][2];
    for(int i = 0; i < 3; i++) cube[FRONT][i][2] = temp[i];
}

// Rotaciones para la cara Izquierda
void rotar_izquierda_clockwise() {
    rotar_cara_clockwise(LEFT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][0];

    for(int i = 0; i < 3; i++) cube[UP][i][0] = cube[BACK][2-i][2];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][2] = cube[DOWN][i][0];
    for(int i = 0; i < 3; i++) cube[DOWN][i][0] = cube[FRONT][i][0];
    for(int i = 0; i < 3; i++) cube[FRONT][i][0] = temp[i];
}

void rotar_izquierda_counterclockwise() {
    rotar_cara_counterclockwise(LEFT);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][i][0];

    for(int i = 0; i < 3; i++) cube[UP][i][0] = cube[FRONT][i][0];
    for(int i = 0; i < 3; i++) cube[FRONT][i][0] = cube[DOWN][i][0];
    for(int i = 0; i < 3; i++) cube[DOWN][i][0] = cube[BACK][2-i][2];
    for(int i = 0; i < 3; i++) cube[BACK][2-i][2] = temp[i];
}

// Rotaciones para la cara Superior
void rotar_superior_clockwise() {
    rotar_cara_clockwise(UP);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][0][i];

    for(int i = 0; i < 3; i++) cube[FRONT][0][i] = cube[RIGHT][0][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][0][i] = cube[BACK][0][i];
    for(int i = 0; i < 3; i++) cube[BACK][0][i] = cube[LEFT][0][i];
    for(int i = 0; i < 3; i++) cube[LEFT][0][i] = temp[i];
}

void rotar_superior_counterclockwise() {
    rotar_cara_counterclockwise(UP);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][0][i];

    for(int i = 0; i < 3; i++) cube[FRONT][0][i] = cube[LEFT][0][i];
    for(int i = 0; i < 3; i++) cube[LEFT][0][i] = cube[BACK][0][i];
    for(int i = 0; i < 3; i++) cube[BACK][0][i] = cube[RIGHT][0][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][0][i] = temp[i];
}

// Rotaciones para la cara Inferior
void rotar_inferior_clockwise() {
    rotar_cara_clockwise(DOWN);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][2][i];

    for(int i = 0; i < 3; i++) cube[FRONT][2][i] = cube[LEFT][2][i];
    for(int i = 0; i < 3; i++) cube[LEFT][2][i] = cube[BACK][2][i];
    for(int i = 0; i < 3; i++) cube[BACK][2][i] = cube[RIGHT][2][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][2][i] = temp[i];
}

void rotar_inferior_counterclockwise() {
    rotar_cara_counterclockwise(DOWN);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[FRONT][2][i];

    for(int i = 0; i < 3; i++) cube[FRONT][2][i] = cube[RIGHT][2][i];
    for(int i = 0; i < 3; i++) cube[RIGHT][2][i] = cube[BACK][2][i];
    for(int i = 0; i < 3; i++) cube[BACK][2][i] = cube[LEFT][2][i];
    for(int i = 0; i < 3; i++) cube[LEFT][2][i] = temp[i];
}

// Rotaciones para la cara Trasera
void rotar_atras_clockwise() {
    rotar_cara_clockwise(BACK);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][0][i];

    for(int i = 0; i < 3; i++) cube[UP][0][i] = cube[RIGHT][i][2];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][2] = cube[DOWN][2][2-i];
    for(int i = 0; i < 3; i++) cube[DOWN][2][2-i] = cube[LEFT][2-i][0];
    for(int i = 0; i < 3; i++) cube[LEFT][2-i][0] = temp[i];
}

void rotar_atras_counterclockwise() {
    rotar_cara_counterclockwise(BACK);

    char temp[3];
    for(int i = 0; i < 3; i++) temp[i] = cube[UP][0][i];

    for(int i = 0; i < 3; i++) cube[UP][0][i] = cube[LEFT][i][0];
    for(int i = 0; i < 3; i++) cube[LEFT][2-i][0] = cube[DOWN][2][i];
    for(int i = 0; i < 3; i++) cube[DOWN][2][i] = cube[RIGHT][2-i][2];
    for(int i = 0; i < 3; i++) cube[RIGHT][i][2] = temp[2-i];
}

void manejar_movimiento(char movimiento, int inverso) {
    switch(toupper(movimiento)) {
        case 'F': 
            if(inverso) rotar_frente_counterclockwise();
            else rotar_frente_clockwise();
            contador_movimientos++;
            break;
        case 'R':
            if(inverso) rotar_derecha_counterclockwise();
            else rotar_derecha_clockwise();
            contador_movimientos++;
            break;
        case 'L':
            if(inverso) rotar_izquierda_counterclockwise();
            else rotar_izquierda_clockwise();
            contador_movimientos++;
            break;
        case 'U':
            if(inverso) rotar_superior_counterclockwise();
            else rotar_superior_clockwise();
            contador_movimientos++;
            break;
        case 'D':
            if(inverso) rotar_inferior_counterclockwise();
            else rotar_inferior_clockwise();
            contador_movimientos++;
            break;
        case 'B':
            if(inverso) rotar_atras_counterclockwise();
            else rotar_atras_clockwise();
            contador_movimientos++;
            break;
        default: 
            printf("Movimiento no válido: %c\n", movimiento);
    }
}



void mezclar_cubo() {
    char caras[] = {'F', 'R', 'L', 'U', 'D', 'B'};

    // Mezclar cada cara entre 0 y 3 veces
    for(int i = 0; i < 6; i++) {
        int rotaciones = rand() % 4; // 0-3 rotaciones
        for(int j = 0; j < rotaciones; j++) {
            int direccion = 0;
            manejar_movimiento(caras[i], direccion);
        }
    }
}

int cubo_resuelto() {
    for(int cara = 0; cara < 6; cara++) {
        char color_referencia = cube[cara][0][0];
        
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(cube[cara][i][j] != color_referencia) {
                    return 0; // Falso - no está resuelto
                }
            }
        }
    }
    return 1; // Verdadero - cubo resuelto
}



int main() {
    inicializar_cubo();
    char entrada[10];
    srand(time(NULL));
    mezclar_cubo();
    while(1) {
        mostrar_cubo();
        
        
        printf("Comandos: [F,R,L,U,D,B][',2]| Q=Salir\n");
        printf("Ingrese movimiento: ");
        scanf("%s", entrada);
        
        if(toupper(entrada[0]) == 'Q') break;
        
        
        
        
        for(int i = 0; i < strlen(entrada);) {
            char mov = entrada[i];
            int inverso = 0;
            int doble = 0;
            
            if(i+1 < strlen(entrada)) {
                if(entrada[i+1] == '\'') {
                    inverso = 1;
                    i++;
                }
                else if(entrada[i+1] == '2') {
                    doble = 1;
                    i++;
                }
            }
            
            manejar_movimiento(mov, inverso);
            if(doble) manejar_movimiento(mov, inverso);
            
            i++;
        }
        
        // Verificar automáticamente después de cada movimiento
        if(cubo_resuelto()) {
            mostrar_cubo();
            printf("\n¡Felicidades! Has resuelto el cubo en %d movimientos!\n", contador_movimientos);
            break;
        }
    }
    
    return 0;
}

