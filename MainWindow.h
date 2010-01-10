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

#ifndef __MainWindow__
#define __MainWindow__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>

#include "CheckedListCtrl.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public wxDialog 
{
	private:

	protected:
		wxButton* m_btnStartSearch;
		wxButton* m_btnExtractChecked;
		wxButton* m_btnStop;
		wxButton* m_btnExtractSectors;
		wxButton* m_btnExit;
		wxStaticText* m_staticText6;
		wxDirPickerCtrl* m_dpExtract;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_txtPrefix;
		wxCheckedListCtrl* m_lcItems;
		wxButton* m_btnCheckAll;
		wxButton* m_btnCheckNone;
		wxButton* m_btnCheckInvert;
		wxButton* m_btnCheckSelected;
		wxTextCtrl* m_txtLog;
		wxCheckBox* m_chkScrollDown;

		wxButton* m_btnLogClear;
		wxPanel* m_videoPlayer;
		wxButton* m_button21;
		wxButton* m_button17;
		wxSlider* m_slider1;
		wxButton* m_button19;
		wxButton* m_button20;
		wxStaticText* m_staticText1;
		wxChoice* m_cbPlugin;
		wxButton* m_btnConfigurePlugin;

		wxButton* m_btnAboutPlugin;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_txtRangeStart;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_txtRangeEnd;
		wxCheckBox* m_chkFromDisk;
		wxCheckBox* m_chkLooseSearch;
		wxStaticBitmap* m_bmLogo;
		wxButton* m_btnShowAbout;
		wxRadioButton* m_optUserData;
		wxRadioButton* m_optRawSectors;
		wxButton* m_btnSave;
		wxButton* m_btnOpen;

		Process* m_process;

		std::vector<StreamItem> loadedItems;

		bool wasInitialized;
	
	public:
		MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("FmvTool2"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1031,637 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainWindow();
	

		void Initialize();

		void PrintToLog(const wchar_t* fmt, ...);
		void SetFormCaption(const wchar_t* fmt, ...);

		void OnExitClick(wxCommandEvent & event);
		void OnQuit(wxCloseEvent & event);

		void OnShow(wxEvent & event);

		void OnLogClear(wxCommandEvent & event);

		void OnPluginChange(wxCommandEvent & event); // what's the event type for this?
		void OnPluginConfig(wxCommandEvent & event);
		void OnPluginAbout(wxCommandEvent & event);

		void OnProcessStart(wxCommandEvent & event);
		void OnProcessStop(wxCommandEvent & event);
		void OnProcessDone(wxEvent & event);

		void OnCheckAll(wxCommandEvent & event);
		void OnCheckNone(wxCommandEvent & event);
		void OnCheckInvert(wxCommandEvent & event);
		void OnCheckSelected(wxCommandEvent & event);

		void OnSaveList(wxCommandEvent & event);
		void OnOpenList(wxCommandEvent & event);

		// TODO
		void OnAboutBox(wxCommandEvent & event);

		void OnConvertXAToWAV(wxCommandEvent & event);
};

#endif //__MainWindow__
