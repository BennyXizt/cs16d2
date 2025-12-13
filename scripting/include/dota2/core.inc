#if defined _dota2core_included
  #endinput
#endif
#define _dota2core_included

public Dota2CoreShowHeroMenu(id) {
  if(!is_user_connected(id) || is_user_bot(id)) return 0
  
  new menu = menu_create("Choose Hero:", "Dota2CoreShowHeroMenuHandler");
  new buffer[64];
  
  for(new i = 0; i < sizeof(g_HeroNames); i++) {
    new heroName[32];
    formatex(heroName, sizeof(heroName), g_HeroNames[i]);

    new heroLevel = g_HeroCurrLevels[id][i];
    new heroExp =  g_HeroCurrExps[id][i];
    new heroExpToLvLUp = g_HeroExpPerLevel[heroLevel];

    formatex(buffer, charsmax(buffer), "%-16s  \rLevel: \r%3d \w[%d/%d]", heroName, heroLevel, heroExp, heroExpToLvLUp);
    
    menu_additem(menu, buffer);
  }
  
  menu_display(id, menu, 0);
  
  return 1;
}

public Dota2CoreShowHeroMenuHandler(id, menu, item) {
  if(item >= 0) {
    PrintChatF(id, "Your Hero is %s", g_HeroNames[item]);
    g_PlayerHero[id] = item;
  }

  return 1;
}

public Dota2CoreAddHeroExp(id, exp) {
  new currHero =  g_PlayerHero[id];
  
  if(currHero < 0 || currHero >= MAX_HEROES) {
    PrintChat(id, "You have no hero selected yet!");
    Dota2CoreShowHeroMenu(id);
    return 1;
  }
  
  g_HeroCurrExps[id][currHero] += exp;

  new currLevel = g_HeroCurrLevels[id][currHero];
  new expToLVLUP = g_HeroExpPerLevel[currLevel];
  new currEXP = g_HeroCurrExps[id][currHero];
  
  while(currEXP >= expToLVLUP) {
    if(g_HeroCurrLevels[id][currHero] + 1 >= sizeof(g_HeroExpPerLevel))
      break;

    g_HeroCurrExps[id][currHero] = currEXP - expToLVLUP;
    g_HeroCurrLevels[id][currHero] += 1;
    
    currEXP = g_HeroCurrExps[id][currHero];
    currLevel = g_HeroCurrLevels[id][currHero];
    expToLVLUP = g_HeroExpPerLevel[currLevel];
    PrintChat(id, "LVL UP!");
  }
  
  PrintChatF(id, "Gained %d exp || Curr exp [%d/%d]", exp, g_HeroCurrExps[id][currHero], expToLVLUP);
  
  return 1;
}