#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

class Camera 
{
public:
    void update();

private:
    bool isLocked = true;
    sf::Vector2i currentRotation{0,0};
    sf::Vector2f currentPosition{0,0};
};