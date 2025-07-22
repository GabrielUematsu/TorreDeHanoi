#define MAXPILHA 30

struct TpPilhaM2{

    int PILHA[MAXPILHA], BASE[MAXPILHA], TOPO[MAXPILHA];
};

void Inicializar(TpPilhaM2 &PM, int QtdePILHAS){

    int QtdeElem = MAXPILHA / QtdePILHAS;

    for(int i = 0; i <= QtdeElem; i++){

        PM.BASE[i] = i * QtdePILHAS;
        PM.TOPO[i] = PM.BASE[i] - 1;
    }
}

char PMCheia(TpPilhaM2 PM, int NP){
    return PM.TOPO[NP - 1] == PM.BASE[NP] - 1;
}

char PMVazia(TpPilhaM2 PM, int NP){
    return PM.TOPO[NP - 1] < PM.BASE[NP - 1];
}

void PUSH(TpPilhaM2 &PM, int Elemento, int NP){
    PM.PILHA[++PM.TOPO[NP - 1]] = Elemento;
}

char POP(TpPilhaM2 &PM, int NP){
    return PM.PILHA[PM.TOPO[NP - 1]--];
}

char ElementoTopo(TpPilhaM2 &PM, int NP){
    return PM.PILHA[PM.TOPO[NP - 1]];
}

//=============== Funções da torre ===============

char ganhar(TpPilhaM2 PM){

    return PMVazia(PM, 1) && PMVazia(PM, 2) || PMVazia(PM, 1) && PMVazia(PM, 3);
        
}

void PrintaTorre(TpPilhaM2 PM,int discos){

    for(int i = discos; i > 0;i--){
        
        printf("\n");

        if(i <= PM.TOPO[0] - PM.BASE[0] + 1)
            printf("\t\t\t\t\t %d       ",POP(PM,1));
        else
            printf("\t\t\t\t\t |       ");
        if(i <= PM.TOPO[1] - PM.BASE[1] + 1)
            printf(" %d       ",POP(PM,2));
        else
            printf(" |       ");
        if (i <= PM.TOPO[2] - PM.BASE[2] + 1)
            printf(" %d       ",POP(PM,3));
        else
            printf(" |       ");
    }
    printf("\n\t\t\t\t\t---------------------");
    printf("\n");
    
}

void moverdisco(TpPilhaM2 &PM, int origem, int destino) {
    int disco = POP(PM, origem);
    PUSH(PM, disco, destino);
    printf("\n\t\t\t\t   Disco %d da torre %d para a torre %d\n", disco, origem, destino);
}

void mover(TpPilhaM2 &PM, int origem, int destino) {
    if (PMVazia(PM, origem)){
        moverdisco(PM, destino, origem);
    } else if (PMVazia(PM, destino)) {
        moverdisco(PM, origem, destino);
    } else if (ElementoTopo(PM, origem) > ElementoTopo(PM, destino)) {
        moverdisco(PM, destino, origem);
    } else {
        moverdisco(PM, origem, destino);
    }
}

void Automatico(TpPilhaM2 &PM, int discos) {
    int origem = 1, destino = 3, auxiliar = 2;

    if (discos % 2 == 0) {
        destino = 2;
        auxiliar = 3;
    }

    int totalMovimentos = pow(2,discos)-1;
    for (int i = 1; i <= totalMovimentos; i++) {
        if (i % 3 == 1) {
            mover(PM, origem, destino);
            Sleep(1000);
            PrintaTorre(PM, discos);
        } else if (i % 3 == 2) {
            mover(PM, origem, auxiliar);
            Sleep(1000);
            PrintaTorre(PM, discos);
        } else {
            mover(PM, auxiliar, destino);
            Sleep(1000);
            PrintaTorre(PM, discos);
        }
    }

    MessageBox(NULL, "Jogo Concluido!", "Acabou", MB_OK | MB_ICONINFORMATION);

}

void JogarManual(TpPilhaM2 &PM, int discos) {
    int origem, destino;
    while(!ganhar(PM)) {
        printf("\t\t\t Torre de origem [1, 2, 3] e Torre destino [1, 2, 3]: ");
        scanf("%d %d", &origem, &destino);

        if (PMVazia(PM, origem)) {
            
            printf("\t\t\t\tTorre de origem esta vazia! Escolha outra.\n");
        } else if (!PMVazia(PM, destino) && ElementoTopo(PM, origem) > ElementoTopo(PM, destino)) {

            printf("\t\t\tMovimento invalido! Disco maior não pode ser colocado sobre disco menor.\n");
        } else {

            moverdisco(PM, origem, destino);
        }

        PrintaTorre(PM, discos);
    }
    MessageBox(NULL, "Voce venceu!", "Parabens", MB_OK | MB_ICONINFORMATION);
}