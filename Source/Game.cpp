#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Game.h"

// Constructor 
SpaceInvaders::SpaceInvaders()
{
}

//Deconstructor 
SpaceInvaders::~SpaceInvaders()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);


}

// Intilise 
bool SpaceInvaders::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}

	toggleFPS();
	renderer->setWindowTitle("Space Invaders!");

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &SpaceInvaders::keyHandler, this);
	
	mouse_callback_id =inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &SpaceInvaders::clickHandler, this);

	bool retflag;
	bool retval = initGameobjects(retflag);
	if (retflag) return retval;

return true;
}

bool SpaceInvaders::initGameobjects(bool &retflag)
{
	retflag = true;
	//Gameobjects  Init 

	if (!options.addSpriteComponent(renderer.get(), "Resources\\textures\\spaceshooter\\backgrounds\\black.PNG"))
	{
		return false;
	}
	options_Sprite = options.spriteComponent()->getSprite();
	options_Sprite->width(1920);
	options_Sprite->height(1080);

	//Background 

	if (!game.addSpriteComponent(renderer.get(), "Resources\\snake_bg.PNG"))
	{
		return false;
	}
	game_Sprite = game.spriteComponent()->getSprite();
	game_Sprite->width(1920);
	game_Sprite->height(1080);

	if (!snake.addSpriteComponent(renderer.get(), "Resources\\snake.PNG"))
	{
		return false;
	}
	snake.setSpeed(150);
	snake.spriteComponent()->getSprite()->xPos(game_width /2);
	snake.spriteComponent()->getSprite()->yPos(game_height/2);
	retflag = false;
	return {};
}

// Sets height and width for the Screen 
void SpaceInvaders::setupResolution()
{
	
	game_height = 1080;
	game_width = 1920;
}
// All the keys for Controls 
void SpaceInvaders::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
	
	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}





	// Changing Menu 
	switch (ffff)
	{
	case MENU:
		if (key->key == ASGE::KEYS::KEY_K)
		{
			ffff = GAME;	
			
		}
		break;

	case GAME:
		SnakeKeys(key);
		if (key->key == ASGE::KEYS::KEY_L)
		{
			ffff = MENU;
		}
		break;
	}

}

void SpaceInvaders::SnakeKeys(const ASGE::KeyEvent * key)
{
	if (key->key == ASGE::KEYS::KEY_LEFT  &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		snake_left = true;
		snake_right = false;
		snake_up = false;
		snake_down = false;


	}

	if (key->key == ASGE::KEYS::KEY_RIGHT &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		snake_left = false;
		snake_right = true;
		snake_up = false;
		snake_down = false;

	}

	if (key->key == ASGE::KEYS::KEY_UP  &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		snake_left = false;
		snake_right = false;
		snake_up = true;
		snake_down = false;
	}

	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		snake_left = false;
		snake_right = false;
		snake_up = false;
		snake_down = true;
	}
}

// all the Movements for the mouse 
void SpaceInvaders::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());

	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
}


// Updates any Game objects 
void SpaceInvaders::update(const ASGE::GameTime& us)
{
	//make sure you use delta time in any movement calculations!
	auto dt_sec = us.delta_time.count() / 1000.0;
	auto snake_xpos = snake.spriteComponent()->getSprite()->xPos();
	auto snake_ypos = snake.spriteComponent()->getSprite()->yPos();

	//Movement
	switch (ffff)
	{
		case MENU:
			break;
	
		case GAME:
			if (snake_xpos <= 165 || snake_ypos <=90 || snake_xpos >= 1625 || snake_ypos >= 860)
			{
				ffff = MENU;
				
				snake.spriteComponent()->getSprite()->xPos(game_width / 2);
				snake.spriteComponent()->getSprite()->yPos(game_height / 2);
				snake_left = false;
				snake_right = false;
				snake_up = false;
				snake_down = false;

			}
			SnakeMovement(dt_sec);
			
			break;
	}

}

void SpaceInvaders::SnakeMovement(double dt_sec)
{
	if (snake_left == true)
	{
		snake.spriteComponent()->getSprite()->xPos
			// This updates the xpostion by using Get Speed then divides it by Dt sec
			(snake.spriteComponent()->getSprite()->xPos() - snake.getSpeed() * dt_sec);
	}
	if (snake_right == true)
	{
		// This finds the Current X postion 
		snake.spriteComponent()->getSprite()->xPos
			// This updates the xpostion by using Get Speed then divides it by Dt sec
			(snake.spriteComponent()->getSprite()->xPos() + snake.getSpeed() * dt_sec);

	}

	if (snake_up == true)
	{
		snake.spriteComponent()->getSprite()->yPos
			// This updates the xpostion by using Get Speed then divides it by Dt sec
			(snake.spriteComponent()->getSprite()->yPos() - snake.getSpeed() * dt_sec);
	}

	if (snake_down == true)
	{
		snake.spriteComponent()->getSprite()->yPos
			// This updates the xpostion by using Get Speed then divides it by Dt sec
			(snake.spriteComponent()->getSprite()->yPos() + snake.getSpeed() * dt_sec);
	}
}

// Renders the Objects 
void SpaceInvaders::render(const ASGE::GameTime &)
{
	renderer->setFont(0);

	switch (ffff)
	{
	case MENU:
		renderer->renderSprite(*options.spriteComponent()->getSprite());
		break;

	case GAME:
		renderer->renderSprite(*game.spriteComponent()->getSprite());
		renderer->renderSprite(*snake.spriteComponent()->getSprite());
		break;
	}
	

}
