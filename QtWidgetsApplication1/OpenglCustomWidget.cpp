#include <OpenGLCustomWidget.h>

void OpenGLCustomWidget::initializeGL()
{
	gl = QOpenGLContext::currentContext()->functions();
	shaderProgram = new QOpenGLShaderProgram(this);
	shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.vert");
	showLog();
	shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.frag");
	showLog();
	shaderProgram->link();
	showLog();

	positionAttribute = shaderProgram->attributeLocation("position");
	modelUniform = shaderProgram->uniformLocation("model");
	viewUniform = shaderProgram->uniformLocation("view");
	projectionUniform = shaderProgram->uniformLocation("projection");

	cameraRenderer = new GLCameraRendererSystem{
		registry,
		gl,
		shaderProgram,
		projectionUniform,
		viewUniform
	};
	glMeshRenderer = new GLMeshRendererSystem{
		positionAttribute,
		registry,
		gl,
		shaderProgram
	};

	const auto camera = registry.create();
	registry.emplace<Transform>(camera);
	auto& frustum = registry.emplace<CameraFrustum>(camera);
	
	frustum.aspectRatio = 1.0f * width() / height();
	frustum.nearClipPlane = 0.1f;
	frustum.farClipPlane = 1000.f;
	frustum.verticalFieldOfViewInDegrees = 45;

	const auto meshEntity = registry.create();
	registry.emplace<Mesh>(meshEntity);
	registry.emplace<Transform>(meshEntity);
}

void OpenGLCustomWidget::paintGL()
{
	gl->glClearColor(0, 0, 0, 1);
	gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->bind();

	cameraRenderer->update();
	glMeshRenderer->update();

	std::cout << "Was painter" << std::endl;
}

void OpenGLCustomWidget::showLog() const
{
	std::cout << shaderProgram->log().toStdString() << std::endl;
}

void OpenGLCustomWidget::addVertex(glm::vec3 vertexPosition)
{
	std::cout << glm::to_string(vertexPosition) << std::endl;
	auto view = registry.view<Mesh>();
	for (auto entity : view)
	{
		auto& mesh = view.get<Mesh>(entity);
		mesh.vertices.push_back(Vertex { vertexPosition });
	}
	
	update();
}

void OpenGLCustomWidget::setCameraPosition(glm::vec3 cameraPosition)
{
	auto view = registry.view<CameraFrustum, Transform>();
	for (auto entity: view)
	{
		auto& transform = view.get<Transform>(entity);
		transform.position = cameraPosition;
	}
	
	update();
}
