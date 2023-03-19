#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Inicialização do struct dos lutadores
 *
 */

typedef struct{
    char name[30];
    float attack;
    float defense;
    float life;
} Players;

typedef struct {
    Players players[3];
} Team;

void initializeCharacters(Players* characters);
void showCharacterList(Players* characters, int choose[3]);
void createTeams(Team * teams, Players* characters, int choose[3]);
void verifyIfExistsInArray (int arrayNumbers[30], int choose[3]);
int verifyIfNumberExistsInArray(int number, int array[30]);

int main(void) {

    srand(time(NULL));

    // Atribuição do vetor de personagens
    int chooseCharacters[3];
    Players characters[30];

    // Initializing Characters
    initializeCharacters(characters);
    showCharacterList(characters,  chooseCharacters);

    Team teamPlayer = {characters[chooseCharacters[0]], characters[chooseCharacters[1]], characters[chooseCharacters[2]]};
    Team teams[9];
    int wins = 0;

    createTeams(teams, characters, chooseCharacters);

    for(int i = 0; i < 9; i++) {
        printf("++----- Time %d -----++\n", i);
        for(int j = 0; j < 3; j++) {
            printf("Nome: %s |Ataque: %.2f |Defesa %.2f\n", teams[i].players[j].name,  teams[i].players[j].attack,  teams[i].players[j].defense);
        }
    }

    return 0;
}

void initializeCharacters(Players* characters) {

    char names[30][20] = {"Scorpion", "Sub-Zero", "Raiden", "Liu Kang", "Kitana", "Jade", "Mileena", "Sonya Blade", "Johnny Cage",
                          "Jax Briggs", "Kano", "Shang Tsung", "Goro", "Reptile", "Baraka", "Cyrax", "Sektor", "Smoke", "Noob Saibot",
                          "Kung Lao", "Shao Kahn", "Quan Chi", "Kotal Kahn", "Erron Black", "Frost", "Jacqui Briggs", "Cassie Cage",
                          "Kabal", "Nightwolf", "Sheeva"};

    // Inicialização dos atributos
    for(int i = 0; i < 30; i++){
        strcpy(characters[i].name, names[i]);
        characters[i].attack = rand()%11;
        characters[i].defense = rand()%11;
        characters[i].life = 100;
        if(characters[i].attack == 0) characters[i].attack = characters[i].attack + 1;
        if(characters[i].defense == 0) characters[i].defense = characters[i].defense + 1;
    }
}

void showCharacterList(Players * characters, int choose[3] ) {
    //Tabela de Personagens

    printf("|++---- Tabela de Personagens ----++|\n");
    printf("    Name | Attack | Defense | Life\n");
    for(int i = 0; i < 30; i++){
        printf("%d. (%s): %.2f | %.2f | %.2f\n", i,characters[i].name, characters[i].attack, characters[i].defense, characters[i].life);
    }
    printf("Escolha seus personagens: \n");
    scanf("%d %d %d", &choose[0], &choose[1], &choose[2]);
}

void createTeams(Team * teams, Players* characters, int choose[3]) {

    int arrayNumbers[30];

    for(int i = 0; i < 30; i++) {
        arrayNumbers[i] = i;
    }

    verifyIfExistsInArray(arrayNumbers, choose);

    for(int i = 0; i < 9; i++) {
        Team team;

        for (int j = 0; j < 3; j++) {

            int randomNumber = rand() % 30;
            while (!(verifyIfNumberExistsInArray(randomNumber, arrayNumbers))) {
                randomNumber = rand() % 30;
            }

            team.players[j] = characters[randomNumber];
            arrayNumbers[randomNumber] = -1;
        }

        teams[i] = team;
    }
}

void verifyIfExistsInArray (int arrayNumbers[30], int choose[3]) {

    for(int i = 0; i < 30; i ++) {
        for(int j = 0; j < 3; j++) {
            if(arrayNumbers[i] == choose[j]) {
                arrayNumbers[i] = -1;
            }
        }
    }
}

int verifyIfNumberExistsInArray(int number, int array[30]) {

    for(int i = 0; i < 30; i++ ) {
        if(number == array[i]) {
            return 1;
        }
    }
    return 0;
}