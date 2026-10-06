#include "preview_display.hpp"

#include "../domain/pet_snapshot.hpp"
#include "../ui/screen.hpp"
#include "../ui/zumi.hpp"

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#include <windows.h>
#endif

static PetSnapshot g_pet;
static TouchLatch g_latch = {false, 0};
static CareNotice g_notice = {0, 0};

#ifdef _WIN32

static void show_pet() {
  zumi_show(preview_display(), g_pet, care_notice_text(g_notice, GetTickCount()));
}

static const int kScale = 3;

static void paint_window(HWND window) {
  show_pet();
  PAINTSTRUCT paint;
  HDC dc = BeginPaint(window, &paint);
  const uint16_t* pixels = preview_framebuffer();

  BITMAPINFO info;
  memset(&info, 0, sizeof(info));
  info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  info.bmiHeader.biWidth = kPreviewW;
  info.bmiHeader.biHeight = -kPreviewH;
  info.bmiHeader.biPlanes = 1;
  info.bmiHeader.biBitCount = 32;
  info.bmiHeader.biCompression = BI_RGB;

  uint32_t image[kPreviewW * kPreviewH];
  for (int i = 0; i < kPreviewW * kPreviewH; ++i) {
    const uint16_t color = pixels[i];
    const int red = ((color >> 11) & 0x1F) * 255 / 31;
    const int green = ((color >> 5) & 0x3F) * 255 / 63;
    const int blue = (color & 0x1F) * 255 / 31;
    image[i] = static_cast<uint32_t>(blue) | (static_cast<uint32_t>(green) << 8) |
               (static_cast<uint32_t>(red) << 16);
  }

  RECT client;
  GetClientRect(window, &client);
  SetStretchBltMode(dc, COLORONCOLOR);
  StretchDIBits(dc, 0, 0, client.right, client.bottom, 0, 0, kPreviewW, kPreviewH, image, &info,
                DIB_RGB_COLORS, SRCCOPY);
  EndPaint(window, &paint);

  char title[96];
  snprintf(title, sizeof(title), "Zumi 320x240  fome %u  energia %u  diversao %u  higiene %u%s",
           g_pet.bars.hunger, g_pet.bars.energy, g_pet.bars.fun, g_pet.bars.hygiene,
           g_pet.asleep ? "  dormindo" : "");
  SetWindowTextA(window, title);
}

static LRESULT CALLBACK preview_wndproc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
  switch (message) {
  case WM_PAINT:
    paint_window(window);
    return 0;
  case WM_LBUTTONDOWN: {
    RECT client;
    GetClientRect(window, &client);
    const int width = client.right > 0 ? client.right : 1;
    const int height = client.bottom > 0 ? client.bottom : 1;
    const int x = static_cast<int>(LOWORD(lparam)) * kPreviewW / width;
    const int y = static_cast<int>(HIWORD(lparam)) * kPreviewH / height;
    const uint32_t now = GetTickCount();
    if (touch_accept(g_latch, true, now)) {
      const TouchOutcome outcome = touch_at(g_pet, x, y);
      if (outcome.attempted) {
        care_notice_show(g_notice, outcome.notice, now);
      }
    }
    InvalidateRect(window, 0, FALSE);
    return 0;
  }
  case WM_LBUTTONUP:
    touch_accept(g_latch, false, GetTickCount());
    return 0;
  case WM_TIMER:
    InvalidateRect(window, 0, FALSE);
    return 0;
  case WM_KEYDOWN:
    if (wparam == VK_ESCAPE) {
      DestroyWindow(window);
    }
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    break;
  }
  return DefWindowProc(window, message, wparam, lparam);
}

extern "C" __declspec(dllimport) int __stdcall SetProcessDPIAware(void);

static int run_window() {
  SetProcessDPIAware();
  HINSTANCE instance = GetModuleHandle(0);
  const char* klass = "ZumiPreview";
  WNDCLASSA window_class = {};
  window_class.lpfnWndProc = preview_wndproc;
  window_class.hInstance = instance;
  window_class.lpszClassName = klass;
  window_class.hCursor = LoadCursor(0, IDC_ARROW);
  window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  RegisterClassA(&window_class);

  RECT rect = {0, 0, kPreviewW * kScale, kPreviewH * kScale};
  AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
  HWND window = CreateWindowA(klass, "Zumi 320x240", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                              CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 0, 0,
                              instance, 0);
  ShowWindow(window, SW_SHOW);
  SetTimer(window, 1, 100, 0);

  MSG message;
  while (GetMessage(&message, 0, 0, 0) > 0) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return 0;
}

#endif

int main(int argc, char** argv) {
  g_pet = pet_snapshot_newborn(0);

  if (argc >= 3 && strcmp(argv[1], "--dump") == 0) {
    g_pet.bars.hunger = 20;
    care_notice_show(g_notice, "Comeu", 0);
    zumi_show(preview_display(), g_pet, care_notice_text(g_notice, 0));
    return preview_write_bmp(argv[2]) ? 0 : 1;
  }

#ifdef _WIN32
  return run_window();
#else
  (void)argc;
  (void)argv;
  fprintf(stderr, "preview de janela disponivel no Windows\n");
  return 1;
#endif
}
