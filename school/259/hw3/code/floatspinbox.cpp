#include "floatspinbox.h"
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qvalidator.h>

//----------------------------------------------------------------------------

// Internal utility function.  The values tend to get "bruised" as we convert
// back and forth from int and double.  Sometimes when converting to int we
// come up one fraction of a decimal place short of the whole value, and we
// do not wish for these to be rounded down.
inline int round(double a)
{
  if (a>0) return int(a+0.5);
  if (a<0) return int(a-0.5);
  return int(a);
}

//----------------------------------------------------------------------------
/**
   Constructs a spin box with the default range and step value.
 */
FloatSpinBox::FloatSpinBox ( QWidget * parent , const char * name ) 
  : QSpinBox( parent, name ) 
{
  _init();
  setDoubleLineStep( m_increment );
  setDoubleRange( 0, 10 );
}

/**
   Constructs a spin box with the specified range and step value.
   The range is inclusive.  
   @note The \p minValue and \maxValue are rounded to the nearest integer
         multiple of \p step.
 */
FloatSpinBox::FloatSpinBox ( double minValue, double maxValue, double step , 
               QWidget * parent , const char * name ) 
  : QSpinBox( parent, name )
{
  _init();
  setDoubleLineStep( step );
  setDoubleRange( minValue, maxValue );
}

void FloatSpinBox::_init()
{
  m_mungMode = 0;
  m_increment= 0.1;
  m_warpCursor = true;
  m_floatFormat = 'g';
  m_floatPrec = 4;

  setValidator( new QDoubleValidator( 0, 1, 0, this ) );
  upButton()->installEventFilter(this);
  downButton()->installEventFilter(this);
  editor()->installEventFilter(this);
}

FloatSpinBox::~FloatSpinBox() {};

//----------------------------------------------------------------------------

/**
   Steps the value up by \p howMany steps.  Equivalent to calling stepUp() 
   \p howMany times, but is more efficient.
   @note If \p howMany is negative, this is equivalent to calling stepDown(int) 
         with a positive value.
 */
void FloatSpinBox::stepUp(int howMany)
{
  int val = value();
  val += howMany;
  if (wrapping()) {
    if (val > maxValue()) val = minValue()+(val-maxValue());
    else if (val < minValue()) val = maxValue()+(val-minValue());
  }
  setValue(val);
}

/**
   Steps the value down by \p howMany steps.  Equivalent to calling stepDown() 
   \p howMany times, but is more efficient.
   @note If \p howMany is negative, this is equivalent to calling stepUp(int) 
         with a positive value.
 */
void FloatSpinBox::stepDown(int howMany)
{
  int val = value();
  val -= howMany;
  if (wrapping()) {
    if (val > maxValue()) val = minValue()+(val-maxValue());
    else if (val < minValue()) val = maxValue()+(val-minValue());
  }
  setValue(val);
}

//----------------------------------------------------------------------------
/**
   Sets whether the cursor will be warped during munging when it gets to
   the edge of the screen.  Default value is \c true;
 */
void FloatSpinBox::setCursorWarping(bool onOff)
{
  m_warpCursor = onOff;
}
/**
   Returns whether the cursor is warped during munging when it gets to
   the edge of the screen.  Default value is \c true;
 */
bool FloatSpinBox::cursorWarping() const
{
  return m_warpCursor;
}

/**
   Sets the floating point output format for the spinner to use.
   These parameters are passed to QString::setNum() in order to convert
   the floating point value to a string.
 */
void FloatSpinBox::setDoubleFormat(char f, int prec)
{
  m_floatFormat = f;
  m_floatPrec = prec;
}

//----------------------------------------------------------------------------
/**
   Returns the minimum value of the spinner as a double.
   Analogous to QSpinBox::minValue() for the standard QSpinBox.
 */
double FloatSpinBox::doubleMinValue ( ) const
{
  return minValue() * m_increment;
}

/**
   Returns the maximum value of the spinner as a double.
   Analogous to QSpinBox::maxValue() for the standard QSpinBox.
 */
double FloatSpinBox::doubleMaxValue ( ) const
{
  return maxValue() * m_increment;
}

/**
   Returns the current line step of the spinner as a double.
   This is the amount the spinner will be incremented in response
   to clicks of the up and down buttons and in response to the up and 
   down arrow keys.
   Analogous to QSpinBox::lineStep() for the standard QSpinBox.
 */
double FloatSpinBox::doubleLineStep ( ) const
{
  return m_increment;
}

/**
   Returns the current value of the spinner as a double.
   Analogous to QSpinBox::value() for the standard QSpinBox.
 */
double FloatSpinBox::doubleValue ( ) const
{
  return value() * m_increment;
}

