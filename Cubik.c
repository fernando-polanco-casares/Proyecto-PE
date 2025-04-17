#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// ... (las constantes y definiciones anteriores se mantienen igual)

void mezclar_cubo() {
    char caras[] = {'F', 'R', 'L', 'U', 'D', 'B'};
    
    // Mezclar cada cara entre 0 y 3 veces
    for(int i = 0; i < 6; i++) {
        int rotaciones = rand() % 4; // 0-3 rotaciones
        for(int j = 0; j < rotaciones; j++) {
            int direccion = rand() % 2; // 0 = clockwise, 1 = counterclockwise
            manejar_movimiento(caras[i], direccion);
        }
    }
}

// ... (las demás funciones se mantienen igual)

int main() {
    inicializar_cubo();
    char entrada[10];
    srand(time(NULL)); // Inicializar semilla para números aleatorios
    
    while(1) {
        mostrar_cubo();
        printf("Comandos: [F,R,L,U,D,B][',2] | S=Mezclar | Q=Salir\n");
        printf("Ingrese movimiento: ");
        scanf("%s", entrada);
        
        if(toupper(entrada[0]) == 'Q') break;
        
        if(toupper(entrada[0]) == 'S') {
            mezclar_cubo();
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
            
            manejar_movimiento(mov, inverso);
            if(doble) manejar_movimiento(mov, inverso);
            
            i++;
        }
    }
    
    return 0;
}