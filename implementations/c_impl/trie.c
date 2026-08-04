#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ptr.h"

#define ALPHABET_SIZE 26

typedef struct node {
  int end;
  int occurrence;
  int letters[ALPHABET_SIZE];
} node;

typedef struct node_pool {
  node* nodes;
  size_t used;
  size_t size;
} node_pool;

typedef struct trie {
  int root;
  node_pool pool;
} trie;

static void node_pool_resize(node_pool* pool) {
  size_t new_size = 2 * pool->size;
  node* tmp = realloc(pool->nodes, new_size * sizeof(node));
  check_null(tmp);

  pool->nodes = tmp;
  memset(&pool->nodes[pool->size], 0, (new_size - pool->size) * sizeof(node));
  pool->size = new_size;
}

static int node_new(node_pool* pool) {
  if (pool->used == pool->size) node_pool_resize(pool);
  return pool->used++;
}

trie* trie_new() {
  trie* t = malloc(sizeof(trie));
  check_null(t);

  t->pool.size = 20;
  t->pool.nodes = calloc(t->pool.size, sizeof(node));
  check_null(t->pool.nodes);

  t->root = 0;
  t->pool.used = 1;
  return t;
}

bool trie_check_word(const trie* t, const char* word) {
  int cur = t->root;

  while (*word != '\0') {
    int c = *word - 'a';
    if (t->pool.nodes[cur].letters[c] == 0) return false;
    cur = t->pool.nodes[cur].letters[c];
    word++;
  }

  return t->pool.nodes[cur].end;
}

void trie_add(trie* t, const char* word) {
  int cur = t->root;
  t->pool.nodes[cur].occurrence++;

  while (*word != '\0') {
    int c = *word - 'a';
    if (t->pool.nodes[cur].letters[c] == 0) {
      int new_idx = node_new(&t->pool);
      t->pool.nodes[cur].letters[c] = new_idx;
    }

    cur = t->pool.nodes[cur].letters[c];
    t->pool.nodes[cur].occurrence++;
    word++;
  }
  t->pool.nodes[cur].end++;
}

void trie_remove(trie* t, const char* word) {
  if (!trie_check_word(t, word)) return;

  int cur = t->root;
  t->pool.nodes[cur].occurrence--;

  while (*word != '\0') {
    int c = *word - 'a';
    int next = t->pool.nodes[cur].letters[c];
    t->pool.nodes[next].occurrence--;
    if (t->pool.nodes[next].occurrence == 0) {
      t->pool.nodes[cur].letters[c] = 0;
      return;
    }
    cur = next;
    word++;
  }
  t->pool.nodes[cur].end--;
}

int trie_count_prefix(const trie* t, const char* word) {
  int cur = t->root;
  while (*word != '\0') {
    int c = *word - 'a';
    if (t->pool.nodes[cur].letters[c] == 0) return 0;
    cur = t->pool.nodes[cur].letters[c];
    word++;
  }

  return t->pool.nodes[cur].occurrence;
}

void trie_free(trie* t) {
  if (t == NULL) return;
  free(t->pool.nodes);
  free(t);
}
