#include "crm/db/client.h"

#include "cbased/db/postgresql.h"

void
DB_client_create(const DB_Client *client)
{
  DB_pg_exec("");
}

void
DB_client_destroy(const DB_Client *client)
{
}

DB_ClientList
DB_client_list(void)
{
  DB_ClientList list;

  PGresult *pg_result = DB_pg_exec("SELECT * FROM clients");
  u32       rows      = PQntuples(pg_result);
  u32       cols      = PQnfields(pg_result);

  PQgetvalue(pg_result, 0, 0);

  return list;
}

u32
DB_client_count(void)
{
  PGresult *pg_result = DB_pg_exec("SELECT * FROM clients");
  return PQntuples(pg_result);
}
