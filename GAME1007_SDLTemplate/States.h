#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "Engine.h"
#include "SDL.h"

class State
{
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
	virtual ~State() = default;
protected:
	State() {};
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:
	SDL_Texture* m_pTitle;
	SDL_Texture* m_pStartButton;
	SDL_Texture* m_pBGTexture;
	Sprite m_title;
	Sprite m_start;
	Sprite m_bg1;

	// Music
	Mix_Music* m_music;
	
	// Mouse
	SDL_Point m_mousePos;
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

private:
	//SDL_Texture* m_pEnemyTexture;
	//SDL_Texture* m_pLazerTexture;
	//SDL_Texture* m_pElazerTexture;
	//SDL_Texture* m_pMarvinTexture;
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pBGTexture1;
	SDL_Texture* m_pBGTexture2;
	SDL_Texture* m_pBGTexture3;
	SDL_Texture* m_pBGTexture4;
	SDL_Texture* m_pBGTexture5;
	SDL_Texture* m_pBGTexture6;


	//Sprite m_bg1, m_bg2;	
	
	// Backgrounds
	Sprite m_backgroundLayer01[2];
	Sprite m_backgroundLayer02[2];
	Sprite m_backgroundLayer03[2];
	Sprite m_backgroundLayer04[2];
	Sprite m_backgroundLayer05[2];
	Sprite m_backgroundLayer06;

	vector<Sprite> m_backgrounds;

	// Player Pointer
	Sprite* m_player = nullptr;	

	//// Bullet Vector
	//vector<Bullet*> m_bullets;

	//// Enemy Bullet Vector
	//vector<eBullet*> m_enemyBullets;

	//// Enemy vector
	//vector<Enemy*> m_enemies;

	//// Marvin(Obstacles) vector
	//vector<Marvins*> m_marvins;

	// Music
	Mix_Music* m_music;
	// Sound Effects
	/*Mix_Chunk* m_pLaser;
	Mix_Chunk* m_eLaser;
	Mix_Chunk* m_pDeath;
	Mix_Chunk* m_eDeath;*/

	int m_speed = 5; // In-class initialization. Not normal.
	/*int m_spawnTimer = 60;
	int m_bulletTimer = 60;
	int m_marvinTimer = 80;
	int m_shotTimer = 0;*/

	bool m_isDead;
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
private:
	SDL_Texture* m_pResume;
	Sprite m_resume;

	// Mouse
	SDL_Point m_mousePos;
};


class LoseState : public State
{
public:
	LoseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
	SDL_Texture* m_pBGTexture;
	SDL_Texture* m_pRestart;
	Sprite m_bg1;
	Sprite m_restart;

	// Music
	Mix_Music* m_music;
	
	// Mouse
	SDL_Point m_mousePos;
};

#endif