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
      |= ImGuiConfigFlags_NavEnableKeyboard;        // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

  io.Fonts->AddFontFromFileTTF("assets/fonts/SourceCodePro-Medium.otf", 20.0f,
                               nullptr,
                               ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

  ImGui::StyleColorsLight();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding              = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

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

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window   *backup_current_window  = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }
}
