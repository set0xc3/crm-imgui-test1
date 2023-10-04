#include <cbased.h>

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_sdl2.h>

int
main(int, char **)
{
  os_init(false);
  gfx_init();

  DB_pg_connect("host=172.17.0.2 port=5432 dbname=test user=postgres "
                "password=root connect_timeout=10");

  if (!DB_pg_connect_is_valid()) {
    DB_pg_finish();
    return 1;
  }

  PGresult *pg_result = DB_pg_exec("SELECT * FROM clients");
  if (!pg_result) {
    DB_pg_finish();
  }

  u32 pg_result_rows = PQntuples(pg_result);
  u32 pg_result_cols = PQnfields(pg_result);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags
      |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags
      |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/NotoSansCJK-Regular.ttc",
      18.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

  ImGui::StyleColorsLight();

  ImGui_ImplSDL2_InitForOpenGL(os_window_root_get()->sdl.window,
                               os_window_root_get()->sdl.gl_ctx);
  ImGui_ImplOpenGL2_Init();

  ImGui::GetIO().FontGlobalScale = 2.0; // HACK

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
            ImGui::Text("Клиенты");

            static ImGuiTableFlags flags
                = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
            static bool display_headers = false;

            if (ImGui::BeginTable("table_clients", 6, flags)) {
              ImGui::TableSetupColumn("ID");
              ImGui::TableSetupColumn("Ф.И.О");
              ImGui::TableSetupColumn("Телефон");
              ImGui::TableSetupColumn("Адрес");
              ImGui::TableSetupColumn("Эл.почта");
              ImGui::TableSetupColumn("Дата регистрации");
              ImGui::TableHeadersRow();

              for (u32 row = 0; row < pg_result_rows; row++) {
                ImGui::TableNextRow();
                for (u32 i = 0; i < 6; i++) {
                  ImGui::TableSetColumnIndex(i);
                  ImGui::TextUnformatted(PQgetvalue(pg_result, row, i + 1));
                }
                ImGui::Button("X");
              }
            }
            ImGui::EndTable();
            ImGui::EndTabItem();
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

    gfx_begin(0, 0, (u32)io.DisplaySize.x, (u32)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    os_window_swap_buffer(os_window_root_get());

    os_delay(1);
  }

  // Cleanup
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  return 0;
}
