//---------------------------------------------------------------------------
// Sword3 Engine (c) 2002 by Kingsoft
//
// File:	KPlayerChat.cpp
// Date:	2002.10.05
// Code:	边城浪子
// Desc:	PlayerChat Class
//---------------------------------------------------------------------------

#ifdef _STANDALONE
#include <string>
#endif

#include	"KCore.h"
#ifdef _SERVER
//#include	"KNetServer.h"
//#include "../MultiServer/Heaven/Interface/iServer.h"
#include	"KGMCommand.h"
#else
//#include	"KNetClient.h"
#include "../../Headers/IClient.h"
#include	"CoreShell.h"
#endif
#include	"KNpc.h"
#include	"KNpcSet.h"
#include	"KSubWorld.h"
#include	"KPlayer.h"
#include	"KPlayerSet.h"
#include	"KPlayerTeam.h"
#include	"KPlayerChat.h"
#include	"MsgGenreDef.h"
#include	"CoreUseNameDef.h"
#include	"Text.h"
#include	"malloc.h"
#ifdef _SERVER
#include "KNewProtocolProcess.h"
#endif
#include "KTongProtocol.h"

//---------------------------------------------------------------------------
//	功能：清空
//---------------------------------------------------------------------------
void	KPlayerChat::Release()
{
}

#ifdef _SERVER
void	KPlayerChat::SendSystemInfo(int nType, int nTargetIdx, char *lpszSendName, char *lpszSentence, int nSentenceLength, int nChannedID/* = -1*/)
{
	if (!lpszSendName || !lpszSentence)
		return;

	if(nTargetIdx)
	{
		TReplaceText(lpszSentence, PLAYERNAME_KEY, Npc[Player[nTargetIdx].m_nIndex].Name);
		TReplaceText(lpszSentence, SEXNAME_KEY, Npc[Player[nTargetIdx].m_nIndex].m_nSex? "C" "\xAB" " n" "\xAD" "\xAC" "ng":"Thi" "\xD5" "u hi" "\xD6" "p");
		nSentenceLength = strlen(lpszSentence);
	}

	if (nSentenceLength >= MAX_SENTENCE_LENGTH)
		nSentenceLength = MAX_SENTENCE_LENGTH;

	BOOL bAll = nType == 0;


	size_t chatsize = sizeof(CHAT_CHANNELCHAT_SYNC) + nSentenceLength;
	size_t pckgsize = sizeof(tagExtendProtoHeader) + chatsize;

#ifdef WIN32
	tagExtendProtoHeader* pExHeader = (tagExtendProtoHeader*)_alloca(pckgsize);
#else
	tagExtendProtoHeader* pExHeader = (tagExtendProtoHeader*)(new char[pckgsize]);
#endif
	pExHeader->ProtocolType = s2c_extendchat;
	pExHeader->wLength = pckgsize - 1;

	CHAT_CHANNELCHAT_SYNC* pCccSync= (CHAT_CHANNELCHAT_SYNC*)(pExHeader + 1);
	pCccSync->ProtocolType = chat_channelchat;
	pCccSync->wSize = chatsize - 1;
	pCccSync->packageID = -1;
	strncpy(pCccSync->someone, lpszSendName, _NAME_LEN - 1); // 可能需要根据玩家身份改动
	pCccSync->channelid = nChannedID;
	pCccSync->sentlen = nSentenceLength;
	memcpy(pCccSync + 1, lpszSentence, nSentenceLength);
	pCccSync->item[0] = 0;
	pCccSync->someflag = 0;

	if (bAll)	// 给全体玩家发送
	{
		int nTargetIdx;
		nTargetIdx = PlayerSet.GetFirstPlayer();
		while (nTargetIdx)
		{
			g_pServer->PackDataToClient(Player[nTargetIdx].m_nNetConnectIdx, pExHeader, pckgsize);
			nTargetIdx = PlayerSet.GetNextPlayer();
		}
	}
	else			// 给某个特定玩家发送
	{
		if (nTargetIdx <= 0)
		{
#ifndef WIN32
			if (pExHeader)
				delete ((char*)pExHeader);
#endif
			return;
		}
		g_pServer->PackDataToClient(Player[nTargetIdx].m_nNetConnectIdx, pExHeader, pckgsize);
	}

#ifndef WIN32
			if (pExHeader)
				delete ((char*)pExHeader);
#endif
	return;
}
#endif

