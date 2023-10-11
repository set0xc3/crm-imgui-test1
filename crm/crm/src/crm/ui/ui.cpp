#include "crm/ui/ui.h"
#include "crm/ui/imgui.h"

void
ui_init(void)
{
  imgui_init();
}

void
ui_destroy(void)
{
  imgui_destroy();
}

void
ui_process_event(SDL_Event *event)
{
  ImGui_ImplSDL2_ProcessEvent(event);
}

void
ui_update(void)
{
}

void
ui_render(void)
{
  imgui_render();
}

void
ui_begin(void)
{
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  ImVec4   clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  ImGuiIO &io          = ImGui::GetIO();
  gfx_begin(0, 0, (u32)io.DisplaySize.x, (u32)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
ui_end(void)
{
  ImGui::Render();
}
