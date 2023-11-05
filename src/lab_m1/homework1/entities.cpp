#include <lab_m1/homework1/entities.h>
#include <lab_m1/homework1/hw_object2D.h>
#include <lab_m1/homework1/hw_transform2D.h>

using namespace std;

MeshesCreator::MeshesCreator() {
	Mesh* mesh;
	mesh = hw_object2D::CreateRectangle("homeBase", 100, 600, glm::vec3(1, 0, 0), true, 0);
	meshes["homeBase"] = mesh;
	mesh = hw_object2D::CreateRectangle("backGround", 1800, 1000, glm::vec3(0.2, 0.2, 0.2), true, -1);
	meshes["backGround"] = mesh;
	mesh = hw_object2D::CreateSquare("cell", 150, glm::vec3(0, 1, 0.2), true, 0);
	meshes["cell"] = mesh;
	mesh = hw_object2D::CreateRomb("orangeRomb", 60, glm::vec3(1, 0.5, 0.15), 10);
	meshes["orangeRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("blueRomb", 60, glm::vec3(0.2, 0.5, 0.95), 10);
	meshes["blueRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("yellowRomb", 60, glm::vec3(1, 1, 0.35), 10);
	meshes["yellowRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("purpleRomb", 60, glm::vec3(0.45, 0.16, 0.95), 10);
	meshes["purpleRomb"] = mesh;
	mesh = hw_object2D::CreateSquare("priceSquare", 150, glm::vec3(0, 0, 0), false, 0);
	meshes["priceSquare"] = mesh;
	mesh = hw_object2D::CreateStar("priceStar", 20, 10, glm::vec3(0.6, 0.6, 0.6), true, 0);
	meshes["priceStar"] = mesh;
	mesh = hw_object2D::CreateStar("resourceStar", 20, 10, glm::vec3(0.6, 0.6, 0.6), true, 0);
	meshes["resourceStar"] = mesh;
	mesh = hw_object2D::CreateSquare("lifeSquare", 100, glm::vec3(1, 0, 0), true, 0);
	meshes["lifeSquare"] = mesh;
	mesh = hw_object2D::CreateStar("collectableStar", 60, 20, glm::vec3(0.9, 0.25, 0.95), true, 1);
	meshes["collectableStar"] = mesh;
	mesh = hw_object2D::CreateHexagon("orangeHex", 60, glm::vec3(1, 0.5, 0.15), true, 1);
	meshes["orangeHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("blueHex", 60, glm::vec3(0.2, 0.5, 0.95), true, 1);
	meshes["blueHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("yellowHex", 60, glm::vec3(1, 1, 0.35), true, 1);
	meshes["yellowHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("purpleHex", 60, glm::vec3(0.45, 0.16, 0.95), true, 1);
	meshes["purpleHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("fullHPHex", 45, glm::vec3(0.114, 0.478, 0.29), true, 2);
	meshes["fullHPHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("halfHPHex", 45, glm::vec3(0.97, 0.72, 0), true, 2);
	meshes["halfHPHex"] = mesh;
	mesh = hw_object2D::CreateHexagon("lowHPHex", 45, glm::vec3(0.97, 0.18, 0), true, 2);
	meshes["lowHPHex"] = mesh;
	mesh = hw_object2D::CreateStar("orangeStar", 45, 15, glm::vec3(1, 0.5, 0.15), true, 1);
	meshes["orangeStar"] = mesh;
	mesh = hw_object2D::CreateStar("blueStar", 45, 15, glm::vec3(0.2, 0.5, 0.95), true, 1);
	meshes["blueStar"] = mesh;
	mesh = hw_object2D::CreateStar("yellowStar", 45, 15, glm::vec3(1, 1, 0.35), true, 1);
	meshes["yellowStar"] = mesh;
	mesh = hw_object2D::CreateStar("purpleStar", 45, 15, glm::vec3(0.45, 0.16, 0.95), true, 1);
	meshes["purpleStar"] = mesh;

}

MeshesCreator& MeshesCreator::getInstance() {
	static MeshesCreator instance;
	return instance;
}

Mesh* MeshesCreator::getMesh(std::string name) {
	return meshes[name];
}

HomeBase::HomeBase() {
	this->center = glm::vec2(75, 350);
	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("homeBase"), modelMatrix);
};

HomeBase::~HomeBase() = default;

Background::Background() {
	this->center = glm::vec2(900, 500);
	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("backGround"), modelMatrix);
}

Background::~Background() = default;

Cell::Cell(int i, int j) {
	if (i == 0) {
		this->center.y = 575;
	} else if (i == 1) {
		this->center.y = 350;
	} else if (i == 2) {
		this->center.y = 125;
	}

	if (j == 0) {
		this->center.x = 225;
	} else if (j == 1) {
		this->center.x = 450;
	} else if (j == 2) {
		this->center.x = 675;
	}

	this->width = 75;
	this->heigth = 75;

	this->hitboxCenter = center;
	this->hitBoxRadius = 60;

	this->line = i;

	this->shotDelta = 2000;

	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->pressBoxCenter = glm::vec2(this->center.x, this->center.y);
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("cell"), modelMatrix);
}

Cell::~Cell() = default;

const glm::vec2& Cell::getCenter() const {
	return center;
}

bool Cell::occupy(unitType type) {
	if (this->type.has_value())
		return false;
	timer = shotDelta;
	switch (type) {
	case ORANGE:
		this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("orangeRomb"), transform2D::Translate(center.x, center.y));
		break;
	case BLUE:
		this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("blueRomb"), transform2D::Translate(center.x, center.y));
		break;
	case YELLOW:
		this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("yellowRomb"), transform2D::Translate(center.x, center.y));
		break;
	case PURPLE:
		this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("purpleRomb"), transform2D::Translate(center.x, center.y));
		break;
	}
	this->type = type;
	return true;
}

void Cell::free() {
	if (!this->type.has_value())
		return;
	this->type = {};
	objectData.pop_back();
}

std::optional<unitType> Cell::shoot(Enemy enemy, float deltaTime) {
	if (this->type.has_value() && enemy.getLine() == this->line && enemy.getType() == this->type) {
		timer += deltaTime;
		if (timer >= this->shotDelta) {
			timer = 0;
			return this->type;
		}
	}
	return {};
}

Price::Price(unitType type) {
	this->type = type;

	Mesh* romb;

	switch (type) {
	case ORANGE:
		this->squareCenter.x = 200;
		this->firstStarCenter.x = 145;
		this->cost = 1;
		romb = MeshesCreator::getInstance().getMesh("orangeRomb");
		break;
	case BLUE:
		this->squareCenter.x = 425;
		this->firstStarCenter.x = 370;
		this->cost = 2;
		romb = MeshesCreator::getInstance().getMesh("blueRomb");
		break;
	case YELLOW:
		this->squareCenter.x = 650;
		this->firstStarCenter.x = 595;
		this->cost = 2;
		romb = MeshesCreator::getInstance().getMesh("yellowRomb");
		break;
	case PURPLE:
		this->squareCenter.x = 875;
		this->firstStarCenter.x = 820;
		this->cost = 3;
		romb = MeshesCreator::getInstance().getMesh("purpleRomb");
		break;
	}

	this->firstStarCenter.y = 760;
	this->squareCenter.y = 875;
	this->pressBoxCenter = squareCenter;

	this->width = 75;
	this->heigth = 75;

	objectData.emplace_back(MeshesCreator::getInstance().getMesh("priceSquare"), transform2D::Translate(this->squareCenter.x, this->squareCenter.y));

	for (int i = 0; i < this->cost; i++) {
		objectData.emplace_back(MeshesCreator::getInstance().getMesh("priceStar"), transform2D::Translate(static_cast<float>(i) * 55 + this->firstStarCenter.x, this->firstStarCenter.y));
	}

	objectData.emplace_back(romb, transform2D::Translate(this->squareCenter.x, this->squareCenter.y));
}

Price::~Price() = default;

const unitType& Price::getUnitType() const {
	return this->type;
}

const int& Price::getCost() const {
	return this->cost;
}

Resource::Resource(int index) {
	this->firstStarCenter = glm::vec2(1100, 800);

	objectData.emplace_back(MeshesCreator::getInstance().getMesh("resourceStar"), transform2D::Translate(index * 55 + firstStarCenter.x, firstStarCenter.y));
}

Resource::~Resource() = default;

Life::Life(int index) {
	this->firstLifeCenter = glm::vec2(1130, 880);

	objectData.emplace_back(MeshesCreator::getInstance().getMesh("lifeSquare"), transform2D::Translate(index * 120 + firstLifeCenter.x, firstLifeCenter.y));
}

Life::~Life() = default;

DragRomb::DragRomb() {
	objectData.emplace_back(MeshesCreator::getInstance().getMesh("blueRomb"), transform2D::Translate(0, 0));
}

DragRomb::~DragRomb() = default;

void DragRomb::changeColor(unitType type) {
	this->type = type;
	switch (type) {
	case ORANGE:
		this->objectData[0].first = MeshesCreator::getInstance().getMesh("orangeRomb");
		cost = 1;
		break;
	case BLUE:
		this->objectData[0].first = MeshesCreator::getInstance().getMesh("blueRomb");
		cost = 2;
		break;
	case YELLOW:
		this->objectData[0].first = MeshesCreator::getInstance().getMesh("yellowRomb");
		cost = 2;
		break;
	case PURPLE:
		this->objectData[0].first = MeshesCreator::getInstance().getMesh("purpleRomb");
		cost = 3;
		break;
	}
}

void DragRomb::changePos(glm::vec2 pos) {
	this->objectData[0].second = transform2D::Translate(pos.x, pos.y);
}

const unitType& DragRomb::getUnitType() const {
	return this->type;
}

const int& DragRomb::getCost() const {
	return this->cost;
}

Collectable::Collectable(glm::vec2 center) {
	this->stars = 1;
	this->pressBoxCenter = center;
	this->heigth = 40;
	this->width = 40;
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("collectableStar"), transform2D::Translate(center.x, center.y));
}

