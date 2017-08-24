#pragma once
#include "GameObjects.h"

class collision
{
public:
	collision();

	~collision();

	bool Colliding();

	void Draw();
	void Update();
	void Destroy();

protected:
	int bottomLeft;


};