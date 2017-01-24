/****************************************************************************
** Form interface generated from reading ui file '.\mycontrolpanel.ui'
**
** Created: Thu Feb 14 13:45:24 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef MYCONTROLPANELBASE_H
#define MYCONTROLPANELBASE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QButtonGroup;
class QDial;
class QFrame;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;
class QSpinBox;
class QTabWidget;

class MyControlPanelBase : public QWidget
{ 
    Q_OBJECT

public:
    MyControlPanelBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MyControlPanelBase();

    QTabWidget* TabWidget2;
    QWidget* tab;
    QFrame* Frame8;
    QFrame* Frame6_2;
    QDial* DialDirection;
    QLabel* TextLabel1_2_3;
    QFrame* Frame7_2;
    QDial* DialElevation;
    QLabel* TextLabel1_2_2_2;
    QFrame* Frame7;
    QGroupBox* GroupBox2_3;
    QSpinBox* SpinBoxPowder;
    QGroupBox* GroupBox2_2;
    QSpinBox* SpinBoxCannonMass;
    QGroupBox* GroupBox2_3_2;
    QSpinBox* SpinBoxAirFriction;
    QFrame* Frame6;
    QPushButton* PushButtonFire;
    QPushButton* PushButtonClearShots;
    QWidget* tab_2;
    QGroupBox* GroupBox3;
    QSpinBox* SpinBoxSpringMass;
    QGroupBox* GroupBox4;
    QSpinBox* SpinBoxSpring;
    QPushButton* PushButtonSpringReset;
    QWidget* tab_3;
    QPushButton* PushButtonCamSpring;
    QPushButton* PushButtonCamCannon1;
    QPushButton* PushButtonCamCannon2;
    QPushButton* PushButtonCamOutside;
    QButtonGroup* ButtonGroupIntegrator;
    QRadioButton* RadioButton3;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButtonEuler;
    QRadioButton* RadioButton4;
    QGroupBox* GroupBoxTimeStep;
    QSpinBox* SpinBoxTimeStep;

protected:
    QVBoxLayout* MyControlPanelBaseLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* Frame8Layout;
    QVBoxLayout* Frame6_2Layout;
    QVBoxLayout* Frame7_2Layout;
    QHBoxLayout* Frame7Layout;
    QGridLayout* GroupBox2_3Layout;
    QGridLayout* GroupBox2_2Layout;
    QGridLayout* GroupBox2_3_2Layout;
    QHBoxLayout* Frame6Layout;
    QVBoxLayout* tabLayout_2;
    QGridLayout* GroupBox3Layout;
    QGridLayout* GroupBox4Layout;
    QVBoxLayout* tabLayout_3;
    QGridLayout* ButtonGroupIntegratorLayout;
    QVBoxLayout* GroupBoxTimeStepLayout;
};

#endif // MYCONTROLPANELBASE_H
