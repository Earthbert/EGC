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


Homework1::Homework1()
{
}


Homework1::~Homework1()
{
}


void Homework1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = logicSpaceWidth;   // logic width
	logicSpace.height = logicSpaceHeigth;  // logic height

	CreatePermanentObjects();
}

// 2D visualization matrix
glm::mat3 Homework1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, s;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	s = min(sx, sy);
	tx = (viewSpace.width - s * logicSpace.width) / 2.0;
	ty = (viewSpace.height - s * logicSpace.height) / 2.0;

	return glm::transpose(glm::mat3(
		s, 0.0f, tx,
		0.0f, s, ty,
		0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Homework1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}


void Homework1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
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


void Homework1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Homework1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw - the left half of the window
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(1), true);

	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	DrawScene();
}

void Homework1::DrawScene()
{
	drawBackground();
	DrawUI();
}

void m1::Homework1::DrawUI()
{
	DrawObject(*homeBase);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			DrawObject(*cells[i][j]);
}

void Homework1::DrawObject(Drawable& object)
{
	auto objectData = object.getDrawData();
	for (auto& meshModelPair : objectData) {
		modelMatrix = visMatrix * meshModelPair.second;
		RenderMesh2D(meshModelPair.first, shaders["VertexColor"], modelMatrix);
	}
}


void Homework1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Homework1::OnInputUpdate(float deltaTime, int mods)
{

}


void Homework1::OnKeyPress(int key, int mods)
{
	// Add key press event
}


void Homework1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Homework1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Homework1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Homework1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Homework1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Homework1::OnWindowResize(int width, int height)
{
}

void m1::Homework1::CreatePermanentObjects()
{
	background = new Background(logicSpaceWidth, logicSpaceHeigth);
	homeBase = new HomeBase();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j] = new Cell(i, j);
}

inline void Homework1::drawBackground() {
	DrawObject(*background);
}

void Homework1::RenderMesh(Mesh* mesh, const glm::mat3& modelMatrix)
{
	RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
}
