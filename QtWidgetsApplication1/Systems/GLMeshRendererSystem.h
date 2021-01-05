#pragma once

#include <entt/entt.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <glm/gtc/type_ptr.hpp>
#include "BaseSystem.h"

#include "Components/Mesh.h"

class GLMeshRendererSystem : public BaseSystem
{
public:
	void update(entt::registry & registry) override
	{
		auto glView = registry.view<GlContext, CoreGlVariables>();
		auto view = registry.view<Mesh>();

		for (auto glEntity : glView)
		{
			auto [context, glVars] = glView.get<GlContext, CoreGlVariables>(glEntity);
			auto* shaderProgram = context.shaderProgram;
			auto* gl = context.glFunctions;
			const auto positionAttribute = glVars.positionAttribute;
			
			shaderProgram->enableAttributeArray(positionAttribute);

			for (auto meshEntity : view)
			{
				auto& mesh = view.get<Mesh>(meshEntity);
				auto& vertices = mesh.vertices;
				const auto vertSize = vertices.size();

				if (vertSize == 0) return;

				shaderProgram->setAttributeArray(
					positionAttribute, glm::value_ptr(vertices[0].position), 3);
				gl->glDrawArrays(GL_TRIANGLES, 0, vertSize);
			}

			shaderProgram->disableAttributeArray(positionAttribute);
		}
	}
};
