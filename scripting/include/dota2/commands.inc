#if defined _dota2commands_included
  #endinput
#endif
#define _dota2commands_included

static ADMIN_GENERIC = 0

public cmdAddExp(id) {
  if (!is_user_connected(id) || is_user_bot(id))
  {
      client_print(id, print_chat, "Kannot access to these command");
      return 0;
  }
  PrintChat(id, "Command used!");
  new exp = 7800;
      
  Dota2CoreAddHeroExp(id, exp);
  return 1;
    
}

public cmdChangeHero(id) {
  if (!is_user_connected(id) || is_user_bot(id))
  {
      client_print(id, print_chat, "Kannot access to these command");
      return 0;
  }
  
  PrintChat(id, "Command used!");
  
  g_PlayerHero[id] = -1;
  Dota2CoreShowHeroMenu(id);

  return 1;
    
}

public Dota2CMDRegisterCommands() {
  register_clcmd("say /a", "cmdAddExp", ADMIN_GENERIC);
  register_clcmd("say /hero", "cmdChangeHero");
}