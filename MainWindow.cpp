//FMVTool2: The FMV Extractor (v2)
//Copyright (C) 2010  David Quintana <gigaherz@gmail.com>
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MainWindow.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->AddGrowableCol( 2 );
	gbSizer2->AddGrowableRow( 1 );
	gbSizer2->AddGrowableRow( 2 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbGroupPlugin;
	sbGroupPlugin = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("CDVD Plugin Controls") ), wxVERTICAL );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Plugin:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer15->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString m_cbPluginChoices;
	m_cbPlugin = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cbPluginChoices, 0 );
	m_cbPlugin->SetSelection( 0 );
	bSizer15->Add( m_cbPlugin, 1, wxBOTTOM|wxRIGHT|wxTOP, 5 );

	sbGroupPlugin->Add( bSizer15, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	m_btnConfigurePlugin = new wxButton( this, wxID_ANY, wxT("Configure"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_btnConfigurePlugin, 1, wxBOTTOM|wxLEFT, 5 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnAboutPlugin = new wxButton( this, wxID_ANY, wxT("About"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_btnAboutPlugin, 1, wxBOTTOM|wxRIGHT, 5 );

	sbGroupPlugin->Add( bSizer16, 1, wxEXPAND, 5 );

	bSizer40->Add( sbGroupPlugin, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbGroupSearch;
	sbGroupSearch = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Search Settings") ), wxVERTICAL );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("From:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer17->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_txtRangeStart = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer17->Add( m_txtRangeStart, 1, wxRIGHT|wxTOP, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("to:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer17->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );

	m_txtRangeEnd = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer17->Add( m_txtRangeEnd, 1, wxRIGHT|wxTOP, 5 );

	sbGroupSearch->Add( bSizer17, 1, wxEXPAND, 5 );

	m_chkFromDisk = new wxCheckBox( this, wxID_ANY, wxT("Get sector range from disk"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkFromDisk->SetValue(true);

	sbGroupSearch->Add( m_chkFromDisk, 0, wxALL|wxEXPAND, 5 );

	m_chkLooseSearch = new wxCheckBox( this, wxID_ANY, wxT("Loosen search (can find false positives)"), wxDefaultPosition, wxDefaultSize, 0 );

	sbGroupSearch->Add( m_chkLooseSearch, 0, wxALL|wxEXPAND, 5 );

	bSizer40->Add( sbGroupSearch, 1, wxTOP|wxEXPAND, 5 );

	bSizer41->Add( bSizer40, 0, wxRIGHT, 5 );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer33;
	sbSizer33 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("About") ), wxVERTICAL );

	m_btnShowAbout = new wxButton( this, wxID_ABOUT, wxT("Show About box..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer33->Add( m_btnShowAbout, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	bSizer36->Add( sbSizer33, 1, wxEXPAND|wxRIGHT, 5 );

	m_bmLogo = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("\"LOGO\""), wxBITMAP_TYPE_RESOURCE ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer36->Add( m_bmLogo, 0, 0, 5 );

	bSizer23->Add( bSizer36, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbGroupExtract;
	sbGroupExtract = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Dump read mode") ), wxVERTICAL );

	m_optUserData = new wxRadioButton( this, wxID_ANY, wxT("User data (2048 bytes, CD/DVD)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_optUserData->SetValue( true ); 
	sbGroupExtract->Add( m_optUserData, 1, wxALL, 5 );

	m_optRawSectors = new wxRadioButton( this, wxID_ANY, wxT("Raw sectors (2352 bytes, CD only)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbGroupExtract->Add( m_optRawSectors, 1, wxALL, 5 );

	bSizer23->Add( sbGroupExtract, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );

	wxStaticBoxSizer* sbSizer28;
	sbSizer28 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Load/Save") ), wxHORIZONTAL );

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxHORIZONTAL );

	m_btnOpen = new wxButton( this, wxID_OPEN, wxT("Load FMVList"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( m_btnOpen, 1, wxBOTTOM|wxEXPAND|wxLEFT, 5 );

	m_btnSave = new wxButton( this, wxID_SAVE, wxT("Save FMVList"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( m_btnSave, 1, wxBOTTOM|wxEXPAND|wxLEFT, 5 );

	sbSizer28->Add( bSizer43, 1, wxEXPAND|wxRIGHT, 5 );

	bSizer23->Add( sbSizer28, 1, wxEXPAND, 5 );

	bSizer41->Add( bSizer23, 1, wxEXPAND, 5 );

	gbSizer2->Add( bSizer41, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxRIGHT, 5 );

	wxStaticBoxSizer* sbGroupPreview;
	sbGroupPreview = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Preview") ), wxVERTICAL );

	m_videoPlayer = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	sbGroupPreview->Add( m_videoPlayer, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_button21 = new wxButton( this, wxID_ANY, wxT("|<"), wxDefaultPosition, wxSize( 24,-1 ), 0 );
	bSizer19->Add( m_button21, 0, wxALL, 5 );

	m_button17 = new wxButton( this, wxID_ANY, wxT("Play"), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	bSizer19->Add( m_button17, 0, wxALL, 5 );

	m_slider1 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer19->Add( m_slider1, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_button19 = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	bSizer19->Add( m_button19, 0, wxALL, 5 );

	m_button20 = new wxButton( this, wxID_ANY, wxT(">|"), wxDefaultPosition, wxSize( 24,-1 ), 0 );
	bSizer19->Add( m_button20, 0, wxALL, 5 );

	sbGroupPreview->Add( bSizer19, 0, wxEXPAND, 5 );

	gbSizer2->Add( sbGroupPreview, wxGBPosition( 0, 2 ), wxGBSpan( 2, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* sbGroupItems;
	sbGroupItems = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Found Items") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Extraction path:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_dpExtract = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	fgSizer1->Add( m_dpExtract, 0, wxBOTTOM|wxRIGHT|wxTOP|wxEXPAND, 5 );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Filename Prefix:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_txtPrefix = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_txtPrefix, 1, wxRIGHT|wxEXPAND, 5 );

	sbGroupItems->Add( fgSizer1, 0, wxEXPAND, 5 );

	m_lcItems = new wxCheckedListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbGroupItems->Add( m_lcItems, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_btnCheckAll = new wxButton( this, wxID_ANY, wxT("Check all"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_btnCheckAll, 1, wxLEFT|wxRIGHT, 5 );

	m_btnCheckNone = new wxButton( this, wxID_ANY, wxT("None"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_btnCheckNone, 1, wxRIGHT, 5 );

	m_btnCheckInvert = new wxButton( this, wxID_ANY, wxT("Invert"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_btnCheckInvert, 1, wxRIGHT, 5 );

	m_btnCheckSelected = new wxButton( this, wxID_ANY, wxT("Selected"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_btnCheckSelected, 1, wxRIGHT, 5 );

	sbGroupItems->Add( bSizer20, 0, wxEXPAND, 5 );

	gbSizer2->Add( sbGroupItems, wxGBPosition( 1, 0 ), wxGBSpan( 2, 1 ), wxEXPAND|wxRIGHT|wxTOP, 5 );

	wxStaticBoxSizer* sbGroupTools;
	sbGroupTools = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Tools") ), wxVERTICAL );

	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->AddGrowableCol( 0 );
	gbSizer3->AddGrowableCol( 1 );
	gbSizer3->AddGrowableRow( 0 );
	gbSizer3->AddGrowableRow( 1 );
	gbSizer3->AddGrowableRow( 2 );
	gbSizer3->SetFlexibleDirection( wxVERTICAL );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_btnStartSearch = new wxButton( this, wxID_ANY, wxT("Start Searching"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_btnStartSearch, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxEXPAND|wxRIGHT, 5 );

	m_btnExtractChecked = new wxButton( this, wxID_ANY, wxT("Start Extracting"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_btnExtractChecked, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxEXPAND|wxRIGHT, 5 );

	m_btnStop = new wxButton( this, wxID_ANY, wxT("Stop current process"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_btnStop, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxEXPAND|wxRIGHT, 5 );

	m_btnExtractSectors = new wxButton( this, wxID_ANY, wxT("Dump Raw Sectors"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_btnExtractSectors, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxEXPAND|wxRIGHT, 5 );

	m_btnExit = new wxButton( this, wxID_EXIT, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_btnExit, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxBOTTOM|wxEXPAND|wxRIGHT, 5 );

	sbGroupTools->Add( gbSizer3, 1, wxEXPAND|wxLEFT|wxTOP, 5 );

	gbSizer2->Add( sbGroupTools, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxEXPAND|wxRIGHT|wxTOP, 5 );

	wxStaticBoxSizer* sbGroupLog;
	sbGroupLog = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Message Log") ), wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_txtLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_txtLog->SetMinSize( wxSize( 600,200 ) );

	bSizer4->Add( m_txtLog, 1, wxBOTTOM|wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnLogClear = new wxButton( this, wxID_ANY, wxT("Clear Log"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_btnLogClear, 0, wxALL, 0 );

	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );

	sbGroupLog->Add( bSizer4, 1, wxEXPAND, 5 );

	gbSizer2->Add( sbGroupLog, wxGBPosition( 2, 1 ), wxGBSpan( 1, 2 ), wxEXPAND|wxTOP, 5 );

	bSizerMain->Add( gbSizer2, 1, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizerMain );
	this->Layout();
	this->Initialize();
}

MainWindow::~MainWindow()
{
}
