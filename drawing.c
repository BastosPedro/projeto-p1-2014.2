#include "drawing.h"

void draw_area(cairo_t *context, Point * points, int x, int y, double a, Color color) {
    cairo_save(context);
    cairo_set_line_width (context, 1.5*a);
    cairo_set_source_rgba (context, color.r,
                                    color.g,
                                    color.b,
                                    color.a);
    cairo_move_to(context, points[0].x - x*0.02, points[0].y + y*0.02);    
    cairo_stroke(context);
    int i = 0;
    for(; points[i].x > 0; i++) {
        cairo_line_to(context, points[i].x - x*0.02, points[i].y + y*0.02);
    }    	
    cairo_line_to(context, x - (x*0.02), y - (y*0.02));
    cairo_line_to(context, points[0].x - (x*0.02), y-(y*0.02));
    cairo_line_to(context, points[0].x - (x*0.02), points[0].y + (y*0.02)); 

    cairo_fill(context);
    cairo_stroke(context);
    cairo_restore(context);
}

void draw_line(cairo_t *context, Point * points, int x, int y, int z, double a, Color color){
    cairo_save(context);
    cairo_set_line_width (context, 1.5*a);
    cairo_set_source_rgba (context, 0, 0, 0, 1);
    cairo_arc(context, x*0.02, y*0.02, 3*a, 0, 2*360);
    cairo_fill(context);
    cairo_line_to(context, x*0.02, y*0.02);
    cairo_line_to(context, x*0.02, y-(y*0.02));
    cairo_line_to(context, x-(x*0.02), y-(y*0.02));
    cairo_stroke(context);
    cairo_arc(context, x-(x*0.02), y-(y*0.02), 3*a, 0, 2*360);
    cairo_fill(context);
    cairo_stroke(context);
    int i = 0;
    if(z==1){
        cairo_set_source_rgba (context, color.r,
                                        color.g,
                                        color.b,
                                        color.a);
        for(; points[i].x > 0; i++) {
        cairo_line_to(context, points[i].x - x*0.02, points[i].y + y*0.02);
        }
    }
    else if(z==2){
	    for(; points[i].x > 0; i++) {
        cairo_line_to(context, points[i].x - x*0.02, points[i].y + y*0.02);
        }
        cairo_line_to(context, x - (x*0.02), y - (y*0.02));
    	cairo_line_to(context, points[0].x - (x*0.02), y-(y*0.02));
    	cairo_line_to(context, points[0].x - (x*0.02), points[0].y + (y*0.02)); 
    }
    cairo_stroke(context);
    cairo_restore(context);
 
} 

void create_point(cairo_t *context, Point * points, int x, int y, int z, double a, Color color) {
    cairo_save(context);
    if (z==2) cairo_set_source_rgba (context, 0, 0, 0, 1);
    else cairo_set_source_rgba (context, color.r, 
                                         color.g, 
                                         color.b, 
                                         color.a);
    int i = 0;
    for(; points[i].x > 0; i++) {
        cairo_arc(context, points[i].x - x*0.02, points[i].y + y*0.02, 2.5*a, 0, 2*360);
        cairo_fill (context);
        cairo_stroke(context);
        }
    cairo_restore(context);
}
void write_text(cairo_t *context, const char *string, int x, int y, double a, Color color) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r,
                                    color.g, 
                                    color.b,
                                    color.a);
    cairo_move_to(context, (x*0.01), (y*0.03));
    cairo_set_font_size(context, 5.5*a);
    cairo_show_text (context, "Y");
    cairo_move_to(context, x-(x*0.03), y-(y*0.01));
    cairo_show_text (context, "X");
    cairo_set_source_rgba (context, 0, 0, 0, 1);
    cairo_move_to(context, ((x/2) - (x*0.05)), (0 + (y*0.05)));
    cairo_set_font_size (context, 10.0*a);
    cairo_show_text (context, string);
    cairo_stroke(context);
    cairo_restore(context);
}
    
    
