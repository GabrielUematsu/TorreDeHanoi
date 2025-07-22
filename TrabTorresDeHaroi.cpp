#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include <math.h>
#include "Tad.h"

int main(){

    int op,discos;
    TpPilhaM2 PM;

    printf("1- Jogar Manual\n");
    printf("2- Automatico\n");
    scanf("%d", &op);

    printf("Quantidade de discos (entre 3 e 10): ");
    scanf("%d", &discos);

    Inicializar(PM, discos);

    for (int i = discos; i > 0; i--) {
        PUSH(PM, i, 1);
    }

    PrintaTorre(PM, discos);

    if (op == 1) {
        JogarManual(PM, discos);
    } else if (op == 2) {
        Automatico(PM, discos);
    }

    getche();
    return 0;
}
