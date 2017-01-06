#ifndef RAPTORPARTIE_H
#define RAPTORPARTIE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../RaptorNiveau/RaptorNiveau.h"
#include "../RaptorJoueur/RaptorJoueur.h"
#include "../RaptorEnnemi/RaptorEnnemi.h"
#include "../RaptorTirAmi/RaptorTirAmi.h"
#include "../RaptorTirEnnemi/RaptorTirEnnemi.h"
#include <iostream>
#include <vector>

/// class RaptorPartie -
class RaptorPartie
{
    // Attributes
private:
    sf::RenderWindow * App;
    float ElapsedTime;
    float Time;
    float TimeWithPause;
    float menuLatence;
    bool gameLaunched;
    bool gamePaused;
    bool gameOver;
    sf::Music* AcidJazz;
    int nbJoueurs;
    std::vector<RaptorJoueur*> Joueurs;
    std::vector<RaptorEnnemi*> Ennemis;
    std::vector<RaptorTirAmi*> TirsAmi;
    std::vector<RaptorTirEnnemi*> TirsEnnemi;
    std::vector<RaptorNiveau*>::iterator NiveauCourant;
    std::vector<RaptorNiveau*> Niveaux;
    std::vector<sf::Drawable*> Elements;
    sf::Sprite* TitleSprite;
    sf::Sprite* Fond1[2];
    sf::Sprite* Fond2[2];
    sf::Font* Font;
    sf::String* PauseText;
    sf::String* GameOverText;
    sf::String* PlayerText;
    sf::String* InfoText;
    std::vector<sf::String*> CreditText;
    void manageEvents ();
    void manageDisplay ();
    void manageCollisions ();
    bool areColliding (const sf::Sprite& s1, const sf::Sprite& s2, const int AlphaMax = -1);
    // Operations
public:
    RaptorPartie ();
    virtual ~RaptorPartie ();
    void lancerPartie ();
    void quitterPartie ();
    void pushEnnemis (std::vector<RaptorEnnemi*> newEnnemis);
    void pushTirsEnnemi (std::vector<RaptorTirEnnemi*> newTirEnnemi);
    void pushElements (std::vector<sf::Drawable*> Elements);
};

#endif

