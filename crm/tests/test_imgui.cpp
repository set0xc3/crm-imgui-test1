#include <cbased.h>
#include <crm.h>

int
main(void)
{
  chdir("../../.."); // TODO: Remove this
  os_init(false);
  gfx_init();
  ui_init();
  b32 is_quit = false;
  while (!is_quit) {
    SDL_Event event;
    while (os_event_next(&event)) {
      if (!os_process_event(&event)) {
        is_quit = true;
      }
      ui_process_event(&event);
    }
    gfx_frame_begin();
    ui_begin();
    {
      static float f       = 0.0f;
      static int   counter = 0;
      ImGui::Begin("Hello, world!");
      ImGui::Text("This is some useful text.");
      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
      if (ImGui::Button("Button"))
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate,
                  ImGui::GetIO().Framerate);
      ImGui::End();
    }
    ui_end();
    gfx_frame_end();
    os_window_swap_buffer(os_window_root_get());
  }
  ui_destroy();
  gfx_destroy();
  os_destroy();
  return 0;
}
