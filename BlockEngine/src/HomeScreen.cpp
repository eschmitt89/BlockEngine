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
#include <sstream>

HomeScreen::HomeScreen() 
{
	GridGenerator gridGenerator;
	grid = gridGenerator.Generate(12, 12, 20, 2, 4, 1, 3, 5, 32, 32);
	camera = new Camera(sf::Vector2f(480,0), sf::Vector2f(960,540));
	player = new Player(ResourceManager::GetInstance().GetTexture("player"), sf::Vector2f(100,100), sf::Vector2f(32, 32));
	physicsManager = new PhysicsManager(grid);
	physicsManager->AddPhysicsObject(player);
	itemGenerator = new ItemGenerator();

	fpsText = sf::Text("", *ResourceManager::GetInstance().GetFont("font"));
	fpsText.setFillColor(sf::Color::Red);
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

	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::M))
	{
		for (int i = 0; i < 10; i++)
		{

		
		Item* item = itemGenerator->Generate(10);
		if (item->GetItemType() == ItemType_Equipment)
		{
			Equipment* equipment = (Equipment*)item;
			sf::Color color = sf::Color::White;


		    if (equipment->GetEquipmentRarity() == EquipmentRarity_Good)
			{
				color = sf::Color::Green;
			}
			else if (equipment->GetEquipmentRarity() == EquipmentRarity_Rare)
			{
				color = sf::Color::Blue;
			}
			else if (equipment->GetEquipmentRarity() == EquipmentRarity_Epic)
			{
				color = sf::Color(128, 0, 255, 155);
			}
			else if (equipment->GetEquipmentRarity() == EquipmentRarity_Legendary)
			{
				color = sf::Color(250,100,0,155);
			}
			else if (equipment->GetEquipmentRarity() == EquipmentRarity_Artifact)
			{
				color = sf::Color::Red;
			}

			physicsManager->AddPhysicsObject(new Particle(color, GetMousePosition(window), sf::Vector2f(10, 10), 4));
		}

		delete item;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::RBracket))
	{
		currentItemLevel++;
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::LBracket))
	{
		currentItemLevel--;
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
	//camera->SetCenter(player->GetCenter());

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
	ss << "\ncurrent item level: " << currentItemLevel;
	return ss.str();
}
