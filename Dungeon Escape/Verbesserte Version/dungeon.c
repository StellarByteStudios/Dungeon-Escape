#include "dungeon.h"

int main(int argc, char *argv[]){
    // Variablen deklarieren
    char *leveladresse;
    FILE *levelvorlage;
    FILE *output;
    FILE *input;
    int doubleIn = 0;
    int doubleOut = 0;
    char option;

    // Variablen mit Standartwerten füllen
    leveladresse = "level/6.txt";
    output = stdout;
    input = stdin;

    while ((option = getopt(argc, argv, "i:o:")) != EOF){
        switch (option) {
        // case -i
        case 'i':
            // Holt den Input aus einer anderen Datei
            if(doubleIn > 0){
                fclose(input);
                errormsg("Es wurden zu viel input geben");
                return 3;
            }
            input = fopen(optarg, "r");
            doubleIn++;
            break;  
        // case -o
        case 'o':
            // Leitet den Output in andere Datei um
            if(doubleOut > 0){
                fclose(output);
                errormsg("Es wurden zu viel output gegeben");
                return 3;
            }
            output = fopen(optarg, "w");   
            doubleOut++;        
            break;
        default:
            // Gibt eine Fehlermeldung aus
            errormsg("Falsche Option angegeben");
            // Beendet das Programm mit einem Fehler
            return 3;
        }
    }
    argc -= optind;
    argv += optind;  

    // Leveladresse laden
    if (argc == 1){ leveladresse = argv[0]; }

    if(argc > 1){
        errormsg("Es wurden zu viele Parameter übergeben");
        return 3;
    }    

    // Levelvorlage zum einlesen bereitmachen
    levelvorlage = fopen(leveladresse, "r");

    // Fehlerbehandlung
    if (levelvorlage == NULL){
        errormsg("Inputdatei konnte nicht geöffnet werden");
        return 1;
    }
    if (output == NULL){
        errormsg("Outputdatei kann nicht beschrieben werden");
        fclose(levelvorlage);
        fclose(input);
        return 1;
    }
    if (input == NULL){
        errormsg("Inputdatei konnte nicht geöffnet werden");
        fclose(levelvorlage);
        fclose(output);
        return 1;
    }
    // Spiel mit allen Daten starten
    int fehlerstatus = game_start(levelvorlage, input, output);

    // Alle Streams schließen
    fclose(levelvorlage);
    fclose(output);
    fclose(input);

    return fehlerstatus;
}

/* * Hier beginnt das eigentliche Spiel * */ 
int game_start(FILE* level, FILE* input, FILE* output){
    // Spielfeld einlesen
    int outcome;
    Grid *spielfeld = read_grid(level);

    // Fehlerbehandlung
    if(spielfeld->status == LEESEFEHLER){
        errormsg("Level konnte nicht gelesen werden");
        free_grid(spielfeld);
        return 2;
    }
    print_grid(output, spielfeld);

    // Game_Loop Starten
    // return 0 = gewonnen; return 1 = verloren; return 2 = beendet
    outcome = game_loop(spielfeld, input, output);

    // Ende vorbereiten
    if(outcome == 0){
        fprintf(output, "Gewonnen!\n");
    }
    if(outcome == 1){
        fprintf(output, "Du wurdest von einem Monster gefressen.\n");
    }
    if(outcome == 2){
        fprintf(output, "Wie kannst du nur mein Spiel beenden...?\n");
    }
    // Leesefehler
    if(outcome == 3){
        free_grid(spielfeld);
        return 2;
    }
    free_grid(spielfeld);
    return 0;
}

/* Game-Loop der bis zum Durchläuft */
int game_loop(Grid* spielfeld, FILE* input, FILE* output){
    // Variable zum zählen der Spielzüge
    int k = 1;
    // Die Richtung in die der Spieler gehen will
    char richtungseingabe;
    Himmelsrichtung richtung;

    while(1){
        // In welche Richtung soll gegangen werden + Fehlerbehandlung, wenn die Eingabe nicht leesbar ist
        if(fscanf(input, " %c", &richtungseingabe) == EOF){
            errormsg("Die Eingabe konnte nicht gelesen werden");
            return 3;
        }

        // Ausgabe des wievielten Spielzugs
        fprintf(output, "%d %c\n", k,richtungseingabe);

        // Wurde das Spiel beendet?
        if(richtungseingabe == 'q') {return 2; }

        // Konvertieren der Richtung
        richtung = char_to_dir(richtungseingabe);
        
        // Ausführen eines Spielzykluses
        grid_cycle(spielfeld, richtung);

        // Ausgeben des neu veränderten Feldes
        print_grid(output, spielfeld);

        // Unterbrechungen im Game Loop
        if(spielfeld->status == GEWONNEN) { return 0; }
        if(spielfeld->status == VERLOREN) { return 1; }
        k++;
    }

    return 0;
}

/* Konvertiert die Eingabe des Spielers in eine Richtung*/
Himmelsrichtung char_to_dir(char in){
    Himmelsrichtung dir = NORDEN;
    switch (in){
        case 'd':
            dir = OSTEN;
            break;
        case 's':
            dir = SUEDEN;
            break;
        case 'a':
            dir = WESTEN;
            break;
        default:
            dir = NORDEN;
            break;
    }
    return dir;
}

/* Ein Level via Stream einlesen und in einen outputstream ausgeben */ // Verwendet für Debugging
void execute_debugging_read_and_out(FILE* level, FILE* output){
    debug_level_streams(output, level);
}

/* Die ersten paar Level ausmessen, alloziieren, einlesen und ausprinten */ // Verwendet für Debugging
void execute_debugging_print_levels(){
    char *filename[20] = {  "level/1.txt", 
                            "level/2.txt",
                            "level/3.txt", 
                            "level/4.txt", 
                            "level/5.txt", 
                            "level/6.txt",
                            "level/7.txt", 
                            "level/8.txt",
                            "level/9.txt",
                            "level/10.dateiendungen_pruefen_gilt_nicht",
                            "level/11"};
    
    debug_multi_level(stdout, filename, 11);
    return;
}

/* Gibt eine Fehlermeldung aus (auf der Standartfehlerausgabe) */
void errormsg(char grund[]){
    fprintf(stderr, "Es gab einen FEHLER: %s\n", grund);
    return;
}
