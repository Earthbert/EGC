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
	mesh = hw_object2D::CreateRomb("orangeRomb", 60, glm::vec3(1, 0.5, 0.15), 0);
	meshes["orangeRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("blueRomb", 60, glm::vec3(0.2, 0.5, 0.95), 0);
	meshes["blueRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("yellowRomb", 60, glm::vec3(1, 1, 0.35), 0);
	meshes["yellowRomb"] = mesh;
	mesh = hw_object2D::CreateRomb("purpleRomb", 60, glm::vec3(0.45, 0.16, 0.95), 0);
	meshes["purpleRomb"] = mesh;
	mesh = hw_object2D::CreateSquare("priceSquare", 150, glm::vec3(0, 0, 0), false, 0);
	meshes["priceSquare"] = mesh;
	mesh = hw_object2D::CreateStar("priceStar", 20, 10, glm::vec3(0.6, 0.6, 0.6), true, 0);
	meshes["priceStar"] = mesh;
	mesh = hw_object2D::CreateStar("resourceStar", 20, 10, glm::vec3(0.6, 0.6, 0.6), true, 0);
	meshes["resourceStar"] = mesh;
	mesh = hw_object2D::CreateSquare("lifeSquare", 100, glm::vec3(1, 0, 0), true, 0);
	meshes["lifeSquare"] = mesh;
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

	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(MeshesCreator::getInstance().getMesh("cell"), modelMatrix);
}

Cell::~Cell() = default;

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

	objectData.emplace_back(MeshesCreator::getInstance().getMesh("priceSquare"), transform2D::Translate(this->squareCenter.x, this->squareCenter.y));

	for (int i = 0; i < this->cost; i++) {
		objectData.emplace_back(MeshesCreator::getInstance().getMesh("priceStar"), transform2D::Translate(static_cast<float>(i) * 55 + this->firstStarCenter.x, this->firstStarCenter.y));
	}

	objectData.emplace_back(romb, transform2D::Translate(this->squareCenter.x, this->squareCenter.y));
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

Life::~Life() {}
