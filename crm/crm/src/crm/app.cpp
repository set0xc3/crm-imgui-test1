#include "app.h"

#include "crm/ui/ui.h"

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <cbased.h>

vec2
os_display_get_resolution_with_scaling(i32 display_index)
{
  vec2 result;

  static Display *display = XOpenDisplay(nullptr);
  if (display == nullptr) {
    LOG_ERR("Failed to open X11 display\n");
    return result;
  }

  static Window root_window = DefaultRootWindow(display);

  static XRRScreenResources *screen_resources
      = XRRGetScreenResources(display, root_window);
  if (screen_resources == nullptr) {
    LOG_ERR("Failed to get XRandR screen resources\n");
    XCloseDisplay(display);
    return result;
  }

  XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(
      display, screen_resources, screen_resources->crtcs[display_index]);
  result = vec2_init((f32)crtc_info->width, (f32)crtc_info->height);
  if (crtc_info == nullptr) {
    LOG_ERR("Failed to get XRandR CRTC info\n");
    XRRFreeScreenResources(screen_resources);
    XCloseDisplay(display);
    return result;
  }

  // XRRFreeScreenResources(screen_resources);
  // XCloseDisplay(display);
  return result;
}

int
main(void)
{
  chdir("../../..");
  app_init();
  app_run();
  app_shutdown();
  return 0;
}

void
app_init(void)
{
  os_init(false);
  gfx_init();
  ui_init();

  for (i32 idx = 0; idx < SDL_GetNumVideoDisplays(); idx++) {
    vec4 window_rect = os_window_root_get()->rect;
    vec4 display_rect;
    f32  display_scale = 0.5f;

    SDL_Rect rect;
    SDL_GetDisplayBounds(idx, &rect);

    display_rect.x = rect.x;
    display_rect.y = rect.y;

    vec2 display_rws    = os_display_get_resolution_with_scaling(idx);
    display_rect.width  = display_rws.width;
    display_rect.height = display_rws.height;

    b32 is_half_in_display
        = (window_rect.x + window_rect.width / 2) >= display_rect.x
          && (window_rect.x + window_rect.width / 2)
                 <= (display_rect.x + display_rect.width);

    if (is_half_in_display) {
      LOG_INFO("[%i] (%f, %f, %f, %f)\n", idx, display_rect.x, display_rect.y,
               display_rect.width, display_rect.height);
    }
  }
}

void
app_run(void)
{
  b32 is_quit = false;
  while (!is_quit) {
    SDL_Event event;
    while (os_event_next(&event)) {
      if (!os_process_event(&event)) {
        is_quit = true;
      }
      ui_process_event(&event);
    }

    gfx_begin();
    ui_begin();
    ui_main();
    ui_end();
    gfx_end();
    os_window_swap_buffer(os_window_root_get());
    os_delay(1);
  }
}

void
app_shutdown(void)
{
  ui_destroy();
  gfx_destroy();
  os_destroy();
}
