#include "StateManger.h"

void StateManger::Update()
{
	if (!s_states.empty())
		s_states.back()->Update();
}

void StateManger::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();
}

void StateManger::PushState(State* pState)
{
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManger::PopState()
{
	if (s_states.size() <= 1) return;
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.back()->Resume();
}

void StateManger::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	pState->Enter();
	s_states.push_back(pState);
}

void StateManger::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManger::GetStates() { return s_states; }

std::vector<State*> StateManger::s_states;