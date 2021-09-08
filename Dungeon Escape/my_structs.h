// * * * * Hier werden alle Structs und Enums deklariert, die ich brauche * * * * //
// Verhindern, das die Enums & Structs mehrfach eingebunden werden
#ifndef my_structs_h
#define my_structs_h
// * Enums * //
// Richtungen
typedef enum {
    NORDEN, 
    OSTEN, 
    SUEDEN, 
    WESTEN
}Himmelsrichtung;

// Feldtyp
typedef enum {
    LEER,
    SPIELER, 
    MONSTER, 
    WAND, 
    AUSGANG
}EntityArt;

// Status des Spiels
typedef enum {
    LAUFT,
    GEWONNEN, 
    VERLOREN,
    LEESEFEHLER
}Spielstand;

// * Structs * //
// Entität
typedef struct {
    int x_coord;
    int y_coord;
    Himmelsrichtung blickrichtung;
    EntityArt art;
    char sprite;
}Entity;

// Verkettete Liste der Monster
typedef struct Monsterknoten{
    Entity* monster;
    struct Monsterknoten* vorgaenger;
    struct Monsterknoten* nachfolger;
}Monsterknoten;

// Das Spielfeld
typedef struct {
    Entity*** felder;
    int hoehe;
    int breite;
    Spielstand status;
    Monsterknoten* monsterliste;
}Grid;

#endif