#if defined _dota2globals_included
  #endinput
#endif
#define _dota2globals_included

#include <amxmodx>
#include <amxmisc>
#include <hamsandwich>

#define PLUGIN "DOTA 2 Core"
#define VERSION "1.0"
#define AUTHOR "me3"

const MAX_PLAYERS = 64;

new g_HeroNames[][] = {
  "Wraith King",
  "Sniper"
};

const MAX_HEROES = sizeof(g_HeroNames);

new g_HeroCurrLevels[MAX_PLAYERS][MAX_HEROES];
new g_HeroCurrExps[MAX_PLAYERS][MAX_HEROES];
new g_HeroExpPerLevel[] = {
    0,   // Level 0
    100, // Level 1 > 2
    250, // Level 2 > 3
    450, // Level 3 > 4
    700, // Level 4 > 5
    1000, // Level 5 > 6
    1350, // Level 6 > 7
    1750, // Level 7 > 8
    2200, // Level 8 > 9 7800
    2700, // Level 9 > 10 10500
};

new g_PlayerHero[MAX_PLAYERS];

public PrintChat(id, const fmt[])
{
  new g_msgSayText = get_user_msgid("SayText");
  new msg[192];
  vformat(msg, charsmax(msg), fmt, 3);
  
  new fullmsg[256];
  formatex(fullmsg, charsmax(fullmsg), "^3[%s]:^1 %s", PLUGIN, msg);

  if (id) // personal
  {
      message_begin(MSG_ONE, g_msgSayText, _, id);
      write_byte(id);
      write_string(fullmsg);
      message_end();
  }
  else // all
  {
      new players[32], pnum;
      get_players(players, pnum, "ch");

      for (new i; i < pnum; i++)
      {
          message_begin(MSG_ONE, g_msgSayText, _, players[i]);
          write_byte(players[i]);
          write_string(fullmsg);
          message_end();
      }
  }
}

public PrintChatF(id, const fmt[], any:...)
{
  new g_msgSayText = get_user_msgid("SayText");
  new msg[192];
  vformat(msg, charsmax(msg), fmt, 3);
  
  new fullmsg[256];
  formatex(fullmsg, charsmax(fullmsg), "^3[%s]:^1 %s", PLUGIN, msg);

  if (id) // personal
  {
      message_begin(MSG_ONE, g_msgSayText, _, id);
      write_byte(id);
      write_string(fullmsg);
      message_end();
  }
  else // all
  {
      new players[32], pnum;
      get_players(players, pnum, "ch");

      for (new i; i < pnum; i++)
      {
          message_begin(MSG_ONE, g_msgSayText, _, players[i]);
          write_byte(players[i]);
          write_string(fullmsg);
          message_end();
      }
  }
}