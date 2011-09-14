///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GeneratedGui__
#define __GeneratedGui__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>

///////////////////////////////////////////////////////////////////////////

#define ID_START 1000
#define ID_EXIT 1001
#define ID_USER_EVENTS_FILE 1002
#define ID_SYSTEM_EVENTS_FILE 1003
#define ID_APPLICATION_EVENTS_FILE 1004
#define ID_CONTENTS 1005
#define ID_ABOUT 1006

///////////////////////////////////////////////////////////////////////////////
/// Class BdayFrameGUI
///////////////////////////////////////////////////////////////////////////////
class BdayFrameGUI : public wxFrame 
{
	private:
		wxPanel* m_panel2;
	
	protected:
		wxMenu* file;
		wxMenuItem* start;
		wxMenu* edit;
		wxMenuItem* systemEventsFile;
		wxMenuItem* applicationEventsFile;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_okay;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void onClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void menuStart( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuExit( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuUserEdit( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuSystemEdit( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuApplicationEdit( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuContents( wxCommandEvent& event ){ event.Skip(); }
		virtual void menuAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void OkClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		BdayFrameGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Events"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~BdayFrameGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class EditorFrameGUI
///////////////////////////////////////////////////////////////////////////////
class EditorFrameGUI : public wxFrame 
{
	private:
		wxPanel* m_panel3;
		wxButton* m_help;
	
	protected:
		wxTextCtrl* m_textCtrl3;
		wxTextCtrl* m_textCtrl2;
		wxButton* m_save;
		wxButton* m_close;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void onClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void saveClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void closeClicked( wxCommandEvent& event ){ event.Skip(); }
		virtual void helpClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		EditorFrameGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE );
		~EditorFrameGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialogueGUI
///////////////////////////////////////////////////////////////////////////////
class AboutDialogueGUI : public wxDialog 
{
	private:
		wxStaticText* m_staticText1;
	
	protected:
		wxStaticBitmap* m_bitmap2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onLeftUp( wxMouseEvent& event ){ event.Skip(); }
		
	
	public:
		AboutDialogueGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("BDay"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 331,167 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AboutDialogueGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class HelpFrameGUI
///////////////////////////////////////////////////////////////////////////////
class HelpFrameGUI : public wxFrame 
{
	private:
		wxButton* m_close;
	
	protected:
		wxPanel* m_panel3;
		wxHtmlWindow* m_htmlWin1;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void closeClicked( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		HelpFrameGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("BDay Help"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE );
		~HelpFrameGUI();
	
};

#endif //__GeneratedGui__
