#pragma once
#include <SFML/Graphics.hpp>
#include <array>


const std::array<sf::Vector3i,8> cubeVertices
{{
    {1, 1, 1},      // 0
    {1, 1, -1},     // 1
    {-1, 1, 1},     // 2
    {-1, 1, -1},    // 3
    {1, -1, 1},     // 4
    {1, -1, -1},    // 5
    {-1, -1, 1},    // 6
    {-1, -1, -1}    // 7
}};

// Vertices stored C-CW
const std::array<std::array<int,4>,6> cubeFaces
{{
    {1,5,7,3}, // FRONT
    {2,6,4,0}, // BACK
    {2,0,1,3}, // TOP
    {7,6,4,5}, // BOTTOM
    {1,0,4,5}, // LEFT
    {3,7,6,2}  // RIGHT
}};

/*
// Vertices stored CW
const std::array<std::array<int,4>,6> cubeFaces
{{
    {1,3,7,5}, // FRONT
    {2,0,4,6}, // BACK
    {2,3,1,0}, // TOP
    {5,4,6,7}, // BOTTOM
    {4,0,1,5}, // LEFT
    {3,2,6,7}  // RIGHT
}};
*/