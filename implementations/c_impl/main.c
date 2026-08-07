#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "trie.h"
char buffer[2000007];
char out[1 << 30];
char* p = out;

int main() {
  FILE* fptr;
  fptr = fopen("../../scripts/time_c.txt", "w");

  if (fptr == NULL) {
    fprintf(stderr, "File not found\n");
    exit(0);
  }

  struct timespec start, end;

  timespec_get(&start, TIME_UTC);

  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    trie* Trie = trie_new();
    for (int i = 0; i < n; i++) {
      int operation;
      scanf("%d %s", &operation, buffer);

      if (operation == 1) trie_add(Trie, buffer);

      if (operation == 2) {
        bool k = trie_check_word(Trie, buffer);
        if (k)
          p += sprintf(p, "YES\n");
        else
          p += sprintf(p, "NO\n");
      }

      if (operation == 3) {
        int cnt = trie_count_prefix(Trie, buffer);
        p += sprintf(p, "%d\n", cnt);
      }

      if (operation == 4) trie_remove(Trie, buffer);
    }

    trie_free(Trie);
  }

  timespec_get(&end, TIME_UTC);

  long double time =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

  fprintf(fptr, "%Lf", time);
  fclose(fptr);

  fwrite(out, 1, p - out, stdout);
}
