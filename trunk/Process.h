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
#pragma once

#include "MainWindow.h"

#include <vector>

class Process: public wxThread
{

	std::vector<StreamItem> ListItems;

	int ProcessMode;
	int FirstSector;
	int LastSector;

	bool Processing;

	wxString path;
	wxString prefix;

	MainWindow* parentWindow;

public:

	Process(MainWindow* parent, int mode, int first, int last, const wxString& pathName = wxT(""), const wxString& prefixText = wxT(""), const std::vector<StreamItem>& items = std::vector<StreamItem>());

	std::vector<StreamItem>& GetListItems() { return ListItems; }
	void  SetListItems(std::vector<StreamItem>& list) { ListItems = list; }

	int GetMode() { return ProcessMode; }

	bool IsWorking() { return Processing; }

	void SetPath(const wxString& str) { path = str; }
	void SetPrefix(const wxString& str) { prefix = str; }

	virtual ExitCode Entry();

	void Process1();
	void Process2();
	void Extract();

	void ExitLoop() { Processing = false; }
};