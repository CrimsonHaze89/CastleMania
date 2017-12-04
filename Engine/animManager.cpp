#include "animManager.h"
#include <iostream>

AnimationManager::AnimationManager()
{
	m_currrentAnim = AnimationType::IDLE;
	//setColumn(m_col);
	//setRow(m_row);
	//setHeight(m_height);
	//setWidth(m_width);
	m_col = 0;
	m_row = 0;
	m_height = 64;
	m_width = 64;
	animationTimer = 0.0f;
}

AnimationManager::~AnimationManager()
{}

int AnimationManager::ChooseRow(AnimationType type, float dt)
{
	switch (type)
	{
	case AnimationType::IDLE:
	{
		AnimationManager::setLoopAnimation(0, 5, dt);
		break;
	}

	case AnimationType::L_IDLE:
	{
		AnimationManager::setLoopAnimation(5, 4, dt);
		break;
	}

	case AnimationType::ATTACK:
	{
		AnimationManager::setLoopAnimation(4, 5, dt);
		break;
	}

	case AnimationType::L_ATTACK:
	{
		AnimationManager::setLoopAnimation(8, 5, dt);
		break;
	}
	
	case AnimationType::CROUCH:
	{
		AnimationManager::setLoopAnimation(1, 1, dt);
		break;
	}

	case AnimationType::MOVE:
	{
		AnimationManager::setLoopAnimation(3, 7, dt);
		break;
	}

	case AnimationType::L_MOVE:
	{
		AnimationManager::setLoopAnimation(7 , 7, dt);
		break;
	}

	case AnimationType::JUMP:
	{
		AnimationManager::setLoopAnimation(2, 4, dt);
		break;
	}


	//case AnimationType::DEAD:
	//{
	//	return m_row = 12;
	//	break;
	//}

	}
	return 0;
}

void AnimationManager::setLoopAnimation( int row, int numOfFrames, float dt)
{
	animationTimer += dt;

	if (animationTimer >= 0.2f)
	{
		m_col += 64;

		if (m_col >= (m_width * numOfFrames) - 64)
		{
			m_col = 0;
		}
		animationTimer = 0.0f;
	}

	setRow(64 * row);
}

void AnimationManager::setPlayAnimation(int row, int frameEnd, float dt)
{
	animationTimer += dt;
	
	if (animationTimer > 0.2f)
	{
		m_col += 64;
		if (m_col >= 64 * frameEnd)
		{
			m_col = 0;
		}
		animationTimer = 0.0f;
	}
	setRow(64 * row);
}