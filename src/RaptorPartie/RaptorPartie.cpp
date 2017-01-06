#include "RaptorPartie.h"
#include <sstream>
#include <math.h>

using namespace std;

RaptorPartie::RaptorPartie()
{
    this->nbJoueurs = 1;

    this->gameLaunched = false;
    this->gamePaused = false;
    this->gameOver = false;

    this->App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Raptor Game", sf::Style::Close);

    this->Time = 0;
    this->TimeWithPause = 0;
    this->menuLatence = 0;

    this->Niveaux.clear();

    this->AcidJazz = new sf::Music();

    this->AcidJazz->OpenFromFile("media/AcidJazz.ogg");
    this->AcidJazz->SetLoop(true);

    Font = new sf::Font();
    Font->LoadFromFile("media/visitor2.ttf");

    // Load the sprite image from a file
    sf::Image* Espace = new sf::Image();
    Espace->LoadFromFile("media/Espace.png");

    // Create the sprite
    for(int i=0; i<2; i++)
    {
        Fond1[i] = new sf::Sprite(*Espace);
        Fond1[i]->SetColor(sf::Color(255, 255, 255, 255));
        Fond1[i]->SetCenter(400, 300);
        Fond1[i]->SetScale(1.0f, 1.0f);
        Fond1[i]->SetPosition(400.f, (-300.f+(600.f)*i));

        Fond2[i] = new sf::Sprite(*Espace);
        Fond2[i]->FlipX(true);
        Fond2[i]->FlipY(true);
        Fond2[i]->SetColor(sf::Color(225, 225, 255, 200));
        Fond2[i]->SetCenter(400, 300);
        Fond2[i]->SetScale(1.0f, 1.0f);
        Fond2[i]->SetPosition(400.f, (-300.f+(600.f)*i));
    }

    // Load the sprite image from a file
    sf::Image* Title = new sf::Image();
    Title->LoadFromFile("media/raptortitle.png");

    // Create the sprite
    TitleSprite = new sf::Sprite(*Title);
    TitleSprite->SetColor(sf::Color(155, 155, 255, 150));
    TitleSprite->SetCenter(300, 200);
    TitleSprite->SetPosition(400.f, 200.f);

    PauseText = new sf::String("PAUSE");
    PauseText->SetFont(*Font);
    PauseText->SetPosition(365.f,300.f);
    PauseText->SetColor(sf::Color(200,0,250,150));
    PauseText->SetStyle(sf::String::Bold);

    GameOverText = new sf::String("GAME OVER");
    GameOverText->SetFont(*Font);
    GameOverText->SetPosition(360.f,300.f);
    GameOverText->SetColor(sf::Color(200,0,250,150));
    GameOverText->SetStyle(sf::String::Bold);

    ostringstream s;
    if(nbJoueurs==1)
        s << nbJoueurs << " Player";
    else
        s << nbJoueurs << " Players";
    PlayerText = new sf::String(s.str());
    PlayerText->SetFont(*Font);
    PlayerText->SetPosition(335.f,300.f);
    PlayerText->SetColor(sf::Color(200,150,255,150));
    PlayerText->SetStyle(sf::String::Bold);

    InfoText = new sf::String("Press Enter to Start");
    InfoText->SetFont(*Font);
    InfoText->SetPosition(265.f,350.f);
    InfoText->SetColor(sf::Color(200,150,255,150));
    InfoText->SetStyle(sf::String::Bold);

    std::string text = "Created by BENADEL Mehdi - Bonne Retraite M. Leclerc !";
    sf::String * Text;
    stringstream s1[text.size()];
    for(unsigned int i =0; i<text.size(); i++)
    {
        s1[i] << text[i];
        Text = new sf::String(s1[i].str());
        Text->SetFont(*Font);
        Text->SetPosition(-100,-100);
        Text->SetColor(sf::Color(200,150,255,150));
        Text->SetStyle(sf::String::Bold);
        CreditText.push_back(Text);
    }
}

