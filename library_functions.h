#ifndef LIBRARY_FUNCTIONS_H
#define LIBRARY_FUNCTIONS_H

typedef struct {
    char name[50];
    int durability;
    int defense;
    int hp_boost;
    int price;
} ArmorPiece;

typedef struct {
    ArmorPiece* chest;
    ArmorPiece* legs;
} ArmorSet;

typedef struct {
    int base_hp;
    int current_hp;
    int lost_hp;
    int base_defense;
    int total_defense;
    int cash;
    ArmorSet armor;
} Player;

void cleanup();
void clearConsole();
void chooseLocation();
void waitForExit();
void initPlayer(Player* player);
void showPlayerStats(Player* player);
void recalculateStats(Player* player);
void freeArmorPiece(ArmorPiece** armor);
void mainCamp();
void shopInCamp();
void inGate();
void inAncienRuins(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur);
void findArmor(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur);
void inSicretLocation();
void guideHouse();
int gateCheck(Player* player);
void uncorrectWay();
void playerHealinCamp();
ArmorPiece* generateRandomArmor(int part_type, int min_hp, int max_hp, int min_def, int max_def, int min_durab, int max_durab);

void randomDungeonLobby();

void smalTrapRoom();
void bigTrapRoom();
void emptyRoom();
void roomWithBarArmor();
void roomWithGreatArmor();
void moneyRoom();

#endif