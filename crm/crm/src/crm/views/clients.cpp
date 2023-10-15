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
        | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Sortable
        | ImGuiTableFlags_Resizable;
  static bool display_headers = false;

  const char *items[] = {
    "5", "10", "20", "50", "100",
  };
  static int  item_current_idx = 0;
  const char *preview_value    = items[item_current_idx];
  static u32  max_client_view  = strtol(preview_value, NULL, 10);

  ImGui::Text("Клиенты");

  // ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth()
  //                                - ImGui::GetStyle().ItemSpacing.x
  //                                - ImGui::GetItemRectSize().x,
  //                            ImGui::GetItemRectMax().y));

  ImGui::BeginGroup();
  if (ImGui::Button("Создать клиента")) {
    ImGui::OpenPopup("Создать клиента");
  }

  // Always center this window when appearing
  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  ImGui::SetNextWindowSize(ImVec2(500, 400));
  if (ImGui::BeginPopupModal("Создать клиента", NULL,
                             ImGuiWindowFlags_NoDocking
                                 | ImGuiWindowFlags_NoResize
                                 | ImGuiWindowFlags_NoMove)) {
    b32 is_valid = false;

    // Физ/Юр лицо
    {
      static const char *items[] = {
        "Физ. лицо",
        "Юр. лицо",
      };
      static u32  item_current_idx = 0;
      const char *preview_value    = items[item_current_idx];

      static Uuid uuid            = uuid_gen();
      static char input_buf[1024] = { 0 };
      static char title_buf[1024] = { 0 };
      sprintf(title_buf, "##%s", uuid.value);

      ImGui::Text("%s", preview_value);
      ImGui::SameLine();

      if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
        for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
          const u32 is_selected = (item_current_idx == i);
          if (ImGui::Selectable(items[i], is_selected)) {
            item_current_idx = i;
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
      ImGui::Separator();

      if (item_current_idx == 0) {
        // Телефон
        {
          ImGui::Text("Телефон:*");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Ф.И.О
        {
          ImGui::Text("Ф.И.О:*");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Адрес
        {
          ImGui::Text("Адрес:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Эл.почта
        {
          ImGui::Text("Эл.почта:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Примечание
        {
          ImGui::Text("Примечание:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Контрагент
        {
          ImGui::Text("Контрагент:");
          ImGui::SameLine();

          static const char *items[] = {
            "Не выбран",
            "Иван Иванович",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
        // Статус клиента(метка)
        {
          ImGui::Text("Статус клиента(метка):");
          ImGui::SameLine();

          static const char *items[] = {
            "Не выбран", "-5%",      "-10%",    "-20%", "-30%",
            "blacklist", "discount", "regular", "VIP",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
        // Рекламный канал(источник)
        {
          ImGui::Text("Рекламный канал(источник):");
          ImGui::SameLine();

          static const char *items[] = {
            "Не определен",    "Интернет",           "Партнер",
            "По рекомендации", "Постоянные клиенты", "Проходящий поток",
            "СЦ ТРУД",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
      } else {
        // Название организации
        {
          ImGui::Text("Название организации:*");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Телефон
        {
          ImGui::Text("Телефон:*");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Юридический адрес
        {
          ImGui::Text("Юридический адрес:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Фактический адрес
        {
          ImGui::Text("Фактический адрес:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Эл.почта
        {
          ImGui::Text("Эл.почта:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Примечание
        {
          ImGui::Text("Примечание:");
          ImGui::SameLine();

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);
          ImGui::InputText(title_buf, input_buf, ARRAY_COUNT(input_buf));
        }
        // Контрагент
        {
          ImGui::Text("Контрагент:");
          ImGui::SameLine();

          static const char *items[] = {
            "Не выбран",
            "Иван Иванович",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
        // Статус клиента(метка)
        {
          ImGui::Text("Статус клиента(метка):");
          ImGui::SameLine();

          static const char *items[] = {
            "Не выбран", "-5%",      "-10%",    "-20%", "-30%",
            "blacklist", "discount", "regular", "VIP",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
        // Рекламный канал(источник)
        {
          ImGui::Text("Рекламный канал(источник):");
          ImGui::SameLine();

          static const char *items[] = {
            "Не определен",    "Интернет",           "Партнер",
            "По рекомендации", "Постоянные клиенты", "Проходящий поток",
            "СЦ ТРУД",
          };
          static u32  item_current_idx = 0;
          const char *preview_value    = items[item_current_idx];

          static Uuid uuid            = uuid_gen();
          static char input_buf[1024] = { 0 };
          static char title_buf[1024] = { 0 };
          sprintf(title_buf, "##%s", uuid.value);

          ImGui::Text("%s", preview_value);
          ImGui::SameLine();

          if (ImGui::BeginCombo(title_buf, preview_value, flags)) {
            for (size_t i = 0; i < ARRAY_COUNT(items); i++) {
              const u32 is_selected = (item_current_idx == i);
              if (ImGui::Selectable(items[i], is_selected)) {
                item_current_idx = i;
              }
              if (is_selected) {
                ImGui::SetItemDefaultFocus();
              }
            }
            ImGui::EndCombo();
          }
        }
      }
    }

    ImGui::SetCursorPos(ImVec2(ImGui::GetStyle().ItemSpacing.x,
                               ImGui::GetWindowHeight()
                                   - ImGui::GetStyle().ItemSpacing.y
                                   - ImGui::GetFontSize() - 10.0f));
    ImGui::BeginGroup();
    if (ImGui::Button("Создать") && is_valid) {
      max_client_view++;
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Отмена")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndGroup();

    ImGui::EndPopup();
  }

  ImGui::SameLine();
  ImGui::Button("Экспорт");

  group_size = ImGui::GetItemRectSize();
  ImGui::EndGroup();

  if (ImGui::BeginTable("table_clients", 9, flags,
                        ImVec2(0.0f, TEXT_BASE_HEIGHT * 15), 0.0f)) {
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn(""); // Mark
    ImGui::TableSetupColumn(""); // Tag
    ImGui::TableSetupColumn("Ф.И.О");
    ImGui::TableSetupColumn("Телефон");
    ImGui::TableSetupColumn("Адрес");
    ImGui::TableSetupColumn("Эл.почта");
    ImGui::TableSetupColumn("Дата регистрации");
    ImGui::TableSetupColumn(""); // Close
    ImGui::TableHeadersRow();

    for (u32 row = 0;
         row < CLAMP_TOP(strtol(preview_value, NULL, 10), max_client_view);
         row++) {
      ImGui::TableNextRow();

      ImGui::TableSetColumnIndex(0);
      static char title_buf[1024] = { 0 };
      sprintf(title_buf, "#%d", row);
      ImGui::TextUnformatted(title_buf);

      ImGui::TableSetColumnIndex(1);
      ImGui::TextUnformatted("*");

      ImGui::TableSetColumnIndex(2);
      ImGui::TextUnformatted("VIP");

      ImGui::TableSetColumnIndex(8);
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
    if (ImGui::BeginCombo("##combo", preview_value, flags)) {
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
