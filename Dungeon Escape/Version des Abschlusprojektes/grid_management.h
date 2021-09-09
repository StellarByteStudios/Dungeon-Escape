// Verhindern, das der header mehrfach eingebunden wird
#ifndef grid_management_h
#define grid_management_h

#include <stdio.h>
#include <stdlib.h>
#include "my_structs.h"
#include "entity_management.h"
#include "debugging_Methoden.h"
#include "monsterliste.h"

Grid* read_grid(FILE* level);
void fill_grid(Grid* grid, FILE* feldvorlage);
Grid* create_empty_grid(int mase[]);
void get_size_of_grid(FILE* feldvorlage, int mase[]);
void free_grid(Grid* grid);
void print_grid(FILE* outStream, Grid* grid);
void grid_cycle(Grid* grid, Himmelsrichtung dir);
void move_player(Grid* grid, Himmelsrichtung dir, int x, int y);
void collision_player(Grid* grid, EntityArt nachbar, int x, int y, int new_x, int new_y);
void move_monster(Grid* grid);
void collision_monster(Grid* grid, Monsterknoten* monsterKnoten, EntityArt nachbar, 
                        int x, int y, int new_x, int new_y);
void set_monster_on_grid(Grid* grid);

#endif