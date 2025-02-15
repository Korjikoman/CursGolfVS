#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;


	SDL_Rect srcR, destR;



	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{

			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		//tex = TextureManager::LoadTexture("assets/ColTex.png");
		srcR = { 0, 0, 32, 32 };
		destR = { 0, 0, 32, 32 };
		std::cout << "Added COLLIDER COMPONENT\n";
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR);
	}

	void update() override 
	{
		if (tag != "terrain" && tag != "UPPDOWNER" && tag != "LEFTRIGHTER"
			&& tag != "corUPLEFT" && tag != "corUPRIGHT" && tag != "corDOWNLEFT" 
			&& tag != "corDOWNRIGHT" && tag != "dirt" && tag != "sand")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		
		
		destR.x = collider.x;
		destR.y = collider.y;
		
		if (tag == "hole") {
			collider.x = static_cast<int>(transform->position.x)+15;
			collider.y = static_cast<int>(transform->position.y)+15;
			collider.w = (transform->width * transform->scale)-30;
			collider.h = (transform->height * transform->scale)-30;
		}
	}
};
