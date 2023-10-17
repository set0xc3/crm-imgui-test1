#include "cbased.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <SDL2/SDL.h>

void ui_init(void);
void ui_destroy(void);
void ui_process_event(SDL_Event *event);
void ui_begin(void);
void ui_end(void);
