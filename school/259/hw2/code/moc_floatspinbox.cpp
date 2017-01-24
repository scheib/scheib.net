/****************************************************************************
** FloatSpinBox meta object code from reading C++ file 'floatspinbox.h'
**
** Created: Thu Feb 28 21:55:53 2002
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_FloatSpinBox
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "floatspinbox.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *FloatSpinBox::className() const
{
    return "FloatSpinBox";
}

QMetaObject *FloatSpinBox::metaObj = 0;

void FloatSpinBox::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QSpinBox::className(), "QSpinBox") != 0 )
	badSuperclassWarning("FloatSpinBox","QSpinBox");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString FloatSpinBox::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("FloatSpinBox",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* FloatSpinBox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QSpinBox::staticMetaObject();
#ifndef QT_NO_PROPERTIES
    typedef double(FloatSpinBox::*m3_t0)()const;
    typedef void(FloatSpinBox::*m3_t1)(double);
    typedef double(FloatSpinBox::*m3_t3)()const;
    typedef void(FloatSpinBox::*m3_t4)(double);
    typedef double(FloatSpinBox::*m3_t6)()const;
    typedef void(FloatSpinBox::*m3_t7)(double);
    typedef double(FloatSpinBox::*m3_t9)()const;
    typedef void(FloatSpinBox::*m3_t10)(double);
    typedef QString(FloatSpinBox::*m3_t12)()const;
    typedef void(FloatSpinBox::*m3_t13)(const QString&);
    typedef QString(FloatSpinBox::*m3_t15)()const;
    typedef void(FloatSpinBox::*m3_t16)(const QString&);
    typedef QString(FloatSpinBox::*m3_t18)()const;
    typedef void(FloatSpinBox::*m3_t19)(const QString&);
    typedef QString(FloatSpinBox::*m3_t21)()const;
    typedef void(FloatSpinBox::*m3_t22)(const QString&);
    m3_t0 v3_0 = &FloatSpinBox::doubleMaxValue;
    m3_t1 v3_1 = &FloatSpinBox::setDoubleMaxValue;
    m3_t3 v3_3 = &FloatSpinBox::doubleMinValue;
    m3_t4 v3_4 = &FloatSpinBox::setDoubleMinValue;
    m3_t6 v3_6 = &FloatSpinBox::doubleLineStep;
    m3_t7 v3_7 = &FloatSpinBox::setDoubleLineStep;
    m3_t9 v3_9 = &FloatSpinBox::doubleValue;
    m3_t10 v3_10 = &FloatSpinBox::setDoubleValue;
    m3_t12 v3_12 = &FloatSpinBox::doubleMaxValueStr;
    m3_t13 v3_13 = &FloatSpinBox::setDoubleMaxValue;
    m3_t15 v3_15 = &FloatSpinBox::doubleMinValueStr;
    m3_t16 v3_16 = &FloatSpinBox::setDoubleMinValue;
    m3_t18 v3_18 = &FloatSpinBox::doubleLineStepStr;
    m3_t19 v3_19 = &FloatSpinBox::setDoubleLineStep;
    m3_t21 v3_21 = &FloatSpinBox::doubleValueStr;
    m3_t22 v3_22 = &FloatSpinBox::setDoubleValue;
    QMetaProperty *props_tbl = QMetaObject::new_metaproperty( 8 );
    props_tbl[0].t = "double";
    props_tbl[0].n = "doubleMaxValue";
    props_tbl[0].get = *((QMember*)&v3_0);
    props_tbl[0].set = *((QMember*)&v3_1);
    props_tbl[0].reset = 0;
    props_tbl[0].gspec = QMetaProperty::Class;
    props_tbl[0].sspec = QMetaProperty::Class;
    props_tbl[1].t = "double";
    props_tbl[1].n = "doubleMinValue";
    props_tbl[1].get = *((QMember*)&v3_3);
    props_tbl[1].set = *((QMember*)&v3_4);
    props_tbl[1].reset = 0;
    props_tbl[1].gspec = QMetaProperty::Class;
    props_tbl[1].sspec = QMetaProperty::Class;
    props_tbl[2].t = "double";
    props_tbl[2].n = "doubleLineStep";
    props_tbl[2].get = *((QMember*)&v3_6);
    props_tbl[2].set = *((QMember*)&v3_7);
    props_tbl[2].reset = 0;
    props_tbl[2].gspec = QMetaProperty::Class;
    props_tbl[2].sspec = QMetaProperty::Class;
    props_tbl[3].t = "double";
    props_tbl[3].n = "doubleValue";
    props_tbl[3].get = *((QMember*)&v3_9);
    props_tbl[3].set = *((QMember*)&v3_10);
    props_tbl[3].reset = 0;
    props_tbl[3].gspec = QMetaProperty::Class;
    props_tbl[3].sspec = QMetaProperty::Class;
    props_tbl[4].t = "QString";
    props_tbl[4].n = "maxValueStr";
    props_tbl[4].get = *((QMember*)&v3_12);
    props_tbl[4].set = *((QMember*)&v3_13);
    props_tbl[4].reset = 0;
    props_tbl[4].gspec = QMetaProperty::Class;
    props_tbl[4].sspec = QMetaProperty::Reference;
    props_tbl[5].t = "QString";
    props_tbl[5].n = "minValueStr";
    props_tbl[5].get = *((QMember*)&v3_15);
    props_tbl[5].set = *((QMember*)&v3_16);
    props_tbl[5].reset = 0;
    props_tbl[5].gspec = QMetaProperty::Class;
    props_tbl[5].sspec = QMetaProperty::Reference;
    props_tbl[6].t = "QString";
    props_tbl[6].n = "lineStepStr";
    props_tbl[6].get = *((QMember*)&v3_18);
    props_tbl[6].set = *((QMember*)&v3_19);
    props_tbl[6].reset = 0;
    props_tbl[6].gspec = QMetaProperty::Class;
    props_tbl[6].sspec = QMetaProperty::Reference;
    props_tbl[7].t = "QString";
    props_tbl[7].n = "valueStr";
    props_tbl[7].get = *((QMember*)&v3_21);
    props_tbl[7].set = *((QMember*)&v3_22);
    props_tbl[7].reset = 0;
    props_tbl[7].gspec = QMetaProperty::Class;
    props_tbl[7].sspec = QMetaProperty::Reference;
#endif // QT_NO_PROPERTIES
    typedef void(FloatSpinBox::*m1_t0)(double,double);
    typedef void(FloatSpinBox::*m1_t1)(double);
    typedef void(FloatSpinBox::*m1_t2)(double);
    typedef void(FloatSpinBox::*m1_t3)(double);
    typedef void(FloatSpinBox::*m1_t4)(double);
    typedef void(FloatSpinBox::*m1_t5)(int);
    m1_t0 v1_0 = Q_AMPERSAND FloatSpinBox::setDoubleRange;
    m1_t1 v1_1 = Q_AMPERSAND FloatSpinBox::setDoubleMinValue;
    m1_t2 v1_2 = Q_AMPERSAND FloatSpinBox::setDoubleMaxValue;
    m1_t3 v1_3 = Q_AMPERSAND FloatSpinBox::setDoubleLineStep;
    m1_t4 v1_4 = Q_AMPERSAND FloatSpinBox::setDoubleValue;
    m1_t5 v1_5 = Q_AMPERSAND FloatSpinBox::setValue;
    QMetaData *slot_tbl = QMetaObject::new_metadata(6);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(6);
    slot_tbl[0].name = "setDoubleRange(double,double)";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "setDoubleMinValue(double)";
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "setDoubleMaxValue(double)";
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "setDoubleLineStep(double)";
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "setDoubleValue(double)";
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "setValue(int)";
    slot_tbl[5].ptr = *((QMember*)&v1_5);
    slot_tbl_access[5] = QMetaData::Private;
    typedef void(FloatSpinBox::*m2_t0)(double);
    m2_t0 v2_0 = Q_AMPERSAND FloatSpinBox::valueChanged;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "valueChanged(double)";
    signal_tbl[0].ptr = *((QMember*)&v2_0);
    metaObj = QMetaObject::new_metaobject(
	"FloatSpinBox", "QSpinBox",
	slot_tbl, 6,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	props_tbl, 8,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL valueChanged
void FloatSpinBox::valueChanged( double t0 )
{
    // No builtin function for signal parameter type double
    QConnectionList *clist = receivers("valueChanged(double)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef RT0 *PRT0;
    typedef void (QObject::*RT1)(double);
    typedef RT1 *PRT1;
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
		r0 = *((PRT0)(c->member()));
		(object->*r0)();
		break;
	    case 1:
		r1 = *((PRT1)(c->member()));
		(object->*r1)(t0);
		break;
	}
    }
}
