/****************************************************************************
** Form implementation generated from reading ui file '.\mycontrolpanel.ui'
**
** Created: Thu Feb 14 13:45:25 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "mycontrolpanel.h"

#include <qbuttongroup.h>
#include <qdial.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a MyControlPanelBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
MyControlPanelBase::MyControlPanelBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MyControlPanelBase" );
    resize( 234, 551 ); 
    setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, sizePolicy().hasHeightForWidth() ) );
    setProperty( "caption", tr( "Control Panel" ) );
    MyControlPanelBaseLayout = new QVBoxLayout( this ); 
    MyControlPanelBaseLayout->setSpacing( 6 );
    MyControlPanelBaseLayout->setMargin( 11 );

    TabWidget2 = new QTabWidget( this, "TabWidget2" );
    TabWidget2->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)7, TabWidget2->sizePolicy().hasHeightForWidth() ) );

    tab = new QWidget( TabWidget2, "tab" );
    tabLayout = new QVBoxLayout( tab ); 
    tabLayout->setSpacing( 6 );
    tabLayout->setMargin( 11 );

    Frame8 = new QFrame( tab, "Frame8" );
    Frame8->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame8->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame8Layout = new QHBoxLayout( Frame8 ); 
    Frame8Layout->setSpacing( 0 );
    Frame8Layout->setMargin( 0 );

    Frame6_2 = new QFrame( Frame8, "Frame6_2" );
    Frame6_2->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame6_2->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame6_2Layout = new QVBoxLayout( Frame6_2 ); 
    Frame6_2Layout->setSpacing( 0 );
    Frame6_2Layout->setMargin( 0 );

    DialDirection = new QDial( Frame6_2, "DialDirection" );
    DialDirection->setProperty( "minValue", -150 );
    DialDirection->setProperty( "maxValue", 150 );
    Frame6_2Layout->addWidget( DialDirection );

    TextLabel1_2_3 = new QLabel( Frame6_2, "TextLabel1_2_3" );
    TextLabel1_2_3->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, TextLabel1_2_3->sizePolicy().hasHeightForWidth() ) );
    TextLabel1_2_3->setProperty( "text", tr( "Direction" ) );
    TextLabel1_2_3->setProperty( "alignment", int( QLabel::AlignCenter ) );
    Frame6_2Layout->addWidget( TextLabel1_2_3 );
    Frame8Layout->addWidget( Frame6_2 );

    Frame7_2 = new QFrame( Frame8, "Frame7_2" );
    Frame7_2->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame7_2->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame7_2Layout = new QVBoxLayout( Frame7_2 ); 
    Frame7_2Layout->setSpacing( 0 );
    Frame7_2Layout->setMargin( 0 );

    DialElevation = new QDial( Frame7_2, "DialElevation" );
    DialElevation->setProperty( "minValue", -60 );
    DialElevation->setProperty( "maxValue", 240 );
    DialElevation->setProperty( "value", 45 );
    Frame7_2Layout->addWidget( DialElevation );

    TextLabel1_2_2_2 = new QLabel( Frame7_2, "TextLabel1_2_2_2" );
    TextLabel1_2_2_2->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, TextLabel1_2_2_2->sizePolicy().hasHeightForWidth() ) );
    TextLabel1_2_2_2->setProperty( "text", tr( "Elevation" ) );
    TextLabel1_2_2_2->setProperty( "alignment", int( QLabel::AlignCenter ) );
    Frame7_2Layout->addWidget( TextLabel1_2_2_2 );
    Frame8Layout->addWidget( Frame7_2 );
    tabLayout->addWidget( Frame8 );

    Frame7 = new QFrame( tab, "Frame7" );
    Frame7->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame7->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame7Layout = new QHBoxLayout( Frame7 ); 
    Frame7Layout->setSpacing( 0 );
    Frame7Layout->setMargin( 0 );

    GroupBox2_3 = new QGroupBox( Frame7, "GroupBox2_3" );
    GroupBox2_3->setProperty( "title", tr( "Powder (g)" ) );
    GroupBox2_3->setColumnLayout(0, Qt::Vertical );
    GroupBox2_3->layout()->setSpacing( 0 );
    GroupBox2_3->layout()->setMargin( 0 );
    GroupBox2_3Layout = new QGridLayout( GroupBox2_3->layout() );
    GroupBox2_3Layout->setAlignment( Qt::AlignTop );
    GroupBox2_3Layout->setSpacing( 6 );
    GroupBox2_3Layout->setMargin( 11 );

    SpinBoxPowder = new QSpinBox( GroupBox2_3, "SpinBoxPowder" );
    SpinBoxPowder->setProperty( "maxValue", 100000 );
    SpinBoxPowder->setProperty( "minValue", 1 );
    SpinBoxPowder->setProperty( "value", 5000 );

    GroupBox2_3Layout->addWidget( SpinBoxPowder, 0, 0 );
    Frame7Layout->addWidget( GroupBox2_3 );

    GroupBox2_2 = new QGroupBox( Frame7, "GroupBox2_2" );
    GroupBox2_2->setProperty( "title", tr( "Mass (g)" ) );
    GroupBox2_2->setColumnLayout(0, Qt::Vertical );
    GroupBox2_2->layout()->setSpacing( 0 );
    GroupBox2_2->layout()->setMargin( 0 );
    GroupBox2_2Layout = new QGridLayout( GroupBox2_2->layout() );
    GroupBox2_2Layout->setAlignment( Qt::AlignTop );
    GroupBox2_2Layout->setSpacing( 6 );
    GroupBox2_2Layout->setMargin( 11 );

    SpinBoxCannonMass = new QSpinBox( GroupBox2_2, "SpinBoxCannonMass" );
    SpinBoxCannonMass->setProperty( "maxValue", 100000 );
    SpinBoxCannonMass->setProperty( "minValue", 1 );
    SpinBoxCannonMass->setProperty( "value", 20000 );

    GroupBox2_2Layout->addWidget( SpinBoxCannonMass, 0, 0 );
    Frame7Layout->addWidget( GroupBox2_2 );
    tabLayout->addWidget( Frame7 );

    GroupBox2_3_2 = new QGroupBox( tab, "GroupBox2_3_2" );
    GroupBox2_3_2->setProperty( "title", tr( "Air Friction (g/s)" ) );
    GroupBox2_3_2->setColumnLayout(0, Qt::Vertical );
    GroupBox2_3_2->layout()->setSpacing( 0 );
    GroupBox2_3_2->layout()->setMargin( 0 );
    GroupBox2_3_2Layout = new QGridLayout( GroupBox2_3_2->layout() );
    GroupBox2_3_2Layout->setAlignment( Qt::AlignTop );
    GroupBox2_3_2Layout->setSpacing( 6 );
    GroupBox2_3_2Layout->setMargin( 11 );

    SpinBoxAirFriction = new QSpinBox( GroupBox2_3_2, "SpinBoxAirFriction" );
    SpinBoxAirFriction->setProperty( "maxValue", 100000 );
    SpinBoxAirFriction->setProperty( "minValue", 1 );
    SpinBoxAirFriction->setProperty( "value", 1000 );

    GroupBox2_3_2Layout->addWidget( SpinBoxAirFriction, 0, 0 );
    tabLayout->addWidget( GroupBox2_3_2 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout->addItem( spacer );

    Frame6 = new QFrame( tab, "Frame6" );
    Frame6->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, Frame6->sizePolicy().hasHeightForWidth() ) );
    Frame6->setProperty( "frameShape", (int)QFrame::NoFrame );
    Frame6->setProperty( "frameShadow", (int)QFrame::Raised );
    Frame6Layout = new QHBoxLayout( Frame6 ); 
    Frame6Layout->setSpacing( 6 );
    Frame6Layout->setMargin( 0 );

    PushButtonFire = new QPushButton( Frame6, "PushButtonFire" );
    PushButtonFire->setProperty( "text", tr( "Fire!" ) );
    PushButtonFire->setProperty( "accel", 268435488 );
    PushButtonFire->setProperty( "default", QVariant( TRUE, 0 ) );
    Frame6Layout->addWidget( PushButtonFire );

    PushButtonClearShots = new QPushButton( Frame6, "PushButtonClearShots" );
    PushButtonClearShots->setProperty( "text", tr( "Clear" ) );
    Frame6Layout->addWidget( PushButtonClearShots );
    tabLayout->addWidget( Frame6 );
    TabWidget2->insertTab( tab, tr( "Cannon" ) );

    tab_2 = new QWidget( TabWidget2, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2 ); 
    tabLayout_2->setSpacing( 6 );
    tabLayout_2->setMargin( 11 );

    GroupBox3 = new QGroupBox( tab_2, "GroupBox3" );
    GroupBox3->setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, GroupBox3->sizePolicy().hasHeightForWidth() ) );
    GroupBox3->setProperty( "title", tr( "Mass (kg)" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QGridLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    SpinBoxSpringMass = new QSpinBox( GroupBox3, "SpinBoxSpringMass" );
    SpinBoxSpringMass->setProperty( "minValue", 1 );
    SpinBoxSpringMass->setProperty( "value", 5 );

    GroupBox3Layout->addWidget( SpinBoxSpringMass, 0, 0 );
    tabLayout_2->addWidget( GroupBox3 );

    GroupBox4 = new QGroupBox( tab_2, "GroupBox4" );
    GroupBox4->setProperty( "title", tr( "Spring (kg/s/s)" ) );
    GroupBox4->setColumnLayout(0, Qt::Vertical );
    GroupBox4->layout()->setSpacing( 0 );
    GroupBox4->layout()->setMargin( 0 );
    GroupBox4Layout = new QGridLayout( GroupBox4->layout() );
    GroupBox4Layout->setAlignment( Qt::AlignTop );
    GroupBox4Layout->setSpacing( 6 );
    GroupBox4Layout->setMargin( 11 );

    SpinBoxSpring = new QSpinBox( GroupBox4, "SpinBoxSpring" );
    SpinBoxSpring->setProperty( "value", 15 );

    GroupBox4Layout->addWidget( SpinBoxSpring, 0, 0 );
    tabLayout_2->addWidget( GroupBox4 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_2->addItem( spacer_2 );

    PushButtonSpringReset = new QPushButton( tab_2, "PushButtonSpringReset" );
    PushButtonSpringReset->setProperty( "text", tr( "Reset to Rest Length" ) );
    tabLayout_2->addWidget( PushButtonSpringReset );
    TabWidget2->insertTab( tab_2, tr( "Spring" ) );

    tab_3 = new QWidget( TabWidget2, "tab_3" );
    tabLayout_3 = new QVBoxLayout( tab_3 ); 
    tabLayout_3->setSpacing( 6 );
    tabLayout_3->setMargin( 11 );

    PushButtonCamSpring = new QPushButton( tab_3, "PushButtonCamSpring" );
    PushButtonCamSpring->setProperty( "text", tr( "Spring View" ) );
    tabLayout_3->addWidget( PushButtonCamSpring );

    PushButtonCamCannon1 = new QPushButton( tab_3, "PushButtonCamCannon1" );
    PushButtonCamCannon1->setProperty( "text", tr( "Cannon Close View" ) );
    tabLayout_3->addWidget( PushButtonCamCannon1 );

    PushButtonCamCannon2 = new QPushButton( tab_3, "PushButtonCamCannon2" );
    PushButtonCamCannon2->setProperty( "text", tr( "Cannon Overhead View" ) );
    tabLayout_3->addWidget( PushButtonCamCannon2 );

    PushButtonCamOutside = new QPushButton( tab_3, "PushButtonCamOutside" );
    PushButtonCamOutside->setProperty( "text", tr( "Outside View" ) );
    tabLayout_3->addWidget( PushButtonCamOutside );
    TabWidget2->insertTab( tab_3, tr( "Cameras" ) );
    MyControlPanelBaseLayout->addWidget( TabWidget2 );

    ButtonGroupIntegrator = new QButtonGroup( this, "ButtonGroupIntegrator" );
    ButtonGroupIntegrator->setProperty( "title", tr( "Integrator" ) );
    ButtonGroupIntegrator->setColumnLayout(0, Qt::Vertical );
    ButtonGroupIntegrator->layout()->setSpacing( 0 );
    ButtonGroupIntegrator->layout()->setMargin( 0 );
    ButtonGroupIntegratorLayout = new QGridLayout( ButtonGroupIntegrator->layout() );
    ButtonGroupIntegratorLayout->setAlignment( Qt::AlignTop );
    ButtonGroupIntegratorLayout->setSpacing( 6 );
    ButtonGroupIntegratorLayout->setMargin( 11 );

    RadioButton3 = new QRadioButton( ButtonGroupIntegrator, "RadioButton3" );
    RadioButton3->setProperty( "text", tr( "Runga-Kutta 4" ) );
    RadioButton3->setProperty( "checked", QVariant( TRUE, 0 ) );
    ButtonGroupIntegrator->insert( RadioButton3, 2 );

    ButtonGroupIntegratorLayout->addWidget( RadioButton3, 2, 0 );

    RadioButton2 = new QRadioButton( ButtonGroupIntegrator, "RadioButton2" );
    RadioButton2->setProperty( "text", tr( "Midpoint" ) );

    ButtonGroupIntegratorLayout->addWidget( RadioButton2, 1, 0 );

    RadioButtonEuler = new QRadioButton( ButtonGroupIntegrator, "RadioButtonEuler" );
    RadioButtonEuler->setProperty( "text", tr( "Euler" ) );
    ButtonGroupIntegrator->insert( RadioButtonEuler, 0 );

    ButtonGroupIntegratorLayout->addWidget( RadioButtonEuler, 0, 0 );

    RadioButton4 = new QRadioButton( ButtonGroupIntegrator, "RadioButton4" );
    RadioButton4->setProperty( "text", tr( "Implicit" ) );

    ButtonGroupIntegratorLayout->addWidget( RadioButton4, 0, 1 );
    MyControlPanelBaseLayout->addWidget( ButtonGroupIntegrator );

    GroupBoxTimeStep = new QGroupBox( this, "GroupBoxTimeStep" );
    GroupBoxTimeStep->setProperty( "title", tr( "TimeStep (ms)" ) );
    GroupBoxTimeStep->setColumnLayout(0, Qt::Vertical );
    GroupBoxTimeStep->layout()->setSpacing( 0 );
    GroupBoxTimeStep->layout()->setMargin( 0 );
    GroupBoxTimeStepLayout = new QVBoxLayout( GroupBoxTimeStep->layout() );
    GroupBoxTimeStepLayout->setAlignment( Qt::AlignTop );
    GroupBoxTimeStepLayout->setSpacing( 6 );
    GroupBoxTimeStepLayout->setMargin( 11 );

    SpinBoxTimeStep = new QSpinBox( GroupBoxTimeStep, "SpinBoxTimeStep" );
    SpinBoxTimeStep->setProperty( "maxValue", 1000 );
    SpinBoxTimeStep->setProperty( "minValue", 1 );
    SpinBoxTimeStep->setProperty( "value", 10 );
    GroupBoxTimeStepLayout->addWidget( SpinBoxTimeStep );
    MyControlPanelBaseLayout->addWidget( GroupBoxTimeStep );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    MyControlPanelBaseLayout->addItem( spacer_3 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
MyControlPanelBase::~MyControlPanelBase()
{
    // no need to delete child widgets, Qt does it all for us
}

