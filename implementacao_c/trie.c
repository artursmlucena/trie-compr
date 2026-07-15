#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ptr.h"

#define ALPHABET_SIZE 26

typedef struct node {
  struct node* letters[ALPHABET_SIZE];
  bool end;
  int prefix_num;

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
  newNode->end = false;
  newNode->prefix_num = 0;
  return newNode;
}

static void index_check(int i) {
  if (i < 0 || i >= ALPHABET_SIZE) {
    fprintf(stderr, "Index out of bounds for node\n");
    exit(EXIT_FAILURE);
  }
}

node* node_get_letter(const node* n, int i) {
  assert(n != NULL);
  index_check(i);
  return n->letters[i];
}

void node_add_letter(node* n, int i, node* next) {
  assert(n != NULL);
  index_check(i);
  if (n->letters[i] != NULL) {
    fprintf(stderr, "Children node should not be overwritten\n");
    exit(EXIT_FAILURE);
  }
  n->letters[i] = next;
}

void node_remove_letter_sub_tree(node* n, int i) {
  check_null(n);
  index_check(i);
  node_free(n->letters[i]);
  n->letters[i] = NULL;
}

bool node_get_end(const node* n) {
  assert(n != NULL);
  return n->end;
}

void node_set_end(node* n) {
  assert(n != NULL);
  n->end = true;
}

void node_erase_end(node* n) {
  assert(n != NULL);
  n->end = false;
}

int node_get_prefix_num(const node* n) {
  assert(n != NULL);
  return n->prefix_num;
}

void node_add_prefix_num(node* n) {
  assert(n != NULL);
  n->prefix_num++;
}

void node_sub_prefix_num(node* n) {
  assert(n != NULL);
  n->prefix_num--;
}

static int get_letter_index(char c) {
  int i = c - 'a';
  index_check(i);
  return i;
}

typedef struct trie {
  node* root;
  int words;
} trie;

trie* trie_new() {
  trie* t = malloc(sizeof(trie));
  check_null(t);
  t->root = node_new();
  check_null(t->root);
  t->words = 0;
  return t;
}

static bool recursive_check(const node* cur, const char* word) {
  if (!*(word)) return node_get_end(cur);

  int c = get_letter_index(*word);
  const node* next = node_get_letter(cur, c);
  if (next == NULL) return false;

  return recursive_check(next, word + 1);
}

bool trie_check(const trie* t, const char* word) {
  return recursive_check(t->root, word);
}

void trie_add(trie* t, const char* word) {
  node* cur = t->root;

  if (trie_check(t, word)) return;

  for (const char* p = word; *p; p++) {
    int c = get_letter_index(*p);
    node* next = node_get_letter(cur, c);

    if (next == NULL) {
      next = node_new();
      node_add_letter(cur, c, next);
    }

    cur = next;
    node_add_prefix_num(cur);
  }

  if (!node_get_end(cur)) t->words++;
  node_set_end(cur);
}

bool trie_remove(trie* t, const char* word) {
  node* cur = t->root;
  node* nodeToRemove = NULL;
  int idToRemove = -1;

  if (!trie_check(t, word)) return false;

  for (const char* p = word; *p; p++) {
    int c = get_letter_index(*p);
    node* next = node_get_letter(cur, c);

    node_sub_prefix_num(next);
    if (nodeToRemove == NULL && node_get_prefix_num(next) == 0) {
      nodeToRemove = cur;
      idToRemove = c;
    }
    cur = next;
  }

  t->words--;
  node_erase_end(cur);
  if (nodeToRemove != NULL)
    node_remove_letter_sub_tree(nodeToRemove, idToRemove);

  return true;
};

int trie_cnt(const trie* t, const char* word) {
  node* cur = t->root;
  for (const char* p = word; *p; p++) {
    int c = get_letter_index(*p);
    node* next = node_get_letter(cur, c);
    if (next == NULL) return 0;
    cur = next;
  }
  return node_get_prefix_num(cur);
}

int trie_get_words(const trie* t) { return t->words; }

void trie_free(trie* t) {
  if (t == NULL) return;
  node_free(t->root);
  free(t);
}
