#include "GameObjects.h"
#include <iostream>

GameObject::GameObject(std::string texturePath, const sf::Vector2f & pos)
{
	m_texture.loadFromFile(texturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(m_pos));
	m_sprite.setScale(sf::Vector2f(2.0f, 2.0f));
}

GameObject::~GameObject()
{
}

void GameEngine::AddObject(GameObject * obj)
{
	obj->SetEngine(this);
	m_gameObjects.push_back(obj);
}

void GameEngine::Draw(sf::RenderWindow * window)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Draw(window);
	}
}

void GameEngine::Update(float dt)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Update(dt);
	}
}

void GameEngine::SpawnPlayer()
{
	if (m_playerLives > 0)
	{
		m_playerLives--; 
		Hero* elisa = new Hero("Art/elisa-spritesheet1.png", sf::Vector2f(0, 0));
		AddObject(elisa);
	}
}

void GameEngine::SpawnEnemie()
{
	if (true)
	{
		Bat* bat = new Bat("Art/bat.png", sf::Vector2f(0, 0));
		AddObject(bat);

		FloorTile* floor = new FloorTile("Art/floor.png", sf::Vector2f(0, 0));
		AddObject(floor);
	}
}

/////////////////////////////////////////////////////////////////////////

void GameObject::SetEngine(GameEngine * engine)
{
	m_engine = engine;
}

void GameObject::Update(float dt)
{
	m_sprite.move(sf::Vector2f(x * dt, y * dt));
	LimitVelocity(dt);
}

void GameObject::Draw(sf::RenderWindow * window)
{
	window->draw(m_sprite);
}

void GameObject::LimitVelocity(float dt)
{
	float speed = sqrt(m_velocity.x * m_velocity.x + m_velocity.y  * m_velocity.y);

	if (speed <= 0.1)
	{
		return;
	}

	sf::Vector2f normalizedVel = sf::Vector2f(m_velocity.x / speed, m_velocity.y / speed);

	if (speed > 0.00003)
	{
		speed = 0.00003;
	}

	m_velocity.x = normalizedVel.x * speed;
	m_velocity.y = normalizedVel.y * speed;
}

void GameObject::SetAcceleration(float amount)
{
	if (amount > 0)
	{
		m_acceleration = sf::Vector2f(amount, -amount);
	}
	else
	{
		m_acceleration = sf::Vector2f(0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////

Hero::Hero(std::string texturePath, const sf::Vector2f & pos)
	:GameObject(texturePath, pos)
{
	m_sprite.setPosition(sf::Vector2f(50, 150));

	Anim.setColumn(1);
}

Hero::~Hero()
{
}

void Hero::Draw(sf::RenderWindow * window)
{

	GameObject::Draw(window);
}

void Hero::Update(float dt)
{
	GameObject::Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//SetAcceleration();
		velocityX = -2;
		setFacingLeft(true);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocityX = 2;
		setFacingLeft(false);
	}

	else
	{
		x = 0;
		velocityX = 0;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		crouching = true;
	}

	else
	{
		crouching = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		setAttacking(true);
	}

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
	
			velocityY -= 0.008;
			setJumping(true);
	}

	
	velocityY += .003;

/////////////////////////////////////////////////////////////////////////

	if (x == 0 && !crouching && getFacingLeft() == false)
	{
		Anim.ChooseRow(IDLE, dt);
	}

	if (x > 0)
	{
		Anim.ChooseRow(MOVE, dt);
	}

	if (x == 0 && crouching && getFacingLeft() == false)
	{
		Anim.ChooseRow(CROUCH, dt);
	}

	if (velocityY < 0 && getJumping() == true)
	{
		Anim.ChooseRow(JUMP, dt);
	}
	


	if (x == 0 && getFacingLeft() == true)
	{
		Anim.ChooseRow(L_IDLE, dt);
	}

	if (x < 0)
	{
		Anim.ChooseRow(L_MOVE, dt);
	}

	/////////////////////////////////////////////////////////////////////////

	else if (getFacingLeft() == true && getAttacking() == true && x == 0)
	{
		Anim.ChooseRow(L_ATTACK, dt);

		attackTimer += dt;

		if (attackTimer >= 0.30008)
		{
			setAttacking(false);
			attackTimer = 0.0f;
		}
	}

	else if(getAttacking() == true && x == 0)
	{
		Anim.ChooseRow(ATTACK, dt);

		attackTimer += dt;

		if (attackTimer >= 0.30008)
		{
			setAttacking(false);
			attackTimer = 0.0f;
		}
	}
	
	m_sprite.setTextureRect(sf::IntRect(Anim.getColumn(), Anim.getRow(), 64, 64));

	if (m_sprite.getPosition().y <= 523.5)
	{
		m_acceleration.y = gravity;
	}

	else if (m_sprite.getPosition().y >= 523.5)
	{
		m_acceleration.y = 0;
		velocityY = 0;
		m_sprite.setPosition(m_sprite.getPosition().x, 523.5);
		y = 0;
	}

	velocityX += m_acceleration.x;
	velocityY += m_acceleration.y;

	x += velocityX;
	y += velocityY;
}

//void Hero::Destroy()
//{
//}

//////////////////////////////////////////////////////////////////////////////////////////////

Bat::Bat(std::string texturePath, const sf::Vector2f & pos)
	:GameObject(texturePath, pos)
{
	m_sprite.setPosition(sf::Vector2f(10, 250));
}

void Bat::Update(float dt)
{


	accelerationX += 0.1 ;
	m_sprite.move(sf::Vector2f (x,0));
	Anim.setLoopAnimation(0, 4, dt);
	m_sprite.setTextureRect(sf::IntRect(Anim.getColumn(), Anim.getRow(), 64, 64));


	velocityX += accelerationX *dt;
	velocityY += accelerationY;

	x += velocityX;
	y += velocityY;


	//std::cout << velocityY << std::endl;


	//limit velocity
	if (x >= 0.08)
	{	
		x = 0.08;
	}	
	if (velocityX < -0.1)
	{	
		velocityX = -0.5;
	}

	std::cout << x << std::endl;
}

void Bat::Draw(sf::RenderWindow * window)
{
	GameObject::Draw(window);
}

void Bat::Destroy()
{

}




FloorTile::FloorTile(std::string texturePath, const sf::Vector2f & pos)
	:GameObject(texturePath, pos)
{
	m_sprite.setPosition(sf::Vector2f(0, 650));
}
