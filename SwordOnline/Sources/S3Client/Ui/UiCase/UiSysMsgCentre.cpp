/*******************Editer	: duccom0123 EditTime:	2024/06/12 11:48:43*********************
//	界面--系统消息中心
//	Copyright : Kingsoft 2003
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2003-4-15
*****************************************************************************************/
#include "KWin32.h"
#include "KIniFile.h"
#include "../Elem/Wnds.h"
#include "../Elem/WndMessage.h"
#include "UiSysMsgCentre.h"
#include "UiMsgCentrePad.h"
#include "UiInformation.h"
#include "UiInformation1.h"
#include "UiNewsSysMsg.h"
#include "UiStatus.h"
#include "UiSkills.h"
#include "UiTeamManage.h"
#include "UiPlayerBar.h"
#include "UiTaskNote.h"
#include "UiInit.h"
#include "UiConnectInfo.h"
#include "../UiBase.h"
#include "UiReconnect.h"
#include "../../../core/src/MsgGenreDef.h"
#include "../../../Engine/Src/Text.h"
#include "../../../Engine/Src/KDebug.h"
#include "../../../Represent/iRepresent/iRepresentShell.h"
#include "../../../core/src/coreshell.h"
#include "../UiShell.h"
#include <crtdbg.h>
#include "UiChatCentre.h"
#include "KTongProtocol.h"
#include "../ShortcutKey.h"

extern iCoreShell*		g_pCoreShell;
extern iRepresentShell*	g_pRepresentShell;

#define	SCHEME_INI					"UiSysMsgCentre.ini"
#define	SYSTEM_MSG_SENDER_NAME		"H" "\xD6" " th" "\xE8" "ng"
#define	MSG_LIST_EXPAND_STEP		4
#define	POPUP_MOVE_INTERVAL_DEF		20
#define MSG_DISAPPEAR_INTERVAL_DEF	30000
#define POPUP_MOVE_SPEED			24
#define	LAST_MOVEMENT_POS			-1
#define	MAX_MSG_IN_RECYCLE_HEAP		10

#define	MSG_BACK_TO_TOWN	"V" "\xD2" " th" "\xB5" "nh d" "\xAD" "\xEC" "ng s" "\xF8" "c"

#define	POP_UP_TIME			uReservedForUi

KUiSysMsgCentre*		KUiSysMsgCentre::m_pSelf = NULL;


//--------------------------------------------------------------------------
//	功能：构造函数
//--------------------------------------------------------------------------
KUiSysMsgCentre::KUiSysMsgCentre()
{
	m_SysMsgParam.cChatPrefixLen = 0;
	m_SysMsgParam.eGenre = MSG_G_CHAT;
	m_SysMsgParam.nMsgLength = 0;
	strcpy(m_SysMsgParam.szName, SYSTEM_MSG_SENDER_NAME);
	m_nPopupMsgDestX = 0;
	m_nPopupMsgX = LAST_MOVEMENT_POS;
	m_nPopupMsgDestIndex = 0;
	memset(&m_MsgHeap, 0, sizeof(m_MsgHeap));
	memset(&m_MsgIcon, 0, sizeof(m_MsgIcon));
	memset(&m_nMsgIconFrame, 0, sizeof(m_nMsgIconFrame));
	m_pHandlingMsg = NULL;
	m_bShowMsgText = false;
	m_uMoveInterval = POPUP_MOVE_INTERVAL_DEF;
	m_uDisappearInterval = MSG_DISAPPEAR_INTERVAL_DEF;
}

KUiSysMsgCentre::~KUiSysMsgCentre()
{
	Clear();
}

//--------------------------------------------------------------------------
//	功能：打开窗口，返回唯一的一个类对象实例
//--------------------------------------------------------------------------
KUiSysMsgCentre* KUiSysMsgCentre::OpenWindow()
{
	if (m_pSelf == NULL)
	{
		m_pSelf = new KUiSysMsgCentre;
		if (m_pSelf)
			m_pSelf->Initialize();
	}
	if (m_pSelf)
		m_pSelf->Show();
	return m_pSelf;
}

