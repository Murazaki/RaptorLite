#include "RaptorEnnemi.h"
#include <SFML/Graphics.hpp>

int RaptorEnnemi::idmax = 0;

RaptorEnnemi::RaptorEnnemi (int typeennemi, RaptorPosition2D position)
{
    this->id=idmax;
    idmax++;

    if(typeennemi<3)
        this->nbPtVie = 1;
    else if(typeennemi>6)
        this->nbPtVie = 5;
    else if(typeennemi>8)
        this->nbPtVie = 100;

    this->dernierTir = 0;

    // Load the sprite image from a file
    this->EnnemiImage = new sf::Image();
    EnnemiImage->LoadFromFile((std::string)("media/Ennemi1.png"));


    // Create the sprite
    EnnemiSprite = new sf::Sprite(*EnnemiImage);
    EnnemiSprite->SetCenter(30, 15);
    EnnemiSprite->SetColor(sf::Color(255, 0, 0, 255));
    EnnemiSprite->SetPosition(position.getX(), position.getY());
}

RaptorEnnemi::~RaptorEnnemi ()
{
    delete EnnemiSprite;
    delete EnnemiImage;
}

sf::Sprite* RaptorEnnemi::getEnnemiSprite ()
{
    return EnnemiSprite;
}

void RaptorEnnemi::ennemiTouche ()
{
    EnnemiSprite->SetColor(sf::Color(255, 255, 0, 255));
    if(this->nbPtVie>0)
        this->nbPtVie--;
}

void RaptorEnnemi::ennemiMeurt ()
{
    EnnemiSprite->SetColor(sf::Color(255, 255, 0, 255));
}

int RaptorEnnemi::getPtVie()
{
    return nbPtVie;
}

float RaptorEnnemi::getDernierTir()
{
    return dernierTir;
}

int RaptorEnnemi::getId()
{
    return id;
}

void RaptorEnnemi::resetIdmax()
{
	idmax = 0;
}

void RaptorEnnemi::setDernierTir(float time)
{
    this->dernierTir = time;
}


