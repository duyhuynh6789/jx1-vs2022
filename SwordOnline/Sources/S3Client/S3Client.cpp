// S3Client.cpp : Defines the entry point for the application.
//

#include "KWin32.h"
#include "KCore.h"
#include "S3Client.h"
#include "KWin32Wnd.h"
#include "../../Represent/iRepresent/iRepresentShell.h"
#include "Ui/UiShell.h"
#include "NetConnect/NetConnectAgent.h"
#include "TextCtrlCmd/TextCtrlCmd.h"
#include "KPakList.h"
#include "Ui/Elem/TextPic.h"
#include "Ui/Elem/UiCursor.h"
#include "Ui/Elem/SpecialFuncs.h"
#include "../Engine/Src/FilterText.h"
#include "Ui/uibase.h"
#include "ErrorCode.h"
#include <locale.h>

#define ClientVersion
KMyApp MyApp;
HINSTANCE hInst;
KPakList g_PakList;
ITextFilter *g_libFilterText;
ITextFilter *g_ChatFilter;

#define QUIT_QUESTION_ID "22"
#define GAME_TITLE "23"

#define REPRESENT_MODULE_2 "Represent2.dll"
#define REPRESENT_MODULE_3 "Represent3.dll"
#define CREATE_REPRESENT_SHELL_FUN "CreateRepresentShell"
#define GAME_FPS 18

struct iRepresentShell *g_pRepresentShell = NULL;
struct IInlinePicEngineSink *g_pIInlinePicSink = NULL;
iCoreShell *g_pCoreShell = NULL;
KMusic *g_pMusic = NULL;

#define DYNAMIC_LINK_REPRESENT_LIBRARY

#ifdef DYNAMIC_LINK_REPRESENT_LIBRARY
static HMODULE l_hRepresentModule = NULL;
int g_bRepresent3 = false;
#endif

int g_bScreen = true;
char g_szGameName[128] = "11/11/2019";

KClientCallback g_ClientCallback;

// Do phan giai logic cua game: 1920x1080. Giao dien .ini van thiet ke cho khung 800x600
// va duoc dat lai bang he neo Anchor (S3Client\Ui\Elem\WndWindow.cpp).
// Phai trung voi RESOLUTION_* (Core\Src\GameDataDef.h), DEFAULT_SCREEN* (Represent3\BaseInclude.h)
// va WND_INIT_* (Engine\Src\KDDraw.h).
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
// Giao dien (ca ngoai game lan trong game) ve vao lop rieng roi phong len toan cua so;
// ban do van ve o SCREEN_WIDTH x SCREEN_HEIGHT (nhan vat nho, nhin rong).
// Kich thuoc lop giao dien = vung client cua cua so * 100 / UiScale, nen chu va nut giu
// nguyen co du cua so to hay nho. Doi trong config.ini: [Client] UiScale=120 (phan tram,
// 0 = tat, giao dien ve thang o SCREEN_*).
#define UI_SCALE_DEFAULT 120
void Wnd_SetWorldSize(int nWidth, int nHeight);
static int s_nUiScale = UI_SCALE_DEFAULT;
static int s_nUiCurW = 0, s_nUiCurH = 0;		// kich thuoc giao dien dang dung
static int s_nUiPendW = 0, s_nUiPendH = 0;		// kich thuoc dang cho cua so on dinh
static DWORD s_dwUiPendTick = 0;
// Vung ve ban do = vung client cua cua so (toi da SCREEN_*): ban do ve 1:1 nen nhan vat luon giu
// dung kich thuoc nhu o 1920x1080, cua so nho hon thi chi nhin thay it ban do hon.
static int s_nViewW = SCREEN_WIDTH, s_nViewH = SCREEN_HEIGHT;
static int s_nViewPendW = 0, s_nViewPendH = 0;

