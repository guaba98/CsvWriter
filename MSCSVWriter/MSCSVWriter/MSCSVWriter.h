
// MSCSVWriter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMSCSVWriterApp:
// �� Ŭ������ ������ ���ؼ��� MSCSVWriter.cpp�� �����Ͻʽÿ�.
//

class CMSCSVWriterApp : public CWinApp
{
public:
	CMSCSVWriterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMSCSVWriterApp theApp;