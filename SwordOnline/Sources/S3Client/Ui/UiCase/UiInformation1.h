/*******************Editer	: duccom0123 EditTime:	2024/06/12 11:48:45*********************
//	界面--消息窗口
//	Copyright : Kingsoft 2002
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2002-8-14
------------------------------------------------------------------------------------------
*****************************************************************************************/
#pragma once

#include "../Elem/WndText.h"
#include "../Elem/WndImage.h"
#include "../Elem/WndPureTextBtn.h"
#include "../Elem/WndShowAnimate.h"

class KUiInformation1 : protected KWndShowAnimate
{
public:
	void	Initialize();							//初始化
	void	LoadScheme(const char* pScheme);		//载入界面方案
	void	Show(const char* pInformation, int nMsgLen = -1, 
				const char* pszFirstBtnText = "\xA7" "\xE5" "ng " "\xFD",
				const char* pszSecondBtnText = 0,
				KWndWindow* pCallerWnd = 0,
				unsigned int uParam = 0,
				const char* pszImage = 0,
				int nLeftTime = -1);			//显示窗口
	void	SpeakWords(KUiInformationParam* pWordDataList, int nCount, int nLeftTime = -1);	//显示对话内容
	void	Close();								//关闭窗口，不通知调用窗口
	KUiInformation1();

private:
	void	Hide(int nBtnIndex);					//隐藏窗口
	int		WndProc(unsigned int uMsg, unsigned int uParam, int nParam);//窗口函数
	void	PaintWindow();
	void	Breathe();
private:
	KUiInformationParam*	m_pWordDataList;
	KWndText256			m_Information;
	KWndPureTextBtn		m_FirstBtn;
	KWndPureTextBtn		m_SecondBtn;
	KWndImage			m_MsgIcon;
	KWndWindow*			m_pCallerWnd;
	unsigned int		m_uCallerParam;
	int					m_nMsgIconFrame;
	unsigned int		m_uLastShowMessage;
	int					m_nLeftTime;
};

void UIMessageBox1(const char* pMsg, int nMsgLen = -1, KWndWindow* pCaller = 0, 
				  const char* pszFirstBtnText = "\xA7" "\xE5" "ng " "\xFD",
				  const char* pszSecondBtnText = 0,
				  unsigned int uParam = 0,
				  const char* pszImage = 0,
				  int nLeftTime = -1);
void UiCloseMessageBox1();

extern KUiInformation1	g_UiInformation1;