static bool CalcViewSize(int& nWidth, int& nHeight)
{
    nWidth = SCREEN_WIDTH;
    nHeight = SCREEN_HEIGHT;
    RECT rc;
    HWND hWnd = g_GetMainHWnd();
    if (hWnd == NULL || IsIconic(hWnd) || !GetClientRect(hWnd, &rc) || rc.right <= 0 || rc.bottom <= 0)
        return false;
    if (rc.right < nWidth)   nWidth = rc.right;
    if (rc.bottom < nHeight) nHeight = rc.bottom;
    return true;
}

static void ApplyViewSize(int nWidth, int nHeight)
{
    s_nViewW = nWidth;
    s_nViewH = nHeight;
    if (g_pRepresentShell)
        g_pRepresentShell->SetViewSize(nWidth, nHeight);
    Wnd_SetWorldSize(nWidth, nHeight);
    if (g_pCoreShell)
        g_pCoreShell->SetRepresentAreaSize(nWidth, nHeight);
}

// Kich thuoc giao dien mong muon theo vung client hien tai cua cua so
static bool CalcUiSize(int& nWidth, int& nHeight)
{
    nWidth = s_nViewW;
    nHeight = s_nViewH;
    if (s_nUiScale <= 0)
        return true;
    RECT rc;
    HWND hWnd = g_GetMainHWnd();
    if (hWnd == NULL || IsIconic(hWnd) || !GetClientRect(hWnd, &rc) || rc.right <= 0 || rc.bottom <= 0)
        return false;
    nWidth  = rc.right  * 100 / s_nUiScale;
    nHeight = rc.bottom * 100 / s_nUiScale;
    // Khung giao dien thiet ke 800x600: cua so qua nho thi giao dien thu nho theo
    if (nWidth < 800)  { nHeight = nHeight * 800 / nWidth;  nWidth = 800; }
    if (nHeight < 600) { nWidth  = nWidth * 600 / nHeight;  nHeight = 600; }
    if (nWidth > 4096)  nWidth = 4096;
    if (nHeight > 4096) nHeight = 4096;
    return true;
}

// Ap kich thuoc giao dien (lop rieng neu card ho tro, khong thi ve thang o SCREEN_*)
static void ApplyUiSize(int nWidth, int nHeight, bool bInit)
{
    if (!(g_pRepresentShell && g_pRepresentShell->SetUiLayerSize(nWidth, nHeight)))
    {
        // khong co lop giao dien: giao dien ve thang len vung ban do
        nWidth = s_nViewW;
        nHeight = s_nViewH;
    }
    s_nUiCurW = nWidth;
    s_nUiCurH = nHeight;
    if (bInit)
        UiSetScreenSize(nWidth, nHeight);
    else
        UiOnScreenResize(nWidth, nHeight);
}

// Goi moi vong lap: cua so doi kich thuoc (keo vien, phong to...) thi doi kich thuoc giao dien
// khi cua so da on dinh mot chut.
static void CheckUiResize()
{
    int vw, vh, w, h;
    if (!CalcViewSize(vw, vh))
    {
        s_nUiPendW = s_nUiPendH = s_nViewPendW = s_nViewPendH = 0;
        return;
    }
    // giao dien tinh theo vung ban do moi (khi tat lop giao dien)
    int nSaveVW = s_nViewW, nSaveVH = s_nViewH;
    s_nViewW = vw; s_nViewH = vh;
    bool bUiOk = CalcUiSize(w, h);
    s_nViewW = nSaveVW; s_nViewH = nSaveVH;
    if (!bUiOk || (w == s_nUiCurW && h == s_nUiCurH && vw == s_nViewW && vh == s_nViewH))
    {
        s_nUiPendW = s_nUiPendH = s_nViewPendW = s_nViewPendH = 0;
        return;
    }
    DWORD dwNow = GetTickCount();
    if (w != s_nUiPendW || h != s_nUiPendH || vw != s_nViewPendW || vh != s_nViewPendH)
    {
        s_nUiPendW = w;
        s_nUiPendH = h;
        s_nViewPendW = vw;
        s_nViewPendH = vh;
        s_dwUiPendTick = dwNow;
        return;
    }
    if (dwNow - s_dwUiPendTick >= 200)
    {
        s_nUiPendW = s_nUiPendH = s_nViewPendW = s_nViewPendH = 0;
        if (vw != s_nViewW || vh != s_nViewH)
            ApplyViewSize(vw, vh);
        if (w != s_nUiCurW || h != s_nUiCurH)
            ApplyUiSize(w, h, false);
    }
}

