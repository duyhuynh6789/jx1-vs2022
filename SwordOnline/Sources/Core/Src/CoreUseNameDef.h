
#ifndef COREUSENAMEDEF_H
#define COREUSENAMEDEF_H

#define		MAX_PLAYER_IN_ACCOUNT			3

#define		SETTING_PATH					"\\settings"


#define		NPCNAME_KEY						"<npc>"
#define		PLAYERNAME_KEY					"<player>"
#define		SEXNAME_KEY						"<sex>"

#define 	STRANGER_UNITNAME 				"[Ng" "\xAD" "\xEA" "i l" "\xB9" "]"
#define 	FRIEND_INDEX					0
#define 	FRIEND_UNITNAME 				"H" "\xB6" "o h" "\xF7" "u"
#define 	ENEMY_INDEX						1
#define 	ENEMY_UNITNAME	 				"C" "\xF5" "u nh" "\xA9" "n"
#define 	ADDENEMY_UNITNAME	 			"C" "\xF5" "u nh" "\xA9" "n\n"
#define		BLACKLIST_UNITNAME				"S" "\xE6" " " "\xAE" "en"
#define		BLACKLIST_INDEX					2
//---------------------------- npc res 相关 ------------------------------
#define		RES_INI_FILE_PATH				"\\settings\\npcres"
#define		RES_NPC_STYLE_PATH				"\\spr\\npcres\\style"
#define		RES_SOUND_FILE_PATH				"sound"

#define		NPC_RES_KIND_FILE_NAME			"\\settings\\npcres\\" "\xC8" "\xCB" "\xCE" "\xEF" "\xC0" "\xE0" "\xD0" "\xCD" ".txt"
#define		NPC_NORMAL_RES_FILE				"\\settings\\npcres\\" "\xC6" "\xD5" "\xCD" "\xA8" "npc" "\xD7" "\xCA" "\xD4" "\xB4" ".txt"
#define		NPC_NORMAL_SPRINFO_FILE			"\\settings\\npcres\\" "\xC6" "\xD5" "\xCD" "\xA8" "npc" "\xD7" "\xCA" "\xD4" "\xB4" "\xD0" "\xC5" "\xCF" "\xA2" ".txt"
#define		STATE_MAGIC_TABLE_NAME			"\\settings\\npcres\\" "\xD7" "\xB4" "\xCC" "\xAC" "\xCD" "\xBC" "\xD0" "\xCE" "\xB6" "\xD4" "\xD5" "\xD5" "\xB1" "\xED" ".txt"
#define		PLAYER_RES_SHADOW_FILE			"\\settings\\npcres\\" "\xD6" "\xF7" "\xBD" "\xC7" "\xB6" "\xAF" "\xD7" "\xF7" "\xD2" "\xF5" "\xD3" "\xB0" "\xB6" "\xD4" "\xD3" "\xA6" "\xB1" "\xED" ".txt"
#define		NPC_RES_SHADOW_FILE				"\xC6" "\xD5" "\xCD" "\xA8" "npc" "\xB6" "\xAF" "\xD7" "\xF7" "\xD2" "\xF5" "\xD3" "\xB0" "\xB6" "\xD4" "\xD3" "\xA6" "\xB1" "\xED" ".txt"
#define		PLAYER_SOUND_FILE				"\\settings\\npcres\\" "\xD6" "\xF7" "\xBD" "\xC7" "\xB6" "\xAF" "\xD7" "\xF7" "\xC9" "\xF9" "\xD2" "\xF4" "\xB1" "\xED" ".txt"
#define		NPC_SOUND_FILE					"\\settings\\npcres\\npc" "\xB6" "\xAF" "\xD7" "\xF7" "\xC9" "\xF9" "\xD2" "\xF4" "\xB1" "\xED" ".txt"

#define		NPC_ACTION_NAME					"npc" "\xB6" "\xAF" "\xD7" "\xF7" "\xB1" "\xED" ".txt"
#define		ACTION_FILE_NAME				"\xB6" "\xAF" "\xD7" "\xF7" "\xB1" "\xE0" "\xBA" "\xC5" "\xB1" "\xED" ".txt"

#define		PLAYER_MENU_STATE_RES_FILE		"\\settings\\npcres\\" "\xBD" "\xE7" "\xC3" "\xE6" "\xD7" "\xB4" "\xCC" "\xAC" "\xD3" "\xEB" "\xCD" "\xBC" "\xD0" "\xCE" "\xB6" "\xD4" "\xD5" "\xD5" "\xB1" "\xED" ".txt"
#define		PLAYER_INSTANT_SPECIAL_FILE		"\\settings\\npcres\\" "\xCB" "\xB2" "\xBC" "\xE4" "\xCC" "\xD8" "\xD0" "\xA7" ".txt"

#define		SPR_INFO_NAME					"\xD0" "\xC5" "\xCF" "\xA2"
#define		SPR_EFFECT_NAME					"_effect"
#define		KIND_NAME_SECT					"CharacterType"
#define		KIND_NAME_SPECIAL				"SpecialNpc"
#define		KIND_NAME_NORMAL				"NormalNpc"
#define		KIND_FILE_SECT1					"PartFileName"
#define		KIND_FILE_SECT2					"WeaponActionTab1"
#define		KIND_FILE_SECT3					"WeaponActionTab2"
#define		KIND_FILE_SECT4					"ActionRenderOrderTab"
#define		KIND_FILE_SECT5					"ResFilePath"

//--------------------------- player 门派相关 ------------------------------
// 注：下面这个设定文件必须按 金 金 木 木 水 水 火 火 土 土 的顺序排列
#define		FACTION_FILE					"\\settings\\faction\\" "\xC3" "\xC5" "\xC5" "\xC9" "\xC9" "\xE8" "\xB6" "\xA8" ".ini"

//--------------------------- player PK相关 ------------------------------
#define		defPK_PUNISH_FILE				"\\settings\\npc\\player\\PKPunish.txt"

//--------------------------- player 帮会相关 ------------------------------
#define		defTONG_PARAM_FILE				"\\settings\\tong\\Tong_Setting.ini"
#define		defTONG_LEVEL_FILE				"\\settings\\tong\\Tong_Level.txt"
#define		defTONG_DATA_FILE				"\\settings\\tong\\Tong_Data.ini"

//---------------------------- player 数值相关 ------------------------------
#define		PLAYER_LEVEL_EXP_FILE			"\\settings\\npc\\player\\level_exp.txt"
#define		PLAYER_LEVEL_ADD_FILE			"\\settings\\npc\\player\\level_add.txt"
#define		PLAYER_LEVEL_LEAD_EXP_FILE		"\\settings\\npc\\player\\level_lead_exp.txt"
#define		PLAYER_MAGIC_LEVEL_EXP_FILE		"\\settings\\npc\\player\\magic_level_exp.txt"
#define		BASE_ATTRIBUTE_FILE_NAME		"\\settings\\npc\\player\\NewPlayerBaseAttribute.ini"
#define		PLAYER_PK_SET_FILE				"\\settings\\npc\\PKSet.ini"
#define		PLAYER_BASE_VALUE				"\\settings\\npc\\player\\BaseValue.ini"
#define		PLAYER_STAMINA_FILE_NAME		"\\settings\\npc\\player\\stamina.ini"

// 00男金 01女金 02男木 03女木 04男水 05女水 06男火 07女火 08男土 09女土
#define		NEW_PLAYER_INI_FILE_NAME		"\\settings\\npc\\player\\NewPlayerIni%02d.ini"

//---------------------------- player 交易相关 ------------------------------
#define		BUYSELL_FILE					"\\settings\\buysell.txt"
#define		GOODS_FILE						"\\settings\\goods.txt"

//----------------------------- 物品相关 ------------------------------
#define		CHANGERES_MELEE_FILE			"\\settings\\item\\MeleeRes.txt"
#define		CHANGERES_RANGE_FILE			"\\settings\\item\\RangeRes.txt"
#define		CHANGERES_ARMOR_FILE			"\\settings\\item\\ArmorRes.txt"
#define		CHANGERES_HELM_FILE				"\\settings\\item\\HelmRes.txt"
#define		CHANGERES_HORSE_FILE			"\\settings\\item\\HorseRes.txt"
#define		CHANGERES_GOLD_FILE				"\\settings\\item\\GoldEquipRes.txt"
#define		CHANGERES_MASK_FILE				"\\settings\\item\\MaskRes.txt"
#define		CHANGERES_HOODS_FILE			"\\settings\\item\\HoodsRes.txt"
#define		CHANGERES_CLOAK_FILE			"\\settings\\item\\CloakRes.txt"
#define		ITEM_ABRADE_FILE				"\\settings\\item\\AbradeRate.ini"

//--------------- npc skill missles 设定文件，用于生成模板 -------------
#define		SKILL_SETTING_FILE				"\\settings\\Skills.txt"
#define		MISSLES_SETTING_FILE			"\\settings\\Missles.txt"
#define		NPC_SETTING_FILE				"\\settings\\NpcS.txt"
#define		NPC_NAME_FILE					"\\settings\\NpcName.txt"

//---------------------------- object 相关 ------------------------------
#define		OBJ_DATA_FILE_NAME		"\\settings\\obj\\ObjData.txt"
#define		MONEY_OBJ_FILE_NAME		"\\settings\\obj\\MoneyObj.txt"
#define		OBJ_NAME_COLOR_FILE		"\\settings\\obj\\ObjNameColor.ini"

//---------------------------- 小地图相关 -------------------------------
#define		defLITTLE_MAP_SET_FILE	"\\Ui\\Default\\" "\xD0" "\xA1" "\xB5" "\xD8" "\xCD" "\xBC" "\xD1" "\xD5" "\xC9" "\xAB" ".ini"

//----------------------------- 声音相关 --------------------------------
#define		defINSTANT_SOUND_FILE	"\\settings\\SoundList.txt"
#define		defMUSIC_SET_FILE		"\\settings\\music\\MusicSet.txt"
#define		defMUSIC_FIGHT_SET_FILE	"\\settings\\music\\MusicFightSet.ini"

