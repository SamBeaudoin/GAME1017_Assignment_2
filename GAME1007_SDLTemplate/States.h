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
	
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pBGTexture1;
	SDL_Texture* m_pBGTexture2;
	SDL_Texture* m_pBGTexture3;
	SDL_Texture* m_pBGTexture4;
	SDL_Texture* m_pBGTexture5;
	SDL_Texture* m_pBGTexture6;
	
	// Backgrounds
	Sprite m_backgroundLayer01[2];
	Sprite m_backgroundLayer02[2];
	Sprite m_backgroundLayer03[2];
	Sprite m_backgroundLayer04[2];
	Sprite m_backgroundLayer05[2];
	Sprite m_backgroundLayer06;

	vector<Sprite> m_backgrounds;

	// Player Pointer
	Player* m_player = nullptr;	

	

	// Music
	Mix_Music* m_music;
	
	Mix_Chunk* m_pDeath;
	

	int m_speed = 5; 
	

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