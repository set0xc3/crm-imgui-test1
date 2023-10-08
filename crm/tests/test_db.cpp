#include <cbased.h>
#include <crm.h>

int
main(void)
{
  DB_server_connect("host=172.17.0.2 port=5432 dbname=test user=postgres "
                    "password=root connect_timeout=10");

  DB_Client client_info = {
    .id      = 0,
    .name    = "Александр",
    .phone   = "+00000000000",
    .address = "None",
    .email   = "alexander@gmail.com",
    .date    = "2023-04-10",
  };
  // DB_client_create(&client_info);

  LOG_INFO("DB:client:count: %d\n", DB_client_count());

  DB_ClientList *client_list = DB_client_list();
#if 1
  DLL_Iterator it = DLL_iterator_head(client_list->list, DB_ClientNode, next);
  for (DB_ClientNode *node = (DB_ClientNode *)DLL_iterate_next(&it);
       node != NULL; node  = (DB_ClientNode *)DLL_iterate_next(&it)) {
    DB_Client *client = &node->client;
    LOG_INFO("entity.id: %d\n", client->id);
    LOG_INFO("entity.name: %s\n", client->name);
    LOG_INFO("entity.phone: %s\n", client->phone);
    LOG_INFO("entity.address: %s\n", client->address);
    LOG_INFO("entity.email: %s\n", client->email);
    LOG_INFO("entity.date: %s\n", client->date);
    LOG_INFO("\n");
  }
#endif

  DB_server_disconnect();

  return 0;
}
