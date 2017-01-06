#include "RaptorTir.h"
 
RaptorTir::RaptorTir ()
{
    this->TirSprite = NULL;
}
 
RaptorTir::~RaptorTir ()
{
    delete TirSprite;
}
 
sf::Sprite* RaptorTir::getTirSprite ()
{
    return TirSprite;
}
 
void RaptorTir::deplacementTir (float ElapsedTime)
{
 
}
 
