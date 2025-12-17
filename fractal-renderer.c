#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <raylib.h>

#define WIDTH  1500
#define HEIGHT (WIDTH / 16 * 10)

float complex mandelbrot(float complex z, float complex c)
{
  return z * z + c;
}

float complex burning_ship(float complex z, float complex c)
{
    float zr = fabsf(crealf(z));
    float zi = fabsf(cimagf(z));
    float complex w = zr + I * zi;
    return w * w + c;
}

float complex mandelbar(float complex z, float complex c)
{
    return conjf(z) * conjf(z) + c;
}

float complex julia(float complex z, float complex c)
{
    return z * z * z + c;
}

float is_in_fractal(float complex (* zn)(float complex, float complex), float complex c, int max_iter, float escape_rad)
{
  float complex z = 0.0f + I * 0.0f;
  float zr, zc;
  for (int i = 0; i < max_iter; i++) {
    z = zn(z, c);
    zr = crealf(z);
    zc = cimagf(z);
    if (zr * zr + zc * zc > escape_rad * escape_rad)
      return i;
  }
  return 0;
}

int is_in_julia(float complex (* zn)(float complex, float complex), float complex z0, float complex c, int max_iter, float escape_rad)
{
    float complex z = z0;
    float zr, zc;
    for (int i = 0; i < max_iter; i++) {
        z = zn(z, c);
        zr = crealf(z);
        zc = cimagf(z);
        if (zr * zr + zc * zc > escape_rad*escape_rad)
            return i;
    }
    return 0;
}

int main()
{
  int max_iter = 100;
  float escape_rad = 2.0f;

  InitWindow(WIDTH, HEIGHT, "fractal-renderer");
  SetTargetFPS(60);

  Image img = GenImageColor(WIDTH, HEIGHT, BLACK);
  Texture2D tex = LoadTextureFromImage(img);

  Color *pixels = (Color *)img.data;

  float x = 0.0f, y = 0.0f;
  float dx = 4.0f / WIDTH;
  float dy = 4.0f / HEIGHT;

  float t;
  float complex julia_c;
  int iter;

  while(!WindowShouldClose()) {
    t = GetTime();
    julia_c = 0.9f * cosf(t) + 0.4f * sinf(t) * I;

    BeginDrawing();
    ClearBackground((Color) { 0.0f, 0.0f, 0.0f, 1.0f });


    float complex z0;
    float complex c;

    for (int px = 0; px < WIDTH; px++) {
      for (int py = 0; py < HEIGHT; py++) {

        x = -2.0 + px * dx;
        y = -2.0 + py * dy;

        c = x + I * y;

        iter = is_in_fractal(mandelbrot, c, max_iter, escape_rad);
        z0 = x + I * y;
        // iter = is_in_julia(julia, z0, julia_c, max_iter, escape_rad);

        Color color;
        if (iter == 0)
          color = BLACK;
        else {
          float r = (2 * iter) % 255;
          float g = (2 * iter) % 255;
          float b = (12 * iter) % 255;
          color = (Color) { r, g, b, 255 };
        }
        pixels[py * WIDTH + px] = color;
      }
    }
    UpdateTexture(tex, pixels);
    DrawTexture(tex, 0, 0, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
