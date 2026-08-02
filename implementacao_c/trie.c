#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ptr.h"

#define ALPHABET_SIZE 26
#define POOL_SIZE 1000001

typedef struct node {
  struct node* letters[ALPHABET_SIZE];
  int end;
  int occurrence;

} node;

typedef struct node_pool {
  node* nodes;
  int used;
} node_pool;

node* node_new(node_pool* pool) {
  node* n = &pool->nodes[pool->used++];
  memset(n, 0, sizeof *n);
  return n;
}

typedef struct trie {
  node* root;
  node_pool pool;
} trie;

trie* trie_new() {
  trie* t = malloc(sizeof(trie));
  check_null(t);

  t->pool.nodes = calloc(POOL_SIZE, sizeof(node));
  check_null(t->pool.nodes);
  t->pool.used = 0;

  t->root = node_new(&t->pool);
  return t;
}

bool trie_check_word(const trie* t, const char* word) {
  const node* cur = t->root;

  while (*word != '\0') {
    int c = *word - 'a';
    if (cur->letters[c] == NULL) return false;
    cur = cur->letters[c];
    word++;
  }

  return cur->end;
}

void trie_add(trie* t, const char* word) {
  node* cur = t->root;
  cur->occurrence++;

  while (*word != '\0') {
    int c = *word - 'a';
    if (cur->letters[c] == NULL) cur->letters[c] = node_new(&t->pool);

    cur = cur->letters[c];
    cur->occurrence++;
    word++;
  }
  cur->end++;
}

void trie_remove(const trie* t, const char* word) {
  if (!trie_check_word(t, word)) return;

  node* cur = t->root;
  cur->occurrence--;
  while (*word != '\0') {
    int c = *word - 'a';
    node* next = cur->letters[c];
    next->occurrence--;
    if (next->occurrence == 0) {
      cur->letters[c] = NULL;
      return;
    }
    cur = next;
    word++;
  }
  cur->end--;
}

int trie_count_prefix(const trie* t, const char* word) {
  const node* cur = t->root;
  while (*word != '\0') {
    int c = *word - 'a';
    if (cur->letters[c] == NULL) return 0;
    cur = cur->letters[c];
    word++;
  }

  return cur->occurrence;
}

void trie_free(trie* t) {
  if (t == NULL) return;
  free(t->pool.nodes);
  free(t);
}
