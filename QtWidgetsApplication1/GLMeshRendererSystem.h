#pragma once
#include <entt/entt.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

class GLMeshRendererSystem
{
public:
	GLMeshRendererSystem(
		GLuint positionLocation,
		entt::registry& registry,
		QOpenGLFunctions* glFunctions,
		QOpenGLShaderProgram* shaderProgram)
		:
		_positionLocation(positionLocation),
		_registry(registry),
		_glFunctions(glFunctions),
		_shaderProgram(shaderProgram)
	{
	}

	void update() const
	{
		auto view = _registry.view<Mesh>();
		_shaderProgram->enableAttributeArray(_positionLocation);

		for (auto entity : view)
		{
			auto& mesh = view.get<Mesh>(entity);
			auto vertices = mesh.vertices;
			const auto vertSize = vertices.size();

			if (vertSize == 0) return;

			_shaderProgram->setAttributeArray(
				_positionLocation, glm::value_ptr(vertices[0].position), 3);
			_glFunctions->glDrawArrays(GL_TRIANGLES, 0, vertSize);
		}

		_shaderProgram->disableAttributeArray(_positionLocation);
	}

private:
	GLuint _positionLocation;
	entt::registry& _registry;
	QOpenGLFunctions* _glFunctions;
	QOpenGLShaderProgram* _shaderProgram;
};
