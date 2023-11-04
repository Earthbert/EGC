#pragma once

#include <lab_m1/homework1/attributes.h>

enum unitType{
	ORANGE,
	BLUE,
	YELLOW,
	PURPLE
};

class HomeBase : public Drawable {
public:
	HomeBase();
	~HomeBase();
private:
	glm::vec2 center;
};

class Background : public Drawable {
public:
	Background(float logicSpaceWidth, float logicSpaceHeigth);
	~Background();
private:
	glm::vec2 center;
};

class Cell : public Drawable {
public:
	Cell(int i, int j);
	~Cell();
private:
	glm::vec2 center;
};

class RombPrice : public Drawable {
public:
	RombPrice(unitType type);
	~RombPrice();
private:
	glm::vec2 squareCenter;
	glm::vec2 firstStarCenter;
	unitType type;
	int cost;
};

