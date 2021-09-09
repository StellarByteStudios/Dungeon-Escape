#include "grid_management.h"

// * * Liest das Level aus einem Stream ein und gibt das Grid zurück * * //
Grid* read_grid(FILE* level){
    // Variablen festlegen
    int mase[3];
    Grid *grid;
    // Sicherheitsmaßname
    rewind(level);

    // Ist das Level leesbar? Wenn nicht, leeres Feld mit Fehlerstatus zurückgeben
    if(fgetc(level) == EOF){
        mase[0] = 5;
        mase[1] = 5;
        grid = create_empty_grid(mase);
        grid->status = LEESEFEHLER;
        return grid;
    }

    // Maße des Levels bestimmen
    get_size_of_grid(level, mase);
    rewind(level);

    // Erzeugen eines groß genugen, leeren Spielfeldes
    grid = create_empty_grid(mase);
    grid->status = LAUFT;
    
    // Füllen des Grids
    fill_grid(grid, level);

    // Rückgabe des Grids
    return grid;
}

/* Lädt das Level in das Grid */
void fill_grid(Grid* grid, FILE* feldvorlage){
    //Variablen festlegen
    char nextField;
    // Koordinaten
    int x = 0;
    int y = 0;
    
    // Geht durch die Zeilen
    while(y < grid->hoehe){
        // Variablen zurücksetzen
        nextField = 42;
        x = 0;

        // Geht eine Zeile durch
        while(x < grid->breite){
            // Spaltenabbruchbedingungen; Prüfe ob wir am Ende der Zeile Sind
            if(nextField == 10){ break; }

            // Liest ein, was die nächste Entität ist
            nextField = fgetc(feldvorlage);

            // Erzeugt die neue Entität
            Entity *cell = char_to_entity(x, y, nextField);

            // Überschreibt das alte Feld mit dem neuen
            free_entity(grid->felder[y][x]);
            grid->felder[y][x] = cell;
            
            // Monster in die Liste einfüllen, wenn das eingelesene ein Monster ist
            if(cell->art == MONSTER){
                // Neues Monster erzeugen
                Entity *newMon = char_to_entity(x, y, nextField);
                // Erstes Monster?
                if(grid->monsterliste == NULL){
                    // Leere Liste Löschen
                    free_Monsterliste(grid->monsterliste);
                    // Neuer Kopf einfügen 
                    grid->monsterliste = create_Monster(newMon); 
                } else {
                    // Einfach neues Monster in die Liste packen
                    grid->monsterliste = add_Monster_front(grid->monsterliste, newMon);
                }
            }
            x++;
        }
        y++;
    }
    return;
}

/* Erzeugt ein Spielfeld nach Maß und befüllt es leer */
Grid* create_empty_grid(int mase[]){
    // Variablen festlegen
    Entity ***felder;
    int hoehe  = mase[0];
    int breite = mase[1];

    // So viele Zeiger auf Zeilen freigeben, wie das Feld an Höhe hat
    felder = malloc(hoehe * sizeof(Entity ***));

    // In jeder Zeile genug platz schaffen für das gesammte Spielfeld
    for (int i = 0; i < hoehe; i++){
        felder[i] = malloc(breite * sizeof(Entity **));
    }
    
    // Leer Befüllen 
    for (int i = 0; i < hoehe; i++) {
        for (int k = 0; k < breite; k++) {
            felder[i][k] = create_entity(k, i , NORDEN, LEER);
        } 
    }

    // Platz für den eigentlichen Gridpointer
    Grid *grid = malloc(sizeof(Entity***) 
                        + sizeof(int) 
                        + sizeof(int) 
                        + sizeof(Spielstand) 
                        + sizeof(Monsterknoten)); // Müsste eigentlich sizeof(Monsterknoten*) sein, aber das gibt Fehler
    
    // Grid jetzt nur noch befüllen
    grid->felder = felder;
    grid->hoehe = hoehe;
    grid->breite = breite;
    grid->monsterliste = NULL;

    // Das leere Spielfeld zurückgeben
    return grid;
}

