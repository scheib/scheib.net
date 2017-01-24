// ControlPanel.h: interface for the ControlPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLPANEL1_H__7002AB04_1DBD_4022_B358_863512DF9D92__INCLUDED_)
#define AFX_CONTROLPANEL1_H__7002AB04_1DBD_4022_B358_863512DF9D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControlPanelBase.h"

class ControlPanel : public ControlPanelBase  
{
  Q_OBJECT
    
public:
  ControlPanel( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
  virtual ~ControlPanel();

};

#endif // !defined(AFX_CONTROLPANEL1_H__7002AB04_1DBD_4022_B358_863512DF9D92__INCLUDED_)
