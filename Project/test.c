#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eps.h"
int main()
{
	Color clr;
	clr.red = 0;
	clr.blue = 0;
	clr.green = 0;

	/* ---------------------------------------------------- draw_fx function test ---------------------------------------- */

	Figure *fig = start_figure(400.0, 400.0);
	set_thickness_resolution(fig, 50, 0.5);	  
	set_color(fig, clr);
	fig->text = NULL;
	fig->point = NULL;

	draw_fx(fig,cos,0,100,0);
 	export_eps(fig,"draw_fx.eps");

	/* ---------------------------------------------------- draw_polyline function test ---------------------------------- */

	Figure *fig2 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig2, 50, 0.5);	  
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
	set_thickness_resolution(fig3, 50, 0.5);	  
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
	set_thickness_resolution(fig4, 50, 0.5);	  
	set_color(fig4, clr);
	fig4->point = NULL;
	fig4->text = NULL;
	fig4->point = NULL;

	Point2D *centre = (Point2D*)malloc(sizeof(Point2D));
	centre->x = 34; // optional choose , can be changed
	centre->y = 34; // optional choose , can be changed

	Point2D *width_height = (Point2D*)malloc(sizeof(Point2D));
	width_height->x = 20; // optional choose , can be changed
	width_height->y = 40; // optional choose , can be changed

	draw_ellipse(fig4,centre,width_height);
	export_eps(fig4,"draw_ellipse.eps");
	


	/* ----------------------------------------------------- draw_binary_tree function test ------------------------------------ */

	Figure *fig5 = start_figure(400.0, 400.0);
	set_thickness_resolution(fig5, 50, 0.5);
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
	