//------------------------------------------------------------------------
#define NPC_TEMPLATE_BINFILEPATH		"\\settings"
#define NPC_TEMPLATE_BINFILE			"NpcTemplate.Bin"
#define WEAPON_PHYSICSSKILLFILE			"\\settings\\ClientWeaponSkill.txt"				
#define WEAPON_PARTICULARTYPE			"ParticularType"
#define	WEAPON_DETAILTYPE				"DetailType"
#define	WEAPON_SKILLID					"PhysicsSkillID"
//-----------------------------------------------------------------------
#define	WORLD_WAYPOINT_TABFILE			"\\settings\\WayPoint.txt"
#define WORLD_STATION_TABFILE			"\\settings\\Station.txt"
#define WORLD_STATIONPRICE_TABFILE		"\\settings\\StationPrice.txt"
#define WORLD_WAYPOINTPRICE_TABFILE		"\\settings\\WayPointPrice.txt"
#define WORLD_DOCK_TABFILE				"\\settings\\Wharf.txt"
#define WORLD_DOCKPRICE_TABFILE			"\\settings\\WharfPrice.txt"
#define STRINGRESOURSE_TABFILE			"\\settings\\StringResource.txt"
#define PLAYER_RANK_SETTING_TABFILE		"\\settings\\RankSetting.txt"	
#define EVENTITEM_TABFILE				"\\settings\\item\\EventItem.txt"
#define QUESTITEM_TABFILE				"\\settings\\item\\QuestKey.txt"
#define TOWNPORTAL_TABFILE				"\\settings\\item\\TownPortal.txt"
#define MAGICSCRIPT_TABFILE				"\\settings\\item\\MagicScript.txt"

//---------------------------------任务--------------------------
#define		MAGICATTRIB_LEVEL_FILE		"\\settings\\item\\magicattriblevel.txt"
#define		MAGICATTRIB_LVINDEX_FILE	"\\settings\\item\\magicattriblevel_index.txt"

#define		MAPLIST_SETTING_FILE			"\\settings\\MapList.ini"

#define		PLATINA_EQUIP_FILE			"\\settings\\item\\platinaequip.txt"
#define		GOLD_EQUIP_FILE				"\\settings\\item\\goldequip.txt"
#define		GOLD_EQUIP_MAGIC_FILE		"\\settings\\item\\magicattrib_ge.txt"

#define		GM_SCRIPT					"\\script\\gmscript.lua"
#define		SERVERTIMER_SCRIPT			"\\script\\servertimer.lua"
#define		SERVERSTARTUP_SCRIPT		"\\script\\serverscript.lua"

#define		LOGIN_SCRIPT				"\\script\\player\\playerlogin.lua"
#define		LEVELUP_SCRIPT				"\\script\\player\\playerlevelup.lua"
#define		LOGOUT_SCRIPT				"\\script\\player\\playerlogout.lua"
#define		SCRIPT_PROTOCOL_FILE		"\\script\\global\\script_protocol.lua"

#define		MINIMAP_SETTING_FILE_INI	"\\Settings\\MapTraffic.ini"
#define 	GAME_DATA_FILE_INI			"\\settings\\GameData.ini"
#define 	GAME_SETTING_FILE_INI		"\\settings\\GameSetting.ini"

#define		UNKNOWNITEM_SPR				"\\spr\\item\\unknownitem.spr"
#define		UNKNOWNITEM_SPR36			"\\spr\\item\\unknownitem36.spr"
#define		RESIZEITEM_SPR				"\\spr\\item\\twzhuanyun\\zhuanyunbao_big.spr"

#define		NORMAL_UNCLEAR_WORD			"Ch" "\xAD" "a r" "\xE2"
#define		NORMAL_FUNCTION_NAME		"main"
//---------------------------- 消息相关 ------------------------------
// 特别注意：以下字符串长度不能超过32字节，包括 %d %s 等接收具体内容以后的长度
#define		MSG_GET_EXP						"B" "\xB9" "n nh" "\xCB" "n " "\xAE" "\xAD" "\xEE" "c <color=green>%d <color>" "\xAE" "i" "\xD3" "m kinh nghi" "\xD6" "m"
#define		MSG_DEC_EXP						"B" "\xB9" "n t" "\xE6" "n th" "\xCA" "t <color=green>%d <color>" "\xAE" "i" "\xD3" "m kinh nghi" "\xD6" "m"
#define		MSG_LEVEL_UP					"\xA7" "\xBC" "ng c" "\xCA" "p " "\xAE" "\xB9" "t %d c" "\xCA" "p"
#define		MSG_LEADER_LEVEL_UP				"\xA7" "\xBC" "ng c" "\xCA" "p th" "\xE8" "ng so" "\xB8" "i c" "\xF1" "a b" "\xB9" "n " "\xAE" "\xB9" "t c" "\xCA" "p %d"
#define		MSG_GET_ATTRIBUTE_POINT			"B" "\xB9" "n c" "\xE3" " %d " "\xAE" "i" "\xD3" "m ti" "\xD2" "m n" "\xA8" "ng"
#define		MSG_GET_SKILL_POINT				"B" "\xB9" "n c" "\xE3" " %d " "\xAE" "i" "\xD3" "m k" "\xFC" " n" "\xA8" "ng"
#define		MSG_GET_ATTRIBUTE_SKILL_POINT	"B" "\xB9" "n c" "\xE3" " %d " "\xAE" "i" "\xD3" "m ti" "\xD2" "m n" "\xA8" "ng %d " "\xAE" "i" "\xD3" "m k" "\xFC" " n" "\xA8" "ng"

#define		MSG_TEAM_SEND_INVITE			"B" "\xB9" "n g" "\xF6" "i " "\xAE" "\xD5" "n %s l" "\xEA" "i m" "\xEA" "i gia nh" "\xCB" "p t" "\xE6" " " "\xAE" "\xE9" "i"
#define		MSG_TEAM_GET_INVITE				"\xA7" "\xE9" "i tr" "\xAD" "\xEB" "ng %s g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i gia nh" "\xCB" "p t" "\xE6" " " "\xAE" "\xE9" "i " "\xAE" "\xD5" "n b" "\xB9" "n"
#define		MSG_TEAM_REFUSE_INVITE			"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s t" "\xF5" " ch" "\xE8" "i l" "\xEA" "i gia nh" "\xCB" "p t" "\xE6" " " "\xAE" "\xE9" "i c" "\xF1" "a nh" "\xE3" "m b" "\xB9" "n"
#define		MSG_TEAM_APPLY_INVITE_FAIL		"Nh" "\xE3" "m m" "\xB5" " b" "\xB9" "n v" "\xF5" "a " "\xAE" "\xE8" "ng " "\xFD" " gia nh" "\xCB" "p kh" "\xAB" "ng t" "\xE5" "n t" "\xB9" "i"
#define		MSG_TEAM_APPLY_INVITE_FAIL2		"Nh" "\xE3" "m m" "\xB5" " b" "\xB9" "n v" "\xF5" "a " "\xAE" "\xE8" "ng " "\xFD" " gia nh" "\xCB" "p " "\xAE" "\xB7" " " "\xAE" "\xE3" "ng ch" "\xF8" "c n" "\xA8" "ng chi" "\xAA" "u m" "\xE9"
#define		MSG_TEAM_CREATE					"B" "\xB9" "n s" "\xB8" "ng l" "\xCB" "p n" "\xAA" "n m" "\xE9" "t nh" "\xE3" "m m" "\xED" "i"
#define		MSG_TEAM_CREATE_FAIL			"S" "\xB8" "ng l" "\xCB" "p nh" "\xE3" "m th" "\xCA" "t b" "\xB9" "i."
#define		MSG_TEAM_CREATE_FAIL1			"PK m" "\xAB" " h" "\xD7" "nh bang chi" "\xD5" "n kh" "\xAB" "ng th" "\xD3" " s" "\xB8" "ng l" "\xCB" "p nh" "\xE3" "m m" "\xED" "i!"
#define		MSG_TEAM_CANNOT_CREATE			"B" "\xB9" "n hi" "\xD6" "n gi" "\xEA" " kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p nh" "\xE3" "m!"
#define		MSG_TEAM_TARGET_CANNOT_ADD_TEAM	"\xA7" "\xE8" "i ph" "\xAD" "\xAC" "ng hi" "\xD6" "n gi" "\xEA" " kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p nh" "\xE3" "m!"
#define		MSG_TEAM_IS_FULL				"Nh" "\xE3" "m m" "\xB5" " b" "\xB9" "n xin ph" "\xD0" "p gia nh" "\xCB" "p " "\xAE" "\xB7" " " "\xAE" "\xF1" " s" "\xE8" " l" "\xAD" "\xEE" "ng"
#define		MSG_TEAM_OPEN					"Nh" "\xE3" "m c" "\xF1" "a b" "\xB9" "n hi" "\xD6" "n t" "\xB9" "i c" "\xE3" " th" "\xD3" " ti" "\xD5" "p nh" "\xCB" "n th" "\xB5" "nh vi" "\xAA" "n m" "\xED" "i"
#define		MSG_TEAM_CLOSE					"Nh" "\xE3" "m c" "\xF1" "a b" "\xB9" "n hi" "\xD6" "n t" "\xB9" "i kh" "\xAB" "ng th" "\xD3" " ti" "\xD5" "p nh" "\xCB" "n th" "\xB5" "nh vi" "\xAA" "n m" "\xED" "i"
#define		MSG_TEAM_MODEPICK_SELF			"T" "\xF9" " nh" "\xC6" "t"
#define		MSG_TEAM_MODEPICK_FREE			"T" "\xF9" " do nh" "\xC6" "t"
#define		MSG_TEAM_MODEPICK_CAPTAIN		"\xA7" "\xE9" "i tr" "\xAD" "\xEB" "ng nh" "\xC6" "t"
#define		MSG_TEAM_MODEPICK_ALTERNATE		"Lu" "\xA9" "n phi" "\xAA" "n nh" "\xC6" "t"
#define		MSG_TEAM_PKFOLLOW_OPEN			"B" "\xB9" "n m" "\xEB" " ch" "\xD5" " " "\xAE" "\xE9" " PK theo nh" "\xE3" "m"
#define		MSG_TEAM_PKFOLLOW_CLOSE			"B" "\xB9" "n " "\xAE" "\xE3" "ng ch" "\xD5" " " "\xAE" "\xE9" " PK theo nh" "\xE3" "m"
#define		MSG_TEAM_ADD_MEMBER				"%s tr" "\xEB" " th" "\xB5" "nh b" "\xBB" "ng h" "\xF7" "u c" "\xF1" "a nh" "\xE3" "m B" "\xB9" "n."
#define		MSG_TEAM_SELF_ADD				"B" "\xB9" "n " "\xAE" "\xB7" " tham gia nh" "\xE3" "m c" "\xF1" "a %s"
#define		MSG_TEAM_ADDMEMBER_NOTVALID		"B" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " tham gia nh" "\xE3" "m c" "\xF1" "a ng" "\xAD" "\xEA" "i ch" "\xAC" "i m" "\xED" "i"
#define		MSG_TEAM_DISMISS_CAPTAIN		"B" "\xB9" "n " "\xAE" "\xB7" " gi" "\xB6" "i t" "\xB8" "n nh" "\xE3" "m c" "\xF1" "a m" "\xD7" "nh"
#define		MSG_TEAM_DISMISS_MEMBER			"%s gi" "\xB6" "i t" "\xB8" "n nh" "\xE3" "m!"
#define		MSG_TEAM_KICK_ONE				"%s b" "\xDE" " khai tr" "\xF5" " kh" "\xE1" "i nh" "\xE3" "m"
#define		MSG_TEAM_BE_KICKEN				"B" "\xB9" "n b" "\xDE" " khai tr" "\xF5" " kh" "\xE1" "i nh" "\xE3" "m"
#define		MSG_TEAM_APPLY_ADD				"%s xin ph" "\xD0" "p gia nh" "\xCB" "p nh" "\xE3" "m!"
#define		MSG_TEAM_APPLY_ADD_SELF_MSG		"B" "\xB9" "n g" "\xF6" "i l" "\xEA" "i xin ph" "\xD0" "p gia nh" "\xCB" "p t" "\xE6" " " "\xAE" "\xE9" "i c" "\xF1" "a %s"
#define		MSG_TEAM_LEAVE					"%s r" "\xEA" "i kh" "\xE1" "i nh" "\xE3" "m."
#define		MSG_TEAM_LEAVE_SELF_MSG			"B" "\xB9" "n " "\xAE" "\xB7" " r" "\xEA" "i kh" "\xE1" "i nh" "\xE3" "m c" "\xF1" "a %s"
#define		MSG_TEAM_CHANGE_CAPTAIN_FAIL1	"\xA7" "\xB6" "m nh" "\xCB" "n nh" "\xE3" "m tr" "\xAD" "\xEB" "ng th" "\xCA" "t b" "\xB9" "i!"
#define		MSG_TEAM_CHANGE_CAPTAIN_FAIL2	"%s kh" "\xAB" "ng " "\xAE" "\xF1" " s" "\xF8" "c th" "\xE8" "ng so" "\xB8" "i!"
#define		MSG_TEAM_CHANGE_CAPTAIN_FAIL3	"Kh" "\xAB" "ng th" "\xD3" " giao ch" "\xF8" "c v" "\xF4" " " "\xAE" "\xE9" "i tr" "\xAD" "\xEB" "ng cho ng" "\xAD" "\xEA" "i m" "\xED" "i ch" "\xAC" "i"
#define		MSG_TEAM_CHANGE_CAPTAIN			"%s " "\xAE" "\xAD" "\xEE" "c " "\xAE" "\xB6" "m nh" "\xCB" "n l" "\xB5" " nh" "\xE3" "m tr" "\xAD" "\xEB" "ng"
#define		MSG_TEAM_CHANGE_CAPTAIN_SELF	"B" "\xB9" "n " "\xAE" "\xAD" "\xEE" "c %s " "\xAE" "\xB6" "m nh" "\xCB" "n l" "\xB5" " nh" "\xE3" "m tr" "\xAD" "\xEB" "ng"
#define		MSG_TEAM_AUTO_CAPTAIN			"%s " "\xAE" "\xAD" "\xEE" "c h" "\xD6" " th" "\xE8" "ng ch" "\xD8" " " "\xAE" "\xDE" "nh l" "\xB5" " nh" "\xE3" "m tr" "\xAD" "\xEB" "ng"
#define		MSG_TEAM_AUTO_CAPTAIN_SELF		"B" "\xB9" "n " "\xAE" "\xAD" "\xEE" "c h" "\xD6" " th" "\xE8" "ng ch" "\xD8" " " "\xAE" "\xDE" "nh l" "\xB5" " nh" "\xE3" "m tr" "\xAD" "\xEB" "ng"