Collectable::~Collectable() = default;

const int& Collectable::getStars() const {
	return this->stars;
}

Enemy::Enemy(unitType type, int lineIndex) {
	int y;

	if (lineIndex == 0) {
		y = 575;
	} else if (lineIndex == 1) {
		y = 350;
	} else if (lineIndex == 2) {
		y = 125;
	}

	Mesh* mesh;
	switch (type) {
	case ORANGE:
		mesh = MeshesCreator::getInstance().getMesh("orangeHex");
		break;
	case BLUE:
		mesh = MeshesCreator::getInstance().getMesh("blueHex");
		break;
	case YELLOW:
		mesh = MeshesCreator::getInstance().getMesh("yellowHex");
		break;
	case PURPLE:
		mesh = MeshesCreator::getInstance().getMesh("purpleHex");
		break;
	}

	this->currentPos = glm::vec2(1860, y);
	this->hitboxCenter = currentPos;
	this->hitBoxRadius = 60;
	this->type = type;
	this->line = lineIndex;
	this->speed = glm::vec2(-100, 0);
	this->lives = 3;
	this->finalPos = glm::vec2(100, y);

	this->objectData.emplace_back(mesh, transform2D::Translate(currentPos.x, currentPos.y));
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("halfHPHex"), transform2D::Translate(currentPos.x, currentPos.y));
}

