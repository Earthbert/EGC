#include "lab_m1/homework1/attributes.h"
#include "lab_m1/homework1/entities.h"
#include "lab_m1/Homework1/Homework1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Homework1/hw_transform2D.h"
#include "lab_m1/Homework1/hw_object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Homework1::Homework1() :
	uniTime(0, 3),
	uniX(40, 1760),
	uniY(40, 960),
	uniThree(0, 2),
	uniUnit(ORANGE, PURPLE),
	uni20(1, 20)
{};


Homework1::~Homework1() = default;


void Homework1::Init() {
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = 1800;   // logic width
	logicSpace.height = 1000;  // logic height

	std::random_device rd;
	rng.seed(rd());

	CreatePermanentObjects();
}

// 2D visualization matrix
glm::mat3 Homework1::VisualizationTransf2D() const {
	float sx = viewSpace.width / logicSpace.width;
	float sy = viewSpace.height / logicSpace.height;
	float s = min(sx, sy);
	float tx = (viewSpace.width - s * logicSpace.width) / 2.0;
	float ty = (viewSpace.height - s * logicSpace.height) / 2.0;

	return glm::transpose(glm::mat3(
		s, 0.0f, tx,
		0.0f, s, ty,
		0.0f, 0.0f, 1.0f));
}

void Homework1::SetViewportArea(glm::vec3 colorColor, bool clear) const {
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}


void Homework1::FrameStart() {
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Homework1::CheckCollisions() {
	for (auto& cellLine : cells)
		for (auto& cell : cellLine)
			for (auto& enemy : enemies)
				if (cell.validCollision(enemy)) {
					cell.free();
				}

	for (auto iterP = projectiles.begin(); iterP != projectiles.end();) {
		bool increment = true;
		for (auto iterE = enemies.begin(); iterE != enemies.end();) {
			if (iterP->validCollision(*iterE)) {
				if (iterE->getHit(iterP->getDamage())) {
					dyingEnemies.emplace_back(*iterE);
					iterE = enemies.erase(iterE);
				}
				iterP = projectiles.erase(iterP);
				increment = false;
				break;
			}
			++iterE;
		}
		if (increment)
			++iterP;
	}

}


void Homework1::UpdateEntities(float deltaTime) {
	for (auto iterE = dyingEnemies.begin(); iterE != dyingEnemies.end();) {
		if (iterE->update(deltaTime))
			iterE = dyingEnemies.erase(iterE);
		else
			++iterE;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j].update(deltaTime);

	for (auto iter = goldenGuns.begin(); iter != goldenGuns.end();) {
		if (iter->checkTimeLeft(deltaTime)) {
			iter = goldenGuns.erase(iter);
		} else
			++iter;
	}
}


void Homework1::Update(float deltaTimeSeconds) {
	const glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw - the left half of the window
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(glm::vec3(1), true);

	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D();

	CreateRandomEntities(deltaTimeSeconds);

	MoveObjects(deltaTimeSeconds);

	CheckCollisions();

	UpdateEntities(deltaTimeSeconds);

	DrawScene();
}

void Homework1::CreateRandomEntities(float deltaTime) {
	// Collectables
	collectableTimer += deltaTime;
	if (collectableTimer >= collectableDelta) {
		for (int i = 0; i < 3; i++)
			collectables.emplace_back(glm::vec2(uniX(rng), uniY(rng)));
		collectableTimer = 0;
		collectableDelta = uniTime(rng) + 3;
		if (uni20(rng) == 20) {
			goldenGuns.emplace_back(glm::vec2(uniX(rng), uniY(rng)));
		}
	}

	// Enemies
	enemyTimer += deltaTime;
	if (enemyTimer >= enemyDelta) {
		enemies.emplace_back(static_cast<unitType>(uniUnit(rng)), uniThree(rng));
		enemyTimer = 0;
		enemyDelta = uniTime(rng) + 2;
	}

	// Shooters
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (Enemy& enemy : enemies) {
				auto projectileType = cells[i][j].shoot(enemy);
				if (projectileType.has_value()) {
					projectiles.emplace_back(projectileType.value(), cells[i][j].getCenter());
				}
			}

}

void Homework1::DrawScene() {
	DrawBackground();
	DrawUI();
	DrawLiveElements();
}

void m1::Homework1::DrawUI() {
	DrawObject(homeBase);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			DrawObject(cells[i][j]);

	for (int i = 0; i < 4; i++)
		DrawObject(rombPrices[i]);

	for (int i = 0; i < gameState.numStars; ++i) {
		DrawObject(resources[i]);
	}

	for (int i = 0; i < gameState.numLives; ++i) {
		DrawObject(lives[i]);
	}

	if (dragingRomb)
		DrawObject(dragRomb);
}

void Homework1::DrawLiveElements() {
	for (Collectable& collectable : collectables)
		DrawObject(collectable);

	for (Enemy& enemy : enemies)
		DrawObject(enemy);

	for (Projectile& projectile : projectiles)
		DrawObject(projectile);

	for (Enemy& enemy : dyingEnemies)
		DrawObject(enemy);

	for (GoldenGun &goldenGun : goldenGuns)
		DrawObject(goldenGun);
}

void Homework1::DrawObject(Drawable& object) {
	auto objectData = object.getDrawData();
	for (auto& meshModelPair : objectData) {
		modelMatrix = visMatrix * meshModelPair.second;
		RenderMesh2D(meshModelPair.first, shaders["VertexColor"], modelMatrix);
	}
}


void Homework1::FrameEnd() {}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Homework1::OnInputUpdate(float deltaTime, int mods) {

}


void Homework1::OnKeyPress(int key, int mods) {
	// Add key press event
}


void Homework1::OnKeyRelease(int key, int mods) {
	// Add key release event
}


void Homework1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	glm::vec2 logicCoord = calcLogicSpaceCoord(mouseX, mouseY);
	// Add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		dragRomb.changePos(logicCoord);
	}
}


