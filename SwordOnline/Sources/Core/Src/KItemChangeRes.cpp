//---------------------------------------------------------------------------
// Sword3 Core (c) 2002 by Kingsoft
//
// File:	KItemChangeRes.h
// Date:	2002.12
// Code:	Spe
// Desc:	Header File
//---------------------------------------------------------------------------
#include "KCore.h"
#include "KEngine.h"
#include "KItemChangeRes.h"
#include "KItem.h"
#include "CoreUseNameDef.h"

typedef struct _KFlashTable
{
	char			Name[64];
	int				NormalRes;
	int				FlashRes;
}KFlashTable;

static	const KFlashTable	s_FlashTable[] =
{
	{"Quy" "\xD2" "n Th" "\xF1",				0,		45	},
	{"Y" "\xD3" "m Nguy" "\xD6" "t " "\xA7" "ao",			6,		62	},
	{"Th" "\xCA" "t X" "\xDD" "c Ki" "\xD5" "m",			3,		63	},
	{"Thanh Long " "\xA7" "ao",			6,		64	},
	{"Thi" "\xAA" "n Nh" "\xCB" "n Ki" "\xD5" "m",			3,		65	},
	{"H" "\xE7" "n Thi" "\xD5" "t B" "\xE6" "ng",			12,		66	},
	{"Nh" "\xB9" "n Linh Th" "\xAD" "\xAC" "ng",		9,		67	},
	{"Kim Qua Ch" "\xEF" "y",			18,		68	},
	{"H" "\xE5" " " "\xA7" "i" "\xD6" "p Song " "\xA7" "ao",		15,		69	},
	{"\xA4" " Kim Tri" "\xD2" "n Th" "\xF1",			19,		45	},
	{"Huy" "\xD2" "n Thi" "\xD5" "t Tri" "\xD2" "n Th" "\xF1",	19,		45	},
	{"Lo" "\xB9" "i " "\xB8" "m Kh" "\xDD",				19,		46	},
	{"\xA7" "\xB9" "i Phong " "\xA7" "ao",			22,		73	},
	{"Huy" "\xD2" "n Thi" "\xD5" "t Ki" "\xD5" "m",		20,		74	},
	{"\xA7" "\xB9" "i Phong " "\xA7" "ao",			22,		75	},
	{"Huy" "\xD2" "n Thi" "\xD5" "t Ki" "\xD5" "m",		20,		76	},
	{"Kim C" "\xAB" " B" "\xE6" "ng",				26,		77	},
	{"Ph" "\xB8" " Thi" "\xAA" "n K" "\xDD" "ch",			24,		78	},
	{"Ph" "\xB8" " Thi" "\xAA" "n Ch" "\xEF" "y",			30,		79	},
	{"Th" "\xAB" "n Nh" "\xCB" "t Tr" "\xB6" "m",			28,		80	},
	{"M" "\xCB" "t V" "\xA9" "n Tri" "\xD2" "n Th" "\xF1",		19,		45	},
	{"M" "\xCB" "t V" "\xA9" "n Tri" "\xD2" "n Th" "\xF1",		19,		45	},
	{"Lo" "\xB9" "i " "\xB8" "m Kh" "\xDD",				19,		46	},
};

static	const int	s_nFlashCount = sizeof(s_FlashTable)/sizeof(KFlashTable);

KItemChangeRes	g_ItemChangeRes;
BOOL KItemChangeRes::Init()
{
	if (!m_MeleeWeapon.Load(CHANGERES_MELEE_FILE))
		return FALSE;
	if (!m_RangeWeapon.Load(CHANGERES_RANGE_FILE))
		return FALSE;
	if (!m_Armor.Load(CHANGERES_ARMOR_FILE))
		return FALSE;
	if (!m_Helm.Load(CHANGERES_HELM_FILE))
		return FALSE;
	if (!m_Horse.Load(CHANGERES_HORSE_FILE))
		return FALSE;
	if (!m_Gold.Load(CHANGERES_GOLD_FILE))
		return FALSE;
	if (!m_Hoods.Load(CHANGERES_HOODS_FILE))
		return FALSE;
	if (!m_Cloak.Load(CHANGERES_CLOAK_FILE))
		return FALSE;
	return TRUE;
}

int	KItemChangeRes::GetWeaponRes(int nDetail, int nParti, int nLevel, unsigned uFlash)
{
	int nRet;
	if (nLevel == 0)
	{
		m_MeleeWeapon.GetInteger(2, 2, 2, &nRet);
		return nRet - 2;
	}

	int nRow = nParti * 10 + nLevel + 2;
	switch(nDetail)
	{
	case equip_meleeweapon:
		m_MeleeWeapon.GetInteger(nRow, 2, 2, &nRet);
		break;
	case equip_rangeweapon:
		m_RangeWeapon.GetInteger(nRow - 1, 2, 2, &nRet);	// 没有默认状态
		break;
	}
	nRet -= 2;
	if(uFlash)
	{
		for(int i=0; i< s_nFlashCount; i++)
		{
			if(nRet == s_FlashTable[i].NormalRes)
				nRet = s_FlashTable[i].FlashRes;
		}
	}
	return nRet;
}

int	KItemChangeRes::GetArmorRes(int nParti, int nLevel)
{
	int nRet;
	if (nLevel == 0)
	{
		m_Armor.GetInteger(2, 2, 19, &nRet);
		return nRet - 2;
	}
	int nRow = nParti * 10 + nLevel + 2;
	m_Armor.GetInteger(nRow, 2, 19, &nRet);
	return nRet - 2;
}

int	KItemChangeRes::GetHelmRes(int nParti, int nLevel)
{
	int nRet;
	if (nLevel == 0)
	{
		m_Helm.GetInteger(2, 2, 19, &nRet);
		return nRet - 2;
	}
	int nRow = nParti * 10 + nLevel + 2;
	m_Helm.GetInteger(nRow, 2, 19, &nRet);
	return nRet - 2;
}

int KItemChangeRes::GetHorseRes(int nParti, int nLevel)
{
	int nRet;
	if (nLevel == 0)
	{
		return -1;
	}
	int nRow = nParti * 10 + nLevel + 2;
	m_Horse.GetInteger(nRow, 2, 2, &nRet);
	return nRet - 2;
}

int	KItemChangeRes::GetGoldItemRes(int nDetail, int nRow, unsigned uFlash/* = 0*/)
{
	int nRet;
	char szRow[16];
	char pszInfo[6];
	itoa(nRow + 1, szRow, 10);
	m_Gold.GetString(szRow, "\xB2" "\xBF" "\xBC" "\xFE" "\xB1" "\xE0" "\xBA" "\xC5", "19", pszInfo, sizeof(pszInfo));
	nRet = atoi(pszInfo);
	nRet -= 2;

	if(uFlash)
	{
		switch(nDetail)
		{
			case equip_meleeweapon:
			case equip_rangeweapon:
				for(int i=0; i< s_nFlashCount; i++)
				{
					if(nRet == s_FlashTable[i].NormalRes)
						nRet = s_FlashTable[i].FlashRes;
				}
				break;
		}
	}
	return nRet;
}

int	KItemChangeRes::GetHoodsRes(int nParti)
{
	int nRet;
	int nRow = nParti + 2;
	m_Hoods.GetInteger(nRow, 2, 2, &nRet);

	return nRet - 2;
}

int	KItemChangeRes::GetCloakRes(int nParti)
{
	int nRet;
	int nRow = nParti + 2;
	m_Cloak.GetInteger(nRow, 2, 2, &nRet);

	return nRet - 2;
}