/**
   Sets the floating point range of allowed values for the spin box.
   @note The \p min and \max are rounded to the nearest integer
         multiples of the current line step as given by doubleLineStep().
*/
void FloatSpinBox::setDoubleRange( double min , double max )
{
  int iMin = round(min / m_increment);
  int iMax = round(max / m_increment);
  setRange( iMin, iMax );
  if (validator()->inherits("QDoubleValidator")) {
    ((QDoubleValidator*)validator())->setRange(min, max);
  }
  else {
    setValidator( new QDoubleValidator( min, max, 0, this ) );
  }
}

/**
   Set the minimum allowable floating point value for the spinner.
   Analogous to QSpinBox::setMinValue() for the standard QSpinBox.
   @note \p min is rounded to the nearest integer multiple of the current 
         line step as given by doubleLineStep().
 */
void FloatSpinBox::setDoubleMinValue ( double min ) 
{
  setDoubleRange( min, doubleMaxValue() );
}

/**
   Set the maximum allowable floating point value for the spinner.
   Analogous to QSpinBox::setMaxValue() for the standard QSpinBox.
   @note \p max is rounded to the nearest integer multiple of the current 
         line step as given by doubleLineStep().
 */
void FloatSpinBox::setDoubleMaxValue ( double max )
{
  setDoubleRange( doubleMinValue(), max );
}

/**
   Sets the current floating point line step of the spinner.
   This is the amount the spinner will be incremented in response
   to clicks of the up and down buttons and in response to the up and 
   down arrow keys.
   Analogous to QSpinBox::setLineStep() for the standard QSpinBox.
   @note Calling this will cause the minimum, maximum and current values
         of the spinner to be rounded to the nearest integer multiple
         of \p step.
 */
void FloatSpinBox::setDoubleLineStep ( double step )
{
  double min = doubleMinValue();
  double max = doubleMaxValue();
  m_increment = step;
  // fix ranges too.  Careful about calling doubleMinValue and doubleMaxValue.
  // must be done BEFORE setting m_increment to get the actual old values.
  setDoubleRange( min, max );
}

/**
   Sets the current value of the spinner as a double.
   Analogous to QSpinBox::setValue() for the standard QSpinBox.
   @note \p value is rounded to the nearest integer multiple of the current 
         line step as given by doubleLineStep().
 */
void FloatSpinBox::setDoubleValue( double value )
{
  setValue( round(value / m_increment) );
}

/**
   Sets the minimum value of the spinner to be allowed using a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The min property appears
   in QDesigner as \p minValueStr.  Use that to set the initial min value
   of the spinner.
 */
void FloatSpinBox::setDoubleMinValue ( const QString& min ) 
{  setDoubleMinValue( min.toDouble() ); }
/**
   Sets the maximum value of the spinner to be allowed using a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The max property appears
   in QDesigner as \p maxValueStr.  Use that to set the initial max value
   of the spinner.
 */
void FloatSpinBox::setDoubleMaxValue ( const QString& max ) 
{  setDoubleMaxValue( max.toDouble() ); }

/**
   Sets the floating point line step using a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The line step property 
   appears in QDesigner as \p lineStepStr.  Use that to set the initial 
   line step of the spinner.
 */
void FloatSpinBox::setDoubleLineStep ( const QString& step ) 
{  setDoubleLineStep( step.toDouble() ); }

/**
   Sets the floating point value of the spinner using a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The value property 
   appears in QDesigner as \p valueStr.  Use that to set the initial 
   value of the spinner.
 */
void FloatSpinBox::setDoubleValue    ( const QString& val ) 
{  setDoubleValue( val.toDouble() ); }

/**
   Returns the minimum value of the spinner allowed as a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The min property appears
   in QDesigner as \p minValueStr.  Use that to set the initial min value
   of the spinner.
 */
QString FloatSpinBox::doubleMinValueStr ( ) const
{  QString s; return s.setNum(doubleMinValue()); }
/**
   Returns the maximum value of the spinner allowed as a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The max property appears
   in QDesigner as \p maxValueStr.  Use that to set the initial max value
   of the spinner.
 */
QString FloatSpinBox::doubleMaxValueStr ( ) const
{  QString s; return s.setNum(doubleMaxValue()); }
/**
   Returns the floating point line step as a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The line step property 
   appears in QDesigner as \p lineStepStr.  Use that to set the initial 
   line step of the spinner.
 */
QString FloatSpinBox::doubleLineStepStr ( ) const
{  QString s; return s.setNum(doubleLineStep()); }
/**
   Return the floating point value of the spinner as a string.

   This is here because QDesigner 2.3.0 won't allow a user to set properties 
   that are doubles, just strings or ints or the like.  The value property 
   appears in QDesigner as \p valueStr.  Use that to set the initial 
   value of the spinner.
 */
QString FloatSpinBox::doubleValueStr ( ) const
{  QString s; return s.setNum(doubleValue()); }

//----------------------------------------------------------------------------

/** @reimp */
QString FloatSpinBox::mapValueToText( int v )
{
  QString str;
  str.setNum( doubleValue(), m_floatFormat, m_floatPrec );
  return str;
}

/** @reimp */
int FloatSpinBox::mapTextToValue( bool *ok )
{

  QString str = cleanText();
  return round(str.toDouble()/m_increment);
}

