#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FALSE 0
#define TRUE 1

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



Figure *start_figure(double width, double height)
{
	Figure *fig = (Figure *)malloc(sizeof(Figure));
	fig->urx = width / 2;
	fig->ury = height / 2;
	fig->llx = -width / 2;
	fig->lly = -height / 2;
	return fig;
}

void set_thickness_resolution(Figure *fig, double resolution, double thickness)
{
	fig->resolution = resolution;
	fig->thickness = thickness;
}

void set_color(Figure *fig, Color col)
{
	fig->color.blue = col.blue;
	fig->color.red = col.red;
	fig->color.green = col.green;
}

void point_insert(Point2D *point, double x, double y, int FLAG)
{
	point->x = x;
	point->y = y;
	point->flag = FLAG;
}


void draw_fx(Figure *fig, double f(double x), double start_x, double end_x, double step_size)
{
	Point2D *point = (Point2D *)malloc(sizeof(Point2D));
	point->x = start_x;
	point->y = f(start_x);
	point->flag = 1; // flag 'move to' 
	point->next = NULL;

	Point2D *temp = (Point2D *)malloc(sizeof(Point2D));
	temp = point;

	double i = 0;
	for (i = start_x + 1 / fig->resolution; i <= end_x; i += 1 / fig->resolution) // adding all the points between start_x and end_x (increasing in multiplies of resolution)
	{
		temp->next = (Point2D *)malloc(sizeof(Point2D));
		temp = temp->next;
		point_insert(temp, i, f(i), 0);
		temp->next = NULL;
	}
	
	temp->next = (Point2D *)malloc(sizeof(Point2D)); // adding the last point
	temp = temp->next;
	point_insert(temp, end_x, f(end_x), 0);
	temp->next = NULL;

	if (fig->point != NULL) // if figure has already points, we must go to the last addres of these points
	{
		Point2D *showpo = (Point2D *)malloc(sizeof(Point2D));
		showpo = fig->point;

		while (showpo->next != NULL)
			showpo = showpo->next;
		
		showpo->next = (Point2D *)malloc(sizeof(Point2D));
		showpo->next = point; // when we arrive, merging the points that was created with the function to the figure->point's last addres.
	}

	else
	{
		fig->point = point;
	}
}

void append_figures(Figure *fig, Figure *fig2) // this function merges points of the figure on the right to the figure on the left
{

	if (fig->point == NULL)
	{
		Point2D *pointfig2 = (Point2D *)malloc(sizeof(Point2D));
		pointfig2 = fig2->point;
		fig->point = pointfig2;
		fig->point->flag = 1;
		return;
	}

	Point2D *pointfig1 = (Point2D *)malloc(sizeof(Point2D));
	Point2D *pointfig2 = (Point2D *)malloc(sizeof(Point2D));
	pointfig2 = fig2->point;
	pointfig1 = fig->point;

	while (pointfig1->next != NULL)
	{
		pointfig1 = pointfig1->next;
	}
	pointfig1->next = (Point2D *)malloc(sizeof(Point2D));
	pointfig1->next = pointfig2;
	pointfig1->next->flag = 1;

}

void draw_ellipse(Figure *fig, Point2D *centre, Point2D *width_height)
{
	Figure *fig2 = (Figure *)malloc(sizeof(Figure));
	fig2->text = NULL;
	fig2->color = fig->color;
	fig2->llx = fig->llx;
	fig2->lly = fig->lly;
	fig2->urx = fig->urx;
	fig2->ury = fig->ury;
	fig2->resolution = fig->resolution;
	fig2->thickness = fig->thickness; // fig1 copied to fig2 to merge later.
	fig2->point = NULL;

	double width = width_height->x;
	double height = width_height->y;
	double start_x, end_x;
	start_x = -width_height->x; // center is assumed (0,0), will be shifted if necessary
	end_x = width_height->x;	// center is assumed (0,0), will be shifted if necessary

	double pos_ellipse(double x) { return sqrt((1 - ((x * x) / (width * width))) * (height * height)); }
	double neg_ellipse(double x) { return -sqrt((1 - ((x * x) / (width * width))) * (height * height)); }
	draw_fx(fig, pos_ellipse, start_x, end_x, 0);
	draw_fx(fig2, neg_ellipse, start_x, end_x, 0);
	append_figures(fig, fig2);
	
	Point2D *point = (Point2D *)malloc(sizeof(Point2D));
	if (centre->x != 0 && centre->y != 0) // if the center is not (0,0), coordinates must be shifted. ->>
	{
		
		point = fig->point;
		while (point != NULL)
		{
			point->x += centre->x;
			point->y += centre->y;
			point = point->next;
		}
	}

	point = fig->point;
	while(point->next != NULL) point = point->next;

	point->next == NULL;


}

void text(Figure *fig, Text *text2)
{
	Text *texto = (Text *)malloc(sizeof(Text));
	texto = fig->text;
	if(texto==NULL)
	{
		texto=text2;
		return;
	}

	while (texto->next != NULL)
	{
		texto = texto->next;
	}

	texto->next = text2;
}

