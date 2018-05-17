#include "Mainwindow.h"
#include <ui_MainWindow.h>
#include "GLWidget.h"
#include<QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl= new GLWidget(this);

  m_ui->horizontalLayout_2->addWidget(m_gl);

}

MainWindow::~MainWindow()
{
  delete m_ui;
}

void MainWindow::StartSimulate()
{
  m_gl->start_simulate();
  std::cout<<"simulation started";
}

void MainWindow::Reset()
{
  m_gl->reset();
  //bring back default_particle settings
  m_ui->selectobject->setCurrentIndex(0);
  //toggled groundplane
  m_ui->checkBox_2->setCheckState(Qt::Checked);
  //bring back gravity settings
  m_ui->lineEdit->setText("-9.8");
  m_ui->lineEdit_2->setText("0.2");
  m_ui->lineEdit_3->setText("0.5");
  Set_Gravity();
  m_gl->Set_Gravity_Change_Flag();
  m_ui->checkBox_4->setChecked(true);


}
//this slots reset particles with user specified particle type
void MainWindow::Choose_ParticleType()
{
  if(m_ui->selectobject->currentIndex() == 1)
  {
  m_gl->setParticle_Type(1);
  }
  else
  {
    m_gl->Change_Back_to_Sphere();
  }
}

void MainWindow::Set_Gravity()
{
  m_gl->Set_Custom_Gravity(m_ui->lineEdit->text().toFloat());
}

void MainWindow::Gravity_change_flag()
{
  m_gl->Set_Gravity_Change_Flag();
}

void MainWindow::Add_GroundPlane()
{
  if(m_ui->checkBox_2->isChecked())
  {
  if (!(m_gl->Has_GroundPlane()))
  {
    m_gl->Add_ground_plane();
  }
  }
  if(!(m_ui->checkBox_2->isChecked()))
  {
    m_gl->Delete_ground_plane();
  }
}

void MainWindow::Delete_GroundPlane()
{
  m_gl->Delete_ground_plane();

}

void MainWindow::Set_Particle_Count()
{
  m_gl->set_particle_count((int)(m_ui->lineEdit_4->text().toInt()));
  Add_GroundPlane();
}

void MainWindow::Set_Cloth_Sim()
{
  if(m_ui->checkBox_4->isChecked())
  {
    m_gl->Activate_Cloth(true);
  }
  else
   {
    m_gl->Activate_Cloth(false);
  }
}

void MainWindow::Set_Rigid_Sim()
{
  if(m_ui->checkBox->isChecked())
  {
    m_gl->Activate_Rigid(true);
  }
  else
   {
    m_gl->Activate_Rigid(false);
  }
}

void MainWindow::set_Friction_Coefficient()
{
  float coefficient = m_ui->lineEdit_2->text().toFloat();
  m_gl->Set_Friction_Coe(coefficient);
}

void MainWindow::set_Bouncing_Coefficient()
{
  float coefficient = m_ui->lineEdit_3->text().toFloat();
  m_gl->Set_Bouncing_Coe(coefficient);
}




