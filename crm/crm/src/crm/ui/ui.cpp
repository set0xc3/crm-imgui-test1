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

enum {
  UI_TextFlags_PosLeft,
  UI_TextFlags_PosCenter,
  UI_TextFlags_PosRight,
};

enum UI_CategoryView {
  UI_CategoryView_Main,
  UI_CategoryView_Repairs,
  UI_CategoryView_Clients,
  UI_CategoryView_Products,
  UI_CategoryView_Finance,
  UI_CategoryView_Reports,
  UI_CategoryView_Tasks,
  UI_CategoryView_Settings,
};

b32
ui_button(const char *label, const ImVec2 &size = ImVec2(0, 0),
          const u32 text_flags = UI_TextFlags_PosCenter)
{
  b32    result          = false;
  ImVec2 cursor_position = ImGui::GetCursorPos();
  ImVec2 text_position;
  f32    padding = 7.0f;

  switch (text_flags) {
  case UI_TextFlags_PosLeft:
    text_position = {
      cursor_position.x + padding,
      cursor_position.y + (size.y - ImGui::GetTextLineHeightWithSpacing()) / 2,
    };
    break;
  case UI_TextFlags_PosCenter:
    text_position = {
      cursor_position.x + (size.x - ImGui::CalcTextSize(label).x) / 2,
      cursor_position.y + (size.y - ImGui::GetTextLineHeightWithSpacing()) / 2,
    };
    break;
  case UI_TextFlags_PosRight:
    text_position = {
      cursor_position.x + (size.x - ImGui::CalcTextSize(label).x) - padding,
      cursor_position.y + (size.y - ImGui::GetTextLineHeightWithSpacing()) / 2,
    };
    break;
  }

  static char title_buf[1024] = { 0 };
  sprintf(title_buf, "##%s", label);

  ImGui::SetCursorPos(cursor_position);
  if (ImGui::Button(title_buf, size)) {
    result = true;
  }
  ImGui::SetCursorPos(text_position);
  ImGui::Text("%s", label);
  ImGui::Spacing();
  ImGui::Spacing();

  return result;
}

void
ui_main(void)
{
  static ImGuiStyle      &style         = ImGui::GetStyle();
  static bool             use_work_area = true;
  static ImGuiWindowFlags flags         = ImGuiWindowFlags_NoDecoration
                                  | ImGuiWindowFlags_NoMove
                                  | ImGuiWindowFlags_NoSavedSettings;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
  ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize
                                         : viewport->Size);
  ImGui::Begin("RootWindow", NULL, flags);
  {
    ImGui::BeginChild("##left_panel",
                      ImVec2(226, ImGui::GetIO().DisplaySize.y - 28), flags);
    {
      ImGui::BeginGroup();
      {
        static ImVec2 button_size = ImVec2(200, 50);
        static ImVec4 button_default_color
            = ImGui::GetStyleColorVec4(ImGuiCol_Button);

        struct UI_ButtonInfo {
          const char *label;
          u32         category_idx;
        };

        static UI_ButtonInfo buttons[]
            = { { "Главная", UI_CategoryView_Main },
                { "Клиенты", UI_CategoryView_Clients },
                { "Ремонты", UI_CategoryView_Repairs },
                { "Товары", UI_CategoryView_Products },
                { "Финансы", UI_CategoryView_Finance },
                { "Отчёты", UI_CategoryView_Reports },
                { "Задания", UI_CategoryView_Tasks },
                { "Настройки", UI_CategoryView_Settings } };

        static u32 category_current_idx = 0;

        for (const auto &button : buttons) {
          if (category_current_idx == button.category_idx) {
            ImGui::PushStyleColor(ImGuiCol_Button, button_default_color);
          } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
          }

          if (ui_button(button.label, button_size, UI_TextFlags_PosLeft)) {
            category_current_idx = button.category_idx;
          }

          ImGui::PopStyleColor();
        }
      }
      ImGui::EndGroup();
    }
    ImGui::EndChild();

    ImGui::ShowDemoWindow();
  }
  ImGui::End();
}
