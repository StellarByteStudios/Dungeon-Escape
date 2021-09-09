
SOURCES='dungeon.c debugging_Methoden.c grid_management.c entity_management.c monsterliste.c'
HEADERS='dungeon.h my_structs.h debugging_Methoden.h grid_management.h entity_management.h monsterliste.h'

printf 'Es wird Kompiliert\n\n'

gcc -Wall -Wmissing-prototypes -Werror -std=c99 $SOURCES $HEADERS -o DungeonEscape -g
#printf 'Teil 1\n\n'
#gcc -c dungeon.c my_structs.h
#printf '\nTeil 2\n\n'
#gcc -c debugging_Methoden.c my_structs.h
#printf '\nTeil 3\n\n'
#gcc -Wall -std=c99 *.o -o Testprogramm

#printf '\nEs wird Ausgeführt\n\n'

#./dungeon

#printf '\nJetzt mit Leveladresse\n\n'

#./dungeon level/4.txt

#printf '\nJetzt mit Leveladresse und umleitung des Outputs\n\n'

#./dungeon -o Outputumleitung.txt level/5.txt

#printf '\nJetzt automatische Input\n\n'

#./dungeon -i Testinput.txt -o Outputumleitung.txt

#printf '\nJetzt noch mit Valgrind\n\n'

#valgrind -s --leak-check=full ./dungeon level/2.txt # -o Outputumleitung.txt -i eingabe/level3_1.txt


printf '\nEs es ist vorbei\n\n'