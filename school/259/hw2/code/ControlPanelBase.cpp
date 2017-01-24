/****************************************************************************
** Form implementation generated from reading ui file '.\ControlPanelBase.ui'
**
** Created: Thu Mar 7 00:19:44 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ControlPanelBase.h"

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
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
    resize( 175, 331 ); 
    setProperty( "caption", tr( "Form1" ) );
    ControlPanelBaseLayout = new QGridLayout( this ); 
    ControlPanelBaseLayout->setSpacing( 0 );
    ControlPanelBaseLayout->setMargin( 0 );

    TabWidget2 = new QTabWidget( this, "TabWidget2" );

    tab = new QWidget( TabWidget2, "tab" );
    tabLayout = new QGridLayout( tab ); 
    tabLayout->setSpacing( 6 );
    tabLayout->setMargin( 11 );

    ButtonGroup_ObjectType = new QButtonGroup( tab, "ButtonGroup_ObjectType" );
    ButtonGroup_ObjectType->setProperty( "title", tr( "Object Type" ) );
    ButtonGroup_ObjectType->setColumnLayout(0, Qt::Vertical );
    ButtonGroup_ObjectType->layout()->setSpacing( 0 );
    ButtonGroup_ObjectType->layout()->setMargin( 0 );
    ButtonGroup_ObjectTypeLayout = new QGridLayout( ButtonGroup_ObjectType->layout() );
    ButtonGroup_ObjectTypeLayout->setAlignment( Qt::AlignTop );
    ButtonGroup_ObjectTypeLayout->setSpacing( 6 );
    ButtonGroup_ObjectTypeLayout->setMargin( 11 );

    RadioButton1 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton1" );
    RadioButton1->setProperty( "text", tr( "0" ) );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton1, 0, 0 );

    RadioButton2 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton2" );
    RadioButton2->setProperty( "text", tr( "1" ) );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton2, 1, 0 );

    RadioButton3 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton3" );
    RadioButton3->setProperty( "text", tr( "2" ) );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton3, 2, 0 );

    RadioButton4 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton4" );
    RadioButton4->setProperty( "text", tr( "3" ) );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton4, 0, 1 );

    RadioButton6 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton6" );
    RadioButton6->setProperty( "text", tr( "5" ) );
    ButtonGroup_ObjectType->insert( RadioButton6, 5 );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton6, 2, 1 );

    RadioButton7 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton7" );
    RadioButton7->setProperty( "text", tr( "Random" ) );
    RadioButton7->setProperty( "checked", QVariant( TRUE, 0 ) );
    ButtonGroup_ObjectType->insert( RadioButton7, 6 );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton7, 3, 1 );

    RadioButton5 = new QRadioButton( ButtonGroup_ObjectType, "RadioButton5" );
    RadioButton5->setProperty( "text", tr( "4" ) );
    ButtonGroup_ObjectType->insert( RadioButton5, 4 );

    ButtonGroup_ObjectTypeLayout->addWidget( RadioButton5, 1, 1 );

    tabLayout->addMultiCellWidget( ButtonGroup_ObjectType, 2, 2, 0, 1 );

    TextLabel1 = new QLabel( tab, "TextLabel1" );
    TextLabel1->setProperty( "text", tr( "Objects" ) );

    tabLayout->addWidget( TextLabel1, 0, 0 );

    FloatSpinBox_MaxVelocity = new FloatSpinBox( tab, "FloatSpinBox_MaxVelocity" );

    tabLayout->addWidget( FloatSpinBox_MaxVelocity, 1, 1 );

    TextLabel1_2 = new QLabel( tab, "TextLabel1_2" );
    TextLabel1_2->setProperty( "text", tr( "Velocity" ) );

    tabLayout->addWidget( TextLabel1_2, 1, 0 );

    SpinBox_ObjectCount = new QSpinBox( tab, "SpinBox_ObjectCount" );
    SpinBox_ObjectCount->setProperty( "maxValue", 1000 );

    tabLayout->addWidget( SpinBox_ObjectCount, 0, 1 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout->addItem( spacer, 5, 0 );

    CheckBox_Render = new QCheckBox( tab, "CheckBox_Render" );
    CheckBox_Render->setProperty( "text", tr( "Render Objects" ) );
    CheckBox_Render->setProperty( "checked", QVariant( TRUE, 0 ) );

    tabLayout->addMultiCellWidget( CheckBox_Render, 3, 3, 0, 1 );

    CheckBox_SameSizeTest = new QCheckBox( tab, "CheckBox_SameSizeTest" );
    CheckBox_SameSizeTest->setProperty( "text", tr( "Same Size Test" ) );
    CheckBox_SameSizeTest->setProperty( "checked", QVariant( FALSE, 0 ) );

    tabLayout->addMultiCellWidget( CheckBox_SameSizeTest, 4, 4, 0, 1 );
    TabWidget2->insertTab( tab, tr( "Collision Controls" ) );

    ControlPanelBaseLayout->addWidget( TabWidget2, 0, 0 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ControlPanelBase::~ControlPanelBase()
{
    // no need to delete child widgets, Qt does it all for us
}