#define		MSG_CHATROOM_CREATE				"B" "\xB9" "n t" "\xB9" "o ph" "\xDF" "ng m" "\xED" "i %s"
#define		MSG_CHATROOM_CREATE_ERROR_SAMENAME	"T" "\xAA" "n n" "\xB5" "y " "\xAE" "\xB7" " t" "\xE5" "n t" "\xB9" "i"
#define		MSG_CHATROOM_CREATE_ERROR_SAMEHOST	"B" "\xB9" "n " "\xAE" "\xB7" " t" "\xB9" "o m" "\xE9" "t ph" "\xDF" "ng r" "\xE5" "i"
#define		MSG_CHATROOM_CREATE_ERROR_NAME	"T" "\xAA" "n kh" "\xAB" "ng h" "\xEE" "p l" "\xD6"
#define		MSG_CHATROOM_CREATE_ERROR_PASS	"M" "\xCB" "t m" "\xB7" " ph" "\xDF" "ng kh" "\xAB" "ng h" "\xEE" "p l" "\xD6"
#define		MSG_CHATROOM_CREATE_ERROR_ROOMFULL	"S" "\xE8" " ph" "\xDF" "ng t" "\xB8" "n g" "\xC9" "u c" "\xF1" "a m" "\xB8" "y ch" "\xF1" " n" "\xB5" "y " "\xAE" "\xB7" " " "\xAE" "\xF1" ", kh" "\xAB" "ng th" "\xD3" " t" "\xB9" "o th" "\xAA" "m"
#define		MSG_CHATROOM_SELF_JOIN			"B" "\xB9" "n v" "\xB5" "o ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_JOIN				"%s " "\xAE" "\xB7" " v" "\xB5" "o ph" "\xDF" "ng"
#define		MSG_CHATROOM_JOIN_FAIL1			"B" "\xB9" "n nh" "\xCB" "p sai m" "\xCB" "t m" "\xB7" " ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_JOIN_FAIL2			"B" "\xB9" "n b" "\xDE" " li" "\xD6" "t v" "\xB5" "o s" "\xE6" " " "\xAE" "en kh" "\xAB" "ng th" "\xD3" " " "\xAE" "\xA8" "ng nh" "\xCB" "p v" "\xB5" "o ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_JOIN_FAIL3			"Ph" "\xDF" "ng %s " "\xAE" "\xB7" " " "\xAE" "\xC7" "y"
#define		MSG_CHATROOM_SELF_LEAVE			"B" "\xB9" "n r" "\xEA" "i kh" "\xE1" "i ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_LEAVE				"%s r" "\xEA" "i kh" "\xE1" "i ph" "\xDF" "ng"
#define		MSG_CHATROOM_SELF_DELETE		"B" "\xB9" "n " "\xAE" "\xB7" " h" "\xF1" "y ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_SELF_FORCELEAVE	"B" "\xB9" "n b" "\xDE" " " "\xAE" "\xC8" "y kh" "\xE1" "i ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_SELF_BEKICK		"B" "\xB9" "n b" "\xDE" " khai tr" "\xF5" " kh" "\xE1" "i ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_BEKICK				"%s b" "\xDE" " khai tr" "\xF5" " kh" "\xE1" "i ph" "\xDF" "ng"
#define		MSG_CHATROOM_ADDBLACKLIST		"Th" "\xAA" "m %s v" "\xB5" "o s" "\xE6" " " "\xAE" "en"
#define		MSG_CHATROOM_ADDBLACKLIST_FAIL	"Th" "\xAA" "m %s v" "\xB5" "o s" "\xE6" " " "\xAE" "en th" "\xCA" "t b" "\xB9" "i"
#define		MSG_CHATROOM_REMOVEBLACKLIST	"L" "\xAD" "\xEE" "c b" "\xE1" " %s kh" "\xE1" "i s" "\xE6" " " "\xAE" "en"
#define		MSG_CHATROOM_SELD_CHANGEPW		"B" "\xB9" "n " "\xAE" "\xB7" " " "\xAE" "\xE6" "i m" "\xCB" "t m" "\xB7" " ph" "\xDF" "ng %s"
#define		MSG_CHATROOM_OPENGAME			"L" "\xAD" "\xEE" "t ch" "\xAC" "i m" "\xED" "i " "\xAE" "\xAD" "\xEE" "c m" "\xEB" ", l" "\xC7" "n n" "\xB5" "y " "\xAE" "\xC6" "t t" "\xE8" "i " "\xAE" "a %d " "\xAE" "i" "\xD3" "m"
#define		MSG_CHATROOM_REVERSE			"L" "\xAD" "\xEE" "t ch" "\xAC" "i c" "\xF1" "a ph" "\xDF" "ng %s " "\xAE" "\xB7" " k" "\xD5" "t th" "\xF3" "c"

#define		MSG_CHAT_APPLY_ADD_FRIEND		"B" "\xB9" "n " "\xAE" "\xD5" "n %s xin ph" "\xD0" "p " "\xAE" "\xAD" "\xEE" "c k" "\xD5" "t giao."
#define		MSG_CHAT_FRIEND_HAD_IN			"%s " "\xAE" "\xB7" " " "\xAE" "\xAD" "\xEE" "c nh" "\xCB" "n l" "\xB5" "m b" "\xBC" "ng h" "\xF7" "u."
#define		MSG_CHAT_GET_FRIEND_APPLY		"%s xin ph" "\xD0" "p gia nh" "\xCB" "p b" "\xBB" "ng h" "\xF7" "u"
#define		MSG_CHAT_REFUSE_FRIEND			"%s t" "\xF5" " ch" "\xE8" "i y" "\xAA" "u c" "\xC7" "u k" "\xD5" "t b" "\xB9" "n"
#define		MSG_CHAT_ADD_FRIEND_FAIL		"Th" "\xAA" "m %s v" "\xB5" "o danh s" "\xB8" "ch b" "\xBB" "ng h" "\xF7" "u th" "\xCA" "t b" "\xB9" "i"
#define		MSG_CHAT_ADD_FRIEND_SUCCESS		"Th" "\xAA" "m %s v" "\xB5" "o danh s" "\xB8" "ch b" "\xBB" "ng h" "\xF7" "u th" "\xB5" "nh c" "\xAB" "ng"
#define		MSG_CHAT_FRIEND_ONLINE			"H" "\xB6" "o h" "\xF7" "u %s l" "\xAA" "n m" "\xB9" "ng r" "\xE5" "i!"
#define		MSG_CHAT_FRIEND_OFFLINE			"H" "\xB6" "o h" "\xF7" "u %s r" "\xEA" "i m" "\xB9" "ng r" "\xE5" "i!"
#define		MSG_CHAT_ENEMY_ONLINE			"C" "\xF5" "u nh" "\xA9" "n %s l" "\xAA" "n m" "\xB9" "ng r" "\xE5" "i!"
#define		MSG_CHAT_ENEMY_OFFLINE			"C" "\xF5" "u nh" "\xA9" "n %s r" "\xEA" "i m" "\xB9" "ng r" "\xE5" "i!"
#define		MSG_CHAT_DELETE_FRIEND			"B" "\xB9" "n c" "\xEF" "ng %s h" "\xF1" "y b" "\xE1" " quan h" "\xD6"
#define		MSG_CHAT_DELETED_FRIEND			"%s c" "\xEF" "ng B" "\xB9" "n h" "\xF1" "y b" "\xE1" " quan h" "\xD6"

