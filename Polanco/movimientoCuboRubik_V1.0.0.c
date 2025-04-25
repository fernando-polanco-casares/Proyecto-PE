// movimientoCuboRubik
// Codigo para leer movimientos ingresados por el usuario para girar el cubo rubik
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 3
char rotacionMovimiento;

void limpiarBuffer();
int verificar_movimiento(char movimiento[]);
int verificar_rotacion(char*, char);
int analizar_movimiento(char movimiento[]);

int main(){
    int parada = 0;
    char movimientoCubo[BUFFER];

    printf ("Ingrese un movimiento: ");
    while(parada == 0){
        fgets (movimientoCubo, BUFFER, stdin);
        limpiarBuffer();
        parada = analizar_movimiento(movimientoCubo);
        if (parada == 0) printf("Intende de nuevo: ");
    }

    return 0;
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificar_movimiento(char movimiento[]){
    movimiento[0] = toupper(movimiento[0]);
    if ((movimiento[0] == 'F' || movimiento [0] == 'C') && movimiento[1] >= '1' && movimiento[1] <= '3'){
        return 1;
    }
    return 0;
}

int verificar_rotacion(char* rotacion, char direccion){
    *rotacion = toupper(*rotacion);
    if (direccion == 'F'){
        if (*rotacion == 'R' || *rotacion == 'L'){
            return 1;
        } else return 0;
    } else if (direccion == 'C'){
        if (*rotacion == 'U' || *rotacion == 'D'){
            return 1;
        } else return 0;
    }
    return 0;
}

int analizar_movimiento(char movimiento[]){
    int stop = 0;
    if (verificar_movimiento(movimiento)){
        if (strcmp(movimiento, "F1") == 0){
            printf("Derecha o izquierda (R o L): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                limpiarBuffer();
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;

        } else if (strcmp(movimiento, "F2") == 0){
            printf("Derecha o izquierda (R o L): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                limpiarBuffer();
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;

        } else if (strcmp(movimiento, "F3") == 0){
            printf("Derecha o izquierda (R o L): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                limpiarBuffer();
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;

        } else if (strcmp(movimiento, "C1") == 0){
            printf("Arriba o abajo (U o D): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                limpiarBuffer();
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;

        } else if (strcmp(movimiento, "C2") == 0){
            printf("Arriba o abajo (U o D): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;

        } else if (strcmp(movimiento, "C3") == 0){
            printf("Arriba o abajo (U o D): ");
            while(stop == 0){
                scanf("%c", &rotacionMovimiento);
                if (verificar_rotacion(&rotacionMovimiento, movimiento[0])){
                    stop = 1;
                } else {
                    printf("Intenta de nuevo: ");
                }
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}