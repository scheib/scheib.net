/****************************************************************************
** Form interface generated from reading ui file '.\ControlPanelBase.ui'
**
** Created: Mon Apr 1 21:32:47 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef CONTROLPANELBASE_H
#define CONTROLPANELBASE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class FloatSpinBox;
class QFrame;
class QGroupBox;
class QLabel;
class QPushButton;
class QSpinBox;
class QTabWidget;

class ControlPanelBase : public QWidget
{ 
    Q_OBJECT

public:
    ControlPanelBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ControlPanelBase();

    QTabWidget* TabWidget2;
    QWidget* tab;
    QGroupBox* GroupBox1;
    QPushButton* PushButton_Hold_Left;
    QPushButton* PushButton_Hold_Up;
    QPushButton* PushButton_Hold_Right;
    QGroupBox* GroupBox1_2;
    QFrame* Frame5;
    QPushButton* PushButton_Force_Left;
    QPushButton* PushButton_Force_Up;
    QPushButton* PushButton_Force_Right;
    QFrame* Frame3;
    QLabel* TextLabel1_2;
    FloatSpinBox* FloatSpinBox_force;
    QLabel* TextLabel1;
    QSpinBox* SpinBox_TimeStep;
    FloatSpinBox* FloatSpinBox_dampening;
    QLabel* TextLabel12;
    QLabel* TextLabel12_2;
    FloatSpinBox* FloatSpinBox_mass;

protected:
    QGridLayout* ControlPanelBaseLayout;
    QGridLayout* tabLayout;
    QHBoxLayout* GroupBox1Layout;
    QVBoxLayout* GroupBox1_2Layout;
    QHBoxLayout* Frame5Layout;
    QHBoxLayout* Frame3Layout;
};

#endif // CONTROLPANELBASE_H
