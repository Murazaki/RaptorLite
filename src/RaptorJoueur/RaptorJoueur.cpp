#include "RaptorJoueur.h"
 
using namespace std;
 
RaptorJoueur::RaptorJoueur (sf::Font* Font, int numerojoueur, int nbjoueurs, int nbvies)
{
    this->numJoueur = numerojoueur;
    this->totalVies = nbvies;
    this->Score = 0;
    this->nbVies = totalVies;
    this->dernierTir = 0;
    this->Vaisseau = new RaptorVaisseau(numerojoueur,nbjoueurs);
 
    ostringstream s1;
    s1 << "PLAYER " << numerojoueur;
    PlayerText[0] = new sf::String(s1.str());
    PlayerText[0]->SetFont(*Font);
    PlayerText[0]->SetPosition(5.f,5.f+65.f*(numerojoueur-1));
    PlayerText[0]->SetColor(sf::Color(200,0,250,150));
    PlayerText[0]->SetStyle(sf::String::Bold);
 
    ostringstream s2;
    s2 << "LIFE " << nbVies;
    PlayerText[1] = new sf::String(s2.str());
    PlayerText[1]->SetFont(*Font);
    PlayerText[1]->SetPosition(5.f,20.f+65.f*(numerojoueur-1));
    PlayerText[1]->SetColor(sf::Color(200,0,250,150));
    PlayerText[1]->SetStyle(sf::String::Bold);
 
    ostringstream s3;
    s3 << "SCORE " << Score;
    PlayerText[2] = new sf::String(s3.str());
    PlayerText[2]->SetFont(*Font);
    PlayerText[2]->SetPosition(5.f,35.f+65.f*(numerojoueur-1));
    PlayerText[2]->SetColor(sf::Color(200,0,250,150));
    PlayerText[2]->SetStyle(sf::String::Bold);
}
 
RaptorJoueur::~RaptorJoueur ()
{
    for(int i = 0; i<3; i++)
        delete PlayerText[i];
    delete Vaisseau;
}
 
int RaptorJoueur::getNbVies ()
{
    return nbVies;
}
 
void RaptorJoueur::setNbVies (int nb)
{
    this->nbVies = nb;
    ostringstream s;
    if(nbVies==0)
        s << "GAME OVER";
    else
        s << "LIFE " << nbVies;
    PlayerText[1]->SetText(s.str());
}
 
void RaptorJoueur::resetVies ()
{
    this->nbVies = totalVies;
    ostringstream s;
    s << "LIFE " << nbVies;
    PlayerText[1]->SetText(s.str());
}
 
int RaptorJoueur::getScore ()
{
    return Score;
    ostringstream s;
    s << "SCORE " << Score;
    PlayerText[2]->SetText(s.str());
}
 
void RaptorJoueur::addtoScore (int nb)
{
    this->Score += nb;
    ostringstream s;
    s << "SCORE " << Score;
    PlayerText[2]->SetText(s.str());
}
 
void RaptorJoueur::resetScore ()
{
    this->Score = 0;
    ostringstream s;
    s << "SCORE " << Score;
    PlayerText[2]->SetText(s.str());
}
 
void RaptorJoueur::resetJoueur (int nbJoueurs)
{
    resetVies();
    resetScore();
    Vaisseau->resetPosition(numJoueur,nbJoueurs);
}
 
float RaptorJoueur::getDernierTir()
{
    return dernierTir;
}
 
void RaptorJoueur::setDernierTir(float time)
{
    this->dernierTir = time;
}
 
sf::String** RaptorJoueur::getPlayerText()
{
    return PlayerText;
}
 
RaptorVaisseau* RaptorJoueur::getVaisseau ()
{
    return Vaisseau;
}
 
void RaptorJoueur::joueurMeurt (int nbJoueurs)
{
    if(nbVies>0)
    {
        nbVies--;
        ostringstream s;
        if(nbVies==0)
            s << "GAME OVER";
        else
            s << "LIFE " << nbVies;
        PlayerText[1]->SetText(s.str());
        Vaisseau->resetPosition(numJoueur,nbJoueurs);
    }
}
 
