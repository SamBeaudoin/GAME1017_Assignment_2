#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
#define JUMPFORCE 40.0
#define GRAV 4.0
using namespace std;

//class Sprite
//{
//protected:
//	SDL_Rect m_src; // Source rectangle.
//	SDL_Rect m_dst; // Destination rectangle.
//	int m_angle = 0;
//public:
//	void SetRects(SDL_Rect s, SDL_Rect d)
//	{
//		m_src = s;
//		m_dst = d;
//	}
//	SDL_Rect* GetSrc()
//	{
//		return &m_src;
//	}
//	SDL_Rect* GetDst()
//	{
//		return &m_dst;
//	}
//};

class Sprite // Represents visual component of Box.
{
protected:
	SDL_Rect m_src;
	SDL_Rect m_dst; // Position on screen.
	SDL_Color m_color; // Random color for box.
	SDL_Texture* m_pTexture;
public:
	Sprite();
	Sprite(const SDL_Rect r, const SDL_Color c);
	void Render();
	friend class Box; // Or make a setter for m_dst.
	void SetRects(SDL_Rect s, SDL_Rect d)
	{
		m_src = s;
		m_dst = d;
	}
	SDL_Rect* GetSrc()
	{
		return &m_src;
	}
	SDL_Rect* GetDst()
	{
		return &m_dst;
	}
	void setTexture(SDL_Texture* t)
	{
		m_pTexture = t;
	}
};

class Box // Obstacle parent/proxy for the Sprite.
{
private:
	SDL_Point m_pos; // Position on screen. Y is optional.
	Sprite* m_pSprite; // Pointer to dynamic array of Sprites.
	int m_numSprites;
public:
	Box(const SDL_Point p, bool hasSprite = false, int numSprites = 0,
		const SDL_Rect r = { 0,0,0,0 }, const SDL_Color c = { 255,255,255,255 });
	~Box();
	Box* Clone();
	void Update();
	void Render();
	const SDL_Point GetPos() { return m_pos; }
	void AddSprite(const int index, const SDL_Rect r, const SDL_Color c);
	void AddSprite(const int index, const Sprite& s);
};

class Player : public Sprite
{
private:

	bool m_grounded = false;
	bool m_isRolling = false;

	double m_accelX = 0.0,
		m_accelY = 0.0,
		m_velX = 0.0,
		m_maxVelX = 10.0,
		m_velY = 0.0,
		m_maxVelY = JUMPFORCE,
		m_drag = 0.88,
		m_grav = GRAV;

public:

	void SetAccelX(double a) { m_accelX = a; }
	void SetAccelY(double a) { m_accelY = a; }	

	bool IsGrounded() { return m_grounded; }				   
	void SetGrounded(bool g) { m_grounded = g; }	

	bool IsRolling() { return m_isRolling; }
	void SetRolling(bool g) { m_isRolling = g; }

	double GetVelX() { return m_velX; }						   
	double GetVelY() { return m_velY; }		

	void SetX(float y) { m_dst.x = y; }						   
	void SetY(float y) { m_dst.y = y; }	

	void StopY() { m_velY = 0.0; }

	void Update()
	{
		// Do X axis first.
		m_velX += m_accelX;
		m_velX *= (m_grounded ? m_drag : 1);
		m_velX = std::min(std::max(m_velX, -(m_maxVelX)), (m_maxVelX));
		m_dst.x += (int)m_velX; 
		// Now do Y axis.
		m_velY += m_accelY + m_grav;
		m_velY = std::min(std::max(m_velY, -(m_maxVelY)), (m_grav * 5));
		m_dst.y += (int)m_velY; 
		m_accelX = m_accelY = 0.0;
	}
};



class Engine
{
private: // private properties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

private: // private method prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	void Update();
	void Render();
	void Sleep();

public: // public method prototypes.
	int Run();

	// Singleton
	static Engine& Instance();
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	bool KeyDown(SDL_Scancode c);
};

#endif

// Reminder: you can ONLY have declarations in headers, not logical code
