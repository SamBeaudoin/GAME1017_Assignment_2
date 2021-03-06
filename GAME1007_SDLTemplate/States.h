#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "Engine.h"
#include "SDL.h"
#include <map>
#include <vector>
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
	SDL_Texture* m_pExitButton;

	Sprite m_exit;
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


	TTF_Font* m_pfont;
	SDL_Surface* m_pFontSurf;
	SDL_Texture* m_pFontTexture;
	SDL_Rect m_textRect; //The Size of the text element. // w/h are automatically from texture;
	
	SDL_Texture* m_pPlayerTexture;

	SDL_Texture* m_pBGTexture1;
	SDL_Texture* m_pBGTexture2;
	SDL_Texture* m_pBGTexture3;
	SDL_Texture* m_pBGTexture4;
	SDL_Texture* m_pBGTexture5;
	SDL_Texture* m_pBGTexture6;
	SDL_Texture* m_pBGTexture7;

	SDL_Texture* m_pObstacle1;
	SDL_Texture* m_pObstacle2;
	SDL_Texture* m_pObstacle3;
	SDL_Texture* m_pObstacle4;
	SDL_Texture* m_pObstacle5;
	SDL_Texture* m_pObstacle6;
	SDL_Texture* m_pObstacle7;
	SDL_Texture* m_pObstacle8;
	SDL_Texture* m_pObstacle9;
	
	Sprite m_backgroundLayer01[2];
	Sprite m_backgroundLayer02[2];
	Sprite m_backgroundLayer03[2];
	Sprite m_backgroundLayer04[2];
	Sprite m_backgroundLayer05[2];
	Sprite m_backgroundLayer06;
	Sprite m_backgroundLayer07[2];

	Sprite m_Obstacle1;
	Sprite m_Obstacle2;
	Sprite m_Obstacle3;
	Sprite m_Obstacle4;
	Sprite m_Obstacle5;
	Sprite m_Obstacle6;
	Sprite m_Obstacle7;
	Sprite m_Obstacle8;
	Sprite m_Obstacle9;


	vector<Sprite> m_backgrounds;

	// Box specific
	vector<Box*> m_vec;
	map<int, Box*> m_map;

	int m_gapCtr = 0, m_gapMax = 8;


	// Player Pointer
	Player* m_player = nullptr;	
	int playerindex = 0;

	int m_score = 0;

	// Music
	Mix_Music* m_music;
	
	Mix_Chunk* m_pDeath;
	Mix_Chunk* m_pJump;
	

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
	SDL_Texture* m_pExitButton;

	Sprite m_exit;
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