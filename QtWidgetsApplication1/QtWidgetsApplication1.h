#pragma once

#include <QtWidgets/QMainWindow>
#include <glm/vec3.hpp>
#include "ui_QtWidgetsApplication1.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1Class ui{};

private slots:
    void onAddVertexClicked() const;
    void onCameraPositionSpinChanged() const;
};
