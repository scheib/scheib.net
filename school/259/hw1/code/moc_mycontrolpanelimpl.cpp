/****************************************************************************
** MyControlPanel meta object code from reading C++ file 'mycontrolpanelimpl.h'
**
** Created: Wed Feb 13 22:37:05 2002
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MyControlPanel
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "mycontrolpanelimpl.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MyControlPanel::className() const
{
    return "MyControlPanel";
}

QMetaObject *MyControlPanel::metaObj = 0;

void MyControlPanel::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(MyControlPanelBase::className(), "MyControlPanelBase") != 0 )
	badSuperclassWarning("MyControlPanel","MyControlPanelBase");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString MyControlPanel::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MyControlPanel",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* MyControlPanel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) MyControlPanelBase::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"MyControlPanel", "MyControlPanelBase",
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
