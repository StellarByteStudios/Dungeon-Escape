// Verhindern, das der header mehrfach eingebunden wird
#ifndef monsterliste_h
#define monsterliste_h

#include "my_structs.h"
#include "debugging_Methoden.h"

Monsterknoten* create_Monster(Entity* monster);
Monsterknoten* add_Monster_front(Monsterknoten* head, Entity* monster);
void print_Monsterlist(Monsterknoten* head);
void free_Monsterliste(Monsterknoten* head);

#endif