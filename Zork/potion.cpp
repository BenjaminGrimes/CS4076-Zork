#include "potion.h"

Potion::Potion(PotionType t) : Item(t == health_potion ? "Health Potion" : "Magic Potion"), type(t)
{

}

int Potion::getPotionType()
{
    return type;
}
