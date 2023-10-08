#include "crm/db/server.h"

b32
DB_server_connect(const char *path)
{
  if (!DB_pg_connect(path)) {
    return false;
  }

  if (!DB_pg_connect_is_valid()) {
    return false;
  }

  return true;
}

void
DB_server_disconnect(void)
{
  DB_pg_finish();
}
