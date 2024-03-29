#include "homework2.h"

#include <iostream>

#include "colors.h"
#include "consts.h"
#include "components/text_renderer.h"
#include "entities/entity.h"
#include "entities/ground.h"

m1::Homework2::Homework2() = default;

m1::Homework2::~Homework2() = default;

void m1::Homework2::Init() {
	projectionMatrix = glm::perspective(RADIANS(100), window->props.aspectRatio, 0.01f, 200.0f);
	camera = HW2_Camera();

	minimapViewMatrix = glm::lookAt(glm::vec3(0, 50, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
	minimapProjectionMatrix = glm::ortho(-HW2_PLANE_LENGTH / 2 - HW2_MINIMAP_BORDER, HW2_PLANE_LENGTH / 2 + HW2_MINIMAP_BORDER, -HW2_PLANE_LENGTH / 2 - HW2_MINIMAP_BORDER, HW2_PLANE_LENGTH / 2 + HW2_MINIMAP_BORDER, 0.01f, 200.0f);

	CreateShaders();
	CreateMeshes();
	CreateEntities();
}

void m1::Homework2::FrameStart() {
	glClearColor(RGB_SKY_BLUE.x, RGB_SKY_BLUE.y, RGB_SKY_BLUE.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void m1::Homework2::Update(float deltaTimeSeconds) {
	gameOverTimer -= deltaTimeSeconds;
	if (gameOverTimer < 0) {
		lostGame = true;
		timeLimit = true;
	};
	if (lostGame) {
		if (explosions.empty()) {
			std::cout << "------------GAME OVER------------" << std::endl;
			if (timeLimit) {
				std::cout << "Score: " << score << std::endl;
			} else {
				std::cout << "YOUR TANK GOT DESTROYED" << std::endl;
			}
			Exit();
		} else {
			explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [&](Explosion& explosion) {
				return explosion.update(deltaTimeSeconds);
				}), explosions.end());
		}
		RenderEntities();
		return;
	}
	CreateEnemies(deltaTimeSeconds);
	UpdateEntities(deltaTimeSeconds);
	CheckCollisions(deltaTimeSeconds);
	RenderEntities();
	RenderMinimap();
}

void m1::Homework2::FrameEnd() {}

void m1::Homework2::OnInputUpdate(float deltaTime, int mods) {
	if (lostGame)
		return;

	// Tank movement
	if (window->KeyHold(GLFW_KEY_W)) {
		playerTank.moveForward(deltaTime);
		camera.Move(deltaTime * HW2_TANK_SPEED, this->playerTank.getTankDirection());
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		playerTank.rotateLeft(deltaTime);
		camera.RotateThirdPerson_OY(deltaTime * HW2_TANK_ANGULAR_SPEED);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		playerTank.moveBackward(deltaTime);
		camera.Move(-deltaTime * HW2_TANK_SPEED, this->playerTank.getTankDirection());
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		playerTank.rotateRight(deltaTime);
		camera.RotateThirdPerson_OY(-deltaTime * HW2_TANK_ANGULAR_SPEED);
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
	if (lostGame)
		return;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		constexpr float sensivity = 0.001f;
		camera.RotateThirdPerson_OX(sensivity * static_cast<float>(-deltaY));
		camera.RotateThirdPerson_OY(sensivity * static_cast<float>(-deltaX));
	} else {
		constexpr float sensivity = 0.003f;
		if (deltaX > 0 && abs(deltaX) < 200)
			playerTank.rotateTurretRight(sensivity * static_cast<float>(deltaX));
		else if (abs(deltaX) < 200)
			playerTank.rotateTurretLeft(sensivity * static_cast<float>(-deltaX));
	}
}

void m1::Homework2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	if (lostGame)
		return;

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		const auto missile = playerTank.shoot();
		if (missile.has_value()) {
			missiles.push_back(missile.value());
		}
	}
}

void m1::Homework2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void m1::Homework2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void m1::Homework2::OnWindowResize(int width, int height) { SimpleScene::OnWindowResize(width, height); }

void m1::Homework2::RenderEntities() {
	RenderObject(ground);
	RenderObject(playerTank);

	std::for_each(missiles.begin(), missiles.end(), [&](Missile& missile) {
		RenderObject(missile);
		});

	std::for_each(houses.begin(), houses.end(), [&](House& house) {
		RenderObject(house);
		});

	std::for_each(explosions.begin(), explosions.end(), [&](Explosion& explosion) {
		RenderObject(explosion);
		});

	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		RenderObject(enemyTank);
		});
}

