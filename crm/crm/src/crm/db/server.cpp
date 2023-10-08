#include "crm/db/server.h"

#include "cbased/db/postgresql.h"

b32
DB_server_connect(const char *path)
{
  DB_pg_connect(path);

  if (!DB_pg_connect_is_valid()) {
    DB_pg_finish();
    return false;
  }

  return true;
}

void
DB_server_disconnect(void)
{
}
