/*____________________________________________________________________________
  
  FILE....: main.cpp
  CREATED.: 27 February 2002
  AUTHOR..: Vincent Scheib
  
  COMMENTS: Homework assignment for Physically Based Modeling
  See http://www.scheib.net/school/259/hw3/
    
  REVISION: 
            
                                            Copyright (C) 2002, Vincent Scheib
  ____________________________________________________________________________*/

#pragma warning (disable : 4305 ) // double to float

#include <qapplication.h>
#include <qtoolbar.h>
#include <qdial.h>
#include <qbuttongroup.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qgl.h>
#include <math.h>
#include <time.h>

#include <qglvuwindow.h>
#include <stopwatch.hpp>
#include <Vec3f.hpp>
#include <mat33.hpp>
#include <GL/glut.h>

#include "floatspinbox.h"
#include "ControlPanel.h"

///////////////////////////////////////////////////////////////////////////////
// GLOBALS

QGLVUWidget *pGLVU;
ControlPanel *pControlPanel;

//simulation
static Stopwatch timer;
struct _circle
{
  float theta;  
  float thetaVelocity;  
  Vec3f worldForces;
  float mass;
} circle;
Vec3f gravity;

// GL
GLfloat light1_ambient[] =  {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat light1_diffuse[] =  {.5f, 1, 1, 1};
GLfloat light1_position[] = {-2, 2, 2, 1};

GLfloat light2_ambient[] =  {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat light2_diffuse[] =  {1, 1, .5f, 1};
GLfloat light2_position[] = {2, 2, -2, 1};

///////////////////////////////////////////////////////////////////////////////
//

void initObjects(void)
{
  timer.Start();
  
  circle.theta = 3.1415/2;
  gravity.Set(0, -9.8, 0);
}


void simulation(void)
{
  static float time_simulated = 0;
  float time_now = timer.GetTime();
  float time_passed = time_now - time_simulated;

  circle.mass = pControlPanel->FloatSpinBox_mass->doubleValue();

  circle.worldForces.Set(0,0,0);
  circle.worldForces += circle.mass * gravity;

  if (pControlPanel->PushButton_Hold_Left->isDown() ) 
  {
    circle.theta = 3.14159;
    circle.thetaVelocity = 0;
  }
  if (pControlPanel->PushButton_Hold_Up->isDown()   ) 
  {
    circle.theta = 3.14159/2;
    circle.thetaVelocity = 0;
  }    
  if (pControlPanel->PushButton_Hold_Right->isDown()) 
  {
    circle.theta = 0;
    circle.thetaVelocity = 0;
  }    

  float force_amount = pControlPanel->FloatSpinBox_force->doubleValue();
  if (pControlPanel->PushButton_Force_Left->isDown() ) circle.worldForces += Vec3f(-force_amount,0,0);
  if (pControlPanel->PushButton_Force_Up->isDown()   ) circle.worldForces += Vec3f(0,force_amount,0);
  if (pControlPanel->PushButton_Force_Right->isDown()) circle.worldForces += Vec3f(force_amount,0,0);

  float timestep = pControlPanel->SpinBox_TimeStep->value() / (float)1000;
  float dampening = 1-pControlPanel->FloatSpinBox_dampening->doubleValue();
  
  int i=0;
  while ((time_simulated < time_now) && (timestep > 0))
  {
    float acceleration = 
      - circle.worldForces.x/circle.mass*sin(circle.theta)
      + circle.worldForces.y/circle.mass*cos(circle.theta);

    circle.theta += circle.thetaVelocity * timestep;
    circle.thetaVelocity += acceleration * timestep;
    
    circle.thetaVelocity *= dampening;

    time_simulated += timestep;
    i++;
  }
}

void initCallback( QGLVUWidget* pGLVU )
{
  pGLVU->DefaultInitializeGL( pGLVU );

  glEnable(GL_CULL_FACE); 
  
  GLfloat light0_ambient[] =  {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light0_diffuse[] =  {.8f, .8f, .8f, 1.0f};
  GLfloat light0_position[] = {0, 0, 1, 1};
    
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}


void drawXYPlane(int cells = 1)
{
  glBegin(GL_QUADS);
  int x;
  int y;
  for (y=0; y<cells; y++)
  {
    for (x=0; x<cells; x++)
    {      
      float xm = 2*( x   /(float)cells)-1;
      float xM = 2*((x+1)/(float)cells)-1;
      float ym = 2*( y   /(float)cells)-1;
      float yM = 2*((y+1)/(float)cells)-1;
      
      glVertex2f( xm, ym );
      glVertex2f( xM, ym );
      glVertex2f( xM, yM );
      glVertex2f( xm, yM );
    }
  }
  glEnd();
}

void drawBox(void)
{
  int cells = 6;

  glPushMatrix();
  glTranslatef(-1,0,0);
  glRotatef(90, 0, 1, 0);
  drawXYPlane(cells);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0,-1,0);
  glRotatef(90,-1, 0, 0);
  drawXYPlane(cells);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0,0,-1);
  drawXYPlane(cells);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(1,0,0);
  glRotatef(90, 0,-1, 0);
  drawXYPlane(cells);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0,1,0);
  glRotatef(90, 1, 0, 0);
  drawXYPlane(cells);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0,0,1);
  glRotatef(180, 1, 0, 0);
  drawXYPlane(cells);
  glPopMatrix();
  
}

