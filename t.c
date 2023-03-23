#include <stdio.h>

int main() {
  switch (5) {
  case 1:
    printf("1\n");
  case 5:
    switch (6) {
    case 5:
      printf("55\n");
    case 6:
      printf("66\n");
    case 8:
      printf("88\n");
    case 9:
      printf("88\n");
    default:
      printf("0\n");
    }
  case 4:
    printf("4\n");
    break;
  default:
    printf("10\n");
    break;
  }

  printf("\n");
  return 0;
}
