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

class Enemy : public Drawable, public HasHitbox, public Moveable {
public:
	Enemy();
	Enemy(unitType type, int lineIndex);
	~Enemy();

	bool move(float deltaTime) override;
	bool getHit(int damage);
	const int& getLine() const;
	const unitType& getType() const;

	bool update(float deltaTime);
private:
	float scale = 1;
	bool animation = false;

	int lives;
	unitType type;
	int line;
};


class Cell : public Drawable, public Clickable, public HasHitbox {
public:
	Cell();
	Cell(int i, int j);
	~Cell();
	const glm::vec2& getCenter() const;
	bool occupy(unitType type);
	void free();
	std::optional<unitType> shoot(Enemy& enemy);
	bool validCollision(Enemy& enemy) const;

	void update(float deltaTime);
private:
	float scale = 1;
	bool animation = false;

	glm::vec2 center;
	float shotDelta;
	float timer;
	int line;
	std::optional<unitType> type = {};
};

class Price : public Drawable, public Clickable {
public:
	Price();
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
	Resource();
	Resource(int index);
	~Resource();
private:
	glm::vec2 firstStarCenter;
};

class Life : public Drawable {
public:
	Life();
	Life(int index);
	~Life();
private:
	glm::vec2 firstLifeCenter;
};

class Defender : public Drawable {
public:
	Defender();
	~Defender();

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
	~Collectable() override;
	const int& getStars() const;
private:
	int stars;
};

class Projectile : public Drawable, public HasHitbox, public Moveable {
public:
	Projectile(unitType type, glm::vec2 pos);
	bool move(float deltaTime) override;
	bool validCollision(Enemy& enemy);
	const int& getDamage() const;

private:
	unitType type;
	int damage;
	float angularSpeed;
	float angularStep;
};

class GoldenGun : public Drawable, public Clickable {
public:
	GoldenGun(glm::vec2 center);
	~GoldenGun() override;

	bool checkTimeLeft(float deltaTime);
private:
	float timer;
	float timerDelta;
};