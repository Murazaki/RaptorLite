#ifndef RAPTORVAISSEAU_H
#define RAPTORVAISSEAU_H
 
#include "../RaptorPosition2D/RaptorPosition2D.h"
#include <SFML/Graphics.hpp>
 
/// class RaptorVaisseau -
class RaptorVaisseau
{
    // Attributes
private:
    sf::Sprite* VaisseauSprite;
    // Operations
public:
    RaptorVaisseau (int numerojoueur, int nbjoueurs);
    ~RaptorVaisseau ();
    sf::Sprite* getVaisseauSprite ();
    void resetPosition (int numerojoueur, int nbjoueurs);
};
 
#endif
 
