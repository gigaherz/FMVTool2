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
#include "CheckedListCtrl.h"

#ifndef _WIN32
#include <bitmaps/checked.xpm>
#include <bitmaps/unchecked.xpm>
#endif

IMPLEMENT_CLASS(wxCheckedListCtrl, wxListCtrl)

BEGIN_EVENT_TABLE(wxCheckedListCtrl, wxListCtrl)
EVT_LEFT_DOWN(wxCheckedListCtrl::OnMouseEvent)
END_EVENT_TABLE()

wxCheckedListCtrl::wxCheckedListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt,
									 const wxSize& sz, long style):
wxListCtrl(parent, id, pt, sz, style), m_imageList(13, 13, TRUE)
{
	SetImageList(&m_imageList, wxIMAGE_LIST_SMALL);

#ifndef _WIN32
	m_imageList.Add(wxICON(unchecked));
	m_imageList.Add(wxICON(checked));
#else
	m_imageList.Add(wxBitmap(L"\"UNCHECKED\""));
	m_imageList.Add(wxBitmap(L"\"CHECKED\""));
#endif

	InsertColumn(0, _("Item"), wxLIST_FORMAT_LEFT, 200);
	InsertColumn(1, _("Value"), wxLIST_FORMAT_LEFT, 80);
}

void wxCheckedListCtrl::OnMouseEvent(wxMouseEvent& event)
{
	if (event.LeftDown())
	{
		int flags;
		long item = HitTest(event.GetPosition(), flags);
		if (item > -1 && (flags & wxLIST_HITTEST_ONITEMICON))
		{
			SetChecked(item, !IsChecked(item));
		}
		else
			event.Skip();
	}
	else
	{
		event.Skip();
	}
}

bool wxCheckedListCtrl::IsChecked(long item) const
{
	wxListItem info;
	info.m_mask = wxLIST_MASK_IMAGE ;
	info.m_itemId = item;

	if (GetItem(info))
	{
		return (info.m_image == 1);
	}
	else
		return FALSE;
}

void wxCheckedListCtrl::SetChecked(long item, bool checked)
{
	SetItemImage(item, (checked ? 1 : 0), -1);
}
