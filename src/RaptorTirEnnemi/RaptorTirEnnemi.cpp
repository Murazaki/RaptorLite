#include "RaptorTirEnnemi.h"
#include <math.h>
 
RaptorTirEnnemi::RaptorTirEnnemi (RaptorPosition2D positionDepart, float orientation) : RaptorTir()
{
    this->orientation = orientation;
    this->ImageTirEnnemi = new sf::Image();
    this->ImageTirEnnemi->LoadFromFile("media/TirEnnemi.png");
 
    this->TirSprite = new sf::Sprite(*ImageTirEnnemi);
    this->TirSprite->SetCenter(10, 10);
    this->TirSprite->SetPosition(positionDepart.getX(),positionDepart.getY());
}
 
RaptorTirEnnemi::~RaptorTirEnnemi ()
{
    delete ImageTirEnnemi;
}
 
void RaptorTirEnnemi::deplacementTir (float ElapsedTime)
{
    this->TirSprite->Move(500 * sin(orientation) * ElapsedTime, 500 * cos(orientation) * ElapsedTime);
}
 
