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
#include "StdAfx.h"
#include "App.h"
#include "MainWindow.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
	SetExitOnFrameDelete(true);

	MainWindow *mainWnd = new MainWindow(NULL);
	mainWnd->Show(true);

	return true;
}