//--------------------------------------------------------------------------
//	功能：初始化
//--------------------------------------------------------------------------
void KUiSysMsgCentre::Initialize()
{
	AddChild(&m_MsgTextWnd);
	for (int i = 0; i < SMT_WAR; i++)
		AddChild(&m_MsgIconBtn[i]);

	m_Style &= ~WND_S_VISIBLE;
		
	char Scheme[128];
	g_UiBase.GetCurSchemePath(Scheme, 256);
	LoadScheme(Scheme);

	KIniFile* pSetting = g_UiBase.GetCommConfigFile();
	if (pSetting)
	{
		pSetting->GetInteger("Main", "SysMsgMoveInterval", POPUP_MOVE_INTERVAL_DEF, (int*)(&m_uMoveInterval));
		pSetting->GetInteger("Main", "SysMsgDisappearInterval", MSG_DISAPPEAR_INTERVAL_DEF, (int*)(&m_uDisappearInterval));
		g_UiBase.CloseCommConfigFile();
	}
	else
		m_uMoveInterval = POPUP_MOVE_INTERVAL_DEF;
	
	Wnd_AddWindow(this, WL_TOPMOST);
}

//--------------------------------------------------------------------------
//	功能：关闭窗口
//--------------------------------------------------------------------------
void KUiSysMsgCentre::CloseWindow()
{
	if (m_pSelf)
	{
		m_pSelf->Clear();
		m_pSelf->Destroy();
		m_pSelf = NULL;
	}
}


//--------------------------------------------------------------------------
//	功能：载入窗口的界面方案
//--------------------------------------------------------------------------
void KUiSysMsgCentre::LoadScheme(const char* pScheme)
{
	if (m_pSelf)
	{
		char		Buff[128];
		KIniFile	Ini;
		sprintf(Buff, "%s\\%s" , pScheme, SCHEME_INI);
		if (Ini.Load(Buff))
			m_pSelf->LoadScheme(&Ini);
	}
}

//--------------------------------------------------------------------------
//	功能：载入窗口的界面方案
//--------------------------------------------------------------------------
void KUiSysMsgCentre::LoadScheme(KIniFile* pIni)
{
	KWndWindow::Init(pIni, "Main");
	m_MsgTextWnd .Init(pIni, "MsgText");

	char		szBuf[16];
	for (int i = 0; i < SMT_WAR; i++)
	{
		sprintf(szBuf, "MsgIcon_%d", i + 1);
		m_MsgIconBtn[i].Init(pIni, szBuf);
		m_MsgIconBtn[i].RemoveImage();
//		m_MsgIconBtn[i].m_Image.szImage[0] = 0;
//		m_MsgIconBtn[i].m_Image.uImage = 0;
		m_MsgIcon[i].Color.Color_b.a = 255;
		m_MsgIcon[i].nFlipTime = 0;
		m_MsgIcon[i].nInterval = 0;
		m_MsgIcon[i].nNumFrames = 0;
		m_MsgIcon[i].nType = ISI_T_SPR;
		m_MsgIcon[i].bRenderStyle = IMAGE_RENDER_STYLE_ALPHA;
		m_MsgIcon[i].uImage = 0;
		m_MsgIcon[i].nISPosition = IMAGE_IS_POSITION_INIT;
		pIni->GetString (szBuf, "Image", "" , m_MsgIcon[i].szImage, sizeof(m_MsgIcon[i].szImage));
		int nValue;
		pIni->GetInteger(szBuf, "Frame", 0, &nValue);
		m_MsgIcon[i].nFrame = m_nMsgIconFrame[i] = nValue;
	}

	pIni->GetString("Main", "NormalMsgColor", "255,255,255", szBuf, sizeof(szBuf));
	unsigned int uColor = GetColor(szBuf);
	m_SysMsgParam.cChatPrefix[0] = KTC_COLOR;
	m_SysMsgParam.cChatPrefix[1] = (uColor >> 16) & 0xff;
	m_SysMsgParam.cChatPrefix[2] = (uColor >> 8) & 0xff;
	m_SysMsgParam.cChatPrefix[3] = uColor & 0xff;
	m_SysMsgParam.cChatPrefixLen = 4;
}

