#include "pch.h"
#include "Game.h"

#include "Manager/Input/InputManager.h"
#include "Manager/Render/RenderManager.h"
#include "Manager/Resource/ResourceManager.h"
#include "Manager/Scene/SceneManager.h"
#include "Manager/Time/TimeManager.h"

unique_ptr<Game> GGame = make_unique<Game>();

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);

	_input = make_shared<InputManager>();
	_input->Init(hwnd);
	_time = make_shared<TimeManager>();
	_time->Init();
	_scene = make_shared<SceneManager>(_graphics);
	_scene->Init();
	_resource = make_shared<ResourceManager>(_graphics->GetDevice());
	_resource->Init();
	_render = make_shared<RenderManager>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_render->Init();

	SCENE->LoadScene(L"Test");
}

void Game::Update()
{
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}

void Game::Render()
{
	RENDER->Update(_graphics);
}