#ifdef _SERVER
void KPlayerChat::SendGlobalSystemInfo(char *lpszSendName, char *lpszSentence, int nSentenceLength)
{
	if (!lpszSendName || !lpszSentence)
		return;
	if (nSentenceLength >= MAX_SENTENCE_LENGTH)
		nSentenceLength = MAX_SENTENCE_LENGTH;

	size_t chatsize = sizeof(CHAT_CHANNELCHAT_SYNC) + nSentenceLength;
	size_t pckgsize = sizeof(tagExtendProtoHeader) + chatsize;

#ifdef WIN32
	tagExtendProtoHeader* pExHeader = (tagExtendProtoHeader*)_alloca(pckgsize);
#else
	tagExtendProtoHeader* pExHeader = (tagExtendProtoHeader*)(new char[pckgsize]);
#endif
	pExHeader->ProtocolType = s2c_extendchat;
	pExHeader->wLength = pckgsize - 1;

	CHAT_CHANNELCHAT_SYNC* pCccSync= (CHAT_CHANNELCHAT_SYNC*)(pExHeader + 1);
	pCccSync->ProtocolType = chat_channelchat;
	pCccSync->wSize = chatsize - 1;
	pCccSync->packageID = -1;
	strncpy(pCccSync->someone, lpszSendName, _NAME_LEN - 1); // 可能需要根据玩家身份改动
	pCccSync->channelid = -1;
	pCccSync->sentlen = nSentenceLength;
	memcpy(pCccSync + 1, lpszSentence, nSentenceLength);
	pCccSync->item[0] = 0;
	pCccSync->someflag = 0;

	g_NewProtocolProcess.BroadcastGlobal(pExHeader, pckgsize);

#ifndef WIN32
	if (pExHeader)
		delete ((char*)pExHeader);
#endif
}
#endif

#ifdef _SERVER
void KPlayerChat::SendInfoToGM(char *lpszAccName, char *lpszRoleName, char *lpszSentence, int nSentenceLength)
{
	if (!lpszAccName ||
		!lpszRoleName ||
		!lpszSentence)
		return;
	if (nSentenceLength >= MAX_SENTENCE_LENGTH)
		nSentenceLength = MAX_SENTENCE_LENGTH;

	size_t chatsize = sizeof(CHAT_MSG_EX) + nSentenceLength;
	size_t pckgsize = sizeof(RELAY_ASKWAY_DATA) + chatsize;


#ifdef WIN32
	RELAY_ASKWAY_DATA* pExHeader = (RELAY_ASKWAY_DATA*)_alloca(pckgsize);
#else
	RELAY_ASKWAY_DATA* pExHeader = (RELAY_ASKWAY_DATA*)(new char[pckgsize]);
#endif
	pExHeader->ProtocolFamily = pf_relay;
	pExHeader->ProtocolID = relay_c2c_askwaydata;
	pExHeader->nFromIP = 0;
	pExHeader->nFromRelayID = 0;
	pExHeader->seekRelayCount = 0;
	pExHeader->seekMethod = rm_gm;
	pExHeader->wMethodDataLength = 0;
	pExHeader->routeDateLength = chatsize;

	CHAT_MSG_EX* pChatMsgEx= (CHAT_MSG_EX*)(pExHeader + 1);
	pChatMsgEx->ProtocolFamily = pf_playercommunity;
	pChatMsgEx->ProtocolID = playercomm_channelchat;
	strcpy(pChatMsgEx->m_szSourceName, lpszRoleName);
	strcpy(pChatMsgEx->m_szAccountName, lpszAccName);
	pChatMsgEx->SentenceLength = nSentenceLength;
	memcpy(pChatMsgEx + 1, lpszSentence, nSentenceLength);

	g_NewProtocolProcess.PushMsgInTransfer(pExHeader, pckgsize);

#ifndef WIN32
	if (pExHeader)
		delete ((char*)pExHeader);
#endif
}
#endif

#ifdef _SERVER
void KPlayerChat::SendInfoToIP(DWORD nIP, DWORD nID, char *lpszAccName, char *lpszRoleName, char *lpszSentence, int nSentenceLength)
{
	if (!lpszAccName ||
		!lpszRoleName ||
		!lpszSentence)
		return;
	if (nSentenceLength >= MAX_SENTENCE_LENGTH)
		nSentenceLength = MAX_SENTENCE_LENGTH;

	size_t chatsize = sizeof(CHAT_MSG_EX) + nSentenceLength;
	size_t pckgsize = sizeof(RELAY_DATA) + chatsize;


#ifdef WIN32
	RELAY_DATA* pExHeader = (RELAY_DATA*)_alloca(pckgsize);
#else
	RELAY_DATA* pExHeader = (RELAY_DATA*)(new char[pckgsize]);
#endif
	pExHeader->ProtocolFamily = pf_relay;
	pExHeader->ProtocolID = relay_c2c_data;
	pExHeader->nToIP = nIP;
	pExHeader->nToRelayID = nID;
	pExHeader->nFromIP = 0;
	pExHeader->nFromRelayID = 0;
	pExHeader->routeDateLength = chatsize;

	CHAT_MSG_EX* pChatMsgEx= (CHAT_MSG_EX*)(pExHeader + 1);
	pChatMsgEx->ProtocolFamily = pf_playercommunity;
	pChatMsgEx->ProtocolID = playercomm_channelchat;
	strcpy(pChatMsgEx->m_szSourceName, lpszRoleName);
	strcpy(pChatMsgEx->m_szAccountName, lpszAccName);
	pChatMsgEx->SentenceLength = nSentenceLength;
	memcpy(pChatMsgEx + 1, lpszSentence, nSentenceLength);

	g_NewProtocolProcess.PushMsgInTransfer(pExHeader, pckgsize);

#ifndef WIN32
	if (pExHeader)
		delete ((char*)pExHeader);
#endif
}
#endif