//--------------------------------------------------------------------------
//	功能：窗口函数
//--------------------------------------------------------------------------
int KUiSysMsgCentre::WndProc(unsigned int uMsg, unsigned int uParam, int nParam)
{
	int i, nRet = 0;
	switch(uMsg)
	{
	case WND_N_BUTTON_MR_DOWN:
	case WND_N_BUTTON_CLICK:
		for (i = 0; i < SMT_WAR; i++)
		{
			if (uParam == (unsigned int)(KWndWindow*)&m_MsgIconBtn[i])
			{
				DeleteMsgInHeap(i, 0, (uMsg == WND_N_BUTTON_MR_DOWN), true);
				break;
			}
		}
		break;
	case WND_N_BUTTON_LCLICK:
		for (i = 0; i < SMT_WAR; i++)
		{
			if (uParam == (unsigned int)(KWndWindow*)&m_MsgIconBtn[i])
			{
				DeleteMsgInHeap(i, 0, (uMsg == WND_N_BUTTON_MR_DOWN), false);
				break;
			}
		}
		break;
	case WND_N_MOUSE_ENTER_CHILD:
		for (i = 0; i < SMT_WAR; i++)
		{
			if (uParam == (unsigned int)(KWndWindow*)&m_MsgIconBtn[i])
			{
				m_MsgTextWnd.SetText("", 0);
				if (m_MsgHeap[i].nNumValid)
				{
					m_MsgTextWnd.SetText(m_MsgHeap[i].pMsgList[0]->szMessage);
					m_bShowMsgText = true;
				}
				break;
			}			
		}
		break;
	case WND_N_MOUSE_LEAVE_CHILD:
		m_MsgTextWnd.SetText("", 0);
		m_bShowMsgText = false;
		break;
	case WND_M_OTHER_WORK_RESULT:
		OnConfirmOperFinished(uParam, nParam);
		break;
	default:
		nRet = KWndWindow::WndProc(uMsg, uParam, nParam);
		break;
	}
	return nRet;
}

//响应操作结束，玩家已经做出选择。
void KUiSysMsgCentre::OnConfirmOperFinished(unsigned int uParam, int nSelAction)
{
	//_ASSERT(m_pHandlingMsg);
	KUiPlayerItem* pPlayer = NULL;
	switch(uParam)
	{
	case SMCT_UI_RENASCENCE:	//选择重生
		g_pCoreShell->OperationRequest(GOI_PLAYER_RENASCENCE, 0, nSelAction);//nSelAction=0：原地重生, nSelAction=1：回城
		break;
	case SMCT_UI_TEAM_INVITE:	//答应或拒绝加入队伍的邀请
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem))
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->TeamOperation(TEAM_OI_INVITE_RESPONSE,
				(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_TEAM_APPLY:	//答应或拒绝加入队伍的申请,
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem))
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->TeamOperation(TEAM_OI_APPLY_RESPONSE,
				(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_FRIEND_INVITE:	//批准或拒绝别人加自己为好友
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem));
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->OperationRequest(GOI_CHAT_FRIEND_INVITE,
				(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
			if (nSelAction == 0)
			{
				int nUnit = KUiChatCentre::FindUnitIndexByRoleNameAtServerUnit(pPlayer->Name);
				if (nUnit >= 0)
				{
					KUiChatCentre::DeleteFriend(nUnit, pPlayer->Name, false);
				}
				KUiChatCentre::AddFriendInfo(0, pPlayer->Name, "");
				KUiChatCentre::FriendStatus(0, pPlayer->Name, stateOnline);
			}
		}
		break;
	case SMCT_UI_TRADE:
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem));
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->OperationRequest(GOI_TRADE_INVITE_RESPONSE,
					(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_TRADE_FOLKGAME:
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem));
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->OperationRequest(GOI_TRADE_FOLKGAME_INVITE_RESPONSE,
					(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_SPAR:
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem));
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->OperationRequest(GOI_SPAR_INVITE_RESPONSE,
					(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_TONG_JOIN:
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem))
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->TongOperation(GTOI_TONG_JOIN,
				(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	case SMCT_UI_TONG_JOIN_APPLY:
		if (m_pHandlingMsg)
		{
			//_ASSERT(m_pHandlingMsg->byParamSize >= sizeof(KUiPlayerItem))
			pPlayer = (KUiPlayerItem*)(&m_pHandlingMsg[1]);
			g_pCoreShell->TongOperation(GTOI_TONG_JOIN_REPLY,
				(unsigned int)pPlayer, (nSelAction == 0));	//nSelAction=0：答应, nSelAction=1：拒绝
		}
		break;
	}
	if (m_pHandlingMsg)
	{
		if (m_MsgHeap[RECYCLE_MSG_HEAP_INDEX].nNumValid >= MAX_MSG_IN_RECYCLE_HEAP ||
			!AddAMsgToHeap(m_pHandlingMsg, RECYCLE_MSG_HEAP_INDEX, false))
		{
			free(m_pHandlingMsg);
		}
		m_pHandlingMsg = NULL;
	}
}