void Homework1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	// Add mouse button press event
	glm::vec2 logicCoord = calcLogicSpaceCoord(mouseX, mouseY);

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		for (Price& rombPrice : rombPrices) {
			if (rombPrice.checkClick(logicCoord)) {
				if (rombPrice.getCost() <= gameState.numStars) {
					dragingRomb = true;
					dragRomb.changeColor(rombPrice.getUnitType());
					dragRomb.changePos(logicCoord);
				}
				break;
			}
		}

		for (auto iter = collectables.begin(); iter != collectables.end();) {
			if (iter->checkClick(logicCoord)) {
				gameState.numStars = min(gameState.numStars + iter->getStars(), maxStars);
				iter = collectables.erase(iter);
			} else
				++iter;
		}

		for (auto iter = goldenGuns.begin(); iter != goldenGuns.end();) {
			if (iter->checkClick(logicCoord)) {
				for (auto &enemy : enemies) {
					enemy.getHit(3);
				}
				dyingEnemies.insert(dyingEnemies.begin(), enemies.begin(), enemies.end());
				enemies.clear();
				iter = goldenGuns.erase(iter);
			} else
				++iter;
		}
	}

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (cells[i][j].checkClick(logicCoord)) {
					cells[i][j].free();
				}
	}

}


void Homework1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	// Add mouse button release event
	glm::vec2 logicCoord = calcLogicSpaceCoord(mouseX, mouseY);

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (cells[i][j].checkClick(logicCoord)) {
					if (dragingRomb && cells[i][j].occupy(dragRomb.getUnitType()))
						gameState.numStars -= dragRomb.getCost();
					break;
				}

		dragingRomb = false;
	}
}


void Homework1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}


void Homework1::OnWindowResize(int width, int height) {}

void m1::Homework1::CreatePermanentObjects() {
	background = Background();
	homeBase = HomeBase();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j] = Cell(i, j);

	rombPrices[0] = Price(ORANGE);
	rombPrices[1] = Price(BLUE);
	rombPrices[2] = Price(YELLOW);
	rombPrices[3] = Price(PURPLE);

	for (int i = 0; i < maxStars; ++i) {
		resources[i] = Resource(i);
	}

	for (int i = 0; i < maxLives; ++i) {
		lives[i] = Life(i);
	}

	dragRomb = Defender();
}

void Homework1::MoveObjects(float deltaTime) {
	for (auto iter = enemies.begin(); iter != enemies.end();) {
		if (iter->move(deltaTime)) {
			gameState.numLives--;
			if (gameState.numLives == 0) {
				this->Exit();
			}
			iter = enemies.erase(iter);
		} else
			++iter;
	}

	for (auto iter = projectiles.begin(); iter != projectiles.end();) {
		if (iter->move(deltaTime)) {
			iter = projectiles.erase(iter);
		} else
			++iter;
	}
}

inline void Homework1::DrawBackground() {
	DrawObject(background);
}

glm::vec2 Homework1::calcLogicSpaceCoord(int x, int y) {
	y = viewSpace.height - y;

	glm::mat3 visMat = VisualizationTransf2D();
	glm::mat3 invMat = glm::inverse(visMat);
	glm::vec3 logicCoord = invMat * glm::vec3(x, y, 1);

	return glm::vec2(logicCoord.x, logicCoord.y);
}

