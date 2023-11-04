#pragma once

#include <lab_m1/homework1/attributes.h>

enum starType {
	ORANGE,
	BLUE,
	PURPLE
};

class HomeBase : public Drawable {
public:
	HomeBase();
	~HomeBase();
private:
};

class Background : public Drawable {
public:
	Background(float logicSpaceWidth, float logicSpaceHeigth);
	~Background();
private:
};

class Cell : public Drawable {
public:
	Cell(int i, int j);
	~Cell();
private:
	static glm::vec2 calcCenter(int i, int j);
};

class my_class {
public:

};