//判断一个点是否在窗口范围内,传入的是绝对坐标
int	KUiSysMsgCentre::PtInWindow(int x, int y)
{
	if (KWndWindow::PtInWindow(x, y))
	{
		for (int i = 0; i < SMT_WAR; i++)
		{
			if (m_MsgHeap[i].nNumValid && m_MsgIconBtn[i].PtInWindow(x, y))
				return (i + 1);
		}
	}
	return 0;
}

void KUiSysMsgCentre::Breathe()
{
	//让超时的消息消失
	int	i, j;
	for (i = 0; i < SMT_WAR; i++)
	{
		if (m_MsgHeap[i].nNumValid == 0)
			break;
		for (j = m_MsgHeap[i].nNumValid - 1;  j >= 0; j--)
		{
			KSystemMessage* pMsg = m_MsgHeap[i].pMsgList[j];
			if (pMsg->byConfirmType == SMCT_CLICK &&
				IR_IsTimePassed(m_uDisappearInterval * pMsg->byPriority + m_uDisappearInterval, pMsg->uReservedForUi))
			{
				DeleteMsgInHeap(i, j, true, false);
			}
		}
	}

	//移动正在弹出消息
	if (m_MsgHeap[POPUPING_MSG_HEAP_INDEX].nNumValid)
	{
		if (IR_IsTimePassed(m_uMoveInterval, m_uLastMovementTime))
		{
			m_nPopupMsgX -= POPUP_MOVE_SPEED;
			if (m_nPopupMsgX <= m_nPopupMsgDestX)
				MovePopupedMsgToHeap();
		}
	}
}

bool KUiSysMsgCentre::AMessageArrival(KSystemMessage* pMsg, void* pParam)
{
	if (pMsg == NULL || m_pSelf == NULL || 
		(pMsg->byParamSize != 0 && pParam == NULL))
		return false;
	if (pMsg->eType == SMT_NORMAL)
	{
		KUiMsgCentrePad::SystemMessageArrival(pMsg->szMessage, strlen(pMsg->szMessage));
		return true;
	}
	if (pMsg->byConfirmType == SMCT_UI_RENASCENCE)	//重生
	{
		UIMessageBox(pMsg->szMessage, m_pSelf, MSG_BACK_TO_TOWN, NULL, SMCT_UI_RENASCENCE, 5000);
		return true;
	}
	//过滤相同的消息
	if (pMsg->byConfirmType != SMCT_MSG_BOX)
	{
		if (m_pSelf->FilterSameMsg(pMsg, pParam))
			return true;
	}

	KSystemMessage* pCloneMsg = m_pSelf->GetAMsgSpace(pMsg->byParamSize);
	if (pCloneMsg)
	{
		memcpy(pCloneMsg, pMsg, sizeof(KSystemMessage) - sizeof(pMsg->byParamSize));
		if (pMsg->byParamSize && pParam)
			memcpy(&pCloneMsg[1], pParam, pMsg->byParamSize);
		if (m_pSelf->AddAMsgToHeap(pCloneMsg, POPUPING_MSG_HEAP_INDEX, false))
		{
			pCloneMsg->POP_UP_TIME = IR_GetCurrentTime();
			if (m_pSelf->m_MsgHeap[POPUPING_MSG_HEAP_INDEX].nNumValid == 1)
				m_pSelf->SetPopupMsgDest();
			return true;
		}
		free(pCloneMsg);
		pCloneMsg = NULL;
	}
	return false;
}

