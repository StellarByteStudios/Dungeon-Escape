#include "entity_management.h"

// * * Entität erzeugen * * //
Entity* create_entity(int x, int y, Himmelsrichtung dir, EntityArt art){
    // Reservierung des Speicherplatz
    Entity *newEnt = malloc(sizeof(Entity));

    // Füllen der einzelnen Felder
    newEnt->x_coord = x;
    newEnt->y_coord = y;
    newEnt->art = art;
    newEnt->blickrichtung = dir;
    newEnt->sprite = get_sprite(newEnt);

    return newEnt;
}

/* Sprite berechnen und zurückgeben */
char get_sprite(Entity *entity){
    char sprite;
    // Art der Entität wird überprüft
    switch (entity->art){
        case SPIELER:
            sprite = 'S';
            break;

        case WAND:
            sprite = '#';
            break;

        case AUSGANG:
            sprite = 'A';
            break;
        // Wenn es ein Monster ist muss noch die Blickrichtung betrachtet werden
        case MONSTER:
            switch (entity->blickrichtung){
                case NORDEN:
                    sprite = '^';
                    break;

                case OSTEN:
                    sprite = '>';
                    break;

                case SUEDEN:
                    sprite = 'v';
                    break;

                default:
                    sprite = '<';
                    break;
            }
            break;

        default:
            sprite = ' ';
            break;
    }

    return sprite;
}

/* Freigeben des Speichers einer Entity */
void free_entity(Entity *entity){
    free(entity);
    return;
}

/* Übersetzens eines Chars in eine Entity */
Entity* char_to_entity(int x, int y, char sprite){
    switch (sprite){
    case 'S':
        return create_entity(x, y, NORDEN, SPIELER);
        break;

    case 'A':
        return create_entity(x, y, NORDEN, AUSGANG);
        break;

    case '#':
        return create_entity(x, y, NORDEN, WAND);
        break;

    case '^':
        return create_entity(x, y, NORDEN, MONSTER);
        break;

    case '>':
        return create_entity(x, y, OSTEN, MONSTER);
        break;

    case 'v':
        return create_entity(x, y, SUEDEN, MONSTER);
        break;

    case '<':
        return create_entity(x, y, WESTEN, MONSTER);
        break;
    
    default:
        return create_entity(x, y, NORDEN, LEER);
        break;
    }
}
