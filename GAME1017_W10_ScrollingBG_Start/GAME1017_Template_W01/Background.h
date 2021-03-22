#pragma once
#include "GameObject.h"

// Because SpriteObject is abstract
class Background : public SpriteObject
{
private:
	float scrollSpeed, startX, endX;
	std::string m_key;
public:
	Background(const SDL_Rect s, const SDL_FRect d, float ss, std::string key)
		:SpriteObject(s, d), scrollSpeed(ss)
	{
		startX = d.x;
		endX = d.x - d.w;
		m_key = key;
	}
	void Update()
	{
		// Bounds check for end point
		if (GetDst()->x <= endX)
		{
			GetDst()->x = startX;
		}
		//Scroll
		GetDst()->x -= scrollSpeed;
	}
	void Render();

};

