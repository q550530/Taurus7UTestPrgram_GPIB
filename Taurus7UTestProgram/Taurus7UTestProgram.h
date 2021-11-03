
// Taurus7UTestProgram.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTaurus7UTestProgramApp:
// See Taurus7UTestProgram.cpp for the implementation of this class
//

class CTaurus7UTestProgramApp : public CWinApp
{
public:
	CTaurus7UTestProgramApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTaurus7UTestProgramApp theApp;