#include "RaptorNiveau.h"
#include "../RaptorPartie/RaptorPartie.h"
#include <math.h>

using namespace std;

RaptorNiveau::RaptorNiveau (int numeroniveau, RaptorPartie * Partie, std::vector<RaptorEnnemi*> * Ennemis, sf::Font * Font)
{
    this->LevelTime = 0;
    this->numeroniveau = numeroniveau;
    this->Partie = Partie;
    this->Ennemis = Ennemis;
    this->finished = false;

    /*stringstream s;
    s << "NIVEAU " << numeroniveau;
    NiveauText = new sf::String(s.str());
    NiveauText->SetFont(*Font);
    NiveauText->SetPosition(360.f,300.f);
    NiveauText->SetColor(sf::Color(200,0,250,150));
    NiveauText->SetStyle(sf::String::Bold);

    Elements.push_back(NiveauText);

    Partie->pushElements(Elements);*/
}

RaptorNiveau::~RaptorNiveau ()
{
    for(vector<sf::Drawable*>::iterator it=Elements.begin(); it<Elements.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Elements.clear();
    //delete NiveauText;
}

void RaptorNiveau::lancerNiveau (float Time)
{

    std::vector<RaptorTirEnnemi*> TirsEnnemi;
    std::vector<RaptorEnnemi*> TempEnnemis;

    if(LevelTime == 0)
    {
        LevelTime = Time;
        for(int i = 0; i<50; i++)
            Ennemis->push_back(new RaptorEnnemi(1,RaptorPosition2D(-10,300)));
    }

    for(vector<RaptorEnnemi*>::iterator it=Ennemis->begin(); it<Ennemis->end(); it++)
        if(*it!=NULL)
			TempEnnemis.push_back(*it);

    //if(Time-LevelTime>2)
    //Supprimer le titre du niveau


    for(vector<RaptorEnnemi*>::iterator it=TempEnnemis.begin(); it<TempEnnemis.end(); it++)
    {
        if(*it!=NULL)
        {
            (*it)->getEnnemiSprite()->SetPosition(400.f+300.f*cos(Time+(*it)->getId()*0.5),((*it)->getId()-50)*50.f+(Time-LevelTime)*40.f);
            if (((*it)->getDernierTir() == 0) & ((*it)->getPtVie()!=0))
            {
                if(int(float(Time*1.5))%((int)TempEnnemis.size())==(*it)->getId())
                    TirsEnnemi.push_back(new RaptorTirEnnemi(RaptorPosition2D((*it)->getEnnemiSprite()->GetPosition().x, (*it)->getEnnemiSprite()->GetPosition().y)));
                (*it)->setDernierTir(Time);
            }
            else if (((Time-(*it)->getDernierTir())>2) & ((*it)->getPtVie()!=0))
            {
                TirsEnnemi.push_back(new RaptorTirEnnemi(RaptorPosition2D((*it)->getEnnemiSprite()->GetPosition().x, (*it)->getEnnemiSprite()->GetPosition().y)));
                (*it)->setDernierTir(Time);
            }
        }
    }

    Partie->pushTirsEnnemi(TirsEnnemi);

    finished = true;
    for(vector<RaptorEnnemi*>::iterator it=TempEnnemis.begin(); it<TempEnnemis.end(); it++)
    {
        if((*it)!=NULL)
        {
            finished = false;
            break;
        }
    }
}


bool RaptorNiveau::getFinished()
{
    return finished;
}

void RaptorNiveau::reset()
{
    for(vector<sf::Drawable*>::iterator it=Elements.begin(); it<Elements.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Elements.clear();

    this->LevelTime = 0;
    this->finished = false;
}

