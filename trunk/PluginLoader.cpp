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
#include <windows.h>

#define CDVDdefs
#include "PS2Edefs.h"

//#define CE(x) if( x != 0 ) return (*x)
#define CE(x) if( x == 0 ) return 0; else return (*x)
#define CEV(x) if( x != 0 ) (*x)

typedef u32  (CALLBACK* t_PS2EgetLibType)(void);
typedef u32  (CALLBACK* t_PS2EgetLibVersion2)(u32 type);
typedef char*(CALLBACK* t_PS2EgetLibName)(void);
typedef s32  (CALLBACK* t_CDVDinit)();
typedef s32  (CALLBACK* t_CDVDopen)(const char* pTitleFilename);
typedef void (CALLBACK* t_CDVDclose)();
typedef void (CALLBACK* t_CDVDshutdown)();
typedef s32  (CALLBACK* t_CDVDreadTrack)(u32 lsn, int mode);
typedef u8*  (CALLBACK* t_CDVDgetBuffer)();
typedef s32  (CALLBACK* t_CDVDgetBuffer2)(u8* buffer);
typedef s32  (CALLBACK* t_CDVDgetTN)(cdvdTN *Buffer);
typedef s32  (CALLBACK* t_CDVDgetTD)(u8 Track, cdvdTD *Buffer);
typedef s32  (CALLBACK* t_CDVDgetDiskType)();
typedef s32  (CALLBACK* t_CDVDgetTrayStatus)();
typedef void (CALLBACK* t_CDVDconfigure)();
typedef s32  (CALLBACK* t_CDVDtest)();
typedef void (CALLBACK* t_CDVDabout)();

typedef s32  (CALLBACK* t_CDVDreadSubQ)(u32 lsn, void* subq);
typedef s32  (CALLBACK* t_CDVDgetTOC)(void* toc);				//gets ps2 style toc from disc
typedef s32  (CALLBACK* t_CDVDctrlTrayOpen)();					//open disc tray
typedef s32  (CALLBACK* t_CDVDctrlTrayClose)();					//close disc tray

typedef void (CALLBACK* t_CDVDnewDiskCB)(void (*callback)());

u32  (CALLBACK* _PS2EgetLibType)(void);
u32  (CALLBACK* _PS2EgetLibVersion2)(u32 type);
char*(CALLBACK* _PS2EgetLibName)(void);
s32  (CALLBACK* _CDVDinit)();
s32  (CALLBACK* _CDVDopen)(const char* pTitleFilename);
void (CALLBACK* _CDVDclose)();
void (CALLBACK* _CDVDshutdown)();
s32  (CALLBACK* _CDVDreadTrack)(u32 lsn, int mode);
u8*  (CALLBACK* _CDVDgetBuffer)();
s32  (CALLBACK* _CDVDgetBuffer2)(u8* buffer);
s32  (CALLBACK* _CDVDgetTN)(cdvdTN *Buffer);
s32  (CALLBACK* _CDVDgetTD)(u8 Track, cdvdTD *Buffer);
s32  (CALLBACK* _CDVDgetDiskType)();
s32  (CALLBACK* _CDVDgetTrayStatus)();
void (CALLBACK* _CDVDconfigure)();
s32  (CALLBACK* _CDVDtest)();
void (CALLBACK* _CDVDabout)();

s32  (CALLBACK* _CDVDreadSubQ)(u32 lsn, void* subq);
s32  (CALLBACK* _CDVDgetTOC)(void* toc);				//gets ps2 style toc from disc
s32  (CALLBACK* _CDVDctrlTrayOpen)();					//open disc tray
s32  (CALLBACK* _CDVDctrlTrayClose)();					//close disc tray

void (CALLBACK* _CDVDnewDiskCB)(void (*callback)());

HMODULE hLib;

int lastSize = 0;

u32   CALLBACK PS2EgetLibType(void) { CE(_PS2EgetLibType)(); }
u32   CALLBACK PS2EgetLibVersion2(u32 type) { CE(_PS2EgetLibVersion2)(type); }
char* CALLBACK PS2EgetLibName(void) { CE(_PS2EgetLibName)(); }

