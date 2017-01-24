/****************************************************************************
** ControlPanel meta object code from reading C++ file 'ControlPanel.h'
**
** Created: Sun Mar 3 22:41:37 2002
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_ControlPanel
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ControlPanel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *ControlPanel::className() const
{
    return "ControlPanel";
}

QMetaObject *ControlPanel::metaObj = 0;

void ControlPanel::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(ControlPanelBase::className(), "ControlPanelBase") != 0 )
	badSuperclassWarning("ControlPanel","ControlPanelBase");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString ControlPanel::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("ControlPanel",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* ControlPanel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ControlPanelBase::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ControlPanel", "ControlPanelBase",
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
