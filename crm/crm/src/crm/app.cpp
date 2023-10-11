#include "app.h"

#include "crm/views/clients.h"
#include "db/client.h"
#include "db/server.h"

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_sdl2.h>

static ImVec4  clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static App_Ctx ctx;

void
app_init(void)
{
  os_init(false);
  gfx_init();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags
      |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags
      |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  io.Fonts->AddFontFromFileTTF("assets/fonts/SourceCodePro-Medium.otf", 18.0f,
                               nullptr,
                               ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

  ImGui::StyleColorsLight();

  ImGui_ImplSDL2_InitForOpenGL(os_window_root_get()->sdl.window,
                               os_window_root_get()->sdl.gl_ctx);
  ImGui_ImplOpenGL2_Init();

  ImGui::GetIO().FontGlobalScale = 1.0; // HACK
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
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT
          && event.window.event == SDL_WINDOWEVENT_CLOSE
          && event.window.windowID
                 == SDL_GetWindowID(os_window_root_get()->sdl.window))
        done = true;
    }

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
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
            clients_view_display();
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
    ImGui::Render();

    ImGuiIO &io = ImGui::GetIO();
    gfx_begin(0, 0, (u32)io.DisplaySize.x, (u32)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    os_window_swap_buffer(os_window_root_get());

    os_delay(1);
  }

  app_shutdown();
}

void
app_shutdown(void)
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
