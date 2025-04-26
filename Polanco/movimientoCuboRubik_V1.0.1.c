#include <stdio.h>
#include <ctype.h>

#define BUFFER 4

void limpiar_buffer();
void leer_movimiento_cubo(char movimientoCubo[]);
int verificar_movimiento(char movimiento[]);

int main(){
    char movimientoCubo[BUFFER];
    printf("Ingrese un movimiento: ");
    leer_movimiento_cubo(movimientoCubo);

    return 0;
}

void limpiar_buffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leer_movimiento_cubo(char movimientoCubo[]){
    do{
        fgets(movimientoCubo, BUFFER, stdin);
        limpiar_buffer();

    } while (!verificar_movimiento(movimientoCubo));

    return;
}

int verificar_movimiento(char movimiento[]){
    movimiento[0] = toupper(movimiento[0]);
    movimiento[2] = toupper(movimiento[2]);
    if (movimiento[0] == 'F' || movimiento[0] == 'C'){
        if (movimiento[1] >= '1' && movimiento[1] <= '3'){
            if (movimiento[0] == 'F' && (movimiento[2] == 'R' || movimiento[2] == 'L')){
                return 1;
            }
            if (movimiento[0] == 'C' && (movimiento[2] == 'U' || movimiento[2] == 'D')){
                return 1;
            }
            printf("Movimiento invalido. Intente de nuevo: ");
            return 0;

        } else {
            printf("Movimiento invalido. Intente de nuevo: ");
            return 0;
        }

    } else {
        printf("Movimiento invalido. Intente de nuevo: ");
        return 0;
    }
}