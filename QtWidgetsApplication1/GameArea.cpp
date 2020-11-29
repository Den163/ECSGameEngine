#include "GameArea.h"

GameArea::GameArea(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

GameArea::~GameArea()
{
}
