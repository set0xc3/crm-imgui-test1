#include "app.h"

int
main(void)
{
  chdir("../../..");
  app_init();
  app_run();
  app_shutdown();
  return 0;
}

void
app_init(void)
{
  os_init(false);
  gfx_init();
}

void
app_run(void)
{
  b32 is_quit = false;
  while (!is_quit) {
    SDL_Event event;
    while (os_event_next(&event)) {
      if (!os_process_event(&event)) {
        is_quit = true;
      }
    }
    gfx_frame_begin();
    gfx_frame_end();
    os_window_swap_buffer(os_window_root_get());
    os_delay(1);
  }
}

void
app_shutdown(void)
{
  gfx_destroy();
  os_destroy();
}