/** @reimp */
void FloatSpinBox::valueChange()
{
  QSpinBox::valueChange();
  emit valueChanged(doubleValue());
}


//----------------------------------------------------------------------------

/** @reimp */
void FloatSpinBox::mousePressEvent(QMouseEvent* e)
{
  QSpinBox::mousePressEvent(e);
}
/** @reimp */
void FloatSpinBox::mouseReleaseEvent(QMouseEvent* e)
{
  QSpinBox::mouseReleaseEvent(e);
  m_mungMode = 0;
}

/** @reimp */
void FloatSpinBox::mouseMoveEvent(QMouseEvent* e)
{
  QSpinBox::mouseMoveEvent(e);
  // if mouse moved outside of box far enough, go into 
  // mung mode
  if (m_mungMode) 
  {
    int delta = (m_mungMode==MUNG_HORIZONTAL)? 
      e->pos().x() - m_lastPos.x() :
      -e->pos().y() + m_lastPos.y();
    if (m_warpCursor && ((delta<0)?-delta:delta)> 250) {
      m_lastPos=e->pos();
      delta=0;
    }
    m_moveLeftover += delta;
    m_lastPos = e->pos();
    int val = value();
    int incstep = 6; // how many pixels you have to move to get one increment
    stepUp( m_moveLeftover / incstep );
    m_moveLeftover %= incstep;
    if (m_warpCursor) {
      QRect r = QApplication::desktop()->rect();
      QPoint p = e->globalPos();
      int b=10;
      if (p.x() > r.right()-b) p.rx()=r.left()+2*b;
      if (p.x() < r.left()+b) p.rx()=r.right()-2*b;
      if (p.y() > r.bottom()-b) p.ry()=r.top()+2*b;
      if (p.y() < r.top()+b) p.ry()=r.bottom()-2*b;
      if (p != e->globalPos()) {
        m_lastPos = e->pos();
        QCursor::setPos(p);
      }
    }
  }
  else 
  {
    QPoint pos = e->pos();
    const QRect& r = geometry();
    const int tol = 10;
    if (pos.x() < -tol ||
        pos.x() > width()+tol)
    {
      m_mungMode = MUNG_HORIZONTAL;
    }
    else if (pos.y() < -tol ||
             pos.y() > height()+tol)
    {
      m_mungMode = MUNG_VERTICAL;
    }
    if (m_mungMode) {
      m_moveLeftover = 0;
      m_lastPos = e->pos();
      // commit any text that's currently showing
      interpretText();
    }
  }
}

/** @reimp */
void FloatSpinBox::keyPressEvent( QKeyEvent *e )
{
  switch (e->key())
  {
    case Key_Up:
      stepUp();
      e->accept();
      break;
    case Key_Down:
      stepDown();
      e->accept();
      break;
    case Key_PageUp:
      stepUp(10);
      e->accept();
      break;
    case Key_PageDown:
      stepDown(10);
      e->accept();
      break;
    default:
      e->ignore();
  }
  if (!e->isAccepted()) QSpinBox::keyPressEvent( e );
}


/** @reimp */
bool FloatSpinBox::eventFilter(QObject *o, QEvent *ee)
{
  if (!o->isWidgetType()) return QSpinBox::eventFilter(o,ee);
  QWidget *w = (QWidget*)o;
  if (ee->type() == QEvent::MouseMove) 
  {
    QMouseEvent *e = (QMouseEvent*)ee;
    QMouseEvent pe(QEvent::MouseMove, w->mapToParent(e->pos()), 
                   e->button(), e->state());
    int wasMungMode = m_mungMode;
    mouseMoveEvent( &pe );

    // send a button up to the object getting the move
    // so it doesn't think we're still moving for it.
    // (Primarily a problem with up and down buttons
    //  which only respond to mouse LeftButton)
    if (!wasMungMode && m_mungMode) {
      if (e->state() & LeftButton) {
        QMouseEvent mouseup(QEvent::MouseButtonRelease,
                            e->pos(), LeftButton, e->state());
        o->removeEventFilter(this);
        QApplication::sendEvent(o, &mouseup);
        o->installEventFilter(this);
      }
    }
    if (m_mungMode)
      return true;
  }
  else if (ee->type() == QEvent::MouseButtonRelease) 
  {
    QMouseEvent *e = (QMouseEvent*)ee;
    QMouseEvent pe(QEvent::MouseButtonRelease, w->mapToParent(e->pos()), 
                   e->button(), e->state());
    mouseReleaseEvent( &pe );
    if (m_mungMode) {
      m_mungMode = 0;
      return true; // don't send it to parent object (already did)
    }
  }
  else if (ee->type() == QEvent::KeyPress)
  {
    QKeyEvent *e = (QKeyEvent*)ee;
    keyPressEvent( e );
    if (e->isAccepted()) return true;
  }

  return QSpinBox::eventFilter(o,ee);
}


