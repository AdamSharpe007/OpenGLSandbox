#include "Camera.h"
#include <cmath>
#include <iostream>

void Camera::update()
{
    if (!isLocked) 
        return;

    // Just getting the size of the user's display
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i screenHalfRes {
        static_cast<int>(desktop.width / 2U),
        static_cast<int>(desktop.height / 2U)
    };

    // Get how much the mouse moved since last update and reset back to center
    sf::Vector2i diff = screenHalfRes - sf::Mouse::getPosition();
    sf::Mouse::setPosition(screenHalfRes);

    currentRotation += diff;


    /* Clamping Rotation */
    // Y-Axis rotation (0->360->0->360)
    if (currentRotation.x > 360)
        currentRotation.x = 0;
    if (currentRotation.x < 0)
        currentRotation.x = 360;

    // X-Axis rotation (-60->70)
    currentRotation.y = std::min(70, std::max(currentRotation.y,-60));
   
    glMatrixMode(GL_MODELVIEW); // Switch to editing the "world" transform, rotation, scale
    glLoadIdentity(); // Reset the position, transform and scale of GL_MODELVIEW

    // Order of these is important (for some reason)
    glRotatef(-currentRotation.y, 1, 0, 0); // Rotate everything on X to simulate pitch 
    glRotatef(-currentRotation.x, 0, 1, 0); // Rotate everything on Y to simulate yaw

    // Offset world by player position
    glTranslatef(-currentPosition.x, -1.5f, -currentPosition.y);

    // Get player input
    sf::Vector2f moveInput{0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveInput.y += 0.002f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveInput.x += 0.002f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveInput.y -= 0.002f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveInput.x -= 0.002f;


    /* Rotate input movement to face camera direction */

    const float rotRad = (currentRotation.x) * (3.14159/180);

    const float 
        sinAngle = sin(-rotRad),
        cosAngle = cos(-rotRad);

    currentPosition.x -= cosAngle * moveInput.x - sinAngle * moveInput.y;
    currentPosition.y -= sinAngle * moveInput.x + cosAngle * moveInput.y;
    

    // Lets us unlock the mouse so the game can be closed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        isLocked = !isLocked;
}