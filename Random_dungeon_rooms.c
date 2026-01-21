#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "library_functions.h"

Player globalPlayer;

void smalTrapRoom() {
    int damage;
    damage = getRandomInt(5, 15);
    globalPlayer.lost_hp += damage;
    recalculateStats(&globalPlayer);
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" Room with small trap:\n");
    printf(" you slipped and fell into a hole...\n");
    printf(" You're a little bruised and cut up....\n");
    printf("=================================================================\n\n");
    printf(" You took some damage when you fell into the trap");
    printf(" Taken damage: %d", damage);
}

void bigTrapRoom() {
    int damage;
    damage = getRandomInt(10, 25);
    globalPlayer.lost_hp += damage;
    recalculateStats(&globalPlayer);
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" Room with big danger trap:\n");
    printf(" A lot of shells flew in your direction...\n");
    printf(" The traps have really messed you up....\n");
    printf("=================================================================\n\n");
    printf(" You took some damage when you fell into the trap");
    printf(" Taken damage: %d", damage);
}

void emptyRoom() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" An unexplored dusty room:\n");
    printf(" you're trying to find something in the room...\n");
    printf(" But unfortunately you didn't find anything.....\n");
    printf("=================================================================\n\n");
    printf(" this expedition did not bring any results.");
}

void roomWithBarArmor() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" An unexplored dusty room:\n");
    printf(" After examining the room, you find some decent armor in it...\n");
    printf("=================================================================\n\n");
    findArmor(10, 20, 3, 5, 20, 40);
}

void roomWithGreatArmor() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" An unexplored room:\n");
    printf(" Walking through the tunnels, you suddenly enter a shining room...\n");
    printf(" In the middle of the room, there is a high-quality armor on a pedestal.\n");
    printf("=================================================================\n\n");
    findArmor(30, 40, 6, 10, 100, 100);
}

void moneyRoom() {
    int money = getRandomInt(100, 300);
    globalPlayer.cash += money;
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" An unexplored dusty room:\n");
    printf(" When you search the room, you find some coins...\n");
    printf(" by cleaning them from dust, you put the find in your pocket.....\n");
    printf("=================================================================\n\n");
    printf(" in this room, your balance has increased on '%d' gold", money);
}

void roomWithWeakMonster() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" A dangerous room with monster:\n");
    printf(" As you round the corner, you spot a goblin...\n");
    printf(" Unfortunately, the goblins are very agile, and you couldn't avoid the battle..\n");
    printf("=================================================================\n\n");

    printf("Choose a fighting style:\n");
    printf(" 1 - Precise (small damage but lesser reward)\n");
    printf(" 2 - Aggressive (combat and rewards become unpredictable)\n");
    printf("\nEnter your choice: ");

    int Choice;
    int takenDamage;
    int reward;
    int battleResult;

    scanf("%d", &Choice);
    while (getchar() != '\n');

    if (Choice == 1) {
        takenDamage = getRandomInt(3, 15);

        int actualDamage = takenDamage - globalPlayer.total_defense;
        if (actualDamage < 0) {
            actualDamage = 0;
        }

        reward = getRandomInt(30, 120);

        if (actualDamage == 0) {
            printf("\n Your armor protected you! No damage taken.\n");
        }
        else {
            printf("\n You lost %d HP!\n", actualDamage);
            globalPlayer.lost_hp += actualDamage;
        }

        armorDamage(&globalPlayer, 2);
        globalPlayer.cash += reward;
        printf(" Received reward: %d gold\n", reward);

    }

    else {
        battleResult = getRandomInt(1, 10);

        if (battleResult >= 1 && battleResult <= 5) {

            reward = getRandomInt(60, 160);
            printf("\n Perfect victory! You defeated the goblin quickly.\n");
            printf(" No damage taken, but armor worn out.\n");
            printf(" Received reward: %d gold\n", reward);

            armorDamage(&globalPlayer, 1);
            globalPlayer.cash += reward;

        }
        else if (battleResult >= 6 && battleResult <= 9) {

            takenDamage = getRandomInt(8, 18);
            reward = getRandomInt(30, 130);

            int actualDamage = takenDamage - globalPlayer.total_defense;
            if (actualDamage < 0) {
                actualDamage = 0;
            }

            if (actualDamage == 0) {
                printf("\n Your armor blocked the attack!\n");
            }
            else {
                printf("\n You lost %d HP in the fight!\n", actualDamage);
                globalPlayer.lost_hp += actualDamage;
            }

            armorDamage(&globalPlayer, 4);
            globalPlayer.cash += reward;
            printf(" Received reward: %d gold\n", reward);

        }
        else if (battleResult == 10) {

            takenDamage = getRandomInt(20, 30);
            reward = getRandomInt(30, 120);

            int actualDamage = takenDamage - globalPlayer.total_defense;
            if (actualDamage < 1) {
                actualDamage = 1;
            }

            printf("\n Critical hit! The goblin struck you hard!\n");
            printf(" You lost %d HP!\n", actualDamage);

            globalPlayer.lost_hp += actualDamage;
            armorDamage(&globalPlayer, 6);
            globalPlayer.cash += reward;

            printf(" Received minimal reward: %d gold\n", reward);
        }
    }

    recalculateStats(&globalPlayer);
}

void cursedArmorRoom() {
    int cursedDamage = getRandomInt(5, 10);
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT ROOM-----------------------------\n");
    printf("=================================================================\n");
    printf(" A room with a strange fog\n");
    printf(" You are under the influence of a strange curse\n");
    printf(" Your armor has lost %d durability.\n", cursedDamage);
    armorDamage(&globalPlayer, cursedDamage);
    printf("=================================================================\n\n");
}
