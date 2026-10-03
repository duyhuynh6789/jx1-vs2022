// -------------------------------------------------------------------------
//	文件名		：	UiReconnect.h
//	创建者		：	Freeway Chen
//	创建时间	：	2003-7-18
//	功能描述	：	自动重连的流程控制	
// -------------------------------------------------------------------------
#include "KWin32.h"
#include "KIniFile.h"
#include "../Elem/WndMessage.h"
#include "../Elem/Wnds.h"
#include "UiReconnect.h"
#include "UiInformation.h"
#include "UiSysMsgCentre.h"
#include "../UiShell.h"
#include "../UiCase/UiInit.h"
#include "../Elem/UiImage.h"
#include "../UiBase.h"
#include "../../Login/Login.h"
#include "../../../Engine/Src/Text.h"
#include "../../../Engine/Src/KDebug.h"
#include <crtdbg.h>

#define	MSG_RECONNECTING				"H" "\xD6" " th" "\xE8" "ng " "\xAE" "ang k" "\xD5" "t n" "\xE8" "i l" "\xB9" "i l" "\xC7" "n th" "\xF8" " <color=255,0,0>%d<color>\n%s"
#define	MSG_WAIT_TO_RECONNECT			"Ti" "\xD5" "n h" "\xB5" "nh k" "\xD5" "t n" "\xE8" "i l" "\xB9" "i trong %d gi" "\xA9" "y (l" "\xC7" "n th" "\xF8" " <color=255,0,0>%d<color>)"
#define	MSG_WAIT_NEXT_GROUP_RECONNECT	"Ti" "\xD5" "n h" "\xB5" "nh k" "\xD5" "t n" "\xE8" "i l" "\xB9" "i trong %d gi" "\xA9" "y"
#define	MSG_HIDE_RECONNECT_MSG_ID		"21"

//两组断线重连的间隔时间，单位毫秒
#define RECONNECT_GROUP_INTERVAL		60000
//两次断线重连的间隔时间，单位毫秒
#define RECONNECT_INTERVAL				10000
//开始时不可见的重连的次数
#define INVISIBLE_RECONNECT_TIMES		3
//不可见的两次断线重连的间隔时间，单位毫秒
#define INVISIBLE_RECONNECT_INTERVAL	5000

//取消重连的按钮的文字
#define	RECONNECT_QUIT_BTN_LABEL	"Tho" "\xB8" "t"
//立即重连的按钮的文字
#define	RECONNECT_START_AT_ONCE		"K" "\xD5" "t n" "\xE8" "i l" "\xB9" "i"

KReconnectWnd*	KReconnectWnd::m_pSelf = NULL;

bool KReconnectWnd::LaunchReconnect(int nMaxTimes)
{
	_ASSERT(m_pSelf == NULL);
	if (m_pSelf == NULL)
		m_pSelf = new KReconnectWnd;
	if (m_pSelf)
	{
		m_pSelf->m_bStop = false;
		Wnd_AddWindow(m_pSelf, WL_TOPMOST);
		if (nMaxTimes >= 1)
			m_pSelf->m_nMaxReconnectTimes = nMaxTimes;
		else
			m_pSelf->m_nMaxReconnectTimes = 1;
		m_pSelf->FirstReconnect();
	}
	else
	{
		Exit(true);
	}
	return (m_pSelf != NULL);
}

bool KReconnectWnd::IsReconnecttingGoingOn()
{
	return (m_pSelf != NULL);
}

void KReconnectWnd::FirstReconnect()
{
	m_nReconnectTimes = 0;
	m_bWaitToReconnect = true;
	m_uWaitStartTime = IR_GetCurrentTime();
	m_uToWaitTime = rand () % INVISIBLE_RECONNECT_INTERVAL + 1000;

	KIniFile* pConfig = g_UiBase.GetCommConfigFile();
	m_nHideTimes = INVISIBLE_RECONNECT_TIMES;
	if (pConfig)
	{
		pConfig->GetInteger("Main", "AutoReconnectHideTimes", 3, &m_nHideTimes);
		if (m_nHideTimes < 0)
			m_nHideTimes = 0;
	}
}

bool KReconnectWnd::StartReconnect()
{
	if (m_nHideTimes > 0 ||
		(++m_nReconnectTimes) < m_nMaxReconnectTimes)
	{
		/*if (m_nHideTimes > 0)
		{
			KSystemMessage	Msg;
			Msg.byConfirmType = SMCT_NONE;
			Msg.byParamSize = 0;
			Msg.byPriority = 0;
			Msg.eType = SMT_NORMAL;
			Msg.uReservedForUi = 0;

			KIniFile*	pIni = g_UiBase.GetCommConfigFile();
			if (pIni)
			{
				if (pIni->GetString("InfoString", MSG_HIDE_RECONNECT_MSG_ID,
					"", Msg.szMessage, sizeof(Msg.szMessage)))
				{
					KUiSysMsgCentre::AMessageArrival(&Msg, NULL);
				}
				g_UiBase.CloseCommConfigFile();
			}
		}*/

		g_LoginLogic.ReturnToIdle();
		g_LoginLogic.AutoLogin();
		m_bWaitToReconnect = false;
	}
	else
	{
		m_nReconnectTimes = 0;
		m_pSelf->m_bWaitToReconnect = true;
		m_pSelf->m_uWaitStartTime = IR_GetCurrentTime();
		m_pSelf->m_uToWaitTime = RECONNECT_GROUP_INTERVAL;
	}
	return true;
}

