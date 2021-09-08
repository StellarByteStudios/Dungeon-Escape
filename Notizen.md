# - Was soll das Programm sein? - #
Ein Dungeon Escape-Room Spiel in welchem man durch eingaben ein Männchen Bewegen kann


# - Was brauch ich? - #
## Strucktur:
- Ein Grind bestehend aus Feldern (Wichtig: Variabel und unbeschränkt)
    + Entweder als 2-dim-LinkedList oder mit Koordinaten (DynArray)
- Felder, welche einen Inhalt und vier Nachbarn haben
- Die Entitäten welche auf den Feldern sein können
    + Wand          (#): Undurchdringlich für alle beweglichen Entitäten
    + Spieler       (S): Kann in 4 Richtungen Bewegt werden
    + Ausgang       (A): Muss vom Spieler erreicht werden. Beendet das Spiel
    + Leeres Feld   ( ): Leeres Feld auf dem sich Spieler und Monster bewegen können
    + Monster (< > v ^): Geht immer in eine Richtung (Dreht bei Wänden). Kann Spieler fressen
    


# - Wie läuft das Programm ab? - #
## Start:
- Einlesen des Levels
- Visualisieren des Levels im Speicher
- Auf ersten Befehl warten

## Spielloop:
- Eingabe des Befehls für den Spieler
- Spieler und dann Monster werden auf dem Spielfeld bewegt
    + Kollision:
        * Wand: Spieler kommt nicht weiter/Monster dreht um 180°
        * Ausgang: Spieler gewinnt
        * Monster/Spieler: Spieler verliert
- Ausgabe des Befehls
- Ausgabe des Levels

## Ende:


# - Wie funktioniert die Eingabe/der Aufruf? - #
## Starten des Programmes:
- Dateiname des Levels als CmdLnArg angeben (std = level/1.txt)
- i: Datei der Eingabe (std = Standardeingabe)
- o: Datei der Ausgabe (std = Standardausgabe)

- Level: Wird beim Aufruf von einer Datei eingelesen
- Spielerbewegung: Über die Standarteingabe oder eine Datei

# - Wie funktioniert die Ausgabe? - #
## Spielbeginn:
- Das Level ausgeben    

## nach bearbeitung des Befehls:
- Anzahl der bereits gegangenen Schritte
- Eingegebener Befehl
- Neuer Stand des Spielfeldes

## Beenden des Spiel (nach der obigen Ausgabe)
- Bei erreichen des Ausgangs: "Gewonnen"
    + Level soll noch angezeigt werden, Spieler aber nicht mehr
- Verloren durch Monster: "Du wurdest von einem Monster gefressen."
    + Level soll noch angezeigt werden, Spieler aber nicht mehr


# - Verhalten bei falschen Angaben und sonstigen Fehlern - #
## Rückgabewerte
- 0 wenn alles glatt läuft
- 1 wenn eine Datei sich nicht öffnen lässt
- 2 wenn eine Datei nicht leesbar ist
- 3 wenn eine ungültige, zu viele oder doppelte Optionen an das Programm übergeben wurden
## Monster trifft auf Monster
- Nur das Erste soll angezeigt werden (Aber es müssen beide Existieren)



# - Was ist an Code dabei herumgekommen? - #
Alles in Zeilen (Mit Kommentaren)
- Alle .c dokumente: 877
- Alle .c dokumente mit structs: 934
- .c + Headder: 1021