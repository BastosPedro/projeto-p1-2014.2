#include "storage.h"

int JSON_getInt(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_integer_value(jVal);
}

const char * JSON_getString(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_string_value(jVal);
}

/*int JSON_getBool(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_is_true(jVal);
}*/

Color JSON_getColor(json_t *root) {
    Color c;
    json_t *jColor = json_object_get(root, "color");
    json_t * jItem0 = json_array_get(jColor, 0);
    c.r = json_integer_value(jItem0)/255.0;
    json_t * jItem1 = json_array_get(jColor, 1);
    c.g = json_integer_value(jItem1)/255.0;
    json_t * jItem2 = json_array_get(jColor, 2);
    c.b = json_integer_value(jItem2)/255.0;
    json_t * jItem3 = json_array_get(jColor, 3);
    c.a = json_integer_value(jItem3)/255.0;
    return c;
}

Point * JSON_getPoints(json_t *root) {
    json_t *jPoints = json_object_get(root, "points");
    Point * points = malloc(sizeof(Point)*json_array_size(jPoints));
    double alphax = 0, alphay = 0; 
    double borderx = 0.02*JSON_getInt(root, "width"); 
    double bordery = 0.02*JSON_getInt(root, "height");
    int i, width = JSON_getInt(root, "width"), height = JSON_getInt(root, "height");
    for(i = 0; i < json_array_size(jPoints); ++i){
    	json_t * jPoint = json_array_get(jPoints, i);
    	json_t *jX = json_object_get(jPoint, "x");
    	points[i].x = json_integer_value(jX);
	if (points[i].x > alphax) alphax = points[i].x;
    	json_t *jY = json_object_get(jPoint, "y");
        points[i].y = json_integer_value(jY);
	if (points[i].y > alphay) alphay = points[i].y;
    } 
    for(i = 0; i< json_array_size(jPoints); ++i){
	points[i].x = points[i].x * (width/alphax);
	points[i].y = 1.1*(height) - (points[i].y * (height/alphay));
    }	
    return points;
}
