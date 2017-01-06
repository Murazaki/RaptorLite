#include "RaptorTirAmi.h"
 
RaptorTirAmi::RaptorTirAmi (RaptorJoueur * Joueur, float orientation) : RaptorTir()
{
    this->orientation = orientation;
    this->ImageTirAmi = new sf::Image();
    this->ImageTirAmi->LoadFromFile("media/TirAmi.png");
    this->Joueur = Joueur;
 
    this->TirSprite = new sf::Sprite(*ImageTirAmi);
    this->TirSprite->SetCenter(10, 10);
    this->TirSprite->SetPosition(Joueur->getVaisseau()->getVaisseauSprite()->GetPosition().x, Joueur->getVaisseau()->getVaisseauSprite()->GetPosition().y);
}
 
RaptorTirAmi::~RaptorTirAmi ()
{
    delete ImageTirAmi;
}
 
void RaptorTirAmi::deplacementTir (float ElapsedTime)
{
    this->TirSprite->Move(-500 * sin(orientation) * ElapsedTime, -500 * cos(orientation) * ElapsedTime);
}
 
RaptorJoueur* RaptorTirAmi::getJoueur ()
{
    return Joueur;
}
 
