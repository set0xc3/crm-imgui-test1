#include "app.h"

#include "crm/ui/imgui.h"
#include "crm/ui/ui.h"
#include "crm/views/clients.h"
#include "db/client.h"
#include "db/server.h"

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_sdl2.h>

static App_Ctx ctx;

void
app_init(void)
{
  os_init(false);
  gfx_init();
  ui_init();
}

void
app_run(void)
{
  app_init();

  // Main loop
  b32 done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ui_process_event(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT
          && event.window.event == SDL_WINDOWEVENT_CLOSE
          && event.window.windowID
                 == SDL_GetWindowID(os_window_root_get()->sdl.window))
        done = true;
    }

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
        // TabBars
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
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
    ui_render();

    os_window_swap_buffer(os_window_root_get());

    os_delay(1);
  }

  app_shutdown();
}

void
app_shutdown(void)
{
  imgui_destroy();
}
