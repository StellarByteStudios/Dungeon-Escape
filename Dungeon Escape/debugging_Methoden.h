// Verhindern, das der header mehrfach eingebunden wird
#ifndef debugging_Methoden_h
#define debugging_Methoden_h

#include <stdio.h>
#include <stdlib.h>

#include "my_structs.h"
#include "entity_management.h"
#include "grid_management.h"

void debug_entity(Entity* ent, char name[]);
void debug_level_streams(FILE* output, FILE* level);
void debug_level(FILE* output, char levelname[]);
void debug_multi_level(FILE* output, char* levelname[], int anzahl);

#endif