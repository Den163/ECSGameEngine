#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

struct GlContext
{
	QOpenGLShaderProgram* shaderProgram;
	QOpenGLFunctions* glFunctions;
};
