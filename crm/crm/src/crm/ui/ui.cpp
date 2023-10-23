#include "crm/ui/ui.h"
#include "crm/ui/clients.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <cbased.h>

void
ui_init(void)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard
                    | ImGuiConfigFlags_DpiEnableScaleViewports
                    | ImGuiConfigFlags_DpiEnableScaleFonts;

  f32 dpi_scale = 0.0f;
  SDL_GetDisplayDPI(0, &dpi_scale, NULL, NULL);
  dpi_scale = dpi_scale / 96.0f;

  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(dpi_scale);

  ImFont *font = io.Fonts->AddFontFromFileTTF(
      "assets/fonts/SourceCodePro-Regular.otf", 10.0f * dpi_scale, NULL,
      io.Fonts->GetGlyphRangesCyrillic());

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(os_window_root_get()->sdl.window,
                               os_window_root_get()->sdl.gl_ctx);
  ImGui_ImplOpenGL3_Init();
}

void
ui_destroy(void)
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void
ui_process_event(SDL_Event *event)
{
  ImGui_ImplSDL2_ProcessEvent(event);
}

void
ui_begin(void)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

void
ui_end(void)
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void
ui_main(void)
{
  static bool             use_work_area = true;
  static ImGuiWindowFlags flags         = ImGuiWindowFlags_NoDecoration
                                  | ImGuiWindowFlags_NoMove
                                  | ImGuiWindowFlags_NoSavedSettings;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
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
        clients_view_display(NULL);
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
