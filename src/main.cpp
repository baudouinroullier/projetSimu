#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Perso.h"
#include "CarteCollision.h"

using namespace sf;
using namespace std;

const Vector2f TAILLE_FENETRE(800,600);

const int LARGEUR_CANARD=40;
const int HAUTEUR_CANARD=48;
const Vector2f TAILLE_CANARD(LARGEUR_CANARD,HAUTEUR_CANARD);
const int GRAVITE=1;

const Vector2f POSITION_CANARD(TAILLE_FENETRE.x/4*3,TAILLE_FENETRE.y/6);
const Vector2f VITESSE_CANARD(-2,0);

const int DEPLACEMENT=10;
const int FORCE_SAUT=100;



int main()
{
    RenderWindow window(sf::VideoMode(800, 600), "Canard qui rebondit");  // create window
    window.setFramerateLimit(60);
//    CircleShape shape(200.f);
//    CircleShape cercle(100.f);
//    shape.setFillColor(Color::Blue);
//    cercle.setFillColor(Color::Red);

    Image fondEcran;
    Texture texture;
    Sprite spriteBackground;
    Perso canard("../img/pititcanard.jpg", POSITION_CANARD,TAILLE_CANARD, VITESSE_CANARD,GRAVITE);
    CarteCollision noirBlanc(canard, "../img/collision.jpg", TAILLE_FENETRE);

    if (!fondEcran.loadFromFile("../img/Rayman-Origins-4.jpg"))
    {
        cout<<"fond non charge, je repete, fond non charge";
        return EXIT_FAILURE;
    }
        texture.loadFromImage(fondEcran);
        spriteBackground.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed :
                    window.close();
                    break;
                case Event::KeyPressed :
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Left :
                            canard.DeplacerGauche(DEPLACEMENT);
                            break;
                        case Keyboard::Right :
                            canard.DeplacerDroite(DEPLACEMENT);
                            break;
                        case Keyboard::Up :
                            canard.Sauter(-FORCE_SAUT, noirBlanc);
                    }
                }
            }

        }

        window.clear();
        canard.forceGravite();
        noirBlanc.ManageCollisionsX();
        noirBlanc.ManageCollisionsY();

        canard.MoveX();
        canard.MoveY();
        canard.DeplacerDroite(0);
        canard.DeplacerGauche(0);

 //       window.draw(shape);
 //       window.draw(cercle);

 //           image.createMaskFromColor(Color(0,255,1));
        window.draw(spriteBackground);
//           canard.loadFromImage(image);

//            sprite.setTexture(canard);
            //sprite.setColor(Color(255,255,255,128));
//            sprite.move(Vector2f(1,1));
//            sprite.setPosition(150,150);
 //           sprite.setOrigin(11,11);
//            sprite.rotate(1);
//            sprite.scale(0.999,0.999);
        window.draw(canard.GetSprite());

        window.display();
    }

    return 0;
}
