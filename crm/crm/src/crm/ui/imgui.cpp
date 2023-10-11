#include "crm/ui/imgui.h"

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_sdl2.h>

void
imgui_init(void)
{
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

  ImGui::GetIO().FontGlobalScale = 1.0;
}

void
imgui_destroy(void)
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void
imgui_render(void)
{
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
