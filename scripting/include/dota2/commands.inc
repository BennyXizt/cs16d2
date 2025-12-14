#if defined _dota2commands_included
  #endinput
#endif
#define _dota2commands_included

static ADMIN_GENERIC = 0

public cmdAddExp(id) {
  if (!is_user_connected(id) || is_user_bot(id)) {
      client_print(id, print_chat, "Cannot access to these command");
      return 0;
  }
  PrintChat(id, "Command used!");
  new exp = 7800;
      
  Dota2CoreAddHeroExp(id, exp);
  return 1;
}

public cmdChangeHero(id) {
  if (!is_user_connected(id) || is_user_bot(id)) {
      client_print(id, print_chat, "Cannot access to these command");
      return 0;
  }
  
  PrintChat(id, "Command used!");
  
  g_PlayerHero[id] = -1;
  Dota2CoreShowHeroMenu(id);

  return 1;
}

public standartVGUIMenus(msgid, dest, id) { 
  new menuType = get_msg_arg_int(1);
  new menuName[64];
  get_msg_arg_string(4, menuName, charsmax(menuName));
  
  // menuType = Team Menu && Team_Select
  if(menuType == 2 && contain(menuName, "#Team_Select") != -1) {
    Dota2CoreShowTeamMenu(id);
    return PLUGIN_HANDLED;
  }
  // menuType = Team Menu && Team_Select
  if(menuType == 2 && contain(menuName, "#Model_Choose") != -1) {
    return PLUGIN_HANDLED;
  }
  return PLUGIN_CONTINUE;
}

public standartShowMenus(msgid, dest, id) {
  new menu[32];
  get_msg_arg_string(4, menu, charsmax(menu));

  if(contain(menu, "#Team_Select") != -1) {
    Dota2CoreShowTeamMenu(id)
    return PLUGIN_HANDLED;
  }

  if(contain(menu, "#Model_Choose") != -1) {
    return PLUGIN_HANDLED; 
  }
      
  return PLUGIN_CONTINUE;
}

public blockUnesessaryCommands(id) {
  Dota2CoreShowTeamMenu(id);
  return PLUGIN_HANDLED;
}

public Dota2CMDRegisterCommands() {
  register_clcmd("say /a", "cmdAddExp", ADMIN_GENERIC);
  register_clcmd("say /hero", "cmdChangeHero");

  // Block Standart Menu
  register_message(get_user_msgid("VGUIMenu"), "standartVGUIMenus");
  register_message(get_user_msgid("ShowMenu"), "standartShowMenus");
  // register_clcmd("jointeam", "blockUnesessaryCommands");
  register_clcmd("chooseteam", "blockUnesessaryCommands");
}