#include "pch.h"
#include "Game.h"
#include "graphics.h"
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
//싱글톤 패턴으로, Game에서 필요한 모든 Manager를 초기화 한다.
/*
 input
 time
 scene
 resource
 render 
 */
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
//프레임의 변화마다 바뀌는 것들만 업데이트한다. 대표적으로 시간, input에 따른 변화, Scene의 업데이트가 주다.
//render와 resource는 초기에 한번만 로드하면 되기에 제외한다.
void Game::Update()
{
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}
//render는 추가적인 소스를 불러올떄 사용한다.
void Game::Render()
{
	RENDER->Update(_graphics);
}