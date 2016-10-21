#ifndef CarteCollision_H
#define CarteCollision_H

#include <SFML/Graphics.hpp>

#include "Perso.h"

class Perso;

class CarteCollision
{
public :

    CarteCollision(Perso & perso, const std::string & filePath, const sf::Vector2f windowSize);

    void ManageCollisionsX();
    void ManageCollisionsY();
    bool isOnFloor() const;

private :

    Perso & m_Perso;

    sf::Image m_Carte;
    sf::Vector2f m_WindowSize; // Taille de la fenêtre
};

bool Collision(const sf::IntRect & a, const sf::IntRect & b); // Collisions entre deux rectangles

#endif
