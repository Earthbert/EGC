#include "homework2.h"

#include "colors.h"
#include "consts.h"
#include "entities/entity.h"
#include "entities/ground.h"

m1::Homework2::Homework2() = default;

m1::Homework2::~Homework2() = default;

void m1::Homework2::Init() {
	projectionMatrix = glm::perspective(RADIANS(100), window->props.aspectRatio, 0.01f, 200.0f);
	camera = HW2_Camera();

	CreateShaders();
	CreateMeshes();
	CreateEntities();
}

void m1::Homework2::FrameStart() {
	glClearColor(RGB_GRAY.x, RGB_GRAY.y, RGB_GRAY.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void m1::Homework2::Update(float deltaTimeSeconds) {
	RenderObject(ground);
	RenderObject(playerTank);
	DrawCoordinateSystem(camera.GetViewMatrix(), projectionMatrix);
}

void m1::Homework2::FrameEnd() {}

void m1::Homework2::OnInputUpdate(float deltaTime, int mods) {
	// Tank movement
	if (window->KeyHold(GLFW_KEY_W)) {
		playerTank.moveForward(deltaTime);
		camera.Move(deltaTime * this->playerTank.getTankSpeed(), this->playerTank.getTankDirection());
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		playerTank.rotateLeft(deltaTime);
		camera.RotateThirdPerson_OY(deltaTime * this->playerTank.getTankAngularSpeed());
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		playerTank.moveBackward(deltaTime);
		camera.Move(-deltaTime * this->playerTank.getTankSpeed(), this->playerTank.getTankDirection());
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		playerTank.rotateRight(deltaTime);
		camera.RotateThirdPerson_OY(-deltaTime * this->playerTank.getTankAngularSpeed());
	}
	// Zoom in/out
	if (window->KeyHold(GLFW_KEY_E)) {
		camera.Zoom(deltaTime);
	}
	if (window->KeyHold(GLFW_KEY_Q)) {
		camera.Zoom(-deltaTime);
	}
}

void m1::Homework2::OnKeyPress(int key, int mods) {}

void m1::Homework2::OnKeyRelease(int key, int mods) {}

void m1::Homework2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	constexpr float sensivity = 0.001f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->GetSpecialKeyState() == 0) {
			camera.RotateThirdPerson_OX(sensivity * static_cast<float>(-deltaY));
			camera.RotateThirdPerson_OY(sensivity * static_cast<float>(-deltaX));
		}
	} else {
		if (deltaX > 0)
			playerTank.rotateTurretRight(sensivity * static_cast<float>(deltaX));
		else
			playerTank.rotateTurretLeft(sensivity * static_cast<float>(-deltaX));
	}
}

void m1::Homework2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void m1::Homework2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void m1::Homework2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void m1::Homework2::OnWindowResize(int width, int height) { SimpleScene::OnWindowResize(width, height); }

void m1::Homework2::RenderObject(Entity& entity) {
	for (auto& renderInfo : entity.getRenderInfo()) {
		if (renderInfo.shader_name == HW2_BASIC_SHADER)
			RenderUsingBasicShader(meshes[renderInfo.mesh_name], renderInfo.model_matrix, renderInfo.color);
	}
}

void m1::Homework2::RenderUsingBasicShader(Mesh* mesh, const glm::mat4& modelMatrix, const glm::vec3& color) {
	const Shader* shader = shaders[HW2_BASIC_SHADER];

	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	GLint location = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->program, "model_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	location = glGetUniformLocation(shader->program, "view_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	location = glGetUniformLocation(shader->program, "projection_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Homework2::CreateShaders() {
	{
		Shader* shader = new Shader(HW2_BASIC_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "homework2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "homework2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void m1::Homework2::CreateMeshes() {
	{
		Mesh* mesh = new Mesh(HW2_GROUND_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_TRACK_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "track.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_TURRET_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "turret.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_BODY_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "body.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_CANNON_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "cannon.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_BALL_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh(HW2_BUILDING_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void m1::Homework2::CreateEntities() {
	ground = Ground();
	playerTank = PlayerTank(glm::vec4(0));
}