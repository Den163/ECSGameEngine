#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void QtWidgetsApplication1::onAddVertexClicked() const
{
	const auto vertex = glm::vec3(
        ui.vertexXSpin->value(), 
        ui.vertexYSpin->value(), 
        ui.vertexZSpin->value()
	);

    ui.openGLWidget->addVertex(vertex);
}

void QtWidgetsApplication1::onCameraPositionSpinChanged() const
{
    const auto cameraPosition = glm::vec3(
        ui.cameraXSpin->value(),
        ui.cameraYSpin->value(),
        ui.cameraZSpin->value()
    );
	
    ui.openGLWidget->setCameraPosition(cameraPosition);
}