#define		MSG_SHOP_NO_ROOM				"Kho" "\xB6" "ng tr" "\xE8" "ng trong t" "\xF3" "i kh" "\xAB" "ng " "\xAE" "\xF1"
#define		MSG_SHOP_NO_MONEY				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " ng" "\xA9" "n l" "\xAD" "\xEE" "ng"
#define		MSG_SHOP_NO_EXTPOINT			"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " ti" "\xD2" "n " "\xAE" "\xE5" "ng"
#define		MSG_SHOP_NO_FUYUAN				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " ph" "\xF3" "c duy" "\xAA" "n"
#define		MSG_SHOP_NO_REPUTE				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " danh v" "\xE4" "ng"
#define		MSG_SHOP_NO_ACCUM				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " t" "\xDD" "ch l" "\xF2" "y"
#define		MSG_SHOP_NO_HONOR				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " vinh d" "\xF9"
#define		MSG_SHOP_NO_RESPECT				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " uy danh"

#define		MSG_NPC_NO_MANA					"N" "\xE9" "i l" "\xF9" "c kh" "\xAB" "ng " "\xAE" "\xF1" "!"
#define		MSG_NPC_NO_STAMINA				"Th" "\xD3" " l" "\xF9" "c kh" "\xAB" "ng " "\xAE" "\xF1" "!"
#define		MSG_NPC_NO_LIFE					"Sinh l" "\xF9" "c kh" "\xAB" "ng " "\xAE" "\xF1" "!"

#define		MSG_NPC_NOT_USE_TOWNPORTAL		"Kh" "\xAB" "ng th" "\xD3" " s" "\xF6" " d" "\xF4" "ng th" "\xE6" " " "\xAE" "\xDE" "a ph" "\xEF" " " "\xEB" " " "\xAE" "\xA9" "y"
#define		MSG_NPC_NOT_PAY_FOR_SPEECH		"B" "\xB9" "n b" "\xDE" " c" "\xCA" "m ph" "\xB8" "t ng" "\xAB" "n " "\xAE" "\xD5" "n %H:%M - %d/%m/%Y"
#define		MSG_NPC_NOT_USE_SKILL_SILENT	"B" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " thi tri" "\xD3" "n v" "\xE2" " c" "\xAB" "ng l" "\xF3" "c n" "\xB5" "y"
#define		MSG_NPC_NOT_USE_SKILL_DISTANCE	"B" "\xB9" "n " "\xAE" "\xF8" "ng c" "\xB8" "ch ti" "\xAA" "u " "\xAE" "i" "\xD3" "m qu" "\xB8" " xa, tr" "\xAD" "\xED" "c m" "\xBE" "t s" "\xF6" " d" "\xF4" "ng v" "\xE2" " c" "\xAB" "ng n" "\xB5" "y s" "\xCF" " kh" "\xAB" "ng " "\xAE" "\xF1" " hi" "\xD6" "u nghi" "\xD6" "m"
#define		MSG_NPC_NOT_USE_SKILL_WEAPON	"V" "\xF2" " kh" "\xDD" " m" "\xB5" " b" "\xB9" "n " "\xAE" "ang s" "\xF6" " d" "\xF4" "ng kh" "\xAB" "ng ph" "\xEF" " h" "\xEE" "p v" "\xED" "i lo" "\xB9" "i v" "\xE2" " c" "\xAB" "ng m" "\xB5" " b" "\xB9" "n hi" "\xD6" "n " "\xAE" "ang s" "\xF6" " d" "\xF4" "ng"
#define		MSG_NPC_NOT_USE_SKILL_HORSE1	"V" "\xE2" " c" "\xAB" "ng m" "\xB5" " b" "\xB9" "n s" "\xF6" " d" "\xF4" "ng hi" "\xD6" "n gi" "\xEA" " kh" "\xAB" "ng th" "\xD3" " c" "\xAD" "\xEC" "i ng" "\xF9" "a"
#define		MSG_NPC_NOT_USE_SKILL_HORSE2	"V" "\xE2" " c" "\xAB" "ng m" "\xB5" " b" "\xB9" "n s" "\xF6" " d" "\xF4" "ng hi" "\xD6" "n gi" "\xEA" " c" "\xC7" "n ph" "\xB6" "i c" "\xAD" "\xEC" "i ng" "\xF9" "a"
#define		MSG_NPC_RENASCENCE_SOMEONE		"B" "\xB9" "n b" "\xDE" " %s h" "\xB9" " tr" "\xE4" "ng th" "\xAD" "\xAC" "ng"
#define		MSG_NPC_RENASCENCE				"B" "\xB9" "n " "\xAE" "\xB7" " b" "\xDE" " tr" "\xE4" "ng th" "\xAD" "\xAC" "ng"

#define		MSG_OBJ_CANNOT_PICKUP			"B" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " l" "\xCA" "y v" "\xCB" "t ph" "\xC8" "m c" "\xF1" "a ng" "\xAD" "\xEA" "i kh" "\xB8" "c"
#define		MSG_MONEY_CANNOT_PICKUP			"B" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " l" "\xCA" "y ti" "\xD2" "n c" "\xF1" "a ng" "\xAD" "\xEA" "i kh" "\xB8" "c"
#define		MSG_OBJ_TOO_FAR					"V" "\xCB" "t ph" "\xC8" "m qu" "\xB8" " xa kh" "\xAB" "ng th" "\xD3" " l" "\xCA" "y"
#define		MSG_DEC_MONEY					"B" "\xB9" "n b" "\xDE" " m" "\xCA" "t <color=yellow>%d <color>l" "\xAD" "\xEE" "ng b" "\xB9" "c"
#define		MSG_EARN_MONEY					"B" "\xB9" "n nh" "\xCB" "n " "\xAE" "\xAD" "\xEE" "c <color=yellow>%d <color>l" "\xAD" "\xEE" "ng b" "\xB9" "c"
#define		MSG_DEATH_LOSE_ITEM				"B" "\xB9" "n " "\xAE" "\xB7" " b" "\xDE" " m" "\xCA" "t <color=blue>%s<color>"
#define		MSG_ADD_ITEM					"B" "\xB9" "n nh" "\xCB" "n " "\xAE" "\xAD" "\xEE" "c m" "\xE9" "t c" "\xB8" "i <color=blue>%s<color>"
#define		MSG_ADD_ITEM_STACK				"B" "\xB9" "n nh" "\xCB" "n " "\xAE" "\xAD" "\xEE" "c %d c" "\xB8" "i <color=blue>%s<color>"

#define		MSG_ITEM_SAME_IN_IMMEDIATE		"Hi" "\xD6" "n " "\xAE" "\xB7" " c" "\xE3" " v" "\xCB" "t ph" "\xC8" "m " "\xAE" "\xE5" "ng lo" "\xB9" "i r" "\xE5" "i"
#define		MSG_ITEM_PUT_IN_IMMEDIATE		"Thanh ph" "\xDD" "m t" "\xBE" "t kh" "\xAB" "ng th" "\xD3" " " "\xAE" "\xC6" "t v" "\xB5" "o v" "\xCB" "t ph" "\xC8" "m n" "\xB5" "y!"

#define		MSG_ITEM_DAMAGED				"Trang b" "\xDE" " %s " "\xAE" "\xB7" " b" "\xDE" " h" "\xE1" "ng r" "\xE5" "i"
#define		MSG_ITEM_NEARLY_DAMAGED			"Trang b" "\xDE" " %s s" "\xBE" "p h" "\xE1" "ng h" "\xB7" "y " "\xAE" "\xD5" "n th" "\xEE" " r" "\xCC" "n " "\xAE" "\xD3" " s" "\xF6" "a ch" "\xF6" "a l" "\xB9" "i"
#define		MSG_ITEM_REPAIRED				"Ti" "\xAA" "u t" "\xE8" "n %d l" "\xAD" "\xEE" "ng b" "\xB9" "c " "\xAE" "\xD3" " s" "\xF6" "a ch" "\xF6" "a %s"

#define		MSG_LOCK_NOT_THROW				"Nh" "\xBB" "m b" "\xB6" "o v" "\xD6" " t" "\xB5" "i s" "\xB6" "n cho b" "\xB9" "n V" "\xCB" "t ph" "\xC8" "m n" "\xB5" "y kh" "\xAB" "ng " "\xAE" "\xAD" "\xEE" "c t" "\xEF" "y " "\xFD" " v" "\xF8" "t b" "\xE1"
#define		MSG_LOCK_NOT_TRADE				"Nh" "\xBB" "m b" "\xB6" "o v" "\xD6" " t" "\xB5" "i s" "\xB6" "n cho b" "\xB9" "n V" "\xCB" "t ph" "\xC8" "m n" "\xB5" "y kh" "\xAB" "ng th" "\xD3" " giao d" "\xDE" "ch"
#define		MSG_LOCK_NOT_SETPRICE			"Nh" "\xBB" "m b" "\xB6" "o v" "\xD6" " t" "\xB5" "i s" "\xB6" "n cho b" "\xB9" "n V" "\xCB" "t ph" "\xC8" "m n" "\xB5" "y kh" "\xAB" "ng th" "\xD3" " " "\xAE" "\xDE" "nh gi" "\xB8"

#define		MSG_BROKEN_CANTREPAIR			"Trang b" "\xDE" " " "\xAE" "\xB7" " h" "\xAD" " h" "\xE1" "ng ho" "\xB5" "n to" "\xB5" "n kh" "\xAB" "ng th" "\xD3" " s" "\xF6" "a ch" "\xF7" "a b" "\xBB" "ng ph" "\xAD" "\xAC" "ng ph" "\xB8" "p b" "\xD7" "nh th" "\xAD" "\xEA" "ng"

