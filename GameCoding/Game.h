#pragma once

#include "GameObject/GameObject.h"
#include "Pipeline/graphics.h"

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd;
	//width, height=0; -> init의 GWinsizeX, Bufferdesc.height, setviewport
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;
	shared_ptr<GameObject> _gameObject;

};

