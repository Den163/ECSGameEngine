#pragma once

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Components/CameraFrustum.h"
#include "Components/CameraMatrices.h"
#include "Components/Transofrm.h"
#include "entt/entt.hpp"

class GLCameraRendererSystem
{
public:
	explicit GLCameraRendererSystem(
		entt::registry& registry,
		QOpenGLFunctions* glFunctions,
		QOpenGLShaderProgram* shaderProgram)
		:
		_registry(registry),
		_glFunctions(glFunctions),
		_projectionUniform(shaderProgram->uniformLocation("projection")),
		_viewUniform(shaderProgram->uniformLocation("view"))
	{
	}

public:
	void update() const
	{
		auto view = _registry.view<CameraFrustum, Transform>();
		
		for (auto entity : view)
		{
			auto [frustum, transform] = _registry.get<CameraFrustum, Transform>(entity);

			auto viewMatrix =
				glm::lookAt(transform.position, glm::vec3{0}, glm::vec3{0, 1, 0});
			auto projectionMatrix = glm::perspective(
				glm::radians(frustum.verticalFieldOfViewInDegrees),
				frustum.aspectRatio,
				frustum.nearClipPlane,
				frustum.farClipPlane);

			_glFunctions->glUniformMatrix4fv(
				_viewUniform,
				1,
				GL_FALSE,
				glm::value_ptr(viewMatrix));
			_glFunctions->glUniformMatrix4fv(
				_projectionUniform,
				1,
				GL_FALSE,
				glm::value_ptr(projectionMatrix));
		}
	}

private:
	entt::registry& _registry;
	QOpenGLFunctions* _glFunctions;
	GLuint _projectionUniform;
	GLuint _viewUniform;
};
