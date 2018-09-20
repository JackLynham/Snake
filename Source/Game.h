#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"


/**
*  An OpenGL Game based on ASGE.
*/
class SpaceInvaders :
	public ASGE::OGLGame
{
public:
	SpaceInvaders();
	~SpaceInvaders();
	virtual bool init() override;

	bool initGameobjects(bool &retflag);

private:
	void keyHandler(const ASGE::SharedEventData data);
	void SnakeKeys(const ASGE::KeyEvent * key);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();

	virtual void update(const ASGE::GameTime &) override;
	void SnakeMovement(double dt_sec);
	virtual void render(const ASGE::GameTime &) override;

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

	//Add your GameObjects

	bool in_menu = true;
	GameObject game; 
	ASGE::Sprite*game_Sprite;

	GameObject snake;
	ASGE::Sprite*snake_Sprite;

	GameObject options;
	ASGE::Sprite*options_Sprite;


	Vector2 snake_velocity{ 1, 0 };

	enum SELECT 
	{
		MENU,
		GAME
	};

	SELECT ffff = MENU;

	bool snake_left = false;
	bool snake_right = false ;
	bool snake_up = false;
	bool snake_down = false;
};