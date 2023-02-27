#pragma once
#include "object.h"
#include <vector>
#include <string>


namespace Shapes {
	extern void renderShapes();
	extern std::vector<Object*> sub_objects;
	extern void main();
}
// extern keyword = tell compiler that the var is defined somewhere else
class Square : Object {
private :
	bool texture_changed;
	bool color_changed;
	bool vertexbuffer_changed;
	void updateTexture();
	void updateColors();
	void updateRotation();
	void updateVertexBuffer();
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
	void setPositions(int XY);
	void setPositions(int X, int Y);
	void setPositions(int X, int Y, int Z);
	void setRotation(int Z);
	void setRotations(int X, int Y, int Z);
	Square();
	int R;
	int G;
	int B;
	int A;
	int X;
	int Y;
	int Z_index;
	int X_rotate;
	int Y_rotate;
	int Z_rotate;
	int Size;
	std::string Texture;
};