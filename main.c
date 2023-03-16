#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Inicialização do struct dos lutadores
 *
 * */


typedef struct{
    char name[30];
    float attack;
    float defense;
    float life;
} Players;

void initializeCharacters(Players* characters);
void showCharacterList(Players* characters, int choose[3]);

int main(void) {

    srand(time(NULL));

    // Atribuição do vetor de personagens
    int chooseCharacters[3];
    Players characters[30];

    int wins = 0;

    initializeCharacters(characters);
    showCharacterList(characters,  chooseCharacters);

    return 0;
}

void initializeCharacters(Players* characters) {
    // Inicialização dos atributos
    for(int i = 0; i < 30; i++){
        characters[i].attack = rand()%10;
        characters[i].defense = rand()%10;
        characters[i].life = 100;
    }
}

void showCharacterList(Players * characters, int choose[3] ) {
    //Tabela de Personagens
    printf("|++---- Tabela de Personagens ----++|\n");
    printf("     Attack | Defense | Life\n");
    for(int i = 0; i < 30; i++){
        printf("  Personagem(%d):%.2f %.2f %.2f\n", i, characters[i].attack, characters[i].defense, characters[i].life);
    }
    printf("Escolha seus personagens: \n");
    scanf("%d %d %d", &choose[0], &choose[1], &choose[2]);
}