void m1::Homework2::UpdateEntities(float deltaTimeSeconds) {
	playerTank.update(deltaTimeSeconds);

	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [&](Missile& missile) {
		return missile.travel(deltaTimeSeconds);
		}), missiles.end());

	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		const auto result = enemyTank.updateEnemyTank(deltaTimeSeconds);
		if (result.has_value()) {
			missiles.push_back(result.value());
		}
		});

	explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [&](Explosion& explosion) {
		return explosion.update(deltaTimeSeconds);
		}), explosions.end());
}

void m1::Homework2::CheckCollisions(float deltaTimeSeconds) {

	// PlayerTank - Borders
	std::for_each(borders.begin(), borders.end(), [&](Border& border) {
		const auto result = playerTank.checkCollision(border);
		if (result.has_value()) {
			playerTank.getPushed(result.value());
			camera.Move(glm::length(result.value()), -(result.value()));
		}
		});

	// PlayerTank - Houses
	std::for_each(houses.begin(), houses.end(), [&](House& house) {
		const auto result = playerTank.checkCollision(house);
		if (result.has_value()) {
			playerTank.getPushed(result.value());
			camera.Move(glm::length(result.value()), -(result.value()));
		}
		});

	// Missile - Houses
	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [&](Missile& missile) {
		if (houses.empty())
			return false;
		return std::any_of(houses.begin(), houses.end(), [&](House& house) {
			const auto result = missile.checkCollision(house);
			if (result.has_value()) {
				explosions.emplace_back(missile.explode());
				return true;
			}
			return false;
			});
		}), missiles.end());

	// PlayerTank - Missiles
	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [&](Missile& missile) {
		const auto result = playerTank.checkCollision(missile);
		if (result.has_value()) {
			explosions.emplace_back(missile.explode());
			auto hitResult = playerTank.takeDamage();
			if (hitResult.has_value()) {
				explosions.emplace_back(hitResult.value());
				lostGame = true;
			}
			return true;
		}
		return false;
		}), missiles.end());

	// EnemyTanks - Borders
	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		std::for_each(borders.begin(), borders.end(), [&](Border& border) {
			const auto result = enemyTank.checkCollision(border);
			if (result.has_value()) {
				enemyTank.getPushed(result.value());
			}
			});
		});

	// EnemyTanks - Houses
	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		std::for_each(houses.begin(), houses.end(), [&](House& house) {
			const auto result = enemyTank.checkCollision(house);
			if (result.has_value()) {
				enemyTank.getPushed(result.value());
			}
			});
		});

	// EnemyTanks - PlayerTank
	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		const auto result = enemyTank.checkCollision(playerTank);
		if (result.has_value()) {
			enemyTank.getPushed(-(result.value() / 2.0f));
			playerTank.getPushed((result.value() / 2.0f));
			camera.Move(glm::length(result.value() / 2.0f), -(result.value()));
		}
		});

	// EnemyTanks - EnemyTanks
	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& otherEnemyTank) {
			if (&enemyTank == &otherEnemyTank)
				return;
			const auto result = enemyTank.checkCollision(otherEnemyTank);
			if (result.has_value()) {
				enemyTank.getPushed(-(result.value() / 2.0f));
				otherEnemyTank.getPushed((result.value() / 2.0f));
			}
			});
		});

	// EnemyTanks - Missiles
	std::for_each(enemyTanks.begin(), enemyTanks.end(), [&](EnemyTank& enemyTank) {
		missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [&](Missile& missile) {
			const auto result = enemyTank.checkCollision(missile);
			if (result.has_value()) {
				explosions.emplace_back(missile.explode());
				auto hitResult = enemyTank.takeDamage();
				if (hitResult.has_value()) {
					explosions.emplace_back(hitResult.value());
					score += 10;
				}
				return true;
			}
			return false;
			}), missiles.end());
		});
}

void m1::Homework2::CreateEnemies(float deltaTimeSeconds) {
	enemyTimer += deltaTimeSeconds;
	if (enemyTimer > HW2_SPAWN_ENEMY_COOLDOWN) {
		enemyTimer = 0;

		glm::vec3 center;
		center.x = generator.getRandomFloat(-(HW2_PLANE_LENGTH / 2) + HW2_TANK_RADIUS, (HW2_PLANE_LENGTH / 2) - HW2_TANK_RADIUS);
		center.y = 0;
		center.z = generator.getRandomFloat(-(HW2_PLANE_LENGTH / 2) + HW2_TANK_RADIUS, (HW2_PLANE_LENGTH / 2) - HW2_TANK_RADIUS);

		enemyTanks.emplace_back(playerTank, center);
	}
}