#define		MSG_TRADE_STATE_OPEN			"B" "\xB9" "n hi" "\xD6" "n gi" "\xEA" " c" "\xE3" " th" "\xD3" " giao d" "\xDE" "ch"
#define		MSG_TRADE_STATE_CLOSE			"B" "\xB9" "n hi" "\xD6" "n gi" "\xEA" " kh" "\xAB" "ng th" "\xD3" " giao d" "\xDE" "ch"
#define		MSG_TRADE_SELF_LOCK				"B" "\xB9" "n " "\xAE" "\xB7" " kh" "\xE3" "a ch" "\xF8" "c n" "\xA8" "ng giao d" "\xDE" "ch v" "\xCB" "t ph" "\xC8" "m, ch" "\xEA" " " "\xAE" "\xE8" "i ph" "\xAD" "\xAC" "ng tr" "\xB6" " l" "\xEA" "i"
#define		MSG_TRADE_DEST_LOCK				"Ng" "\xAD" "\xAC" "i ch" "\xAC" "i %s " "\xAE" "\xB7" " kh" "\xE3" "a ch" "\xF8" "c n" "\xA8" "ng giao d" "\xDE" "ch v" "\xCB" "t ph" "\xC8" "m"
#define		MSG_TRADE_SUCCESS				"B" "\xB9" "n c" "\xEF" "ng v" "\xED" "i %s giao d" "\xDE" "ch th" "\xB5" "nh c" "\xAB" "ng"
#define		MSG_TRADE_FAIL					"B" "\xB9" "n c" "\xEF" "ng v" "\xED" "i %s giao d" "\xDE" "ch th" "\xCA" "t b" "\xB9" "i"
#define		MSG_TRADE_SELF_ROOM_FULL		"Kho" "\xB6" "ng tr" "\xE8" "ng trong t" "\xF3" "i c" "\xF1" "a B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" "!"
#define		MSG_TRADE_DEST_ROOM_FULL		"%s kho" "\xB6" "ng tr" "\xE8" "ng trong t" "\xF3" "i kh" "\xAB" "ng " "\xAE" "\xF1" "!"
#define		MSG_TRADE_SEND_APPLY			"B" "\xB9" "n g" "\xC6" "p %s xin ph" "\xD0" "p giao d" "\xDE" "ch!"
#define		MSG_TRADE_GET_APPLY				"%s xin ph" "\xD0" "p c" "\xEF" "ng v" "\xED" "i B" "\xB9" "n giao d" "\xDE" "ch!"
#define		MSG_TRADE_REFUSE_APPLY			"%s c" "\xF9" " tuy" "\xD6" "t giao d" "\xDE" "ch v" "\xED" "i B" "\xB9" "n!"
#define		MSG_TRADE_INPUT_MONEY			"\xA7" "\xE8" "i ph" "\xAD" "\xAC" "ng " "\xAE" "\xC6" "t v" "\xB5" "o s" "\xE8" " ti" "\xD2" "n %d l" "\xAD" "\xEE" "ng"

#define		MSG_SPAR_SEND_APPLY				"B" "\xB9" "n g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i t" "\xFB" " th" "\xDD" " v" "\xE2" " ngh" "\xD6" " " "\xAE" "\xD5" "n %s"
#define		MSG_SPAR_GET_APPLY				"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i t" "\xFB" " th" "\xDD" " v" "\xE2" " ngh" "\xD6" " " "\xAE" "\xD5" "n v" "\xED" "i b" "\xB9" "n"
#define		MSG_SPAR_REFUSE_APPLY			"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s t" "\xF5" " ch" "\xE8" "i l" "\xEA" "i m" "\xEA" "i t" "\xFB" " v" "\xE2" " c" "\xF1" "a b" "\xB9" "n"
#define		MSG_SPAR_VICTORY				"B" "\xB9" "n " "\xAE" "\xB7" " chi" "\xD5" "n th" "\xBE" "ng trong l" "\xC7" "n t" "\xFB" " th" "\xDD" " v" "\xE2" " ngh" "\xD6" " n" "\xB5" "y"
#define		MSG_SPAR_DEFEAT					"T" "\xFB" " v" "\xE2" " th" "\xCA" "t b" "\xB9" "i, xin " "\xAE" "\xF5" "ng ng" "\xB7" " l" "\xDF" "ng"

#define		MSG_TRADE_FOLKGAME_SEND_APPLY	"B" "\xB9" "n g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i " "\xAE" "\xCA" "u " "\xAE" "\xE8" " thu" "\xCB" "t " "\xAE" "\xD5" "n %s"
#define		MSG_TRADE_FOLKGAME_GET_APPLY	"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i " "\xAE" "\xCA" "u " "\xAE" "\xE8" " thu" "\xCB" "t " "\xAE" "\xD5" "n v" "\xED" "i b" "\xB9" "n"
#define		MSG_TRADEFOLKGAME_SELF_ROOM_FULL	"H" "\xB5" "nh trang c" "\xF1" "a b" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %dx%d " "\xAB" " tr" "\xE8" "ng"
#define		MSG_TRADEFOLKGAME_DEST_ROOM_FULL	"H" "\xB5" "nh trang c" "\xF1" "a %s kh" "\xAB" "ng " "\xAE" "\xF1" " %dx%d " "\xAB" " tr" "\xE8" "ng"

#define		MSG_PK_NORMAL_FLAG_OPEN			"Tr" "\xB9" "ng th" "\xB8" "i PK " "\xEB" " d" "\xB9" "ng chi" "\xD5" "n " "\xAE" "\xCA" "u"
#define		MSG_PK_NORMAL_FLAG_CLOSE		"Tr" "\xB9" "ng th" "\xB8" "i PK " "\xEB" " d" "\xB9" "ng luy" "\xD6" "n c" "\xAB" "ng"
#define		MSG_PK_NORMAL_FLAG_DS			"Tr" "\xB9" "ng th" "\xB8" "i PK " "\xEB" " d" "\xB9" "ng th" "\xF8" "c gi" "\xD5" "t ng" "\xAD" "\xEA" "i"
#define		MSG_PK_NORMAL_FLAG_TONGWAR		"Tr" "\xB9" "ng th" "\xB8" "i PK " "\xEB" " d" "\xB9" "ng th" "\xF8" "c m" "\xAB" " h" "\xD7" "nh bang chi" "\xD5" "n"
#define		MSG_PK_NORMAL_FLAG_UNKNOWN		"Tr" "\xB9" "ng th" "\xB8" "i PK " "\xEB" " d" "\xB9" "ng th" "\xF8" "c ch" "\xAD" "a r" "\xE2"
#define		MSG_PK_HIGHT_LOCK_NOT_SWITCH	"Hi" "\xD6" "n gi" "\xEA" " PK c" "\xF1" "a b" "\xB9" "n >= %d, tr" "\xAD" "\xED" "c khi PK xin h" "\xB7" "y h" "\xF1" "y b" "\xE1" " tr" "\xB9" "ng th" "\xB8" "i kh" "\xE3" "a b" "\xB6" "o hi" "\xD3" "m."
#define		MSG_PKSTATE_NOT_OPEN			"Tr" "\xB9" "ng th" "\xB8" "i PK n" "\xB5" "y ch" "\xAD" "a m" "\xEB"
#define		MSG_PK_VALUE					"Tr" "\xDE" " s" "\xE8" " PK hi" "\xD6" "n t" "\xB9" "i l" "\xB5" " %d"
#define		MSG_PK_ERROR_1					"B" "\xB9" "n hi" "\xD6" "n gi" "\xEA" " " "\xAE" "ang " "\xEB" " trong tr" "\xB9" "ng th" "\xB8" "i phi chi" "\xD5" "n " "\xAE" "\xCA" "u!"
#define		MSG_PK_ERROR_2					"Ng" "\xAD" "\xEA" "i m" "\xED" "i kh" "\xAB" "ng th" "\xD3" " gi" "\xD5" "t th" "\xEF" "!"
#define		MSG_PK_ERROR_3					"B" "\xB9" "n " "\xAE" "ang c" "\xEF" "ng v" "\xED" "i ng" "\xAD" "\xEA" "i kh" "\xB8" "c trao " "\xAE" "\xE6" "i " "\xFD" " ki" "\xD5" "n!"
#define		MSG_PK_ERROR_4					"B" "\xB9" "n " "\xAE" "ang c" "\xEF" "ng v" "\xED" "i ng" "\xAD" "\xEA" "i kh" "\xB8" "c gi" "\xD5" "t th" "\xEF" "!"
#define		MSG_PK_ERROR_5					"B" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " gi" "\xD5" "t ng" "\xAD" "\xEA" "i m" "\xED" "i!"
#define		MSG_PK_ERROR_6					"\xA7" "\xE8" "i ph" "\xAD" "\xAC" "ng " "\xAE" "ang " "\xEB" " trong tr" "\xB9" "ng th" "\xB8" "i phi chi" "\xD5" "n " "\xAE" "\xCA" "u!"
#define		MSG_PK_ERROR_7					"\xA7" "\xE8" "i ph" "\xAD" "\xAC" "ng " "\xAE" "ang c" "\xEF" "ng v" "\xED" "i ng" "\xAD" "\xEA" "i kh" "\xB8" "c gi" "\xD5" "t th" "\xEF" "!"
#define		MSG_PK_ERROR_8					"B" "\xB9" "n hi" "\xD6" "n gi" "\xEA" " kh" "\xAB" "ng th" "\xD3" " c" "\xF5" "u s" "\xB8" "t!"
#define		MSG_PK_ERROR_9					"Ng" "\xAD" "\xEA" "i n" "\xB5" "y " "\xAE" "ang trong tr" "\xB9" "ng th" "\xB8" "i " "\xAE" "\xE3" "ng c" "\xF5" "u s" "\xB8" "t"
#define		MSG_PK_ENMITY_SUCCESS_1			"%s c" "\xEF" "ng v" "\xED" "i B" "\xB9" "n ti" "\xD5" "n h" "\xB5" "nh c" "\xF5" "u s" "\xB8" "t"
#define		MSG_PK_ENMITY_SUCCESS_2			"Sau 10 gi" "\xA9" "y b" "\xBE" "t " "\xAE" "\xC7" "u ti" "\xD5" "n h" "\xB5" "nh c" "\xF5" "u s" "\xB8" "t"
#define		MSG_PK_SPAR_ENMITY_SUCCESS_1	"%s c" "\xEF" "ng v" "\xED" "i B" "\xB9" "n ti" "\xD5" "n h" "\xB5" "nh t" "\xFB" " v" "\xE2"
#define		MSG_PK_SPAR_ENMITY_SUCCESS_2	"Sau 5 gi" "\xA9" "y b" "\xBE" "t " "\xAE" "\xC7" "u ti" "\xD5" "n h" "\xB5" "nh t" "\xFB" " v" "\xE2"
#define		MSG_PK_ENMITY_CLOSE				"Tr" "\xB9" "ng th" "\xB8" "i c" "\xF5" "u s" "\xB8" "t k" "\xD5" "t th" "\xF3" "c"
#define		MSG_PK_SPAR_ENMITY_CLOSE		"Tr" "\xB9" "ng th" "\xB8" "i t" "\xFB" " v" "\xE2" " k" "\xD5" "t th" "\xF3" "c"
#define		MSG_PK_ENMITY_OPEN				"B" "\xBE" "t " "\xAE" "\xC7" "u ti" "\xD5" "n h" "\xB5" "nh c" "\xF5" "u s" "\xB8" "t"
#define		MSG_PK_SPAR_ENMITY_OPEN			"B" "\xBE" "t " "\xAE" "\xC7" "u ti" "\xD5" "n h" "\xB5" "nh t" "\xFB" " v" "\xE2"
#define		MGS_PK_IS_LOCK					"PK t" "\xF5" " phi chi" "\xD5" "n " "\xAE" "\xCA" "u chuy" "\xD3" "n sang luy" "\xD6" "n c" "\xAB" "ng ph" "\xB6" "i m" "\xCA" "t %d ph" "\xF3" "t"
#define		MGS_PK_IS_LOCK1					"Tr" "\xB9" "ng th" "\xB8" "i " "\xAE" "\xC6" "c bi" "\xD6" "t kh" "\xAB" "ng th" "\xD3" " chuy" "\xD3" "n ki" "\xD3" "u chi" "\xD5" "n " "\xAE" "\xCA" "u"
#define		MGS_PK_IS_LOCK2					"Th" "\xB5" "nh vi" "\xAA" "n bang h" "\xE9" "i m" "\xED" "i c" "\xE3" " th" "\xD3" " m" "\xEB" " chi" "\xD5" "n " "\xAE" "\xCA" "u bang h" "\xE9" "i"
#define		MGS_PK_IS_LOCK3					"Ch" "\xD5" " " "\xAE" "\xE9" "i PK nh" "\xE3" "m kh" "\xAB" "ng th" "\xD3" " t" "\xF9" " " "\xFD" " chuy" "\xD3" "n tr" "\xB9" "ng th" "\xB8" "i chi" "\xD5" "n " "\xAE" "\xCA" "u"
#define		MGS_PK_IS_LOCK4					"Trong t" "\xE6" " " "\xAE" "\xE9" "i kh" "\xAB" "ng th" "\xD3" " chuy" "\xD3" "n PK m" "\xAB" " h" "\xD7" "nh bang chi" "\xD5" "n"
#define		MGS_PK_IS_LOCK5					"\xA7" "i" "\xD3" "m PK c" "\xF1" "a b" "\xB9" "n qu" "\xB8" " nhi" "\xD2" "u, kh" "\xAB" "ng th" "\xD3" " h" "\xB9" " th" "\xF1" " " "\xAE" "\xAD" "\xEE" "c!"
#define		MGS_PK_IS_LOCK6					"\xA7" "i" "\xD3" "m kinh nghi" "\xD6" "m " "\xA9" "m c" "\xF1" "a b" "\xB9" "n qu" "\xB8" " nhi" "\xD2" "u, kh" "\xAB" "ng th" "\xD3" " h" "\xB9" " th" "\xF1" " " "\xAE" "\xAD" "\xEE" "c!"
#define		MGS_PK_IS_LOCK7					"PK chuy" "\xD3" "n gi" "\xF7" "a c" "\xB8" "c tr" "\xB9" "ng th" "\xB8" "i chi" "\xD5" "n " "\xAE" "\xCA" "u ph" "\xB6" "i m" "\xCA" "t %d gi" "\xA9" "y"

