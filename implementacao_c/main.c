#include <stdio.h>

#include "trie.h"
char buffer[2000007];

int main() {
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
          printf("YES\n");
        else
          printf("NO\n");
      }

      if (operation == 3) {
        int cnt = trie_count_prefix(Trie, buffer);
        printf("%d\n", cnt);
      }

      if (operation == 4) trie_remove(Trie, buffer);
    }

    trie_free(Trie);
  }
}
