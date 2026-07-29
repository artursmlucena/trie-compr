#include <stdio.h>

#include "trie.h"

int main() {
  int n;
  scanf("%d", &n);
  char buffer[2000007];

  trie* Trie = trie_new();

  for (int i = 0; i < n; i++) {
    scanf("%s", buffer);
    trie_add(Trie, buffer);
  }
}