#define 	ADDBROTHER_UNITNAME 			"Th" "\xA9" "n nh" "\xA9" "n\n"
#define 	ADDENEMY_UNITNAME	 			"C" "\xF5" "u nh" "\xA9" "n\n"
#define 	ADDMATE_UNITNAME	 			"Ph" "\xE8" "i ng" "\xC9" "u\n"

#ifdef _SERVER
void KPlayerChat::MakeBrother(const STRINGLIST& brothers)
{
	if (brothers.size() == 0)
		return;

	static const size_t max_packagesize = 1000;
	char buffer[max_packagesize];	//max package size
	size_t maxsize = max_packagesize - 1;	//留个0的位置
	size_t basesize = sizeof(FRIEND_ASSOCIATEBEVY);

	FRIEND_ASSOCIATEBEVY* pGf = (FRIEND_ASSOCIATEBEVY*)(buffer);
	pGf->ProtocolFamily = pf_friend;
	pGf->ProtocolID = friend_c2s_associatebevy;

	int nG = strlen(ADDBROTHER_UNITNAME) + 1;
	strcpy(buffer + basesize, ADDBROTHER_UNITNAME);
	basesize += nG;

	size_t cursor = basesize;

	for (STRINGLIST::const_iterator itFriend = brothers.begin(); itFriend != brothers.end(); itFriend++)
	{
		std::string dst = *itFriend;
		size_t appendsize = dst.size() + 1;

		if (cursor + appendsize > maxsize)
		{
			buffer[cursor++] = specOver;	//加个结尾,发走

			g_NewProtocolProcess.PushMsgInTong(buffer, cursor);

			cursor = basesize;	//从头开始
		}

		strcpy(buffer + cursor, dst.c_str());
		cursor += appendsize;
	}

	if (cursor > basesize)
	{
		buffer[cursor++] = specOver;

		g_NewProtocolProcess.PushMsgInTong(buffer, cursor);
	}
}
#endif

#ifdef _SERVER
void KPlayerChat::MakeEnemy(char* szPlayer, char* szEnemy)
{
	if (!szPlayer || szPlayer[0] == 0 ||
		!szEnemy || szEnemy[0] == 0)
		return;

	int nG = strlen(ADDENEMY_UNITNAME) + 1;
	int nP = strlen(szPlayer) + 1;
	int nE = strlen(szEnemy) + 1;
	size_t fsize = sizeof(FRIEND_ASSOCIATE) + nG + nP + nE;

#ifdef WIN32
	FRIEND_ASSOCIATE* pCccSync = (FRIEND_ASSOCIATE*)_alloca(fsize);
#else
	FRIEND_ASSOCIATE* pCccSync = (FRIEND_ASSOCIATE*)(new char[fsize]);
#endif
	pCccSync->ProtocolFamily = pf_friend;
	pCccSync->ProtocolID = friend_c2s_associate;
	pCccSync->bidir = 0;
	char* pBuf = (char*)(pCccSync + 1);
	strcpy(pBuf, ADDENEMY_UNITNAME);
	pBuf += nG;
	strcpy(pBuf, szPlayer);
	pBuf += nP;
	strcpy(pBuf, szEnemy);
	pBuf += nE;

	g_NewProtocolProcess.PushMsgInTong(pCccSync, fsize);

#ifndef WIN32
	if (pCccSync)
		delete ((char*)pCccSync);
#endif
}
#endif

#ifdef _SERVER
void KPlayerChat::MakeMate(char* szPlayer, char* szMate)
{
	if (!szPlayer || szPlayer[0] == 0 ||
		!szMate || szMate[0] == 0)
		return;

	int nG = strlen(ADDMATE_UNITNAME) + 1;
	int nP = strlen(szPlayer) + 1;
	int nE = strlen(szMate) + 1;
	size_t fsize = sizeof(FRIEND_ASSOCIATE) + nG + nP + nE;

#ifdef WIN32
	FRIEND_ASSOCIATE* pCccSync = (FRIEND_ASSOCIATE*)_alloca(fsize);
#else
	FRIEND_ASSOCIATE* pCccSync = (FRIEND_ASSOCIATE*)(new char[fsize]);
#endif
	pCccSync->ProtocolFamily = pf_friend;
	pCccSync->ProtocolID = friend_c2s_associate;
	pCccSync->bidir = 1;
	char* pBuf = (char*)(pCccSync + 1);
	strcpy(pBuf, ADDMATE_UNITNAME);
	pBuf += nG;
	strcpy(pBuf, szPlayer);
	pBuf += nP;
	strcpy(pBuf, szMate);
	pBuf += nE;

	g_NewProtocolProcess.PushMsgInTong(pCccSync, fsize);

#ifndef WIN32
	if (pCccSync)
		delete ((char*)pCccSync);
#endif
}
#endif



