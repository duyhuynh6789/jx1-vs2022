/*******************Editer	: duccom0123 EditTime:	2024/06/12 11:48:43*********************
//	界面窗口体系结构--带移动控制的显示图形的窗口
//	Copyright : Kingsoft 2002
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2002-12-10
*****************************************************************************************/
#include "KWin32.h"
#include "KIniFile.h"
#include "WndMovingImage.h"

#include "../../../Represent/iRepresent/iRepresentShell.h"
extern iRepresentShell*	g_pRepresentShell;

//--------------------------------------------------------------------------
//	功能：构造函数
//--------------------------------------------------------------------------
KWndMovingImage::KWndMovingImage()
{
	m_nCurrentValue = 0;
	m_nFullValue = 1;
	m_MoveRange.cx = 0;
	m_MoveRange.cy = 0;
}

void KWndMovingImage::Clone(KWndMovingImage* pCopy)
{
	if (pCopy)
	{
		KWndImage::Clone(pCopy);
		pCopy->m_oFixPos	= m_oFixPos;
		pCopy->m_MoveRange	= m_MoveRange;
		SetMoveValue(m_nCurrentValue, m_nFullValue);
	}
}

//--------------------------------------------------------------------------
//	功能：初始化窗口
//--------------------------------------------------------------------------
int KWndMovingImage::Init(KIniFile* pIniFile, const char* pSection)
{
	if (KWndImage::Init(pIniFile, pSection))
	{
		m_MoveRange.cx = m_oFixPos.x = m_Left;
		m_MoveRange.cy = m_oFixPos.y = m_Top;
		int nIniLeft = m_Left, nIniTop = m_Top;
		pIniFile->GetInteger(pSection, "Left", m_Left, &nIniLeft);
		pIniFile->GetInteger(pSection, "Top",  m_Top,  &nIniTop);
		int nEndX = -32768, nEndY = -32768;
		pIniFile->GetInteger2(pSection, "EndPos", &nEndX, &nEndY);
		if (nEndX != -32768 || nEndY != -32768)
		{
			m_MoveRange.cx = (nEndX != -32768) ? nEndX : m_Left;
			m_MoveRange.cy = (nEndY != -32768) ? nEndY : m_Top;
			//	EndPos tinh theo khung 800x600: dich theo do dich cua cua so khi neo
			m_MoveRange.cx += m_Left - nIniLeft;
			m_MoveRange.cy += m_Top - nIniTop;
		}
		m_MoveRange.cx -= m_oFixPos.x;
		m_MoveRange.cy -= m_oFixPos.y;
		SetMoveValue(m_nCurrentValue, m_nFullValue);
		return true;
	}
	return false;
}

void KWndMovingImage::SetMoveValue(int nCurrentValue, int nFullValue)
{
	m_nFullValue = nFullValue ? nFullValue : 1;
	m_nCurrentValue = nCurrentValue;
	int	x, y;
	if (m_MoveRange.cx)
		 x = (m_MoveRange.cx * m_nCurrentValue) / m_nFullValue + m_oFixPos.x;
	else
		x = m_oFixPos.x;
	if (m_MoveRange.cy)
		 y = (m_MoveRange.cy * m_nCurrentValue) / m_nFullValue + m_oFixPos.y;
	else
		y = m_oFixPos.y;
	SetPosition(x, y);
}

void KWndMovingImage::OnAnchorShift(int dx, int dy)
{
	m_oFixPos.x += dx;
	m_oFixPos.y += dy;
	KWndImage::OnAnchorShift(dx, dy);
}
