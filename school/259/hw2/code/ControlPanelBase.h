/****************************************************************************
** Form interface generated from reading ui file '.\ControlPanelBase.ui'
**
** Created: Thu Mar 7 00:19:43 2002
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
class QButtonGroup;
class QCheckBox;
class QLabel;
class QRadioButton;
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
    QButtonGroup* ButtonGroup_ObjectType;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
    QRadioButton* RadioButton4;
    QRadioButton* RadioButton6;
    QRadioButton* RadioButton7;
    QRadioButton* RadioButton5;
    QLabel* TextLabel1;
    FloatSpinBox* FloatSpinBox_MaxVelocity;
    QLabel* TextLabel1_2;
    QSpinBox* SpinBox_ObjectCount;
    QCheckBox* CheckBox_Render;
    QCheckBox* CheckBox_SameSizeTest;

protected:
    QGridLayout* ControlPanelBaseLayout;
    QGridLayout* tabLayout;
    QGridLayout* ButtonGroup_ObjectTypeLayout;
};

#endif // CONTROLPANELBASE_H
