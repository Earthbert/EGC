#pragma once

#include <lab_m1/homework1/attributes.h>

class HomeBase : public Drawable
{
public:
	HomeBase();
	~HomeBase();
private:
};

class Background : public Drawable
{
public:
	Background(int logicSpaceWidth, int logicSpaceHeigth);
	~Background();
private:
};

class Cell : public Drawable
{
public:
	Cell(int i, int j);
	~Cell();
private:
	glm::vec2 calcCenter(int i, int j);
};

