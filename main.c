#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/*
 * Inicialização do struct dos lutadores
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
int starterTeam();
int defineNextPlayer();
void doAttack(Players * offensePlayer, Players * defensePlayer);
int calculatePrecision(Players * offensePlayer);
float calculateDamage(Players * offensePlayer, Players * defensePlayer);
void updateLife(Players * defensePlayer, float damage);
int playTheGame(Team * teamOne, Team * teamTwo, int * wins);

int main(void) {


    srand(time(NULL));

    int chooseCharacters[3];
    Players characters[30];

    initializeCharacters(characters);
    showCharacterList(characters,  chooseCharacters);

    Team teamPlayer = {characters[chooseCharacters[0]], characters[chooseCharacters[1]], characters[chooseCharacters[2]]};
    Team teams[9];


    createTeams(teams, characters, chooseCharacters);

    for(int i = 0; i < 9; i++) {
        printf("++----- Time %d -----++\n", i);
        for(int j = 0; j < 3; j++) {
            printf("Nome: %s |Ataque: %.2f |Defesa %.2f\n", teams[i].players[j].name,  teams[i].players[j].attack,  teams[i].players[j].defense);
        }
    }

    printf("\n\n\n\n");

    for(int i = 0; i < 9; i++) {
        if(teamPlayer.players[0].life <= 0 && teamPlayer.players[1].life <= 0 && teamPlayer.players[2].life <= 0) {
            printf("\nYou lose.\n");
        }
    }

    int i = 0;
    int wins = 0;
    while(playTheGame(&teamPlayer, &teams[i], &wins) == 1) {
        printf("=-=-=-=- Time %d =-=-=-=-", i);
        i++;
    }

    return 0;
}

void initializeCharacters(Players* characters) {

    const char* names[] = {"Scorpion", "Sub-Zero", "Raiden", "Liu Kang", "Kitana", "Jade", "Mileena", "Sonya Blade", "Johnny Cage",
                           "Jax Briggs", "Kano", "Shang Tsung", "Goro", "Reptile", "Baraka", "Cyrax", "Sektor", "Smoke", "Noob Saibot",
                           "Kung Lao", "Shao Kahn", "Quan Chi", "Kotal Kahn", "Erron Black", "Frost", "Jacqui Briggs", "Cassie Cage",
                           "Kabal", "Nightwolf", "Sheeva"};

    // Inicialização dos atributos
    for(int i = 0; i < 30; i++){
        strcpy(characters[i].name, names[i]);
        characters[i].attack = (rand()%10) + 1;
        characters[i].defense = (rand()%10) + 1;
        characters[i].life = 100;
        if(characters[i].attack == 0) characters[i].attack++;
        if(characters[i].defense == 0) characters[i].defense++;
    }
}