void end_point_instert(Figure *fig, double x, double y, int flag)
{
	Point2D *pointt = (Point2D*)malloc(sizeof(Point2D));
	pointt = fig->point;
	while (pointt->next!=NULL) pointt = pointt->next;

	Point2D *new = (Point2D*)malloc(sizeof(Point2D));
	new->x = x;
	new->y = y;
	new->flag = flag;

	pointt->next = new;
}


void draw_binary_tree(Figure *fig, Tree *tree, double center_x, double center_y)
{
	if (tree == NULL)
		return;
	int radius = 10; // optional choosing, can be changed
	Point2D *center = (Point2D *)malloc(sizeof(Point2D));
	center->x = center_x;
	center->y = center_y;

	Point2D *width_height = (Point2D *)malloc(sizeof(Point2D));
	width_height->x = radius;
	width_height->y = radius;

	Figure *fig2 = (Figure *)malloc(sizeof(Figure));
	fig2->color = fig->color;
	fig2->llx = fig->llx;
	fig2->lly = fig->lly;
	fig2->urx = fig->urx;
	fig2->ury = fig->ury;
	fig2->resolution = fig->resolution;
	fig2->thickness = fig->thickness; // fig1 copied to fig2 to merge later.
	fig2->point = NULL;
	fig2->text = NULL;


	Text *texto = (Text *)malloc(sizeof(Text));
	texto->number = tree->number;
	texto->x = center_x - radius / 3;
	texto->y = center_y;
	texto->next = NULL;

	if (fig->text == NULL)
		fig->text = texto;

	else text(fig, texto);

	draw_ellipse(fig2, center, width_height);
	append_figures(fig, fig2);



	if (tree->branch1 != NULL)
	{
		end_point_instert(fig,center_x,center_y-radius,1); // drawing arms
		end_point_instert(fig,center_x - radius * 3,(center_y - radius * 3)+radius,0); // drawing arms
		draw_binary_tree(fig, tree->branch1, center_x - radius * 3, center_y - radius * 3); // go to left branch ->
	}
		
	if (tree->branch2 != NULL)
	{
		end_point_instert(fig,center_x,center_y-radius,1); // drawing arms
		end_point_instert(fig,center_x + radius * 3,(center_y - radius * 3)+radius,0); // drawing arms
		draw_binary_tree(fig, tree->branch2, center_x + radius * 3, center_y - radius * 3); // go to left branch ->
	}
		

}

void draw_polygon(Figure *fig, Point2D *poly_line) // merges the last point to the first point, and merges this point struct to fig->point
{
	Point2D *temp1 = (Point2D *)malloc(sizeof(Point2D));
	Point2D *temp2 = (Point2D *)malloc(sizeof(Point2D));
	temp1 = poly_line;
	temp2 = poly_line;
	temp1 = temp2;

	while (temp1->next != NULL)
	{
		temp1 = temp1->next;
	}

	temp1->next = (Point2D *)malloc(sizeof(Point2D));
	temp1 = temp1->next;
	temp1->x = temp2->x;
	temp1->y = temp2->y;
	temp1->flag = temp2->flag;

	fig->point = temp2;
}

void draw_polyline(Figure *fig, Point2D *point, int n)
{
	Point2D *temp = (Point2D *)malloc(sizeof(Point2D));
	temp->x = point[0].x;
	temp->y = point[0].y;
	temp->flag = 0;
	temp->next = NULL;

	Point2D *p = (Point2D *)malloc(sizeof(Point2D));
	p = temp;

	temp->next = (Point2D *)malloc(sizeof(Point2D));
	temp = temp->next;

	int i = 1;
	while (i < n)
	{
		temp->x = point[i].x;
		temp->y = point[i].y;
		temp->flag = 0;
		temp->next = NULL;
		if (i == (n - 1))
			break;
		temp->next = (Point2D *)malloc(sizeof(Point2D));
		temp = temp->next;
		i++;
	}

	fig->point = p;
}

void export_eps(Figure *fig, char *filename)
{
	FILE *file;
	file = fopen(filename, "wt");

	

	fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0");
	fprintf(file, "\n%%%%BoundingBox: %d %d %d %d", (int)fig->llx, (int)fig->lly, (int)fig->urx, (int)fig->ury);
	fprintf(file, "\n%d setlinewidth", (int)fig->thickness);
	fprintf(file, "\n%.1f %.1f %.1f setrgbcolor", fig->color.red, fig->color.green, fig->color.blue);

	if (fig->text != NULL)
	{
		fprintf(file, "\n/Times-Roman findfont\n5 scalefont\nsetfont");
		while (fig->text != NULL)
		{
			fprintf(file, "\n%d %d moveto", (int)fig->text->x, (int)fig->text->y);
			fprintf(file, "\n(%d) show", fig->text->number);
			fig->text = fig->text->next;
		}
	}


	fprintf(file, "\n%.1f %.1f moveto", fig->point->x, fig->point->y); // move to starting point
	Point2D *point = (Point2D *)malloc(sizeof(Point2D));
	point = fig->point->next;

	while (point != NULL)
	{
		fprintf(file, "\n%.1f %.1f ", point->x, point->y);
		if (point->flag == 1)
			fprintf(file, "moveto");
		else
			fprintf(file, "lineto");

		point = point->next;
	}
	fprintf(file, "\nstroke\n");
	fclose(file);
}

