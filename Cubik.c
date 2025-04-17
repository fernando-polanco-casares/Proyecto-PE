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

// Colores ANSI para la terminal
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define WHITE   "\x1B[37m"
#define ORANGE  "\x1B[38;5;208m"
#define RESET   "\x1B[0m"

char cube[6][3][3];
const char* cara_nombres[] = {"FRENTE", "ATRÁS", "IZQUIERDA", "DERECHA", "SUPERIOR", "INFERIOR"};
const char colores[] = {'R', 'O', 'G', 'B', 'W', 'Y'};
int contador_movimientos = 0;

const char* color_ansi(char c) {
    switch(c) {
        case 'R': return RED;
        case 'O': return ORANGE;
        case 'G': return GREEN;
        case 'B': return BLUE;
        case 'W': return WHITE;
        case 'Y': return YELLOW;
        default: return RESET;
    }
}

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
    printf("┌───────┐\n");
    for(int i = 0; i < 3; i++) {
        printf("│ ");
        for(int j = 0; j < 3; j++) {
            printf("%s■ %s", color_ansi(cube[cara][i][j]), RESET);
        }
        printf("│\n");
    }
    printf("└───────┘\n");
}

void mostrar_cubo() {
    system("clear || cls"); // Limpiar pantalla
    
    printf("\n");
    printf("          ┌───────┐          \n");
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[UP][0][0]), color_ansi(cube[UP][0][1]), color_ansi(cube[UP][0][2]), RESET);
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[UP][1][0]), color_ansi(cube[UP][1][1]), color_ansi(cube[UP][1][2]), RESET);
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[UP][2][0]), color_ansi(cube[UP][2][1]), color_ansi(cube[UP][2][2]), RESET);
    printf("┌───────┬───────┬───────┬───────┐\n");
    
    for(int i = 0; i < 3; i++) {
        printf("│ %s■ %s■ %s■ %s│ ", color_ansi(cube[LEFT][i][0]), color_ansi(cube[LEFT][i][1]), color_ansi(cube[LEFT][i][2]), RESET);
        printf("%s■ %s■ %s■ %s│ ", color_ansi(cube[FRONT][i][0]), color_ansi(cube[FRONT][i][1]), color_ansi(cube[FRONT][i][2]), RESET);
        printf("%s■ %s■ %s■ %s│ ", color_ansi(cube[RIGHT][i][0]), color_ansi(cube[RIGHT][i][1]), color_ansi(cube[RIGHT][i][2]), RESET);
        printf("%s■ %s■ %s■ %s│\n", color_ansi(cube[BACK][i][0]), color_ansi(cube[BACK][i][1]), color_ansi(cube[BACK][i][2]), RESET);
    }
    
    printf("└───────┴───────┴───────┴───────┘\n");
    printf("          ┌───────┐          \n");
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[DOWN][0][0]), color_ansi(cube[DOWN][0][1]), color_ansi(cube[DOWN][0][2]), RESET);
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[DOWN][1][0]), color_ansi(cube[DOWN][1][1]), color_ansi(cube[DOWN][1][2]), RESET);
    printf("          │ %s■ %s■ %s■ %s│          \n", color_ansi(cube[DOWN][2][0]), color_ansi(cube[DOWN][2][1]), color_ansi(cube[DOWN][2][2]), RESET);
    printf("          └───────┘          \n");
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

// Rotaciones para la cara Front
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

// Rotaciones para la cara Rigth
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

// Rotaciones para la cara Left
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

// Rotaciones para la cara Up
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

// Rotaciones para la cara Down
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

// Rotaciones para la cara Back
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

void manejo_movimiento(char movimiento, int inverso) {
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
        int rotaciones = rand() % 4; 
        for(int j = 0; j < rotaciones; j++) {
            int direccion = 0;
            manejo_movimiento(caras[i], direccion);
        }
    }
}

int cubo_resuelto() {
    for(int cara = 0; cara < 6; cara++) {
        char color_referencia = cube[cara][0][0];
        
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(cube[cara][i][j] != color_referencia) {
                    return 0; // Falso - no resuelto
                }
            }
        }
    }
    return 1; // Verdadero - resuelto
}

