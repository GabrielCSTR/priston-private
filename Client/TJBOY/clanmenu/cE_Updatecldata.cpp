#include "StdAfx.h"
#define CE_UPDATECLDATA_CPP

#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include <stdio.h>
#include "tjclan.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "cE_Updatecldata.h"
#include "..\\ygy\\ygyheader.h"


//Ŭ��������������� Ŭ���� ���Խ� Ŭ������Ÿ�� ������Ʈ �϶�� �����Ѵ�.

CUpdateCldata::CUpdateCldata()
{
}

CUpdateCldata::~CUpdateCldata()
{
}


void CUpdateCldata::Updatecldata()
{
	static int cnt = 0;
	extern char updateis[256];
	wsprintf(updateis, "Updatecldata : %d ", cnt++);

	WebDB.Resume();		//��db�� �簳�Ѵ�.
	WebDB.Updatcldata(cldata.szID, cldata.gserver, cldata.ChaName);
}


//auth.cpp���� �����.
void g_UpdateCldata_Close() //������ ����
{
	g_UpdateCldata.Close();




#ifdef VOICE_CHAT
	if (bCheckClan)
	{
		if (cldata.intClanMark) {

			g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
				cldata.name, (DWORD)cldata.intClanMark, cldata.myPosition);
		}
		else {

			g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
				NULL, 0, cldata.myPosition);
		}
		//bCheckClan = FALSE;
	}
#endif


}

extern int downClanSu;		//Ŭ�������� ����bmp�޴� �κе� ýũ�� �����ҵ����
void CUpdateCldata::Close()
{
	if (OpenFlag == 0 && downClanSu == 0) {	//Ŭ�������� ����bmp�޴� �κе� ýũ�� �����ҵ����
		WebDB.Suspend();			//����� ���δ�.
	}
}