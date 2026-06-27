#include "objmap.h"
#include "game.h"

static const ObjectTemplate objectTemplates[] = {
    {"Poción pequeña",     true,  false, SLOT_NONE},
    {"Poción mediana",     true,  false, SLOT_NONE},
    {"Poción grande",      true,  false, SLOT_NONE},
    {"Espada ligera",      false, true,  SLOT_WEAPON},
    {"Espada pesada",      false, true,  SLOT_WEAPON},
    {"Ultra espadón",      false, true,  SLOT_WEAPON},
    {"Armadura ligera",    false, true,  SLOT_ARMOR},
    {"Armadura pesada",    false, true,  SLOT_ARMOR},
    {"Armadura berserker", false, true,  SLOT_ARMOR},  // armadura aunque tenga ataque
    {"Rollo de historia",  false, false, SLOT_NONE}
};

/* +++
Pergaminos de historia que sueltan los jefes. Cada uno cuenta un fragmento
del lore del Rey Amarillo. El texto se guarda en el campo lore del GameObject
(MAX_LORE_LENGTH = 256), así que cada fragmento cabe holgado.
--- */

static const char *storyScrolls[][2] = {
    {"Pergamino I",
     "Antano este lugar no era mazmorra. Magia y tecnologia convivian en sintonia, y las razas colaboraban por un futuro comun. Nadie imaginaba lo que se gestaba en las sombras."},
    {"Pergamino II",
     "Un humano sin nombre comenzo a oir una voz. El ente jamas se mostro, solo susurraba. Al preguntarle su nombre, callo un instante y dijo: \"tu especie suele llamarme El Rey Amarillo\"."},
    {"Pergamino III",
     "Tras aquella charla, el humano enloquecio lentamente. Sus iguales le parecian un estorbo. El conocimiento ajeno lo corrompia mientras se alzaba por encima de los demas."},
    {"Pergamino IV",
     "Se volvio gobernante de la ciudad cuyo nombre se perdio, y tomo uno nuevo, impronunciable: #$%Tur. Reino con un saber que ningun hombre deberia poseer."},
    {"Pergamino V",
     "Abrio un portal para hallar recursos en otras dimensiones. No previo que se abria hacia ambos lados. Al activarse, algo cruzo desde el otro lado."},
    {"Pergamino VI",
     "Cruzo algo que la mente mortal no puede contener. No tenia forma, sino todas a la vez; sus miembros doblaban angulos que la logica prohibe. Mirarlo era desentender la razon. Solo quedo el amarillo de su capa, y luego, la locura."},
    {"Pergamino VII",
     "El heroe crecio lejos, oyendo de sus padres las maravillas de aquel sitio. Un dia volvio a casa: ambos muertos. Con su sangre, en el muro: \"El Rey Amarillo volvio\"."},
    {"Pergamino VIII",
     "Movido por la venganza, el heredero de los antiguos desciende a la mazmorra. Busca la verdad de la tragedia y un modo de detener el mal que aun acecha en lo profundo."}
};

void handleGameObject(GameObject *currentObject) {
    if(!currentObject) return;
    switch(currentObject->equip) {

        case ITEM_CONSUMABLE:
            generateStatsConsumable(currentObject);
            break;
        case ITEM_EQUIPPABLE:
            generateStatsEquipabble(currentObject);
            break;
        case ITEM_KEY:
            generateStatsKey(currentObject);
            break;
        default:
            break;
    }
}

GameObject* generateObject(const char *name)
{
    GameObject *object = (GameObject*) malloc(sizeof(GameObject));
    if(!object) return NULL;

    object->x = -1;
    object->y = -1;
    object->stats.attack = -1;
    object->stats.currentHp = -1;
    object->stats.defense = -1;
    object->stats.maxHp = -1;
    object->stats.speed = -1;
    object->lore[0] = '\0';
    object->equipSlot = SLOT_NONE;   // por defecto: no equipable, se sobreescribe si corresponde
    strncpy(object->name, name, MAX_OBJECT_NAME - 1);
    object->name[MAX_OBJECT_NAME - 1] = '\0';

    return object;
}

