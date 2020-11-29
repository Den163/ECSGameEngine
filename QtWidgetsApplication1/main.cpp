#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "w", stdin);
	
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
	
    w.show();
    return QApplication::exec();
}
