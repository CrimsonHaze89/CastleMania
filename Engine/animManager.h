#pragma once

enum AnimationType
{
	IDLE,
	L_IDLE,
	ATTACK,
	L_ATTACK,
	ITEM,
	MOVE,
	L_MOVE,
	CROUCH,
	JUMP,
	//DEAD
};

class AnimationManager
{
public:
	AnimationManager();

	~AnimationManager();

	int getColumn() { return m_col; }
	int getRow() { return m_row; }
	int getHeight() { return m_height; }
	int getWidth() { return m_width; }

	int ChooseRow(AnimationType type, float dt);

	void setColumn(int val) { m_col = val; }
	void setRow(int val) { m_row = val; }
	void setHeight(int val) { m_height = val; }
	void setWidth(int val) { m_width = val; }
	void setLoopAnimation(int row, int numOfFrames, float dt);
	void setPlayAnimation(int row, int frameEnd, float dt);
	
private:
	AnimationType m_currrentAnim;
	int m_col;
	int m_row;
	int m_height;
	int m_width;
	float animationTimer;
};