bool Enemy::move(float deltaTime) {
	bool ret = this->Moveable::move(deltaTime);
	objectData[0].second = transform2D::Translate(currentPos.x, currentPos.y);
	objectData[1].second = transform2D::Translate(currentPos.x, currentPos.y);
	hitboxCenter = currentPos;
	return ret;
}

bool Enemy::getHit(int damage) {
	this->lives -= damage;

	switch (lives) {
	case 3:
		this->objectData[1].first = MeshesCreator::getInstance().getMesh("fullHPHex");
		break;
	case 2:
		this->objectData[1].first = MeshesCreator::getInstance().getMesh("halfHPHex");
		break;
	case 1:
		this->objectData[1].first = MeshesCreator::getInstance().getMesh("lowHPHex");
		break;
	}

	if (this->lives <= 0)
		return true;
	return  false;
}

const int& Enemy::getLine() const {
	return this->line;
}

const unitType& Enemy::getType() const {
	return this->type;
}

Projectile::Projectile(unitType type, glm::vec2 pos) {
	Mesh* mesh;
	switch (type) {
	case ORANGE:
		mesh = MeshesCreator::getInstance().getMesh("orangeStar");
		break;
	case BLUE:
		mesh = MeshesCreator::getInstance().getMesh("blueStar");
		break;
	case YELLOW:
		mesh = MeshesCreator::getInstance().getMesh("yellowStar");
		break;
	case PURPLE:
		mesh = MeshesCreator::getInstance().getMesh("purpleStar");
		break;
	}

	this->type = type;
	this->currentPos = glm::vec2(pos.x + 50, pos.y);
	this->hitboxCenter = this->currentPos;
	this->hitBoxRadius = 45;
	this->finalPos = glm::vec2(1860, this->currentPos.y);
	this->speed = glm::vec2(150, 0);
	this->angularStep = 0;
	this->angularSpeed = -2;
	this->objectData.emplace_back(mesh, transform2D::Translate(this->currentPos.x, this->currentPos.y));
}

bool Projectile::move(float deltaTime) {
	bool ret = this->Moveable::move(deltaTime);

	this->angularStep += deltaTime * angularSpeed;
	glm::mat3 	modelMat = transform2D::Translate(currentPos.x, currentPos.y);
	modelMat *= transform2D::Rotate(angularStep);

	objectData[0].second = modelMat;
	hitboxCenter = currentPos;
	return ret;
}

bool Projectile::checkCollisionAndType(Enemy& other) const {
	return this->type == other.getType() && this->checkCollision(other);
}

