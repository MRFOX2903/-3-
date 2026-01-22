#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "library_functions.h"

Player globalPlayer;

void waitForExit() {
    int cmd = 1;
    while (cmd != 0) {
        printf(" Enter '0' to exit this location: ");
        scanf("%d", &cmd);
        while (getchar() != '\n');
    }
    clearConsole();
}

int BranchingPointInfo() {
    int choice;
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" BRANCHING POINT:\n");
    printf(" Choose your journey:\n");
    printf(" 1 - Ancient Ruins\n");
    printf(" 2 - Random Dungeon\n");
    printf(" 3 - Camp\n");
    printf(" 4 - The path to freedom\n");
    printf(" 5 - Guide's house\n");
    printf("=================================================================\n");
    printf("\n Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    clearConsole();
    return choice;
}

void findArmor(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur) {

    int armor_type = getRandomInt(0, 1);
    const char* armor_type_name = (armor_type == 0) ? "CHEST" : "LEGS";

    ArmorPiece* found_armor = generateRandomArmor(armor_type, min_hp, max_hp, min_def, max_def, min_dur, max_dur);
    if (found_armor != NULL) {
        printf("\n=================================================================\n");
        printf(" CONGRATULATIONS! YOU FOUND ARMOR!\n");
        printf("=================================================================\n");
        printf(" Type: %s armor\n", armor_type_name);
        printf(" Name: %s\n", found_armor->name);
        printf(" Defense: +%d\n", found_armor->defense);
        printf(" Durability: %d\n", found_armor->durability);
        printf(" HP Boost: +%d%%\n", found_armor->hp_boost);
        printf(" Value: %d gold\n", found_armor->price);
        printf("=================================================================\n");

        printf("\n Your current %s armor: ", armor_type_name);

        if (armor_type == 0) {
            if (globalPlayer.armor.chest != NULL) {
                printf("%s (Def: +%d, HP: +%d%%, Durability: %d)\n",
                    globalPlayer.armor.chest->name,
                    globalPlayer.armor.chest->defense,
                    globalPlayer.armor.chest->hp_boost,
                    globalPlayer.armor.chest->durability);
            }
            else {
                printf(" NONE\n");
            }
        }

        else {
            if (globalPlayer.armor.legs != NULL) {
                printf("%s (Def: +%d, HP: +%d%%, Durability: %d)\n",
                    globalPlayer.armor.legs->name,
                    globalPlayer.armor.legs->defense,
                    globalPlayer.armor.legs->hp_boost,
                    globalPlayer.armor.legs->durability);
            }
            else {
                printf(" NONE\n");
            }
        }

        printf("\n Do you want to equip this armor?\n");
        printf(" 1 - YES, equip found armor\n");
        printf(" 0 - NO, keep current armor\n");
        printf(" Enter your choice: ");

        int armorChoice;
        scanf("%d", &armorChoice);

        while (getchar() != '\n');

        if (armorChoice == 1) {
            if (armor_type == 0) {
                freeArmorPiece(&globalPlayer.armor.chest);
                globalPlayer.armor.chest = found_armor;
            }
            else {
                freeArmorPiece(&globalPlayer.armor.legs);
                globalPlayer.armor.legs = found_armor;
            }
            recalculateStats(&globalPlayer);

            printf("\n=================================================================\n");
            printf(" ARMOR EQUIPPED!\n");
            printf(" You are now wearing: %s\n", found_armor->name);
            printf("=================================================================\n");
        }
        else {
            free(found_armor);
            found_armor = NULL;

            printf("\n=================================================================\n");
            printf(" ARMOR LEFT BEHIND\n");
            printf("=================================================================\n");
        }
    }
}

//-------(блок лагеря)

