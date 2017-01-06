#ifndef RAPTORJOUEUR_H
#define RAPTORJOUEUR_H
 
#define NB_VIES_PAR_DEFAUT 5
 
#include "../RaptorVaisseau/RaptorVaisseau.h"
#include <sstream>
 
/// class RaptorJoueur -
class RaptorJoueur
{
    // Attributes
private:
    int nbVies;
    int totalVies;
    int Score;
    float dernierTir;
    int numJoueur;
    sf::String* PlayerText[3];
    RaptorVaisseau* Vaisseau;
    // Operations
public:
    RaptorJoueur (sf::Font* Font, int numerojoueur, int nbjoueurs, int nbvies = 5);
    ~RaptorJoueur ();
    int getNbVies ();
    void setNbVies (int nb);
    void resetVies ();
    int getScore ();
    void addtoScore (int nb);
    void resetScore ();
    void resetJoueur (int nbJoueurs);
    float getDernierTir();
    void setDernierTir(float time);
    sf::String** getPlayerText();
    RaptorVaisseau* getVaisseau ();
    void joueurMeurt (int nbJoueurs);
};
 
#endif
 
