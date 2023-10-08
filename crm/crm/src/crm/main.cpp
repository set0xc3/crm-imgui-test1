#include <cbased.h>

#include "app.h"

#include <unistd.h>

int
main(void)
{
  char cwd[256];

  if (chdir("../..") == 0) {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Родительский каталог: %s\n", cwd);
    } else {
      perror("Ошибка при получении родительского каталога");
      return 1;
    }
  }

  app_run();

  return 0;
}
