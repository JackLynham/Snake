#pragma once

class Vector2
{
public:
	Vector2(float x_vec_val, float y_vec_val);
	~Vector2();
	float get_x();
	float get_y();
	// This Gives us a normalsie funciton
	void normalise();

	void set_x(float x_vec_val);
	void set_y(float y_vec_val);
private:

	float x;
	float y;
};
