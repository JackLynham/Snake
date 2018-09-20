#include "Vector2.h"
#include <math.h>


Vector2::Vector2(float x_vec_val, float y_vec_val)
{
	//Grabs the Normalise function 
	x = x_vec_val;
	y = y_vec_val;
}

Vector2::~Vector2()
{
}

// Get are to get value of What X is 
float Vector2::get_x()
{
	return x;

}

float Vector2::get_y()
{
	return y;
}

// Set is to set X to a certain Value 
void Vector2::set_x(float x_vec_val)
{
	x = x_vec_val;

}
void Vector2::set_y(float y_vec_val)
{
	y = y_vec_val;

}
void Vector2::normalise()
{

	// This Gives me a Magnitude then uses maths.h to get me Unit Vectors 
	float magnitude;
	magnitude = sqrt(pow(x, 2) + pow(y, 2));
	x = x / magnitude;
	y = y / magnitude;

}