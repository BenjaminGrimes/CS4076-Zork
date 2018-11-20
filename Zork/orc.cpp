#include "orc.h"

orc::orc() : race(){
     setAtt();
}
void orc::setAtt(){
    type = "Orc";
    setMagicLevel(20);
    setMagicDamage(5);
}
