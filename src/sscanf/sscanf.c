/* sscanf example */
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("<-- sscanf -->\n");
  char input[10]="0x1234";

  char parsed[10];
  int result = sscanf (input,"%[xX0-9]", parsed);
  printf("result = %d, parsed = %s\n", result, parsed);

  char *parsed2 = NULL;
  int result2 = sscanf(input,"%m[xX0-9]", &parsed2);
  printf("result2 = %d, parsed2 = %s\n", result2, parsed2);
  free(parsed2);
  return 0;
}