/* Misst Höhe und Breite des Spielfeldes */
void get_size_of_grid(FILE* feldvorlage, int mase[]){
    // Variablen festlegen
    int hoehe = 0;
    int breite = 0;
    int maxBreite = 0;
    char nextChar = 42;
    
    // Erste While zählt die Zeilen
    while(1){
        // Geht durch das ganze Level durch
        if(feof(feldvorlage)){ break; }

        breite = 0;
        nextChar = 42;

        // Zweite While zählt die maximale länge einer Zeile
        while(1){
            nextChar = fgetc(feldvorlage);
            breite++;
            // Prüfe ob wir am Ende der Zeile Sind
            if(nextChar == 10){ break; }

            // Wenn das nicht hier steht, gib es einen Dauerloop
            if(feof(feldvorlage)){ break; }
        }        
        // Überprüft ob es eine neue maximale Breite gibt
        if(breite > maxBreite){
            maxBreite = breite;
        }

        hoehe++;
    }

    // Übergibt die gemessenen Daten
    mase[0] = hoehe;
    mase[1] = maxBreite;
    return; 
}

/* Freigeben des Spielfeldes */
void free_grid(Grid* grid){
    
    for (int i = 0; i < grid->hoehe; i++){
        for (int k = 0; k < grid->breite; k++){
            // Freigeben jedes einzelnen Feldes
            free(grid->felder[i][k]);
        }
        // Freigeben jeder einzelnen Zeile (Pointer)
        free(grid->felder[i]);   
    }
    // Freigeben der Monsterliste des Spielfeldes
    free_Monsterliste(grid->monsterliste);

    // Freigabe des Pointers auf die Spielfelder
    free(grid->felder);

    // Freigeben des gesammten Spielbrettes ansich
    free(grid);
    return;
}

// * * Gibt das Spielfeld in einen Stream aus * * //
void print_grid(FILE* outStream, Grid* grid){
    // Geht durch das ganze Spielfeld durch
    for (int x = 0; x < grid->hoehe -1; x++){
        for (int y = 0; y < grid->breite -1; y++){ // -1 Weil die Tests sonst Stress machen
            // Ausgabe des Sprites der Entität auf der entsprechenden Koordinate
            fprintf(outStream, "%c", grid->felder[x][y]->sprite);
        }
        // Zeilenumbruch nach einer Zeile
        fprintf(outStream, "\n");
    }

    return;
}

// * * Aktualliesiert das Spielfeld für einen Zyklus * * //
void grid_cycle(Grid* grid, Himmelsrichtung dir){
    // Koordinaten für den Spieler
    int x_spieler;
    int y_spieler;

    // Gehe durch das ganze Grid durch und schau wo der Spieler ist
    for (int y = 0; y < grid->hoehe; y++){
        for (int x = 0; x < grid->breite; x++){
            if(grid->felder[y][x]->art == SPIELER){
                x_spieler = x;
                y_spieler = y;
            }
        }   
    }

    // Bewegt den Spieler in die gewollte Richtung
    move_player(grid, dir, x_spieler, y_spieler);

    // Bewegt die Monster (Löscht sie von Spielfeld, aber speichert die Koordinaten in der Monsterliste)
    move_monster(grid);

    // Nimmt alle Monster aus der Monsterliste und setzt sie wieder auf das Spielfeld
    set_monster_on_grid(grid);

    return;
}

/* Bewegt den Spieler in einem Spielzyklus */
void move_player(Grid* grid, Himmelsrichtung dir, int x, int y){
    // Koordinaten zur Berechnung
    int new_x = x;
    int new_y = y;
    // Sonstige Variablen
    EntityArt nachbar;

    // Wohin geht der Spieler?
    switch (dir) {
        case SUEDEN:
            // Bestimmen der Nachbarkoordinaten
            new_y = y + 1;
            // Welche Art von Entität ist der Nachbar
            nachbar = grid->felder[new_y][x]->art;
            // Kollision berechnen
            collision_player(grid, nachbar, x, y, new_x, new_y);
            break;

        case OSTEN:
            // Bestimmen der Nachbarkoordinaten
            new_x = x + 1;
            // Welche Art von Entität ist der Nachbar
            nachbar = grid->felder[y][new_x]->art;
            // Kollision berechnen
            collision_player(grid, nachbar, x, y, new_x, new_y);
            break;

        case NORDEN:
            // Bestimmen der Nachbarkoordinaten
            new_y = y - 1;
            // Welche Art von Entität ist der Nachbar
            nachbar = grid->felder[new_y][x]->art;
            // Kollision berechnen
            collision_player(grid, nachbar, x, y, new_x, new_y);
            break;
            
        case WESTEN:
            // Bestimmen der Nachbarkoordinaten
            new_x = x - 1;
            // Welche Art von Entität ist der Nachbar
            nachbar = grid->felder[y][new_x]->art;
            // Kollision berechnen
            collision_player(grid, nachbar, x, y, new_x, new_y);
            break;
    }
    return;
}

