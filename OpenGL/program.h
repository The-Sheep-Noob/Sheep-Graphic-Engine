#pragma once
#include "shapes.h"

class Program {
public:
	void renderShapes();
	inline static std::vector<Object*> sub_objects;
	void onStartup();
	void onUpdate();
	void clearObjects();
};
