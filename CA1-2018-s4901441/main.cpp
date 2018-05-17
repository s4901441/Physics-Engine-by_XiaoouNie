#include "Mainwindow.h"

#include <QtGui/QGuiApplication>
#include "CollidePlane.h"
#include "BoudingSphere.h"
#include "ui_MainWindow.h"
#include <iostream>

int main(int argc, char **argv)
{

  QApplication app (argc, argv);
  QSurfaceFormat format;
  format.setSamples(4);

  format.setMajorVersion(4);
  format.setMinorVersion(5);

  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);


  MainWindow w;
  w.show();


  return app.exec();
}
