#include <stdbool.h>
#include <stdlib.h>

#include "ptr.h"

#define ALPHABET_SIZE 26

typedef struct node {
  struct node* letters[ALPHABET_SIZE];
  int end;
  int occurrence;

} node;

void node_free(node* n) {
  if (n == NULL) return;
  for (int i = 0; i < ALPHABET_SIZE; i++) node_free(n->letters[i]);
  free(n);
}

node* node_new() {
  node* newNode = malloc(sizeof(node));
  check_null(newNode);
  for (int i = 0; i < ALPHABET_SIZE; i++) newNode->letters[i] = NULL;
  newNode->end = 0;
  newNode->occurrence = 0;
  return newNode;
}

typedef struct trie {
  node* root;
} trie;

trie* trie_new() {
  trie* t = malloc(sizeof(trie));
  check_null(t);
  t->root = node_new();
  return t;
}

static bool recursive_check_word(const node* cur, const char* word) {
  if (*word == '\0') return cur->end;

  int c = *word - 'a';
  const node* next = cur->letters[c];
  if (next == NULL) return false;

  return recursive_check_word(next, word + 1);
}

bool trie_check_word(const trie* t, const char* word) {
  return recursive_check_word(t->root, word);
}

static void recursive_add(node* cur, const char* word) {
  if (*word == '\0') {
    cur->end++;
    cur->occurrence++;
    return;
  }
  int c = *word - 'a';
  node* next = cur->letters[c];

  if (next == NULL) {
    next = node_new();
    cur->letters[c] = next;
  }

  recursive_add(next, word + 1);

  cur->occurrence++;
}

void trie_add(trie* t, const char* word) { recursive_add(t->root, word); }

static bool recursive_remove(node* cur, const char* word) {
  if (*word == '\0') {
    if (!cur->end) return false;

    cur->end--;
    cur->occurrence--;
    return true;
  }
  int c = *word - 'a';
  node* next = cur->letters[c];

  if (next == NULL) return false;

  bool removed = recursive_remove(next, word + 1);

  if (removed) {
    cur->occurrence--;
    if (next->occurrence == 0) {
      node_free(next);
      cur->letters[c] = NULL;
    }
  }

  return removed;
}

bool trie_remove(trie* t, const char* word) {
  return recursive_remove(t->root, word);
};

static int recursive_count_prefix(const node* cur, const char* word) {
  if (*word == '\0') return cur->occurrence;
  int c = *word - 'a';
  const node* next = cur->letters[c];

  if (next == NULL) return 0;
  return recursive_count_prefix(next, word + 1);
}

int trie_count_prefix(const trie* t, const char* word) {
  return recursive_count_prefix(t->root, word);
}

void trie_free(trie* t) {
  if (t == NULL) return;
  node_free(t->root);
  free(t);
}
