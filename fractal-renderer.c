#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <raylib.h>

#define WIDTH     1500
#define HEIGHT    1000

float complex mandelbrot(float complex z, float complex c)
{
  return z * z + c;
}

float is_in_fractal(float complex (* zn)(float complex, float complex), float complex c, int max_iter, float escape_rad)
{
  float complex z = 0.0f + I * 0.0f;
  for (int i = 0; i < max_iter; i++) {
    z = zn(z, c);
    if (cabsf(z) > escape_rad)
      return i;
  }
  return 0;
}

int main()
{
  int max_iter = 250;
  float escape_rad = 10.0f;
  InitWindow(WIDTH, HEIGHT, "mandelbrot set");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground((Color) { 0.0f, 0.0f, 0.0f, 1.0f });
    for (int px = 0; px < WIDTH; px++) {
      for (int py = 0; py < HEIGHT; py++) {
        float x = -2.0 + 4.0 * px / WIDTH;
        float y = -2.0 + 4.0 * py / HEIGHT;

        float complex c = x + I * y;
        int iter = is_in_fractal(mandelbrot, c, max_iter, escape_rad);

        Color color;
        if (iter == 0)
          color = BLACK;
        else {
          float r = (5 * iter) % 255;
          float g = (5 * iter) % 255;
          float b = (10 * iter) % 255;
          color = (Color) { r, g, b, 255 };
        }
        DrawPixel(px, py, color);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
