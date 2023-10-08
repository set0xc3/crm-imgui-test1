#include "crm/db/client.h"

#include "cbased/db/postgresql.h"

void
DB_client_create(const DB_Client *client)
{
  int buffer_size
      = snprintf(NULL, 0,
                 "INSERT INTO clients (id, name, phone, address,email,date) "
                 "VALUES (%d,'%s','%s','%s', '%s', '%s');",
                 client->id, client->name, client->phone, client->address,
                 client->email, client->date);

  // Проверяем успешность выполнения функции и учитываем символ завершения
  // строки '\0'
  if (buffer_size > 0) {
    char *buffer = (char *)malloc(buffer_size + 1);
    snprintf(buffer, buffer_size + 1,
             "INSERT INTO clients (id, name, phone,address,email,date) VALUES "
             "(%d,'%s','%s','%s', '%s', '%s');",
             client->id, client->name, client->phone, client->address,
             client->email, client->date);

    DB_pg_exec(buffer);

    free(buffer);
  }
}

void
DB_client_destroy(const DB_Client *client)
{
}

DB_ClientList *
DB_client_list(void)
{
  DB_ClientList *list = (DB_ClientList *)malloc(sizeof(DB_ClientList));
  memset(list, 0, sizeof(DB_ClientList));

  PGresult *pg_result = DB_pg_exec("SELECT * FROM clients");
  u32       rows      = PQntuples(pg_result);
  u32       cols      = PQnfields(pg_result);

  LOG_INFO("DB:client:rows: %d\n", rows);
  LOG_INFO("DB:client:cols: %d\n", cols);

  for (u32 i = 0; i < rows; i++) {
    DB_ClientNode *node = (DB_ClientNode *)malloc(sizeof(DB_ClientNode));
    memset(node, 0, sizeof(DB_ClientNode));

    node->client.id      = strtol(PQgetvalue(pg_result, i, 1), NULL, 10);
    node->client.name    = PQgetvalue(pg_result, i, 2);
    node->client.phone   = PQgetvalue(pg_result, i, 3);
    node->client.address = PQgetvalue(pg_result, i, 4);
    node->client.email   = PQgetvalue(pg_result, i, 5);
    node->client.date    = PQgetvalue(pg_result, i, 6);

    DLL_push_back(&list->list, &node->next);
    list->count++;
  }

  return list;
}

u32
DB_client_count(void)
{
  PGresult *pg_result = DB_pg_exec("SELECT * FROM clients");
  return PQntuples(pg_result);
}
