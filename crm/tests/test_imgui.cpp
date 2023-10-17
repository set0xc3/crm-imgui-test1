#include <cbased.h>
#include <crm.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int
main(void)
{
  chdir("../../.."); // TODO: Remove this

  os_init(false);

  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.Fonts->AddFontFromFileTTF("assets/fonts/SourceCodePro-Medium.otf", 20.0f,
                               nullptr,
                               ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(os_window_root_get()->sdl.window,
                               os_window_root_get()->sdl.gl_ctx);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Main loop
  b32 is_quit = false;
  while (!is_quit) {
    SDL_Event event;
    while (os_event_next(&event)) {
      if (!os_process_event(&event)) {
        is_quit = true;
      }
      ImGui_ImplSDL2_ProcessEvent(&event);
    }

    // GFX begin
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    // UI begin
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

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
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }

    // UI end
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // GFX end
    os_window_swap_buffer(os_window_root_get());
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  os_destroy();

  return 0;
}
