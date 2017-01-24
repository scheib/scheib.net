//============================================================================
// floatspinbox.h
//============================================================================
/** @class FloatSpinBox  "floatspinbox.h"
 *
 * @author William V. Baxter III
 * @date October 25, 2001
 *
 * @brief A floating point spinner class for Qt which also supports enhanced
 *        munging.
 *
 *  Works just like a normal QSpinBox, but 
 *  - Floating point: it accepts floating point values and ranges.
 *
 *  - Enhanced munging: if you click on it then start dragging your mouse 
 *    outside the spinner's bounding box, then it starts acting like a slider 
 *    rather than spinner.  Of course it still looks like a spinner, but you
 *    can change the value by dragging the mouse over the whole desktop
 *    area (as long as you keep the button pressed).  Furthermore, 
 *    FloatSpinBox warps the cursor to the other side when you get to the
 *    edge of the screen so that you can mung endlessly in a "virtual
 *    toroidal desktop".  This type of spinner is sometimes seen in 3D 
 *    modeling and animation packages.
 *
 *  - Enhanced keyboard: up and down arrow keys increment and decrement the 
 *    value by 1 increment, and page up and page down increment and decrement
 *    by 10 increments.
 *
 *  There is also a Qt ".cw" Custom Widget file that can be imported
 *  into QDesigner, which provides a complete description of the widget.
 *  QDesigner 2.3.0 doesn't allow for setting floating point properties (silly!), 
 *  so I've added some string properties for getting and setting the various values
 *  which do appear in QDesigner, and can be used to set the floating point 
 *  range, step size, and value.
 *  
 *  @note The underlying values are still stored in integers.  So if you type
 *        in an arbitrary floating point value it will be rounded to the 
 *        nearest whole value in the underlying representation.  This should 
 *        be sufficient for most applications, really, but I could probably
 *        fix it by keeping track of a \c double floating point offset to use 
 *        when converting back and forth between the \c int and \c double 
 *        representations.  An exercise for the reader, perhaps.
 */
//============================================================================


#ifndef _FLOAT_SPIN_BOX_H_
#define _FLOAT_SPIN_BOX_H_

#include <qspinbox.h>

class FloatSpinBox : public QSpinBox
{
  Q_OBJECT
  Q_PROPERTY( double doubleMaxValue READ doubleMaxValue WRITE setDoubleMaxValue )
  Q_PROPERTY( double doubleMinValue READ doubleMinValue WRITE setDoubleMinValue )
  Q_PROPERTY( double doubleLineStep READ doubleLineStep WRITE setDoubleLineStep )
  Q_PROPERTY( double doubleValue READ doubleValue WRITE setDoubleValue )
    // These are just to get around the fact that Designer (2.3.0) can't
    // edit double values, but it *can* edit strings.  Not sure if 3.0 is any 
    // better...
  Q_PROPERTY( QString maxValueStr READ doubleMaxValueStr WRITE setDoubleMaxValue )
  Q_PROPERTY( QString minValueStr READ doubleMinValueStr WRITE setDoubleMinValue )
  Q_PROPERTY( QString lineStepStr READ doubleLineStepStr WRITE setDoubleLineStep )
  Q_PROPERTY( QString valueStr    READ doubleValueStr    WRITE setDoubleValue )
public:
  enum { MUNG_OFF, MUNG_VERTICAL, MUNG_HORIZONTAL };

public:
  FloatSpinBox ( QWidget * parent = 0, const char * name = 0 ) ;
  FloatSpinBox ( double minValue, double maxValue, double step = 0.1, 
                 QWidget * parent = 0, const char * name = 0 ) ;
  ~FloatSpinBox();

  /** @reimp */
  void stepUp()   { QSpinBox::stepUp(); }
  /** @reimp */
  void stepDown() { QSpinBox::stepDown(); }
  void stepUp(int howMany);
  void stepDown(int howMany);

  void setCursorWarping(bool onOff);
  bool cursorWarping() const;

  void setDoubleFormat(char f='g', int prec = 4);

  // Theese are for Designer too, but could be useful otherwise as well.
  void setDoubleMinValue ( const QString& min ) ;
  void setDoubleMaxValue ( const QString& max ) ;
  void setDoubleLineStep ( const QString& step ) ;
  void setDoubleValue    ( const QString& val ) ;
  QString doubleMinValueStr ( ) const ;
  QString doubleMaxValueStr ( ) const ;
  QString doubleLineStepStr ( ) const ;
  QString doubleValueStr ( ) const ;

  // These are the ones you should use normally.
  double doubleMinValue ( ) const ;
  double doubleMaxValue ( ) const ;
  double doubleLineStep ( ) const ;
  double doubleValue ( )    const ;

public slots:
  void setDoubleRange    ( double min, double max ) ;
  void setDoubleMinValue ( double min ) ;
  void setDoubleMaxValue ( double max ) ;
  void setDoubleLineStep ( double step ) ;
  void setDoubleValue    ( double val ) ;

private:
  // Overrides to hide methods that shouldn't be called by users
  // because they won't have the expected behavior.
  // Really I'd like to inherit privately from QSpinBox, but
  // still inherit from it's parent publicly.  Not possible in C++, though.
  /** @reimp */
  int value() const    { return QSpinBox::value(); }
  /** @reimp */
  int minValue() const { return QSpinBox::minValue(); }
  /** @reimp */
  int maxValue() const { return QSpinBox::maxValue(); }
  /** @reimp */
  int lineStep() const { return QSpinBox::lineStep(); }
  /** @reimp */
  void setMinValue(int v) { QSpinBox::setMinValue(v); }
  /** @reimp */
  void setMaxValue(int v) { QSpinBox::setMaxValue(v); }
  /** @reimp */
  void setLineStep(int v) { QSpinBox::setLineStep(v); }

private slots:
  /** @reimp */
  void setValue(int v)  { QSpinBox::setValue(v); }


signals:
  void valueChanged ( double );

protected:
  int     mapTextToValue( bool* );
  QString mapValueToText( int v );
  void    valueChange( ) ;

  void mousePressEvent(QMouseEvent*);
  void mouseReleaseEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent *);

  bool eventFilter(QObject*, QEvent*);

private:
  void _init( );
  double m_increment;
  int m_mungMode;
  bool m_warpCursor;
  int m_moveLeftover;
  QPoint m_lastPos;
  char m_floatFormat;
  int m_floatPrec;
};


#endif
