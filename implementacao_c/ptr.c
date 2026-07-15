#include <stdio.h>
#include <stdlib.h>

void checkNull(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "Memory Allocation failed\n");
    exit(EXIT_FAILURE);
  }
}
