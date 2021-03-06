#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>
#include <iostream>
#include <tuple>
#include <utility>
#include <QKeyEvent>

#include "Systems/GLCameraRendererSystem.h"
#include "Systems/GLMeshRendererSystem.h"
#include "entt/entt.hpp"
#include "Systems/SystemsContainer.h"

class OpenGLCustomWidget final : public QOpenGLWidget
{
public:
	explicit OpenGLCustomWidget(QWidget* parent);

public slots:
	void addVertex(glm::vec3 vertexPosition);
	void setCameraPosition(glm::vec3 cameraPosition);

protected:
	void initializeGL() override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent* keyEvent) override;

private:
	GLCameraRendererSystem* cameraRenderer = nullptr;
	GLMeshRendererSystem* glMeshRenderer = nullptr;
	entt::registry registry;
	SystemsContainer systemsContainer;
	
};
