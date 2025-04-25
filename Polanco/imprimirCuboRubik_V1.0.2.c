#include <stdio.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
void habilitarANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

#define CUADRADO "\u25A0"
#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define ORANGE "\x1B[38;5;208m"
#define WHITE "\x1B[37m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

char* color(int, int, int);
void imprimirCuboRubik2D();
void imprimirCaraCuboRubik(char);
int verificarCaraCuboRubik(char*);

char cuboRubik[6][3][3] = {
    {{'G','G','G'},{'G','G','G'},{'G','G','G'}},
    {{'R','R','R'},{'R','R','R'},{'R','R','R'}},
    {{'B','B','B'},{'B','B','B'},{'B','B','B'}},
    {{'O','O','O'},{'O','O','O'},{'O','O','O'}},
    {{'W','W','W'},{'W','W','W'},{'W','W','W'}},
    {{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}},
};

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    habilitarANSI();
    #endif
    imprimirCuboRubik2D();

    char caraCuboRubik;
    printf ("\nSeleccione una cara para ver: ");
    scanf("%c", &caraCuboRubik);
    if (verificarCaraCuboRubik(&caraCuboRubik)) imprimirCaraCuboRubik(caraCuboRubik);
    else return 0;
    
    return 0;
}

char* color(int cara, int i, int j){
    switch (cuboRubik[cara][i][j]) {
        case 'R': return RED;
        case 'B': return BLUE;
        case 'O': return ORANGE;
        case 'G': return GREEN;
        case 'W': return WHITE;
        case 'Y': return YELLOW;
        default:  return RESET;
    }
    //return RESET;
}

void imprimirCuboRubik2D(){
    //Imprime la cara superior
    for (int i = 0; i < 3; i++){
        printf("      ");
        for (int j = 0; j < 3; j++){
            printf("%s " CUADRADO RESET, color(4, i, j));
        }
        printf("\n");
    }

    //Imprime la cara frontal, trasera, derecha e izquierda
    for (int i = 0; i < 3; i++){
        for (int cara = 0; cara < 4; cara++){
            for (int j = 0; j < 3; j++){
                printf("%s " CUADRADO RESET, color(cara, i, j));
            }
        }
        printf("\n");
    }

    //Imprime la cara inferior
    for (int i = 0; i < 3; i++){
        printf("      ");
        for (int j = 0; j < 3; j++){
            printf("%s " CUADRADO RESET, color(5, i, j));
        }
        printf("\n");
    }
    return;
}

void imprimirCaraCuboRubik(char cara){
    int colorCara;
    switch (cara) {
        case 'L': puts("     Left face:"), colorCara = 0; break; //Izquierda
        case 'F': puts("    Front face:"), colorCara = 1; break; //Frontal
        case 'R': puts("    Right face:"), colorCara = 2; break; //Derecha
        case 'B': puts("     Back face:"), colorCara = 3; break; //Trasera
        case 'U': puts("      Up face:"), colorCara = 4; break; //Superior
        case 'D': puts("     Down face:"), colorCara = 5; break; //Inferior
        default: break;
    }
    //Imprime la cara que eligio el usuario
    for (int i = 0; i < 3; i++) {
        printf("      ");
        for (int j = 0; j < 3; j++) {
            printf("%s " CUADRADO RESET, color(colorCara, i, j));
        }
        printf("\n");
    }
    return;
}

int verificarCaraCuboRubik(char* cara){
    //Convierto en mayusculas
    *cara = toupper(*cara);

    if (*cara != 'B' && *cara != 'D' && *cara != 'F' && *cara != 'L' && *cara != 'R' && *cara != 'U'){
        puts("Cara invalida!!!");
        return 0;
    }
    return 1;
}