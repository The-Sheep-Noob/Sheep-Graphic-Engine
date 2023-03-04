#pragma once
#include "object.h"
#include <vector>
#include <string>

struct Texture_colors {
	int R;
	int G;
	int B;
	int A;
 };
// extern keyword = tell compiler that the var is defined somewhere else*/

class Square : public Object {
private :
	void updateTexture();
	void updateColors();
	void updateRotation();
	void updateVertexBuffer();
	void updateTextureColors();
	int prev_X;
	int prev_Y;
	int prev_Z_index;
	int prev_Size;
	std::string prev_Texture;
	glm::mat4 proj;
public:
	void draw();
	void removeTexture();
	void setColors(int RGB);
	void setColors(int R, int G, int B);
	void setColors(int R, int G, int B, int A);
	void setColorsTexture(int RGB);
	void setColorsTexture(int R, int G, int B);
	void setColorsTexture(int R, int G, int B, int A);
	void setPositions(int XY);
	void setPositions(int X, int Y);
	void setPositions(int X, int Y, int Z);
	void setRotation(int Z);
	void setRotations(int X, int Y, int Z);
	void scale(int scaler);
	Square();
	int R;
	int G;
	int B;
	int A;
	int X;
	int Y;
	int X_rotate;
	int Y_rotate;
	int Z_rotate;
	int Size;
	std::string Texture;
	Texture_colors Texture_colors;
	bool Transform_from_middle;
};

class Rectangle : public Object {
private:
	void updateTexture();
	void updateColors();
	void updateRotation();
	void updateVertexBuffer();
	void updateTextureColors();
	int prev_X;
	int prev_Y;
	int prev_Z_index;
	int prev_X_size;
	int prev_Y_size;
	std::string prev_Texture;
	glm::mat4 proj;
public:
	void draw();
	void removeTexture();
	void setColors(int RGB);
	void setColors(int R, int G, int B);
	void setColors(int R, int G, int B, int A);
	void setColorsTexture(int RGB);
	void setColorsTexture(int R, int G, int B);
	void setColorsTexture(int R, int G, int B, int A);
	void setPositions(int XY);
	void setPositions(int X, int Y);
	void setPositions(int X, int Y, int Z);
	void setRotation(int Z);
	void setRotations(int X, int Y, int Z);
	void setSizes(int X, int Y);
	void setSizes(int XY);
	void scale(int scaler);
	Rectangle();
	int R;
	int G;
	int B;
	int A;
	int X;
	int Y;
	int X_rotate;
	int Y_rotate;
	int Z_rotate;
	int X_size;
	int Y_size;
	std::string Texture;
	Texture_colors Texture_colors;
	bool Transform_from_middle;
};