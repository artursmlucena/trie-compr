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

bool trie_check_word(const trie* t, const char* word) {
  node* cur = t->root;

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
    if (cur->letters[c] == NULL) cur->letters[c] = node_new();

    cur = cur->letters[c];
    cur->occurrence++;
    word++;
  }
  cur->end++;
}

void trie_remove(trie* t, const char* word) {
  if (!trie_check_word(t, word)) return;

  node* cur = t->root;
  cur->occurrence--;
  while (*word != '\0') {
    int c = *word - 'a';
    node* next = cur->letters[c];
    next->occurrence--;
    if (next->occurrence == 0) {
      node_free(cur->letters[c]);
      cur->letters[c] = NULL;
      return;
    }
    cur = next;
    word++;
  }
  cur->end--;
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