#define		MSG_TONG_CREATE_ERROR01			"B" "\xB9" "n nh" "\xCB" "p v" "\xB5" "o t" "\xAA" "n bang h" "\xE9" "i kh" "\xAB" "ng h" "\xEE" "p l" "\xD6"
#define		MSG_TONG_CREATE_ERROR02			"Phe ph" "\xB8" "i trong bang h" "\xE9" "i kh" "\xAB" "ng h" "\xEE" "p l" "\xD6"
#define		MSG_TONG_CREATE_ERROR03			"Th" "\xB5" "nh vi" "\xAA" "n bang h" "\xE9" "i kh" "\xAB" "ng th" "\xD3" " kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p m" "\xE9" "t bang h" "\xE9" "i kh" "\xB8" "c!"
#define		MSG_TONG_CREATE_ERROR04			"B" "\xB9" "n kh" "\xAB" "ng ph" "\xB6" "i l" "\xB5" " s" "\xB8" "t th" "\xF1" " kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p bang!"
#define		MSG_TONG_CREATE_ERROR05			"B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %d c" "\xCA" "p kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p bang!"
#define		MSG_TONG_CREATE_ERROR06			"B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %d " "\xAE" "\xBC" "ng c" "\xCA" "p th" "\xE8" "ng so" "\xB8" "i!"
#define		MSG_TONG_CREATE_ERROR07			"B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %d ng" "\xA9" "n l" "\xAD" "\xEE" "ng b" "\xB9" "c " "\xAE" "\xD3" " l" "\xCB" "p bang!"
#define		MSG_TONG_CREATE_ERROR08			"B" "\xB9" "n " "\xAE" "ang trong " "\xAE" "\xE9" "i ng" "\xF2" ", kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p bang!"
#define		MSG_TONG_CREATE_ERROR09			"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " Nh" "\xB9" "c v" "\xAD" "\xAC" "ng ki" "\xD5" "m!"
#define		MSG_TONG_CREATE_ERROR10			"B" "\xB9" "n " "\xAE" "ang b" "\xCB" "n ho" "\xC6" "c " "\xAE" "ang giao d" "\xDE" "ch kh" "\xAB" "ng th" "\xD3" " l" "\xCB" "p bang"
#define		MSG_TONG_CREATE_ERROR11			"B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %d danh v" "\xE4" "ng"
#define		MSG_TONG_CREATE_ERROR12			"B" "\xB9" "n kh" "\xAB" "ng " "\xAE" "\xF1" " %d ph" "\xF3" "c duy" "\xAA" "n"
#define		MSG_TONG_CREATE_ERROR13			"S" "\xE8" " bang h" "\xE9" "i c" "\xF1" "a server " "\xAE" "\xB7" " " "\xAE" "\xB9" "t gi" "\xED" "i h" "\xB9" "n kh" "\xAB" "ng th" "\xD3" " t" "\xB9" "o th" "\xAA" "m"
#define		MSG_TONG_CREATE_ERROR14			"T" "\xAA" "n bang h" "\xE9" "i ho" "\xC6" "c t" "\xAA" "n bang ch" "\xF1" " b" "\xDE" " l" "\xE7" "i kh" "\xAB" "ng th" "\xD3" " t" "\xB9" "o"
#define		MSG_TONG_CREATE_ERROR15			"Bang h" "\xE9" "i " "\xAE" "\xB7" " t" "\xE5" "n t" "\xB9" "i ho" "\xC6" "c b" "\xB9" "n " "\xAE" "ang l" "\xB5" " bang ch" "\xF1" " c" "\xF1" "a m" "\xE9" "t bang h" "\xE9" "i kh" "\xB8" "c"
#define		MSG_TONG_APPLY_CREATE			"B" "\xB9" "n g" "\xF6" "i y" "\xAA" "u c" "\xC7" "u th" "\xB5" "nh l" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_CREATE_SUCCESS			"Th" "\xB5" "nh l" "\xCB" "p bang h" "\xE9" "i th" "\xB5" "nh c" "\xAB" "ng"
#define		MSG_TONG_SEND_APPLY				"B" "\xB9" "n g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i gia nh" "\xCB" "p bang h" "\xE9" "i " "\xAE" "\xD5" "n %s"
#define		MSG_TONG_REV_APPLY				"%s g" "\xF6" "i l" "\xEA" "i m" "\xEA" "i gia nh" "\xCB" "p bang h" "\xE9" "i " "\xAE" "\xD5" "n b" "\xB9" "n"
#define		MSG_TONG_APPLY_ADD				"B" "\xB9" "n g" "\xF6" "i y" "\xAA" "u c" "\xC7" "u xin gia nh" "\xCB" "p bang h" "\xE9" "i!"
#define		MSG_TONG_APPLY_ADD_SELF_MSG		"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s xin ph" "\xD0" "p gia nh" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_APPLY_ADD_ERROR		"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s kh" "\xAB" "ng " "\xAE" "\xF1" " " "\xAE" "i" "\xD2" "u ki" "\xD6" "n gia nh" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_APPLY_ADD_ERROR1		"Th" "\xB5" "nh vi" "\xAA" "n bang h" "\xE9" "i kh" "\xAB" "ng th" "\xD3" " gia nh" "\xCB" "p bang h" "\xE9" "i kh" "\xB8" "c"
#define		MSG_TONG_APPLY_ADD_ERROR2		"B" "\xB9" "n ph" "\xB6" "i l" "\xB5" " s" "\xB8" "t th" "\xF1" " m" "\xED" "i c" "\xE3" " th" "\xD3" " gia nh" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_APPLY_ADD_ERROR3		"B" "\xB9" "n ph" "\xB6" "i r" "\xEA" "i kh" "\xE1" "i t" "\xE6" " " "\xAE" "\xE9" "i m" "\xED" "i c" "\xE3" " th" "\xD3" " gia nh" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_APPLY_ADD_ERROR4		"B" "\xB9" "n v" "\xF5" "a ch" "\xF1" " " "\xAE" "\xE9" "ng r" "\xEA" "i kh" "\xE1" "i bang h" "\xE9" "i, " "\xAE" "ang trong th" "\xEA" "i gian th" "\xF6" " th" "\xB8" "ch kh" "\xAB" "ng th" "\xD3" " g" "\xF6" "i y" "\xAA" "u c" "\xC7" "u"
#define		MSG_TONG_APPLY_ADD_ERROR5		"Bang h" "\xE9" "i m" "\xB5" " b" "\xB9" "n v" "\xF5" "a xin gia nh" "\xCB" "p " "\xAE" "\xB7" " " "\xAE" "\xE3" "ng ch" "\xF8" "c n" "\xA8" "ng chi" "\xAA" "u m" "\xE9" " " "\xAE" "\xD6" " t" "\xF6"
#define		MSG_TONG_APPLY_ADD_ERROR6		"Bang h" "\xE9" "i " "\xAE" "\xB7" " " "\xAE" "\xE3" "ng ch" "\xF8" "c n" "\xA8" "ng chi" "\xAA" "u m" "\xE9" " " "\xAE" "\xD6" " t" "\xF6"
#define		MSG_TONG_APPLY_ADD_ERROR7		"Ng" "\xAD" "\xEA" "i n" "\xB5" "y v" "\xF5" "a r" "\xEA" "i kh" "\xE1" "i bang h" "\xE9" "i ch" "\xAD" "a th" "\xD3" " gia nh" "\xCB" "p b" "\xA9" "y gi" "\xEA"
#define		MSG_TONG_REFUSE_ADD				"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i %s t" "\xF5" " ch" "\xE8" "i l" "\xEA" "i m" "\xEA" "i gia nh" "\xCB" "p bang h" "\xE9" "i"
#define		MSG_TONG_ADD_SUCCESS			"B" "\xB9" "n " "\xAE" "\xB7" " gia nh" "\xCB" "p bang h" "\xE9" "i th" "\xB5" "nh c" "\xAB" "ng"
#define		MSG_TONG_CANNOT_LEAVE1			"Th" "\xB5" "nh vi" "\xAA" "n ch" "\xDD" "nh th" "\xF8" "c kh" "\xAB" "ng th" "\xD3" " r" "\xEA" "i kh" "\xE1" "i bang"
#define		MSG_TONG_CANNOT_LEAVE2			"Tr" "\xAD" "\xEB" "ng l" "\xB7" "o kh" "\xAB" "ng th" "\xD3" " r" "\xEA" "i kh" "\xE1" "i bang"
#define		MSG_TONG_BE_KICKED				"B" "\xB9" "n b" "\xDE" " tr" "\xF4" "c xu" "\xCA" "t ra kh" "\xE1" "i bang"
#define		MSG_TONG_KICK_ERROR1			"Thao t" "\xB8" "c phi ph" "\xB8" "p, b" "\xB9" "n kh" "\xAB" "ng thu" "\xE9" "c b" "\xCA" "t k" "\xFA" " bang h" "\xE9" "i n" "\xB5" "o"
#define		MSG_TONG_KICK_ERROR2			"Thao t" "\xB8" "c th" "\xCA" "t b" "\xB9" "i, ch" "\xAD" "c Tr" "\xAD" "\xEB" "ng l" "\xB7" "o tr" "\xEB" " l" "\xAA" "n m" "\xED" "i c" "\xE3" " th" "\xD3" " tr" "\xF4" "c xu" "\xCA" "t th" "\xB5" "nh vi" "\xAA" "n"
#define		MSG_TONG_KICK_ERROR3			"Tr" "\xAD" "\xEB" "ng l" "\xB7" "o kh" "\xAB" "ng th" "\xD3" " tr" "\xF4" "c xu" "\xCA" "t tr" "\xF9" "c ti" "\xD5" "p"
#define		MSG_TONG_LEAVE_SUCCESS			"B" "\xB9" "n " "\xAE" "\xB7" " r" "\xEA" "i kh" "\xE1" "i bang h" "\xE9" "i th" "\xB5" "nh c" "\xAB" "ng, c" "\xE3" " th" "\xD3" " xin gia nh" "\xCB" "p bang h" "\xE9" "i kh" "\xB8" "c sau %d ph" "\xF3" "t"
#define		MSG_TONG_LEAVE_FAIL				"R" "\xEA" "i kh" "\xE1" "i bang h" "\xE9" "i th" "\xCA" "t b" "\xB9" "i"
#define		MSG_TONG_NO_MONEY				"B" "\xB9" "n kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " ng" "\xA9" "n l" "\xAD" "\xEE" "ng kh" "\xAB" "ng th" "\xD3" " t" "\xF9" " " "\xFD" " r" "\xEA" "i kh" "\xE1" "i"
#define		MSG_TONG_CHANGE_AS_MASTER		"B" "\xB9" "n b" "\xA9" "y gi" "\xEA" " " "\xAE" "\xB6" "m nh" "\xCB" "n ch" "\xF8" "c v" "\xDE" " Bang ch" "\xF1"
#define		MSG_TONG_CHANGE_MASTER_ERROR1	"Chuy" "\xD3" "n v" "\xDE" " th" "\xCA" "t b" "\xB9" "i, " "\xAE" "\xE8" "i ph" "\xAD" "\xAC" "ng kh" "\xAB" "ng tr" "\xF9" "c tuy" "\xD5" "n!"
#define		MSG_TONG_CHANGE_MASTER_ERROR2	"Chuy" "\xD3" "n v" "\xDE" " th" "\xCA" "t b" "\xB9" "i, " "\xAE" "\xE8" "i ph" "\xAD" "\xAC" "ng n" "\xA8" "ng l" "\xF9" "c kh" "\xAB" "ng " "\xAE" "\xF1" "!"
#define		MSG_TONG_CHANGE_MASTER_ERROR3	"Chuy" "\xD3" "n v" "\xDE" " th" "\xCA" "t b" "\xB9" "i, trong bang kh" "\xAB" "ng c" "\xE3" " ng" "\xAD" "\xEA" "i n" "\xB5" "y!"
#define		MSG_TONG_CHANGE_AS_MEMBER		"B" "\xA9" "y gi" "\xEA" " b" "\xB9" "n tr" "\xEB" " th" "\xB5" "nh th" "\xB5" "nh vi" "\xAA" "n b" "\xD7" "nh th" "\xAD" "\xEA" "ng"
#define		MSG_TONG_CHANGE_AGNAME_ERROR1	"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i n" "\xB5" "y hi" "\xD6" "n kh" "\xAB" "ng tr" "\xF9" "c tuy" "\xD5" "n, thao t" "\xB8" "c th" "\xCA" "t b" "\xB9" "i"
#define		MSG_TONG_CHANGE_AGNAME_ERROR2	"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i n" "\xB5" "y kh" "\xAB" "ng " "\xAE" "\xF1" " t" "\xB5" "i l" "\xB7" "nh " "\xAE" "\xB9" "o, thao t" "\xB8" "c th" "\xCA" "t b" "\xB9" "i"
#define		MSG_TONG_CHANGE_AGNAME_ERROR3	"Ng" "\xAD" "\xEA" "i ch" "\xAC" "i n" "\xB5" "y kh" "\xAB" "ng t" "\xE5" "n t" "\xB9" "i, thao t" "\xB8" "c th" "\xCA" "t b" "\xB9" "i"
#define		MSG_TONG_CHANGE_CAMP			"Ti" "\xD5" "n h" "\xB5" "nh thay " "\xAE" "\xE6" "i phe ph" "\xB8" "i b" "\xE6" "n bang"
#define		MSG_TONG_CHANGE_CAMP_ERROR1		"Ch" "\xD8" " c" "\xE3" " bang ch" "\xF1" " m" "\xED" "i s" "\xF6" " d" "\xF4" "ng " "\xAE" "\xAD" "\xEE" "c ch" "\xF8" "c n" "\xA8" "ng n" "\xB5" "y"
#define		MSG_TONG_CHANGE_CAMP_ERROR2		"Vui l" "\xDF" "ng ch" "\xE4" "n phe ph" "\xB8" "i thay " "\xAE" "\xE6" "i " "\xAE" "\xD5" "n"
#define		MSG_TONG_CHANGE_CAMP_ERROR3		"Ng" "\xA9" "n kh" "\xE8" " kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " %d l" "\xAD" "\xEE" "ng, kh" "\xAB" "ng th" "\xD3" " thay " "\xAE" "\xE6" "i phe ph" "\xB8" "i b" "\xE6" "n bang"
#define		MSG_TONG_CHANGE_SAVEJIYU_ERROR	"Ng" "\xA9" "n kh" "\xE8" " kh" "\xAB" "ng c" "\xE3" " " "\xAE" "\xF1" " %d l" "\xAD" "\xEE" "ng, kh" "\xAB" "ng th" "\xD3" " b" "\xB6" "o l" "\xAD" "u"

