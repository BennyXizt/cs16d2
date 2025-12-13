#if defined _dota2db_included
  #endinput
#endif
#define _dota2db_included

#include <amxmodx>
#include <amxmisc>
#include <mysql>

static PLUGIN[] = "DOTA 2 Core";

static DB_HOST[] = "127.0.0.1:8889";
static DB_USER[] = "cs";
static DB_PASSWORD[] = "cs_password";
static DB_DATABASE[] = "cs_16";

new Handle:db;
new db_errorcode;
new db_errorstring[256];

public Dota2DBInit() {
    db = DBConnect();
    if (db == 0) return 0;

    if (!DBInit()) return 0;

    return 1;
}

public Dota2DBSaveUserOnConnect(id) {
 new name[32];
 get_user_name(id, name, sizeof(name));
 
  new steamid[32];
 get_user_authid(id, steamid, sizeof(steamid));

  new query[256];
  format(query, sizeof(query),
       "INSERT INTO `users` (`user`, `steamid`) VALUES ('%s', '%s') ON DUPLICATE KEY UPDATE `user` = VALUES (`user`), `last_seen` = CURRENT_TIMESTAMP;",
       name, steamid);
       
  if (!SQL_SimpleQuery(db, query)) {
     SQL_QueryError(db, db_errorstring, sizeof(db_errorstring));
     server_print("[%s]: Failed to add new user in table `users`: %s", PLUGIN, db_errorstring);
     return 0;
  } else {
    server_print("[%s]: user already exists", PLUGIN);
  }
  
  return 1;
}

public Dota2DBSaveUserOnDisconnect(id) {
  new steamid[32];
  new kills = get_user_frags(id);  
  new deaths = get_user_deaths(id);
  
  get_user_authid(id, steamid, sizeof(steamid));
  
  if(kills < 0) kills = 0;
  
  new query[256];
   format(query, sizeof(query),
           "UPDATE `users` SET `last_seen` = CURRENT_TIMESTAMP, `kills` = %d, `death` = %d  WHERE steamid = '%s';",
           kills, deaths, steamid);
	   
 if (!SQL_SimpleQuery(db, query))
  {
    SQL_QueryError(db, db_errorstring, sizeof(db_errorstring));
    server_print("[%s]: Failed to update last_seen for %s: %s", PLUGIN, steamid, db_errorstring);
  }
  else
  {
    server_print("[%s]: Updated last_seen for %s", PLUGIN, steamid);
  }

  return 1;
}
 
static DBConnect() {
  new Handle:DBtuple = SQL_MakeDbTuple(DB_HOST, DB_USER, DB_PASSWORD, DB_DATABASE);
  
  db = SQL_Connect(DBtuple, db_errorcode, db_errorstring, sizeof(db_errorstring));
  
  if(db == Empty_Handle) {
    format(db_errorstring, sizeof(db_errorstring),
       "SQL connection failed: %s",
       db_errorstring);
       
    set_fail_state(db_errorstring);
    return 0;	
  }
  
  return db;
}

static DBInit() {
  static queryUsers[] = "CREATE TABLE IF NOT EXISTS `users` (`id` INT NOT NULL AUTO_INCREMENT, `user` VARCHAR(20) NOT NULL, `steamid` VARCHAR(20) NOT NULL UNIQUE, `last_seen` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, `role` VARCHAR(10) NOT NULL DEFAULT 'user', `role_endet` TIMESTAMP NULL DEFAULT NULL, `kills` INT NOT NULL DEFAULT 0, `death` INT NOT NULL DEFAULT 0, PRIMARY KEY (`id`), UNIQUE (`steamid`)) ENGINE=InnoDB;";
  
  if (!SQL_SimpleQuery(db, queryUsers)) {
    format(db_errorstring, sizeof(db_errorstring),
       "[%s]: Failed to create table `users`: %s",
       PLUGIN, db_errorstring);
       
     SQL_QueryError(db, db_errorstring, sizeof(db_errorstring));
     set_fail_state(db_errorstring);
     return 0;	
  } else {
    server_print("[%s]: Table `users` created or already exists", PLUGIN);
  }
  
  static queryHeroes[] = "CREATE TABLE IF NOT EXISTS `heroes` (`id` INT NOT NULL AUTO_INCREMENT, `id_user` INT NOT NULL, `hero` VARCHAR(32) NOT NULL, `level` INT NOT NULL DEFAULT 1, `exp` INT NOT NULL DEFAULT 0, PRIMARY KEY (`id`), FOREIGN KEY (`id_user`) REFERENCES `users`(`id`) ON DELETE CASCADE) ENGINE=InnoDB;";
  
  if (!SQL_SimpleQuery(db, queryHeroes)) {
    format(db_errorstring, sizeof(db_errorstring),
       "[%s]: Failed to create table `heroes`: %s",
       PLUGIN, db_errorstring);
       
     SQL_QueryError(db, db_errorstring, sizeof(db_errorstring));
     set_fail_state(db_errorstring);
     return 0;
  } else {
    server_print("[%s]: Table `heroes` created or already exists", PLUGIN);
  }
  
  return 1;
}