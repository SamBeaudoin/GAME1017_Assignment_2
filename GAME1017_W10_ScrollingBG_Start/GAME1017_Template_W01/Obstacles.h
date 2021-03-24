#pragma once
#include "GameObject.h"

class Obstacle : public AnimatedSpriteObject
{
private:
	float scrollSpeed, startX, endX;
	std::string m_key;

	Obstacle(SDL_Rect src, SDL_FRect dst, std::string key) : AnimatedSpriteObject(src, dst)
	{
		m_frame = 0;	// To be filled with animation values
		m_frameMax = 0;	// Can also be moved into a Obsatcles.cpp file if you want
		m_sprite = 0;	
		m_spriteMin = 0;
		m_spriteMax = 0;

		m_key = key;
	}

	virtual void Render();

	virtual void Update()
	{
		// Bounds check for end point
		if (GetDst()->x <= endX)
		{
			GetDst()->x = startX;
		}
		//Scroll
		GetDst()->x -= scrollSpeed;
	}
};