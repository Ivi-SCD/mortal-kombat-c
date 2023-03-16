#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//inicialização do struct dos lutadores
typedef struct{
    char nome[30];
    float ataque;
    float defesa;
    float vida;
}Lutadores;


int main(void) {
    srand(time(NULL));
//atribuição do vetor de personagens
    Lutadores personagens[30];

    int vitorias = 0;
//inicialização dos atributos
    for(int i = 0; i < 30; i++){
        personagens[i].ataque = rand()%10;
        personagens[i].defesa = rand()%10;
        personagens[i].vida = 100;
    }
//teste da inicialização
    //for(int i = 0; i < 30; i++){
    //printf("%f\n %f\n %f\n", personagens[i].ataque, personagens[i].ataque, personagens[i].vida);
    //}

    return 0;
}