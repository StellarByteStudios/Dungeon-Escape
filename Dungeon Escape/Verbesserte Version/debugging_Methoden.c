#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugging_Methoden.h"
/* Gibt eine Entität mit all ihren daten aus */
void debug_entity(Entity* ent, char name[]){
    printf("%s erzeugt mit:       \n", name);
    printf("\tX-Koordinate:     %d\n", ent->x_coord);
    printf("\tY-Koordinate:     %d\n", ent->y_coord);
    printf("\tBlickrichtung:    %d\n", ent->blickrichtung);
    printf("\tEntity Art:       %d\n", ent->art);
    printf("\tSprite:           %c\n\n", ent->sprite);

    return;
}

/* Ließt ein Spielfeld ein, gibt es einmal aus und gibt den Speicher wieder frei */
void debug_level_streams(FILE* output, FILE* level){
    fprintf(output, "Versuche ein volles Spielfeld zu erzeugen\n");
    Grid *einfachesGrid = read_grid(level);
    fprintf(output, "Spielfeld wurde erzeugt\n");
    fprintf(output, "Spielfeld soll jetzt ausgegeben werden\n\n");
    print_grid(output, einfachesGrid);
    fprintf(output, "\nSpielfeld wird wieder freigegeben\n");
    free_grid(einfachesGrid);
    fprintf(output, "Spielfeld wurde freigegeben\n\n");
}

/* Öffnet ein Spielfeld durch einen Namen und gibt es wieder aus */
void debug_level(FILE* output, char levelname[]){
    printf("%s ---------------------------------------------\n\n", levelname);
        
        fprintf(output, "Öffne Levelfile\n");
        FILE *levelvorlage = fopen(levelname, "r");
        fprintf(output, "Versuche ein volles Spielfeld zu erzeugen\n");
        Grid *einfachesGrid = read_grid(levelvorlage);
        fprintf(output, "Spielfeld wurde erzeugt\n");
        fprintf(output, "Spielfeld soll jetzt ausgegeben werden\n\n");
        print_grid(output, einfachesGrid);
        fprintf(output, "\nSpielfeld wird wieder freigegeben\n");
        free_grid(einfachesGrid);
        fprintf(output, "Spielfeld wurde freigegeben\n\n");
        fclose(levelvorlage);

}

/* Das selbe wie debug_level nur mit mehreren levels */
void debug_multi_level(FILE* output, char* levelname[], int anzahl){
    printf(" - - Gehe jetzt durch die einzelnen Level - -\n\n");

    for (int i = 0; i < anzahl; i++){
        debug_level(output, levelname[i]);
    }

    fprintf(output, "* * * * * Durch alle Level durch * * * * *\n\n");
}
