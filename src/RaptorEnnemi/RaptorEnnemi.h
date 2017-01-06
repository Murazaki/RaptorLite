#ifndef RAPTORENNEMI_H
#define RAPTORENNEMI_H

#include "../RaptorPosition2D/RaptorPosition2D.h"
#include <SFML/Graphics.hpp>

/// class RaptorEnnemi -
class RaptorEnnemi
{
    // Attributes
private:
    static int idmax;
    int id;
    int nbPtVie;
    float dernierTir;
    sf::Image* EnnemiImage;
    sf::Sprite* EnnemiSprite;
    // Operations
public:
    RaptorEnnemi (int typeennemi, RaptorPosition2D position);
    ~RaptorEnnemi ();
    sf::Sprite* getEnnemiSprite ();
    void ennemiTouche();
    void ennemiMeurt();
    int getPtVie();
    float getDernierTir();
    int getId();
    static void resetIdmax();
    void setDernierTir(float time);
};

#endif


