#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "GameObject.h"
#include "Background.h"
#include "Obstacles.h"
#include "Player.h"

using namespace std;
// Do not include any macros, initialized properties or full function definitions in this header.

class Engine
{
private: // Private properties.
	bool m_bRunning; // Loop control flag.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.

	// Example-specific properties.
	Background m_layer01[2] = { Background({0,0,1920,1080}, {0,0,1024,768}, 5,"L01"),
									Background({0,0,1920,1080}, {1024,0,1024,768}, 5,"L01") };

	Background m_layer02[2] = { Background({0,0,1920,1080}, {0,0,1024,768}, 4,"L02"),
									Background({0,0,1920,1080}, {1024,0,1024,768}, 4,"L02") };

	Background m_layer03[2] = { Background({0,0,1920,1080}, {0,0,1024,768}, 3,"L03"),
									Background({0,0,1920,1080}, {1024,0,1024,768}, 3,"L03") };

	Background m_layer04[2] = { Background({0,0,1920,1080}, {0,0,1024,768}, 2,"L04"),
									Background({0,0,1920,1080}, {1024,0,1024,768}, 2,"L04") };

	Background m_layer05[2] = { Background({0,0,1920,1080}, {0,0,1024,768}, 1,"L05"),
									Background({0,0,1920,1080}, {1024,0,1024,768}, 1,"L05") };

	Background m_layer06 = { Background({0,0,1920,1080}, {0,0,1024,768}, 0,"L06") };


	std::vector<Background> m_backgrounds;

	/*
	* 
	Obstacle m_obstacle01 = Obstacle()		Adding Obstacles in here...

	
	*/

	std::vector<Obstacle> m_obstacles;

	//Player
	
									

private: // Private methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
public: // Public methods.
	Engine();
	~Engine();
	int Run();
	static Engine& Instance(); // This static method creates the static instance that can be accessed 'globally'
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer();
};