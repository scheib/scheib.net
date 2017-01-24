/****************************************************************************
** MyControlPanelBase meta object code from reading C++ file 'mycontrolpanel.h'
**
** Created: Thu Feb 14 13:45:25 2002
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MyControlPanelBase
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mycontrolpanel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MyControlPanelBase::className() const
{
    return "MyControlPanelBase";
}

QMetaObject *MyControlPanelBase::metaObj = 0;

void MyControlPanelBase::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("MyControlPanelBase","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString MyControlPanelBase::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MyControlPanelBase",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* MyControlPanelBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"MyControlPanelBase", "QWidget",
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