/*
 * Add this macro by liupeng on 2003.3.20
 * This macro is helper that can judge some legal character
 */
#define _private_IS_SPACE(c) ((c) == ' ' || (c) == '\r' || (c) == '\n' || (c) == '\t' || (c) == 'x')
#define IS_SPACE(c) _private_IS_SPACE(c)

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // TODO: Place code here.

    /*
	 * Add this funtion by liupeng on 2003.3.20
	 * We can find some error when start a console tracer
	 */
#ifdef TRUE

    bool bOpenTracer = false;

    while (lpCmdLine[0] == '-' || lpCmdLine[0] == '/')
    {
        lpCmdLine++;

        switch (*lpCmdLine++)
        {
        case 'c':
        case 'C':
            bOpenTracer = true;
            break;
        }

        while (IS_SPACE(*lpCmdLine))
        {
            lpCmdLine++;
        }
    }

    if (bOpenTracer)
    {
        AllocConsole();
    }

#endif   // End of this function

    hInst = hInstance;
    if (MyApp.Init(hInstance))
        MyApp.Run();

#ifdef TRUE

    if (bOpenTracer)
    {
        FreeConsole();
    }

#endif
    Error_Box();

    return 0;
}

KMyApp::KMyApp()
{
    m_pInlinePicSink = NULL;
}

BOOL InitRepresentShell(BOOL bFullScreen, int nWidth, int nHeight)
{
    Error_SetErrorString(g_bRepresent3 ? REPRESENT_MODULE_3 : REPRESENT_MODULE_2);
    if (g_pRepresentShell == NULL)
    {
#ifdef DYNAMIC_LINK_REPRESENT_LIBRARY
        if (l_hRepresentModule == NULL && (l_hRepresentModule = LoadLibrary(g_bRepresent3 ? REPRESENT_MODULE_3 : REPRESENT_MODULE_2)) == NULL)
        {
            Error_SetErrorCode(ERR_T_LOAD_MODULE_FAILED);
            return FALSE;
        }
        fnCreateRepresentShell pCreate = (fnCreateRepresentShell)GetProcAddress(l_hRepresentModule, CREATE_REPRESENT_SHELL_FUN);
        if (pCreate == NULL || (g_pRepresentShell = pCreate()) == NULL)
        {
            Error_SetErrorCode((pCreate == NULL) ? ERR_T_MODULE_UNCORRECT : ERR_T_MODULE_INIT_FAILED);
            return FALSE;
        }
#else
        g_pRepresentShell = CreateRepresentShell();
#endif
    }
    if (g_pRepresentShell->Create(nWidth, nHeight, bFullScreen != 0))
    {
        return TRUE;
    }
    else
    {
        Error_SetErrorCode(g_bRepresent3 ? ERR_T_REPRESENT3_INIT_FAILED : ERR_T_REPRESENT2_INIT_FAILED);
        return FALSE;
    }
}

