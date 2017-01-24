/****************************************************************************
** Form implementation generated from reading ui file '.\ControlPanelBase.ui'
**
** Created: Mon Apr 1 21:32:47 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ControlPanelBase.h"

#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include "floatspinbox.h"
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a ControlPanelBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
ControlPanelBase::ControlPanelBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ControlPanelBase" );
    resize( 179, 334 ); 
    setProperty( "caption", tr( "Form1" ) );
    ControlPanelBaseLayout = new QGridLayout( this ); 
    ControlPanelBaseLayout->setSpacing( 0 );
    ControlPanelBaseLayout->setMargin( 0 );

    TabWidget2 = new QTabWidget( this, "TabWidget2" );

    tab = new QWidget( TabWidget2, "tab" );
    tabLayout = new QGridLayout( tab ); 
    tabLayout->setSpacing( 6 );
    tabLayout->setMargin( 11 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout->addItem( spacer, 5, 0 );

    GroupBox1 = new QGroupBox( tab, "GroupBox1" );
    GroupBox1->setProperty( "title", tr( "Hold" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QHBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    PushButton_Hold_Left = new QPushButton( GroupBox1, "PushButton_Hold_Left" );
    PushButton_Hold_Left->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Hold_Left->sizePolicy().hasHeightForWidth() ) );
    PushButton_Hold_Left->setProperty( "text", tr( "<" ) );
    GroupBox1Layout->addWidget( PushButton_Hold_Left );

    PushButton_Hold_Up = new QPushButton( GroupBox1, "PushButton_Hold_Up" );
    PushButton_Hold_Up->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Hold_Up->sizePolicy().hasHeightForWidth() ) );
    PushButton_Hold_Up->setProperty( "text", tr( "^" ) );
    GroupBox1Layout->addWidget( PushButton_Hold_Up );

    PushButton_Hold_Right = new QPushButton( GroupBox1, "PushButton_Hold_Right" );
    PushButton_Hold_Right->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Hold_Right->sizePolicy().hasHeightForWidth() ) );
    PushButton_Hold_Right->setProperty( "text", tr( ">" ) );
    GroupBox1Layout->addWidget( PushButton_Hold_Right );

    tabLayout->addMultiCellWidget( GroupBox1, 3, 3, 0, 1 );

    GroupBox1_2 = new QGroupBox( tab, "GroupBox1_2" );
    GroupBox1_2->setProperty( "title", tr( "Add Force" ) );
    GroupBox1_2->setColumnLayout(0, Qt::Vertical );
    GroupBox1_2->layout()->setSpacing( 0 );
    GroupBox1_2->layout()->setMargin( 0 );
    GroupBox1_2Layout = new QVBoxLayout( GroupBox1_2->layout() );
    GroupBox1_2Layout->setAlignment( Qt::AlignTop );
    GroupBox1_2Layout->setSpacing( 6 );
    GroupBox1_2Layout->setMargin( 11 );

    Frame5 = new QFrame( GroupBox1_2, "Frame5" );
    Frame5->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame5->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame5Layout = new QHBoxLayout( Frame5 ); 
    Frame5Layout->setSpacing( 6 );
    Frame5Layout->setMargin( 0 );

    PushButton_Force_Left = new QPushButton( Frame5, "PushButton_Force_Left" );
    PushButton_Force_Left->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Force_Left->sizePolicy().hasHeightForWidth() ) );
    PushButton_Force_Left->setProperty( "text", tr( "<" ) );
    Frame5Layout->addWidget( PushButton_Force_Left );

    PushButton_Force_Up = new QPushButton( Frame5, "PushButton_Force_Up" );
    PushButton_Force_Up->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Force_Up->sizePolicy().hasHeightForWidth() ) );
    PushButton_Force_Up->setProperty( "text", tr( "^" ) );
    Frame5Layout->addWidget( PushButton_Force_Up );

    PushButton_Force_Right = new QPushButton( Frame5, "PushButton_Force_Right" );
    PushButton_Force_Right->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, PushButton_Force_Right->sizePolicy().hasHeightForWidth() ) );
    PushButton_Force_Right->setProperty( "text", tr( ">" ) );
    Frame5Layout->addWidget( PushButton_Force_Right );
    GroupBox1_2Layout->addWidget( Frame5 );

    Frame3 = new QFrame( GroupBox1_2, "Frame3" );
    Frame3->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame3->setProperty( "frameShadow", (int)QFrame::Plain );
    Frame3Layout = new QHBoxLayout( Frame3 ); 
    Frame3Layout->setSpacing( 6 );
    Frame3Layout->setMargin( 0 );

    TextLabel1_2 = new QLabel( Frame3, "TextLabel1_2" );
    TextLabel1_2->setProperty( "text", tr( "Newtons:" ) );
    Frame3Layout->addWidget( TextLabel1_2 );

    FloatSpinBox_force = new FloatSpinBox( Frame3, "FloatSpinBox_force" );
    FloatSpinBox_force->setProperty( "lineStepStr", tr( "1" ) );
    FloatSpinBox_force->setProperty( "maxValueStr", tr( "100" ) );
    FloatSpinBox_force->setProperty( "minValueStr", tr( "0" ) );
    FloatSpinBox_force->setProperty( "valueStr", tr( "10" ) );
    Frame3Layout->addWidget( FloatSpinBox_force );
    GroupBox1_2Layout->addWidget( Frame3 );

    tabLayout->addMultiCellWidget( GroupBox1_2, 4, 4, 0, 1 );

    TextLabel1 = new QLabel( tab, "TextLabel1" );
    TextLabel1->setProperty( "text", tr( "TimeStep (ms)" ) );

    tabLayout->addWidget( TextLabel1, 0, 0 );

    SpinBox_TimeStep = new QSpinBox( tab, "SpinBox_TimeStep" );
    SpinBox_TimeStep->setProperty( "maxValue", 1000 );
    SpinBox_TimeStep->setProperty( "value", 10 );

    tabLayout->addWidget( SpinBox_TimeStep, 0, 1 );

    FloatSpinBox_dampening = new FloatSpinBox( tab, "FloatSpinBox_dampening" );
    FloatSpinBox_dampening->setProperty( "lineStepStr", tr( "0.001" ) );
    FloatSpinBox_dampening->setProperty( "maxValueStr", tr( "1" ) );
    FloatSpinBox_dampening->setProperty( "minValueStr", tr( "0" ) );
    FloatSpinBox_dampening->setProperty( "valueStr", tr( ".001" ) );

    tabLayout->addWidget( FloatSpinBox_dampening, 1, 1 );

    TextLabel12 = new QLabel( tab, "TextLabel12" );
    TextLabel12->setProperty( "text", tr( "Dampening" ) );

    tabLayout->addWidget( TextLabel12, 1, 0 );

    TextLabel12_2 = new QLabel( tab, "TextLabel12_2" );
    TextLabel12_2->setProperty( "text", tr( "Mass (Kg)" ) );

    tabLayout->addWidget( TextLabel12_2, 2, 0 );

    FloatSpinBox_mass = new FloatSpinBox( tab, "FloatSpinBox_mass" );
    FloatSpinBox_mass->setProperty( "lineStepStr", tr( ".25" ) );
    FloatSpinBox_mass->setProperty( "maxValueStr", tr( "1000" ) );
    FloatSpinBox_mass->setProperty( "minValueStr", tr( "0.25" ) );
    FloatSpinBox_mass->setProperty( "valueStr", tr( "1" ) );

    tabLayout->addWidget( FloatSpinBox_mass, 2, 1 );
    TabWidget2->insertTab( tab, tr( "Controls" ) );

    ControlPanelBaseLayout->addWidget( TabWidget2, 0, 0 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ControlPanelBase::~ControlPanelBase()
{
    // no need to delete child widgets, Qt does it all for us
}