GameObject *chooseRandomObject(void) {
    int count = sizeof(objectTemplates) / sizeof(objectTemplates[0]);
    int randomIndex = rand() % count;
    const ObjectTemplate *tpl = &objectTemplates[randomIndex];

    GameObject *object = generateObject((char *)tpl->name);
    if(!object) return NULL;

    if(tpl->isConsumable) {
        object->equip = ITEM_CONSUMABLE;
        generateStatsConsumable(object);
    }
    else if(tpl->isEquippable) {
        object->equip = ITEM_EQUIPPABLE;
        object->equipSlot = tpl->slot;   // <-- slot explícito desde el template
        generateStatsEquipabble(object);
    }
    else {
        object->equip = ITEM_KEY;
        generateStatsKey(object); // <-- antes llamaba a generateStatsEquipabble por error
    }

    return object;
}

void generateStatsConsumable(GameObject* object)
{
    if(strcmp(object->name, "Poción pequeña") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 20;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
    else if(strcmp(object->name, "Poción mediana") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 50;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
    else if(strcmp(object->name, "Poción grande") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 80;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
}

void generateStatsEquipabble(GameObject* object)
{
    if(strcmp(object->name, "Espada ligera") == 0) {
        object->stats.attack = 3;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 4;
    }
    else if(strcmp(object->name, "Espada pesada") == 0) {
        object->stats.attack = 5;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 0;
    }
    else if(strcmp(object->name, "Ultra espadón") == 0) { // <-- antes era "if", rompía la cadena else-if
        object->stats.attack = 7;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = -2;
    }
    else if(strcmp(object->name, "Armadura ligera") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 5;
        object->stats.maxHp = 10;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 2;
    }
    else if(strcmp(object->name, "Armadura pesada") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 7;
        object->stats.maxHp = 14;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = -2;
    }
    else if(strcmp(object->name, "Armadura berserker") == 0) {
        object->stats.attack = 12;
        object->stats.defense = 1;
        object->stats.maxHp = 30;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
}

void generateStatsKey(GameObject* object)
{
    if(strcmp(object->name, "Rollo de historia") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 0;
    }
}

Map *createObjectsMap(void) {
    Map *map = mapCreate();
    if(!map) return NULL;
    int count = sizeof(objectTemplates) / sizeof(objectTemplates[0]);

    for(int i=0; i < count; ++i) {
        const ObjectTemplate *tpl = &objectTemplates[i];

        GameObject *object = generateObject(tpl->name);
        if(!object) continue;

        if(tpl->isEquippable) object->equipSlot = tpl->slot;

        if(tpl->isConsumable) generateStatsConsumable(object);
        else if(tpl->isEquippable) generateStatsEquipabble(object);
        else generateStatsKey(object);

        mapInsert(map, object->name, object);
    }
    return map;
}

GameObject *chooseRandomPotion(void) {
    int potionIndex = rand() % 3; // Las 3 primeras posiciones del arreglo son las pociones
    const ObjectTemplate *tpl = &objectTemplates[potionIndex];

    GameObject *object = generateObject((char *)tpl->name);
    if(!object) return NULL;

    object->equip = ITEM_CONSUMABLE;
    generateStatsConsumable(object);

    return object;
}

/* +++
Devuelve un pergamino de historia al azar (drop de jefe). Es un objeto tipo
ITEM_KEY: no tiene stats de combate, su valor está en el lore que carga.
--- */
GameObject *chooseRandomScroll(void) {
    int count = sizeof(storyScrolls) / sizeof(storyScrolls[0]);
    int randomIndex = rand() % count;

    GameObject *object = generateObject(storyScrolls[randomIndex][0]);
    if(!object) return NULL;

    object->equip = ITEM_KEY;
    object->stats.attack = 0;
    object->stats.defense = 0;
    object->stats.maxHp = 0;
    object->stats.currentHp = 0;
    object->stats.speed = 0;

    strncpy(object->lore, storyScrolls[randomIndex][1], MAX_LORE_LENGTH - 1);
    object->lore[MAX_LORE_LENGTH - 1] = '\0';

    return object;
}