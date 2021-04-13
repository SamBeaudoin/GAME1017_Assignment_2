#include "States.h"
#include "Engine.h"
#include "StateManger.h"

Sprite::Sprite() :m_dst({ 0,0,0,0 }), m_color({ 255,255,255,255 }) {}
Sprite::Sprite(const SDL_Rect r, const SDL_Color c) : m_dst(r), m_color(c) {}

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume() {}

// Begin TitleState
TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering TitleState..." << endl;

	m_pTitle = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/title.png");
	m_pStartButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/startbutton.png");
	m_pBGTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/backgroundSpace.png");
	m_title.SetRects({ 0, 0, 500, 300 }, { 262, 75, 500, 300 });
	m_bg1.SetRects({ 0,0,1024,768 }, { 0,0,1024,768 });
	m_start.SetRects({ 0, 0, 400, 200 }, { 312, 550, 400, 200 });

	m_music = Mix_LoadMUS("sfxs/ChildrensPolka.mp3");

	Mix_PlayMusic(m_music, -1);	// 0-n for # of loops, -1 for infinite
	Mix_VolumeMusic(20);	// 0 - 128
}

void TitleState::Update()
{
	SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

	if (SDL_PointInRect(&m_mousePos, m_start.GetDst()))
	{
		SDL_SetTextureColorMod(m_pStartButton, 150,150, 150);
		if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			STMA::ChangeState(new GameState);
		}
	}
	else {
		SDL_SetTextureColorMod(m_pStartButton, 255, 255, 255);
	}
}

void TitleState::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture, m_bg1.GetSrc(), m_bg1.GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTitle, m_title.GetSrc(), m_title.GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pStartButton, m_start.GetSrc(), m_start.GetDst());
	
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	SDL_DestroyTexture(m_pStartButton);
	SDL_DestroyTexture(m_pBGTexture);
	SDL_DestroyTexture(m_pTitle);

	Mix_FreeMusic(m_music);
}

GameState::GameState() {}

