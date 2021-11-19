#pragma once
#include<iostream>
extern int CurrentState;
class State
{
public:
	int currentState();
	void NextState(int s);
private:
	int state;
};

