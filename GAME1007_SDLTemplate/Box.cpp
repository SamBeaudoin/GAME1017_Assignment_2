#include "Engine.h"
#define SCROLLSPD 5

//Sprite::Sprite() :m_dst({ 0,0,0,0 }), m_color({ 255,255,255,255 }) {}
//Sprite::Sprite(const SDL_Rect r, const SDL_Color c) : m_dst(r), m_color(c) {}

//void Sprite::Render()
//{
//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
//	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_dst);
//}

void Sprite::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, this->GetSrc(), this->GetDst());
}

Box::Box(const SDL_Point p, bool hasSprite, int numSprites, const SDL_Rect r,
	const SDL_Color c) :m_pos(p), m_pSprite(nullptr), m_numSprites(numSprites)
{
	if (hasSprite)
	{
		m_pSprite = new Sprite[m_numSprites];
		if (m_numSprites == 1)
		{
			Sprite newSprite(r, c);
			m_pSprite[0] = newSprite;
		}
	}
}

Box::~Box()
{
	if (m_numSprites > 0)
		delete[] m_pSprite;
}

Box* Box::Clone()
{
	Box* clone = new Box(m_pos, (m_numSprites > 0), m_numSprites);
	for (int i = 0; i < m_numSprites; i++)
		clone->AddSprite(i, this->m_pSprite[i]); // Or: clone->m_pSprite[i] = this->m_pSprite[i];
	return clone;
}

void Box::Update()
{
	m_pos.x -= SCROLLSPD; // Scroll the box.
	for (int i = 0; i < m_numSprites; i++)
		m_pSprite[i].m_dst.x = m_pos.x; // Scrolling sprite with box.
}

void Box::Render()
{
	// Render sprite.
	for (int i = 0; i < m_numSprites; i++)
		m_pSprite[i].Render();
	// Render white border. Extra for solution and supplemental video.
	//SDL_Rect m_dst = { m_pos.x, m_pos.y, 64, 64 };
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 128, 128, 128, 255);
	//SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &m_dst);
}

void Box::AddSprite(const int index, const SDL_Rect r, const SDL_Color c)
{
	Sprite newSprite(r, c);
	m_pSprite[index] = newSprite;
}

void Box::AddSprite(const int index, const Sprite& s)
{
	this->m_pSprite[index] = s;
}