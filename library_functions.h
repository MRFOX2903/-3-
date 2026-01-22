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

//-------------------(блок main_functions.c)

void cleanup();
void clearConsole();
void initPlayer(Player* player);
void showPlayerStats(Player* player);
void recalculateStats(Player* player);
void freeArmorPiece(ArmorPiece** armor);
void findArmor(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur);
ArmorPiece* generateRandomArmor(int part_type, int min_hp, int max_hp, int min_def, int max_def, int min_durab, int max_durab);
void armorDamage(Player* player, int value);

ArmorPiece** sortShopArr(ArmorPiece** arr, int size);

//-------------------(блок location_functions.c)
void chooseLocation();
void waitForExit();
void mainCamp();
void shopInCamp();
void sellInCamp(Player* player);
void playerHealinCamp();
void inGate();
int gateCheck(Player* player);
void inAncienRuins(int min_hp, int max_hp, int min_def, int max_def, int min_dur, int max_dur);
void inSicretLocation();
void guideHouse();
void uncorrectWay();

//-------------------(блок Random_dungeon_rooms.c)

void randomDungeonLobby();

void smalTrapRoom();
void bigTrapRoom();
void emptyRoom();
void roomWithBarArmor();
void roomWithGreatArmor();
void moneyRoom();
void roomWithWeakMonster();
void cursedArmorRoom();

#endif