void KReconnectWnd::Exit(bool bQuitGame)
{
	if (m_pSelf)
	{
		m_pSelf->Destroy();
		m_pSelf = NULL;
	}
	if (bQuitGame)
	{
		g_LoginLogic.ReturnToIdle();
		UiEndGame();
		KUiInit::OpenWindow(true, false);
	}
}

// 用来控制下一次重连的时间
void KReconnectWnd::Breathe()
{
	if (m_bStop)
		return;
	char	szInfo[256];
	int		nInfoLen;
	if (m_bWaitToReconnect)
	{	//====等待进行下次自动重连====
		unsigned int uRemain;
		if (uRemain = IR_GetRemainTime(m_uToWaitTime, m_uWaitStartTime))
		{
			if (m_nHideTimes == 0)
			{
				if (uRemain < RECONNECT_INTERVAL)
				{
					nInfoLen = sprintf(szInfo, MSG_WAIT_TO_RECONNECT,
						(uRemain + 999)/ 1000, m_nReconnectTimes + 1);
				}
				else
				{
					nInfoLen = sprintf(szInfo, MSG_WAIT_NEXT_GROUP_RECONNECT,
						(uRemain + 999) / 1000);
				}			
				nInfoLen = TEncodeText(szInfo, nInfoLen);
				g_UiInformation.Show(szInfo, RECONNECT_QUIT_BTN_LABEL, RECONNECT_START_AT_ONCE, this, 0, nInfoLen);
			}
		}
		else
		{	//====开始下次自动重连====
			StartReconnect();
		}
		return;
	}

	LOGIN_LOGIC_STATUS eStatus = g_LoginLogic.GetStatus();
	const char* pReconnectMsg = NULL;
	switch (eStatus)
	{
	case LL_S_IN_GAME://====重连成功====
		g_UiInformation.Close();
		UiResumeGame();
		Exit(false);
		break;
	case LL_S_IDLE:	//====重连失败====
		{
			LOGIN_LOGIC_RESULT_INFO eResult= g_LoginLogic.GetResult();
			if (eResult == LL_R_ACCOUNT_NOT_ENOUGH_POINT)
			{
				m_bStop = true;
				pReconnectMsg = "Kh" "\xAB" "ng " "\xAE" "\xF1" " th" "\xEA" "i gian " "\xAE" "\xD3" " ch" "\xAC" "i!. H" "\xB7" "y n" "\xB9" "p card " "\xAE" "\xD3" " ti" "\xD5" "p t" "\xF4" "c tr" "\xDF" " ch" "\xAC" "i!";
			}
			else if (eResult == LL_R_ACCOUNT_FREEZE)
			{
				m_bStop = true;
				pReconnectMsg = "T" "\xB5" "i kho" "\xB6" "n n" "\xB5" "y " "\xAE" "\xB7" " b" "\xDE" " kh" "\xE3" "a";
			}
			else
			{
				m_bWaitToReconnect = true;
				m_uWaitStartTime = IR_GetCurrentTime();
				if (m_nHideTimes > 0)
				{
					m_nHideTimes--;
					m_uToWaitTime = INVISIBLE_RECONNECT_INTERVAL;
				}
				else
				{
					m_uToWaitTime = RECONNECT_INTERVAL;
					pReconnectMsg = "K" "\xD5" "t n" "\xE8" "i th" "\xCA" "t b" "\xB9" "i";
				}
			}
		}
		break;
	case LL_S_ACCOUNT_CONFIRMING:	//等待账号密码验证
		pReconnectMsg = "\xA7" "ang ti" "\xD5" "n h" "\xB5" "nh ki" "\xD3" "m tra t" "\xB5" "i kho" "\xB6" "n v" "\xB5" " m" "\xCB" "t kh" "\xC8" "u";
		break;
	case LL_S_WAIT_ROLE_LIST:		//等待接收角色列表数据
		pReconnectMsg = "\xA7" "ang nh" "\xCB" "n danh s" "\xB8" "ch nh" "\xA9" "n v" "\xCB" "t";
		break;
	case LL_S_WAIT_TO_LOGIN_GAMESERVER:	//等待登陆游戏服务器
		pReconnectMsg = "\xA7" "ang ph" "\xF4" "c v" "\xF4" " tr" "\xDF" " ch" "\xAC" "i";
		break;
	case LL_S_ENTERING_GAME:		//正在进入游戏
		pReconnectMsg = "\xA7" "ang " "\xAE" "\xA8" "ng nh" "\xCB" "p v" "\xB5" "o tr" "\xDF" " ch" "\xAC" "i";
		break;
	}

	if (m_bStop)
	{
		nInfoLen = strlen(pReconnectMsg);
		g_UiInformation.Show(pReconnectMsg, RECONNECT_QUIT_BTN_LABEL, NULL, this, 0, nInfoLen);
	}
	else if (pReconnectMsg && m_nHideTimes == 0)
	{
		nInfoLen = sprintf(szInfo, MSG_RECONNECTING,
				m_nReconnectTimes + 1, pReconnectMsg);
		nInfoLen = TEncodeText(szInfo, nInfoLen);
		g_UiInformation.Show(szInfo, RECONNECT_QUIT_BTN_LABEL, NULL, this, 0, nInfoLen);
	}
}

int KReconnectWnd::WndProc(unsigned int uMsg, unsigned int uParam, int nParam)//窗口函数
{
	if (uMsg == WND_M_OTHER_WORK_RESULT)
	{
		if (nParam == 1)	//立即重连
		{
			StartReconnect();
			Breathe();
		}
		else
			Exit(true);		//取消，退出游戏
	}
	return 0;
}
