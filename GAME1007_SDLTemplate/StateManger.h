#pragma once
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_
#include "States.h"

class StateManger
{
public: // Properties
	static std::vector<State*> s_states;

public: // Methods
	static void Update();
	static void Render();
	static void PushState(State* pState);
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit();
	static std::vector<State*>& GetStates();
private:
	StateManger() {}
};

typedef StateManger STMA;

#endif
