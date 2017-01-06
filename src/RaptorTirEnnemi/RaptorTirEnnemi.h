#ifndef RAPTORTIRENNEMI_H
#define RAPTORTIRENNEMI_H
 
#include "../RaptorTir/RaptorTir.h"
#include "../RaptorPosition2D/RaptorPosition2D.h"
#include "../RaptorEnnemi/RaptorEnnemi.h"
 
/// class RaptorTirEnnemi -
class RaptorTirEnnemi : public RaptorTir
{
    // Attributes
private:
    sf::Image * ImageTirEnnemi;
    float orientation;
    // Operations
public:
    RaptorTirEnnemi (RaptorPosition2D positionDepart, float orientation = 0);
    virtual ~RaptorTirEnnemi ();
    void deplacementTir (float ElapsedTime);
};
 
#endif
 
