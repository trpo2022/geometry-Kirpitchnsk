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
    c[i] = "";
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
bool check_point(double *x, double *y, double x0, double y0) {
  double a = (x[0] - x0) * (y[1] - y[0]) - (x[1] - x[0]) * (y[0] - y0);
  double b = (x[1] - x0) * (y[2] - y[1]) - (x[2] - x[1]) * (y[1] - y0);
  double c = (x[2] - x0) * (y[0] - y[2]) - (x[0] - x[2]) * (y[2] - y0);
  if (a * b * c == 0) {
    return 0;
  }
  return ((signbit(a) ^ signbit(b)) || (signbit(a) ^ signbit(c)));
}
double distance_from_dot_to_line(double x0, double y0, double x1, double y1,
                                 double x2, double y2) {
  double A = y2 - y1;
  double B = x1 - x2;
  double C = y1 * x2 + x1 * y2;
  double d = (A * x0 + B * y0 + C) / sqrt(A * A + B * B);
  return d;
}
bool line_intersection(double x1, double x2, double y1, double y2, double x3,
                       double x4, double y3, double y4) {
  double A1 = y2 - y1;
  double B1 = x1 - x2;
  double C1 = y1 * x2 + x1 * y2;
  double A2 = y4 - y3;
  double B2 = x3 - x4;
  double C2 = y3 * x4 + x3 * y4;
  if (A1 * B2 - B1 * A2 == 0) {
    return false;
  } else {
    double x = ((B1 * C2 - C1 * B2) / (A1 * B2 - B1 * A2));
    double y = ((C1 * A2 - A1 * C2) / (A1 * B2 - B1 * A2));
    if (((abs(x - x1) + abs(x - x2) == abs(x1 - x2)) &&
         (abs(y - y1) + abs(y - y2) == abs(y1 - y2))) &&
        ((abs(x - x3) + abs(x - x4) == abs(x3 - x4)) &&
         (abs(y - y3) + abs(y - y4) == abs(y3 - y4)))) {
      return true;
    } else {
      return false;
    }
  }
}
void intersection(struct shape f[], int o, int num) {
  int i, j, w, e;
  double d, D;
  bool intersect = false;
  switch (f[o].fnumber) {
    case 1: {
      for (i = 0; i < num; i++) {
        switch (f[i].fnumber) {
          case 1: {
            d = side(f[i].one[f[i].countfigure].x, f[i].one[f[i].countfigure].y,
                     f[o].one[f[o].countfigure].x,
                     f[o].one[f[o].countfigure].y);
            if (d == 0) {
              intersect = true;
            }
            if (d <= f[i].one[f[i].countfigure].rradius +
                         f[o].one[f[o].countfigure].rradius) {
              intersect = true;
            }
            if (d < abs(f[i].one[f[i].countfigure].rradius -
                        f[o].one[f[o].countfigure].rradius)) {
              intersect = false;
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.circle\n", i + 1);
            }
            break;
          }
          case 2: {
            for (j = 0; j < 3; j++) {
              D = distance_from_dot_to_line(
                  f[o].one[f[o].countfigure].x, f[o].one[f[o].countfigure].y,
                  f[i].two[f[i].countfigure].xsides[j],
                  f[i].two[f[i].countfigure].ysides[j],
                  f[i].two[f[i].countfigure].xsides[j + 1],
                  f[i].two[f[i].countfigure].ysides[j + 1]);
              if (D <= f[o].one[f[o].countfigure].rradius) {
                intersect = true;
                break;
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.triangle\n", i + 1);
            }
            break;
          }
          case 3: {
            for (j = 0; j < f[i].three[f[i].countfigure].sidenumber; j++) {
              D = distance_from_dot_to_line(
                  f[o].one[f[o].countfigure].x, f[o].one[f[o].countfigure].y,
                  f[i].three[f[i].countfigure].xxsides[j],
                  f[i].three[f[i].countfigure].yysides[j],
                  f[i].three[f[i].countfigure].xxsides[j + 1],
                  f[i].three[f[i].countfigure].yysides[j + 1]);
              if (D <= f[o].one[f[o].countfigure].rradius) {
                intersect = true;
                break;
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.polygon\n", i + 1);
            }
            break;
          }
          default: {
            break;
          }
        }
        intersect = false;
      }
    }
    case 2: {
      for (i = 0; i < num; i++) {
        switch (f[i].fnumber) {
          case 1: {
            for (j = 0; j < 3; j++) {
              D = distance_from_dot_to_line(
                  f[i].one[f[i].countfigure].x, f[i].one[f[i].countfigure].y,
                  f[o].two[f[o].countfigure].xsides[j],
                  f[o].two[f[o].countfigure].ysides[j],
                  f[o].two[f[o].countfigure].xsides[j + 1],
                  f[o].two[f[o].countfigure].ysides[j + 1]);
              if (D <= f[i].one[f[i].countfigure].rradius) {
                intersect = true;
                break;
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.circle\n", i + 1);
            }
            break;
          }
          case 2: {
            for (j = 0; j < 3; j++) {
              if (!check_point(f[i].two[f[i].countfigure].xsides,
                               f[i].two[f[i].countfigure].ysides,
                               f[o].two[f[o].countfigure].xsides[j],
                               f[o].two[f[o].countfigure].ysides[j])) {
                intersect = true;
                break;
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.triangle\n", i + 1);
            }
            break;
          }
          case 3: {
            for (w = 0; w < 3; w++) {
              for (e = 0; e < f[i].three[f[i].countfigure].sidenumber; e++) {
                if (line_intersection(
                        f[o].two[f[o].countfigure].xsides[w],
                        f[o].two[f[o].countfigure].xsides[w + 1],
                        f[o].two[f[o].countfigure].ysides[w],
                        f[o].two[f[o].countfigure].ysides[w + 1],
                        f[i].three[f[i].countfigure].xxsides[e],
                        f[i].three[f[i].countfigure].xxsides[e + 1],
                        f[i].three[f[i].countfigure].yysides[e],
                        f[i].three[f[i].countfigure].yysides[e + 1])) {
                  intersect = true;
                  break;
                }
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.polygon\n", i + 1);
            }
            break;
          }
          default: {
            break;
          }
        }
        intersect = false;
      }
    }
    case 3: {
      for (i = 0; i < num; i++) {
        switch (f[i].fnumber) {
          case 1: {
            for (j = 0; j < f[o].three[f[o].countfigure].sidenumber; j++) {
              D = distance_from_dot_to_line(
                  f[i].one[f[i].countfigure].x, f[i].one[f[i].countfigure].y,
                  f[o].three[f[o].countfigure].xxsides[j],
                  f[o].three[f[o].countfigure].yysides[j],
                  f[i].three[f[o].countfigure].xxsides[j + 1],
                  f[o].three[f[o].countfigure].yysides[j + 1]);
              if (D <= f[i].one[f[i].countfigure].rradius) {
                intersect = true;
                break;
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.circle\n", i + 1);
            }
            break;
          }
          case 2: {
            for (w = 0; w < 3; w++) {
              for (e = 0; e < f[o].three[f[o].countfigure].sidenumber; e++) {
                if (line_intersection(
                        f[i].two[f[i].countfigure].xsides[w],
                        f[i].two[f[i].countfigure].xsides[w + 1],
                        f[i].two[f[i].countfigure].ysides[w],
                        f[i].two[f[i].countfigure].ysides[w + 1],
                        f[o].three[f[o].countfigure].xxsides[e],
                        f[o].three[f[o].countfigure].xxsides[e + 1],
                        f[o].three[f[o].countfigure].yysides[e],
                        f[o].three[f[o].countfigure].yysides[e + 1])) {
                  intersect = true;
                  break;
                }
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.triangle\n", i + 1);
            }
            break;
          }
          case 3: {
            for (w = 0; w < f[i].three[f[i].countfigure].sidenumber; w++) {
              for (e = 0; e < f[o].three[f[o].countfigure].sidenumber; e++) {
                if (line_intersection(
                        f[o].three[f[o].countfigure].xxsides[w],
                        f[o].three[f[o].countfigure].xxsides[w + 1],
                        f[o].three[f[o].countfigure].yysides[w],
                        f[o].three[f[o].countfigure].yysides[w + 1],
                        f[i].three[f[i].countfigure].xxsides[e],
                        f[i].three[f[i].countfigure].xxsides[e + 1],
                        f[i].three[f[i].countfigure].yysides[e],
                        f[i].three[f[i].countfigure].yysides[e + 1])) {
                  intersect = true;
                  break;
                }
              }
            }
            if ((intersect == true) && (i != o)) {
              printf("%d.triangle\n", i + 1);
            }
            break;
          }
          default: {
            break;
          }
        }
        intersect = false;
      }
    }
    default: {
      break;
    }
  }
}
void print(struct shape f[], int i) {
  int i1;
  for (i1 = 0; i1 < i; i1++) {
    printf("%s", f[i1].string);
    switch (f[i1].fnumber) {
      case 1: {
        printf("perimeter = %5.4lf\narea = %5.4lf\n",
               f[i1].one[f[i1].countfigure].pperimeter,
               f[i1].one[f[i1].countfigure].aarea);
        printf("intersects:\n");
        intersection(f, i1, i);
        puts("\n");
        break;
      }
      case 2: {
        printf("perimeter = %5.4lf\narea = %5.4lf\n",
               f[i1].two[f[i1].countfigure].ppperimeter,
               f[i1].two[f[i1].countfigure].aaarea);
        printf("intersects:\n");
        intersection(f, i1, i);
        puts("\n");
        break;
      }
      case 3: {
        printf("perimeter = %5.4lf\narea = %5.4lf\n",
               f[i1].three[f[i1].countfigure].pppperimeter,
               f[i1].three[f[i1].countfigure].aaaarea);
        printf("intersects:\n");
        intersection(f, i1, i);
        puts("\n");
        break;
      }
      default: {
        break;
      }
    }
  }
}
