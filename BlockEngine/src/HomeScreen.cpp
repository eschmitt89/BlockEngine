//
//  HomeScreen.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "HomeScreen.hpp"
#include "ResourceManager.hpp"
#include <sstream>

HomeScreen::HomeScreen()
{
	grid = new Grid(200, 100, 32, 32);
	camera = new Camera(sf::Vector2f(480,0), sf::Vector2f(960,540));
	player = new Player(ResourceManager::GetInstance().GetTexture("player"), sf::Vector2f(100,-100), sf::Vector2f(32, 32));
	physicsManager = new PhysicsManager(grid);
	physicsManager->AddPhysicsObject(player);

	fpsText = sf::Text("", *ResourceManager::GetInstance().GetFont("font"));
	fpsText.setFillColor(sf::Color::Red);
}

////////////////////////////////////////////////////////////////////////

HomeScreen::~HomeScreen()
{
	delete grid;
	delete camera;
	delete player;
	delete physicsManager;
}

////////////////////////////////////////////////////////////////////////

bool HomeScreen::DoesHandleInput()
{
    return true;
}

////////////////////////////////////////////////////////////////////////

void HomeScreen::HandleInput(const sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::Solid);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::Empty);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::LadderTop);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::Ladder);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::LadderBottom);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::Corner);
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		physicsManager->AddPhysicsObject(new PhysicsObject(ResourceManager::GetInstance().GetTexture("whiteBlock"), GetMousePosition(window), sf::Vector2f(10,10)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		physicsManager->ClearPhyiscsObjects();
	}

	camera->HandleInput(window);

	player->HandleInput(window);
}

////////////////////////////////////////////////////////////////////////

bool HomeScreen::DoesUpdate()
{
    return true;
}

////////////////////////////////////////////////////////////////////////

void HomeScreen::Update(float dt)
{
	camera->Update(dt);
	physicsManager->Update(dt);
	camera->SetCenter(player->GetCenter());

	fpsText.setString(GetFpsString(dt));
}

////////////////////////////////////////////////////////////////////////

bool HomeScreen::DoesDraw()
{
    return true;
}

////////////////////////////////////////////////////////////////////////

void HomeScreen::Draw(sf::RenderWindow &window)
{
	window.setView(camera->GetView());

	grid->Draw(window, camera);
	physicsManager->Draw(window);

	window.setView(window.getDefaultView());
	window.draw(fpsText);
	window.setView(camera->GetView());
}

////////////////////////////////////////////////////////////////////////

string HomeScreen::GetFpsString(float dt)
{
	stringstream ss;
	ss << (int)(1 / dt);
	return ss.str();
}
