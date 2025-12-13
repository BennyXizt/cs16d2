#if defined _dota2core_included
  #endinput
#endif
#define _dota2core_included

const MAX_PLAYERS = 64;
const MAX_HEROES = 2;
const MAX_LEVELS = 30;

new g_HeroNames[MAX_HEROES][] = {
  "Wraith King",
  "Sniper"
};

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
    2200, // Level 8 > 9
    2700, // Level 9 > 10
};

new g_PlayerHero[MAX_PLAYERS];
new g_PlayerHP[MAX_PLAYERS];

public Dota2CoreShowHeroMenu(id) {
  if(!is_user_connected(id) || is_user_bot(id)) return 0
  
  new menu = menu_create("Choose Hero:", "Dota2CoreShowHeroMenuHandler");
  new buffer[64];
  
  for(new i = 0; i < sizeof(g_HeroNames); i++) {
    formatex(buffer, charsmax(buffer), "%-16s  \rLevel: \r%3d", g_HeroNames[i], g_HeroCurrLevels[id][i]);
    
    menu_additem(menu, buffer);
  }
  
  menu_display(id, menu, 0);
  
  return 1;
}

public Dota2CoreShowHeroMenuHandler(id, menu, item) {
  if(item >= 0) {
    client_print(id, print_chat, "Your Hero is %s", g_HeroNames[item]);
    g_PlayerHero[id] = item;
  }
 
 return 1;
}