bool KUiSysMsgCentre::FilterSameMsg(KSystemMessage* pMsg, void* pParam)
{
	//_ASSERT(pMsg);
	int j;
	SYS_MSG_HEAP* pHeap = &m_MsgHeap[POPUPING_MSG_HEAP_INDEX];
	if (pHeap->nNumValid)
	{
		for (j = pHeap->nNumValid - 1; j >= 0; j--)
		{
			KSystemMessage* pHeapMsg = pHeap->pMsgList[j];
			if (pMsg->eType == pHeapMsg->eType &&
				pMsg->byConfirmType == pHeapMsg->byConfirmType &&
				pMsg->byPriority == pHeapMsg->byPriority &&
				pMsg->byParamSize <= pHeapMsg->byParamSize &&
				strcmp(pMsg->szMessage, pHeapMsg->szMessage) == 0)
			{
				if (pMsg->byParamSize == 0 ||
					memcmp(pParam, &pHeapMsg[1], pMsg->byParamSize) == 0)
				{
					return true;
				}
			}
		}
	}

	for (int nIndex = 0; nIndex < SMT_WAR; nIndex++)
	{
		pHeap = &m_MsgHeap[nIndex];
		if (pHeap->nNumValid == 0)
			break;
		if (pHeap->pMsgList[0]->eType != pMsg->eType)
			continue;
		for (int j = pHeap->nNumValid - 1; j >= 0; j--)
		{
			KSystemMessage* pHeapMsg = pHeap->pMsgList[j];
			if (pMsg->byConfirmType == pHeapMsg->byConfirmType &&
				pMsg->byPriority == pHeapMsg->byPriority &&
				pMsg->byParamSize <= pHeapMsg->byParamSize &&
				strcmp(pMsg->szMessage, pHeapMsg->szMessage) == 0)
			{
				if (pMsg->byParamSize == 0 ||
					memcmp(pParam, &pHeapMsg[1], pMsg->byParamSize) == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void KUiSysMsgCentre::Clear()
{
	for (int i = 0; i < SMT_WAR + 2; i++)
	{
		SYS_MSG_HEAP*	pHeap = &m_MsgHeap[i];
		if (pHeap->pMsgList)
		{
			for (int j = 0; j < pHeap->nNumValid; j++)
			{
				if (pHeap->pMsgList[j])
					free(pHeap->pMsgList[j]);
			}
			free(pHeap->pMsgList);
			pHeap->pMsgList = NULL;
			pHeap->nNumValid = 0;
			pHeap->nListSpace = 0;
		}
	}
	m_nPopupMsgX = LAST_MOVEMENT_POS;
	m_nPopupMsgDestIndex = 0;
}

KSystemMessage*	KUiSysMsgCentre::GetAMsgSpace(int nParamSize)
{
	KSystemMessage*	pMsgSpace = NULL;
	SYS_MSG_HEAP*	pHeap = &m_MsgHeap[RECYCLE_MSG_HEAP_INDEX];
	if (pHeap->nNumValid)
	{
		pHeap->nNumValid--;
		for (int i = pHeap->nNumValid; i >= 0; i--)
		{
			if (pHeap->pMsgList[i]->byParamSize >= nParamSize)
			{
				pMsgSpace = pHeap->pMsgList[i];
				for (; i < pHeap->nNumValid; i++)
					pHeap->pMsgList[i] = pHeap->pMsgList[i + 1];
				break;
			}
		}
		if (pMsgSpace == NULL)
		{
			free(pHeap->pMsgList[pHeap->nNumValid]);
			pHeap->pMsgList[pHeap->nNumValid] = NULL;
		}
	}
	if (pMsgSpace == NULL)
	{
		pMsgSpace = (KSystemMessage*)malloc(sizeof(KSystemMessage) + nParamSize);
		pMsgSpace->byParamSize = nParamSize;
	}
	return pMsgSpace;
}

void KUiSysMsgCentre::SetPopupMsgDest()
{
	if (m_MsgHeap[POPUPING_MSG_HEAP_INDEX].nNumValid)
	{
		unsigned char ePopupType = m_MsgHeap[POPUPING_MSG_HEAP_INDEX].pMsgList[0]->eType;
		for (m_nPopupMsgDestIndex = 0; m_nPopupMsgDestIndex < SMT_WAR;
			m_nPopupMsgDestIndex++)
		{
			if (m_MsgHeap[m_nPopupMsgDestIndex].nNumValid == 0 ||
				m_MsgHeap[m_nPopupMsgDestIndex].pMsgList[0]->eType == ePopupType)
			{
				break;
			}
		}
//		_ASSERT(m_nPopupMsgDestIndex < SMT_WAR);
		int	y;
		m_MsgIconBtn[m_nPopupMsgDestIndex].GetPosition(&m_nPopupMsgDestX, &y);
		m_nPopupMsgDestX += m_nAbsoluteLeft;
		if (m_nPopupMsgX == LAST_MOVEMENT_POS)
		{
			Wnd_GetScreenSize(m_nPopupMsgX, m_nPopupMsgY);
			m_nPopupMsgY = y + m_nAbsoluteTop;
		}
	}
}

void KUiSysMsgCentre::ConfirmMsg(KSystemMessage* pMsg, bool bImmedDel)
{
	if (pMsg == NULL)
		return;
	KUiPlayerItem*	pPlayer = NULL;
	unsigned int uSelMsgId = 0;
	char			szBuf[128] = "";
	const char		*pFirstBtnText = NULL, *pSecBtnText = NULL;
	unsigned char	byConfirmType = pMsg->byConfirmType;
	unsigned char	eType = pMsg->eType-1;

	switch(byConfirmType)
	{
	case SMCT_MSG_BOX:
		if (bImmedDel == false)
			UIMessageBox(pMsg->szMessage);
		break;
	case SMCT_UI_ATTRIBUTE:		//打开属性页面
		if (bImmedDel == false)
			KUiStatus::OpenWindow();
		break;
	case SMCT_UI_SKILLS:		//打开技能页面
		if (bImmedDel == false)
			KUiSkills::OpenWindow();
		break;
	case SMCT_UI_ATTRIBUTE_SKILLS:
		if (bImmedDel == false)
		{
			KUiStatus::OpenWindow();
			KUiSkills::OpenWindow();
		}
		break;
	case SMCT_UI_TEAM:			//打开队伍管理面板
		if (bImmedDel == false)
			KUiTeamManage::OpenWindow();
		break;
	case SMCT_UI_TEAM_INVITE:	//答应或拒绝加入队伍的邀请
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s m" "\xEA" "i b" "\xB9" "n gia nh" "\xCB" "p t" "\xE6" " " "\xAE" "\xE9" "i.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_TEAM_APPLY:	//答应或拒绝加入队伍的申请
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s xin gia nh" "\xCB" "p " "\xAE" "\xE9" "i c" "\xF1" "a b" "\xB9" "n.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_INTERVIEW:		//打开聊天对话界面
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		KUiPlayerBar::InputNameMsg(false, pPlayer->Name, true);
		break;
	case SMCT_UI_FRIEND_INVITE:	//批准或拒绝别人加自己为好友
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s mu" "\xE8" "n k" "\xD5" "t giao h" "\xB6" "o h" "\xF7" "u v" "\xED" "i b" "\xB9" "n.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_TRADE:
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s m" "\xEA" "i " "\xAE" "\xAD" "\xEE" "c giao d" "\xDE" "ch v" "\xED" "i b" "\xB9" "n.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_TRADE_FOLKGAME:
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s m" "\xEA" "i " "\xAE" "\xCA" "u " "\xAE" "\xE8" " thu" "\xCB" "t v" "\xED" "i b" "\xB9" "n.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_SPAR:
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s m" "\xEA" "i ng" "\xAD" "\xAC" "i c" "\xEF" "ng t" "\xFB" " th" "\xDD" " v" "\xE2" " ngh" "\xD6" ".", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_TONG_JOIN:
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s xin ph" "\xD0" "p gia nh" "\xCB" "p Bang.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	case SMCT_UI_TONG_JOIN_APPLY:
		_ASSERT (pMsg->byParamSize >= sizeof(KUiPlayerItem));
		pPlayer = (KUiPlayerItem*)(&pMsg[1]);
		sprintf(szBuf, "%s m" "\xEA" "i b" "\xB9" "n gia nh" "\xCB" "p Bang.", pPlayer->Name);
		pFirstBtnText = "\xA7" "\xE5" "ng " "\xFD" "!";
		pSecBtnText = "C" "\xF9" " tuy" "\xD6" "t";
		_ASSERT(m_pHandlingMsg == NULL);
		m_pHandlingMsg = pMsg;
		pMsg = NULL;
		break;
	}
	if (szBuf[0])
		UIMessageBox1(szBuf, strlen(szBuf), this, pFirstBtnText, pSecBtnText, byConfirmType, m_MsgIcon[eType].szImage);

	if (pMsg &&
		(m_MsgHeap[RECYCLE_MSG_HEAP_INDEX].nNumValid >= MAX_MSG_IN_RECYCLE_HEAP ||
		!AddAMsgToHeap(pMsg, RECYCLE_MSG_HEAP_INDEX, false)))
	{
		free(pMsg);
	}
}

void KUiSysMsgCentre::DeleteMsgInHeap(int nHeapIndex, int nMsgIndex, bool bImmedDel, bool bTobeConfirm)
{
	int i;
	//_ASSERT(nHeapIndex >= 0 && nHeapIndex <= POPUPING_MSG_HEAP_INDEX);
	SYS_MSG_HEAP*	pHeap = &m_MsgHeap[nHeapIndex];
	if (nMsgIndex >= 0 && nMsgIndex < pHeap->nNumValid)
	{
		if (bTobeConfirm)
		{
			ConfirmMsg(pHeap->pMsgList[nMsgIndex], bImmedDel);
		}
		else if (m_MsgHeap[RECYCLE_MSG_HEAP_INDEX].nNumValid >= MAX_MSG_IN_RECYCLE_HEAP ||
				!AddAMsgToHeap(pHeap->pMsgList[nMsgIndex], RECYCLE_MSG_HEAP_INDEX, false))
		{
			free(pHeap->pMsgList[nMsgIndex]);
		}

		pHeap->nNumValid--;
		for (i = nMsgIndex; i < pHeap->nNumValid; i++)
		{
			pHeap->pMsgList[i] = pHeap->pMsgList[i + 1];
		}
		pHeap->pMsgList[pHeap->nNumValid] = NULL;

		if (pHeap->nNumValid)
		{
			m_MsgTextWnd.SetText(pHeap->pMsgList[0]->szMessage);
		}
		else
		{
			SYS_MSG_HEAP	temp;
			temp = *pHeap;
			for (; nHeapIndex < SMT_WAR - 1; nHeapIndex ++)
			{
				if (pHeap[1].nNumValid == 0)
					break;
				*pHeap = pHeap[1];
				pHeap++;
			}
			*pHeap = temp;
			SetPopupMsgDest();
			m_MsgTextWnd.Clear();
			m_bShowMsgText = false;
		}
	}
}

void KUiSysMsgCentre::MovePopupedMsgToHeap()
{
	int i;
	SYS_MSG_HEAP* pHeap = &m_MsgHeap[POPUPING_MSG_HEAP_INDEX];
	if (pHeap->nNumValid)
	{
		m_nPopupMsgX = LAST_MOVEMENT_POS;
		KSystemMessage* pMsg = pHeap->pMsgList[0];
		pHeap->nNumValid--;
		for (i = 0; i < pHeap->nNumValid; i++)
		{
			pHeap->pMsgList[i] = pHeap->pMsgList[i + 1];
		}
		pHeap->pMsgList[pHeap->nNumValid] = NULL;

		if (!AddAMsgToHeap(pMsg, m_nPopupMsgDestIndex, true))
			free (pMsg);
		pMsg = NULL;
		if (pHeap->nNumValid)
			SetPopupMsgDest();
	}
}

bool KUiSysMsgCentre::AddAMsgToHeap(KSystemMessage* pMsg, int nHeapIndex, bool bSort)
{
	//_ASSERT(pMsg);
	//_ASSERT(nHeapIndex >= 0 && nHeapIndex <= RECYCLE_MSG_HEAP_INDEX);
	SYS_MSG_HEAP*	pHeap = &m_MsgHeap[nHeapIndex];
	if (pHeap->nNumValid == pHeap->nListSpace)
	{
		KSystemMessage** pNewList = (KSystemMessage**)realloc(pHeap->pMsgList,
			sizeof(KSystemMessage*) * (pHeap->nListSpace + MSG_LIST_EXPAND_STEP));
		if (pNewList)
		{
			memset(&pNewList[pHeap->nNumValid], 0, sizeof(KSystemMessage*) * MSG_LIST_EXPAND_STEP);
			pHeap->pMsgList = pNewList;
			pHeap->nListSpace += MSG_LIST_EXPAND_STEP;
		}
		else
		{
			return false;
		}
	}

	int nIndex = pHeap->nNumValid;
	if (bSort)
	{
		for (nIndex--; nIndex >= 0; nIndex--)
		{
			if (pHeap->pMsgList[nIndex]->byPriority > pMsg->byPriority)
			{
				break;
			}
			pHeap->pMsgList[nIndex + 1] = pHeap->pMsgList[nIndex];
		}
		nIndex ++;
	}

	pHeap->pMsgList[nIndex] = pMsg;
	pHeap->nNumValid++;
	return true;
}

//绘制窗口
void KUiSysMsgCentre::PaintWindow()
{
	KWndWindow::PaintWindow();
	unsigned char eType;
	int  nFrame, i;
	bool bAlreadyChangeFrame = false;

	if (m_bShowMsgText)
	{
		KRUShadow	Shadow;
		m_MsgTextWnd.GetPosition(&Shadow.oPosition.nX, &Shadow.oPosition.nY);
		Shadow.oPosition.nX += m_nAbsoluteLeft;
		Shadow.oPosition.nY += m_nAbsoluteTop;
		Shadow.oPosition.nZ = 0;
		m_MsgTextWnd.GetSize(&Shadow.oEndPos.nX, &Shadow.oEndPos.nY);
		Shadow.oEndPos.nX += Shadow.oPosition.nX;
		Shadow.oEndPos.nY += Shadow.oPosition.nY;
		Shadow.Color.Color_dw = 0x10000000;
		g_pRepresentShell->DrawPrimitives(1, &Shadow, RU_T_SHADOW, true);
	}

	for (i = 0; i < SMT_WAR; i++)
	{
		if (m_MsgHeap[i].nNumValid == 0)
			break;
		eType = m_MsgHeap[i].pMsgList[0]->eType - 1;
		m_MsgIconBtn[i].GetPosition(&m_MsgIcon[eType].oPosition.nX, 
			&m_MsgIcon[eType].oPosition.nY);
		m_MsgIcon[eType].oPosition.nX += m_nAbsoluteLeft;
		m_MsgIcon[eType].oPosition.nY += m_nAbsoluteTop;
		if (m_MsgHeap[i].pMsgList[0]->byConfirmType != SMCT_CLICK)
		{
			if (i == m_nPopupMsgDestIndex)
				bAlreadyChangeFrame = true;
			IR_NextFrame(m_MsgIcon[eType]);
			g_pRepresentShell->DrawPrimitives(1, &m_MsgIcon[eType], RU_T_IMAGE, true);
		}
		else
		{
			nFrame = m_MsgIcon[eType].nFrame;
			m_MsgIcon[eType].nFrame = m_nMsgIconFrame[eType];
			g_pRepresentShell->DrawPrimitives(1, &m_MsgIcon[eType], RU_T_IMAGE, true);
			m_MsgIcon[eType].nFrame = nFrame;
		}
	}
	if (m_MsgHeap[POPUPING_MSG_HEAP_INDEX].nNumValid)
	{
		eType = m_MsgHeap[POPUPING_MSG_HEAP_INDEX].pMsgList[0]->eType - 1;
		m_MsgIcon[eType].oPosition.nX = m_nPopupMsgX;
		m_MsgIcon[eType].oPosition.nY = m_nPopupMsgY;
		g_pRepresentShell->DrawPrimitives(1, &m_MsgIcon[eType], RU_T_IMAGE, true);

		if (m_MsgHeap[POPUPING_MSG_HEAP_INDEX].pMsgList[0]->byConfirmType != SMCT_CLICK)
		{
			if (bAlreadyChangeFrame == false)
				IR_NextFrame(m_MsgIcon[eType]);
			g_pRepresentShell->DrawPrimitives(1, &m_MsgIcon[eType], RU_T_IMAGE, true);
		}
		else
		{
			nFrame = m_MsgIcon[eType].nFrame;
			m_MsgIcon[eType].nFrame = m_nMsgIconFrame[eType];
			g_pRepresentShell->DrawPrimitives(1, &m_MsgIcon[eType], RU_T_IMAGE, true);
			m_MsgIcon[eType].nFrame = nFrame;
		}
	}
}