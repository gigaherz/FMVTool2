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

#include "stdafx.h"
#include "MainWindow.h"
#include "Process.h"

#include "wx/dir.h"
#include "wx/stdpaths.h"

#define CDVDdefs
#include "PS2Edefs.h"
#include "wx/file.h"
#include "wx/tokenzr.h"
#include "wx/filename.h"

void CALLBACK WrapFree();
s32  CALLBACK WrapLoad(const wchar_t *LibName);

void MainWindow::PrintToLog(const wchar_t* fmt, ...)
{
	wxString line;
	va_list ls;

	va_start(ls,fmt);
	line = wxString::FormatV(fmt,ls);
	va_end(ls);

	// hm hack! 
	//line.Replace(L"\n",L"\r\n");

	m_txtLog->AppendText(line);
}

void MainWindow::SetFormCaption(const wchar_t* fmt, ...)
{
	wxString caption;
	va_list ls;

	va_start(ls,fmt);
	caption = wxString::FormatV(fmt,ls);
	va_end(ls);

	this->SetTitle(caption);
}

///////////////////////////////////////////////////////////////////////////

void MainWindow::OnLogClear(wxCommandEvent & WXUNUSED(event))
{
	m_txtLog->Clear();
}

void MainWindow::OnExitClick(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

void MainWindow::OnQuit(wxCloseEvent & WXUNUSED(event))
{
	if((m_process!=NULL) && (m_process->IsWorking()))
	{
		m_process->ExitLoop();
		m_process->Wait();
		delete m_process;
	}
	wxExit();
}

void MainWindow::OnProcessDone(wxEvent & WXUNUSED(event))
{
	if(m_process->GetMode()<2)
	{
		m_lcItems->DeleteAllItems();

		loadedItems = m_process->GetListItems();
		for(unsigned int i=0;i<loadedItems.size();i++)
		{
			wxString start = wxString::Format(L"%d",loadedItems[i].sector);
			wxString offset = wxString::Format(L"%d",loadedItems[i].offset);
			wxString length = wxString::Format(L"%d",loadedItems[i].length);
			m_lcItems->InsertItem(i,L"");
			m_lcItems->SetItem(i,1,start);
			m_lcItems->SetItem(i,2,offset);
			m_lcItems->SetItem(i,3,length);
		}
	}
	m_btnStop->Enable(false);
	m_btnStartSearch->Enable(true);
	m_btnExtractChecked->Enable(true);
	m_btnExtractSectors->Enable(true);
}

void MainWindow::OnProcessStart(wxCommandEvent & event)
{
	if(m_process)
		delete m_process;

	int mode = 0;
	int id = event.GetId();

	if(id == m_btnExtractChecked->GetId())
		mode = 2;
	else if(id == m_btnExtractSectors->GetId())
		mode = 3;
	else if(m_chkLooseSearch->GetValue())
		mode = 1;

	if(mode == 2)
	{

		std::vector<StreamItem> items;

		int nitems = m_lcItems->GetItemCount();
		for(int i=0;i<nitems;i++)
		{
			if (m_lcItems->IsChecked(i))
			{
				items.push_back(loadedItems[i]);
			}
		}

		m_process = new Process(this,2,0,0,m_dpExtract->GetPath(),m_txtPrefix->GetValue(),items);
	}
	else
	{
		unsigned long start = 0;
		unsigned long end = 0;
		if(!m_chkFromDisk->GetValue())
		{
			if (!m_txtRangeStart->GetValue().ToULong(&start))
			{
				wxMessageBox(L"First sector is not a valid number.", L"Error", wxOK | wxICON_ERROR);
				m_txtRangeEnd->SetFocus();
				return;
			}

			if (!m_txtRangeEnd->GetValue().ToULong(&end))
			{
				wxMessageBox(L"Last sector is not a valid number.", L"Error", wxOK | wxICON_ERROR);
				m_txtRangeEnd->SetFocus();
				return;
			}
		}

		m_process = new Process(this,mode,start,end);
	}

	m_process->Create();
	m_process->Run();

	m_btnStop->Enable(true);
	m_btnStartSearch->Enable(false);
	m_btnExtractChecked->Enable(false);
	m_btnExtractSectors->Enable(false);
}

void MainWindow::OnProcessStop(wxCommandEvent & WXUNUSED(event))
{
	if((m_process!=NULL) && (m_process->IsWorking()))
	{
		m_process->ExitLoop();
	}
}

void MainWindow::OnPluginChange(wxCommandEvent & event)
{
	wxString dllName = *(wxString*)event.GetClientData();

	if(wasInitialized)
	{
		CDVDshutdown();
		WrapFree();
	}

	if(WrapLoad(dllName))
	{
		u32 version;
		if ((PS2EgetLibType()&PS2E_LT_CDVD) &&
			((((version=PS2EgetLibVersion2(PS2E_LT_CDVD))>>16)&0xFF)==PS2E_CDVD_VERSION))
		{
			CDVDinit();
			wasInitialized = true;
		}
	}

}

void MainWindow::OnShow(wxEvent & WXUNUSED(event))
{
	wxString dllName = *(wxString*)m_cbPlugin->GetClientData(0);

	if(WrapLoad(dllName))
	{
		u32 version;
		if ((PS2EgetLibType()&PS2E_LT_CDVD) &&
			((((version=PS2EgetLibVersion2(PS2E_LT_CDVD))>>16)&0xFF)==PS2E_CDVD_VERSION))
		{
			CDVDinit();
			wasInitialized = true;
		}
	}
}

void MainWindow::OnPluginConfig(wxCommandEvent & WXUNUSED(event))
{
	if(wasInitialized)
		CDVDconfigure();
}

void MainWindow::OnPluginAbout(wxCommandEvent & WXUNUSED(event))
{
	if(wasInitialized)
		CDVDabout();
}

void MainWindow::OnCheckAll(wxCommandEvent & WXUNUSED(event))
{
	int items = m_lcItems->GetItemCount();
	for(int i=0;i<items;i++)
	{
		m_lcItems->SetChecked(i,true);
	}
}

void MainWindow::OnCheckNone(wxCommandEvent & WXUNUSED(event))
{
	int items = m_lcItems->GetItemCount();
	for(int i=0;i<items;i++)
	{
		m_lcItems->SetChecked(i,false);
	}
}

void MainWindow::OnCheckInvert(wxCommandEvent & WXUNUSED(event))
{
	int items = m_lcItems->GetItemCount();
	for(int i=0;i<items;i++)
	{
		m_lcItems->SetChecked(i,!m_lcItems->IsChecked(i));
	}
}

void MainWindow::OnCheckSelected(wxCommandEvent & WXUNUSED(event))
{
	int items = m_lcItems->GetItemCount();
	for(int i=0;i<items;i++)
	{
		m_lcItems->SetChecked(i,m_lcItems->GetItemState(i,wxLIST_STATE_SELECTED)==wxLIST_STATE_SELECTED);
	}
}

void MainWindow::OnSaveList(wxCommandEvent & WXUNUSED(event))
{
	wxString dlg = wxFileSelector(
		wxT("Save FMV List..."),
		wxEmptyString, wxEmptyString, wxEmptyString,
		wxT("FMV List (*.fmvlist)|*.fmvlist|All files|*.*"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if(!dlg.IsEmpty())
	{
		wxFile file;
		file.Create(dlg, true);
		file.Write(wxT("FMVList v2\n"));
		size_t nitems = loadedItems.size();
		for(unsigned int i=0;i<nitems;i++)
		{
			wxString entry = wxString::Format(wxT("%d,%d,%d\n"),loadedItems[i].sector,loadedItems[i].offset,loadedItems[i].length);
			file.Write(entry);
		}
		file.Close();
	}
}

void MainWindow::OnOpenList(wxCommandEvent & WXUNUSED(event))
{
	wxString dlg = wxFileSelector(
		wxT("Save FMV List..."),
		wxEmptyString, wxEmptyString, wxEmptyString,
		wxT("FMV List (*.fmvlist)|*.fmvlist|All files|*.*"),
		wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if(!dlg.IsEmpty())
	{
		wxFile file;
		file.Open(dlg);

		int len = file.Length();
		u8* buffer = new u8[len+1];
		file.Read(buffer,len);
		file.Close();

		buffer[len] = 0;

		wxString contents = wxString::FromAscii((char*)buffer);

		wxStringTokenizer lines(contents,wxT("\r\n"));

		if(!lines.HasMoreTokens())
		{
			wxMessageBox(L"Parse error.", L"Error", wxOK | wxICON_ERROR);
			return;
		}

		wxString line = lines.GetNextToken();

		if(line.CompareTo(wxT("FMVList v2"))!=0)
		{
			wxMessageBox(L"Not a FMVList v2 file.", L"Error", wxOK | wxICON_ERROR);
			return;
		}

		std::vector<StreamItem> newItems;

		while(lines.HasMoreTokens())
		{
			line = lines.GetNextToken();
			if(line.Length() == 0)
				continue;

			wxStringTokenizer tkn(line,wxT(","));
			if(!tkn.HasMoreTokens())
				continue;
			wxString sSector = tkn.GetNextToken();
			if(!tkn.HasMoreTokens())
			{
				wxMessageBox(L"Parse error.", L"Error", wxOK | wxICON_ERROR);
				return;
			}
			wxString sOffset = tkn.GetNextToken();
			if(!tkn.HasMoreTokens())
			{
				wxMessageBox(L"Parse error.", L"Error", wxOK | wxICON_ERROR);
				return;
			}
			wxString sLength = tkn.GetNextToken();

			long sector,offset,length;
			if (sSector.ToLong(&sector) &&
				sOffset.ToLong(&offset) &&
				sLength.ToLong(&length))
			{
				StreamItem it = { sector,offset,length };
				newItems.push_back(it);
			}
			else
			{
				wxMessageBox(L"Parse error.", L"Error", wxOK | wxICON_ERROR);
				return;
			}
		}

		loadedItems = newItems;

		m_lcItems->DeleteAllItems();

		for(unsigned int i=0;i<loadedItems.size();i++)
		{
			wxString start = wxString::Format(L"%d",loadedItems[i].sector);
			wxString offset = wxString::Format(L"%d",loadedItems[i].offset);
			wxString length = wxString::Format(L"%d",loadedItems[i].length);
			m_lcItems->InsertItem(i,L"");
			m_lcItems->SetItem(i,1,start);
			m_lcItems->SetItem(i,2,offset);
			m_lcItems->SetItem(i,3,length);
		}
	}
}

void MainWindow::Initialize()
{
	m_process = NULL;
	wasInitialized = false;

	Connect(wxEVT_SHOW,
		wxEventHandler(MainWindow::OnShow));

	Connect(wxEVT_CLOSE_WINDOW,
		wxCloseEventHandler(MainWindow::OnQuit));

	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(MainWindow::OnExitClick));

	Connect(wxID_OPEN, wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(MainWindow::OnOpenList));

	Connect(wxID_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(MainWindow::OnSaveList));

	Connect(m_btnLogClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnLogClear));

	Connect(wxEVT_USER_FIRST+1,
		wxEventHandler(MainWindow::OnProcessDone));

	Connect(m_btnStartSearch->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnProcessStart)/*,new wxPoint(0,0)*/);

	Connect(m_btnExtractChecked->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnProcessStart)/*,new wxPoint(1,0)*/);

	Connect(m_btnExtractSectors->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnProcessStart)/*,new wxPoint(2,0)*/);

	Connect(m_btnStop->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnProcessStop));

	Connect(m_cbPlugin->GetId(), wxEVT_COMMAND_CHOICE_SELECTED,
		wxCommandEventHandler(MainWindow::OnPluginChange));

	Connect(m_btnConfigurePlugin->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnPluginConfig));

	Connect(m_btnAboutPlugin->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnPluginAbout));

	Connect(m_btnCheckAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnCheckAll));

	Connect(m_btnCheckNone->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnCheckNone));

	Connect(m_btnCheckInvert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnCheckInvert));

	Connect(m_btnCheckSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MainWindow::OnCheckSelected));

	m_lcItems->ClearAll();
	m_lcItems->InsertColumn(0,L"", wxLIST_FORMAT_LEFT, 24);
	m_lcItems->InsertColumn(1,L"First Sector", wxLIST_FORMAT_RIGHT);
	m_lcItems->InsertColumn(2,L"Offset", wxLIST_FORMAT_RIGHT);
	m_lcItems->InsertColumn(3,L"Length", wxLIST_FORMAT_RIGHT);

	m_btnStop->Enable(false);

	//////////////////////////////////////////////////////////////////////////

	//m_videoPlayer->SetBackgroundColour(wxColour(0x00007F00ul));
	m_videoPlayer->Enable(false);
	m_button21->Enable(false);
	m_button17->Enable(false);
	m_slider1->Enable(false);
	m_button19->Enable(false);
	m_button20->Enable(false);

	//////////////////////////////////////////////////////////////////////////

	wxFileName fname(wxGetCwd(),wxT("dlls"));

	wxString fullPath = fname.GetFullPath();

	wxDir dir(fullPath);
	if ( !dir.IsOpened() )
	{
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		return;
	}

	wxString filename;

	bool cont = dir.GetFirst(&filename, L"*.dll", wxDIR_FILES);
	while ( cont )
	{
		wxFileName dllName(fullPath,filename);
		if(WrapLoad(dllName.GetFullPath()))
		{
			u32 version;
			if ((PS2EgetLibType()&PS2E_LT_CDVD) &&
				((((version=PS2EgetLibVersion2(PS2E_LT_CDVD))>>16)&0xFF)==PS2E_CDVD_VERSION))
			{
				wxString libName = wxString::FromUTF8(PS2EgetLibName()).Trim();

				u32 build = (version>>24)&0xFF;
				u32 major = (version>> 8)&0xFF;
				u32 minor = (version    )&0xFF;

				libName += wxString::Format(L" v%d.%d",major,minor);
				libName += L" [" + filename + L"]";
				m_cbPlugin->Append(	libName, new wxString(dllName.GetFullPath()) );
			}
			WrapFree();
		}
		cont = dir.GetNext(&filename);
	}

	m_cbPlugin->SetSelection(0);

	wxStandardPaths paths;
	m_dpExtract->SetPath(paths.GetDocumentsDir());
	m_txtPrefix->SetValue(L"stream");
}