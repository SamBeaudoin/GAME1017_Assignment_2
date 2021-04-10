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
using namespace std;

class Sprite
{
protected:
	SDL_Rect m_src; // Source rectangle.
	SDL_Rect m_dst; // Destination rectangle.
	int m_angle = 0;
public:
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
};

class Marvins : public Sprite	// Using Enemy class as base
{
private:
	//SDL_Rect m_rect;	// for destination
public:
	Marvins(SDL_Rect spawnLoc)	// non-default
	{
		cout << "Constructing Marvin at..." << &(*this) << endl;
		this->m_dst.x = spawnLoc.x;	//this-> is optional
		this->m_dst.y = spawnLoc.y;
		this->m_dst.w = 100;
		this->m_dst.h = 100;
		m_src = { 0,0,100,100 };
	}
	~Marvins()
	{
		cout << "De-allocating Marvin at " << &(*this) << endl;
	}
	void Update()
	{
		m_angle++;
		this->m_dst.x -= 2.5;	// Speed O' Marvin going <- that way
	}
	void SetLoc(SDL_Point loc)
	{
		m_dst.x = loc.x;
		m_dst.y = loc.y;

	}
	void Render(SDL_Renderer* rend, SDL_Texture* tex)
	{
		SDL_RenderCopyEx(rend, tex, &m_src, &m_dst, m_angle , NULL, SDL_FLIP_HORIZONTAL);
	}
};

class Enemy : public Sprite
{
private:
	int m_frame = 0,		// frame counter
		m_frameMax = 20,	// Number of frames to display each sprite
		m_sprite = 0,		// Which sprites of the animation to display
		m_spriteMax = 2;	// Number of sprites in the animation
public:

	void Animate()
	{
		//Long way
		//if (m_frame == m_frameMax) // Or m_frame++ and eliminate the m_frame++; line
		//{
		//	m_frame = 0;
		//	m_sprite++;
		//	if (m_sprite == m_spriteMax)	// Or ++m_sprite == m_spriteMax
		//		m_sprite = 0;	// Or set to m_spriteMin if row has multiple animations
		//	m_src.x = m_src.w * m_sprite;
		//}
		//m_frame++;

		//Short way

		if (m_frame++ % m_frameMax == 0)
		{
			m_src.x = (m_src.w + 90 ) * (m_sprite++ % (m_spriteMax)); // 128 * 0 is our sprite counter % max sprites 0,1,2,3,4,5,6,7 repeat
		}
	}
	Enemy(SDL_Rect spawnLoc )	// non-default
	{
		cout << "Constructing Enemy at..." << &(*this) << endl;
		this->m_dst.x = spawnLoc.x;	//this-> is optional
		this->m_dst.y = spawnLoc.y;
		this->m_dst.w = 200;
		this->m_dst.h = 250;
		this->m_src = { 0,0,400,728 };
	}
	~Enemy()
	{
		cout << "De-allocating Enemy at " << &(*this) << endl;
	}
	void Update()
	{
		this->m_dst.x -= 3.5;	// Speed O' Enemy going <- that way
	}
	void SetLoc(SDL_Point loc)
	{
		m_dst.x = loc.x;
		m_dst.y = loc.y;
	}
	void Render(SDL_Renderer* rend, SDL_Texture* tex)
	{
		SDL_RenderCopyEx(rend, tex, &m_src, &m_dst, 0.0, NULL, SDL_FLIP_NONE);
	}
};


class eBullet : public Sprite
{
private:
	//SDL_Rect m_rect;	// for destination
public:
	eBullet(SDL_Rect spawnLoc = { 512 , 384 })	// non-default
	{
		cout << "Constructing Bullet at..." << &(*this) << endl;
		this->m_dst.x = spawnLoc.x;	//this-> is optional
		this->m_dst.y = spawnLoc.y;
		this->m_dst.w = 80;
		this->m_dst.h = 20;
		m_src = { 0,0,125,75 };
	}
	~eBullet()
	{
		cout << "De-allocating enemy Bullet at " << &(*this) << endl;
	}
	void Update()
	{
		this->m_dst.x -= 9.5;	// Speed O' Bullet going <- that way
	}
	void SetLoc(SDL_Point loc)
	{
		m_dst.x = loc.x;
		m_dst.y = loc.y;

	}
	void Render(SDL_Renderer* rend, SDL_Texture* tex)
	{
		SDL_RenderCopyEx(rend, tex, &m_src, &m_dst, 0.0, NULL, SDL_FLIP_NONE);

	}
};



class Bullet : public Sprite
{
private:
	//SDL_Rect m_rect;	// for destination
public:
	Bullet(SDL_Rect spawnLoc = {512 , 384})	// non-default
	{
		cout << "Constructing Bullet at..." << &(*this) << endl;
		this->m_dst.x = spawnLoc.x;	//this-> is optional
		this->m_dst.y = spawnLoc.y;
		this->m_dst.w = 20;
		this->m_dst.h = 40;
		m_src = { 0,0,75,88 };
	}
	~Bullet()
	{
		cout << "De-allocating Bullet at " << &(*this) << endl;
	}
	void Update()
	{
		this->m_dst.x += 5;	// Speed O' Bullet going -> that way
	}
	void SetLoc(SDL_Point loc)
	{
		m_dst.x = loc.x;
		m_dst.y = loc.y;

	}
	void Render(SDL_Renderer* rend, SDL_Texture* tex)
	{
		SDL_RenderCopyEx(rend, tex, &m_src, &m_dst, 90.0, NULL, SDL_FLIP_NONE);

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