void scale_figure(Figure *fig, double scale_x, double scale_y)
{
	Point2D *point = (Point2D *)malloc(sizeof(Point2D));
	point = fig->point;
	while (point != NULL)
	{
		point->x *= scale_x;
		point->y *= scale_y;
		point = point->next;
	}
}

void resize_figure(Figure *fig, Point2D *start_roi, Point2D *end_roi)
{
	fig->llx = start_roi->x;
	fig->lly = start_roi->y;

	fig->urx = end_roi->x;
	fig->ury = end_roi->y;
}



int main()
{
	Color clr;
	clr.red = 0;
	clr.blue = 0;
	clr.green = 0;

	/* ---------------------------------------------------- draw_fx function test ---------------------------------------- */

	Figure *fig = start_figure(400.0, 400.0);
	set_thickness_resolution(fig, 50, 1);	  
	set_color(fig, clr);
	fig->text = NULL;
	fig->point = NULL;

	draw_fx(fig,cos,0,100,0);
 	export_eps(fig,"draw_fx.eps");

	/* ---------------------------------------------------- draw_polyline function test ---------------------------------- */

	Figure *fig2 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig2, 50, 1);	  
	set_color(fig2, clr);
	fig2->text = NULL;
	fig2->point = NULL;

	int size = 9; // optional choose, can be changed.  it shows that how many numbers there are
	Point2D *arr_poly= (Point2D*)malloc(size*sizeof(Point2D));
	for(int i=0;i<size;i++){
		arr_poly[i].x=i;
		arr_poly[i].y=i*i;
		arr_poly[i].flag = 0;
	}
	draw_polyline(fig2,arr_poly,size);
	export_eps(fig2,"arr_poly.eps");

	/* ---------------------------------------------------- draw_polygon function test ------------------------------------- */

	Figure *fig3 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig3, 50, 1);	  
	set_color(fig3, clr);
	fig3->point = NULL;
	fig3->text = NULL;

	size = 3; // optional choose, can be changed. it shows that how many numbers there are
	Point2D *arr_polyy= (Point2D*)malloc(sizeof(Point2D));
	Point2D *arr_poly2= (Point2D*)malloc(sizeof(Point2D)); // it will show the first point's addres.
	arr_polyy = arr_poly2;

	for(int i=0;i<size;i++){
		arr_polyy->x=i* 10;
		arr_polyy->y=i*i * 10;
		arr_polyy->flag = 0;
		if (i==8)
		{
			arr_polyy->next = NULL;
			break;
		}
		arr_polyy->next = (Point2D*)malloc(sizeof(Point2D));
		arr_polyy = arr_polyy->next;
	}
	arr_polyy = arr_poly2;

	draw_polygon(fig3,arr_poly2);
	export_eps(fig3,"draw_polygon.eps");

	/* ---------------------------------------------------- draw_ellipse function test ---------------------------------------- */

	Figure *fig4 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig4, 50, 1);	  
	set_color(fig4, clr);
	fig4->point = NULL;
	fig4->text = NULL;
	fig4->point = NULL;

	Point2D *centre = (Point2D*)malloc(sizeof(Point2D));
	centre->x = 34; // optional choose , can be changed
	centre->y = 34; // optional choose , can be changed

	Point2D *width_height = (Point2D*)malloc(sizeof(Point2D));
	width_height->x = 20; // optional choose , can be changed
	width_height->y = 20; // optional choose , can be changed

	draw_ellipse(fig4,centre,width_height);
	export_eps(fig4,"draw_ellipse.eps");
	


	/* ----------------------------------------------------- draw_binary_tree function test ------------------------------------ */

	Figure *fig5 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig5, 50, 1);
	set_color(fig5, clr);
	fig5->text = NULL;
	fig5->point = NULL;

	// making tree
	Tree *node = (Tree *)malloc(sizeof(Tree));
	node->number = 10;
	node->branch1 = (Tree *)malloc(sizeof(Tree));
	node->branch1->number = 20;
	node->branch1->rightleftflag = 0;
	node->branch2 = (Tree *)malloc(sizeof(Tree));
	node->branch2->number = 30;
	node->branch2->rightleftflag = 0;
	node->branch1->branch1 = NULL;
	node->branch1->branch2 = NULL;
	node->branch2->branch1 = NULL;
	node->branch2->branch1 = NULL;

	draw_binary_tree(fig5, node, 1, 1);
	export_eps(fig5, "draw_binary_tree.eps");


	
	return 0;
}