/* Berechnet die Kollision des Spielers */
void collision_player(Grid* grid, EntityArt nachbar, int x, int y, int new_x, int new_y){
    // Anlegen neuer Entitäten
    Entity *spieler;
    Entity *leer;

    // Gegen was läuft der Spieler?
    switch (nachbar){
        case LEER:
        case MONSTER:
                // Spieler geht einfach ein Feld weiter //
                // Erschaffen neuer Felder
                spieler = char_to_entity(new_x, new_y, 'S');
                leer = char_to_entity(x, y, ' ');
                // Alte Felder werden freigegeben
                free_entity(grid->felder[y][x]);
                free_entity(grid->felder[new_y][new_x]);
                // Neue Felder werdem dem Spielfeld übergeben
                grid->felder[new_y][new_x] = spieler;
                grid->felder[y][x] = leer;
            break;
        case AUSGANG:
                // Erschaffen neuew Felde
                leer = char_to_entity(x, y, ' ');
                // Altes Feld wird freigegeben
                free_entity(grid->felder[y][x]);
                grid->felder[y][x] = leer;
                // Unterbricht den Gameloop; Spieler hat gewonnen
                grid->status = GEWONNEN;
            break;

        default:
            // Wenn der Spieler sonst irgendwo gegenläuft, dann soll er einfach stehen bleiben
            break;
    }
    return;
}

/* Bewegt die ganzen Monster in einem Spielzyklus */
void move_monster(Grid* grid){
    // Holen des Anfangs der Monsterliste
    Monsterknoten *aktuellesMonster = grid->monsterliste;

    // Geht alle Monster durch und löse bei ihnen die Kollision aus
    while (aktuellesMonster != NULL){
        // Koordinaten zur Berechnung
        int x = aktuellesMonster->monster->x_coord;
        int y = aktuellesMonster->monster->y_coord;
        int new_x = x;
        int new_y = y;
        // Sonstige Variablen
        Himmelsrichtung monsterrichtung = aktuellesMonster->monster->blickrichtung;
        EntityArt nachbar;

        // In welche Richtung schaut/geht das Monster?
        switch (monsterrichtung){
            case SUEDEN:
                // Bestimmen der Nachbarkoordinaten
                new_y = y + 1;
                // Welche Art von Entität ist der Nachbar
                nachbar = grid->felder[new_y][x]->art;
                // Kollision berechnen
                collision_monster(grid, aktuellesMonster, nachbar, x, y, new_x, new_y);
                break;

            case OSTEN:
                // Bestimmen der Nachbarkoordinaten
                new_x = x + 1;
                // Welche Art von Entität ist der Nachbar
                nachbar = grid->felder[y][new_x]->art;
                // Kollision berechnen
                collision_monster(grid, aktuellesMonster, nachbar, x, y, new_x, new_y);
                break;

            case NORDEN:
                // Bestimmen der Nachbarkoordinaten
                new_y = y - 1;
                // Welche Art von Entität ist der Nachbar
                nachbar = grid->felder[new_y][x]->art;
                // Kollision berechnen
                collision_monster(grid, aktuellesMonster, nachbar, x, y, new_x, new_y);
                break;
                
            case WESTEN:
                // Bestimmen der Nachbarkoordinaten
                new_x = x - 1;
                // Welche Art von Entität ist der Nachbar
                nachbar = grid->felder[y][new_x]->art;
                // Kollision berechnen
                collision_monster(grid, aktuellesMonster, nachbar, x, y, new_x, new_y);
                break;
        }
        // Weiter in der Liste
        aktuellesMonster = aktuellesMonster->nachfolger;
    }
    return;   
}

