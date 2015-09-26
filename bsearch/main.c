#include "stdio.h"
#include "bsearch.h"

int main(int argc, char** argv){
  int ex[] = {};
  char found;
  size_t result = bsearch(ex, sizeof(ex)/sizeof(*ex), 12233, &found);
  printf("Result: %d Found: %d\n", result, found);
}
