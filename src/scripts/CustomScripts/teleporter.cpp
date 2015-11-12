#include "StdAfx.h"
#include "Setup.h"

/*#ifdef WIN32
    #pragma warning(disable:4305)// warning C4305: 'argument' : truncation from 'double' to 'float'
    #endif*/

class SCRIPT_DECL TeleNPC : public GossipScript
{
public:
    void Destroy()
    {
        delete this;
    }

    void GossipHello(Object* pObject, Player * Plr, bool AutoS)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);

        if (Plr->CombatStatus.IsInCombat() == true)
        {
            Plr->BroadcastMessage("Da du in einem Kampf verwickelt bist, darf ich dir nicht behilflich sein!");
            return;
        }

        if (Plr->GetItemInterface()->GetItemCount(98768, true) >= 1)  //VIP
            Menu->AddItem(3, "VIP Mall!", 950, 0);

        if (Plr->GetTeam() == 1)
        {
            Menu->AddItem(3, "Horde Cities", 1, 0);
        }
        else
        {
            Menu->AddItem(3, "Alliance Cities", 2, 0);
        }

        Menu->AddItem(3, "Eastern Kingdom Locations", 3, 0);
        Menu->AddItem(3, "Kalimdor Locations", 4, 0);
        Menu->AddItem(3, "Outland Locations", 5, 0);
        Menu->AddItem(3, "Azeroth Instances", 6, 0);
        Menu->AddItem(3, "Outland Instances", 7, 0);
        Menu->AddItem(1, "Shattrath(mall)", 420, 0);
        Menu->AddItem(4, "Remove Resurrection Sickness", 998, 0);
        Menu->AddItem(3, "Dueling Areas", 3, 0);

        if (AutoS)
            Menu->SendTo(Plr);
    }

    void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
        GossipMenu * Menu;
        switch (IntId)
        {
        case 1: //Horde Cities
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Horde Mall", 419, 0);
            Menu->AddItem(1, "Orgrimmar", 304, 0);
            Menu->AddItem(1, "Thunder Bluff", 305, 0);
            Menu->AddItem(1, "Undercity", 306, 0);
            Menu->AddItem(1, "Silvermoon", 307, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 2: // Alliance Cities
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Alliance Mall", 418, 0);
            Menu->AddItem(1, "Stormwind", 300, 0);
            Menu->AddItem(1, "Ironforge", 301, 0);
            Menu->AddItem(1, "Darnassus", 302, 0);
            Menu->AddItem(1, "Exodar", 303, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 3:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Alterac Mountains", 308, 0);
            Menu->AddItem(1, "Arathi Highlands", 309, 0);
            Menu->AddItem(1, "Badlands", 310, 0);
            Menu->AddItem(1, "Burning Steppes", 311, 0);
            Menu->AddItem(1, "Deadwind Pass", 312, 0);
            Menu->AddItem(1, "Dun Morogh", 313, 0);
            Menu->AddItem(1, "Duskwood", 314, 0);
            Menu->AddItem(1, "Eastern Plaguelands", 315, 0);
            Menu->AddItem(1, "Elwynn Forest", 316, 0);
            Menu->AddItem(1, "Eversong Woods", 317, 0);
            Menu->AddItem(1, "Ghostlands", 318, 0);
            Menu->AddItem(1, "Hillsbrad Foothills", 319, 0);
            Menu->AddItem(1, "Hinterlands", 320, 0);
            Menu->AddItem(1, "Loch Modan", 321, 0);
            Menu->AddItem(0, "--> Page 2 -->", 10, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 4:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Ashenvale", 331, 0);
            Menu->AddItem(1, "Azshara", 332, 0);
            Menu->AddItem(1, "Azuremyst Isle", 333, 0);
            Menu->AddItem(1, "Bloodmyst Isle", 334, 0);
            Menu->AddItem(1, "Darkshore", 335, 0);
            Menu->AddItem(1, "Durotar", 336, 0);
            Menu->AddItem(1, "Desolace", 337, 0);
            Menu->AddItem(1, "Dustwallow Marsh", 338, 0);
            Menu->AddItem(1, "Felwood", 339, 0);
            Menu->AddItem(1, "Feralas", 340, 0);
            Menu->AddItem(1, "Moonglade", 341, 0);
            Menu->AddItem(1, "Mulgore", 342, 0);
            Menu->AddItem(1, "Silithus", 343, 0);
            Menu->AddItem(1, "Stonetalon Mountains", 344, 0);
            Menu->AddItem(0, "--> Page 2 -->", 11, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 5:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Blade's Edge Mountains", 351, 0);
            Menu->AddItem(1, "Hellfire Peninsula", 352, 0);
            Menu->AddItem(1, "Nagrand", 353, 0);
            Menu->AddItem(1, "Netherstorm", 354, 0);
            Menu->AddItem(1, "Shadowmoon Valley", 355, 0);
            Menu->AddItem(1, "Terokkar Forest", 356, 0);
            Menu->AddItem(1, "Zangarmarsh", 357, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 6:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Ahn'Qiraj", 358, 0);
            Menu->AddItem(1, "Blackfathom Depths", 359, 0);
            Menu->AddItem(1, "Blackrock Depths", 360, 0);
            Menu->AddItem(1, "Blackrock Spire", 361, 0);
            Menu->AddItem(1, "Blackwing Lair", 362, 0);
            Menu->AddItem(1, "Caverns of Time", 363, 0);
            Menu->AddItem(1, "Deadmines", 364, 0);
            Menu->AddItem(1, "Dire Maul", 365, 0);
            Menu->AddItem(1, "Gnomeregan", 366, 0);
            Menu->AddItem(1, "Maraudon", 367, 0);
            Menu->AddItem(1, "Molten Core", 368, 0);
            Menu->AddItem(1, "Onyxia's Lair", 369, 0);
            Menu->AddItem(1, "Ragefire Chasm", 370, 0);
            Menu->AddItem(0, "--> Page 2 -->", 12, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 7:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(0, "Outland Raids", 13, 0);
            Menu->AddItem(1, "Auchenai Crypts", 383, 0);
            Menu->AddItem(1, "Coilfang Reservoir", 385, 0);
            Menu->AddItem(1, "Hellfire Ramparts", 387, 0);
            Menu->AddItem(1, "Mana Tombs", 388, 0);
            Menu->AddItem(1, "Pheonix Hall", 389, 0);
            Menu->AddItem(1, "Sethekk Halls", 390, 0);
            Menu->AddItem(1, "Shadow Labyrinth", 391, 0);
            Menu->AddItem(1, "The Blood Furnace", 423, 0);
            Menu->AddItem(1, "The Botanica", 392, 0);
            Menu->AddItem(1, "The Mechanar", 393, 0);
            Menu->AddItem(1, "The Shattered Halls", 425, 0);
            Menu->AddItem(1, "The Slave Pens", 426, 0);
            Menu->AddItem(1, "The Steamvault", 427, 0);
            Menu->AddItem(1, "The Underbog", 428, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 8:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "WinterSpring", 403, 0);
            Menu->SendTo(Plr);
            break;
        case 9:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Azjol'Nerub", 406, 0);
            Menu->AddItem(1, "Drak'Tharon", 407, 0);
            Menu->AddItem(1, "Gun'Drak", 408, 0);
            Menu->AddItem(1, "Icecrown Citadel", 409, 0);
            Menu->AddItem(1, "Naxxaramas", 410, 0);
            Menu->AddItem(1, "Obsidian Sanctum", 411, 0);
            Menu->AddItem(1, "The Nexus/Occulus/Eye of Eternity", 412, 0);
            Menu->AddItem(1, "Halls of Stone/Halls of Lightning", 413, 0);
            Menu->AddItem(1, "Utgarde Keep", 414, 0);
            Menu->AddItem(1, "Utgarde Pinnacle", 415, 0);
            Menu->AddItem(1, "Vault of Archevon", 416, 0);
            Menu->AddItem(1, "Violet Hold", 417, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 10:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Searing Gorge", 322, 0);
            Menu->AddItem(1, "Silverpine Forest", 323, 0);
            Menu->AddItem(1, "Stranglethorn Vale", 324, 0);
            Menu->AddItem(1, "Swamp of Sorrows", 325, 0);
            Menu->AddItem(1, "The Blasted Lands", 326, 0);
            Menu->AddItem(1, "Trisfal Glades", 327, 0);
            Menu->AddItem(1, "Western Plaguelands", 328, 0);
            Menu->AddItem(1, "Westfall", 329, 0);
            Menu->AddItem(1, "Wetlands", 330, 0);
            Menu->AddItem(0, "<-- Page 1 <--", 3, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 11:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Tanaris", 345, 0);
            Menu->AddItem(1, "Teldrassil", 346, 0);
            Menu->AddItem(1, "The Barrens", 347, 0);
            Menu->AddItem(1, "Thousand Needles", 348, 0);
            Menu->AddItem(1, "Un Goro Crater", 349, 0);
            Menu->AddItem(1, "Winterspring", 350, 0);
            Menu->AddItem(0, "<-- Page 1 <--", 4, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 12:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Razorfen Downs", 371, 0);
            Menu->AddItem(1, "Razorfen Kraul", 372, 0);
            Menu->AddItem(1, "Scarlet Monestary", 373, 0);
            Menu->AddItem(1, "Scholomance", 374, 0);
            Menu->AddItem(1, "Shadowfang Keep", 375, 0);
            Menu->AddItem(1, "Stratholme", 376, 0);
            Menu->AddItem(1, "Sunken Temple", 377, 0);
            Menu->AddItem(1, "Uldaman", 378, 0);
            Menu->AddItem(1, "Wailing Caverns", 379, 0);
            Menu->AddItem(1, "Zul'Aman", 380, 0);
            Menu->AddItem(1, "Zul'Farrak", 381, 0);
            Menu->AddItem(1, "Zul'Gurub", 382, 0);
            Menu->AddItem(0, "<-- Page 1 <--", 6, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 13:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(1, "Magtheridon's Lair", 421, 0);
            Menu->AddItem(1, "Sepentshrine Cavern", 422, 0);
            Menu->AddItem(1, "Gruul's Lair", 386, 0);
            Menu->AddItem(1, "The Eye", 424, 0);
            Menu->AddItem(1, "Black Temple", 384, 0);
            Menu->AddItem(0, "[Back]", 999, 0);
            Menu->SendTo(Plr);
            break;
        case 950:
            Plr->EventTeleport(169, -247.572571f, 2916.743896f, 98.119423f);
            Plr->Gossip_Complete();
            break;
        case 998:
            if (Plr->HasAura(15007) == true)
            {
                Plr->RemoveAura(15007);
                Plr->BroadcastMessage("You have been cured of Resurrection Sickness!");
                Plr->Gossip_Complete();
            }
            else
            {
                Plr->BroadcastMessage("You do not currently have Resurrection Sickness!");
                Plr->Gossip_Complete();
            }
            break;
        case 999:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);

            if (Plr->GetItemInterface()->GetItemCount(98768, true) >= 1)  //VIP 
                Menu->AddItem(3, "VIP Mall!", 950, 0);

            if (Plr->GetTeam() == 1)
            {
                Menu->AddItem(3, "Horde Cities", 1, 0);
            }
            else
            {
                Menu->AddItem(3, "Alliance Cities", 2, 0);
            }

            Menu->AddItem(3, "Eastern Kingdom Locations", 3, 0);
            Menu->AddItem(3, "Kalimdor Locations", 4, 0);
            Menu->AddItem(3, "Outland Locations", 5, 0);
            Menu->AddItem(3, "Azeroth Instances", 6, 0);
            Menu->AddItem(3, "Outland Instances", 7, 0);
            Menu->AddItem(1, "Shattrath(mall)", 420, 0);
            Menu->AddItem(4, "Remove Resurrection Sickness", 998, 0);
            Menu->AddItem(3, "Dueling Areas", 3, 0);
            Menu->SendTo(Plr);
            break;
        case 300:  // Stormwind
            Plr->EventTeleport(0, -8928.0f, 540.0f, 95.0f);
            Plr->Gossip_Complete();
            break;
        case 301:  // Ironforge
            Plr->EventTeleport(0, -4981.0f, -881.0f, 502.0f);
            Plr->Gossip_Complete();
            break;
        case 302:  // Darnassus
            Plr->EventTeleport(1, 9978.0f, 2033.0f, 1328.5f);
            Plr->Gossip_Complete();
            break;
        case 303:  // Exodar
            Plr->EventTeleport(530, -4014.0f, -11895.0f, -1.5f);
            Plr->Gossip_Complete();
            break;
        case 304:  // Orgrimmar
            Plr->EventTeleport(1, 1502.0f, -4415.0f, 22.0f);
            Plr->Gossip_Complete();
            break;
        case 305:  // Thunder Bluff
            Plr->EventTeleport(1, -1283.0f, 158.0f, 130.0f);
            Plr->Gossip_Complete();
            break;
        case 306:  // Undercity
            Plr->EventTeleport(0, 1752.0f, 239.0f, 61.5f);
            Plr->Gossip_Complete();
            break;
        case 307:  // Silvermoon
            Plr->EventTeleport(530.0f, 9392.0f, -7277, 14.5f);
            Plr->Gossip_Complete();
            break;
        case 308:  // Alterac Mountains
            Plr->EventTeleport(0, 237.0f, -652.0f, 119.0f);
            Plr->Gossip_Complete();
            break;
        case 309:  // Arathi Highlands
            Plr->EventTeleport(0, -1550.0f, -2495.0f, 55.0f);
            Plr->Gossip_Complete();
            break;
        case 310:  // Badlands
            Plr->EventTeleport(0, -6775.0f, -3286.0f, 242.0f);
            Plr->Gossip_Complete();
            break;
        case 311:  // Burning Steppes
            Plr->EventTeleport(0, -7975.0f, -1786.0f, 133.5f);
            Plr->Gossip_Complete();
            break;
        case 312:  // Deadwind Pass
            Plr->EventTeleport(0, -10447.0f, -1872.0f, 105.0f);
            Plr->Gossip_Complete();
            break;
        case 313:  // Dun Morogh
            Plr->EventTeleport(0, -5709.0f, -1339.0f, 395.0f);
            Plr->Gossip_Complete();
            break;
        case 314:  // Duskwood
            Plr->EventTeleport(0, -10914.0f, -528.0f, 54.0f);
            Plr->Gossip_Complete();
            break;
        case 315:  // Eastern Plaguelands
            Plr->EventTeleport(0, 1739.0f, -3623.0f, 120.0f);
            Plr->Gossip_Complete();
            break;
        case 316:  // Elwynn Forest
            Plr->EventTeleport(0, -9591.0f, -463.0f, 58.0f);
            Plr->Gossip_Complete();
            break;
        case 317:  // Eversong Woods
            Plr->EventTeleport(530, 8250.0f, -7214.0f, 140.0f);
            Plr->Gossip_Complete();
            break;
        case 318:  // Ghostlands
            Plr->EventTeleport(530, 6396.0f, -6848.0f, 101.0f);
            Plr->Gossip_Complete();
            break;
        case 319:  // Hillsbrad Foothills
            Plr->EventTeleport(0, -440.0f, -582.0f, 54.0f);
            Plr->Gossip_Complete();
            break;
        case 320:  // Hinterlands
            Plr->EventTeleport(0, 235.0f, -3298.0f, 110.0f);
            Plr->Gossip_Complete();
            break;
        case 321:  // Loch Modan
            Plr->EventTeleport(0, -5853.0f, -3251.0f, 303.0f);
            Plr->Gossip_Complete();
            break;
        case 322:  // Searing Gorge
            Plr->EventTeleport(0, -6645.0f, -1918.0f, 245.0f);
            Plr->Gossip_Complete();
            break;
        case 323:  // Silverpine Forest
            Plr->EventTeleport(0, 628.0f, 1291.0f, 87.0f);
            Plr->Gossip_Complete();
            break;
        case 324:  // Stranglethorn Vale
            Plr->EventTeleport(0, -14246.0f, 301.0f, 28.0f);
            Plr->Gossip_Complete();
            break;
        case 325:  // Swamp of Sorrows
            Plr->EventTeleport(0, -10476.0f, -2408.0f, 74.0f);
            Plr->Gossip_Complete();
            break;
        case 326:  // The Blasted Lands
            Plr->EventTeleport(0, -11189.0f, -3023.0f, 8.0f);
            Plr->Gossip_Complete();
            break;
        case 327:  // Tirisfal Glades
            Plr->EventTeleport(0, 1599.0f, 569.0f, 38.0f);
            Plr->Gossip_Complete();
            break;
        case 328:  // Western Plaguelands
            Plr->EventTeleport(0, 1676.0f, -1366.0f, 70.0f);
            Plr->Gossip_Complete();
            break;
        case 329:  // Westfall
            Plr->EventTeleport(0, -10922.0f, 998.0f, 36.0f);
            Plr->Gossip_Complete();
            break;
        case 330:  // Wetlands
            Plr->EventTeleport(0, -3604.0f, -2711.0f, 20.0f);
            Plr->Gossip_Complete();
            break;
        case 331:  // Ashenvale
            Plr->EventTeleport(1, 2319.0f, -1672.0f, 124.0f);
            Plr->Gossip_Complete();
            break;
        case 332:  // Azshara
            Plr->EventTeleport(1, 3336.0f, -4599.0f, 93.0f);
            Plr->Gossip_Complete();
            break;
        case 333:  // Azuremyst Isle
            Plr->EventTeleport(530, -4540.0f, -11933.0f, 28.0f);
            Plr->Gossip_Complete();
            break;
        case 334:  // Bloodmyst Isle
            Plr->EventTeleport(530, -2721.0f, -12206.0f, 10.0f);
            Plr->Gossip_Complete();
            break;
        case 335:  // Darkshore
            Plr->EventTeleport(1, 5084.0f, 242.0f, 29.0f);
            Plr->Gossip_Complete();
            break;
        case 336:  // Desolace
            Plr->EventTeleport(1, 301.0f, -4184.0f, 28.0f);
            Plr->Gossip_Complete();
            break;
        case 337:  // Durotar
            Plr->EventTeleport(1, -548.0f, 1276.0f, 90.0f);
            Plr->Gossip_Complete();
            break;
        case 338:  // Dustwallow Marsh
            Plr->EventTeleport(1, -3345.0f, -3078.0f, 33.0f);
            Plr->Gossip_Complete();
            break;
        case 339:  // Felwood
            Plr->EventTeleport(1, 5537.0f, -585.0f, 359.0f);
            Plr->Gossip_Complete();
            break;
        case 340:  // Feralas
            Plr->EventTeleport(1, -4811.0f, 1037.0f, 105.0f);
            Plr->Gossip_Complete();
            break;
        case 341:  // Moonglade
            Plr->EventTeleport(1, 7931.0f, -2616.0f, 493.0f);
            Plr->Gossip_Complete();
            break;
        case 342:  // Mulgore
            Plr->EventTeleport(1, -2372.0f, -893.0f, -9.0f);
            Plr->Gossip_Complete();
            break;
        case 343:  // Silithus
            Plr->EventTeleport(1, -6839.0f, 763.0f, 43.0f);
            Plr->Gossip_Complete();
            break;
        case 344:  // Stonetalon Mountains
            Plr->EventTeleport(1, 588.0f, 330.0f, 48.0f);
            Plr->Gossip_Complete();
            break;
        case 345:  // Tanaris
            Plr->EventTeleport(1, -7149.0f, -3746.0f, 9.0f);
            Plr->Gossip_Complete();
            break;
        case 346:  // Teldrassil
            Plr->EventTeleport(1, 9947.0f, 649.0f, 1310.0f);
            Plr->Gossip_Complete();
            break;
        case 347:  // The Barrens
            Plr->EventTeleport(1, 567.0f, -2573.0f, 96.0f);
            Plr->Gossip_Complete();
            break;
        case 348:  // Thousand Needles
            Plr->EventTeleport(1, -4969.0f, -1723.0f, -61.0f);
            Plr->Gossip_Complete();
            break;
        case 349:  // Un Goro Crater
            Plr->EventTeleport(1, -7932.0f, -2139.0f, -230.0f);
            Plr->Gossip_Complete();
            break;
        case 350:  // Winterspring
            Plr->EventTeleport(1, 6719.0f, -4646.0f, 722.0f);
            Plr->Gossip_Complete();
            break;
        case 351:  // Blade's Edge Mountains
            Plr->EventTeleport(530, 2924.0f, 5982.0f, 1.0f);
            Plr->Gossip_Complete();
            break;
        case 352:  // Hellfire Peninsula
            Plr->EventTeleport(530, -312.657562f, 3030.401855f, -15.506211f);
            Plr->Gossip_Complete();
            break;
        case 353:  // Nagrand
            Plr->EventTeleport(530, -1525.0f, 6571.0f, 21.0f);
            Plr->Gossip_Complete();
            break;
        case 354:  // Netherstorm
            Plr->EventTeleport(530, 3052.0f, 3670.0f, 143.0f);
            Plr->Gossip_Complete();
            break;
        case 355:  // Shadowmoon Valley
            Plr->EventTeleport(530, -3693.0f, 2344.0f, 77.0f);
            Plr->Gossip_Complete();
            break;
        case 356:  // Terokkar Forest
            Plr->EventTeleport(530, -1975.0f, 4516.0f, 13.0f);
            Plr->Gossip_Complete();
            break;
        case 357:  // Zangarmarsh
            Plr->EventTeleport(530, -205.0f, 5545.0f, 24.0f);
            Plr->Gossip_Complete();
            break;
        case 358:  // Ahn'Qiraj
            Plr->EventTeleport(1, -8187.0f, 1539.0f, 5.0f);
            Plr->Gossip_Complete();
            break;
        case 359:  // Blackfathom Depths
            Plr->EventTeleport(1, 4225.5f, 736.2f, -26.1f);
            Plr->Gossip_Complete();
            break;
        case 360:  // Blackrock Depths
            Plr->EventTeleport(0, -7187.0f, -914.0f, 166.0f);
            Plr->Gossip_Complete();
            break;
        case 361:  // Blackrock Spire
            Plr->EventTeleport(0, -7532.0f, -1221.0f, 286.0f);
            Plr->Gossip_Complete();
            break;
        case 362:  // Blackwing Lair
            Plr->EventTeleport(229, 137.0f, -474.0f, 117.0f);
            Plr->Gossip_Complete();
            break;
        case 363:  // Caverns of Time
            Plr->EventTeleport(1, -8568.0f, -4260.0f, -213.0f);
            Plr->Gossip_Complete();
            break;
        case 364:  // Deadmines
            Plr->EventTeleport(0, -11207.7f, 1668.0f, 24.6f);
            Plr->Gossip_Complete();
            break;
        case 365:  // Dire Maul
            Plr->EventTeleport(1, -3524.0f, 1124.0f, 162.0f);
            Plr->Gossip_Complete();
            break;
        case 366:  // Gnomeregan
            Plr->EventTeleport(0, -5164.0f, 918.0f, 258.0f);
            Plr->Gossip_Complete();
            break;
        case 367:  // Maraudon
            Plr->EventTeleport(1, -1458.0f, 2606.0f, 76.0f);
            Plr->Gossip_Complete();
            break;
        case 368:  // Molten Core
            Plr->EventTeleport(230, 1123.0f, -455.0f, -101.0f);
            Plr->Gossip_Complete();
            break;
        case 369:  // Onyxia's Lair
            Plr->EventTeleport(1, -4709.0f, -3729.0f, 55.0f);
            Plr->Gossip_Complete();
            break;
        case 370:  // Ragefire Chasm
            Plr->EventTeleport(1, 1805.0f, -4404.0f, -18.0f);
            Plr->Gossip_Complete();
            break;
        case 371:  // Razorfen Downs
            Plr->EventTeleport(1, -4661.0f, -2511.0f, 81.0f);
            Plr->Gossip_Complete();
            break;
        case 372:  // Razorfen Kraul
            Plr->EventTeleport(1, -4473.0f, -1690.0f, 82.0f);
            Plr->Gossip_Complete();
            break;
        case 373:  // Scarlet Monestary
            Plr->EventTeleport(0, 2841.0f, -692.0f, 140.0f);
            Plr->Gossip_Complete();
            break;
        case 374:  // Scholomance
            Plr->EventTeleport(0, 1265.0f, -2560.0f, 95.0f);
            Plr->Gossip_Complete();
            break;
        case 375:  // Shadowfang Keep
            Plr->EventTeleport(0, -241.0f, 1545.0f, 77.0f);
            Plr->Gossip_Complete();
            break;
        case 376:  // Stratholme
            Plr->EventTeleport(0, 3345.0f, -3380.0f, 145.0f);
            Plr->Gossip_Complete();
            break;
        case 377:  // Sunken Temple
            Plr->EventTeleport(0, -10457.0f, -3828.0f, 19.0f);
            Plr->Gossip_Complete();
            break;
        case 378:  // Uldaman
            Plr->EventTeleport(0, -6076.05f, -2957.7f, 207.0f);
            Plr->Gossip_Complete();
            break;
        case 379:  // Wailing Caverns
            Plr->EventTeleport(1, -737.0f, -2219.0f, 17.0f);
            Plr->Gossip_Complete();
            break;
        case 380:  // Zul'Aman
            Plr->EventTeleport(530, 6850.0f, -7950.0f, 171.0f);
            Plr->Gossip_Complete();
            break;
        case 381:  // Zul'Farrak
            Plr->EventTeleport(1, -6821.0f, -2890.0f, 9.0f);
            Plr->Gossip_Complete();
            break;
        case 382:  // Zul'Gurub
            Plr->EventTeleport(0, -11916.0f, -1204.0f, 93.0f);
            Plr->Gossip_Complete();
            break;
        case 383:  // Auchenai Crypts
            Plr->EventTeleport(530, -3359.8f, 5221.0f, -101.0f);
            Plr->Gossip_Complete();
            break;
        case 384:  // Black Temple
            Plr->EventTeleport(530, -3614.0f, 310.0f, 40.0f);
            Plr->Gossip_Complete();
            break;
        case 385:  // Coilfang Reservoir
            Plr->EventTeleport(530, 740.1f, 6868.0f, -68.0f);
            Plr->Gossip_Complete();
            break;
        case 386:  // Gruul's Lair
            Plr->EventTeleport(530, 3529.0f, 5096.0f, 3.0f);
            Plr->Gossip_Complete();
            break;
        case 387:  // Hellfire Ramparts
            Plr->EventTeleport(530, -172.0f, 3020.0f, -3.2f);
            Plr->Gossip_Complete();
            break;
        case 388:  // Mana Tombs
            Plr->EventTeleport(530, -3081.4f, 4945.6f, -101.0f);
            Plr->Gossip_Complete();
            break;
        case 389:  // Pheonix Hall
            Plr->EventTeleport(530, 3084.0f, 1385.0f, 185.0f);
            Plr->Gossip_Complete();
            break;
        case 390:  // Sethekk Halls
            Plr->EventTeleport(530, -3364.0f, 4675.0f, 101.0f);
            Plr->Gossip_Complete();
            break;
        case 391:  // Shadow Labyrinth
            Plr->EventTeleport(530, -3640.0f, 4941.0f, -101.0f);
            Plr->Gossip_Complete();
            break;
        case 392:  // The Botanica
            Plr->EventTeleport(530, 3404.0f, 1488.0f, 183.0f);
            Plr->Gossip_Complete();
            break;
        case 393:  // The Mechanar
            Plr->EventTeleport(530, 2870.0f, 1557.0f, 252.0f);
            Plr->Gossip_Complete();
            break;
        case 394:  // Borean Tundra
            Plr->EventTeleport(571, 3008.0f, 5290.0f, 60.0f);
            Plr->Gossip_Complete();
            break;
        case 395:  // Dragonblight
            Plr->EventTeleport(571, 3118.0f, 107.0f, 72.0f);
            Plr->Gossip_Complete();
            break;
        case 396:  // Grizzly Hills
            Plr->EventTeleport(571, 3681.0f, -3472.0f, 243.0f);
            Plr->Gossip_Complete();
            break;
        case 397:  // Howling Fjord
            Plr->EventTeleport(571, 1267.0f, -4062.0f, 143.0f);
            Plr->Gossip_Complete();
            break;
        case 398:  // Icecrown
            Plr->EventTeleport(571, 7514.0f, 2091.0f, 623.0f);
            Plr->Gossip_Complete();
            break;
        case 399:  // Sholazar Basin
            Plr->EventTeleport(571, 5501.0f, 4879.0f, 198.0f);
            Plr->Gossip_Complete();
            break;
        case 400:  // Storm Peaks
            Plr->EventTeleport(571, 7514.0f, -1037.0f, 467.0f);
            Plr->Gossip_Complete();
            break;
        case 401:  // Wintergrasp
            Plr->EventTeleport(571, 4611.0f, 2848.0f, 3397.0f);
            Plr->Gossip_Complete();
            break;
        case 402:  // Zul'Drak
            Plr->EventTeleport(571, 5441.0f, -2304.0f, 298.0f);
            Plr->Gossip_Complete();
            break;
        case 403:  // Dalaran
            Plr->EventTeleport(571, 5797.0f, 629.0f, 648.0f);
            Plr->Gossip_Complete();
            break;
        case 404:  // Crystalsong Forest
            Plr->EventTeleport(571, 5402.0f, 72.0f, 151.0f);
            Plr->Gossip_Complete();
            break;
        case 405:  // DK Start Zone
            Plr->EventTeleport(609, 2353.0f, -5666.0f, 427.0f);
            Plr->Gossip_Complete();
            break;
        case 406:  // Azjol'Nerub
            Plr->EventTeleport(571, 3721.0f, 2155.0f, 37.0f);
            Plr->Gossip_Complete();
            break;
        case 407:  // Drak'Tharon
            Plr->EventTeleport(571, 4897.0f, 2046.0f, 249.0f);
            Plr->Gossip_Complete();
            break;
        case 408:  // Gun'Drak
            Plr->EventTeleport(571, 6925.0f, 4447.0f, 451.0f);
            Plr->Gossip_Complete();
            break;
        case 409:  // Icecrown Citadel
            Plr->EventTeleport(571, 6151.0f, 2244.0f, 508.0f);
            Plr->Gossip_Complete();
            break;
        case 410:  // Naxxaramas
            Plr->EventTeleport(571, 3668.0f, -1049.0f, 131.0f);
            Plr->Gossip_Complete();
            break;
        case 411:  // Obsidian Sanctum
            Plr->EventTeleport(571, 3561.0f, 275.0f, 115.0f);
            Plr->Gossip_Complete();
            break;
        case 412:  // The Nexus/Occulus/Eye of Eternity
            Plr->EventTeleport(571, 3783.0f, 6942.0f, 105.0f);
            Plr->Gossip_Complete();
            break;
        case 413:  // Halls of Stone/Halls of Lightning
            Plr->EventTeleport(571, 8937.0f, 1266.0f, 1026.0f);
            Plr->Gossip_Complete();
            break;
        case 414:  // Utgarde Keep
            Plr->EventTeleport(571, 1228.0f, -4943.0f, 36.0f);
            Plr->Gossip_Complete();
            break;
        case 415:  // Utgarde Pinnacle
            Plr->EventTeleport(571, 1274.0f, -4857.0f, 216.0f);
            Plr->Gossip_Complete();
            break;
        case 416:  // Vault of Archevon
            Plr->EventTeleport(571, 5440.0f, 2840.0f, 421.0f);
            Plr->Gossip_Complete();
            break;
        case 417:  // Violet Hold
            Plr->EventTeleport(571, 5708.0f, 521.0f, 650.0f);
            Plr->Gossip_Complete();
            break;
        case 418:  // Alliance Mall
            Plr->EventTeleport(530, 53.706242f, -1503.903809f, 12.486f);
            Plr->Gossip_Complete();
            break;
        case 419:  // Horde Mall
            Plr->EventTeleport(530, 53.706242f, -1503.903809f, 12.486f);
            Plr->Gossip_Complete();
            break;
        case 420:  // shattrath
            Plr->EventTeleport(530, -1887.510010f, 5359.379883f, -12.427300f);
            Plr->Gossip_Complete();
            break;
        case 421:  // Magtheridon's Lair
            Plr->EventTeleport(530, -313.0f, 3088.0f, -116.0f);
            Plr->Gossip_Complete();
            break;
        case 422:  // Serpentshrine Cavern
            Plr->EventTeleport(530, 830.0f, 6865.0f, -63.0f);
            Plr->Gossip_Complete();
            break;
        case 423:  // The Blood Furnace
            Plr->EventTeleport(530, -303.0f, 3164.0f, 32.0f);
            Plr->Gossip_Complete();
            break;
        case 424:  // The Eye
            Plr->EventTeleport(530, 3087.0f, 1373.0f, 185.0f);
            Plr->Gossip_Complete();
            break;
        case 425:  // The Shattered Halls
            Plr->EventTeleport(530, -311.0f, 3083.0f, -3.0f);
            Plr->Gossip_Complete();
            break;
        case 426:  // The Slave Pens
            Plr->EventTeleport(530, 719.0f, 6999.0f, -73.0f);
            Plr->Gossip_Complete();
            break;
        case 427:  // The Steamvault
            Plr->EventTeleport(530.0f, 816.0f, 6934.0f, -80.0f);
            Plr->Gossip_Complete();
            break;
        case 428:  // The Underbog
            Plr->EventTeleport(530, 777.0f, 6763.0f, -72.0f);
            Plr->Gossip_Complete();
            break;
        }
    }
};

void SetupTeleNPC(ScriptMgr * mgr)
{
    GossipScript * teleporter = (GossipScript*) new TeleNPC();
    mgr->register_gossip_script(123456, teleporter);
}
