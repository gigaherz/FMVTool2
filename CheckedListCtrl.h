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

// NOTE: I can't remember where the original was from.
// If it has some copyright, please tell me and I will properly
// give credit to the author(s).
#pragma once 
 
 #include <wx/wxprec.h>
 #include <wx/listctrl.h>
 #include <wx/imaglist.h>
 
 BEGIN_DECLARE_EVENT_TYPES()
     DECLARE_LOCAL_EVENT_TYPE(wxEVT_CHECKED_ITEM, 7791)
 END_DECLARE_EVENT_TYPES()
 
 
 #define EVT_CHECKED_ITEM_LISTCTRL(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CHECKED_ITEM, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxListEventFunction)&fn, (wxObject *) NULL ),
 //#define EVT_CHECKED_ITEM_LISTCTRL(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CHECKED_ITEM, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
 
 
 class wxCheckedListCtrl : public wxListCtrl
 {
 public:
     wxCheckedListCtrl() {};
     wxCheckedListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt = wxDefaultPosition, const wxSize& sz = wxDefaultSize, long style = wxLC_REPORT);
     bool IsChecked(long item) const;
     void SetChecked(long item, bool checked);
     void ClearChecked();
 protected:
     wxWindow * m_parent;
 private:
     void OnMouseEvent(wxMouseEvent& event);
     wxImageList     m_imageList;

     DECLARE_DYNAMIC_CLASS(wxCheckedListCtrl)
     /* DECLARE_DYNAMIC_CLASS == DECLARE_CLASS -> see object. h */
     DECLARE_EVENT_TABLE()
 };
 