BOOL KMyApp::GameInit()
{
    SetConsoleCP(65001);         // Input UTF-8
    SetConsoleOutputCP(65001);   // Output UTF-8

    // Thiết lập môi trường cơ bản
    setlocale(LC_ALL, "en_US.UTF-8");   // Thiết lập locale UTF-8 cụ thể

    Error_SetErrorString("KMyApp::GameInit");
#ifdef KUI_USE_HARDWARE_MOUSE

    ShowMouse(TRUE);

#else   // KUI_USE_HARDWARE_MOUSE

    ShowMouse(FALSE);

#endif

    g_SetRootPath(NULL);
    g_SetFilePath("\\");

    KIniFile *pSetting = g_UiBase.GetCommConfigFile();
    if (pSetting)
    {
        pSetting->GetString("Main", "GameName", "11/11/2019", g_szGameName, sizeof(g_szGameName));
        SetWindowText(g_GetMainHWnd(), g_szGameName);
    }
    g_FindDebugWindow("#32770", "DebugWin");

    KIniFile IniFile;
    if (!IniFile.Load("\\config.ini"))
    {
        Error_SetErrorCode(ERR_T_FILE_NO_FOUND);
        Error_SetErrorString("\\config.ini");
        return FALSE;
    }

#ifdef _DEBUG
    BOOL bCursor = FALSE;
    if (IniFile.GetInteger("Client", "ShowCursor", 0, &bCursor))
        ShowMouse(TRUE);
#endif

    IniFile.GetInteger("Client", "FullScreen", FALSE, &g_bScreen);
    IniFile.GetInteger("Client", "UiScale", UI_SCALE_DEFAULT, &s_nUiScale);
    if (s_nUiScale > 0 && s_nUiScale < 50)   s_nUiScale = 50;
    if (s_nUiScale > 300)                    s_nUiScale = 300;

#ifdef DYNAMIC_LINK_REPRESENT_LIBRARY
    IniFile.GetInteger("Client", "Represent", 2, &g_bRepresent3);
    g_bRepresent3 = (g_bRepresent3 == 3);
#endif

    g_PakList.Open("\\package.ini");

    char szPath[MAX_PATH];
    if (IniFile.GetString("Client", "CapPath", "", szPath, sizeof(szPath)))
    {
        if (szPath[0])
            SetScrPicPath(szPath);
    }

    IniFile.Clear();
    g_libFilterText = CreateTextFilter();
    g_ChatFilter = CreateTextFilter();
    if (!g_libFilterText || !g_ChatFilter)
        return FALSE;

    if (!InitRepresentShell(g_bScreen, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        return FALSE;
    }

    // Dat kich thuoc man hinh TRUOC khi UiInit() nap cac cua so (he neo can no).
    {
        int nViewW, nViewH;
        CalcViewSize(nViewW, nViewH);
        ApplyViewSize(nViewW, nViewH);      // g_pCoreShell chua co: dat lai ben duoi
    }
    {
        int nUiW, nUiH;
        if (!CalcUiSize(nUiW, nUiH))
        {
            nUiW = SCREEN_WIDTH * 100 / (s_nUiScale > 0 ? s_nUiScale : 100);
            nUiH = SCREEN_HEIGHT * 100 / (s_nUiScale > 0 ? s_nUiScale : 100);
        }
        ApplyUiSize(nUiW, nUiH, true);
    }

    if (!UiInit())
    {
        Error_SetErrorCode(ERR_T_MODULE_INIT_FAILED);
        Error_SetErrorString("UiInit");
        return FALSE;
    }

    //[wxb 2003-6-23]
    m_pInlinePicSink = new KInlinePicSink;
    if (m_pInlinePicSink)
    {
        m_pInlinePicSink->Init(g_pRepresentShell);
        _ASSERT(NULL == g_pIInlinePicSink);
        g_pIInlinePicSink = m_pInlinePicSink;
    }

    // (kich thuoc man hinh da dat truoc UiInit; UiInit tu chuyen sang che do ngoai game)

    UiPaint(0);

    // init dsound
    m_Sound.Init();

    SetMultiGame(TRUE);

    if ((g_pCoreShell = CoreGetShell()) == NULL)
    {
        Error_SetErrorCode(ERR_T_MODULE_INIT_FAILED);
        Error_SetErrorString("CoreGetShell");
        return false;
    }
    g_pCoreShell->SetRepresentShell(g_pRepresentShell);
    g_pCoreShell->SetMusicInterface((KMusic *)&m_Music);
    g_pCoreShell->SetCallDataChangedNofify(&g_ClientCallback);
    g_pCoreShell->SetRepresentAreaSize(s_nViewW, s_nViewH);    // vung ban do theo cua so

    g_pMusic = &m_Music;

    if (g_NetConnectAgent.Initialize() == 0)
    {
        Error_SetErrorCode(ERR_T_MODULE_INIT_FAILED);
        Error_SetErrorString("NetConnectAgent");
        return FALSE;
    }

    m_GameCounter = 0;
    m_Timer.Start();

    SetMouseHoverTime(400);

    if (UiStart())
    {
        return TRUE;
    }
    else
    {
        Error_SetErrorCode(ERR_T_MODULE_INIT_FAILED);
        Error_SetErrorString("UiStart");
        return FALSE;
    }
}

BOOL KMyApp::GameExit()
{
    if (m_pInlinePicSink)
    {
        //[wxb 2003-6-23]
        m_pInlinePicSink->UnInit();
        delete m_pInlinePicSink;
        m_pInlinePicSink = NULL;
        g_pIInlinePicSink = NULL;
    }

    UiExit();

    g_pMusic = NULL;
    if (g_pCoreShell)
    {
        g_pCoreShell->SetRepresentShell(NULL);
        g_pCoreShell->SetClient(NULL);
        g_pCoreShell->SetMusicInterface(NULL);
        g_pCoreShell->Release();
        g_pCoreShell = NULL;
    }

    if (g_pRepresentShell)
    {
        g_pRepresentShell->Release();
        g_pRepresentShell = NULL;
    }

    g_NetConnectAgent.Exit();

    m_Music.Close();
    m_Sound.Exit();

#ifdef DYNAMIC_LINK_REPRESENT_LIBRARY
    if (l_hRepresentModule)
    {
        FreeLibrary(l_hRepresentModule);
        l_hRepresentModule = NULL;
    }
#endif

    ::ShowCursor(TRUE);

    return TRUE;
}

BOOL KMyApp::GameLoop()
{
    static int nGameFps = 0;
    CheckUiResize();
    g_NetConnectAgent.Breathe();
    if (m_GameCounter * 1000 <= m_Timer.GetElapse() * GAME_FPS)
    {
        if (g_pCoreShell->Breathe() && UiHeartBeat())
        {
            m_GameCounter++;
            int nElapse = m_Timer.GetElapse();
            if (nElapse)
                nGameFps = m_GameCounter * 1000 / nElapse;
        }
        else
        {
            return false;
        }
    }
    if (m_GameCounter * 1000 >= m_Timer.GetElapse() * GAME_FPS)
    {
        UiPaint(nGameFps);
        Sleep(1);
    }
    else if ((m_GameCounter % 8) == 0)
    {
        Sleep(1);
    }

    return true;
}

int KMyApp::HandleInput(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int nRet = 0;
    if (uMsg != WM_CLOSE)
    {
        UiProcessInput(uMsg, wParam, lParam);
    }
    else if (g_bScreen == false && UiIsAlreadyQuit() == false)
    {
        KIniFile *pSetting = g_UiBase.GetCommConfigFile();
        if (pSetting)
        {
            char szMsg[128], szTitle[64];
            pSetting->GetString("InfoString", QUIT_QUESTION_ID, "", szMsg, sizeof(szMsg));
            pSetting->GetString("InfoString", GAME_TITLE, "", szTitle, sizeof(szTitle));
            if (szMsg[0] && szTitle[0])
            {
                nRet = (MessageBox(g_GetMainHWnd(), szMsg, szTitle, MB_YESNO | MB_ICONQUESTION) != IDYES);
            }
        }
    }
    return nRet;
}