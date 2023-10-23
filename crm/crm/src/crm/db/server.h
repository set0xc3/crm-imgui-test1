#pragma once

#include "cbased/core/uuid.h"
#include "cbased/db/postgresql.h"

typedef struct DB_Server DB_Server;

struct DB_Server {
  void *handle;
};

api b32  DB_server_connect(const char *path);
api void DB_server_disconnect(void);