s32  CALLBACK CDVDinit() { CE(_CDVDinit)(); }
s32  CALLBACK CDVDopen(const char* pTitleFilename) { CE(_CDVDopen)(pTitleFilename); }
void CALLBACK CDVDclose() { CEV(_CDVDclose)(); }
void CALLBACK CDVDshutdown() { CEV(_CDVDshutdown)(); }
s32  CALLBACK CDVDreadTrack(u32 lsn, int mode) 
{
	lastSize = (mode == CDVD_MODE_2048)?2048:2352;
	CE(_CDVDreadTrack)(lsn,mode); 
}
u8*  CALLBACK CDVDgetBuffer() { CE(_CDVDgetBuffer)(); }
s32  CALLBACK CDVDgetBuffer2(u8* buffer) 
{
	if(_CDVDgetBuffer2)
	{
		CE(_CDVDgetBuffer2)(buffer); 
	}
	else if(_CDVDgetBuffer)
	{
		u8* pb = _CDVDgetBuffer();
		if(!pb) return -1;
		memcpy(buffer,pb,lastSize);
		return 0;
	}
	return -1;
}
s32  CALLBACK CDVDgetTN(cdvdTN *Buffer) { CE(_CDVDgetTN)(Buffer); }
s32  CALLBACK CDVDgetTD(u8 Track, cdvdTD *Buffer) { CE(_CDVDgetTD)(Track,Buffer); }
s32  CALLBACK CDVDgetDiskType() { CE(_CDVDgetDiskType)(); }
s32  CALLBACK CDVDgetTrayStatus() { CE(_CDVDgetTrayStatus)(); }
void CALLBACK CDVDconfigure() { CEV(_CDVDconfigure)(); }
void CALLBACK CDVDabout() { CEV(_CDVDabout)(); }
s32  CALLBACK CDVDtest() { CE(_CDVDtest)(); }

s32  CALLBACK CDVDreadSubQ(u32 lsn, void* subq) { CE(_CDVDreadSubQ)(lsn,subq); }
s32  CALLBACK CDVDgetTOC(void* toc) { CE(_CDVDgetTOC)(toc); }
s32  CALLBACK CDVDctrlTrayOpen() { CE(_CDVDctrlTrayOpen)(); }
s32  CALLBACK CDVDctrlTrayClose() { CE(_CDVDctrlTrayClose)(); }
void CALLBACK CDVDnewDiskCB(void (*callback)()) { CEV(_CDVDnewDiskCB)(callback); }

// wrapper functions

#define LOADSYM(x) _##x = (t_##x)GetProcAddress(hLib,#x);

void CALLBACK WrapFree()
{
	if(hLib!=0) FreeLibrary(hLib);
	hLib=0;
}

s32  CALLBACK WrapLoad(const wchar_t *LibName)
{
	WrapFree(); //just to be sure

	hLib = LoadLibrary(LibName);

	if(!hLib) return 0;

	LOADSYM(PS2EgetLibType);
	LOADSYM(PS2EgetLibVersion2);
	LOADSYM(PS2EgetLibName);
	LOADSYM(CDVDinit);
	LOADSYM(CDVDopen);
	LOADSYM(CDVDclose);
	LOADSYM(CDVDshutdown);
	LOADSYM(CDVDreadTrack);
	LOADSYM(CDVDgetBuffer);
	LOADSYM(CDVDgetTN);
	LOADSYM(CDVDgetTD);
	LOADSYM(CDVDgetDiskType);
	LOADSYM(CDVDgetTrayStatus);
	LOADSYM(CDVDconfigure);
	LOADSYM(CDVDabout);
	LOADSYM(CDVDtest);
	LOADSYM(CDVDreadSubQ);
	LOADSYM(CDVDgetTOC);
	LOADSYM(CDVDctrlTrayOpen);
	LOADSYM(CDVDctrlTrayClose);
	LOADSYM(CDVDnewDiskCB);

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if(fdwReason==DLL_PROCESS_ATTACH) hLib=0;
	if(fdwReason==DLL_PROCESS_DETACH) WrapFree();
	return TRUE;
}
