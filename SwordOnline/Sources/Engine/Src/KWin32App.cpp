//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
//
// File:	KWin32App.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	KWin32App Class
//---------------------------------------------------------------------------
#include "KWin32.h"
#include "KDebug.h"
#include "KDDraw.h"
#include "KMemBase.h"
#include "KStrBase.h"
#include "KWin32Wnd.h"
#include "KWin32App.h"
#include "KIme.h"
//#include "KProtocolDef.h"
//---------------------------------------------------------------------------
static KWin32App* m_pWin32App = NULL;
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
ENGINE_API FILE *sout = NULL;
ENGINE_API FILE *serr = NULL;

#ifndef WM_MOUSEHOVER
	#define WM_MOUSEHOVER 0x02A1
#endif

#define	MOUSE_EVENT_NONE			0
#define	MOUSE_EVENT_HAPPEND			1
#define	MOUSE_HOVER_MSG_SENT		2
#define	MOUSE_HOVER_START_TIME_MIN	3
//m_uMouseHoverStartTime ����
//MOUSE_EVENT_NONE		--> δ��������¼�
//MOUSE_EVENT_HAPPEND	--> ������¼�
//MOUSE_HOVER_MSG_SENT	--> ������¼��ĳ���ʱ�䳬�����趨��ʱ�����ƣ��ѷ�����WM_NCMOUSEHOVER��Ϣ
//����ֵ				--> ������¼��ĳ���ʱ��δ�����趨��ʱ�����ƣ���ֵ��ʾ������Ŀ�ʼʱ��

