#ifndef DRAWING_H
#define DRAWING_H

#include <cairo/cairo.h>
#include "utils.h"

void draw_area(cairo_t *context, Point * points, int x, int y, double a, Color color);

void draw_line(cairo_t *context, Point * points, int x, int y, int z, double a, Color color);

void create_point(cairo_t *context, Point * points, int x, int y, int z, double a, Color color);

void write_text(cairo_t *context, const char *string, int x, int y, double a, Color color);

#endif
