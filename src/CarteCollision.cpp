#include <iostream>
#include "CarteCollision.h"

using namespace std;
using namespace sf;

//bool Collision(const IntRect & a, const IntRect & b)
//{
//    if (a.top+a.height <= b.top)
//        return false;
//    if (a.top >= b.top+b.height)
//        return false;
//    if (a.left+a.width <= b.left)
//        return false;
//    if (a.left >= b.left+b.width)
//        return false;
//
//    return true;
//}

CarteCollision::CarteCollision(Perso & perso,const std::string & filePath,  Vector2f windowSize)
: m_Perso(perso), m_WindowSize(windowSize)
{
    if(!m_Carte.loadFromFile(filePath)) // Si le chargement a échoué
    {
        cerr<<"Error during import "<<filePath<<endl; // On affiche l'erreur
    }

}

void CarteCollision::ManageCollisionsX()
{
    // Récupération de la boîte englobante de la balle
    IntRect persoRect = m_Perso.GetBoundingBox();


    // Test des Collisions en X
    if(persoRect.left < 0 || persoRect.left+persoRect.width> m_WindowSize.x || m_Carte.getPixel(persoRect.left,(persoRect.top+persoRect.height/2))==Color::Black||m_Carte.getPixel(persoRect.left+persoRect.width,(persoRect.top+persoRect.height/2))==Color::Black)
    {
        // On stoppe le mouvement du perso si obstacle devant lui
        m_Perso.ReverseDX();
        m_Perso.MoveX();
        m_Perso.DeplacerDroite(0);
        m_Perso.ReverseDX();
    }
    if(m_Carte.getPixel(persoRect.left,(persoRect.top+persoRect.height/2))==Color::Blue||m_Carte.getPixel(persoRect.left+persoRect.width,(persoRect.top+persoRect.height/2))==Color::Blue)
    {
        // Pour accrocher le perso aux rebords
        //m_Perso.ReverseDX();
        m_Perso.ReverseDX();
        m_Perso.MoveX();
        m_Perso.DeplacerDroite(0);
        m_Perso.ReverseDX();
        m_Perso.SetDY(0);
    }
}

void CarteCollision::ManageCollisionsY()
{
    // Récupération de la boîte englobante de la balle
    IntRect persoRect = m_Perso.GetBoundingBox();

    // Test des Collisions en Y
    if(persoRect.top < 0 || persoRect.top+persoRect.height > m_WindowSize.y || m_Carte.getPixel(persoRect.left+persoRect.width/2,persoRect.top)==Color::Black||m_Carte.getPixel(persoRect.left+persoRect.width/2,persoRect.top+persoRect.height)==Color::Black)
    {
        // On annule le mouvement de la balle et on lui inverse son mouvement en Y
        m_Perso.ReverseDY();
        m_Perso.MoveY();
        m_Perso.SetDY(0);
    }
}
bool CarteCollision::isOnFloor() const
{
    // Récupération de la boîte englobante du perso
    IntRect persoRect = m_Perso.GetBoundingBox();
    return(m_Carte.getPixel(persoRect.left+persoRect.width/2 ,persoRect.top+persoRect.height)==Color::Black);
}



