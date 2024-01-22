#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	sf::Vector3f vertexToColor(sf::Vector3f vertex, float range);
	float randomRangef(float min, float max);

	GLuint index;
	sf::Clock clock;
	int elapsed;
	Camera camera{};

	float rotationAngle = 0.0f;
};