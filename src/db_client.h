#pragma once

#include "cbased/core/string.h"
#include "cbased/core/uuid.h"

#include "db_server.h"

typedef struct DB_Client     DB_Client;
typedef struct DB_ClientInfo DB_ClientInfo;

struct DB_ClientInfo {
  Uuid   _uuid;
  u32    id;
  String name;
  String phone;
  String address;
  String email;
  String date;
};

struct DB_Client {
  Uuid          uuid;
  b32           is_dirty;
  DB_ClientInfo info;
};

void DB_client_add(DB_ClientInfo *client_info);
void DB_client_remove(DB_Client *client);
void DB_client_count(void);