RaptorPartie::~RaptorPartie()
{
    delete App;
    AcidJazz->Stop();
    delete AcidJazz;
    for(vector<RaptorJoueur*>::iterator it=Joueurs.begin(); it<Joueurs.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Joueurs.clear();
    for(vector<RaptorEnnemi*>::iterator it=Ennemis.begin(); it<Ennemis.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Ennemis.clear();
    for(vector<RaptorTirEnnemi*>::iterator it=TirsEnnemi.begin(); it<TirsEnnemi.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    TirsEnnemi.clear();
    for(vector<RaptorTirAmi*>::iterator it=TirsAmi.begin(); it<TirsAmi.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    TirsAmi.clear();
    for(vector<RaptorNiveau*>::iterator it=Niveaux.begin(); it<Niveaux.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Niveaux.clear();
    delete TitleSprite;
    for(int i=0; i<2; i++)
    {
        delete Fond1[i];
        delete Fond2[i];
    }
    delete Font;
    delete PauseText;
    delete GameOverText;
    delete PlayerText;
    delete InfoText;
    for(vector<sf::String*>::iterator it=CreditText.begin(); it<CreditText.end(); it++)
    {
        if((*it)!=NULL)
            delete *it;
    }
    CreditText.clear();
}

void RaptorPartie::lancerPartie()
{
    // Start game loop
    while (App->IsOpened())
    {
        // Stocke le temps écoulé
        ElapsedTime = App->GetFrameTime();
        if(!gamePaused)
            Time += ElapsedTime;
        TimeWithPause += ElapsedTime;

        manageEvents();

        manageDisplay();

		if(!gameOver)
			manageCollisions();
    };
}

void RaptorPartie::quitterPartie ()
{
    gameLaunched = false;
    gamePaused = false;
    gameOver = false;
    AcidJazz->Stop();
    for(vector<RaptorJoueur*>::iterator it=Joueurs.begin(); it<Joueurs.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Joueurs.clear();
    for(vector<RaptorEnnemi*>::iterator it=Ennemis.begin(); it<Ennemis.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    Ennemis.clear();
    RaptorEnnemi::resetIdmax();
    for(vector<RaptorTirEnnemi*>::iterator it=TirsEnnemi.begin(); it<TirsEnnemi.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    TirsEnnemi.clear();
    for(vector<RaptorTirAmi*>::iterator it=TirsAmi.begin(); it<TirsAmi.end(); it++)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
    TirsAmi.clear();
    for(vector<RaptorNiveau*>::iterator it=Niveaux.begin(); it<Niveaux.end(); it++)
    {
        delete *it;
        *it=NULL;
    }
    Niveaux.clear();
}

void RaptorPartie::manageEvents ()
{
    // Process events
    sf::Event Event;
    while (App->GetEvent(Event))
    {
        // Quitte le programme
        if (Event.Type == sf::Event::Closed)
            App->Close();
    }

    // Quitte le programme
    if (App->GetInput().IsKeyDown(sf::Key::Escape))
        App->Close();

    if (App->GetInput().IsKeyDown(sf::Key::X) & (TimeWithPause-menuLatence>0.5))
    {
        quitterPartie();
        menuLatence = TimeWithPause;
    }

    if(!gameLaunched)
    {
        if ((App->GetInput().IsKeyDown(sf::Key::Left)) & (nbJoueurs>1) & (TimeWithPause-menuLatence>0.5))
        {
            nbJoueurs--;
            ostringstream s;
            if(nbJoueurs==1)
                s << nbJoueurs << " Player";
            else
                s << nbJoueurs << " Players";
            PlayerText->SetText(s.str());
            menuLatence = TimeWithPause;
        }
        if ((App->GetInput().IsKeyDown(sf::Key::Right)) & (nbJoueurs<4) & (TimeWithPause-menuLatence>0.5))
        {
            nbJoueurs++;
            ostringstream s;
            s << nbJoueurs << " Players";
            PlayerText->SetText(s.str());
            menuLatence = TimeWithPause;
        }
        if (App->GetInput().IsKeyDown(sf::Key::Return) & (TimeWithPause-menuLatence>0.5))
        {
            gameLaunched = true;
            menuLatence = TimeWithPause;

            Niveaux.push_back(new RaptorNiveau(1,this,&Ennemis,Font));
            NiveauCourant = Niveaux.begin();

            for(int i=0; i<nbJoueurs; i++)
                Joueurs.push_back(new RaptorJoueur(Font,i+1,nbJoueurs));
        }
    }
    else if(gameOver)
    {
        if ((App->GetInput().IsKeyDown(sf::Key::X) | App->GetInput().IsKeyDown(sf::Key::Return) ) & (TimeWithPause-menuLatence>0.5))
        {
            quitterPartie();
            menuLatence = TimeWithPause;
        }
    }
    else if(gamePaused)
    {
        if (App->GetInput().IsKeyDown(sf::Key::P) & (TimeWithPause-menuLatence>0.5))
        {
            gamePaused = false;
            menuLatence = TimeWithPause;
        }
    }
    else
    {
        if (App->GetInput().IsKeyDown(sf::Key::P) & (TimeWithPause-menuLatence>0.5))
        {
            gamePaused = true;
            menuLatence = TimeWithPause;
        }

        if(Joueurs[0]->getNbVies()!=0)
        {
            // Bouge l'objet
            if (App->GetInput().IsKeyDown(sf::Key::Left) & (Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetPosition().x-Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetCenter().x > 0))
            {
                Joueurs[0]->getVaisseau()->getVaisseauSprite()->Move(-300 * ElapsedTime, 0);
            }

            if (App->GetInput().IsKeyDown(sf::Key::Right) & (Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetPosition().x+Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetCenter().x < 800))
            {
                Joueurs[0]->getVaisseau()->getVaisseauSprite()->Move( 300 * ElapsedTime, 0);
            }

            if (App->GetInput().IsKeyDown(sf::Key::Up) & (Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetPosition().y-Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetCenter().y > 0))
            {
                Joueurs[0]->getVaisseau()->getVaisseauSprite()->Move(0, -300 * ElapsedTime);
                for(int i=0; i<2; i++)
                {
                    Fond1[i]->Move(0,  150 * ElapsedTime);
                    Fond2[i]->Move(0,  50 * ElapsedTime);
                }
            }

            if (App->GetInput().IsKeyDown(sf::Key::Down) & (Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetPosition().y+Joueurs[0]->getVaisseau()->getVaisseauSprite()->GetCenter().y < 600))
            {
                Joueurs[0]->getVaisseau()->getVaisseauSprite()->Move(0,  300 * ElapsedTime);
                for(int i=0; i<2; i++)
                {
                    Fond1[i]->Move(0,  -50 * ElapsedTime);
                    Fond2[i]->Move(0,  -20 * ElapsedTime);
                }
            }

            if (App->GetInput().IsKeyDown(sf::Key::RControl) & ((Time-Joueurs[0]->getDernierTir())>0.3))
            {
                TirsAmi.push_back(new RaptorTirAmi(Joueurs[0]));
                Joueurs[0]->setDernierTir(Time);
            }
        }

        if(nbJoueurs>1)
        {
            if(Joueurs[1]->getNbVies()!=0)
            {
                // Bouge l'objet
                if (App->GetInput().IsKeyDown(sf::Key::Q) & (Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetPosition().x-Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetCenter().x > 0))
                {
                    Joueurs[1]->getVaisseau()->getVaisseauSprite()->Move(-300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::D) & (Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetPosition().x+Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetCenter().x < 800))
                {
                    Joueurs[1]->getVaisseau()->getVaisseauSprite()->Move( 300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::Z) & (Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetPosition().y-Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetCenter().y > 0))
                {
                    Joueurs[1]->getVaisseau()->getVaisseauSprite()->Move(0, -300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  150 * ElapsedTime);
                        Fond2[i]->Move(0,  50 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::S) & (Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetPosition().y+Joueurs[1]->getVaisseau()->getVaisseauSprite()->GetCenter().y < 600))
                {
                    Joueurs[1]->getVaisseau()->getVaisseauSprite()->Move(0,  300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  -50 * ElapsedTime);
                        Fond2[i]->Move(0,  -20 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::LControl) & ((Time-Joueurs[1]->getDernierTir())>0.3))
                {
                    TirsAmi.push_back(new RaptorTirAmi(Joueurs[1]));
                    Joueurs[1]->setDernierTir(Time);
                }
            }
        }

        if(nbJoueurs>2)
        {
            if(Joueurs[2]->getNbVies()!=0)
            {
                // Bouge l'objet
                if (App->GetInput().IsKeyDown(sf::Key::F) & (Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetPosition().x-Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetCenter().x > 0))
                {
                    Joueurs[2]->getVaisseau()->getVaisseauSprite()->Move(-300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::H) & (Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetPosition().x+Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetCenter().x < 800))
                {
                    Joueurs[2]->getVaisseau()->getVaisseauSprite()->Move( 300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::T) & (Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetPosition().y-Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetCenter().y > 0))
                {
                    Joueurs[2]->getVaisseau()->getVaisseauSprite()->Move(0, -300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  150 * ElapsedTime);
                        Fond2[i]->Move(0,  50 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::G) & (Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetPosition().y+Joueurs[2]->getVaisseau()->getVaisseauSprite()->GetCenter().y < 600))
                {
                    Joueurs[2]->getVaisseau()->getVaisseauSprite()->Move(0,  300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  -50 * ElapsedTime);
                        Fond2[i]->Move(0,  -20 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::V) & ((Time-Joueurs[2]->getDernierTir())>0.3))
                {
                    TirsAmi.push_back(new RaptorTirAmi(Joueurs[2]));
                    Joueurs[2]->setDernierTir(Time);
                }
            }
        }

        if(nbJoueurs>3)
        {
            if(Joueurs[3]->getNbVies()!=0)
            {
                // Bouge l'objet
                if (App->GetInput().IsKeyDown(sf::Key::J) & (Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetPosition().x-Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetCenter().x > 0))
                {
                    Joueurs[3]->getVaisseau()->getVaisseauSprite()->Move(-300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::L) & (Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetPosition().x+Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetCenter().x < 800))
                {
                    Joueurs[3]->getVaisseau()->getVaisseauSprite()->Move( 300 * ElapsedTime, 0);
                }

                if (App->GetInput().IsKeyDown(sf::Key::I) & (Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetPosition().y-Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetCenter().y > 0))
                {
                    Joueurs[3]->getVaisseau()->getVaisseauSprite()->Move(0, -300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  150 * ElapsedTime);
                        Fond2[i]->Move(0,  50 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::K) & (Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetPosition().y+Joueurs[3]->getVaisseau()->getVaisseauSprite()->GetCenter().y < 600))
                {
                    Joueurs[3]->getVaisseau()->getVaisseauSprite()->Move(0,  300 * ElapsedTime);
                    for(int i=0; i<2; i++)
                    {
                        Fond1[i]->Move(0,  -50 * ElapsedTime);
                        Fond2[i]->Move(0,  -20 * ElapsedTime);
                    }
                }

                if (App->GetInput().IsKeyDown(sf::Key::Comma) & ((Time-Joueurs[3]->getDernierTir())>0.3))
                {
                    TirsAmi.push_back(new RaptorTirAmi(Joueurs[3]));
                    Joueurs[3]->setDernierTir(Time);
                }
            }
        }
    }
}

void RaptorPartie::manageDisplay ()
{
    // Efface l'écran
    App->Clear(sf::Color(30,0,30,255));

    if(gamePaused)
    {
        AcidJazz->Pause();
        App->Draw(*PauseText);
    }

    if(!gamePaused)
    {
        for(int i=0; i<2; i++)
        {
            Fond1[i]->Move(0,  500 * ElapsedTime);
            if(Fond1[i]->GetPosition().y>=900)
                Fond1[i]->SetY(-300);

            Fond2[i]->Move(0,  200 * ElapsedTime);
            if(Fond2[i]->GetPosition().y>=900)
                Fond2[i]->SetY(-300);
        }
    }

    // Affiche les objets
    for(int i=0; i<2; i++)
    {
        App->Draw(*(Fond2[i]));// Décor 2
        App->Draw(*(Fond1[i]));// Décor 1
    }

    if(!gameLaunched)
    {
        App->Draw(*TitleSprite);
        App->Draw(*PlayerText);
        App->Draw(*InfoText);
        int i = 0;
        for(vector<sf::String*>::iterator it=CreditText.begin(); it<CreditText.end(); it++)
        {
            (*it)->SetPosition(-10+((int)(+15.f*i+Time*100))%820,450.f+25*cos(Time*2+i*0.23));
            App->Draw(**it);
            i++;
        }
    }
    else if(gameOver)
	{
        App->Draw(*GameOverText);
        if(AcidJazz->GetStatus()!=sf::Music::Stopped)
			AcidJazz->Stop();
	}
    else
    {
        if(!((*NiveauCourant)->getFinished()))
            (*NiveauCourant)->lancerNiveau(Time);
        else
        {
        	NiveauCourant++;
            if(NiveauCourant==Niveaux.end())
				gameOver = true;
        }

        if(!gamePaused)
        {

            for(vector<RaptorEnnemi*>::iterator it=Ennemis.begin(); it!=Ennemis.end(); it++)
            {
                if(((*it)->getEnnemiSprite()->GetPosition().y+(*it)->getEnnemiSprite()->GetCenter().y)>610)
                {
                    delete *it;
                    *it=NULL;
                    Ennemis.erase(it);
                    it--;
                }
            }

            for(vector<RaptorTirAmi*>::iterator it=TirsAmi.begin(); it<TirsAmi.end(); it++)
            {
                (*it)->deplacementTir(ElapsedTime);
                if((((*it)->getTirSprite()->GetPosition().y-(*it)->getTirSprite()->GetCenter().y)<-10) || (((*it)->getTirSprite()->GetPosition().y+(*it)->getTirSprite()->GetCenter().y)>610) || (((*it)->getTirSprite()->GetPosition().x-(*it)->getTirSprite()->GetCenter().x)<-10) || (((*it)->getTirSprite()->GetPosition().x+(*it)->getTirSprite()->GetCenter().x)>810))
                {
                    delete *it;
                    *it=NULL;
                    TirsAmi.erase(it);
                    it--;
                }
            }

            for(vector<RaptorTirEnnemi*>::iterator it=TirsEnnemi.begin(); it<TirsEnnemi.end(); it++)
            {
                (*it)->deplacementTir(ElapsedTime);
                if((((*it)->getTirSprite()->GetPosition().y-(*it)->getTirSprite()->GetCenter().y)<-10) || (((*it)->getTirSprite()->GetPosition().y+(*it)->getTirSprite()->GetCenter().y)>610) || (((*it)->getTirSprite()->GetPosition().x-(*it)->getTirSprite()->GetCenter().x)<-10) || (((*it)->getTirSprite()->GetPosition().x+(*it)->getTirSprite()->GetCenter().x)>810))
                {
                    delete *it;
                    *it=NULL;
                    TirsEnnemi.erase(it);
                    it--;
                }
            }

            for(vector<RaptorJoueur*>::iterator it=Joueurs.begin(); it!=Joueurs.end(); it++)
                (*it)->getVaisseau()->getVaisseauSprite()->Move(0,  (525-(*it)->getVaisseau()->getVaisseauSprite()->GetPosition().y-(*it)->getVaisseau()->getVaisseauSprite()->GetCenter().y) * ElapsedTime/2);

            if((AcidJazz->GetStatus()!=sf::Music::Playing) & (!gameOver))
                AcidJazz->Play();
        }

        for(vector<RaptorTirAmi*>::iterator it=TirsAmi.begin(); it!=TirsAmi.end(); it++)
            App->Draw(*((*it)->getTirSprite())); // Tirs Ami
        for(vector<RaptorTirEnnemi*>::iterator it=TirsEnnemi.begin(); it!=TirsEnnemi.end(); it++)
            App->Draw(*((*it)->getTirSprite())); // Tirs Ennemi
        for(vector<RaptorJoueur*>::iterator it=Joueurs.begin(); it!=Joueurs.end(); it++)
        {
            if((*it)->getNbVies()!=0)
                App->Draw(*((*it)->getVaisseau()->getVaisseauSprite()));	// Vaisseaux Joueurs
            App->Draw(*((*it)->getPlayerText()[0]));
            App->Draw(*((*it)->getPlayerText()[1]));
            App->Draw(*((*it)->getPlayerText()[2]));
        }
        for(vector<RaptorEnnemi*>::iterator it=Ennemis.begin(); it!=Ennemis.end(); it++)
            App->Draw(*((*it)->getEnnemiSprite()));	// Ennemis
        for(vector<sf::Drawable*>::iterator it=Elements.begin(); it!=Elements.end(); it++)
            App->Draw(**it); // Elements tiers
    }

    // Affiche le contenu de la fenêtre
    App->Display();
}

void RaptorPartie::manageCollisions ()
{
    if(gameLaunched & !gameOver)
    {
        for(vector<RaptorJoueur*>::iterator jit=Joueurs.begin(); jit<Joueurs.end(); jit++)
        {
            for(vector<RaptorTirEnnemi*>::iterator teit=TirsEnnemi.begin(); teit<TirsEnnemi.end(); teit++)
            {
                if((*jit!=NULL) && (*teit!=NULL) && (areColliding((*(*jit)->getVaisseau()->getVaisseauSprite()),(*(*teit)->getTirSprite()),1)))
                {
                    (*jit)->joueurMeurt(nbJoueurs);
                    delete *teit;
                    *teit=NULL;
                    TirsEnnemi.erase(teit);
                    teit--;
                }
            }
            for(vector<RaptorEnnemi*>::iterator eit=Ennemis.begin(); eit<Ennemis.end(); eit++)
            {
                if((*jit!=NULL) && (*eit!=NULL) && (areColliding((*(*jit)->getVaisseau()->getVaisseauSprite()),(*(*eit)->getEnnemiSprite()),1)))
                {
                    (*jit)->joueurMeurt(nbJoueurs);
                    (*eit)->ennemiTouche();
                    if((*eit)->getPtVie()==0)
                    {
                        (*eit)->ennemiMeurt();
                        delete *eit;
                        *eit=NULL;
                        Ennemis.erase(eit);
                        eit--;
                    }
                    (*jit)->addtoScore(5);
                }
            }
        }

        for(vector<RaptorEnnemi*>::iterator eit=Ennemis.begin(); eit<Ennemis.end(); eit++)
        {
            for(vector<RaptorTirAmi*>::iterator tait=TirsAmi.begin(); tait<TirsAmi.end(); tait++)
            {
                if(tait<TirsAmi.begin())
                    tait=TirsAmi.begin();
                if(eit<Ennemis.begin())
                    eit=Ennemis.begin();
                if((*eit!=NULL) && (*tait!=NULL) && (areColliding((*(*eit)->getEnnemiSprite()),(*(*tait)->getTirSprite()),1)))
                {
                    (*tait)->getJoueur()->addtoScore(100);
                    delete *tait;
                    *tait=NULL;
                    TirsAmi.erase(tait);
                    tait--;
                    (*eit)->ennemiTouche();
                    if((*eit)->getPtVie()==0)
                    {
                        (*eit)->ennemiMeurt();
                        delete *eit;
                        *eit=NULL;
                        Ennemis.erase(eit);
                        eit--;
                    }
                }
            }
        }

        gameOver = true;

        for(vector<RaptorJoueur*>::iterator jit=Joueurs.begin(); jit<Joueurs.end(); jit++)
        {
            if(((*jit)->getNbVies())!=0)
            {
                gameOver = false;
                break;
            }
        }
    }
}

bool RaptorPartie::areColliding (const sf::Sprite& s1, const sf::Sprite& s2, const int AlphaMax)
{
    // Définition deux objets représentant les dimensions de s1 et s2.
    // Si les Sprites ont été tournés, les calculs ne fonctionneront pas!
    sf::Vector2f pos = s1.GetPosition() - s1.GetCenter();
    const sf::FloatRect r1(pos.x, pos.y, pos.x + s1.GetSize().x, pos.y + s1.GetSize().y);
    pos = s2.GetPosition() - s2.GetCenter();
    const sf::FloatRect r2(pos.x, pos.y, pos.x + s2.GetSize().x, pos.y + s2.GetSize().y);

    // Espace de collision potentiel.
    sf::FloatRect zone;

    // Testons si les Sprites se superposent.
    if (r1.Intersects(r2, &zone))
    {
        if (AlphaMax >= 0)
        {
            int left1 = static_cast<int>(zone.Left - r1.Left);
            int top1 = static_cast<int>(zone.Top - r1.Top);

            int left2 = static_cast<int>(zone.Left - r2.Left);
            int top2 = static_cast<int>(zone.Top - r2.Top);

            int width = static_cast<int>(zone.GetWidth());
            int height = static_cast<int>(zone.GetHeight());

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (s1.GetPixel(x+left1, y+top1).a > AlphaMax && s2.GetPixel(x+left2, y+top2).a > AlphaMax)
                        return true;
                }
            }

            return false;
        }

        return true;
    }

    return false;
}

void RaptorPartie::pushEnnemis (std::vector<RaptorEnnemi*> newEnnemis)
{
    for(vector<RaptorEnnemi*>::iterator it=newEnnemis.begin(); it<newEnnemis.end(); it++)
        Ennemis.push_back(*it);
}

void RaptorPartie::pushTirsEnnemi (std::vector<RaptorTirEnnemi*> newTirsEnnemi)
{
    for(vector<RaptorTirEnnemi*>::iterator it=newTirsEnnemi.begin(); it<newTirsEnnemi.end(); it++)
        TirsEnnemi.push_back(*it);

}

void RaptorPartie::pushElements (std::vector<sf::Drawable*> newElements)
{
    for(vector<sf::Drawable*>::iterator it=newElements.begin(); it<newElements.end(); it++)
        Elements.push_back(*it);
}