void m1::Homework2::RenderObject(Entity& entity) {
	for (auto& renderInfo : entity.getRenderInfo()) {
		if (renderInfo.shader_name == HW2_BASIC_SHADER)
			RenderUsingBasicShader(meshes[renderInfo.mesh_name], renderInfo.model_matrix, renderInfo.color);
		else if (renderInfo.shader_name == HW2_TANK_SHADER) {
			const int health = dynamic_cast<Tank*>(&entity)->getHealth();
			RenderUsingBasicShader(meshes[renderInfo.mesh_name], renderInfo.model_matrix, renderInfo.color, health);
		}
	}
}

void m1::Homework2::RenderUsingBasicShader(Mesh* mesh, const glm::mat4& modelMatrix, const glm::vec3& color, const int health) {
	const Shader* shader = shaders[HW2_BASIC_SHADER];

	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	GLint location = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->program, "model_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix;
	if (renderMinimap)
		viewMatrix = minimapViewMatrix;
	else
		viewMatrix = camera.GetViewMatrix();
	location = glGetUniformLocation(shader->program, "view_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glm::mat4 projectMatrix;
	if (renderMinimap)
		projectMatrix = minimapProjectionMatrix;
	else
		projectMatrix = projectionMatrix;
	location = glGetUniformLocation(shader->program, "projection_matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectMatrix));

	location = glGetUniformLocation(shader->program, "health");
	glUniform1i(location, health);

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
		Mesh* mesh = new Mesh(HW2_HOUSE_MESH);
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void m1::Homework2::CreateEntities() {
	ground = Ground();
	minimapBg = MinimapBg();
	playerTank = PlayerTank(glm::vec4(0));

	// Create Houses
	{
		const int numHouses = generator.getRandomInt(HW2_MIN_HOUSES, HW2_MAX_HOUSES);

		for (int i = 0; i < numHouses;) {
			const float x = generator.getRandomFloat(-(HW2_PLANE_LENGTH / 2) + HW2_MAX_HOUSE_SCALE, (HW2_PLANE_LENGTH / 2) - HW2_MAX_HOUSE_SCALE);
			const float z = generator.getRandomFloat(-(HW2_PLANE_LENGTH / 2) + HW2_MAX_HOUSE_SCALE, (HW2_PLANE_LENGTH / 2) - HW2_MAX_HOUSE_SCALE);

			const float scaleX = generator.getRandomFloat(HW2_MIN_HOUSE_SCALE, HW2_MAX_HOUSE_SCALE);
			const float scaleY = generator.getRandomFloat(HW2_MIN_HOUSE_SCALE, HW2_MAX_HOUSE_SCALE);
			const float scaleZ = generator.getRandomFloat(HW2_MIN_HOUSE_SCALE, HW2_MAX_HOUSE_SCALE);

			houses.emplace_back(glm::vec2(x, z), glm::vec3(scaleX, scaleY, scaleZ));
			i++;
		}
	}

	// Create Invisible Borders
	{
		borders.emplace_back(glm::vec3(0, 0, HW2_PLANE_LENGTH / 2 + HW2_BOUNDRY / 2), HW2_PLANE_LENGTH, HW2_BOUNDRY);
		borders.emplace_back(glm::vec3(0, 0, -(HW2_PLANE_LENGTH / 2 + HW2_BOUNDRY / 2)), HW2_PLANE_LENGTH, HW2_BOUNDRY);
		borders.emplace_back(glm::vec3(HW2_PLANE_LENGTH / 2 + HW2_BOUNDRY / 2, 0, 0), HW2_BOUNDRY, HW2_PLANE_LENGTH);
		borders.emplace_back(glm::vec3(-(HW2_PLANE_LENGTH / 2 + HW2_BOUNDRY / 2), 0, 0), HW2_BOUNDRY, HW2_PLANE_LENGTH);
	}
}

void m1::Homework2::RenderMinimap() {
	renderMinimap = true;

	const auto resolution = window->GetResolution();
	const int minimapLenght = glm::min(resolution.x, resolution.y) / HW2_MINIMAP_PROPORTION;

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(HW2_MINIMAP_BORDER, resolution.y - HW2_MINIMAP_BORDER - minimapLenght,
		minimapLenght, minimapLenght);

	RenderObject(minimapBg);
	RenderEntities();

	renderMinimap = false;
}
