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
	mesh = hw_object2D::CreateRomb("orangeRomb", 60, glm::vec3(1, 0.5, 0.15), 2);
	meshes["orangeRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("blueRomb", 60, glm::vec3(0.2, 0.5, 0.95), 2);
	meshes["blueRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("yellowRomb", 60, glm::vec3(1, 1, 0.35), 2);
	meshes["yellowRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("purpleRomb", 60, glm::vec3(0.45, 0.16, 0.95), 2);
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