void drawCircle(void)
{
  const float skinny_radius = 0.05;

  glColor3f( 0.2, 0.5, 0.5);  
  glutSolidTorus(skinny_radius, 1, 32, 256);

  glPushMatrix();
  {
    glRotatef(180/3.14159*circle.theta, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glRotatef(90, 1, 0, 0);
    glColor3f( 0.2, 0.2, 0.7);  
    glutSolidTorus(skinny_radius, 2*skinny_radius, 32, 128);
  }
  glPopMatrix();
}

void drawObjects(void)
{
  const float scaledown = 0.5;
  glPushMatrix();
  glScalef(scaledown, scaledown, scaledown);
  drawCircle();
  glPopMatrix();
}

void paintCallback(QGLVUWidget* pGLVU)
{
  simulation();

  // Call BeginFrame to set up matrix stack for the current viewpoint
  // according to the user's mouse movements.
  // This call also keeps the frame rate timer up to date.
  pGLVU->BeginFrame();

  // This will indicate if there have been any OpenGL errors recently.
  // Sprinking these judiciously throughout your rendering code can 
  // be an immense help in debugging the rendering part of your code.
  pGLVU->ReportGLError("before draw");

  // Erase the screen
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  
  glEnable(GL_LIGHT2);
  glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  
  glMatrixMode(GL_MODELVIEW);
  glColor3f( 0.7, 0.5, 0.6);  
  drawBox();
  drawObjects();
    
  // EndFrame draws camera frustums if camera display is turned on.
  // See the GLVU menu for that option.
  pGLVU->EndFrame();
}

void exiting()
{
}


int main( int argc, char** argv )
{
  atexit( exiting );
  
  QApplication app( argc, argv );
  
  QGLVUWindow window;
  app.setMainWidget(&window);
  
  window.resize(800, 600);
  
  pGLVU = new QGLVUWidget(&window);
  
  QToolBar *pToolbar = new QToolBar(&window);
  window.addToolBar( pToolbar, "Controls", QMainWindow::Right, FALSE);
  
  pControlPanel = new ControlPanel(pToolbar);
  
  // Note: if you do not include the string "Qt" in your caption, then
  // the Qt non-commercial edition will prepend it with "[freeware] "
  window.Initialize(pGLVU, "[QGLVU] Simple Physics Homework - Scheib [Qt]");
  
  Vec3f ModelMin(-1,-1,-1), ModelMax(1,1,1), 
    Eye(0,0,3), LookAtCntr(0,0,0), Up(0,1,0);
  
  float Yfov    = 45;
  float Aspect  = 1;     // width over height
  float Near    = 0.01f;  // near plane dist relative to model diagonal length
  float Far     = 10.0f; // far plane distance (also relative)
  
  pGLVU->SetAllCams(ModelMin,ModelMax, Eye,LookAtCntr,Up, Yfov, 
    Aspect, Near,Far);
  /*
  Camera *setCam;
  pGLVU->SelectCam(QGLVUWidget::CAMERA_ONE);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(
    Vec3f(-0.026728f, -1.175778f, 0.170671f), 
    Vec3f(-0.009356f, -0.202340f, -0.057618f), 
    Vec3f(0.002551f, 0.228280f, 0.973592f));
  pGLVU->SelectCam(QGLVUWidget::CAMERA_TWO);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(Vec3f(0.108119, 0.223170, 0.129714), Vec3f(-0.335129, -0.650626, -0.070318), Vec3f(-0.072104, -0.187673, 0.979582));
  pGLVU->SelectCam(QGLVUWidget::CAMERA_THREE);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(Vec3f(-0.018547, -1.181103, 1.428571), Vec3f(-0.039156, -0.631921, 0.593122), Vec3f(0,0,1));
  
  pGLVU->SelectCam(QGLVUWidget::CAMERA_ONE);
  */
  pGLVU->SetInertiaEnabled(false);
  pGLVU->SetWorldNavMode(QGLVUWidget::NAV_MODE_HYPERBALL);

  // Set our custom paint function.  The paint function will be called
  // with this QGLVUWidget (pGLVU) as an argument, so the widget
  // doesn't have to be a global pointer.
  pGLVU->SetPaintGL( paintCallback );
  
  // Set a custom initialize function too.  Here we'll just change the default
  // clear color, but still do everything else the default does.
  pGLVU->SetInitializeGL( initCallback );

  initObjects();
  srand( (unsigned)time( NULL ) );  
  
  window.show();
  
  return app.exec();
}
