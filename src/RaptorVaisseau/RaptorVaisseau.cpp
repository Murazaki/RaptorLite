#include "RaptorVaisseau.h"
 
RaptorVaisseau::RaptorVaisseau (int numerojoueur, int nbjoueurs)
{
    // Load the sprite image from a file
    sf::Image * VaisseauImage = new sf::Image();
    VaisseauImage->LoadFromFile("media/Vaisseau.png");
 
 
    // Create the sprite
    VaisseauSprite = new sf::Sprite(*VaisseauImage);
    VaisseauSprite->SetCenter(30, 15);
    VaisseauSprite->SetColor(sf::Color(0, 150+ 105*((float)numerojoueur/(float)nbjoueurs), 255-105*((float)numerojoueur/(float)nbjoueurs), 255));
 
    resetPosition(numerojoueur, nbjoueurs);
}
 
RaptorVaisseau::~RaptorVaisseau ()
{
    delete VaisseauSprite;
}
 
sf::Sprite* RaptorVaisseau::getVaisseauSprite ()
{
    return VaisseauSprite;
}
 
void RaptorVaisseau::resetPosition (int numerojoueur, int nbjoueurs)
{
    VaisseauSprite->SetPosition(200.f + ((400.f*numerojoueur)/(nbjoueurs+1)), 500.f);
}
 
 
