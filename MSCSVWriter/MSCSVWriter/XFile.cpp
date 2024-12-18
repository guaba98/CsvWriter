// XFile.cpp: implementation of the CXFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "controlserver.h"
#include "XFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXFile::CXFile()
{

}

CXFile::~CXFile()
{

}

BOOL CXFile::XCreateDirectory(CString strPath)
{
	CString strTmp;
	BOOL bRet = TRUE;
	int nStt = 0,nlen = strPath.GetLength();

	if(strPath.Find(_T("\\"),0)<0)
		bRet = FALSE;
	while(nlen>=nStt && bRet)
	{
		nStt = strPath.Find(_T("\\"),nStt);
		if(nStt<0)
			break;
		nStt++;
		strTmp = strPath.Left(nStt);
		CreateDirectory(strTmp,NULL);
		if(::GetFileAttributes(strTmp)==-1) //API �Լ��� ����ϰ� ���ϰ��� -1 (INVALID_FILE_ATTRIBUTES)�̸� ���� �Ǵ� ���丮�� �������� �ʴ� ��� �Դϴ�.
			bRet = FALSE;
	}
	return bRet;
}