#define		MSG_CANT_SIT_RIDE				"L" "\xF3" "c c" "\xAD" "\xEC" "i ng" "\xF9" "a kh" "\xAB" "ng th" "\xD3" " thi" "\xD2" "n t" "\xE4" "a"
#define		MSG_CANT_SWITCH_HORSE_SIT		"B" "\xB9" "n " "\xAE" "ang thi" "\xD2" "n t" "\xE4" "a kh" "\xAB" "ng th" "\xD3" " l" "\xAA" "n ng" "\xF9" "a"
#define		MSG_CANT_SWITCH_HORSE			"B" "\xB9" "n qu" "\xB8" " m" "\xD6" "t m" "\xE1" "i kh" "\xAB" "ng th" "\xD3" " li" "\xAA" "n t" "\xF4" "c l" "\xAA" "n ho" "\xC6" "c xu" "\xE8" "ng ng" "\xF9" "a"
#define		MSG_CANT_TRADE_BUZY				"Trong l" "\xF3" "c c" "\xEC" "i ng" "\xF9" "a ho" "\xC6" "c " "\xAE" "ang giao d" "\xDE" "ch v" "\xED" "i t" "\xE6" " " "\xAE" "\xE9" "i kh" "\xAB" "ng th" "\xD3" " b" "\xB5" "y b" "\xB8" "n!"

#define		MESSAGE_BROADCAST_ANNOUCE_HEAD	"C" "\xAB" "ng b" "\xE8"
#define		MESSAGE_SYSTEM_ANNOUCE_HEAD		"H" "\xD6" " th" "\xE8" "ng"
#define		MESSAGE_SYSTEM_ANNOUCE_SKILL	"H" "\xD6" " th" "\xE8" "ng k" "\xFC" " n" "\xA8" "ng"
#define		MESSAGE_SYSTEM_ANNOUCE_PROTECT	"H" "\xD6" " th" "\xE8" "ng b" "\xB6" "o m" "\xCB" "t"
#define		MESSAGE_TEAM_ANNOUCE_HEAD		"Tin " "\xAE" "\xE9" "i"
#define		MESSAGE_TONG_ANNOUCE_HEAD		"Tin bang"
#define		MESSAGE_ROOM_ANNOUCE_HEAD		"Tin ph" "\xDF" "ng"

#define		defTONG_VICEROY_AGNAME			"[Th" "\xB8" "i th" "\xF3" "]"
#define		defTONG_MASTER_AGNAME			"Bang ch" "\xF1"
#define		defTONG_DIRECTOR_AGNAME			"Tr" "\xAD" "\xEB" "ng l" "\xB7" "o"
#define		defTONG_MANAGER_AGNAME			"\xA7" "\xE9" "i tr" "\xAD" "\xEB" "ng"
#define		defTONG_MEMBER_AGNAME			"\xA7" "\xD6" " t" "\xF6"