void mainCamp() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" Camp:\n");
    printf(" It's time to take a short break on your journey...\n");
    printf("=================================================================\n");

    printf("\n Camp Menu:\n");
    printf(" 1 - Visit Petrovich's Store\n");
    printf(" 2 - Badazhkov's pawnshop\n");
    printf(" 3 - The Healler bench\n");
    printf(" 0 - Just relax\n");
    printf("=================================================================\n\n");
    printf("\n Enter your choice: ");

    int campChoice;
    scanf("%d", &campChoice);

    while (getchar() != '\n');

    if (campChoice == 1) {
        shopInCamp();
    }
    if (campChoice == 2) {
        sellInCamp(&globalPlayer);
    }
    if (campChoice == 3) {
        playerHealinCamp();
    }
}

void playerHealinCamp() {
    int action = 1;

    while (action) {
        action = 0;
        clearConsole();
        showPlayerStats(&globalPlayer);

        int money_for_full_recowery = globalPlayer.lost_hp * 9;

        printf("------------------------CURRENT POSITION-------------------------\n");
        printf("=================================================================\n");
        printf(" The free priest's bench:\n");
        printf(" in this storage you can buy some armor:\n");
        printf("=================================================================\n\n");
        printf(" The priest looks at you and says the following :\n");
        printf(" -would you like to recover from your wounds?\n");
        printf(" -full recovery will only cost %d coins.\n", money_for_full_recowery);
        printf(" -Would you like to be healed?\n");
        printf("=================================================================\n\n");
        printf(" 1 - Healing:\n");
        printf(" 0 - Leave bench:\n");
        printf("\n Enter your choice: ");

        scanf("%d", &action);
        while (getchar() != '\n');

        if (action == 1 && globalPlayer.lost_hp != 0 && money_for_full_recowery <= globalPlayer.cash) {
            globalPlayer.lost_hp = 0;
            recalculateStats(&globalPlayer);
            clearConsole();
            showPlayerStats(&globalPlayer);
            printf("------------------------CURRENT ACTOIN-------------------------\n");
            printf(" you have fully recovered your hp\n");
            action = 0;
        }
        if (action == 1 && globalPlayer.lost_hp != 0 && money_for_full_recowery > globalPlayer.cash) {
            printf("------------------------CURRENT ACTOIN-------------------------\n");
            printf(" you haven't gold for this action\n");
            action = 0;
        }

        if (action == 1 && globalPlayer.lost_hp == 0) {
            globalPlayer.lost_hp = 0;
            recalculateStats(&globalPlayer);
            clearConsole();
            showPlayerStats(&globalPlayer);
            printf("------------------------CURRENT ACTOIN-------------------------\n");
            printf(" You already have full hp.\n");
            action = 0;

        }
        else {
            printf("------------------------CURRENT ACTOIN-------------------------\n");
            printf(" Please. Leave my bench.\n");
        }
    }
}

void sellInCamp(Player* player) {
    int action = 1;
    if (action == 1) {
        clearConsole();
        showPlayerStats(&globalPlayer);
        printf("------------------------CURRENT POSITION-------------------------\n");
        printf("=================================================================\n");
        printf(" Badazhkov's pawnshop:\n");
        printf(" Here you can sell your armor items.\n");
        printf("=================================================================\n\n");
        printf(" Your Armor price:\n");

        if (player->armor.chest != NULL) {
            printf(" CHEST: Name: '%s';  Price: %d\n", player->armor.chest->name, player->armor.chest->price);
        }
        else {
            printf(" CHEST: NONE\n");
        }
        if (player->armor.legs != NULL) {
            printf(" LEGS: Name: '%s';  Price: %d\n", player->armor.legs->name, player->armor.legs->price);
        }
        else {
            printf(" LEGS: NONE\n");
        }
        printf("=================================================================\n\n");
        printf(" 1 - If you want to sell Chest\n");
        printf(" 2 - If you want to sell Legs\n");
        printf(" 0 - if you want to exit\n");

        printf("\nEnter your choice: ");
        int Choice;
        scanf("%d", &Choice);
        while (getchar() != '\n');

        if (Choice == 1) {
            clearConsole();
            
            if (player->armor.chest != NULL) {
                globalPlayer.cash += globalPlayer.armor.chest->price;
                freeArmorPiece(&globalPlayer.armor.chest);
                showPlayerStats(&globalPlayer);
                printf("=================================================================\n\n");
                printf("\n You sell Chest\n");

            }
                
            else {
                printf("\n You haven't Chest\n");
            }

        }

        if (Choice == 2) {
            clearConsole();
            if (player->armor.legs != NULL) {
                globalPlayer.cash += globalPlayer.armor.legs->price;
                freeArmorPiece(&globalPlayer.armor.legs);
                showPlayerStats(&globalPlayer);
                printf("=================================================================\n\n");
                printf("\n You sell Legs\n");

            }
                
            else {
                printf("\n You haven't Legs\n");
            }
        }

        if (Choice == 0) {
            clearConsole();
                action = 0;
               
        }
        
        

    }
}

