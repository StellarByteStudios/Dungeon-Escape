// Verhindern, das der header mehrfach eingebunden wird
#ifndef entity_management_h
#define entity_management_h

#include <stdio.h>
#include <stdlib.h>
#include "my_structs.h"

Entity* create_entity(int x, int y, Himmelsrichtung dir, EntityArt art);
char get_sprite(Entity *entity);
void free_entity(Entity *entity);
Entity* char_to_entity(int x, int y, char sprite);

#endif