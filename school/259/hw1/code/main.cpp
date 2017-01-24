/*____________________________________________________________________________
  
  FILE....: main.cpp
  CREATED.: 13 February 2002
  AUTHOR..: Vincent Scheib
  
  COMMENTS: Homework assignment for Physically Based Modeling
            See http://www.scheib.net/school/259/hw1/
            
  REVISION: 
            
                                            Copyright (C) 2002, Vincent Scheib
  ____________________________________________________________________________*/


#include <qapplication.h>
#include <qtoolbar.h>
#include <qstring.h>
#include <qdial.h>
#include <qbuttongroup.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qgl.h>
#include <math.h>
#include <GL/glut.h>

#include <qglvuwindow.h>
#include <stopwatch.hpp>

#include "mycontrolpanelimpl.h"
#include "SimpleQueue.hpp"

///////////////////////////////////////////////////////////////////////////////
// GLOBALS

QGLVUWidget *pGLVU;
MyControlPanel *pControlPanel;

//simulation
Vec3f CannonDirection;
SimpleQueue<Vec3f> CannonShots;
float CannonMass;
SimpleQueue<Vec3f> SpringMassPositions;
float SpringConstant;
float SpringMassMass;
float WindResistance;

///////////////////////////////////////////////////////////////////////////////
//

void integrateCannonBall(float time_step, const Vec3f &pos, const Vec3f &vel, Vec3f &outVel, Vec3f &outAcl)
{
  outVel  = vel;
  outAcl  = Vec3f(0,0,-9.8);    // gravity
  outAcl -= vel*WindResistance/CannonMass; // wind resistance
}

void integrateSpring(float time_step, const Vec3f &pos, const Vec3f &vel, Vec3f &outVel, Vec3f &outAcl)
{
  outVel  = vel;
  outAcl  = Vec3f(0,0,-9.8);                    // gravity
  outAcl -= SpringConstant*pos/SpringMassMass;  // spring force
}

void clearShots(void)
{
  while (CannonShots.getSize() > 0)
    CannonShots.pop();
}