void shopInCamp() {
    int returnToCampMenu = 1;

    while (returnToCampMenu) {
        clearConsole();
        showPlayerStats(&globalPlayer);

        printf("------------------------CURRENT POSITION-------------------------\n");
        printf("=================================================================\n");
        printf(" Petrovich's mysterious store:\n");
        printf(" in this storage you can buy some armor:\n");
        printf("=================================================================\n\n");

        ArmorPiece* relic1 = generateRandomArmor(getRandomInt(0, 1), 20, 40, 5, 10, 50, 100);
        ArmorPiece* relic2 = generateRandomArmor(getRandomInt(0, 1), 10, 30, 3, 7, 25, 75);
        ArmorPiece* relic3 = generateRandomArmor(getRandomInt(0, 1), 1, 20, 1, 4, 1, 50);

        ArmorPiece** ShopArr = (ArmorPiece**)malloc(sizeof(ArmorPiece*) * 3);
        ShopArr[0] = relic1;
        ShopArr[1] = relic2;
        ShopArr[2] = relic3;
        sortShopArr(ShopArr, 3);

        printf(" AVAILABLE RELICS:\n");
        printf("=================================================================\n");

        printf(" 1 - %s (HP: +%d%%, DEF: +%d, DUR: %d)\n",
            ShopArr[0]->name, ShopArr[0]->hp_boost, ShopArr[0]->defense, ShopArr[0]->durability);

        printf("   Price: %d gold\n", ShopArr[0]->price);

        printf(" 2 - %s (HP: +%d%%, DEF: +%d, DUR: %d)\n",
            ShopArr[1]->name, ShopArr[1]->hp_boost, ShopArr[1]->defense, ShopArr[1]->durability);

        printf("   Price: %d gold\n", ShopArr[1]->price);

        printf(" 3 - %s (HP: +%d%%, DEF: +%d, DUR: %d)\n",
            ShopArr[2]->name, ShopArr[2]->hp_boost, ShopArr[2]->defense, ShopArr[2]->durability);

        printf("   Price: %d gold\n", ShopArr[2]->price);

        printf("=================================================================\n");
        printf(" Your gold: %d\n", globalPlayer.cash);
        printf("\n Select relic to buy (1-3) or 0 to leave: ");

        int buyChoice;
        scanf("%d", &buyChoice);
        while (getchar() != '\n');

        clearConsole();
        showPlayerStats(&globalPlayer);

        if (buyChoice >= 1 && buyChoice <= 3) {
            int relicIndex = buyChoice - 1;
            ArmorPiece* selectedRelic = ShopArr[relicIndex];

            if (globalPlayer.cash >= selectedRelic->price) {
                globalPlayer.cash -= selectedRelic->price;

                // Опознание и надевание (ну лил надевание с продажей)
                int isChestArmor = 0;
                const char* chest_words[] = { "Vest", "Chestplate", "Armor", "Cuirass", "Breastplate", "Chainmail" };

                for (int i = 0; i < 6; i++) {
                    if (strstr(selectedRelic->name, chest_words[i])) {
                        isChestArmor = 1;
                        break;
                    }
                }

                if (isChestArmor) {
                    if (globalPlayer.armor.chest != NULL) {
                        globalPlayer.cash += globalPlayer.armor.chest->price;
                    }
                    freeArmorPiece(&globalPlayer.armor.chest);
                    globalPlayer.armor.chest = selectedRelic;
                    printf("\n SUCCESS! %s - CHEST armor!\n", selectedRelic->name);
                }
                    
                else {
                    if (globalPlayer.armor.legs != NULL) {
                        globalPlayer.cash += globalPlayer.armor.legs->price;
                    }
                    freeArmorPiece(&globalPlayer.armor.legs);
                    globalPlayer.armor.legs = selectedRelic;
                    printf("\n SUCCESS! %s - LEGS armor!\n", selectedRelic->name);
                }

                recalculateStats(&globalPlayer);
                printf(" -%d gold\n", selectedRelic->price);

                if (selectedRelic != relic1)
                    free(relic1);
                if (selectedRelic != relic2)
                    free(relic2);
                if (selectedRelic != relic3)
                    free(relic3);

                printf("\n Press Enter to continue...");
                getchar();

            }
                
            else {
                printf("\n NOT ENOUGH GOLD! Need: %d, Have: %d\n", selectedRelic->price, globalPlayer.cash);
                free(relic1); free(relic2); free(relic3);

                printf("\n Press Enter to continue...");
                getchar();
            }

        }
            
        else if (buyChoice == 0) {
            break;

        }
            
        else {
            printf("\n Invalid choice! Please enter 1-3 or 0.\n");
            free(relic1); free(relic2); free(relic3);

            printf("\n Press Enter to continue...");
            getchar();
        }
    }

    clearConsole();
}