/* Berechnet die Kollision der Monster (Verschiebt sie aber nicht auf dem Feld) */
void collision_monster(Grid* grid, Monsterknoten* monsterKnoten, EntityArt nachbar, 
                        int x, int y, int new_x, int new_y){
    // Entität (Leeres Feld) zum auffüllen der verlassenen Position
    Entity *leer;

    // Auf was stößt das Monster?
    // Es werden nur die Koordinaten in der Monsterliste geändert und alle Monster gelöscht
    switch (nachbar){
        case MONSTER:
        case LEER:
                // Geht der Spieler auf ein Feld, auf dem ein Monster war, wird dieser nicht gelöscht
                if(grid->felder[y][x]->art != SPIELER){
                    leer = char_to_entity(x, y, ' ');   
                    free_entity(grid->felder[y][x]);
                    grid->felder[y][x] = leer;
                }
                // Aktuallisiert Monsterliste
                monsterKnoten->monster->x_coord = new_x;
                monsterKnoten->monster->y_coord = new_y;
            break;

        case SPIELER:
                // Spieler wird überschieben und gefressen
                leer = char_to_entity(x, y, ' ');
                free_entity(grid->felder[y][x]);
                grid->felder[y][x] = leer;
                // Aktuallisiert Monsterliste
                monsterKnoten->monster->x_coord = new_x;
                monsterKnoten->monster->y_coord = new_y;
                // Unterbricht den Gameloop; Spieler wird gefressen
                grid->status = VERLOREN;
            break;

        default:
            // Wenn das Monster irgendwo gegenläuft, dann soll es sich einfach umdrehen
            switch(monsterKnoten->monster->blickrichtung){
                case SUEDEN:
                        leer = char_to_entity(x, y, ' ');
                        // Aktuallisiert Monsterliste
                        monsterKnoten->monster->blickrichtung = NORDEN;
                        monsterKnoten->monster->sprite = '^';
                        // Läuft der Spieler in das Monster rein, wird er gefressen
                        if(grid->felder[y][x]->art == SPIELER) { grid->status = VERLOREN; }
                        // Monster wird auf dem Spielfeld gelöscht
                        free_entity(grid->felder[y][x]);
                        grid->felder[y][x] = leer;
                    break;

                case OSTEN:
                        leer = char_to_entity(x, y, ' ');
                        // Aktuallisiert Monsterliste
                        monsterKnoten->monster->blickrichtung = WESTEN;
                        monsterKnoten->monster->sprite = '<';
                        // Läuft der Spieler in das Monster rein, wird er gefressen
                        if(grid->felder[y][x]->art == SPIELER) { grid->status = VERLOREN; }
                        // Monster wird auf dem Spielfeld gelöscht
                        free_entity(grid->felder[y][x]);
                        grid->felder[y][x] = leer;
                    break;

                case NORDEN:
                        leer = char_to_entity(x, y, ' ');
                        // Aktuallisiert Monsterliste
                        monsterKnoten->monster->blickrichtung = SUEDEN;
                        monsterKnoten->monster->sprite = 'v';
                        // Läuft der Spieler in das Monster rein, wird er gefresse
                        if(grid->felder[y][x]->art == SPIELER) { grid->status = VERLOREN; }
                        // Monster wird auf dem Spielfeld gelöscht
                        free_entity(grid->felder[y][x]);
                        grid->felder[y][x] = leer;
                    break;

                case WESTEN:
                        leer = char_to_entity(x, y, ' ');
                        // Aktuallisiert Monsterliste
                        monsterKnoten->monster->blickrichtung = OSTEN;
                        monsterKnoten->monster->sprite = '>';
                        // Läuft der Spieler in das Monster rein, wird er gefresse
                        if(grid->felder[y][x]->art == SPIELER) { grid->status = VERLOREN; }
                        // Monster wird auf dem Spielfeld gelöscht
                        free_entity(grid->felder[y][x]);
                        grid->felder[y][x] = leer;
                    break;
                }
            break;
    }
    return;
}

/* Setzt nun die Monster an die neuen Positionen */
void set_monster_on_grid(Grid* grid){
    // Holen des Anfangs der Monsterliste
    Monsterknoten *aktuellesMonster = grid->monsterliste;

    // Geht alle Monster durch und aktualliesiert die Daten auf dem Spielfeld
    while (aktuellesMonster != NULL){
        // Koordinaten holen
        int x = aktuellesMonster->monster->x_coord;
        int y = aktuellesMonster->monster->y_coord;

        // Monsterfeld erstellen
        Entity *monsterEnt = char_to_entity(x, y, aktuellesMonster->monster->sprite);

        // Zielfeld Freimachen
        free_entity(grid->felder[y][x]);

        //Zielfeld besetzen
        grid->felder[y][x] = monsterEnt;

        // Weiter in der Liste
        aktuellesMonster = aktuellesMonster->nachfolger;
    }
    return;   
}
