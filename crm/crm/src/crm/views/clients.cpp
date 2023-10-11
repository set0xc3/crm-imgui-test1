#include "crm/views/clients.h"

#include <imgui.h>

void
clients_view_display(DB_ClientList *client_list)
{
  const float TEXT_BASE_WIDTH  = ImGui::CalcTextSize("A").x;
  const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

  ImVec2 group_size = ImVec2(0, 0);

  static ImGuiTableFlags flags
      = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg
        | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Sortable;
  static bool display_headers = false;

  const char *items[] = {
    "5", "10", "20", "50", "100",
  };
  static int  item_current_idx    = 0;
  const char *combo_preview_value = items[item_current_idx];
  static u32  max_client_view     = strtol(combo_preview_value, NULL, 10);

  ImGui::Text("Клиенты");

  // ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth()
  //                                - ImGui::GetStyle().ItemSpacing.x
  //                                - ImGui::GetItemRectSize().x,
  //                            ImGui::GetItemRectMax().y));

  ImGui::BeginGroup();
  if (ImGui::Button("Создать клиента")) {
    max_client_view++;
  }
  ImGui::SameLine();
  ImGui::Button("Экспорт");

  group_size = ImGui::GetItemRectSize();
  ImGui::EndGroup();

  if (ImGui::BeginTable("table_clients", 7, flags,
                        ImVec2(0.0f, TEXT_BASE_HEIGHT * 15), 0.0f)) {
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Ф.И.О");
    ImGui::TableSetupColumn("Телефон");
    ImGui::TableSetupColumn("Адрес");
    ImGui::TableSetupColumn("Эл.почта");
    ImGui::TableSetupColumn("Дата регистрации");
    ImGui::TableHeadersRow();

    for (u32 row = 0; row < ClampTop(strtol(combo_preview_value, NULL, 10),
                                     max_client_view);
         row++) {
      ImGui::TableNextRow();
      for (u32 i = 0; i < 6; i++) {
        ImGui::TableSetColumnIndex(i);
        ImGui::TextUnformatted("Test");
      }

      ImGui::TableSetColumnIndex(6);
      ImGui::Button("X");
    }
  }
  ImGui::EndTable();
  ImGui::EndTabItem();

  {
    static ImVec2          combo_padding = ImVec2(20, 20);
    static ImGuiComboFlags flags         = 0;

    ImGui::SetCursorPos(
        ImVec2(combo_padding.x, ImGui::GetWindowHeight()
                                    - ImGui::GetStyle().ItemSpacing.y
                                    - ImGui::GetFontSize() - combo_padding.y));
    ImGui::SetNextItemWidth(60);
    if (ImGui::BeginCombo("combo 1", combo_preview_value, flags)) {
      for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
        const bool is_selected = (item_current_idx == n);
        if (ImGui::Selectable(items[n], is_selected)) {
          item_current_idx = n;
        }
        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
  }
}
