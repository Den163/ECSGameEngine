#pragma once

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>


#include "BaseSystem.h"
#include "Components/CameraFrustum.h"
#include "Components/CameraMatrices.h"
#include "Components/CoreGlVariables.h"
#include "Components/GlContext.h"
#include "Components/ScreenSettings.h"
#include "Components/Transofrm.h"
#include "entt/entt.hpp"

class GLCameraRendererSystem : public BaseSystem
{
public:
	void init(entt::registry & registry) override
	{
		const auto camera = registry.create();
		registry.emplace<Transform>(camera);
		auto& frustum = registry.emplace<CameraFrustum>(camera);

		frustum.nearClipPlane = 0.1f;
		frustum.farClipPlane = 1000.f;
		frustum.verticalFieldOfViewInDegrees = 45;
	}
	
	void update(entt::registry & registry) override
	{
		auto cameraView = registry.view<CameraFrustum, Transform>();
		
		for (auto entity : cameraView)
		{
			auto [frustum, transform] = cameraView.get<CameraFrustum, Transform>(entity);

			auto viewMatrix =
				glm::lookAt(transform.position, glm::vec3{0}, glm::vec3{0, 1, 0});
			auto projectionMatrix = glm::perspective(
				glm::radians(frustum.verticalFieldOfViewInDegrees),
				frustum.aspectRatio,
				frustum.nearClipPlane,
				frustum.farClipPlane);

			addViewProjectionMatrices(registry, viewMatrix, projectionMatrix);
		}
	}
private:
	static void addViewProjectionMatrices(
		entt::registry & registry, glm::mat4x4 & viewMatrix, glm::mat4x4 & projectionMatrix)
	{
		auto glView = registry.view<GlContext, CoreGlVariables, ScreenSettings>();

		for (auto entity : glView)
		{
			auto [context, vars, screenSettings] = 
				glView.get<GlContext, CoreGlVariables, ScreenSettings>(entity);
			auto* gl = context.glFunctions;

			gl->glUniformMatrix4fv(
				vars.viewUniform,
				1,
				GL_FALSE,
				glm::value_ptr(viewMatrix));
			gl->glUniformMatrix4fv(
				vars.projectionUniform,
				1,
				GL_FALSE,
				glm::value_ptr(projectionMatrix));
		}
	}
};
