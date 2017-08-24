#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "animManager.h"
#include "GameObjects.h"

bool fullscreen = true;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Working Title!");
	GameEngine Engine;

	Engine.SpawnPlayer();
	Engine.SpawnEnemie();

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return &&
					event.key.alt)
				{
					window.close();
					fullscreen = !fullscreen;
					window.create(fullscreen ? sf::VideoMode(1920, 1080) : sf::VideoMode(1280, 720), "Game Title TBA!", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar);
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		Engine.Update(dt.asSeconds());
		Engine.Draw(&window);

		window.display();
	}

	return 0;
}
