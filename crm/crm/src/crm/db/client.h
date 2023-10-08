#pragma once

#include "cbased/core/list.h"
#include "cbased/core/string.h"
#include "cbased/core/uuid.h"

#include "crm/db/server.h"

typedef struct DB_Client DB_Client;

typedef struct DB_ClientNode DB_ClientNode;
typedef struct DB_ClientList DB_ClientList;

struct DB_Client {
  u32         id;
  const char *name;
  const char *phone;
  const char *address;
  const char *email;
  const char *date;
};

struct DB_ClientNode {
  DLL_Node  next;
  DB_Client client;
};

struct DB_ClientList {
  DLL_List list;
  u32      count;
};

void           DB_client_create(const DB_Client *client);
void           DB_client_destroy(const DB_Client *client);
DB_ClientList *DB_client_list(void);
u32            DB_client_count(void);
