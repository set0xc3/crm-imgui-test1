#pragma once

#include "cbased/core/uuid.h"

typedef struct DB_Server DB_Server;

struct DB_Server {
};

void DB_server_add(void);
void DB_server_remove(void);
void DB_server_get(void);
