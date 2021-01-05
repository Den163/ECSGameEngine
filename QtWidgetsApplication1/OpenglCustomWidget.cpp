#include <OpenglCustomWidget.h>

#include "Components/GlContext.h"
#include "Components/GlWidgetInfo.h"
#include "Systems/CameraAspectRatioSystem.h"
#include "Systems/GLMeshRendererSystem.h"
#include "Systems/InitGlSystem.h"
#include "Systems/SystemsContainer.h"

OpenGLCustomWidget::OpenGLCustomWidget(QWidget* parent)
: QOpenGLWidget(parent), systemsContainer(SystemsContainer{
	registry,
	{
		new InitGlSystem {},
		new CameraAspectRatioSystem {},
		new GLMeshRendererSystem {},
		new GLCameraRendererSystem {}
	}
})
{
}

void OpenGLCustomWidget::initializeGL()
{
	const auto meshEntity = registry.create();
	registry.emplace<Mesh>(meshEntity);
	registry.emplace<Transform>(meshEntity);

	systemsContainer.init();
	
	auto glView = registry.view<GlContext>();

	for (auto glEntity : glView)
	{
		auto& glWidgetInfo = registry.emplace<GlWidgetInfo>(glEntity);
		auto& screenSettings = registry.emplace<ScreenSettings>(glEntity);

		glWidgetInfo.glWidget = this;
		screenSettings.width = static_cast<float>(width());
		screenSettings.height = static_cast<float>(height());
	}
}

void OpenGLCustomWidget::paintGL()
{
	auto glView = registry.view<GlContext, GlWidgetInfo>();
	for (auto glEntity : glView)
	{
		auto [ctx, glWidgetInfo] = glView.get<GlContext, GlWidgetInfo>(glEntity);
		auto* gl = ctx.glFunctions;
		auto* shaderProgram = ctx.shaderProgram;

		if (glWidgetInfo.glWidget != this) continue;

		gl->glClearColor(0, 0, 0, 1);
		gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->bind();
	}

	systemsContainer.update();

	std::cout << "Was painted" << std::endl;
}

void OpenGLCustomWidget::keyPressEvent(QKeyEvent* keyEvent)
{
	auto keyText = keyEvent->text();

	// TODO Add key press handling
}

void OpenGLCustomWidget::addVertex(glm::vec3 vertexPosition)
{
	std::cout << glm::to_string(vertexPosition) << std::endl;
	const auto view = registry.view<Mesh>();
	if (view.empty()) return;

	const auto firstEntity = view[0];
	auto& mesh = view.get<Mesh>(firstEntity);
	mesh.vertices.push_back(Vertex{vertexPosition});

	update();
}

void OpenGLCustomWidget::setCameraPosition(glm::vec3 cameraPosition)
{
	auto view = registry.view<CameraFrustum, Transform>();
	for (auto entity : view)
	{
		auto& transform = view.get<Transform>(entity);
		transform.position = cameraPosition;
	}

	update();
}
