# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

# set up our project name
project(world CXX)

set(sources
  BufferPools/BufferPools.cpp
  Commands/AccountCommands.cpp
  DBC/DBC.cpp
  DBC/DBCLoader.cpp
  DBC/DBCRecord.cpp
  DBC/DBCSQL.cpp
  DBC/DBCStores.cpp
  MapManagement/AreaManagement/AreaStorage.cpp
  AddonMgr.cpp
  AIAHealSupport.cpp
  AIInterface.cpp
  AlteracValley.cpp
  ArathiBasin.cpp
  AreaTrigger.cpp
  Arenas.cpp
  ArenaTeam.cpp
  AuctionHouse.cpp
  AuctionMgr.cpp
  BattlegroundCommands.cpp
  BattlegroundHandler.cpp
  BattlegroundMgr.cpp
  CConsole.cpp
  Channel.cpp
  ChannelHandler.cpp
  CharacterHandler.cpp
  Chat.cpp
  ChatHandler.cpp
  ClusterInterface.cpp
  CollideInterface.cpp
  CombatHandler.cpp
  CommonScheduleThread.cpp
  ConsoleCommands.cpp
  ConsoleListener.cpp
  Container.cpp
  Corpse.cpp
  Creature.cpp
  DatabaseCleaner.cpp
  DayWatcherThread.cpp
  debugcmds.cpp
  DuelHandler.cpp
  DynamicObject.cpp
  EventableObject.cpp
  EventMgr.cpp
  EyeOfTheStorm.cpp
  faction.cpp
  GameObject.cpp
  GMTicket.cpp
  GMTicketCommands.cpp
  Group.cpp
  GroupHandler.cpp
  Guild.cpp
  GuildHandler.cpp
  HonorHandler.cpp
  InstanceCommands.cpp
  Item.cpp
  ItemHandler.cpp
  ItemInterface.cpp
  Level0.cpp
  Level1.cpp
  Level2.cpp
  Level3.cpp
  LfgHandler.cpp
  LfgMgr.cpp
  LocalizationMgr.cpp
  LogonCommClient.cpp
  LogonCommHandler.cpp
  LootMgr.cpp
  MailSystem.cpp
  Main.cpp
  Map.cpp
  MapCell.cpp
  MapMgr.cpp
  MapScriptInterface.cpp
  Master.cpp
  MiscHandler.cpp
  MovementHandler.cpp
  NPCHandler.cpp
  Object.cpp
  ObjectMgr.cpp
  ObjectStorage.cpp
  Opcodes.cpp
  Pet.cpp
  PetHandler.cpp
  Player.cpp
  PlayerPacketWrapper.cpp
  ProcCondHandler.cpp
  QueryHandler.cpp
  Quest.cpp
  QuestCommands.cpp
  QuestHandler.cpp
  QuestMgr.cpp
  RaidHandler.cpp
  RecallCommands.cpp
  ReputationHandler.cpp
  ScriptMgr.cpp
  SkillHandler.cpp
  SocialHandler.cpp
  SpeedDetector.cpp
  Spell.cpp
  SpellAuras.cpp
  SpellEffects.cpp
  SpellFixes.cpp
  SpellHandler.cpp
  SpellTarget.cpp
  Stats.cpp
  StdAfx.cpp
  TaxiHandler.cpp
  TaxiMgr.cpp
  TerrainMgr.cpp
  TradeHandler.cpp
  TransporterHandler.cpp
  Unit.cpp
  VoiceChatClientSocket.cpp
  VoiceChatHandler.cpp
  WarsongGulch.cpp
  WayPoints.cpp
  WeatherMgr.cpp
  WordFilter.cpp
  WorkdSocketCluster.cpp
  WorkerServerClient.cpp
  World.cpp
  WorldCreator.cpp
  WorldRunnable.cpp
  WorldSession.cpp
  WorldSocket.cpp
  WUtil.cpp)
  
if(WIN32)
  set(sources ${sources} resources.rc)
endif()

set(headers
  BufferPools/BufferPools.h
  DBC/DBC.h
  DBC/DBCGlobals.hpp
  DBC/DBCLoader.hpp
  DBC/DBCRecord.hpp
  DBC/DBCSQL.hpp
  DBC/DBCStorage.hpp
  DBC/DBCStores.h
  DBC/DBCStructures.hpp
  MapManagement/MapManagementGlobals.hpp
  MapManagement/AreaManagement/AreaManagementGlobals.hpp
  MapManagement/AreaManagement/AreaStorage.hpp
  Movement/MovementCommon.hpp
  AddonMgr.h
  AIAHealSupport.h
  AIInterface.h
  AlteracValley.h
  ArathiBasin.h
  AreaTrigger.h
  Arenas.h
  ArenaTeam.h
  AuctionHouse.h
  AuctionMgr.h
  BaseConsole.h
  BattlegroundMgr.h
  CConsole.h
  CellHandler.h
  Channel.h
  ChannelMgr.h
  Chat.h
  ClusterInterface.h
  CollideInterface.h
  CommonScheduleThread.h
  ConsoleCommands.h
  Container.h
  Corpse.h
  Creature.h
  DatabaseCleaner.h
  DayWatcherThread.h
  Definitions.h
  DynamicObject.h
  EventableObject.h
  EventMgr.h
  EyeOfTheStorm.h
  faction.h
  GameObject.h
  Group.h
  Guild.h
  HonorHandler.h
  Item.h
  ItemInterface.h
  ItemPrototype.h
  LfgMgr.h
  LocalizationMgr.h
  LogonCommClient.h
  LogonCommHandler.h
  LootMgr.h
  MailSystem.h
  MainServerDefines.h
  Map.h
  MapCell.h
  MapMgr.h
  MapScriptInterface.h
  Master.h
  MiscHandler.h
  NameTables.h
  NPCHandler.h
  Object.h
  ObjectMgr.h
  ObjectStorage.h
  Opcodes.h
  Packets.h
  Pet.h
  Player.h
  ProcCondHandler.h
  Quest.h
  QuestMgr.h
  ScriptMgr.h
  ScriptSetup.h
  Skill.h
  SkillNameMgr.h
  SpeedDetector.h
  Spell.h
  SpellAuras.h
  SpellFailure.h
  SpellNameHashes.h
  Stats.h
  StdAfx.h
  TaxiMgr.h
  TerrainMgr.h
  TransporterHandler.h
  Unit.h
  UpdateFields.h
  UpdateMask.h
  VoiceChatClientSocket.h
  VoiceChatHandler.h
  WarsongGulch.h
  WeatherMgr.h
  WordFilter.h
  WorkerServerClient.h
  World.h
  WorldCreator.h
  WorldRunnable.h
  WorldSession.h
  WorldSocket.h
  WUtil.h)

include_directories(
   ${OPENSSL_INCLUDE_DIR}
   ${PCRE_INCLUDE_DIR}
   ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
   ${CMAKE_SOURCE_DIR}/dep/vmaplib/include
   ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
   ${CMAKE_SOURCE_DIR}/src/shared
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${ZLIB_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${sources} ${headers})

if(USE_PCH AND PCHSupport_FOUND)
    ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} StdAfx.h ${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.cpp)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)
add_dependencies(${PROJECT_NAME} shared g3dlite vmaplib Detour Recast)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/WorldConf.h.in ${CMAKE_CURRENT_SOURCE_DIR}/WorldConf.h)

target_link_libraries(${PROJECT_NAME} shared g3dlite vmaplib Detour Recast ${PCRE_LIBRARIES})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
