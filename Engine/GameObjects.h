#pragma once

#include "animManager.h"
#include "collision.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>


class GameObject;

//class Soundcache
//{
//public:
//	sf::SoundBuffer m_buffer;
//	std::string m_fileName;
//};

class GameEngine
{
public:
	void AddObject(GameObject* obj);
	void Draw(sf::RenderWindow* window);
	void Update(float dt);
	void SpawnPlayer();
	void SpawnEnemie();
	void SetCheckPoint(float x, float y) { checkPoint.x = x, checkPoint.y = y; }

private:
	std::vector<GameObject*> m_gameObjects;
	//std::vector<Soundcache> m_soundCache;
	//std::vector<sf::Sound> m_soundPlaying;
	int m_playerLives = 5;



	sf::Vector2f checkPoint = sf::Vector2f(100, 100);
	//sf::Sound m_sound;
	//sf::Music m_gameMusic;
};

class GameObject
{
public:
	GameObject(std::string texturePath, const sf::Vector2f & pos);

	~GameObject();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* window);
	void LimitVelocity(float dt);
	void SetAcceleration(float amount);

	bool getFacingLeft() { return m_facingLeft; }
	bool getAttacking() { return m_isAttacking; }
	bool getJumping() { return m_isJumping; }

	void setFacingLeft(bool val) { m_facingLeft = val; }
	void setAttacking(bool val) { m_isAttacking = val; }
	void setJumping(bool val) { m_isJumping = val; }

	//virtual void Destroy();
	//bool IsDestroyed();

	void SetEngine(GameEngine* engine);

protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float gravity = 0.0010;
	float x = 0;
	float y = 0;
	float velocityX = 0;
	float velocityY = 0;
	float accelerationX = 0;
	float accelerationY = 0;

	bool m_facingLeft = false;
	bool m_isAttacking = false;
	bool m_isJumping = false; 

	GameEngine* m_engine;
	AnimationManager Anim;
};

class Hero : public GameObject
{
public:
	Hero(std::string texturePath, const sf::Vector2f& pos);
	~Hero();

	virtual void Draw(sf::RenderWindow* window);
	virtual void Update(float dt);
	collision GetCollider() { return collision(body); }

	//virtual void Destroy();

protected:
	sf::RectangleShape body;
	float attackTimer = 0;
	bool jumping = false;
	bool crouching = false;	
};

class FloorTile : public GameObject
{
public:
	FloorTile(std::string texturePath, const sf::Vector2f& pos);

protected:

};

class Bat : public GameObject
{
public:
	Bat(std::string texturePath, const sf::Vector2f& pos);
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* window);
	virtual void Destroy();


protected:

};