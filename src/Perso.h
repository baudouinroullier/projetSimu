#ifndef PERSO_H
#define PERSO_H

#include <SFML/Graphics.hpp>
#include "CarteCollision.h"

class CarteCollision;

class Perso
{
public :

    Perso(const std::string & filePath, sf::Vector2f position, sf::Vector2f taille, sf::Vector2f speed, int gravite);

    void MoveX();
    void MoveY();
    void DeplacerGauche(int dx);
    void DeplacerDroite(int dx);
    void Sauter(int forceSaut, const CarteCollision & carte);
    void ReverseDX(); // Inverse le mouvement en X
    void ReverseDY(); // Inverse le mouvement en Y
    bool isOnAir(const CarteCollision & carte) const;
    void forceGravite();

    void SetDY(int dy);
    sf::Sprite GetSprite();
    sf::IntRect GetBoundingBox() const; // Retourne la boîte englobante de l'image du perso

private :

    sf::Image m_Image;
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;

    sf::Vector2f m_taille; // Taille
    int m_DX; // Déplacement en X
    int m_DY; // Déplacement en Y
    sf::Vector2f m_Speed; // Vitesse
    int m_gravite;
    int m_sens_image; //Garde en mémoire dans quelle direction regarde le perso: 0 gauche 1 droite
};

#endif
