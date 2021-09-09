#include "monsterliste.h"

/* Erzeugt einen neuen Knotenpunkt */
Monsterknoten* create_Monster(Entity* monster){
    // Platz reservieren
    Monsterknoten *MonKnoten = malloc(sizeof(Monsterknoten));
    // Knoten füllen
    MonKnoten->monster = monster;
    MonKnoten->vorgaenger = NULL;
    MonKnoten->nachfolger = NULL;

    return MonKnoten;
}

/* Erstellt ein neues Monster am oberen Ende der Liste und gibt den neuen Kopf aus */
Monsterknoten* add_Monster_front(Monsterknoten* head, Entity* monster){
    // Neuer Monsterknoten erschaffen
    Monsterknoten *newKnoten = create_Monster(monster);
    // Neue Belegung festlegen
    newKnoten->nachfolger = head;
    head->vorgaenger = newKnoten;
    // Kopf verschieben
    head = newKnoten;
    // Neuen Listenkopf zurückgeben
    return head;
}

/* Gibt die Liste von vorne bis hinten aus */
void print_Monsterlist(Monsterknoten* head){
    Monsterknoten *printPointer = head;
    while (printPointer != NULL){
        debug_entity(printPointer->monster, "Monster aus der Liste");
        printPointer = printPointer->nachfolger;
    }
    return;    
}

/* Gibt den Speicher für die Liste wieder Frei */
void free_Monsterliste(Monsterknoten* head){
    Monsterknoten *freePointer = head;
    Monsterknoten *nextPointer;
    if(freePointer == NULL) { return; }
    while (freePointer != NULL){
        nextPointer = freePointer->nachfolger;
        free_entity(freePointer->monster);
        free(freePointer);
        freePointer = nextPointer;
    }
}
