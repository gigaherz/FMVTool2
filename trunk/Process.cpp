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
#include "Process.h"

#include <stdarg.h>

#include "wx/filename.h"
#include "wx/file.h"

#define CDVDdefs
#include "PS2Edefs.h"

using namespace std;

u8 Sector[2352];

const u8 StartCode[] = {
	0x00,		// \ 
	0x00,		//  | Start Code
	0x01,		//  |
	0xBA,		// /
	0x44,		// \  => MPEG2 Type (mpeg1 uses 0x20)
	0x00,		//  |
	0x04,		//  | Not Sure, but all PSS and VOB files i've seen have them
	0x00,		// /
};
const u8 EndCode[] = {
	0xFF,		// \ 
	0xFF,		//  | Padding Bytes. It seems they use them to make the file use full sectors.
	0xFF,		//  | (2048-byte cdrom sectors)
	0xFF,		// /
	0x00,		// \ 
	0x00,		//  | Program End Code
	0x01,		//  |
	0xB9,		// /
};

int DetectSectors()
{
	cdvdTD td;
	CDVDgetTD(0, &td);
	return td.lsn;
}

const wchar_t* GetDiskTypeName(int TT)
{
	switch(TT)
	{
		case CDVD_TYPE_ILLEGAL:   return L"Illegal";
		case CDVD_TYPE_DVDV:      return L"DVD Video";
		case CDVD_TYPE_CDDA:      return L"CD Audio";
		case CDVD_TYPE_PS2DVD:    return L"DVDROM (PlayStation 2)";
		case CDVD_TYPE_PS2CDDA:   return L"CDROM with Audio (PlayStation 2)";
		case CDVD_TYPE_PS2CD:     return L"CDROM (PlayStation 2)";
		case CDVD_TYPE_PSCDDA:    return L"CDROM with Audio (PlayStation)";
		case CDVD_TYPE_PSCD:      return L"CDROM (PlayStation)";
		case CDVD_TYPE_UNKNOWN:   return L"Unknown";
		case CDVD_TYPE_DETCTDVDD: return L"Detecting DVD (Double Layer)";
		case CDVD_TYPE_DETCTDVDS: return L"Detecting DVD (Single Layer)";
		case CDVD_TYPE_DETCTCD:   return L"Detecting CD";
		case CDVD_TYPE_DETCT:     return L"Detecting";
		case CDVD_TYPE_NODISC:    return L"No Disc";
	}
	return L"Unidentified";
}


wxString FormatSize(int bytes)
{
	const float BytesInK = 1024.0f;
	const float BytesInM = 1024.0f*1024.0f;
	const float BytesInG = 1024.0f*1024.0f*1024.0f;
	
	if(bytes < 1000)
		return wxString::Format(L"%d Bytes", bytes);

	if(bytes < 1024*1000)
		return wxString::Format(L"%1.2f KBytes", bytes/BytesInK);

	if(bytes < 1024*1024*1000)
		return wxString::Format(L"%1.2f MBytes", bytes/BytesInM);

	return wxString::Format(L"%1.2f GBytes", bytes/BytesInG);
}

Process::Process(MainWindow* parent, int mode, int first, int last,
				 const wxString& pathName,
				 const wxString& prefixText,
				 const std::vector<StreamItem>& items)
				 : wxThread(wxTHREAD_JOINABLE), path(pathName), prefix(prefixText), ListItems(items)
{
	parentWindow = parent;
	ProcessMode = mode;
	FirstSector = first;
	LastSector = last;
}

void* Process::Entry()
{
	parentWindow->PrintToLog(L"Opening Disc...\n");
	if (CDVDopen(NULL) == 0)
	{
		parentWindow->PrintToLog(L"Disc Open Successful.\n");
		parentWindow->PrintToLog(L"Disc Type: %d - %s\n", CDVDgetDiskType(), GetDiskTypeName(CDVDgetDiskType()));

		if (CDVDgetDiskType() == 0)
		{
			parentWindow->PrintToLog(L"No disc detected. Aborting...\n");
			wxMessageBox(L"There is no disc in the drive. Operation Aborted.", L"Fatal Error", wxOK | wxICON_ERROR);
		}
		else
		{

			if(LastSector<=FirstSector)
				LastSector = DetectSectors();

			Processing = true;

			switch(ProcessMode)
			{
			case 0: Process1(); break;
			case 1: Process2(); break;
			case 2: Extract(); break;
			}

		}
		
		parentWindow->PrintToLog(L"Closing disc...\n");
		CDVDclose();
		parentWindow->PrintToLog(L"Done.\n");

		parentWindow->SetFormCaption(L"FmvTool2");
		parentWindow->AddPendingEvent(wxCommandEvent(wxEVT_USER_FIRST+1));
	}
	else
	{
		parentWindow->PrintToLog(L"FATAL ERROR: Failed to Open the disc.\n");
		wxMessageBox(L"Failed to Open the disc.", L"Fatal Error", wxOK | wxICON_ERROR);
	}

	return NULL;
}

