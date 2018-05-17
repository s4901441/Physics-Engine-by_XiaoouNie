#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Emitter.h"
#include "Cloth_object.h"
#include <ngl/Camera.h>
#include <QGLWidget>



class GLWidget : public QGLWidget
{

public:
  GLWidget(QWidget *parent);
  ~GLWidget();
  inline void start_simulate(){m_startSimulate = true;}
  void reset();
  inline void setParticle_Type(int _typeIndex) {m_particleType_index = _typeIndex;}
  inline void Change_Back_to_Sphere(){m_change_back_to_sphere =1;}
  inline void Set_Gravity_Change_Flag() {m_gravity_change_flag = true;}
  inline void Set_Custom_Gravity(float _gravity){m_custom_gravity = _gravity;}
  bool Has_GroundPlane();
  void Add_ground_plane();
  void Delete_ground_plane();
  void set_particle_count(int _count);
  void Activate_Cloth(bool _bool){Cloth_Activated = _bool;}
  void Activate_Rigid(bool _bool){Rigid_Actived = _bool;}
  void Set_Friction_Coe(float _coefficient);
  void Set_Bouncing_Coe(float _coefficient);

private:
  void mouseMoveEvent(QMouseEvent *_event) override;
  void addParticles(int _type);
  void timerEvent( QTimerEvent *_event ) override;
  ngl::Mat4 m_mouseGlobalTX;
  ngl::Vec3 m_modelPos;
  void loadMatricesToShader();
  void mousePressEvent(QMouseEvent *_event) override;
  void mouseReleaseEvent(QMouseEvent *_event) override;
  void wheelEvent(QWheelEvent *_event) override;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  bool Cloth_Activated;
  bool Rigid_Actived;


  //Camera
  ngl::Camera *m_cam;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the x rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int spinXFace = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the y rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int spinYFace = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool rotate = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the Right mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool translate = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int origX = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int origY = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int origXPos = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int origYPos = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief window width
  //----------------------------------------------------------------------------------------------------------------------
  int width = 1024;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief window height
  //----------------------------------------------------------------------------------------------------------------------
  int height = 720;

  /// @brief a container for our particles
  std::unique_ptr<Emitter> m_emitter;
  /// @brief the emitter position so we can update
  ngl::Vec3 m_emitterPos;
  Cloth_object* m_object;
  //user input things
  bool m_startSimulate;
  int m_particleType_index; //modified by user: changing combobox ui to decide which type of particle to emit
  int m_change_back_to_sphere;
  float m_custom_gravity;
  bool m_gravity_change_flag;
};


//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
constexpr float INCREMENT = 0.01f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
constexpr float ZOOM = 0.1f;



#endif // GLWIDGET_H