void simulation(void)
{
  // STATIC INIT
  static Stopwatch timer;
  static float time_now = 0;
  static float time_simulated = 0;
  static bool  push_button_down = false;
  if (timer.GetNumStarts() == 0)
  {
    timer.Start();
    SpringMassPositions.push(Vec3f(0,0,0)); 
    SpringMassPositions.push(Vec3f(0,0,0)); 
  }
  // end STATIC INIT

  bool firing;

  time_now = timer.GetTime();

  // When debugging, make reasonable frame rate
  if (time_now-time_simulated > 0.1) 
    time_simulated = time_now - 0.05;

  if ( 1 > pControlPanel->DialElevation->value())
    pControlPanel->DialElevation->setValue(1);
  
  if ( 90 < pControlPanel->DialElevation->value())
    pControlPanel->DialElevation->setValue(90);

  // READ VALUES FROM USER INTERFACE
  float dir          = pControlPanel->DialDirection->value() * 3.14159 / 180;
  float elv          = pControlPanel->DialElevation->value() * 3.14159 / 180;
  int integrator     = pControlPanel->ButtonGroupIntegrator->id(pControlPanel->ButtonGroupIntegrator->selected());
  float time_step    = pControlPanel->SpinBoxTimeStep->value() / 1000.0;
  CannonMass         = pControlPanel->SpinBoxCannonMass->value() / 1000.0;
  float CannonPowder = pControlPanel->SpinBoxPowder->value();
  WindResistance     = pControlPanel->SpinBoxAirFriction->value() / 1000.0;
  SpringConstant     = pControlPanel->SpinBoxSpring->value();
  SpringMassMass     = pControlPanel->SpinBoxSpringMass->value();
  if (pControlPanel->PushButtonSpringReset->isDown()) 
  { 
    SpringMassPositions.pop(); 
    SpringMassPositions.pop(); 
    SpringMassPositions.push(Vec3f(0,0,0)); 
    SpringMassPositions.push(Vec3f(0,0,0)); 
  }
  
  if (!push_button_down) //push-buttons (must lock so we only detect one click)
  {
    push_button_down   = 
      pControlPanel->PushButtonFire->isDown()        ||
      pControlPanel->PushButtonClearShots->isDown()  ||
      pControlPanel->PushButtonCamSpring->isDown()   ||
      pControlPanel->PushButtonCamCannon1->isDown()  ||
      pControlPanel->PushButtonCamCannon2->isDown()  ||
      pControlPanel->PushButtonCamOutside->isDown();
    
    firing = pControlPanel->PushButtonFire->isDown();
    if (pControlPanel->PushButtonClearShots->isDown())    clearShots();
    if (pControlPanel->PushButtonCamSpring->isDown())     pGLVU->SelectCam(QGLVUWidget::CAMERA_ONE);
    if (pControlPanel->PushButtonCamCannon1->isDown())    pGLVU->SelectCam(QGLVUWidget::CAMERA_TWO);
    if (pControlPanel->PushButtonCamCannon2->isDown())    pGLVU->SelectCam(QGLVUWidget::CAMERA_THREE);
    if (pControlPanel->PushButtonCamOutside->isDown())    pGLVU->SelectCam(QGLVUWidget::CAMERA_FOUR);
  }
  else
  {
    push_button_down   = 
      pControlPanel->PushButtonFire->isDown()        ||
      pControlPanel->PushButtonClearShots->isDown()  ||
      pControlPanel->PushButtonCamSpring->isDown()   ||
      pControlPanel->PushButtonCamCannon1->isDown()  ||
      pControlPanel->PushButtonCamCannon2->isDown()  ||
      pControlPanel->PushButtonCamOutside->isDown();
    firing = false;
  }
  // end READ VALUES FROM USER INTERFACE
  
  
  CannonDirection = Vec3f( sinf(dir), cosf(dir), 0);
  CannonDirection *= cosf(elv);
  CannonDirection += Vec3f(0,0, sin(elv));
  
  if (firing)
  {
    float CannonInitialVelocity = sqrt(2 * CannonPowder / CannonMass); // assumed 1 meter application of force
    CannonShots.push(Vec3f(0,0,5) + CannonDirection*3);
    CannonShots.push(CannonDirection * CannonInitialVelocity);
  }
  
  switch(integrator)
  {
  case 0: // Euler
    {
      while (time_simulated < time_now)
      {
        int n = CannonShots.getSize();
        assert (n % 2 == 0);
        int i;
        for(i=0; i<n; i+=2)
        {
          Vec3f pos = CannonShots.top(); CannonShots.pop();
          Vec3f vel = CannonShots.top(); CannonShots.pop();
          
          Vec3f f_pos;
          Vec3f f_vel;
          
          integrateCannonBall(time_step, pos, vel, f_pos, f_vel);

          pos = pos + f_pos*time_step;
          vel = vel + f_vel*time_step;
         
          // bounce
          if ((pos.z < 0) && (vel.z < 0))
            vel &= Vec3f(0.8, 0.8, -0.5);

          CannonShots.push(pos);
          CannonShots.push(vel);
        }
        
        if (SpringMassPositions.getSize() == 2)
        {
          Vec3f pos = SpringMassPositions.top(); SpringMassPositions.pop();
          Vec3f vel = SpringMassPositions.top(); SpringMassPositions.pop();
          
          Vec3f f_pos;
          Vec3f f_vel;
          
          integrateSpring(time_step, pos, vel, f_pos, f_vel);
          pos = pos + f_pos*time_step;
          vel = vel + f_vel*time_step;
          
          SpringMassPositions.push(pos);
          SpringMassPositions.push(vel);
        }

        time_simulated += time_step;
      }
    }
    break;
  case 1: // Midpoint
    {
      while (time_simulated < time_now)
      {
        int n = CannonShots.getSize();
        assert (n % 2 == 0);
        int i;
        for(i=0; i<n; i+=2)
        {
          Vec3f pos = CannonShots.top(); CannonShots.pop();
          Vec3f vel = CannonShots.top(); CannonShots.pop();
          
          Vec3f k1_pos;
          Vec3f k1_vel;
          integrateCannonBall(time_step, pos, vel, k1_pos, k1_vel);
          k1_pos *= time_step;
          k1_vel *= time_step;
          
          Vec3f k2_pos;
          Vec3f k2_vel;
          integrateCannonBall(time_step, pos+0.5*k1_pos, vel+0.5*k1_vel, k2_pos, k2_vel);
          k2_pos *= time_step;
          k2_vel *= time_step;
          
          pos = pos + k2_pos;
          vel = vel + k2_vel;
          
          // bounce
          if ((pos.z < 0) && (vel.z < 0))
            vel &= Vec3f(0.8, 0.8, -0.5);
          
          CannonShots.push(pos);
          CannonShots.push(vel);
        }
        
        if (SpringMassPositions.getSize() == 2)
        {
          Vec3f pos = SpringMassPositions.top(); SpringMassPositions.pop();
          Vec3f vel = SpringMassPositions.top(); SpringMassPositions.pop();
          
          Vec3f k1_pos;
          Vec3f k1_vel;
          integrateSpring(time_step, pos, vel, k1_pos, k1_vel);
          k1_pos *= time_step;
          k1_vel *= time_step;
          
          Vec3f k2_pos;
          Vec3f k2_vel;
          integrateSpring(time_step, pos+0.5*k1_pos, vel+0.5*k1_vel, k2_pos, k2_vel);
          k2_pos *= time_step;
          k2_vel *= time_step;
          
          pos = pos + k2_pos;
          vel = vel + k2_vel;
          
          SpringMassPositions.push(pos);
          SpringMassPositions.push(vel);
        }
        
        time_simulated += time_step;
      }
    }
    break;
  case 2: // RK4
    {
      while (time_simulated < time_now)
      {
        int n = CannonShots.getSize();
        assert (n % 2 == 0);
        int i;
        for(i=0; i<n; i+=2)
        {
          Vec3f pos = CannonShots.top(); CannonShots.pop();
          Vec3f vel = CannonShots.top(); CannonShots.pop();
          
          Vec3f k1_pos;
          Vec3f k1_vel;
          integrateCannonBall(time_step, pos, vel, k1_pos, k1_vel);
          k1_pos *= time_step;
          k1_vel *= time_step;
          
          Vec3f k2_pos;
          Vec3f k2_vel;
          integrateCannonBall(time_step, pos+0.5*k1_pos, vel+0.5*k1_vel, k2_pos, k2_vel);
          k2_pos *= time_step;
          k2_vel *= time_step;
          
          Vec3f k3_pos;
          Vec3f k3_vel;
          integrateCannonBall(time_step, pos+0.5*k2_pos, vel+0.5*k2_vel, k3_pos, k3_vel);
          k3_pos *= time_step;
          k3_vel *= time_step;
          
          Vec3f k4_pos;
          Vec3f k4_vel;
          integrateCannonBall(time_step, pos+k3_pos, vel+k3_vel, k4_pos, k4_vel);
          k4_pos *= time_step;
          k4_vel *= time_step;
          
          pos = pos + k1_pos/6 + k2_pos/3 + k3_pos/3 + k4_pos/6;
          vel = vel + k1_vel/6 + k2_vel/3 + k3_vel/3 + k4_vel/6;
          
          // bounce
          if ((pos.z < 0) && (vel.z < 0))
            vel &= Vec3f(0.8, 0.8, -0.5);
          
          CannonShots.push(pos);
          CannonShots.push(vel);
        }
        
        if (SpringMassPositions.getSize() == 2)
        {
          Vec3f pos = SpringMassPositions.top(); SpringMassPositions.pop();
          Vec3f vel = SpringMassPositions.top(); SpringMassPositions.pop();
          
          Vec3f k1_pos;
          Vec3f k1_vel;
          integrateSpring(time_step, pos, vel, k1_pos, k1_vel);
          k1_pos *= time_step;
          k1_vel *= time_step;
          
          Vec3f k2_pos;
          Vec3f k2_vel;
          integrateSpring(time_step, pos+0.5*k1_pos, vel+0.5*k1_vel, k2_pos, k2_vel);
          k2_pos *= time_step;
          k2_vel *= time_step;
          
          Vec3f k3_pos;
          Vec3f k3_vel;
          integrateSpring(time_step, pos+0.5*k2_pos, vel+0.5*k2_vel, k3_pos, k3_vel);
          k3_pos *= time_step;
          k3_vel *= time_step;
          
          Vec3f k4_pos;
          Vec3f k4_vel;
          integrateSpring(time_step, pos+k3_pos, vel+k3_vel, k4_pos, k4_vel);
          k4_pos *= time_step;
          k4_vel *= time_step;
          
          pos = pos + k1_pos/6 + k2_pos/3 + k3_pos/3 + k4_pos/6;
          vel = vel + k1_vel/6 + k2_vel/3 + k3_vel/3 + k4_vel/6;
          
          SpringMassPositions.push(pos);
          SpringMassPositions.push(vel);
        }
        
        time_simulated += time_step;
      }
    }
    break;
  case 3: // Implicit
    {
      while (time_simulated < time_now)
      {
        int n = CannonShots.getSize();
        assert (n % 2 == 0);
        int i;
        for(i=0; i<n; i+=2)
        {
          Vec3f pos = CannonShots.top(); CannonShots.pop();
          Vec3f vel = CannonShots.top(); CannonShots.pop();
          
          vel = (vel + time_step*Vec3f(0,0,-9.8))/(1+time_step*WindResistance/CannonMass);
          pos = pos + vel*time_step;
          
          // bounce
          if ((pos.z < 0) && (vel.z < 0))
            vel &= Vec3f(0.8, 0.8, -0.5);
          
          CannonShots.push(pos);
          CannonShots.push(vel);
        }
        
        if (SpringMassPositions.getSize() == 2)
        {
          Vec3f pos = SpringMassPositions.top(); SpringMassPositions.pop();
          Vec3f vel = SpringMassPositions.top(); SpringMassPositions.pop();
          
          vel = (vel - time_step*SpringConstant/SpringMassMass*pos + time_step*Vec3f(0,0,-9.8))/(1+time_step*time_step*SpringConstant/SpringMassMass);
          pos = pos + vel*time_step;
          
          SpringMassPositions.push(pos);
          SpringMassPositions.push(vel);
        }
        
        time_simulated += time_step;
      }
    }
    break;
  default:
    qDebug("Integrator %d not implemented\n", integrator);
  }
}

