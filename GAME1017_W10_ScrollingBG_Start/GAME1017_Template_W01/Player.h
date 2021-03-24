#pragma once
#include "GameObject.h"

class Player : public AnimatedSpriteObject
{
private:
	std::string m_key;

	Player(SDL_Rect src, SDL_FRect dst, std::string key) : AnimatedSpriteObject(src, dst) 
	{
		m_frame = 0;	// To be filled with animation values
		m_frameMax = 0;	// Can also be moved into a Player.cpp file if you want
		m_sprite = 0;
		m_spriteMin = 0;
		m_spriteMax = 0;

		m_key = key;
	}

	virtual void Render();

	virtual void Update();

};