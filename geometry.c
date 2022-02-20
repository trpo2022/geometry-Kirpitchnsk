#include <ctype.h>
#include <stdio.h>
#include <string.h>
    int
    ukazatel(char c[], char p, int i) {
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
int main() {
  FILE *S1;
  int i = 1;
  char arr[20];
  S1 = fopen("S1.txt", "r");
  while (fgets(arr, 20, S1) != NULL) {
    int p = ukazatel(arr, ' ', 0);
    // printf("%d and %ld", ukazatel(arr, ')', 0), strlen(arr));
    printf("%s", arr);
    if (strstr(arr, "circle") == NULL) {
      printf("Error at column %d: expected 'circle'\n", i);
    }
    if ((strstr(arr, "(") == NULL) || (strstr(arr, ")") == NULL)) {
      printf("Error at column %d: expected ')' or '('\n", i);
    }
    if ((!isdigit(arr[ukazatel(arr, '(', 0) + 1])) || (!isdigit(arr[p + 1]))) {
      printf("Error at column %d: expected '<double>'\n", i);
    }
    if (ukazatel(arr, ')', 0) < strlen(arr) - 4) {
      printf("Error at column %d: unexpected token\n", i);
    }
    if ((ukazatel(arr, ' ', 0) != p) || (ukazatel(arr, ' ', p + 1) != 0)) {
      printf("Error at column %d: expected ' '\n", i);
    }
    i++;
  }
  fclose(S1);
}
