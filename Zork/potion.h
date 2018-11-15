#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item
{
public:
    enum PotionType {health_potion, magic_potion};

    Potion(PotionType t);

    PotionType getPotionType();

private:
    PotionType type;
};

#endif // POTION_H
