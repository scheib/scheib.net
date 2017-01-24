/****************************************************************************
** ControlPanelBase meta object code from reading C++ file 'ControlPanelBase.h'
**
** Created: Mon Apr 1 21:32:47 2002
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_ControlPanelBase
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ControlPanelBase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *ControlPanelBase::className() const
{
    return "ControlPanelBase";
}

QMetaObject *ControlPanelBase::metaObj = 0;

void ControlPanelBase::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("ControlPanelBase","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString ControlPanelBase::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("ControlPanelBase",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* ControlPanelBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ControlPanelBase", "QWidget",
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