#define		MSG_TRADE_COUNT					"B" "\xB9" "n ch" "\xAD" "a " "\xAE" "\xDE" "nh gi" "\xB8" " cho b" "\xCA" "t k" "\xFA" " v" "\xCB" "t ph" "\xC8" "m n" "\xB5" "o"
#define		MSG_TRADE_SELLED				"V" "\xCB" "t ph" "\xC8" "m n" "\xB5" "y " "\xAE" "\xB7" " " "\xAE" "\xAD" "\xEE" "c b" "\xB8" "n ra r" "\xE5" "i!"
#define		MSG_TRADE_CLOSED				"Ng" "\xAD" "\xEA" "i b" "\xB5" "y b" "\xB8" "n " "\xAE" "\xB7" " c" "\xCA" "t " "\xAE" "i r" "\xE5" "i"

#define		MSG_FIGHT_MODE_ERROR1			"Tr" "\xB9" "ng th" "\xB8" "i kh" "\xAB" "ng " "\xAE" "\xAD" "\xEE" "c b" "\xB6" "o v" "\xD6" " kh" "\xAB" "ng th" "\xD3" " th" "\xF9" "c hi" "\xD6" "n"
#define		MSG_FIGHT_MODE_ERROR2			"B" "\xB9" "n trong tr" "\xB9" "ng th" "\xB8" "i kh" "\xAB" "ng " "\xAE" "\xAD" "\xEE" "c b" "\xB6" "o v" "\xD6" " kh" "\xAB" "ng th" "\xD3" " th" "\xF9" "c hi" "\xD6" "n"
#define		MSG_FIGHT_MODE_ERROR3			"%s trong tr" "\xB9" "ng th" "\xB8" "i kh" "\xAB" "ng " "\xAE" "\xAD" "\xEE" "c b" "\xB6" "o v" "\xD6" " kh" "\xAB" "ng th" "\xD3" " th" "\xF9" "c hi" "\xD6" "n"

#define		MSG_SUBWORLD_NOT_OPEN			"\xA7" "\xAD" "\xEA" "ng " "\xAE" "i ph" "\xDD" "a tr" "\xAD" "\xED" "c kh" "\xAB" "ng th" "\xAB" "ng"

#define		MSG_PASSWORD_ERROR1				"M" "\xCB" "t kh" "\xC8" "u ph" "\xB6" "i c" "\xE3" " " "\xAE" "\xE9" " d" "\xB5" "i t" "\xF5" " 4 " "\xAE" "\xD5" "n 16 k" "\xF3" " t" "\xF9"
#define		MSG_PASSWORD_ERROR2				"M" "\xCB" "t kh" "\xC8" "u x" "\xB8" "c nh" "\xCB" "n kh" "\xAB" "ng tr" "\xEF" "ng kh" "\xED" "p. Xin m" "\xEA" "i nh" "\xCB" "p l" "\xB9" "i"
#define		MSG_PASSWORD_ERROR3				"M" "\xCB" "t kh" "\xC8" "u m" "\xED" "i nh" "\xCB" "p v" "\xB5" "o kh" "\xAB" "ng th" "\xD3" " tr" "\xEF" "ng v" "\xED" "i m" "\xCB" "t kh" "\xC8" "u hi" "\xD6" "n t" "\xB9" "i"

#define		MSG_FUNCTION_FOBIDDENED			"Xin l" "\xE7" "i, c" "\xAB" "ng n" "\xA8" "ng n" "\xB5" "y t" "\xB9" "m th" "\xEA" "i " "\xAE" "\xB7" " b" "\xDE" " " "\xAE" "\xE3" "ng!"
#define		MSG_FUNCTION_LOCKED				"Thao t" "\xB8" "c " "\xAE" "\xB7" " b" "\xDE" " kh" "\xE3" "a! vui l" "\xDF" "ng m" "\xEB" " kh" "\xE3" "a b" "\xB6" "o v" "\xD6" " tr" "\xAD" "\xED" "c khi th" "\xF9" "c hi" "\xD6" "n."


enum enumMSG_ID
{
	enumMSG_ID_NONE = 0,
	enumMSG_ID_TEAM_KICK_ONE,
	enumMSG_ID_TEAM_DISMISS,
	enumMSG_ID_TEAM_LEAVE,
	enumMSG_ID_TEAM_REFUSE_INVITE,
	enumMSG_ID_TEAM_APPLY_INVITE_FAIL,
	enumMSG_ID_TEAM_APPLY_INVITE_FAIL2,
	enumMSG_ID_TEAM_SELF_ADD,
	enumMSG_ID_TEAM_ADDMEMBER_NOTVALID,
	enumMSG_ID_TEAM_CHANGE_CAPTAIN_FAIL,
	enumMSG_ID_TEAM_CHANGE_CAPTAIN_FAIL2,
	enumMSG_ID_OBJ_CANNOT_PICKUP,
	enumMSG_ID_OBJ_TOO_FAR,
	enumMSG_ID_DEC_MONEY,
	enumMSG_ID_SPAR_VICTORY,
	enumMSG_ID_SPAR_DEFEAT,
	enumMSG_ID_TRADE_SELF_ROOM_FULL,
	enumMSG_ID_TRADE_DEST_ROOM_FULL,
	enumMSG_ID_TRADE_REFUSE_APPLY,
	enumMSG_ID_TRADEFOLKGAME_SELF_ROOM_FULL,
	enumMSG_ID_TRADEFOLKGAME_DEST_ROOM_FULL,
	enumMSG_ID_SPAR_REFUSE_APPLY,
	enumMSG_ID_GET_ITEM,
	enumMSG_ID_MONEY_CANNOT_PICKUP,
	enumMSG_ID_CANNOT_ADD_TEAM,
	enumMSG_ID_TEAM_IS_FULL,
	enumMSG_ID_CANNOT_INVITE_TEAM,
	enumMSG_ID_TARGET_CANNOT_ADD_TEAM,
	enumMSG_ID_GET_INVITE_TEAM_REPLY,
	enumMSG_ID_PK_NORMAL_NOT_OPEN,
	enumMSG_ID_PK_HIGHT_LOCK_NOT_SWITCH,
	enumMSG_ID_PKSTATE_NOT_OPEN,
	enumMSG_ID_PK_ERROR_1,
	enumMSG_ID_PK_ERROR_2,
	enumMSG_ID_PK_ERROR_3,
	enumMSG_ID_PK_ERROR_4,
	enumMSG_ID_PK_ERROR_5,
	enumMSG_ID_PK_ERROR_6,
	enumMSG_ID_PK_ERROR_7,
	enumMSG_ID_PK_ERROR_8,
	enumMSG_ID_PK_ERROR_9,
	enumMSG_ID_PK_IS_LOCK,
	enumMSG_ID_PK_IS_LOCK1,
	enumMSG_ID_PK_IS_LOCK2,
	enumMSG_ID_PK_IS_LOCK3,
	enumMSG_ID_PK_IS_LOCK4,
	enumMSG_ID_PK_IS_LOCK5,
	enumMSG_ID_PK_IS_LOCK6,
	enumMSG_ID_PK_IS_LOCK7,
	enumMSG_ID_TRADE_BUZY,
	enumMSG_ID_TRADE_SELLED,
	enumMSG_ID_TRADE_CLOSED,
	enumMSG_ID_DEATH_LOSE_ITEM,
	enumMSG_ID_TONG_REFUSE_ADD,
	enumMSG_ID_TONG_BE_KICK,
	enumMSG_ID_TONG_LEAVE_SUCCESS,
	enumMSG_ID_TONG_LEAVE_FAIL,
	enumMSG_ID_TONG_NO_MONEY,
	enumMSG_ID_TONG_CHANGE_AS_MASTER,
	enumMSG_ID_TONG_CHANGE_AS_MEMBER,
	enumMSG_ID_TONG_APPLY_ADD_ERROR,
	enumMSG_ID_TONG_APPLY_ADD_ERROR1,
	enumMSG_ID_TONG_APPLY_ADD_ERROR2,
	enumMSG_ID_TONG_APPLY_ADD_ERROR3,
	enumMSG_ID_TONG_APPLY_ADD_ERROR4,
	enumMSG_ID_TONG_APPLY_ADD_ERROR5,
	enumMSG_ID_TONG_APPLY_ADD_ERROR6,
	enumMSG_ID_TONG_APPLY_ADD_ERROR7,
	enumMSG_ID_FIGHT_MODE_ERROR1,
	enumMSG_ID_FIGHT_MODE_ERROR2,
	enumMSG_ID_FIGHT_MODE_ERROR3,
	enumMSG_ID_SHOP_NO_ROOM,
	enumMSG_ID_SHOP_NO_MONEY,
	enumMSG_ID_SHOP_NO_EXTPOINT,
	enumMSG_ID_SHOP_NO_FUYUAN,
	enumMSG_ID_SHOP_NO_REPUTE,
	enumMSG_ID_SHOP_NO_ACCUM,
	enumMSG_ID_SHOP_NO_HONOR,
	enumMSG_ID_SHOP_NO_RESPECT,
	enumMSG_ID_FUNCTION_CHAT_FORBIDDENED,
	enumMSG_ID_FUNCTION_FOBIDDENED,
	enumMSG_ID_FUNCTION_LOCKED,
	enumMSG_ID_LOCK_NOT_TRADE,
	enumMSG_ID_LOCK_NOT_SETPRICE,
	enumMSG_ID_LOCK_NOT_THROW,
	enumMSG_ID_ITEM_TOWNPORTAL,
	enumMSG_ID_ITEM_CANTREPAIR,
	enumMSG_ID_ITEM_SAME_IMMEDIATE,
	enumMSG_ID_ITEM_CANTPUT_IMMEDIATE,
	enumMSG_ID_HORSE_CANT_SWITCH1,
	enumMSG_ID_HORSE_CANT_SWITCH2,
	enumMSG_ID_CHATROOM_JOIN,
	enumMSG_ID_CHATROOM_LEAVE,
	enumMSG_ID_CHATROOM_BEKICK,
	enumMSG_ID_CHATROOM_OPENGAME,
	enumMSG_ID_CHATROOM_REVERSE,
	enumMSG_ID_NPC_RENASCENCE_SOMEONE,
	enumMSG_ID_NPC_RENASCENCE,
	enumMSG_ID_NUM,
};

//---------------------------- 鼠标指针相关 ------------------------------
#define		MOUSE_CURSOR_NORMAL				0
#define		MOUSE_CURSOR_FIGHT				1
#define		MOUSE_CURSOR_DIALOG				2
#define		MOUSE_CURSOR_PICK				3
#define		MOUSE_CURSOR_USE				8
#define		MOUSE_CURSOR_TRADE				11
#define		MOUSE_CURSOR_FINGER				12
#define		MOUSE_CURSOR_HELP				13
#endif
