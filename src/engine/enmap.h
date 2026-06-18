#ifndef ENEMYGEN_H
#define ENEMYGEN_H

typedef struct {
    const char *name;
    bool isBoss;
    int difficulty;
} EnemyTemplate;

static const EnemyTemplate enemyTemplates[] = {
    {"Zombi", false, 1},
    {"Esqueleto", false, 1},
    {"Slime", false, 1},
    {"Demonio", false, 1},
    {"Súcubo", false, 1},
    {"Goblin", false, 1},
    {"Bandolero", true, 1},
    {"Aberración Cósmica", true, 1},
    {"Gólem Antiguo", true, 1},
    {"Jefe de carrera", true, 1}
};

#endif