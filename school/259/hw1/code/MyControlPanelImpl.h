#ifndef MYCONTROLPANEL_H
#define MYCONTROLPANEL_H
#include "mycontrolpanel.h"

class MyControlPanel : public MyControlPanelBase
{ 
    Q_OBJECT

public:
    MyControlPanel( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 )
      : MyControlPanelBase( parent, name, fl )
    {};
      
    ~MyControlPanel() {};

    virtual void buttonclicked() 
    {
      qDebug("HI\n");
    }
};

#endif // MYCONTROLPANEL_H
