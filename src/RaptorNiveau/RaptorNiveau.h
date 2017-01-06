#ifndef RAPTORNIVEAU_H
#define RAPTORNIVEAU_H

#include "../RaptorEnnemi/RaptorEnnemi.h"
#include "../RaptorTirEnnemi/RaptorTirEnnemi.h"
#include <vector>

class RaptorPartie;

/// class RaptorNiveau -
class RaptorNiveau
{
    // Attributes
private:
    float LevelTime;
    int numeroniveau;
    std::vector<RaptorEnnemi*> * Ennemis;
    std::vector<sf::Drawable*> Elements;
    RaptorPartie * Partie;
    sf::String* NiveauText;
    bool finished;
    // Operations
public:
    RaptorNiveau(int numeroniveau, RaptorPartie * Partie, std::vector<RaptorEnnemi*> * Ennemis, sf::Font * Font);
    ~RaptorNiveau();
    void lancerNiveau (float Time);
    bool getFinished();
    void reset();
};

#endif

