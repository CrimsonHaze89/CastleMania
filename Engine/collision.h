#pragma once
#include <SFML\Graphics.hpp>

class collision
{
public:
	collision(sf::RectangleShape& body);

	~collision();

	bool CheckCollision(collision& other, float push);
	sf::Vector2f GetPostion() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	
	void Move(float dx, float dy) { body.move(dx, dy); }


private:
	sf::RectangleShape& body;


};