#pragma once
int ukazatel(char c[], char p, int i);
int countelement(char c[], char p);
double side(double x1, double y1, double x2, double y2);
double area_of_circle(double radius);
double area_of_triangle(double a, double b, double c);
void make_string_null(char c[]);
int num_check(char c[]);
int check_point(double *x, double *y, double x0, double y0);
double distance_from_dot_to_line(double x0, double y0, double x1, double y1, double x2, double y2);
int line_intersection(double x1, double x2, double y1, double y2, double x3, double x4, double y3, double y4);
void intersection(struct shape f[], int o, int num);
void print(struct shape f[], int i);