//---------------------------------------------------------------------------
// ����:	WndProc
// ����:	���ڻص�����
// ����:	hWnd		���ھ��?//			uMsg		��Ϣ����
//			wParam		����1(32bit)
//			lParam		����2(32bit)
// ����:	LRESULT
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProc(
						 HWND	hWnd,		// handle of window
						 UINT	uMsg,		// type of message
						 WPARAM	wParam, 	// first message parameter 32bit
						 LPARAM	lParam) 	// second message parameter 32bit
{
	return m_pWin32App->MsgProc(hWnd, uMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
// ����:	KWin32App
// ����:	���캯��
// ����:	void
// ����:	void
//---------------------------------------------------------------------------
KWin32App::KWin32App()
{
	m_bActive = TRUE;
	m_bMultiGame = TRUE;
	m_bShowMouse = TRUE;
	m_uMouseHoverTimeSetting = 0;
	m_uMouseHoverStartTime = MOUSE_EVENT_NONE;
	m_uLastMouseStatus = 0;
	m_nLastMousePos = 0;
	m_uLastMouseStatus = 0;
	m_pWin32App = this;
}
//---------------------------------------------------------------------------
// ����:	Init
// ����:	��ʼ��
// ����:	hInstance	ʵ�����?// ����:	void
//---------------------------------------------------------------------------
BOOL KWin32App::Init(HINSTANCE hInstance)
{
	g_StrCpy(m_szClass, "Sword3 Class");
	g_StrCpy(m_szTitle, "JX2022");

	if (!InitClass(hInstance))
		return FALSE;

	if (!InitWindow(hInstance))
		return FALSE;

	if (!GameInit())
		return FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
// ����:	InitClass
// ����:	��ʼ�����ڳ�����
// ����:	hInstance	ʵ�����?// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
BOOL KWin32App::InitClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	
	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTATOM(SWORD_ICON));
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName 	= NULL;
	wc.lpszClassName	= m_szClass;

	return RegisterClass(&wc);
}
//---------------------------------------------------------------------------
// ����:	InitWindow
// ����:	��ʼ������
// ����:	hInstance	ʵ�����?// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
BOOL KWin32App::InitWindow(HINSTANCE hInstance)
{
	//  Tinh dung kich thuoc cua so de vung client bang chinh xac do phan giai
	//  goc, thay vi uoc luong +12/+35 (sai khi vien cua so day len).
	// Run the 1920x1080 client as a borderless window. This gives us a true
	// edge-to-edge presentation without relying on exclusive fullscreen mode.
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	//  Luc mo, cua so chiem WindowScale% vung lam viec (tru thanh taskbar), giu ty le
	//  WND_INIT_WIDTH : WND_INIT_HEIGHT, dat giua. D3D tu co gian hinh vao vung client.
	//  Doi trong config.ini: [Client] WindowScale=80 (50..100).
	char szCfg[MAX_PATH];
	GetModuleFileNameA(NULL, szCfg, MAX_PATH);
	char* pSlash = strrchr(szCfg, '\\');
	if (pSlash)
		strcpy(pSlash + 1, "config.ini");
	int nScale = GetPrivateProfileIntA("Client", "WindowScale", 80, szCfg);
	if (nScale < 50)  nScale = 50;
	if (nScale > 100) nScale = 100;

	RECT rcWork;
	if (!SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0))
		SetRect(&rcWork, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	int nWorkWidth  = rcWork.right - rcWork.left;
	int nWorkHeight = rcWork.bottom - rcWork.top;

	//  Kich thuoc vien cua so
	RECT rcFrame = { 0, 0, 100, 100 };
	AdjustWindowRect(&rcFrame, dwStyle, FALSE);
	int nFrameW = (rcFrame.right - rcFrame.left) - 100;
	int nFrameH = (rcFrame.bottom - rcFrame.top) - 100;

	int nClientW = (nWorkWidth - nFrameW) * nScale / 100;
	int nClientH = nClientW * WND_INIT_HEIGHT / WND_INIT_WIDTH;
	int nMaxClientH = (nWorkHeight - nFrameH) * nScale / 100;
	if (nClientH > nMaxClientH)
	{
		nClientH = nMaxClientH;
		nClientW = nClientH * WND_INIT_WIDTH / WND_INIT_HEIGHT;
	}
	if (nClientW > WND_INIT_WIDTH || nClientH > WND_INIT_HEIGHT)
	{
		nClientW = WND_INIT_WIDTH;
		nClientH = WND_INIT_HEIGHT;
	}
	int nWindowWidth  = nClientW + nFrameW;
	int nWindowHeight = nClientH + nFrameH;
	int nLeft = rcWork.left + (nWorkWidth - nWindowWidth) / 2;
	int nTop  = rcWork.top + (nWorkHeight - nWindowHeight) / 2;
	if (nLeft < rcWork.left) nLeft = rcWork.left;
	if (nTop < rcWork.top)   nTop = rcWork.top;

	HWND hWnd = CreateWindowExA(
		WS_EX_APPWINDOW,
		m_szClass,
		m_szTitle,
		dwStyle,
		nLeft,
		nTop,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,		NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	g_SetMainHWnd(hWnd);
	g_SetDrawHWnd(hWnd);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	return TRUE;
}
//---------------------------------------------------------------------------
// ����:	Run
// ����:	����Ϣѭ��
// ����:	void
// ����:	void
//---------------------------------------------------------------------------
void KWin32App::Run()
{
	MSG	Msg;

	while (TRUE)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			//if (!GetMessage(&Msg, NULL, 0, 0))
			//	break;
            if (Msg.message == WM_QUIT)
                break;

			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else if (m_bActive || m_bMultiGame)
		{
			GenerateMsgHoverMsg();
			if (!GameLoop())
			{
				PostMessage(g_GetMainHWnd(), WM_CLOSE, 0, 0);
			}
		}
		else
		{
			WaitMessage();
		}
	}
	GameExit();
}
//---------------------------------------------------------------------------
// ����:	GameInit
// ����:	��Ϸ��ʼ��
// ����:	void
// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
BOOL KWin32App::GameInit()
{
	return TRUE;
}
//---------------------------------------------------------------------------
// ����:	GameLoop
// ����:	��Ϸ��ѭ��
// ����:	void
// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
BOOL KWin32App::GameLoop()
{
	WaitMessage();
	return TRUE;
}
//---------------------------------------------------------------------------
// ����:	GameExit
// ����:	��Ϸ�˳�
// ����:	void
// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
BOOL KWin32App::GameExit()
{
	return TRUE;
}
//---------------------------------------------------------------------------
// ����:	MsgProc
// ����:	���ڻص�����
// ����:	hWnd		���ھ��?//			uMsg		��Ϣ����
//			wParam		����1(32bit)
//			lParam		����2(32bit)
// ����:	TRUE		�ɹ�
//			FALSE		ʧ��
//---------------------------------------------------------------------------
LRESULT KWin32App::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZING:
	    {
	        //  Khoa ty le khung hinh khi keo vien, de hinh khong bi bop meo.
	        RECT* pRc = (RECT*)lParam;
	        RECT  rcWnd, rcCli;
	        GetWindowRect(hWnd, &rcWnd);
	        GetClientRect(hWnd, &rcCli);
	        int nFrameW = (rcWnd.right - rcWnd.left) - (rcCli.right - rcCli.left);
	        int nFrameH = (rcWnd.bottom - rcWnd.top) - (rcCli.bottom - rcCli.top);
	        int nCliW   = (pRc->right - pRc->left) - nFrameW;
	        int nCliH   = (pRc->bottom - pRc->top) - nFrameH;
	        if (nCliW > 0 && nCliH > 0)
	        {
	            //  Giu dung ty le goc WND_INIT_WIDTH : WND_INIT_HEIGHT
	            int nWantH = nCliW * WND_INIT_HEIGHT / WND_INIT_WIDTH;
	            int nWantW = nCliH * WND_INIT_WIDTH  / WND_INIT_HEIGHT;
	            switch (wParam)
	            {
	            case WMSZ_LEFT:  case WMSZ_RIGHT:
	                pRc->bottom = pRc->top + nWantH + nFrameH;
	                break;
	            case WMSZ_TOP:   case WMSZ_BOTTOM:
	                pRc->right  = pRc->left + nWantW + nFrameW;
	                break;
	            default:
	                //  Keo goc: lay chieu ngang lam chuan
	                pRc->bottom = pRc->top + nWantH + nFrameH;
	                break;
	            }
	        }
	    }
	    return TRUE;
	
	case WM_CLOSE:
		if (HandleInput(uMsg, wParam, lParam))
			return 0;
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETCURSOR:
		if (m_bShowMouse == FALSE && m_bActive &&
			LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(NULL);
			return TRUE;
		}
        //  Ngoai vung client (vien, thanh tieu de) phai de Windows tu dat con tro,
        //  neu khong nguoi choi se khong thay con tro de keo vien cua so.
        if (LOWORD(lParam) != HTCLIENT)
            break;
        return TRUE;
		break;
//	case WM_SOCKET_READ:
//        if(g_pNetClient)   
//          g_pNetClient->RecvMsg(); 
//		break;

	case WM_IME_CHAR:
		 return HandleInput(uMsg, wParam, lParam);
	case WM_INPUTLANGCHANGEREQUEST:
	case WM_IME_NOTIFY:
		if (g_pIme && 
			g_pIme->WndMsg(hWnd,uMsg,wParam,lParam))
			return 0;
		break;

	case WM_ACTIVATEAPP:
		m_bActive = (BOOL)wParam;
		if (m_bActive && g_pDirectDraw)
			g_pDirectDraw->RestoreSurface();

   	    HandleInput(uMsg, wParam, lParam);
		break;

    case WM_SYSCOMMAND:
        if (wParam == SC_KEYMENU)
        {
            return 0;
        }
	case WM_COPYDATA:
		HandleInput(uMsg, wParam, lParam);
		break;
	default:
		if (uMsg >= WM_KEYFIRST && uMsg <= WM_KEYLAST)
		{
			HandleInput(uMsg, wParam, lParam);
		}
		else if (uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST)
		{
			m_uLastMouseStatus = wParam;
			m_nLastMousePos = lParam;
			m_uMouseHoverStartTime = MOUSE_EVENT_HAPPEND;
			HandleInput(uMsg, wParam, lParam);
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//---------------------------------------------------------------------------
// ����:	ShowMouse
// ����:	�������ɼ�
// ����:	bShow		BOOL
// ����:	void
//---------------------------------------------------------------------------
void KWin32App::ShowMouse(BOOL bShow)
{
	m_bShowMouse = bShow;
}
//---------------------------------------------------------------------------
// ����:	SetMultiGame
// ����:	�����Ƿ��Ǻ�̨�������еĶ�����Ϸ
// ����:	bMulti		BOOL
// ����:	void
//---------------------------------------------------------------------------
void KWin32App::SetMultiGame(BOOL bMulti)
{
	m_bMultiGame = bMulti;
}

void KWin32App::SetMouseHoverTime(unsigned int nHoverTime)
{
	m_uMouseHoverTimeSetting = nHoverTime;
}

void KWin32App::GenerateMsgHoverMsg()
{
	if (m_uMouseHoverStartTime == MOUSE_HOVER_MSG_SENT)
	{
		static char cCounter = 0;
		if ((++cCounter) == 7)
		{
			cCounter = 0;
			HandleInput(WM_MOUSEHOVER, m_uLastMouseStatus, m_nLastMousePos);
		}
	}
	else if (m_uMouseHoverStartTime >= MOUSE_HOVER_START_TIME_MIN)
	{
		unsigned int	nCurrentTime = timeGetTime();
		if ((nCurrentTime - m_uMouseHoverStartTime) >= m_uMouseHoverTimeSetting)
		{
			HandleInput(WM_MOUSEHOVER, m_uLastMouseStatus, m_nLastMousePos);
			m_uMouseHoverStartTime = MOUSE_HOVER_MSG_SENT;
		}
	}
	else if (m_uMouseHoverStartTime == MOUSE_EVENT_HAPPEND)
	{
		m_uMouseHoverStartTime = MOUSE_EVENT_NONE;
	}
	else if (m_uMouseHoverTimeSetting)
	{
		//��ʱ(m_uMouseHoverStartTime == MOUSE_EVENT_NONE)
		m_uMouseHoverStartTime = timeGetTime();
		if (m_uMouseHoverStartTime < MOUSE_HOVER_START_TIME_MIN)
			m_uMouseHoverStartTime = MOUSE_HOVER_START_TIME_MIN;
	}
}