#pragma once

#include <lab_m1/homework1/attributes.h>
#include <optional>

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
	const glm::vec2& getCenter() const;
	bool occupy(unitType type);
	void free();
private:
	glm::vec2 center;
	std::optional<unitType> type = {};
};

class Price : public Drawable, public Clickable {
public:
	Price(unitType type);
	~Price();
	const unitType& getUnitType() const;
	const int& getCost() const;
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

class DragRomb : public Drawable {
public:
	DragRomb();
	~DragRomb();

	void changeColor(unitType type);
	void changePos(glm::vec2 pos);

	const unitType& getUnitType() const;
	const int& getCost() const;
private:
	unitType type;
	int cost;
};

class Collectable : public Drawable, public Clickable {
public:
	Collectable(glm::vec2 center);
	~Collectable();
	const int& getStars() const;
private:
	int stars;
};

class Enemy : public Drawable, public HasHitbox, public Moveable {
public:
	Enemy(int lineIndex, unitType type);

	bool move(float deltaTime) override;
	bool getHit(int damage);
	const int& getLine() const;
	const unitType& getType() const;
private:
	int lives;
	unitType type;
	int line;
};
