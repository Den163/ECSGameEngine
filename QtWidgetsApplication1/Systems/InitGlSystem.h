#pragma once

#include <iostream>
#include <ostream>

#include "BaseSystem.h"
#include "Components/CoreGlVariables.h"
#include "Components/GlContext.h"
#include "Components/GlWidgetInfo.h"
#include "entt/entt.hpp"

class InitGlSystem : public BaseSystem
{
public:
	void init(entt::registry & registry) override
	{
		const auto glEntity = registry.create();
		auto& glContext = registry.emplace<GlContext>(glEntity);
		auto* gl = glContext.glFunctions = QOpenGLContext::currentContext()->functions();
		auto* shaderProgram = glContext.shaderProgram = new QOpenGLShaderProgram();


		shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/Shaders/vertex.vert");
		showLog(shaderProgram);
		shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/fragment.frag");
		showLog(shaderProgram);
		shaderProgram->link();
		showLog(shaderProgram);

		auto& glVars = registry.emplace<CoreGlVariables>(glEntity);

		glVars.positionAttribute = shaderProgram->attributeLocation("position");
		glVars.modelUniform = shaderProgram->uniformLocation("model");
		glVars.viewUniform = shaderProgram->uniformLocation("view");
		glVars.projectionUniform = shaderProgram->uniformLocation("projection");
	}

private:
	static void showLog(QOpenGLShaderProgram* shaderProgram)
	{
		std::cout << shaderProgram->log().toStdString() << std::endl;
	}
};
