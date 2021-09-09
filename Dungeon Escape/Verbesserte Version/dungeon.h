#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "my_structs.h"
#include "debugging_Methoden.h"
#include "grid_management.h"
#include "entity_management.h"
#include "monsterliste.h"

int game_start(FILE* level, FILE* input, FILE* output);
int game_loop(Grid* spielfeld, FILE* input, FILE* output);
Himmelsrichtung char_to_dir(char in);
void execute_debugging_read_and_out(FILE* level, FILE* output);
void execute_debugging_print_levels(void);
void errormsg(char grund[]);