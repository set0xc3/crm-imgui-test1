#pragma once

#include "cbased/core/uuid.h"

typedef struct DB_Server DB_Server;

struct DB_Server {
};

b32  DB_server_connect(const char *path);
void DB_server_disconnect(void);
