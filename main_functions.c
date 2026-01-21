#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "library_functions.h"

Player globalPlayer;

const char* armor_prefixes[] = { "Rusty", "Old", "Simple", "Sturdy", "Fine", "Ancient", "Mystic", "Enchanted" };
const char* armor_materials[] = { "Leather", "Chain", "Iron", "Steel", "Bronze", "Copper", "Silver", "Bone", "Wooden", "Cloth" };
const char* chest_types[] = { "Vest", "Chestplate", "Armor", "Cuirass", "Breastplate", "Chainmail" };
const char* leg_types[] = { "Pants", "Leggings", "Greaves", "Leg Guards", "Legplates", "Sabatons" };

void clearConsole() {
    system("cls");
}

int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

const char* getRandomString(const char* array[], int size) {
    return array[rand() % size];
}

ArmorPiece* generateRandomArmor(int part_type, int min_hp, int max_hp, int min_def, 
                                int max_def, int min_durab, int max_durab) {
    ArmorPiece* armor = (ArmorPiece*)malloc(sizeof(ArmorPiece));
    if (!armor) return NULL;

    // тута рандомится название бронек
    char name[50];
    if (part_type == 0) {
        sprintf(name, "%s %s %s",
            getRandomString(armor_prefixes, 8),
            getRandomString(armor_materials, 10),
            getRandomString(chest_types, 6));
    }
    else {
        sprintf(name, "%s %s %s",
            getRandomString(armor_prefixes, 8),
            getRandomString(armor_materials, 10),
            getRandomString(leg_types, 6));
    }
    strcpy(armor->name, name);

    armor->hp_boost = getRandomInt(min_hp, max_hp);
    armor->defense = getRandomInt(min_def, max_def);
    armor->durability = getRandomInt(min_durab, max_durab);

    armor->price = (armor->hp_boost * 10 + armor->defense * 20) * (armor->durability) / 100;


    return armor;
}

void recalculateStats(Player* player) {
    int armor_def = 0;
    int hp_boost = 0;

    if (player->armor.chest) {
        armor_def += player->armor.chest->defense;
        hp_boost += player->armor.chest->hp_boost;
    }
    if (player->armor.legs) {
        armor_def += player->armor.legs->defense;
        hp_boost += player->armor.legs->hp_boost;
    }

    player->total_defense = player->base_defense + armor_def;
    player->current_hp = player->base_hp + (player->base_hp * hp_boost / 100) - player->lost_hp;

    if (player->current_hp <= 0) {
        printf(" YOU DIE!\n");
        printf(" This is the bad end of my little game for now\n");
        printf(" to complete the game, enter something\n");

        int campChoice;
        scanf("%d", &campChoice);

        while (getchar() != '\n');

        cleanup();
        exit(0);
    }
}

void initPlayer(Player* player) {
    player->base_hp = 100;
    player->current_hp = 100;
    player->lost_hp = 0;
    player->base_defense = 5;
    player->total_defense = 5;
    player->cash = 50;

    player->armor.chest = NULL;
    player->armor.legs = NULL;

    // Старт эквип

    player->armor.chest = (ArmorPiece*)malloc(sizeof(ArmorPiece));

    strcpy(player->armor.chest->name, "Old Chain Vest");
    player->armor.chest->durability = 30;
    player->armor.chest->defense = 3;
    player->armor.chest->hp_boost = 5;
    player->armor.chest->price = (player->armor.chest->hp_boost * 10 + player->armor.chest->defense * 20)
        * player->armor.chest->durability / 100;

    recalculateStats(player);
}

void showPlayerStats(Player* player) {
    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" PLAYER STATISTICS:\n");
    printf(" HP: %d/%d", player->current_hp, player->current_hp + player->lost_hp);
    printf("    DEF: %d", player->total_defense);
    printf("    CASH: %d gold\n", player->cash);
    printf(" ARMOR:\n");
    if (player->armor.chest != NULL) {
        printf(" CHEST: Name: '%s';  HP: %d%%;  ", player->armor.chest->name, player->armor.chest->hp_boost);
        printf("Def: %d;  Durability: %d\n", player->armor.chest->defense, player->armor.chest->durability);
    }
    else {
        printf(" CHEST: NONE\n");
    }
    if (player->armor.legs != NULL) {
        printf(" LEGS: Name: '%s';  HP: %d%%;  ", player->armor.legs->name, player->armor.legs->hp_boost);
        printf("Def: %d;  Durability: %d\n", player->armor.legs->defense, player->armor.legs->durability);
    }
    else {
        printf(" LEGS: NONE\n");
    }
}

void freeArmorPiece(ArmorPiece** armor) {
    if (*armor) {
        free(*armor);
        *armor = NULL;
    }
}

void cleanup() {
    free(globalPlayer.armor.chest);
    free(globalPlayer.armor.legs);
}

void armorDamage(Player* player, int value) {
    if (player->armor.chest != NULL) {
        player->armor.chest->durability -= value;

        if (player->armor.chest->durability <= 0) {
            printf(" Your chest armor broke!\n");
            freeArmorPiece(&player->armor.chest);
        }
    }

    if (player->armor.legs != NULL) {
        player->armor.legs->durability -= value;

        if (player->armor.legs->durability <= 0) {
            printf(" Your leg armor broke!\n");
            freeArmorPiece(&player->armor.legs);
        }
    }
}
