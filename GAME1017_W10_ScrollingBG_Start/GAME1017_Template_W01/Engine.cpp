#include <iostream>
#include <ctime>
#include "Engine.h"
#include "TextureManager.h"
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine():m_bRunning(false){	cout << "Engine class constructed!" << endl; }
Engine::~Engine(){}

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				TEMA::Init();
				TEMA::Load("BG.png", "bg");	// Map key is "bg" ( example Background )

				TEMA::Load("layer01.png","L01");	// Background layers we are using
				TEMA::Load("layer02.png","L02");
				TEMA::Load("layer03.png","L03");
				TEMA::Load("layer04.png","L04");
				TEMA::Load("layer05.png","L05");
				TEMA::Load("layer06.png","L06");

				/* 
				Obstacle and Player .png Loading here...
				
				*/			
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	srand((unsigned)time(NULL)); // Seed random number sequence.
	
	// Fill the background vector now.
	m_backgrounds.push_back(m_layer06);
	m_backgrounds.push_back(m_layer05[1]);
	m_backgrounds.push_back(m_layer05[0]);
	m_backgrounds.push_back(m_layer04[1]);
	m_backgrounds.push_back(m_layer04[0]);
	m_backgrounds.push_back(m_layer03[1]);
	m_backgrounds.push_back(m_layer03[0]);
	m_backgrounds.push_back(m_layer02[1]);
	m_backgrounds.push_back(m_layer02[0]);
	m_backgrounds.push_back(m_layer01[1]);
	m_backgrounds.push_back(m_layer01[0]);

	/*
		Fill m_obstacles here...
	*/

	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_bRunning = false;
				break;
			}
			if (SDL_SCANCODE_W)
			{
				// Player Jumps
				break;
			}
			if (SDL_SCANCODE_S)
			{
				// Player Ducks / Rolls
				break;
			}
		}
	}
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::Update()
{
	for (int i = 0; i < m_backgrounds.size(); i++)
		m_backgrounds[i].Update();
	
	//// Check if first background goes out of bounds.
	//if (m_backgrounds[0].GetDst()->x <= -(m_backgrounds[0].GetDst()->w))
	//{
	//	for (int i = 0; i < 2; i++)
	//		m_backgrounds[i].GetDst()->x += m_backgrounds[i].GetDst()->w;
	//}
	//if (m_midgrounds[0].GetDst()->x <= -(m_midgrounds[0].GetDst()->w))
	//{
	//	for (int i = 0; i < 5; i++)
	//		m_midgrounds[i].GetDst()->x += m_midgrounds[i].GetDst()->w;
	//}
	//if (m_foregrounds[0].GetDst()->x <= -(m_foregrounds[0].GetDst()->w))
	//{
	//	for (int i = 0; i < 3; i++)
	//		m_foregrounds[i].GetDst()->x += m_foregrounds[i].GetDst()->w;
	//}
	//// Scroll the backgrounds.
	//for (int i = 0; i < 2; i++)
	//{
	//	m_backgrounds[i].GetDst()->x -= 1;	// Could have literal as a scroll speed property of class
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	m_midgrounds[i].GetDst()->x -= 3;	// Could have literal as a scroll speed property of class
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	m_foregrounds[i].GetDst()->x -= 4;	// Could have literal as a scroll speed property of class
	//}
	
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Render stuff.
	for (int i = 0; i < m_backgrounds.size(); i++)
		m_backgrounds[i].Render();
		//SDL_RenderCopyF(m_pRenderer, TEMA::GetTexture("bg"), m_backgrounds[i].GetSrc(), m_backgrounds[i].GetDst());
	
	// Draw anew.
	SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TEMA::Quit();
	IMG_Quit();
	SDL_Quit();
}

int Engine::Run()
{
	if (m_bRunning) // What does this do and what can it prevent?
		return -1; 
	if (Init("GAME1017 Engine Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }

// Render Functions for Objects...

void Background::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key), GetSrc(), GetDst());
}

void Obstacle::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key), GetSrc(), GetDst());
}

void Player::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key), GetSrc(), GetDst());
}

void Player::Update()
{
	// Player Controller...


	// Player Collision...


}
