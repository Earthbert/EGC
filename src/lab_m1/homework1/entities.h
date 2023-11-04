#pragma once

#include <lab_m1/homework1/attributes.h>

enum unitType {
	ORANGE,
	BLUE,
	YELLOW,
	PURPLE
};

class MeshesCreator {
public:
	static MeshesCreator& getInstance();
	Mesh* getMesh(std::string name);
	MeshesCreator(MeshesCreator&) = delete;
	void operator=(MeshesCreator const&) = delete;
private:
	MeshesCreator();

	std::unordered_map<std::string, Mesh*> meshes;
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
	Background();
	~Background();
private:
	glm::vec2 center;
};

class Cell : public Drawable, public Clickable {
public:
	Cell(int i, int j);
	~Cell();
private:
	glm::vec2 center;

};

class Price : public Drawable, public Clickable {
public:
	Price(unitType type);
	~Price();
	const unitType& getUnitType();
	const int& getCost();
private:
	glm::vec2 squareCenter;
	glm::vec2 firstStarCenter;
	unitType type;
	int cost;
};

class Resource : public Drawable {
public:
	Resource(int index);
	~Resource();
private:
	glm::vec2 firstStarCenter;
};

class Life : public Drawable {
public:
	Life(int index);
	~Life();
private:
	glm::vec2 firstLifeCenter;
};

class DragRomb : public Drawable{
public:
	DragRomb();
	~DragRomb();

	void changeColor(unitType type);
	void changePos(glm::vec2 pos);

	const unitType& getUnitType() const;
private:
	unitType type;
};
