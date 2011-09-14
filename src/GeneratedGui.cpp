///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GeneratedGui.h"

///////////////////////////////////////////////////////////////////////////

BdayFrameGUI::BdayFrameGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxMenuBar* m_menubar1;
	m_menubar1 = new wxMenuBar( 0 );
	file = new wxMenu();
	start = new wxMenuItem( file, ID_START, wxString( wxT("Run on &Startup") ) , wxEmptyString, wxITEM_CHECK );
	file->Append( start );
	
	wxMenuItem* exit;
	exit = new wxMenuItem( file, ID_EXIT, wxString( wxT("E&xit") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( exit );
	
	m_menubar1->Append( file, wxT("&File") );
	
	edit = new wxMenu();
	wxMenuItem* userEventsFile;
	userEventsFile = new wxMenuItem( edit, ID_USER_EVENTS_FILE, wxString( wxT("&User Events File") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( userEventsFile );
	
	systemEventsFile = new wxMenuItem( edit, ID_SYSTEM_EVENTS_FILE, wxString( wxT("&System Events File") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( systemEventsFile );
	
	applicationEventsFile = new wxMenuItem( edit, ID_APPLICATION_EVENTS_FILE, wxString( wxT("&Application Events File") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( applicationEventsFile );
	
	m_menubar1->Append( edit, wxT("&Edit") );
	
	wxMenu* help;
	help = new wxMenu();
	wxMenuItem* contents;
	contents = new wxMenuItem( help, ID_CONTENTS, wxString( wxT("&Contents") ) , wxEmptyString, wxITEM_NORMAL );
	help->Append( contents );
	
	wxMenuItem* about;
	about = new wxMenuItem( help, ID_ABOUT, wxString( wxT("&About") ) , wxEmptyString, wxITEM_NORMAL );
	help->Append( about );
	
	m_menubar1->Append( help, wxT("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl1 = new wxTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer8->Add( m_textCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_okay = new wxButton( m_panel2, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_okay->SetDefault(); 
	bSizer8->Add( m_okay, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer8->Add( 0, 5, 0, wxEXPAND, 0 );
	
	m_panel2->SetSizer( bSizer8 );
	m_panel2->Layout();
	bSizer8->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 1, wxEXPAND | wxALL, 0 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BdayFrameGUI::onClose ) );
	this->Connect( start->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuStart ) );
	this->Connect( exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuExit ) );
	this->Connect( userEventsFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuUserEdit ) );
	this->Connect( systemEventsFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuSystemEdit ) );
	this->Connect( applicationEventsFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuApplicationEdit ) );
	this->Connect( contents->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuContents ) );
	this->Connect( about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuAbout ) );
	m_okay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BdayFrameGUI::OkClicked ), NULL, this );
}

BdayFrameGUI::~BdayFrameGUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BdayFrameGUI::onClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuStart ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuUserEdit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuSystemEdit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuApplicationEdit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuContents ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BdayFrameGUI::menuAbout ) );
	m_okay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BdayFrameGUI::OkClicked ), NULL, this );
}

EditorFrameGUI::EditorFrameGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl3 = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer9->Add( m_textCtrl3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrl2 = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE );
	bSizer9->Add( m_textCtrl2, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_save = new wxButton( m_panel3, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	m_save->SetDefault(); 
	bSizer3->Add( m_save, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_close = new wxButton( m_panel3, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_close, 0, wxALL, 5 );
	
	m_help = new wxButton( m_panel3, wxID_ANY, wxT("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_help, 0, wxALL, 5 );
	
	bSizer9->Add( bSizer3, 0, wxALIGN_RIGHT, 5 );
	
	
	bSizer9->Add( 0, 5, 0, wxEXPAND, 0 );
	
	m_panel3->SetSizer( bSizer9 );
	m_panel3->Layout();
	bSizer9->Fit( m_panel3 );
	bSizer2->Add( m_panel3, 1, wxEXPAND | wxALL, 0 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorFrameGUI::onClose ) );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::saveClicked ), NULL, this );
	m_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::closeClicked ), NULL, this );
	m_help->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::helpClicked ), NULL, this );
}

EditorFrameGUI::~EditorFrameGUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorFrameGUI::onClose ) );
	m_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::saveClicked ), NULL, this );
	m_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::closeClicked ), NULL, this );
	m_help->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorFrameGUI::helpClicked ), NULL, this );
}

AboutDialogueGUI::AboutDialogueGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap2 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_bitmap2, 0, wxALL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("The super simple birthday\nand anniversary reminder.\n\nVersion 2.0\n\nCopyright 2009 Evan McLean\nhttp://evanmclean.com/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL, 5 );
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ) );
	m_bitmap2->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ), NULL, this );
	m_staticText1->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ), NULL, this );
}

AboutDialogueGUI::~AboutDialogueGUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ) );
	m_bitmap2->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ), NULL, this );
	m_staticText1->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( AboutDialogueGUI::onLeftUp ), NULL, this );
}

HelpFrameGUI::HelpFrameGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlWin1 = new wxHtmlWindow( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer9->Add( m_htmlWin1, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_close = new wxButton( m_panel3, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_close->SetDefault(); 
	bSizer3->Add( m_close, 0, wxALL, 5 );
	
	bSizer9->Add( bSizer3, 0, wxALIGN_RIGHT, 5 );
	
	
	bSizer9->Add( 0, 5, 0, wxEXPAND, 0 );
	
	m_panel3->SetSizer( bSizer9 );
	m_panel3->Layout();
	bSizer9->Fit( m_panel3 );
	bSizer2->Add( m_panel3, 1, wxEXPAND | wxALL, 0 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HelpFrameGUI::closeClicked ), NULL, this );
}

HelpFrameGUI::~HelpFrameGUI()
{
	// Disconnect Events
	m_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HelpFrameGUI::closeClicked ), NULL, this );
}