void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	
	m_isDead = false;
	// Load Textures
	m_pPlayerTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/player.png");

	m_pBGTexture1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer01.png");
	m_pBGTexture2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer02.png");
	m_pBGTexture3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer03.png");
	m_pBGTexture4 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer04.png");
	m_pBGTexture5 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer05.png");
	m_pBGTexture6 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer06.png");

	m_pObstacle1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle4 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle5 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle6 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle7 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle8 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");
	m_pObstacle9 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/obstacle.png");

	m_backgroundLayer01[0].SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });
	m_backgroundLayer01[1].SetRects({ 0,0,1920,1080 }, { 1024,0,1024,768 });
	m_backgroundLayer02[0].SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });
	m_backgroundLayer02[1].SetRects({ 0,0,1920,1080 }, { 1024,0,1024,768 });
	m_backgroundLayer03[0].SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });
	m_backgroundLayer03[1].SetRects({ 0,0,1920,1080 }, { 1024,0,1024,768 });
	m_backgroundLayer04[0].SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });
	m_backgroundLayer04[1].SetRects({ 0,0,1920,1080 }, { 1024,0,1024,768 });
	m_backgroundLayer05[0].SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });
	m_backgroundLayer05[1].SetRects({ 0,0,1920,1080 }, { 1024,0,1024,768 });
	m_backgroundLayer06.SetRects({ 0,0,1920,1080 }, { 0,0,1024,768 });

	//m_backgrounds.push_back(m_backgroundLayer01[0]);

	m_backgrounds.push_back(m_backgroundLayer06);		// sky
	m_backgrounds.push_back(m_backgroundLayer05[1]);
	m_backgrounds.push_back(m_backgroundLayer05[0]);	// Cloud
	m_backgrounds.push_back(m_backgroundLayer04[1]);
	m_backgrounds.push_back(m_backgroundLayer04[0]);	// Mountain
	m_backgrounds.push_back(m_backgroundLayer03[1]);
	m_backgrounds.push_back(m_backgroundLayer03[0]);	// Tree
	m_backgrounds.push_back(m_backgroundLayer02[1]);
	m_backgrounds.push_back(m_backgroundLayer02[0]);	// Cake
	m_backgrounds.push_back(m_backgroundLayer01[1]);
	m_backgrounds.push_back(m_backgroundLayer01[0]);	// Ground

	m_Obstacle1.SetRects({ 0,0,64,128 }, { 600,436,64,128 });
	m_Obstacle2.SetRects({ 64,0,64,128 }, { 600,436,64,128 });
	m_Obstacle3.SetRects({ 128,0,64,128 }, { 600,436,64,128 });
	m_Obstacle4.SetRects({ 0,128,64,128 }, { 600,500,64,128 });
	m_Obstacle5.SetRects({ 64,128,64,128 }, { 600,500,64,128 });
	m_Obstacle6.SetRects({ 128,128,64,128 }, { 600,500,64,128 });
	m_Obstacle7.SetRects({ 0,298,64,86}, { 600,542,64,86 });
	m_Obstacle8.SetRects({ 64,298,64,86 }, { 600,542,64,86 });
	m_Obstacle9.SetRects({ 128,298,64,86 }, { 600,542,64,86 });

	m_Obstacle1.setTexture(m_pObstacle1);
	m_Obstacle2.setTexture(m_pObstacle2);
	m_Obstacle3.setTexture(m_pObstacle3);
	m_Obstacle4.setTexture(m_pObstacle4);
	m_Obstacle5.setTexture(m_pObstacle5);
	m_Obstacle6.setTexture(m_pObstacle6);
	m_Obstacle7.setTexture(m_pObstacle7);
	m_Obstacle8.setTexture(m_pObstacle8);
	m_Obstacle9.setTexture(m_pObstacle9);

	// Load Sounds
	m_music = Mix_LoadMUS("sfxs/space_walk.mp3");
	//m_eDeath = Mix_LoadWAV("sfxs/Example_Sound_Effect.wav");
	
	// Player Placing
	m_player = new Player;
	m_player->SetRects({ 0,0,64,100}, { 150,530,64,100 }); 

	Mix_PlayMusic(m_music, -1);	// 0-n for # of loops, -1 for infinite
	Mix_VolumeMusic(20);	// 0 - 128

	m_isDead = false;
	m_vec.reserve(18); // Canadian programming. Ensures push_back doesn't have to reallocated vector.
	// Create the vector now.
	for (int i = 0; i < 18; i++)
		m_vec.push_back(new Box({ 64 * i,384 }));
	// Populate the map with prototype Boxes.

	m_map.emplace(0, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(1, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(2, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(3, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(4, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(5, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(6, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(7, new Box({ 1024, 384 }, true, 1));
	m_map.emplace(8, new Box({ 1024, 384 }, true, 1));

	m_map[0]->AddSprite(0, m_Obstacle1);
	m_map[1]->AddSprite(0, m_Obstacle2);
	m_map[2]->AddSprite(0, m_Obstacle3);
	m_map[3]->AddSprite(0, m_Obstacle4);
	m_map[4]->AddSprite(0, m_Obstacle5);
	m_map[5]->AddSprite(0, m_Obstacle6);
	m_map[6]->AddSprite(0, m_Obstacle7);
	m_map[7]->AddSprite(0, m_Obstacle8);
	m_map[8]->AddSprite(0, m_Obstacle9);

	/*m_map.emplace(3, new Box({ 1024, 384 }, true, 2));
	m_map[3]->AddSprite(0, { 1024, 498, 64, 128 }, { 255, 0, 0, 255 });
	m_map[3]->AddSprite(1, { 1024, 128, 64, 128}, { 0, 0, 255, 255 });
	m_map.emplace(4, new Box({ 1024, 384 }, true, 2));
	m_map[4]->AddSprite(0, { 1024, 560, 64, 64 }, { 0, 255, 255, 255 });
	m_map[4]->AddSprite(1, { 1024, 128, 64, 128 }, { 255, 0, 255, 255 });*/
}

void GameState::Update()
{
	if (!m_isDead)
	{
		// Background speed
		m_backgrounds[0].GetDst()->x -= 0;
		m_backgrounds[1].GetDst()->x -= 1;
		m_backgrounds[2].GetDst()->x -= 1;
		m_backgrounds[3].GetDst()->x -= 2;
		m_backgrounds[4].GetDst()->x -= 2;
		m_backgrounds[5].GetDst()->x -= 3;
		m_backgrounds[6].GetDst()->x -= 3;
		m_backgrounds[7].GetDst()->x -= 4;
		m_backgrounds[8].GetDst()->x -= 4;
		m_backgrounds[9].GetDst()->x -= 6;
		m_backgrounds[10].GetDst()->x -= 6;

		// Wrap backgrounds
		for (int i = 0; i < m_backgrounds.size(); i++)
		{
			if (m_backgrounds[i].GetDst()->x <= -1024)
				m_backgrounds[i].GetDst()->x = 1024;
		}

		//Parse player movement
		m_player->SetRolling(false);
		if (m_player != nullptr)
		{
			if (Engine::Instance().KeyDown(SDL_SCANCODE_W) && m_player->IsGrounded())
			{
				m_player->SetAccelY(-JUMPFORCE);
				m_player->SetGrounded(false);
			}
			else if (Engine::Instance().KeyDown(SDL_SCANCODE_S) && m_player->IsGrounded())
			{
				m_player->SetRolling(true);
			}
			if (Engine::Instance().KeyDown(SDL_SCANCODE_A) && m_player->GetDst()->x > 20)
			{
				m_player->SetAccelX(-1.0);
			}
			else if (Engine::Instance().KeyDown(SDL_SCANCODE_D) && m_player->GetDst()->x < WIDTH - m_player->GetDst()->w && m_player->GetDst()->x < 800)
			{
				m_player->SetAccelX(1.0);
			}
		}

		if (playerindex != 7)
			playerindex++;
		else playerindex = 0;


		if (m_player->GetDst()->y >= 530)
		{
			m_player->StopY();
			m_player->SetY(530.0f);
			m_player->SetGrounded(true);
		}

		if (m_player->IsRolling())
		{
			m_player->GetDst()->h = 64;
			m_player->GetDst()->y = 566;
		}


		// Check if first column of main vector goes out of bounds.
		if (m_vec[0]->GetPos().x <= -128)
		{
			m_score++;
			cout << m_score << endl;
			// Pop the first vector element/column off.
			delete m_vec[0]; // Deallocate Box via pointer.
			m_vec[0] = nullptr; // Optional wrangle.
			m_vec.erase(m_vec.begin()); // Destroys first element of vector.
			// Add a new Box element to the end.
			if (m_gapCtr++ % m_gapMax == 0) // Add a new Box with obstacle(s).
				m_vec.push_back(m_map[(rand() % 9)]->Clone()); // Pull random Box clone from map.
			else m_vec.push_back(new Box({ 1024,384 }, false)); // Add empty Box proxy.
		}
		// Scroll the boxes.
		for (unsigned int i = 0; i < m_vec.size(); i++)
		{
			m_vec[i]->Update();
		}
		/*for (unsigned i = 0; i < m_map.size(); i++)
		{
			if (SDL_HasIntersection(m_map[i]->GetSprite(), m_player->GetDst()))
				cout << "HIT";
		}*/

	}
	m_player->Update();
		SDL_RenderClear(Engine::Instance().GetRenderer());

		if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
			STMA::PushState(new PauseState);
	
		if (m_isDead)
		{
			m_player->GetDst()->h = 64;
			//m_player->GetDst()->y = 566;
		}
		if(m_player->GetDst()->y > 832)
		STMA::ChangeState(new LoseState);



}

void GameState::Render()
{
	// Any drawing here...

	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture6, m_backgrounds[0].GetSrc(), m_backgrounds[0].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture5, m_backgrounds[1].GetSrc(), m_backgrounds[1].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture5, m_backgrounds[2].GetSrc(), m_backgrounds[2].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture4, m_backgrounds[3].GetSrc(), m_backgrounds[3].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture4, m_backgrounds[4].GetSrc(), m_backgrounds[4].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture3, m_backgrounds[5].GetSrc(), m_backgrounds[5].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture3, m_backgrounds[6].GetSrc(), m_backgrounds[6].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture2, m_backgrounds[7].GetSrc(), m_backgrounds[7].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture2, m_backgrounds[8].GetSrc(), m_backgrounds[8].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture1, m_backgrounds[9].GetSrc(), m_backgrounds[9].GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture1, m_backgrounds[10].GetSrc(), m_backgrounds[10].GetDst());


	if (m_player != nullptr) SDL_RenderCopyEx(Engine::Instance().GetRenderer(), m_pPlayerTexture, m_player->GetSrc(), m_player->GetDst(), 0, NULL, SDL_FLIP_NONE);

	//setRects({ 0,0,64,100 }, { 150,530,64,100 });
	if (!m_isDead)
	{
		if (m_player->IsRolling())
		{
			m_player->GetSrc()->y = 136;
			m_player->GetSrc()->h = 64;


		}
		else
		{
			m_player->GetSrc()->y = 0;
			m_player->GetSrc()->h = 100;
			m_player->GetDst()->h = 100;
		}
		m_player->GetSrc()->x = 64 * playerindex;

	}
	else
	{
		m_player->GetSrc()->y = 236;
		m_player->GetSrc()->x = 0;
		m_player->GetSrc()->h = 64;
	}

	

	
	

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 16, 32, 255);
	// Render stuff.
	for (unsigned int i = 0; i < m_vec.size(); i++)
		m_vec[i]->Render();

	for (unsigned i = 0; i < m_vec.size(); i++)
	{
		if (m_vec[i]->GetRect() != nullptr)
		{
			SDL_Rect obstacle = { m_vec[i]->GetRect()->x, m_vec[i]->GetRect()->y, m_vec[i]->GetRect()->w, m_vec[i]->GetRect()->h };
			if (SDL_HasIntersection(&obstacle, m_player->GetDst()) && m_isDead == false)
			{
				m_player->SetAccelY(-JUMPFORCE);
				m_isDead = true;
			}
		}
	}

	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	
	delete m_player;
	m_player = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	SDL_DestroyTexture(m_pBGTexture1);
	SDL_DestroyTexture(m_pBGTexture2);
	SDL_DestroyTexture(m_pBGTexture3);
	SDL_DestroyTexture(m_pBGTexture4);
	SDL_DestroyTexture(m_pBGTexture5);
	SDL_DestroyTexture(m_pBGTexture6);
	Mix_FreeMusic(m_music);
}

void GameState::Resume()
{
}

PauseState::PauseState()
{
}

void PauseState::Enter()
{

	cout << "Entering PauseState" << endl;
	m_pResume = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/resume.png");
	m_resume.SetRects({ 0,0,300,150}, { 362,300,300,150});
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		STMA::PopState();
	}

	SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

	if (SDL_PointInRect(&m_mousePos, m_resume.GetDst()) && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		STMA::PopState();
	}
}

void PauseState::Render()
{
	STMA::GetStates().front()->Render();
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 210, 105, 30, 64);
	SDL_Rect rect = { 256, 128, 512, 512 };

	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pResume, m_resume.GetSrc(), m_resume.GetDst());
	
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState" << endl;
	SDL_DestroyTexture(m_pResume);
}

void PauseState::Resume()
{
}

LoseState::LoseState() {}

void LoseState::Enter()
{
	cout << "Entering LoseState..." << endl;
	m_pBGTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/backgroundSpace.png");
	m_pRestart = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/restart.png");
	m_bg1.SetRects({ 0,0,1024,768 }, { 0,0,1024,768 });
	m_restart.SetRects({ 0,0,200,400 }, { 412,150,200,400 });

	m_music = Mix_LoadMUS("sfxs/ChildrensPolka.mp3");

	Mix_PlayMusic(m_music, -1);	// 0-n for # of loops, -1 for infinite
	Mix_VolumeMusic(20);	// 0 - 128
}

void LoseState::Update()
{
	SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);


	if (SDL_PointInRect(&m_mousePos, m_restart.GetDst()))
	{
		SDL_SetTextureColorMod(m_pRestart, 150, 150, 150);
		if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			STMA::ChangeState(new TitleState);
		}
	}
	else {
		SDL_SetTextureColorMod(m_pRestart, 255, 255, 255);
	}
}

void LoseState::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTexture, m_bg1.GetSrc(), m_bg1.GetDst());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pRestart, m_restart.GetSrc(), m_restart.GetDst());
	
	State::Render();
}

void LoseState::Exit()
{
	cout << "Exiting LoseState..." << endl;
	SDL_DestroyTexture(m_pBGTexture);
	SDL_DestroyTexture(m_pRestart);

	Mix_FreeMusic(m_music);
}
