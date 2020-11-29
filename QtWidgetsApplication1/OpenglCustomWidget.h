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

#include "GLCameraRendererSystem.h"
#include "GLMeshRendererSystem.h"
#include "entt/entt.hpp"

class OpenGLCustomWidget final : public QOpenGLWidget
{
public:
	explicit OpenGLCustomWidget(QWidget* parent) : QOpenGLWidget(parent) {}

public slots:
	void addVertex(glm::vec3 vertexPosition);
	void setCameraPosition(glm::vec3 cameraPosition);

protected:
	void initializeGL() override;
	void paintGL() override;

private:
	void showLog() const;
	
	QOpenGLShaderProgram* shaderProgram = nullptr;
	QOpenGLFunctions* gl = nullptr;
	std::vector<glm::vec3> vertices {0};
	glm::vec3 cameraPosition {0};

	GLuint positionAttribute = 0;
	GLuint modelUniform = 0;
	GLuint viewUniform = 0;
	GLuint projectionUniform = 0;

	GLCameraRendererSystem* cameraRenderer = nullptr;
	GLMeshRendererSystem* glMeshRenderer = nullptr;
	entt::registry registry;
};