void showCharacterList(Players* characters, int choose[3]) {

    printf("|++---- Tabela de Personagens ----++|\n");
    printf("    Name | Attack | Defense | Life\n");
    for(int i = 0; i < 30; i++) {
        printf("%d. (%s): %.2f | %.2f | %.2f\n", i, characters[i].name, characters[i].attack, characters[i].defense, characters[i].life);
    }
    printf("Escolha seus personagens: \n");
    int valid_input = 0;
    while(!valid_input) {
        if(scanf("%d %d %d", &choose[0], &choose[1], &choose[2]) != 3) {
            printf("Entrada inválida. Por favor, insira três números separados por espaço.\n");
            while(getchar() != '\n');
        } else if(choose[0] < 0 || choose[0] > 29 || choose[1] < 0 || choose[1] > 29 || choose[2] < 0 || choose[2] > 29) {
            printf("Seleção inválida. Por favor, insira um número de personagem entre 0 e 29.\n");
            while(getchar() != '\n');
        } else if(choose[0] == choose[1] || choose[0] == choose[2] || choose[1] == choose[2]) {
            printf("Seleção inválida. Por favor, selecione personagens diferentes.\n");
            while(getchar() != '\n');
        } else {
            valid_input = 1;
        }
    }
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
int starterTeam(){
    return rand()%2 + 1;
}

int defineNextPlayer(){
    return rand()%3;
}

float calculateDamage(Players * offensePlayer, Players * defensePlayer) {
    return offensePlayer->attack/defensePlayer->defense * 50;
}

int calculatePrecision(Players * offensePlayer) {

    float randomNumber = (float)(rand()%100)/100;
    float precision = 1 - (offensePlayer->attack * offensePlayer->life/100);

    if(precision > randomNumber) {
        return 0;
    }

    return 1;
}

void updateLife(Players * defensePlayer, float damage) {
    defensePlayer->life -= damage;
    printf("%s recebeu %.2f de dano\n", defensePlayer->name, damage);
}

void doAttack(Players * offensePlayer, Players * defensePlayer){

    int precision = calculatePrecision(offensePlayer);
    float damage = calculateDamage(offensePlayer, defensePlayer);

    if(!precision){
        printf("\nO ataque de %s errou!\n", offensePlayer->name);
    }
    else {
        printf("\n%s atacou %s\n", offensePlayer->name, defensePlayer->name);
        updateLife((Players *) defensePlayer, damage);
    }
}

void doDefense(Players * offensePlayer, Players* defensePlayer) {
    int precision = calculatePrecision(offensePlayer);
    float damage = calculateDamage(offensePlayer, defensePlayer);

    if(!precision){
        printf("\n%s defendeu %s\n", defensePlayer->name, offensePlayer->name);
    }
    else {
        printf("\nA defesa falhou... %s atacou %s\n", offensePlayer->name, defensePlayer->name);
        updateLife((Players *) defensePlayer, damage);
    }
}

int playTheGame(Team * teamOne, Team * teamTwo, int * wins) {

    int continues = 3;
    int choiceContinue = 0;
    int round = 1;
    Players  playerAttacker;
    Players  playerDefenser;

    while(1) {
        int starterDefinition = starterTeam();

        if (starterDefinition == 1) {

            if(teamOne->players[0].life <= 0 && teamOne->players[1].life <= 0 && teamOne->players[2].life <= 0) {
                printf("\nDeseja continuar?\n1- Sim\n2- Nao");
                scanf("%d",  &choiceContinue);
                while(choiceContinue != 1 && choiceContinue != 2) {
                    printf("Opcao invalida, digite novamente");
                    scanf("%d",  &choiceContinue);
                }

                if(choiceContinue == 1) {
                    teamOne->players[0].life = 100;
                    teamOne->players[1].life = 100;
                    teamOne->players[2].life = 100;
                    continues--;
                } else {
                    return 0;
                }
            }

            if(teamTwo->players[0].life == 0 && teamTwo->players[1].life && teamTwo->players[2].life) {
                wins++;
                return 1;
            }

            int indicePlayerAttack = defineNextPlayer();
            int indicePlayerDefense = defineNextPlayer();

            while(teamOne->players[indicePlayerAttack].life <= 0) {
                indicePlayerAttack = defineNextPlayer();
            }
            while(teamTwo->players[indicePlayerDefense].life <= 0) {
                indicePlayerDefense = defineNextPlayer();
            }

            playerAttacker = teamOne->players[indicePlayerAttack];
            playerDefenser = teamTwo->players[indicePlayerDefense];

            while(teamTwo->players[indicePlayerDefense].life > 0 && teamOne->players[indicePlayerAttack].life > 0) {
                printf("\n------------------------");
                printf("\n| Round [%d] |\n| %s vs %s  |\n", round, playerAttacker.name, playerDefenser.name);
                printf("------------------------\n");
                printf("(T) %s | Life: %.2f     %s | Life: %.2f \n", playerAttacker.name, teamOne->players[indicePlayerAttack].life, playerDefenser.name, teamTwo->players[indicePlayerDefense].life);

                int choice;

                printf("\n%s deve:\n", playerAttacker.name);
                printf("1. Atacar | 2. Defender\n> ");
                scanf("%d", &choice);
                while (choice != 1 && choice != 2) {
                    printf("Opcao invalida, tente novamente.\n> ");
                    scanf("%d", &choice);
                }

                if (choice == 1) {
                    doAttack(&teamOne->players[indicePlayerAttack], &teamTwo->players[indicePlayerDefense]);
                    if(teamTwo->players[indicePlayerDefense].life > 0) {
                        doAttack(&teamTwo->players[indicePlayerDefense], &teamOne->players[indicePlayerAttack]);
                    }
                } else {
                    doDefense(&teamTwo->players[indicePlayerDefense],&teamOne->players[indicePlayerAttack]);
                }

                round++;
                if(teamOne->players[indicePlayerAttack].life <= 0) {
                    printf("%s ganhou a luta.\n", teamTwo->players[indicePlayerDefense].name);
                    break;
                } else if(teamTwo->players[indicePlayerDefense].life <= 0) {
                    printf("%s ganhou a luta.\n", teamOne->players[indicePlayerAttack].name);
                    break;
                }

            }

            sleep(1);
        } else if (starterDefinition == 2) {

            if(teamOne->players[0].life <= 0 && teamOne->players[1].life  <= 0 && teamOne->players[2].life <= 0) {
                printf("\nDeseja continuar?\n1- Sim\n2- Nao");
                scanf("%d",  &choiceContinue);
                while(choiceContinue != 1 && choiceContinue != 2) {
                    printf("Opcao invalida, digite novamente");
                    scanf("%d",  &choiceContinue);
                }

                if(choiceContinue == 1) {
                    teamOne->players[0].life = 100;
                    teamOne->players[1].life = 100;
                    teamOne->players[2].life = 100;
                    continues--;
                } else {
                    return 0;
                }
            }

            if(teamTwo->players[0].life <= 0 && teamTwo->players[1].life <= 0 && teamTwo->players[2].life <= 0) {
                wins++;
                return 1;
            }

            int indicePlayerAttack = defineNextPlayer();
            int indicePlayerDefense = defineNextPlayer();

            while(teamTwo->players[indicePlayerAttack].life <= 0) {
                indicePlayerAttack = defineNextPlayer();
            }
            while(teamOne->players[indicePlayerDefense].life <= 0) {
                indicePlayerDefense = defineNextPlayer();
            }

            playerAttacker = teamTwo->players[indicePlayerAttack];
            playerDefenser = teamOne->players[indicePlayerDefense];
            while(teamTwo->players[indicePlayerAttack].life > 0 && teamOne->players[indicePlayerDefense].life > 0) {
                printf("\n------------------------");
                printf("\nRound [%d]\n%s vs %s\n", round, playerDefenser.name, playerAttacker.name);
                printf("------------------------\n");
                printf("%s | Life: %.2f     %s | Life: %.2f (T)\n", playerDefenser.name, teamOne->players[indicePlayerDefense].life, playerAttacker.name, teamTwo->players[indicePlayerAttack].life);

                printf("\n(T) %s ataca.", playerAttacker.name);

                doAttack(&teamTwo->players[indicePlayerAttack], &teamOne->players[indicePlayerDefense]);

                int choice;

                if(teamOne->players[indicePlayerDefense].life <= 0) {
                    printf("%s ganhou a luta.\n", playerAttacker.name);
                    break;
                }

                printf("\n%s deve:\n", playerDefenser.name);
                printf("1. Atacar | 2. Defender\n> ");
                scanf("%d", &choice);
                while (choice != 1 && choice != 2) {
                    printf("Opcao invalida, tente novamente.\n> ");
                    scanf("%d", &choice);
                }

                if (choice == 1) {
                    doAttack(&teamOne->players[indicePlayerDefense], &teamTwo->players[indicePlayerAttack]);
                } else {
                    doDefense(&teamOne->players[indicePlayerDefense],&teamTwo->players[indicePlayerAttack]);
                }

                round++;
                if(teamOne->players[indicePlayerDefense].life <= 0) {
                    printf("%s ganhou a luta.\n", teamTwo->players[indicePlayerAttack].name);
                    break;
                } else if(teamTwo->players[indicePlayerAttack].life <= 0) {
                    printf("%s ganhou a luta.\n", teamOne->players[indicePlayerDefense].name);
                    break;
                }
            }

            sleep(1);
        }
    }
}