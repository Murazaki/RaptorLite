#ifndef RAPTORTIR_H
#define RAPTORTIR_H

#include <SFML/Graphics.hpp>

/// class RaptorTir -
class RaptorTir
{
    // Attributes
protected:
    sf::Sprite* TirSprite;
    // Operations
public:
    RaptorTir ();
    virtual ~RaptorTir ();
    sf::Sprite* getTirSprite ();
    void virtual deplacementTir (float ElapsedTime);
};

#endif

