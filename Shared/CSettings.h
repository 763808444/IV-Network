/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CSettings_h
#define CSettings_h

#include <map>
#include <list>
#include "Common.h"
#include "CString.h"
#include <tinyxml/tinyxml.h>
#include <tinyxml/ticpp.h>

// Set macros
#define CVAR_SET_BOOL CSettings::SetBool
#define CVAR_SET_INTEGER CSettings::SetInteger
#define CVAR_SET_FLOAT CSettings::SetFloat
#define CVAR_SET_STRING CSettings::SetString
#define CVAR_SET_LIST CSettings::AddToList
#define CVAR_SET_EX CSettings::SetEx

// Get macros
#define CVAR_GET_BOOL CSettings::GetBool
#define CVAR_GET_INTEGER CSettings::GetInteger
#define CVAR_GET_FLOAT CSettings::GetFloat
#define CVAR_GET_STRING CSettings::GetString
#define CVAR_GET_LIST CSettings::GetList
#define CVAR_GET_EX CSettings::GetEx

enum eSettingsFlags
{
	SETTINGS_FLAG_BOOL = 1,
	SETTINGS_FLAG_INTEGER = 2,
	SETTINGS_FLAG_FLOAT = 4,
	SETTINGS_FLAG_STRING = 8,
	SETTINGS_FLAG_LIST = 16
};

struct SettingsValue
{
	char              cFlags;
	bool              bValue;
	int               iValue;
	float             fValue;
	CString           strValue;
	std::list<CString>listValue;
	int               iMinimumValue;
	float             fMinimumValue;
	int               iMaximimValue;
	float             fMaximimValue;

	bool IsBool() { return IS_BIT_SET(cFlags, SETTINGS_FLAG_BOOL); }
	bool IsInteger() { return IS_BIT_SET(cFlags, SETTINGS_FLAG_INTEGER); }
	bool IsFloat() { return IS_BIT_SET(cFlags, SETTINGS_FLAG_FLOAT); }
	bool IsString() { return IS_BIT_SET(cFlags, SETTINGS_FLAG_STRING); }
	bool IsList() { return IS_BIT_SET(cFlags, SETTINGS_FLAG_LIST); }
};

class CSettings
{
private:
	static std::map<CString, SettingsValue *> m_values;
	static bool                              m_bOpen;
	static bool                              m_bSave;
	static TiXmlDocument                     m_XMLDocument;

	static void                                LoadDefaults(bool bClient = false);
	static SettingsValue                     * GetSetting(CString strSetting);

public:
	CSettings();
	~CSettings();

	static std::map<CString, SettingsValue *> * GetValues() { return &m_values; }
	static bool                                Open(CString strPath, bool bCreate = true, bool bSave = true, bool bClient = false);
	static bool                                Close();
	static bool                                Save();

	static bool                                AddBool(CString strSetting, bool bDefaultValue);
	static bool                                AddInteger(CString strSetting, int iDefaultValue, int iMinimumValue, int iMaximumValue);
	static bool                                AddFloat(CString strSetting, float fDefaultValue, float fMinimumValue, float fMaximumValue);
	static bool                                AddString(CString strSetting, CString strDefaultValue);
	static bool                                AddList(CString strSetting);

	static bool                                SetBool(CString strSetting, bool bValue);
	static bool                                SetInteger(CString strSetting, int iValue);
	static bool                                SetFloat(CString strSetting, float fValue);
	static bool                                SetString(CString strSetting, CString strValue);
	static bool                                AddToList(CString strSetting, CString strValue);
	static bool                                SetEx(CString strSetting, CString strValue);

	static bool                                GetBool(CString strSetting);
	static int                                 GetInteger(CString strSetting);
	static float                               GetFloat(CString strSetting);
	static CString                             GetString(CString strSetting);
	static std::list<CString>                  GetList(CString strSetting);
	static CString                             GetEx(CString strSetting);

	static bool                                Exists(CString strSetting);
	static bool                                IsBool(CString strSetting);
	static bool                                IsInteger(CString strSetting);
	static bool                                IsFloat(CString strSetting);
	static bool                                IsString(CString strSetting);
	static bool                                IsList(CString strSetting);

	static bool                                Remove(CString strSetting);

	static void                                ParseCommandLine(int argc, char ** argv);
	static void                                ParseCommandLine(char * szCommandLine);
};

#endif // CSettings_h