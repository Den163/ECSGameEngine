#pragma once

#include <entt/entt.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <glm/gtc/type_ptr.hpp>

#include "Components/Mesh.h"

class GLMeshRendererSystem
{
public:
	GLMeshRendererSystem(
		entt::registry& registry,
		QOpenGLFunctions* glFunctions,
		QOpenGLShaderProgram* shaderProgram)
		:
		_registry(registry),
		_glFunctions(glFunctions),
		_shaderProgram(shaderProgram),
		_positionAttribute(shaderProgram->attributeLocation("position"))
	{
	}

	void update() const
	{
		auto view = _registry.view<Mesh>();
		_shaderProgram->enableAttributeArray(_positionAttribute);

		for (auto entity : view)
		{
			auto& mesh = view.get<Mesh>(entity);
			auto& vertices = mesh.vertices;
			const auto vertSize = vertices.size();

			if (vertSize == 0) return;

			_shaderProgram->setAttributeArray(
				_positionAttribute, glm::value_ptr(vertices[0].position), 3);
			_glFunctions->glDrawArrays(GL_TRIANGLES, 0, vertSize);
		}

		_shaderProgram->disableAttributeArray(_positionAttribute);
	}

private:
	entt::registry& _registry;
	QOpenGLFunctions* _glFunctions;
	QOpenGLShaderProgram* _shaderProgram;
	GLuint _positionAttribute;
};
