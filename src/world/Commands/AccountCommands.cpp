/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"


bool ChatHandler::HandleAccountCreate(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;

    char account[100];
    char password[100];
    int argc = sscanf(args, "%s %s", account, password);
    if (argc != 2)
        return false;

    // get current account name to send back result later
    auto account_name = m_session->GetAccountNameS();

    sLogonCommHandler.AccountCreate(account, password, account_name);

    return true;
}

bool ChatHandler::HandleAccountSetGMCommand(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;

    char account[100];
    char gmlevel[100];
    int argc = sscanf(args, "%s %s", account, gmlevel);
    if (argc != 2)
        return false;

    // get current account name to send back result later
    auto account_name = m_session->GetAccountNameS();

    sLogonCommHandler.Account_CheckExist(account, account_name, gmlevel);

    return true;
}

bool ChatHandler::HandleAccountMuteCommand(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;

    char* pAccount = (char*)args;
    char* pDuration = strchr(pAccount, ' ');
    if (pDuration == NULL)
        return false;
    *pDuration = 0;
    ++pDuration;

    int32 timeperiod = GetTimePeriodFromString(pDuration);
    if (timeperiod <= 0)
        return false;

    uint32 banned = (uint32)UNIXTIME + timeperiod;

    sLogonCommHandler.Account_SetMute(pAccount, banned);

    std::string tsstr = ConvertTimeStampToDataTime(timeperiod + (uint32)UNIXTIME);
    GreenSystemMessage(m_session, "Account '%s' has been muted until %s. The change will be effective immediately.", pAccount,
                       tsstr.c_str());

    sGMLog.writefromsession(m_session, "mutex account %s until %s", pAccount, ConvertTimeStampToDataTime(timeperiod + (uint32)UNIXTIME).c_str());

    WorldSession* pSession = sWorld.FindSessionByName(pAccount);
    if (pSession != NULL)
    {
        pSession->m_muted = banned;
        pSession->SystemMessage("Your voice has been muted until %s by a GM. Until this time, you will not be able to speak in any form.", tsstr.c_str());
    }

    return true;
}

bool ChatHandler::HandleAccountUnmuteCommand(const char* args, WorldSession* m_session)
{
    sLogonCommHandler.Account_SetMute(args, 0);

    GreenSystemMessage(m_session, "Account '%s' has been unmuted.", args);
    sGMLog.writefromsession(m_session, "unmuted account %s", args);
    WorldSession* pSession = sWorld.FindSessionByName(args);
    if (pSession != NULL)
    {
        pSession->m_muted = 0;
        pSession->SystemMessage("Your voice has restored. You may speak again.");
    }

    return true;
}

void ParseAccBanArgs(char* args, char** BanDuration, char** BanReason)
{
    char* pBanDuration = strchr(args, ' ');
    char* pReason = NULL;
    if (pBanDuration != NULL)
    {
        if (isdigit(*(pBanDuration + 1)))       // this is the duration of the ban
        {
            *pBanDuration = 0;                  // NULL-terminate the first string (character/account/ip)
            ++pBanDuration;                     // point to next arg
            pReason = strchr(pBanDuration + 1, ' ');
            if (pReason != NULL)                // BanReason is OPTIONAL
            {
                *pReason = 0;                   // BanReason was given, so NULL-terminate the duration string
                ++pReason;                      // and point to the ban reason
            }
        }
        else                                    // no duration was given (didn't start with a digit) - so this arg must be ban reason and duration defaults to permanent
        {
            pReason = pBanDuration;
            pBanDuration = NULL;
            *pReason = 0;
            ++pReason;
        }
    }
    *BanDuration = pBanDuration;
    *BanReason = pReason;
}

bool ChatHandler::HandleAccountBannedCommand(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;
    char* pAccount = (char*)args;
    char* pReason;
    char* pDuration;
    ParseAccBanArgs(pAccount, &pDuration, &pReason);
    int32 timeperiod = 0;
    if (pDuration != NULL)
    {
        timeperiod = GetTimePeriodFromString(pDuration);
        if (timeperiod < 0)
            return false;
    }
    uint32 banned = (timeperiod ? (uint32)UNIXTIME + timeperiod : 1);

    char emptystring = 0;
    if (pReason == NULL)
        pReason = &emptystring;

    sLogonCommHandler.Account_SetBanned(pAccount, banned, pReason);

    GreenSystemMessage(m_session, "Account '%s' has been banned %s%s for reason : %s. The change will be effective immediately.", pAccount,
                       timeperiod ? "until " : "forever", timeperiod ? ConvertTimeStampToDataTime(timeperiod + (uint32)UNIXTIME).c_str() : "", pReason);

    sWorld.DisconnectUsersWithAccount(pAccount, m_session);
    sGMLog.writefromsession(m_session, "banned account %s until %s", pAccount, timeperiod ? ConvertTimeStampToDataTime(timeperiod + (uint32)UNIXTIME).c_str() : "permanent");
    return true;
}

bool ChatHandler::HandleAccountUnbanCommand(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;
    char* pAccount = (char*)args;

    sLogonCommHandler.Account_SetBanned(pAccount, 0, "");
    GreenSystemMessage(m_session, "Account '%s' has been unbanned. This change will be effective immediately.", pAccount);

    sGMLog.writefromsession(m_session, "unbanned account %s", pAccount);
    return true;
}

bool ChatHandler::HandleAccountChangePassword(const char* args, WorldSession* m_session)
{
    if (!*args)
        return false;

    char old_password[100];
    char new_password_1[100];
    char new_password_2[100];
    int argc = sscanf(args, "%s %s %s", old_password, new_password_1, new_password_2);
    if (argc != 3)
    {
        RedSystemMessage(m_session, "Please type in <old_password> <new_password> <new_password>");
        return false;
    }

    if (std::string(new_password_1) != std::string(new_password_2))
    {
        RedSystemMessage(m_session, "Your new password inputs doesn't match!");
        return false;
    }
    auto account_name = m_session->GetAccountNameS();

    sLogonCommHandler.AccountChangePassword(old_password, new_password_1, account_name);

    return true;
}