void cambiar_cara_front(int nuevo_front) {
    
    if(nuevo_front == UP) {
        // Rotar hacia arriba
        char temp[3][3];
        
        
        memcpy(temp, cube[FRONT], sizeof(temp));
        memcpy(cube[FRONT], cube[UP], sizeof(cube[UP]));
        memcpy(cube[UP], cube[BACK], sizeof(cube[BACK]));
        memcpy(cube[BACK], cube[DOWN], sizeof(cube[DOWN]));
        memcpy(cube[DOWN], temp, sizeof(temp));
        
        rotar_cara_counterclockwise(LEFT);
        rotar_cara_clockwise(RIGHT);
    }
    else if(nuevo_front == DOWN) {
        // Rotar  hacia abajo
        char temp[3][3];
        
        memcpy(temp, cube[FRONT], sizeof(temp));
        memcpy(cube[FRONT], cube[DOWN], sizeof(cube[DOWN]));
        memcpy(cube[DOWN], cube[BACK], sizeof(cube[BACK]));
        memcpy(cube[BACK], cube[UP], sizeof(cube[UP]));
        memcpy(cube[UP], temp, sizeof(temp));
        
        rotar_cara_clockwise(LEFT);
        rotar_cara_counterclockwise(RIGHT);
    }
    else if(nuevo_front == LEFT) {
        // Rotar a la izquierda
        char temp[3][3];
        
        memcpy(temp, cube[FRONT], sizeof(temp));
        memcpy(cube[FRONT], cube[RIGHT], sizeof(cube[RIGHT]));
        memcpy(cube[RIGHT], cube[BACK], sizeof(cube[BACK]));
        memcpy(cube[BACK], cube[LEFT], sizeof(cube[LEFT]));
        memcpy(cube[LEFT], temp, sizeof(temp));
        
        rotar_cara_clockwise(UP);
        rotar_cara_counterclockwise(DOWN);
    }
    else if(nuevo_front == RIGHT) {
        // Rotar  a la derecha
        char temp[3][3];
        
        memcpy(temp, cube[FRONT], sizeof(temp));
        memcpy(cube[FRONT], cube[LEFT], sizeof(cube[LEFT]));
        memcpy(cube[LEFT], cube[BACK], sizeof(cube[BACK]));
        memcpy(cube[BACK], cube[RIGHT], sizeof(cube[RIGHT]));
        memcpy(cube[RIGHT], temp, sizeof(temp));
        
        rotar_cara_counterclockwise(UP);
        rotar_cara_clockwise(DOWN);
    }
    else if(nuevo_front == BACK) {
        // Rotar 180 grados
        char temp[3][3];
        
        memcpy(temp, cube[FRONT], sizeof(temp));
        memcpy(cube[FRONT], cube[BACK], sizeof(cube[BACK]));
        memcpy(cube[BACK], temp, sizeof(temp));
        
        memcpy(temp, cube[UP], sizeof(temp));
        memcpy(cube[UP], cube[DOWN], sizeof(cube[DOWN]));
        memcpy(cube[DOWN], temp, sizeof(temp));
        
        rotar_cara_clockwise(LEFT);
        rotar_cara_clockwise(RIGHT);
    }
    
}

void mostrar_menu_caras() { 
    printf("\n");
    printf("╔══════════════════════════════╗\n");
    printf("║     Elige el nuevo frente    ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║ Comandos:                    ║\n");
    printf("║                              ║\n");
    printf("║ 0 - Frente (actual)          ║\n");
    printf("║ 1 - Atrás                    ║\n");
    printf("║ 2 - Derecha                  ║\n");
    printf("║ 3 - Izquierda                ║\n");
    printf("║ 4 - Superior                 ║\n");
    printf("║ 5 - Inferior                 ║\n");
    printf("╚══════════════════════════════╝\n");
}

void mostrar_menu_principal() {
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║          CUBO DE RUBIK 3x3           ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ Comandos:                            ║\n");
    printf("║                                      ║\n");
    printf("║ [F] Frente     [R] Derecha           ║\n");
    printf("║ [L] Izquierda  [U] Superior          ║\n");
    printf("║ [D] Inferior   [B] Atrás             ║\n");
    printf("║                                      ║\n");
    printf("║ Modificadores:                       ║\n");
    printf("║   ' (ej: F') = Rotación inversa      ║\n");
    printf("║   2 (ej: F2) = Doble rotación        ║\n");
    printf("║                                      ║\n");
    printf("║ [S] Mezclar    [V] Cambiar vista     ║\n");
    printf("║ [C] Verificar  [Q] Salir             ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("\n");
}

int main() {
    inicializar_cubo();
    char entrada[10];
    srand(time(NULL));
    //mezclar_cubo();
    while(1) {
        mostrar_cubo();
        mostrar_cubo();
        printf("\nMovimientos: %d\n", contador_movimientos);
        mostrar_menu_principal();
        
        printf("Ingrese comando: ");
        scanf("%s", entrada);
        
       
        if(toupper(entrada[0]) == 'S') {
            mezclar_cubo();
            continue;
        }
        if(toupper(entrada[0]) == 'Q') break;
        
        if(toupper(entrada[0]) == 'V') {
            int opcion;
            mostrar_menu_caras();
            printf("Ingrese comando: ");
            scanf("%d", &opcion);
            
            if(opcion >= 0 && opcion <= 5 && opcion != FRONT) {
                cambiar_cara_front(opcion);
            } else {
                printf("Opción no válida\n");
            }
            continue;
        }
        
        
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
            
            manejo_movimiento(mov, inverso);
            if(doble) manejo_movimiento(mov, inverso);
            
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
