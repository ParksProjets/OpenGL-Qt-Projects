#include <QApplication>

#include "controller.h"
#include "defaults.h"
#include "gui/mainwindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	MainWindow window;

	Controller controller(
			&window,
			window.GetGLWidgetPtr(),
			defaults::ISOVALUE,
			defaults::RADIUS,
			defaults::SCALE_WEIGHT,
			defaults::RICCI_FACTOR);

	window.show();

	return app.exec();
}
