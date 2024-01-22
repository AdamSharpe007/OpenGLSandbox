#include "Game.h"
#include "CubeDef.h"
#include <cmath>


Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube", 7U, sf::ContextSettings(24))
{
	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning){
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST); // To avoid geometry rendering over itself
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, window.getSize().x / window.getSize().y, 1.0, 500.0);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		// Data located in include/CubeDef.h
		for (auto face : cubeFaces)
		{
			for (auto vertIndex : face)
			{
				sf::Vector3i vertex = cubeVertices[vertIndex];
				sf::Vector3f color = vertexToColor(static_cast<sf::Vector3f>(vertex), 1);
				glColor3f(color.x, color.y, color.z);
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
		
		glColor3f(0.6,0.6,0.6);
		glVertex3f(-50, -2.5, -50);
		glVertex3f(-50, -2.5, 50);
		glVertex3f(50, -2.5, 50);
		glVertex3f(50, -2.5, -50);
	}
	glEnd();
	glBegin(GL_POINTS);
	{
		// Pretty stars
		// Just generates a bunch of randomly positioned points
		const float RANGE = 15;
		for (int i = 0; i < 300; i++)
		{
			sf::Vector3f pointPos {
				randomRangef(-RANGE, RANGE),
				randomRangef(-RANGE, RANGE),
				randomRangef(-RANGE, RANGE)
			};
			sf::Vector3f pointCol = vertexToColor(pointPos, RANGE);
			glColor3f(pointCol.x+0.5, pointCol.y+0.5, pointCol.z+0.5);
			glVertex3f(pointPos.x, pointPos.y, pointPos.z);
		}
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		// Hexagon is bestagon
		const int SIDES = 6;
		const float PORTION = 360.0f / SIDES;
		const float SIZE = 2.5f;
		for (int i = 0; i < 8; i++)
		{
			float angle = PORTION * i;
			angle *= 3.14159f / 180.0f; // to rad
			sf::Vector3f linePointPos {
				std::cos(angle) * SIZE,
				0,
				std::sin(angle) * SIZE,
			};
			sf::Vector3f linePointCol = vertexToColor(linePointPos, SIZE);
			glColor3f(linePointCol.x,linePointCol.y,linePointCol.z);
			glVertex3f(linePointPos.x, linePointPos.y, linePointPos.z);
		}
	}
	glEnd();
	glEndList();
	
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,-5);
}

void Game::update()
{
	elapsed = clock.getElapsedTime().asSeconds();

	// Only run on even seconds
	if (elapsed % 2 == 0)
	{
		rotationAngle += 0.010f;

		if (rotationAngle > 360.0f)
			rotationAngle = 0;
	}

	camera.update();
	
}

void Game::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCallList(1);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up\n";
}

sf::Vector3f Game::vertexToColor(sf::Vector3f vertex, float range)
{
	sf::Vector3f convertedColor;
	// Vertex in range -range to range, convert to 0-1
	convertedColor.x = (vertex.x + range) / (range*2);
	convertedColor.y = (vertex.y + range) / (range*2);
	convertedColor.z = (vertex.z + range) / (range*2);
	return convertedColor;
}

float Game::randomRangef(float min, float max)
{
	return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}