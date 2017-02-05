/*
* ArcEmu MMORPG Server
* Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
* Copyright (C) 2008 <http://www.ArcEmu.org/>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "StdAfx.h"

#ifdef GM_TICKET_MY_MASTER_COMPATIBLE

bool ChatHandler::HandleGMTicketListCommand(const char* args, WorldSession *m_session)
{
    Player *cplr = m_session->GetPlayer();

    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if (!chn)
        return false;

    SystemMessage(m_session, "GM Tickets List:");

    for (GmTicketList::iterator itr = objmgr.GM_TicketList.begin(); itr != objmgr.GM_TicketList.end(); itr++)
    {
        if ((*itr)->deleted)
            continue;

        Player* plr = objmgr.GetPlayer((uint32)(*itr)->playerGuid);

        if (plr == NULL)
            continue;

        //		Player* aplr = ((*itr)->assignedToPlayer == 0 ? NULL : objmgr.GetPlayer((uint32)(*itr)->assignedToPlayer));

        std::stringstream ss;

        uint32 zone = 0;
        if (plr->IsInWorld())
        {
            zone = plr->GetZoneId();
        }
        ss << "Name: " << (*itr)->name << ", Level: " << (*itr)->level << ", Zone: " << zone;
		SystemMessage(m_session, ss.str().c_str());
    }

    return true;
}

bool ChatHandler::HandleGMTicketGetByIdCommand(const char* args, WorldSession *m_session)
{
    if (!*args)
        return false;

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if (!chn)
        return false;

    Player *plr = objmgr.GetPlayer(args, false);
    if (plr == NULL)
    {
        RedSystemMessage(m_session, "Player not found.");
        return true;
    }
    GM_Ticket *ticket = objmgr.GetGMTicketByPlayer(plr->GetGUID());
    if (ticket == NULL || ticket->deleted)
    {
        RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    char* msg = new char[ticket->message.size() + 1];
    strcpy(msg, ticket->message.c_str());
    char * start = msg, *end;
    bool firstLine = true;
    for (;;)
    {
        end = strchr(start, '\n');
        if (!end)
            break;

        *end = '\0';

        std::stringstream ss;
        ss << ticket->name << ": " << start;
		SystemMessage(m_session, ss.str().c_str());

        firstLine = false;

        start = end + 1;
    }
    if (*start != '\0')
    {
        std::stringstream ss;
        ss << ticket->name << ": " << start;
		SystemMessage(m_session, ss.str().c_str());
    }
    delete[] msg;

    return true;
}

bool ChatHandler::HandleGMTicketRemoveByIdCommand(const char* args, WorldSession *m_session)
{
    if (!*args)
        return false;

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if (!chn)
        return false;

    Player *plr = objmgr.GetPlayer(args, true);
    if (plr == NULL)
    {
        RedSystemMessage(m_session, "Player not found.");
        return true;
    }
    GM_Ticket *ticket = objmgr.GetGMTicketByPlayer(plr->GetGUID());
    if (ticket == NULL || ticket->deleted)
    {
        RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    std::stringstream ss;
    ss << "Deleted Ticket for " << ticket->name;
	SystemMessage(m_session, ss.str().c_str());

    objmgr.RemoveGMTicket(ticket->guid);

    if (!plr)
        return true;
    if (!plr->IsInWorld())
        return true;

    // Notify player about removing ticket
    WorldPacket data(SMSG_GMTICKET_DELETETICKET, 4);
    data << uint32(9);
    plr->GetSession()->SendPacket(&data);

    return true;
}

#else

bool ChatHandler::HandleGMTicketListCommand(const char* args, WorldSession *m_session)
{
    Player *cplr = m_session->GetPlayer();

    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    std::stringstream ss0;
    ss0 << "TICKET LIST :" << GM_TICKET_CHAT_OPCODE_LISTSTART;
	SystemMessage(m_session, ss0.str().c_str());

    for(GmTicketList::iterator itr = objmgr.GM_TicketList.begin(); itr != objmgr.GM_TicketList.end(); itr++)
    {
        if((*itr)->deleted)
            continue;

        Player* plr = objmgr.GetPlayer((uint32)(*itr)->playerGuid);

        Player* aplr = NULL;
        PlayerInfo* aplri = NULL;
        if((*itr)->assignedToPlayer != 0)
        {
            aplr = objmgr.GetPlayer((uint32)(*itr)->assignedToPlayer);
            if(aplr == NULL)
                aplri = objmgr.GetPlayerInfo((uint32)(*itr)->assignedToPlayer);
        }

        std::stringstream ss;
        ss << "Ticket ID: " << (*itr)->guid;
		ss << " Name: " << (plr == NULL ? (*itr)->name : plr->GetName());
        ss << " Level: " << (plr == NULL ? (*itr)->level : plr->getLevel());
        ss << " Online: " << (plr == NULL ? 0 : plr->IsInWorld());
        ss << " Assigned: " << (aplr == NULL ? (aplri == NULL ? "None" : aplri->name) : aplr->GetName());
        ss << " Comments: " << (*itr)->comment;
		SystemMessage(m_session, ss.str().c_str());
    }

    return true;
}

bool ChatHandler::HandleGMTicketGetByIdCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid = (args ? atoi(args) : 0);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL || ticket->deleted)
    {
		SystemMessage(m_session, "Ticket not found.");
        return true;
    }

    char* msg = new char[ticket->message.size() + 1];
    strcpy(msg, ticket->message.c_str());
    char * start = msg, *end;
    bool firstLine = true;
    for(;;)
    {
        end = strchr(start, '\n');
        if(!end)
            break;

        *end = '\0';

        std::stringstream ss;
        //ss << ":" << ticket->guid;
        ss << "Message: " << start;
		SystemMessage(m_session, ss.str().c_str());

        firstLine = false;

        start = end + 1;
    }
    if(*start != '\0')
    {
        std::stringstream ss;
        //ss << "GmTicket:" << (firstLine ? GM_TICKET_CHAT_OPCODE_CONTENT : GM_TICKET_CHAT_OPCODE_APPENDCONTENT);
        //ss << ":" << ticket->guid;
        ss << "Message: " << start;
		SystemMessage(m_session, ss.str().c_str());
    }
    delete[] msg;

    return true;
}

bool ChatHandler::HandleGMTicketRemoveByIdCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid = (args ? atoi(args) : 0);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL || ticket->deleted)
    {
		SystemMessage(m_session, "Ticket not found.");
        return true;
    }

    if(ticket->assignedToPlayer != 0 && ticket->assignedToPlayer != cplr->GetGUID() && !cplr->GetSession()->CanUseCommand('z'))
    {
		SystemMessage(m_session, "Ticket is assigned to another GM.");
        return true;
    }

    Player* plr = objmgr.GetPlayer((uint32)ticket->playerGuid);

    std::stringstream ss;
    //ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_REMOVED;
    ss << "Deleted ticket ID:" << ticket->guid;
	SystemMessage(m_session, ss.str().c_str());

    objmgr.RemoveGMTicket(ticket->guid);

    if(!plr)
        return true;
    if(!plr->IsInWorld())
        return true;

    // Notify player about removing ticket
    WorldPacket data(SMSG_GMTICKET_DELETETICKET, 4);
    data << uint32(9);
    plr->GetSession()->SendPacket( &data );

    return true;
}

bool ChatHandler::HandleGMTicketAssignToCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid;
    char guidString[100], name[100];
    int argc = sscanf(args,"%s %s", guidString, name);
    if(argc < 1 || argc > 2)
        return false;

    ticketGuid = atoi(guidString);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL || ticket->deleted)
    {
		RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    Player *plr = (argc == 1 ? cplr : objmgr.GetPlayer(name, false));
    if(plr == NULL)
    {
		RedSystemMessage(m_session, "Player not found.");
        return true;
    }

    if(!plr->IsInWorld())
    {
		RedSystemMessage(m_session, "Player isn't online.");
        return true;
    }

    if(plr->GetSession()->GetPermissionCount() == 0)
    {
		RedSystemMessage(m_session, "Player is not a GM.");
        return true;
    }

    if(ticket->assignedToPlayer == plr->GetGUID())
    {
		RedSystemMessage(m_session, "Ticket already assigned to this GM.");
        return true;
    }

    if(ticket->assignedToPlayer != 0 && ticket->assignedToPlayer != cplr->GetGUID())
    {
        Player *aplr = objmgr.GetPlayer((uint32)ticket->assignedToPlayer);
        if(aplr != NULL && aplr->IsInWorld() && !cplr->GetSession()->CanUseCommand('z'))
        {
			RedSystemMessage(m_session, "Ticket already assigned to another GM.");
            return true;
        }
    }

    ticket->assignedToPlayer = plr->GetGUID();
    objmgr.UpdateGMTicket(ticket);

    std::stringstream ss;
    //ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_ASSIGNED;
    ss << "Ticket ID " << ticket->guid;
    ss << " assigned to " << plr->GetName();
	SystemMessage(m_session, ss.str().c_str());

    return true;
}

bool ChatHandler::HandleGMTicketReleaseCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid = (args ? atoi(args) : 0);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL || ticket->deleted)
    {
		RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    if(ticket->assignedToPlayer == 0)
    {
		RedSystemMessage(m_session, "Ticket not assigned to a GM.");
        return true;
    }

    Player *plr = objmgr.GetPlayer((uint32)ticket->assignedToPlayer);
    if(!cplr->GetSession()->CanUseCommand('z') && plr != NULL && plr->IsInWorld() && plr->GetSession()->CanUseCommand('z'))
    {
		RedSystemMessage(m_session, "You can not release tickets from admins.");
        return true;
    }

    ticket->assignedToPlayer = 0;
    objmgr.UpdateGMTicket(ticket);

    std::stringstream ss;
    //ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_RELEASED;
    ss << "Ticket " << ticket->guid << " released";
	SystemMessage(m_session, ss.str().c_str());

    return true;
}

bool ChatHandler::HandleGMTicketCommentCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid;
    int argc = 1;
    char* comment = NULL;
    char* guidString = (char*)args;

    // Parse arguments
    char* space = (char*)strchr(args, ' ');
    if(space)
    {	
        *space = '\0';
        comment = space + 1;
        argc = 2;
    }

    ticketGuid = atoi(guidString);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL || ticket->deleted)
    {
		RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    if(ticket->assignedToPlayer != 0 && ticket->assignedToPlayer != cplr->GetGUID() && !cplr->GetSession()->CanUseCommand('z'))
    {
		RedSystemMessage(m_session, "Ticket is assigned to another GM.");
        return true;
    }

    ticket->comment = (argc == 1 ? "" : comment);
    objmgr.UpdateGMTicket(ticket);

    std::stringstream ss;
    //ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_COMMENT;
    ss << "Ticket ID: " << ticket->guid;
    ss << " Commentor: " << cplr->GetName();
    ss << " Comments: " << ticket->comment;
	SystemMessage(m_session, ss.str().c_str());

    return true;
}

bool ChatHandler::HandleGMTicketDeletePermanentCommand(const char* args, WorldSession *m_session)
{
    uint64 ticketGuid = (args ? atoi(args) : 0);
    if(!ticketGuid)
    {
        RedSystemMessage(m_session, "You must specify a ticket id.");
        return true;
    }

    Player *cplr = m_session->GetPlayer();
    Channel *chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), cplr);
    if(!chn)
        return false;

    GM_Ticket *ticket = objmgr.GetGMTicket(ticketGuid);
    if(ticket == NULL)
    {
		RedSystemMessage(m_session, "Ticket not found.");
        return true;
    }

    Player* plr = NULL;

    if(!ticket->deleted)
    {
        plr = objmgr.GetPlayer((uint32)ticket->playerGuid);

        std::stringstream ss;
        //ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_REMOVED;
        ss << "Ticket " << ticket->guid << "DELETED";
        SystemMessage(m_session, ss.str().c_str());

        objmgr.RemoveGMTicket(ticket->guid);
    }

    objmgr.DeleteGMTicketPermanently(ticket->guid);
    ticket = NULL;

    if(plr != NULL && plr->IsInWorld())
    {
        // Notify player about removing ticket
        WorldPacket data(SMSG_GMTICKET_DELETETICKET, 4);
        data << uint32(9);
        plr->GetSession()->SendPacket( &data );
    }
    return true;
}

#endif

bool ChatHandler::HandleGMTicketToggleTicketSystemStatusCommand(const char* args, WorldSession *m_session)
{
    if (sWorld.toggleGMTicketStatus())
        GreenSystemMessage(m_session, "TicketSystem enabled.");
    else
        GreenSystemMessage(m_session, "TicketSystem disabled.");
    return true;
}