void initCallback( QGLVUWidget* pGLVU )
{
  pGLVU->DefaultInitializeGL( pGLVU );
  
  GLfloat light0_ambient[] =  {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light0_diffuse[] =  {.9f, .9f, .99f, 1.0f};
  GLfloat light0_position[] = {.9f, .9f, 1.9f, 0.0f};
  
  GLfloat light1_ambient[] =  {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat light1_diffuse[] =  {.8f, .97f, 0.97f, 1.0f};
  GLfloat light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};

  GLfloat light2_position[] = {-1.0f, 1.0f, -2.0f, 0.0f};
  
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

  glEnable(GL_LIGHT2);
  glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
}


void drawGroundPlane(void)
{

    

  glBegin( GL_QUADS );
  {
    glColor3f( 0.0f, 0.4f, 0.2f);  
    glVertex3f( -1,-1, 0 );
    glVertex3f(  1,-1, 0 );
    glVertex3f(  1, 1, 0 );
    glVertex3f( -1, 1, 0 );
  }
  glEnd();
  
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
  { 
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glLineWidth(2);
    
    glColor4f( 0, 1.0f, 0.4f, 0.5);  
    glBegin( GL_LINES );
    {
      float f;
      for (f=-1.0; f< 1.01; f+=0.1f)
      {
        glVertex3f( f, -1, 0 ); 
        glVertex3f( f,  1, 0 );
      }
      
      for (f=-1.0; f< 1.01; f+=0.1f)
      {
        glVertex3f( -1, f, 0 ); 
        glVertex3f(  1, f, 0 );
      }
    }
    glEnd();
  }
  glPopAttrib();
  
  glBegin( GL_QUADS );
  {
    glColor3f( 0.0f, 0.4f, 0.2f);  
    glVertex3f( -1,-1, 0 );
    glVertex3f( -1, 1, 0 );
    glColor3f( 0.40f, 0.3f, 0.0f);  
    glVertex3f( -1, 1, -1);
    glVertex3f( -1,-1, -1);
    
    glColor3f( 0.0f, 0.4f, 0.2f);  
    glVertex3f( -1, 1, 0 );
    glVertex3f(  1, 1, 0 );
    glColor3f( 0.40f, 0.3f, 0.0f);  
    glVertex3f(  1, 1, -1);
    glVertex3f( -1, 1, -1);
    
    glColor3f( 0.0f, 0.4f, 0.2f);  
    glVertex3f(  1, 1, 0 );
    glVertex3f(  1,-1, 0 );
    glColor3f( 0.40f, 0.3f, 0.0f);  
    glVertex3f(  1,-1, -1);
    glVertex3f(  1, 1, -1);
    
    glColor3f( 0.0f, 0.4f, 0.2f);  
    glVertex3f(  1,-1, 0 );
    glVertex3f( -1,-1, 0 );
    glColor3f( 0.40f, 0.3f, 0.0f);  
    glVertex3f( -1,-1, -1);
    glVertex3f(  1,-1, -1);
    
  }
  glEnd();
  
}

void drawCannon(void)
{
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
  { 
    glColor3f( 0.40f, 0.3f, 0.0f);  
    glutSolidCone(0.02, 0.05, 32, 2);

    glColor3f( 0.90f, 0.3f, 0.3f);  
    glPushMatrix();
    glTranslatef(0,0, 0.05);
    glRotatef(90, 1, 0, 0);
    glRotatef(pControlPanel->DialDirection->value(), 0, -1, 0);
    glRotatef(pControlPanel->DialElevation->value(), 1, 0, 0);
    glTranslatef(0,0, -0.03);
    glutSolidCone(0.003, 0.05, 32, 2);
    glPopMatrix();
  }
  glPopAttrib();
}

void drawShots(void)
{
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
  { 
    int i;
    for (i=0; i<CannonShots.getSize(); i+=2)
    {
      glPushMatrix();
      glScalef(0.01, 0.01, 0.01);
      Vec3f pos = CannonShots.top(); CannonShots.pop();
      Vec3f vel = CannonShots.top(); CannonShots.pop();
      glTranslatef(pos.x, pos.y, pos.z);
      CannonShots.push(pos);
      CannonShots.push(vel);
      glColor3f( 0.30f, 0.5f, 0.9f);  
      glutSolidSphere(0.25, 32, 16);
      glTranslatef(0,0, -pos.z);
      glScalef(1,1,0.2);
      glColor3f(0,0,0);
      glutSolidSphere(0.25, 32, 3);
      glPopMatrix();
    }
  }
  glPopAttrib();
}

void drawSpring(void)
{
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
  { 
    glPushMatrix();
    glTranslatef(0,-.9,.2);
    glScalef(0.01, 0.01, 0.01);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor3f(.8,.6,.1);
    glBegin(GL_QUADS);
    glVertex3f(-1,-1,0);
    glVertex3f( 1,-1,0);
    glVertex3f( 1, 1,0);
    glVertex3f(-1, 1,0);
    glEnd();
    glDisable(GL_BLEND);
    
    if (SpringMassPositions.getSize() == 2)
    {
      Vec3f pos = SpringMassPositions.top(); SpringMassPositions.pop();
      Vec3f vel = SpringMassPositions.top(); SpringMassPositions.pop();
      glColor3f( 0.7f, 0.7f, 0.8f);  
      glLineWidth(2);
      glBegin(GL_LINES);
      glVertex3f(0,0,0);
      glVertex3f(pos.x, pos.y, pos.z);
      glEnd();

      glEnable(GL_BLEND);
      glLineWidth(1);
      glColor3f(.8,.6,.1);
      glBegin(GL_LINES);
      glVertex3f(0,0,0);
      glVertex3f(0, 0, -500);
      glEnd();
      glDisable(GL_BLEND);
      
      glTranslatef(pos.x, pos.y, pos.z);
      glColor3f( 0.7f, 0.7f, 0.1f);  
      glutSolidSphere(0.1, 32, 16);
      SpringMassPositions.push(pos);
      SpringMassPositions.push(vel);
    }
    glPopMatrix();
  }
  glPopAttrib();
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

  glMatrixMode(GL_MODELVIEW);
  glColor3f( 1, 1, 1);  
  drawGroundPlane();
  drawCannon();
  drawShots();
  drawSpring();

  // EndFrame draws camera frustums if camera display is turned on.
  // See the GLVU menu for that option.
  pGLVU->EndFrame();
}

void exiting()
{
  while (CannonShots.getSize() > 0)
  {
    CannonShots.pop();
  }
  while (SpringMassPositions.getSize() > 0)
  {
    SpringMassPositions.pop();
  }
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
  
  pControlPanel = new MyControlPanel(pToolbar);
  
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
  Camera *setCam;
  pGLVU->SelectCam(QGLVUWidget::CAMERA_ONE);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(
    Vec3f(-0.026728, -1.175778, 0.170671), 
    Vec3f(-0.009356, -0.202340, -0.057618), 
    Vec3f(0.002551, 0.228280, 0.973592));
  pGLVU->SelectCam(QGLVUWidget::CAMERA_TWO);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(Vec3f(0.108119, 0.223170, 0.129714), Vec3f(-0.335129, -0.650626, -0.070318), Vec3f(-0.072104, -0.187673, 0.979582));
  pGLVU->SelectCam(QGLVUWidget::CAMERA_THREE);
  setCam = pGLVU->GetCurrentCam();
  setCam->LookAt(Vec3f(-0.018547, -1.181103, 1.428571), Vec3f(-0.039156, -0.631921, 0.593122), Vec3f(0,0,1));
  
  pGLVU->SelectCam(QGLVUWidget::CAMERA_ONE);
  
  pGLVU->SetInertiaEnabled(false);

  // Set our custom paint function.  The paint function will be called
  // with this QGLVUWidget (pGLVU) as an argument, so the widget
  // doesn't have to be a global pointer.
  pGLVU->SetPaintGL( paintCallback );
  
  // Set a custom initialize function too.  Here we'll just change the default
  // clear color, but still do everything else the default does.
  pGLVU->SetInitializeGL( initCallback );
  
  
  window.show();
  
  return app.exec();
}
