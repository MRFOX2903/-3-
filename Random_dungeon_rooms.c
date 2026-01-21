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
    printf(" In the middle of the room, there is a high-quality armor on a pedestal.");
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