//---------(блок Великих ворот)

int gateCheck(Player* player) {
    int result = 0;
    if (player->armor.chest != NULL && player->armor.legs != NULL) {
        if (player->current_hp >= 140 && player->total_defense >= 15) {
            return 1;
        }
    }
    return 0;
}

void inGate() {
    showPlayerStats(&globalPlayer);

    printf("\n------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" The Great Gate:\n");
    printf(" In these lands, this is the only way out...\n");
    printf(" However, in order to pass through them, you must have enough strength...\n");
    printf("-----------------------------------------------------------------\n");
    printf(" Gatekeepers require the following characteristics\n");
    printf(" 1 - you must have 2 pieces of armor\n");
    printf(" 2 - your HP should be over 150\n");
    printf(" 3 - Your defense must exceed 15\n");
    printf("=================================================================\n");

    int gateChoice;
    printf(" if you want to enter the gate, enter 1:");
    scanf("%d", &gateChoice);
    while (getchar() != '\n');

    if (gateChoice == 1 && gateCheck(&globalPlayer) == 1) {
        printf("\n\n=================================================================\n");
        printf(" Congratulations! You've been released\n");
        printf(" This is the end of my little game for now\n");
        printf(" to complete the game, enter something\n");
        printf("\n------------------------THANKS FOR PLAНING-----------------------\n");

        int campChoice;
        scanf("%d", &campChoice);

        while (getchar() != '\n');

        cleanup();
        exit(0);
    }

    else if (gateChoice == 1) {
        printf("\n The gate remains closed. You need:\n");
        printf(" - Full armor set (chest + legs)\n");
        printf(" - At least 150 HP (you have: %d)\n", globalPlayer.current_hp);
        printf(" - At least 15 DEF (you have: %d)\n", globalPlayer.total_defense);
        printf("\n Press Enter to leave...");
        getchar();
    }

    else {
        printf("\n You decide not to try the gate.\n");
        printf(" Press Enter to continue...");
        getchar();
    }
}

//---------(Влок Случайного подземелья)

void randomDungeon() {
    int random_way = getRandomInt(1, 8);//редакция выборки комнат для проверки
    switch (random_way) {
    case 1:// неповзло, ловушечка, потеряешь хп
        smalTrapRoom();
        break;
    case 2://а тут большая ловушечка
        bigTrapRoom();
        break;
    case 3://к сожалению тут пусто
        emptyRoom();
        break;
    case 4://тебе повезло найти неплохую броню
        roomWithBarArmor();
        break;
    case 5://тебе повезло найти немного монет
        moneyRoom();
        break;
    case 6://тебе пришлось сцепиться с монстром.
        roomWithWeakMonster();
        break;
    case 7://тебе попалась экипировка с легендарными характеристиками
        roomWithGreatArmor();
        break;
    case 8://твоя броня потеряла в прочности   
        cursedArmorRoom();
        break;
    }
}

void randomDungeonLobby() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" Random Dungeon:\n");
    printf(" There is no way to enter this location...\n");
    printf("=================================================================\n");
    printf(" if you want to go in dungeon ente - 1\n");
    printf(" if you change your mind, enter something else\n");
    printf("\n Enter your choice: ");

    int wayChoice;
    scanf("%d", &wayChoice);
    while (getchar() != '\n');

    clearConsole();

    if (wayChoice == 1) {
        randomDungeon();
    }
}