void Process::Process1()
{
	parentWindow->PrintToLog(L"Searching MPEG2 Streams...\n");

	int startOffset = 0;

	int sector = FirstSector;
	int offset = 0;

	int state = 0;

	int lastTicks = GetTickCount() - 1;

	int prevSector = 0;
	int streamLength = 0;

	
	StreamItem t={sector,0,0};

	while ((sector < LastSector) & Processing)
	{
		int Tr = CDVDreadTrack(sector, CDVD_MODE_2048);
		CDVDgetBuffer2(Sector);

		for(int i=0; i < 2048;)
		{
			switch (state)
			{
				case 0: //Seraching Start1
					if (Sector[i] == StartCode[0])
					{
						state = 1;
						offset = i;
						startOffset = i;
						t.sector = sector;
					}
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					if (Sector[i] == StartCode[state])
					{
						state++;
					}
					else
					{
						state = 0;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 7:
					if (Sector[i] == StartCode[7])
					{
						state = 8;
						parentWindow->PrintToLog(L"Stream found in sector %d, at offset %d...\n", sector, offset);
						streamLength = 8;
					}
					else
					{
						state = 0;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 8: //Copying until End1
					streamLength = streamLength + 1;
					if (Sector[i] == EndCode[0])
					{
						state = 9;
						offset = i;
					}
					break;
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
					if (Sector[i] == EndCode[state - 8])
					{
						state++;
					}
					else
					{
						state = 8;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 15:
					if (Sector[i] == EndCode[7])
					{
						state = 0;
						streamLength = streamLength + 7;
						wxString size = FormatSize(streamLength);
						parentWindow->PrintToLog(L"Stream End found in sector %d, at offset %d. Stream Length: %s.\n",sector,offset,size.c_str());
						t.offset = startOffset;
						t.length = streamLength;
						ListItems.push_back(t);
					}
					else
					{
						state = 8;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
			}
			i++;
		}
		if ((GetTickCount()-lastTicks) >= 1000)
		{
			parentWindow->SetFormCaption(L"Searching... sector %d of %d (%%%1.2f) --- State: %d --- Speed: %1.2f Kbytes/s",
				sector,
				LastSector,
				sector * 100.0f / LastSector,
				state,
				(2000.0f * (sector - prevSector) / (GetTickCount() - lastTicks)));
			lastTicks = GetTickCount();
			prevSector = sector;
		}
		sector++;
	}

	if ((state >= 8) && Processing)
	{
		state = 0;
		parentWindow->PrintToLog(L"Sector Limit Reached! The Stream might not be complete!\n");
	}
	parentWindow->PrintToLog(L"Done searching. Streams Found: %d.\n", ListItems.size());
}

void Process::Process2()
{

	parentWindow->PrintToLog(L"Searching MPEG2 Streams...\n");

	int startOffset = 0;

	int sector = FirstSector;
	int csector = -1;
	int offset = 0;

	int state = 0;

	int lastTicks = GetTickCount() - 1;

	int prevSector = 0;
	int streamLength = 0;

	while ((sector < LastSector) & Processing)
	{
		int Tr = CDVDreadTrack(sector, CDVD_MODE_2048);
		CDVDgetBuffer2(Sector);
		csector = sector;

		for(int i = 0; (i < 2048) && (sector==csector); )
		{
			switch (state)
			{
				case 0: //Seraching Start1
					if (Sector[i] == StartCode[0])
					{
						state = 1;
						offset = i;
						startOffset = i;
					}
					break;
				case 1:
				case 2:
				case 3:
					if (Sector[i] == StartCode[state])
					{
						state++;
					}
					else
					{
						state = 0;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 4:
					if ((Sector[i] & 0xC0) == 0x40)
					{
						parentWindow->PrintToLog(L" *** Detected possible MPEG2 Stream.\n");
						state++;
					}
					else if ((Sector[i] & 0xF0) == 0x20)
					{
						parentWindow->PrintToLog(L" *** Detected possible MPEG1 Stream.\n");
						state++;
					}
					else
					{
						parentWindow->PrintToLog(L" *** Detected invalid MPEG1 Stream.\n");
						state = 0;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 5:
				case 6:
					state++;
					break;
				case 7:
					if (true)
					{
						state = 8;
						parentWindow->PrintToLog(L"Stream found in sector %d, at offset %d...\n", sector, offset);
						streamLength = 8;
					}
					else
					{
						state = 0;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 8: //Copying until End1
					streamLength = streamLength + 1;
					if (Sector[i] == EndCode[4])
					{
						state = 13;
						offset = i;
					}
					break;
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
					if (Sector[i] == EndCode[state - 8])
					{
						state++;
					}
					else
					{
						state = 8;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
				case 15:
					if (Sector[i] == EndCode[7])
					{
						state = 0;
						wxString size = FormatSize(streamLength);
						parentWindow->PrintToLog(L"Stream End found in sector %d, at offset %d. Stream Length: %s.\n",sector,offset,size.c_str());
						streamLength = streamLength + 3;
						StreamItem t={sector,startOffset,streamLength};
						ListItems.push_back(t);
					}
					else
					{
						state = 8;
						if (offset > i)
						{
							sector--;
						}
						i = offset;
					}
					break;
			}
			i++;
		}

		if ((GetTickCount()-lastTicks) >= 1000)
		{
			parentWindow->SetFormCaption(L"Searching... sector %d of %d (%%%1.2f) --- State: %d --- Speed: %1.2f Kbytes/s",
				sector,
				LastSector,
				sector * 100.0f / LastSector,
				state,
				(2000.0f * (sector - prevSector) / (GetTickCount() - lastTicks)));
			lastTicks = GetTickCount();
			prevSector = sector;
		}
		sector++;
	}

	if ((state >= 8) && Processing)
	{
		state = 0;
		parentWindow->PrintToLog(L"Sector Limit Reached! The Stream might not be complete!\n");
	}

	parentWindow->PrintToLog(L"Done searching. Streams Found: %d.\n", ListItems.size());
}

void Process::Extract()
{
	parentWindow->PrintToLog(L" *** Destination: '%s'; Prefix: '%s'\n", path.c_str(), prefix.c_str());

	parentWindow->PrintToLog(L"Extracting...");

	Processing = true;

	int LastTicks = GetTickCount();

	for (unsigned int St = 0; St < ListItems.size(); St++)
	{
		int sector = ListItems[St].sector;
		int offset = ListItems[St].offset;
		int SLength = ListItems[St].length;
		int P = SLength;
		int Ls=sector;

		wxFileName fileName = wxFileName(path,prefix + wxString::Format(L"_%d_%d",sector,offset), L"mpg");

		parentWindow->PrintToLog(L"Extracting to '%s'...\n", fileName.GetFullPath().c_str());

		int Sectors = (SLength+offset)/2048;

		wxFile hFile;
		if (!hFile.Create(fileName.GetFullPath(),true))
		{
			parentWindow->PrintToLog(L"ERROR: Cannot Open file.\n");
		}
		else
		{
			while ((SLength > 0) && Processing)
			{
				int Tr = CDVDreadTrack(sector, CDVD_MODE_2048);
				CDVDgetBuffer2(Sector);

				int dlength = min(SLength, 2048-offset);

				hFile.Write(Sector+offset, dlength);

				SLength = SLength - dlength;

				offset = 0;
				sector++;

				if ((GetTickCount()-LastTicks) >= 1000)
				{
					parentWindow->SetFormCaption(L"Extracting... sector %d of %d (%%%1.2f) --- Speed: %1.2f Kbytes/s",
						sector,
						Sectors,
						sector * 100.0f / Sectors,
						(2000.0f * (sector - Ls) / (GetTickCount() - LastTicks)));
					LastTicks = GetTickCount();
					Ls = sector;
				}

				if (!Processing)
				{
					break;
				}
			}
			hFile.Close();
		}

		if (!Processing)
		{
			break;
		}
	}
	parentWindow->PrintToLog(L"Extraction Finished.\n");
}
