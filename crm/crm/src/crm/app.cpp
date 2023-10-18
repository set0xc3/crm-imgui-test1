#include "app.h"

#include <imgui_internal.h>

static App_Ctx ctx;

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
  ui_init();
  LOG_INFO("WindowDpiScale: %f\n", ImGui::GetWindowDpiScale());
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
      ui_process_event(&event);
    }
    gfx_frame_begin();
    ui_begin();
    {
      static bool             use_work_area = true;
      static ImGuiWindowFlags flags         = ImGuiWindowFlags_NoDecoration
                                      | ImGuiWindowFlags_NoMove
                                      | ImGuiWindowFlags_NoSavedSettings;
      const ImGuiViewport *viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos
                                            : viewport->Pos);
      ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize
                                             : viewport->Size);
      if (ImGui::Begin("RootWindow", NULL, flags)) {
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
          if (ImGui::BeginTabItem("Главная")) {
            ImGui::Text("Главная");
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Ремонты")) {
            ImGui::Text("Ремонты");
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Товары")) {
            ImGui::Text("Товары");
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Клиенты")) {
            DB_ClientList *client_list = NULL;
            clients_view_display(client_list);
          }
          if (ImGui::BeginTabItem("Финансы")) {
            ImGui::Text("Финансы");
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Отчёты")) {
            ImGui::Text("Отчёты");
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Задания")) {
            ImGui::Text("Задания");
            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
        ImGui::ShowDemoWindow();
      }
      ImGui::End();
    }
    ui_end();
    gfx_frame_end();
    os_window_swap_buffer(os_window_root_get());
    os_delay(1);
  }
}

void
app_shutdown(void)
{
  ui_destroy();
  gfx_destroy();
  os_destroy();
}
