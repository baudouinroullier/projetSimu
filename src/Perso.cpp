#include <iostream>
#include "Perso.h"

using namespace std;
using namespace sf;

Perso::Perso(const string &filePath, Vector2f position, Vector2f taille, Vector2f speed, int gravite)
: m_taille(taille), m_DX(speed.x), m_DY(speed.y), m_Speed(speed), m_gravite(gravite)
{
    if(!m_Image.loadFromFile(filePath)) // Si le chargement a échoué
    {
        cerr<<"Error during import "<<filePath<<endl; // On affiche l'erreur
    }
    else // Si le chargement de l'image a réussi
    {

        m_Image.createMaskFromColor(Color(0,255,1));
        m_Texture.loadFromImage(m_Image);
        m_Sprite.setTexture(m_Texture);
        m_Sprite.setPosition(position);
        m_sens_image=0;
    }
}

void Perso::MoveX()
{
    m_Sprite.move(m_DX, 0);
}

void Perso::MoveY()
{
    m_Sprite.move(0, m_DY);
}

void Perso::DeplacerDroite(int dx)
{
    if (m_sens_image==0 && dx!=0)
    {
        this->ReverseDX();
        m_sens_image=1;
    }
    m_DX=dx;
}

void Perso::DeplacerGauche(int dx)
{
    if (m_sens_image==1 && dx!=0)
    {
        this->ReverseDX();
        m_sens_image=0;
    }
    m_DX=-dx;
}

void Perso::SetDY(int dy){
    m_DY=dy;
}

void Perso::Sauter(int forceSaut,const CarteCollision & carte){
    if (!this->isOnAir(carte))
    {
        m_DY-= forceSaut;
    }
}

void Perso::ReverseDX()
{
    m_DX *= -1; // Inversement du mouvement en X
    m_Image.flipHorizontally();
    m_Texture.loadFromImage(m_Image);
    m_Sprite.setTexture(m_Texture);
}

void Perso::ReverseDY()
{
    m_DY *= -1; // Inversement du mouvement en Y
}

bool Perso::isOnAir(const CarteCollision & carte) const
{
    bool retour= !carte.isOnFloor();
    return(retour);
}

void Perso::forceGravite()
{
    m_DY += m_gravite;
}

Sprite Perso::GetSprite()
{
    return m_Sprite;
}

IntRect Perso::GetBoundingBox() const
{
    IntRect boundingBox;
    boundingBox.left = (int)m_Sprite.getPosition().x;
    boundingBox.width = m_taille.x;
    boundingBox.top = (int)m_Sprite.getPosition().y;
    boundingBox.height = m_taille.y;

    return boundingBox;
}
