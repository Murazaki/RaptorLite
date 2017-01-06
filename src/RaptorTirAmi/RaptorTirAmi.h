#ifndef RAPTORTIRAMI_H
#define RAPTORTIRAMI_H

#include "../RaptorTir/RaptorTir.h"
#include "../RaptorJoueur/RaptorJoueur.h"

/// class RaptorTirAmi -
class RaptorTirAmi : public RaptorTir
{
    // Attributes
private:
    sf::Image * ImageTirAmi;
    RaptorJoueur * Joueur;
    float orientation;
    // Operations
public:
    RaptorTirAmi (RaptorJoueur * Joueur, float orientation = 0);
    ~RaptorTirAmi ();
    void deplacementTir (float ElapsedTime);
    RaptorJoueur* getJoueur ();
};

#endif

