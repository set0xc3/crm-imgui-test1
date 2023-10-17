#pragma once

#include <cbased.h>

#include "crm/db/client.h"
#include "crm/db/server.h"
#include "crm/ui/ui.h"
#include "crm/views/clients.h"

typedef struct App_Ctx App_Ctx;

struct App_Ctx {
};

void app_init(void);
void app_run(void);
void app_shutdown(void);
