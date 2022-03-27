#include <libgeometry/functions.h>
#include <stdio.h>
int ukazatel(char c[], char p, int i) {
  int ukaz = 0;
  while (c[i] != '\0') {
    if (c[i] == p) {
      ukaz = i;
      break;
    }
    i++;
  }
  return ukaz;
}
int countelement(char c[], char p) {
  int count = 0;
  int i = 0;
  while (c[i] != '\0') {
    if (c[i] == p) {
      count++;
    }
    i++;
  }
  return count;
}
double side(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double area_of_circle(double radius) { return pi * pow(radius, 2); }
double area_of_triangle(double a, double b, double c) {
  double halfperimeter = (a + b + c) / 2;
  double area = sqrt(halfperimeter * (halfperimeter - a) * (halfperimeter - b) *
                     (halfperimeter - c));
  return area;
}
void make_string_null(char c[]) {
  int i;
  for (i = 0; i < strlen(c); i++) {
    c[i] = ' ';
  }
}
bool num_check(char c[]) {
  int i, k = 0;
  for (i = ukazatel(c, '(', 0); i < ukazatel(c, ')', 0); i++) {
    if (!isdigit(c[i]) && !isspace(c[i]) && !ispunct(c[i])) {
      k++;
    }
  }
  if (k > 0) {
    return false;
  } else {
    return true;
  }
}
