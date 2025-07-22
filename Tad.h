#include <stdio.h>
#include <string.h>

#define MAXFILA 50

struct TpElemento{
    char desc[50];
    char prioridade[30];
    int tempo;

};

struct TpFila
{
    int fim;
    TpElemento fila[MAXFILA];
};

void Inicializar(TpFila &f){
    f.fim = -1;
}

char FilaCheia(int fim){
    return fim == MAXFILA -1;
}

char FilaVazia(int fim){
    return fim == -1;
}
int ConvertePrioridade(char prioridade[30]){
    if (strcmp(prioridade, "Urgente") == 0) 
        return 1;
    else if (strcmp(prioridade, "Normal") == 0) 
        return 2;
    else 
        return 3;

}

void Inserir(TpFila &f,TpElemento elem){
    if(!FilaCheia(f.fim)){
        int i = f.fim;
        int prioridade= ConvertePrioridade(elem.prioridade); // prioridade vai receber um numero
     while(i >= 0 && prioridade < ConvertePrioridade(f.fila[i].prioridade)) { // vai buscar ate prioridade
            f.fila[i+1] = f.fila[i]; //remaneja os elemtnso p direita com menor prioridade
            i--; //decrementa p continuar;
        }
        f.fila[i+1] = elem; // vai adiciona priodidade na ordem
        f.fim++; //add mais 1 no fim pq add
    }
}

TpElemento Retirar(TpFila &f){
    TpElemento aux = f.fila[0];
    for(int i = 0; i < f.fim ; i++)
        f.fila[i] = f.fila[i+1];
    f.fim--;
    return aux;
}

TpElemento Inicio(TpFila f){
    return f.fila[0];
}

TpElemento Fim(TpFila f){
    return f.fila[f.fim];
}

void ExibirFila(TpFila &f) {
   for(int i = 0; i <= f.fim; i++){
    printf("Prioridade: %s, Tempo: %d, Desc: %s \n", f.fila[i].prioridade, f.fila[i].tempo , f.fila[i].desc);
   }
}

void LerArquivoTxt(TpFila &f){
    TpElemento elem;
    FILE *arq = fopen("Arquivo.txt","r");
    if(arq == NULL){
        printf("erro ao abrir arquivo!\n");
    }
    else{
        fscanf(arq,"%[^;];%d;%[^\n]\n",&elem.prioridade,&elem.tempo,&elem.desc);
        Inserir(f,elem);  
        while(!feof(arq)){
            fscanf(arq,"%[^;];%d;%[^\n]\n", &elem.prioridade,&elem.tempo,&elem.desc);
            Inserir(f,elem);
        }
        fclose(arq);
        getch();
    }
}

float GerarTempo(int tempoespera, int tempocontador){
    if(tempocontador > 0){
        return tempoespera / tempocontador;
    }
    else
        return 0;
}

void Simular(TpFila f, int operadores, int tempoexec){
    int tempo = 0; int opeocupado=0; int terminado=0;
    int nterminado=0; int conttarefas=0;
    int urgente=0;int normal=0;int opcional=0;
    int tempourgente=0;int temponormal=0;int tempoopcional=0;
    //define prioridade de cada
    int prioridadeconcluida[operadores];
    //define tempo de cada operador
    int tempooperador[operadores];
    for(int i = 0; i < operadores; i++){
        tempooperador[i] = 0;
        prioridadeconcluida[i] = 0;
    }
    while(tempo < tempoexec){
        printf("Tempo %d\n",tempo);
        ExibirFila(f);
            for (int i = 0; i < operadores; i++) {
                // tarefas, vai pegando
                if (tempooperador[i] == 0 && !FilaVazia(f.fim)) {
                    TpElemento elem = Retirar(f);
                    prioridadeconcluida[i] = ConvertePrioridade(elem.prioridade);
                    tempooperador[i] = elem.tempo;
                    opeocupado++;
                    conttarefas++;
                    printf("Operador %d iniciou tarefa %s (Duracao: %d)\n", i + 1, elem.desc, elem.tempo);
                    
                }

                // esta fazendo
                if (tempooperador[i] > 0) {
                    printf("Operador %d executando (%d restantes)\n", i + 1, tempooperador[i] - 1);
                    tempooperador[i]--;

                    //cabou 
                    if (tempooperador[i] == 0) {
                        printf("Operador %d concluiu a tarefa.\n", i + 1);
                        terminado++;
                        if (prioridadeconcluida[i]== 1)
                        {
                            urgente++;
                            tempourgente +=tempo;
                        }
                            
                        else if (prioridadeconcluida[i] == 2){
                            normal++;
                            temponormal += tempo;
                        }
                        else{
                            opcional++;
                            tempoopcional +=tempo;
                        }
                        opeocupado--;
                    }
                }
            }
        Sleep(1000);
        tempo++;
    }
    

    for (int i = 0; i < operadores; i++) {
        if (tempooperador[i] > 0) 
            nterminado++;
    }
    

    nterminado += f.fim +1;

    printf("Fim do tempo! Simulacao encerrada!\n\n");
    printf("Terminadas: %d\n",terminado);
    printf("Nao terminadas: %d\n",nterminado);

    printf("Concluidas por tipo:\n");
    printf("Urgente: %d\n",urgente);
    printf("Normal: %d\n",normal);
    printf("Opcionais: %d\n\n",opcional);

    printf("Tempo medio por cada tipo:\n");
    printf("Urgente: %.2f\n",GerarTempo(tempourgente,urgente));
    printf("Normal: %.2f\n",GerarTempo(temponormal,normal));
    printf("Opcionais: %.2f\n\n",GerarTempo(tempoopcional,opcional));

}


void Moldura (int CI, int LI,int CF,int LF, int frente,int fundo){
	int a = 0;
	textcolor(frente);
	textbackground(fundo);
	gotoxy(CI,LI); printf("%c",201);
	gotoxy(CF,LI); printf("%c",187);
	gotoxy(CI,LF); printf("%c",200);
	gotoxy(CF,LF); printf("%c",188);
	
	for (a = CI+1 ; a < CF; a++){
		gotoxy(a,LI); printf("%c", 205);
		gotoxy(a, LF); printf("%c",205);
	}
	
	for (a = LI+1 ; a < LF; a++){
		gotoxy(CI,a); printf("%c", 186);
		gotoxy(CF,a); printf("%c",186);
	}
	
	textcolor(7);
	textbackground(0);
	printf("\n\n\n\n");
}

void FormPrincipal(){
    system("cls");
	Moldura (1,1,120,30,11,6); //amarelo
	Moldura (2,2,119,5,15,2); //verde
	gotoxy(56,4); printf("LEANDRAOTOYS");
	Moldura (2,6,119,29,7,3); //azul
}

void LimpaTela(){
	for (int i=13;i<23;i++){
		gotoxy(34,i);
		printf("                                                       ");
	}
}

char Menu(){
    system("cls");
    FormPrincipal();
    gotoxy(10,60);
    printf("Nome RA");
}

void LinhaFinal (int &i){
	if (i == 24){
		FormPrincipal();
		i = 8;
		gotoxy(34,i);
	}
}
