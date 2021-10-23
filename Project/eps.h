#ifndef EPS_H
#define EPS_H

typedef struct Tree
{
	int number;
	struct Tree *branch1; //left
	struct Tree *branch2; //right
	int rightleftflag;

} Tree;

typedef struct Point2D
{
	double x, y;
	struct Point2D *next;
	int flag; // indicates jump to a point without drawing.
} Point2D;

typedef struct Colors
{
	double red, green, blue; 
} Color;

typedef struct Text
{
	double x, y; 
	int number;		
	struct Text *next; 

} Text;

typedef struct Figure
{
	double llx, lly, urx, ury; // upper right and lower left coordinates
	double resolution;
	double thickness;
	Color color;
	Point2D *point;
	Text *text;
} Figure;

Figure *start_figure(double width, double height);
void set_thickness_resolution(Figure *fig, double resolution, double thickness);
void set_color(Figure *fig, Color col);
void point_insert(Point2D *point, double x, double y, int FLAG);
void draw_fx(Figure *fig, double f(double x), double start_x, double end_x, double step_size);
void append_figures(Figure *fig, Figure *fig2);
void draw_ellipse(Figure *fig, Point2D *centre, Point2D *width_height);
void insert_text(Figure *fig, Text *text2);
void end_point_instert(Figure *fig, double x, double y, int flag);
void draw_binary_tree(Figure *fig, Tree *tree, double center_x, double center_y);
void draw_polygon(Figure *fig, Point2D *poly_line);
void draw_polyline(Figure *fig, Point2D *point, int n);
void export_eps(Figure *fig, char *filename);
void scale_figure(Figure *fig, double scale_x, double scale_y);
void resize_figure(Figure *fig, Point2D *start_roi, Point2D *end_roi);

#endif