//---------(блок Остальных локаций)

void inAncienRuins(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur) {
    showPlayerStats(&globalPlayer);

    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" Ancient Ruins:\n");
    printf(" Dust and destruction surround you...\n");
    printf("=================================================================\n");
    findArmor(min_hp, max_hp, min_def, max_def, min_dur, max_dur);
}

void guideHouse() {
    showPlayerStats(&globalPlayer);
    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" The guide's house:\n");
    printf(" The guide looks at you: \"What would you like to know?\"\n");
    printf("=================================================================\n");

    printf(" 1 - What is my goal?\n");
    printf(" 2 - How to strengthen my character?\n");
    printf(" 3 - What are the locations?\n");
    printf(" 4 - About Random Dungeon\n");
    printf(" 5 - Requirements for the Great Gate\n");
    printf(" 0 - Exit\n");
    printf("\n Your choice: ");

    int guideChoice;
    scanf("%d", &guideChoice);
    while (getchar() != '\n');

    clearConsole();

    switch (guideChoice) {

    case 1:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" Your goal is to pass through the Great Gate.\n");
        printf(" But you must first prove your strength.\n");
        break;
    case 2:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" Find armor in the Ruins or buy it in the Camp.\n");
        printf(" Each armor piece increases your stats.\n");
        break;
    case 3:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" Ancient Ruins - guaranteed find bad armor\n");
        printf(" Dangerous Dungeon - test yourself\n");
        printf(" Camp - rest, heal and trade\n");
        printf(" Great Gate - your final purpose\n");
        break;
    case 4:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" Random Dungeon is Very dangerous, but also rich location\n");
        printf(" This location has many rooms\n");
        printf(" Somewhere there are rewards, somewhere there are traps or monsters\n");
        printf(" Try not to die here\n");
        break;
    case 5:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" The Gate requires:\n");
        printf(" - Full armor (chest & legs)\n");
        printf(" - HP: 140 or more (you have: %d)\n", globalPlayer.current_hp);
        printf(" - Defense: 15 or more (you have: %d)\n", globalPlayer.total_defense);
        break;
    default:
        showPlayerStats(&globalPlayer);
        printf("\n=================================================================\n");
        printf(" I don't know what to say to you about this..\n");
        break;
    }
}

void inSicretLocation() {
    globalPlayer.cash += 500;
    showPlayerStats(&globalPlayer);

    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" secret storage:\n");
    printf(" you receive a certain amount of money.\n");
    printf(" the player magically receives 500 coins\n");
    printf("=================================================================\n");
}

void uncorrectWay() {
    showPlayerStats(&globalPlayer);

    printf("------------------------CURRENT LOCATION-------------------------\n");
    printf("=================================================================\n");
    printf(" Unknown Place:\n");
    printf(" You shouldn't follow non-existent paths.\n");
    printf("=================================================================\n");
}

void chooseLocation() {
    int way = BranchingPointInfo();

    switch (way) {
    case 1:
        inAncienRuins(1, 15, 1, 3, 1, 30);
        break;
    case 2:
        randomDungeonLobby();
        break;

    case 3:
        mainCamp();
        break;

    case 4:
        inGate();
        break;

    case 5:
        guideHouse();
        break;

    case 24312:
        inSicretLocation();
        break;

    default:
        uncorrectWay();
        break;

    }
    printf("\n");
}

