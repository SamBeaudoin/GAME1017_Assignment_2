#include "States.h"
#include "Engine.h"
#include "StateManger.h"

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

	if (SDL_PointInRect(&m_mousePos, m_start.GetDst()) && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		STMA::ChangeState(new GameState);
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

	// Load Textures
	m_pPlayerTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/Marvin.png");

	m_pBGTexture1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer01.png");
	m_pBGTexture2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer02.png");
	m_pBGTexture3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer03.png");
	m_pBGTexture4 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer04.png");
	m_pBGTexture5 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer05.png");
	m_pBGTexture6 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "img/layer06.png");

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

	// Load Sounds
	m_music = Mix_LoadMUS("sfxs/space_walk.mp3");
	//m_eDeath = Mix_LoadWAV("sfxs/Example_Sound_Effect.wav");
	
	// Player Placing
	m_player = new Player;
	m_player->SetRects({ 0,0,100,100 }, { 150,560,100,100 }); 

	Mix_PlayMusic(m_music, -1);	// 0-n for # of loops, -1 for infinite
	Mix_VolumeMusic(20);	// 0 - 128

	m_isDead = false;
}

void GameState::Update()
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
	m_backgrounds[9].GetDst()->x -= 5;
	m_backgrounds[10].GetDst()->x -= 5;
	
	// Wrap backgrounds
	for (int i = 0; i < m_backgrounds.size(); i++)
	{
		if (m_backgrounds[i].GetDst()->x <= -1024)
			m_backgrounds[i].GetDst()->x = 1024;
	}

	//Parse player movement
	if (m_player != nullptr)
	{
		if (Engine::Instance().KeyDown(SDL_SCANCODE_W) && m_player->IsGrounded())
		{
			m_player->SetAccelY(-JUMPFORCE);
			m_player->SetGrounded(false);
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S) && m_player->GetDst()->y < HEIGHT - m_player->GetDst()->h)
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
	m_player->Update();

	if (m_player->GetDst()->y >= 560)
	{
		m_player->StopY();
		m_player->SetY(560.0f);
		m_player->SetGrounded(true);
	}

	SDL_RenderClear(Engine::Instance().GetRenderer());

	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		STMA::PushState(new PauseState);

	if (m_isDead)
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

	if (SDL_PointInRect(&m_mousePos, m_restart.GetDst()) && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		STMA::ChangeState(new TitleState);
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
