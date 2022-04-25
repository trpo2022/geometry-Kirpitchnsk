#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/functions.c>

int main() {
  FILE *S1;
  int i = 0;
  bool mistake = false;
  char arr[1000];
  struct shape f[50];
  if ((S1 = fopen("S1.txt", "r")) == NULL) {
    printf("Fatal: file can not open because does not excist");
    getchar();
    return 0;
  }
  S1 = fopen("S1.txt", "r");
  while (fgets(arr, 100, S1) != NULL) {
    int cirnum = 0, trinum = 0, polynum = 0;
    strcpy(f[i].string, arr);
    if ((strstr(arr, "circle") == NULL && !(strstr(arr, "triangle") != NULL ||
                                            strstr(arr, "polygon") != NULL)) ||
        (strstr(arr, "triangle") == NULL &&
         !(strstr(arr, "circle") != NULL || strstr(arr, "polygon") != NULL)) ||
        (strstr(arr, "polygon") == NULL &&
         !(strstr(arr, "circle") != NULL || strstr(arr, "triangle") != NULL))) {
      printf("\n%s\n", arr);
      printf("Error at column %d: expected 'circle, triangle or polygon'\n", i);
      mistake = true;
    }
    if ((countelement(arr, 'c') > 2 && !(strstr(arr, "triangle") != NULL ||
                                         strstr(arr, "polygon") != NULL)) ||
        (countelement(arr, 't') > 1 &&
         !(strstr(arr, "circle") != NULL || strstr(arr, "polygon") != NULL)) ||
        (countelement(arr, 'p') > 1 &&
         !(strstr(arr, "circle") != NULL || strstr(arr, "triangle") != NULL))) {
      printf("Error at column %d: expected 'circle, triangle or polygon'\n", i);
      mistake = true;
    }
    if (((countelement(arr, '(') == 0) || (countelement(arr, ')') == 0)) &&
        (strstr(arr, "circle") != NULL)) {
      printf("\n%s\n", arr);
      printf("Error at column %d: expected ')' or '('\n", i);
      mistake = true;
    }
    if (((strstr(arr, "((") == NULL) || ((strstr(arr, "))") == NULL))) &&
        (strstr(arr, "triangle") != NULL || strstr(arr, "polygon") != NULL)) {
      printf("\n%s\n", arr);
      printf("Error at column %d: expected ')' or '('\n", i);
      mistake = true;
    }
    if ((ukazatel(arr, ')', 8) + 3 < (int)(strlen(arr))) &&
        (strstr(arr, "circle") != 0)) {
      printf("\n%s\n", arr);
      printf("Error at column %d: unexpected token\n", i);
      mistake = true;
    }
    if ((ukazatel(arr, ')', (ukazatel(arr, ')', 8) + 1)) <
         (int)strlen(arr) - 3) &&
        ((strstr(arr, "triangle") != 0) || strstr(arr, "polygon") != 0)) {
      printf("\n%s\n", arr);
      printf("Error at column %d: unexpected token\n", i);
      mistake = true;
    }
    if (!num_check(arr)) {
      printf("\n%s\n", arr);
      printf("Error at column %d: expected '<double>'\n", i);
      mistake = true;
    }
    num_check(arr);
    if (!(mistake)) {
      int j, k = 0;
      double x1, y1, radius;
      if (strstr(arr, "circle") != NULL &&
          (strstr(arr, "triangle") == NULL || strstr(arr, "polygon") == NULL)) {
        f[i].fnumber = 1;
        f[i].countfigure = cirnum;
        int comma = ukazatel(arr, ',', 0);
        int space = ukazatel(arr, ' ', 0);
        char x1c[30] = "", y1c[30] = "", radiusc[30] = "";
        for (j = ukazatel(arr, '(', 0); j < space; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            x1c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        x1 = atof(x1c);
        for (j = space + 1; j < comma; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            y1c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        y1 = atof(y1c);
        for (j = comma + 1; j <= ukazatel(arr, ')', 0); j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            radiusc[k] = arr[j];
            k++;
          }
        }
        k = 0;
        radius = atof(radiusc);
        double perimeter = 2 * pi * radius;
        double area = area_of_circle(radius);
        f[i].one[cirnum].x = x1;
        f[i].one[cirnum].y = y1;
        f[i].one[cirnum].rradius = radius;
        f[i].one[cirnum].aarea = area;
        f[i].one[cirnum].pperimeter = perimeter;
        cirnum++;
      }
      if (strstr(arr, "triangle") != NULL &&
          (strstr(arr, "circle") == NULL || strstr(arr, "polygon") == NULL)) {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        int j, k = 0, space = 0, comma = 0;
        char x1c[30] = "", y1c[30] = "", x2c[30] = "", y2c[30] = "",
             x3c[30] = "", y3c[30] = "", x4c[30] = "", y4c[30] = "";
        f[i].fnumber = 2;
        f[i].countfigure = trinum;
        space = ukazatel(arr, ' ', 0);
        comma = ukazatel(arr, ',', 0);
        for (j = ukazatel(arr, '(', 0) + 1; j < space; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            x1c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        x1 = atof(x1c);
        for (j = space; j < comma; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            y1c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        y1 = atof(y1c);
        space = ukazatel(arr, ' ', space + 1);
        for (j = comma; j < space; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            x2c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        x2 = atof(x2c);
        comma = ukazatel(arr, ',', comma + 1);
        for (j = space; j < comma; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            y2c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        y2 = atof(y2c);
        space = ukazatel(arr, ' ', space + 1);
        for (j = comma; j < space; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            x3c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        x3 = atof(x3c);
        comma = ukazatel(arr, ',', comma + 1);
        for (j = space; j < comma; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            y3c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        y3 = atof(y3c);
        space = ukazatel(arr, ' ', space + 1);
        for (j = comma; j < space; j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            x4c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        x4 = atof(x4c);
        comma = ukazatel(arr, ',', comma + 1);
        for (j = space; j < ukazatel(arr, ')', 0); j++) {
          if (isdigit(arr[j]) || arr[j] == '.' || arr[j] == '-') {
            y4c[k] = arr[j];
            k++;
          }
        }
        k = 0;
        y4 = atof(y4c);
        if ((x1 != x4) || (y1 != y4)) {
          printf("Fatal: Incorreced enter of first point");
          fclose(S1);
          getchar();
          return 1;
        }
        double AB, AC, BC;
        AB = side(x1, y1, x2, y2);
        AC = side(x1, y1, x3, y3);
        BC = side(x2, y2, x3, y3);
        if ((AB + BC < AC) || (AB + AC < BC) || (AC + BC < AB)) {
          printf("Fatal: Triangle does not excists");
          fclose(S1);
          getchar();
          return 1;
        }
        double perimeter = AB + AC + BC;
        double area = area_of_triangle(AB, BC, AC);
        f[i].two[trinum].xsides[0] = x1;
        f[i].two[trinum].xsides[1] = x2;
        f[i].two[trinum].xsides[2] = x3;
        f[i].two[trinum].xsides[3] = x4;
        f[i].two[trinum].ysides[0] = y1;
        f[i].two[trinum].ysides[1] = y2;
        f[i].two[trinum].ysides[2] = y3;
        f[i].two[trinum].ysides[3] = y4;
        f[i].two[trinum].aaarea = area;
        f[i].two[trinum].ppperimeter = perimeter;
        trinum++;
      }
      if (strstr(arr, "polygon") != NULL &&
          (strstr(arr, "triangle") == NULL || strstr(arr, "circle") == NULL)) {
        int sidecount = countelement(arr, ' ') - 1;
        f[i].fnumber = 3;
        f[i].countfigure = polynum;
        f[i].three[polynum].sidenumber = sidecount;
        char number[30];
        double perimeter, area;
        double *xsides = (double *)malloc((sidecount + 1) * sizeof(double));
        double *ysides = (double *)malloc((sidecount + 1) * sizeof(double));
        double *sides = (double *)malloc(sidecount * sizeof(double));
        int comma = 0, space = 0, k = 0, z, m;
        comma = ukazatel(arr, '(', ukazatel(arr, '(', 0));
        space = ukazatel(arr, ' ', 0);
        for (z = 0; z < sidecount + 1; z++) {
          for (m = comma; m < space; m++) {
            if (isdigit(arr[m]) || arr[m] == '.' || arr[m] == '-') {
              number[k] = arr[m];
              k++;
            }
          }
          xsides[z] = atof(number);
          k = 0;
          make_string_null(number);
          comma = ukazatel(arr, ',', comma + 1);
          if (z == sidecount) comma = ukazatel(arr, ')', 0);
          for (m = space; m < comma; m++) {
            if (isdigit(arr[m]) || arr[m] == '.' || arr[m] == '-') {
              number[k] = arr[m];
              k++;
            }
          }
          ysides[z] = atof(number);
          k = 0;
          make_string_null(number);
          space = ukazatel(arr, ' ', space + 1);
        }
        if ((xsides[0] != xsides[sidecount]) ||
            (ysides[0] != ysides[sidecount])) {
          printf("Fatal: Incorreced enter of first point");
          fclose(S1);
          getchar();
          return 1;
        }
        for (m = 0; m < sidecount; m++) {
          sides[m] = side(xsides[m], ysides[m], xsides[m + 1], ysides[m + 1]);
        }
        for (m = 0; m < sidecount; m++) {
          perimeter += sides[m];
        }
        for (m = 1; m < sidecount; m++) {
          area += (xsides[m - 1] * ysides[m] - xsides[m] * ysides[m - 1]);
        }
        area = 0.5 * sqrt(pow(area, 2));
        f[i].three[polynum].aaaarea = area;
        f[i].three[polynum].pppperimeter = perimeter;
        for (m = 0; m < sidecount + 1; m++) {
          f[i].three[polynum].xxsides[m] = xsides[m];
          f[i].three[polynum].yysides[m] = ysides[m];
        }
        free(xsides);
        free(ysides);
        free(sides);
        polynum++;
      }
    }
    i++;
  }
  print(f, i);
  fclose(S1);
  getchar();
  return 0;
}
