//
//  HomeScreen.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "HomeScreen.hpp"
#include "EventManager.hpp"
#include "GridGenerator.hpp"
#include "ResourceManager.hpp"
#include "TransitionParticle.hpp"
#include "Emitter.hpp"
#include "ItemGenerator.hpp"
#include "Coin.hpp"
#include "ItemPhysicsObject.hpp"
#include "Enemy.hpp"
#include <sstream>

HomeScreen::HomeScreen() 
{
	GridGenerator gridGenerator;
	grid = gridGenerator.Generate(12, 12, 20, 2, 4, 1, 3, 5, 32, 32);
	camera = new Camera(sf::Vector2f(480,0), sf::Vector2f(1920,1080));
	player = new Player(ResourceManager::GetInstance().GetTexture("player"), sf::Vector2f(100,100), sf::Vector2f(32, 32));
	physicsManager = new PhysicsManager(grid);
	physicsManager->AddPhysicsObject(player);
	itemGenerator = new ItemGenerator();

	fpsText = sf::Text("", *ResourceManager::GetInstance().GetFont("font"));
	fpsText.setFillColor(sf::Color::Red);

	clickable = new Clickable(sf::Vector2f(300, 100), sf::Vector2f(50, 50));
}

////////////////////////////////////////////////////////////////////////

HomeScreen::~HomeScreen()
{
	delete grid;
	delete camera;
	delete physicsManager;
	delete itemGenerator;
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
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Solid);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Empty);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_LadderTop);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Ladder);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_LadderBottom);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Corner);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Platform);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_Liquid);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
	{
		grid->SetBlockType(GetMousePosition(window), BlockType::BlockType_LiquidTop);
	}

	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::P))
	{
		//physicsManager->AddPhysicsObject(new TransitionParticle(GetMousePosition(window), sf::Vector2f(3,3), 5));
		physicsManager->AddPhysicsObject(new Emitter(new TransitionParticle(GetMousePosition(window), sf::Vector2f(3, 3), 5), GetMousePosition(window), sf::Vector2f(6, 6), 1));
	}


	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::L))
	{
		//physicsManager->AddPhysicsObject(new Coin(GetMousePosition(window), 1));
		physicsManager->AddPhysicsObject(new Enemy(ResourceManager::GetInstance().GetTexture("whiteBlock"), GetMousePosition(window), sf::Vector2f(32, 32)));
	}

	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::M))
	{
		physicsManager->AddPhysicsObjects(itemGenerator->GenerateLoot(currentItemLevel, GetMousePosition(window)));
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::RBracket))
	{
		currentItemLevel += 5;
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::LBracket))
	{
		currentItemLevel -= 5;;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		physicsManager->ClearPhyiscsObjects();
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::B))
	{
		
	}
	else if (EventManager::GetInstance().IsKeyHeld(sf::Keyboard::B))
	{
		
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::B))
	{
		physicsManager->AddPhysicsObject(itemGenerator->Generate(10, GetMousePosition(window)));
	}

	camera->HandleInput(window);

	player->HandleInput(window);

	clickable->HandleInput(window);
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
	//camera->SetCenter(player->GetCenter());

	fpsText.setString(GetFpsString(dt));

	clickable->Update(dt);
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

	clickable->Draw(window);

	window.setView(window.getDefaultView());
	window.draw(fpsText);
	
	window.setView(camera->GetView());
}

////////////////////////////////////////////////////////////////////////

string HomeScreen::GetFpsString(float dt)
{
	stringstream ss;
	ss << (int)(1 / dt);
	ss << "\ncurrent item level: " << currentItemLevel;
	return ss.str();
}
