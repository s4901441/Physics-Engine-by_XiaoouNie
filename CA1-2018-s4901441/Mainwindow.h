#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLWidget.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void StartSimulate();
  void Reset();
  void Choose_ParticleType();
  void Set_Gravity();
  void Gravity_change_flag();
  void Add_GroundPlane();
  void Delete_GroundPlane();
  void Set_Particle_Count();
  void Set_Cloth_Sim();
  void Set_Rigid_Sim();
  void set_Friction_Coefficient();
  void set_Bouncing_Coefficient();
private:
  Ui::MainWindow *m_ui;
  GLWidget *m_gl;
};



#endif // MAINWINDOW_H
