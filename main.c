#include <stdio.h>
#include <string.h>
#include <cairo/cairo-pdf.h>
#include "storage.h"
#include "drawing.h"

int main() {
    json_t *root;
    json_error_t error;
    root = json_load_file("../test.json", 0, &error);
    if(root == 0){
        printf("ERRO AO LER ARQUIVO, linha %d!\n", error.line);
        return error.line;
    }
    const char * fileName = JSON_getString(root, "fileName");
    printf("O nome do arquivo é: %s\n", fileName); 
    const char * format = JSON_getString(root, "format");
    if(strcmp(format, "png") != 0 && strcmp(format, "pdf") != 0 ){
        printf("Formato: o formato %s não é  suportado!\n", format);
        return 0;
    }
    printf("O formato é: %s\n", JSON_getString(root, "format"));
    const char * name = JSON_getString(root, "name");
    printf("O titulo do grafico é: %s\n", name);
    int width = JSON_getInt(root, "width");
    if(width < 200 || width > 1000){
        printf("Width: medida não suportada!\n");
        return 0;
    }
    printf("Width: %d\n", width);
    int height = JSON_getInt(root, "height");
    if(height < 200 || height > 1000){
        printf("Height: medida não suportada!\n");
        return 0;
    }
    printf("Height: %d\n", height);
    int type = JSON_getInt(root, "type");
    printf("Type: %d\n", type);
    double aux;
    //aux = height/width;
    if(height>width) aux = (width/200);
    else aux = (height/200);   
            
    cairo_surface_t *surface; 
    if(strcmp(format, "png") == 0){
 	    surface =   	
	    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    }
    else{
        surface =
        cairo_pdf_surface_create(fileName, width, height);
    }
    cairo_t *context = cairo_create(surface);

    cairo_set_source_rgba(context, 1, 1, 1, 1);
    cairo_rectangle(context, 0, 0, width, height);
    cairo_fill(context);        

    Color pointColor = JSON_getColor(root);
    Point *points = JSON_getPoints(root);
    if(type == 0 || type == 1) create_point(context, points, width, height, type, aux, pointColor); 
    
    if (type==2) {
        draw_area(context, points, width, height, aux, pointColor);
        create_point(context, points, width, height, type, aux, pointColor);
    }
    
    draw_line(context, points, width, height, type, aux, pointColor);
    
    write_text(context, name, width, height, aux, pointColor);

    if(strcmp(JSON_getString(root, "format"), "png") == 0)	cairo_surface_write_to_png(surface, fileName);
    else cairo_show_page(context); 
    	
    cairo_destroy(context);
    cairo_surface_destroy(surface);
    
        
    return 0;
}
