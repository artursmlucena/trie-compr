#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ptr.h"

#define ALPHABET_SIZE 26

typedef struct node {
  struct node* letters[ALPHABET_SIZE];
  bool end;
  int prefixNum;

} node;

void node_free(node* n) {
  if (n == NULL) return;
  for (int i = 0; i < ALPHABET_SIZE; i++) node_free(n->letters[i]);
  free(n);
}

node* node_new() {
  node* newNode = malloc(sizeof(node));
  checkNull(newNode);
  for (int i = 0; i < ALPHABET_SIZE; i++) newNode->letters[i] = NULL;
  newNode->end = false;
  newNode->prefixNum = 0;
  return newNode;
}

static void indexCheck(int i) {
  if (i < 0 || i >= ALPHABET_SIZE) {
    fprintf(stderr, "Index out of bounds for node\n");
    exit(EXIT_FAILURE);
  }
}

node* node_getLetter(const node* n, int i) {
  assert(n != NULL);
  indexCheck(i);
  return n->letters[i];
}
void node_addLetter(node* n, int i, node* next) {
  assert(n != NULL);
  indexCheck(i);
  if (n->letters[i] != NULL) {
    fprintf(stderr, "Children node should not be overwritten\n");
    exit(EXIT_FAILURE);
  }
  n->letters[i] = next;
}

void node_removeLetterSubTree(node* n, int i) {
  checkNull(n);
  indexCheck(i);
  node_free(n->letters[i]);
  n->letters[i] = NULL;
}

bool node_getEnd(const node* n) {
  assert(n != NULL);
  return n->end;
}

void node_setEnd(node* n) {
  assert(n != NULL);
  n->end = true;
}

void node_eraseEnd(node* n) {
  assert(n != NULL);
  n->end = false;
}

int node_getPrefixNum(const node* n) {
  assert(n != NULL);
  return n->prefixNum;
}

void node_addPrefixNum(node* n) {
  assert(n != NULL);
  n->prefixNum++;
}

void node_subPrefixNum(node* n) {
  assert(n != NULL);
  n->prefixNum--;
}

static int getLetterIndex(char c) {
  int i = c - 'a';
  indexCheck(i);
  return i;
}

typedef struct trie {
  node* root;
  int words;
} trie;

trie* trie_new() {
  trie* t = malloc(sizeof(trie));
  checkNull(t);
  t->root = node_new();
  checkNull(t->root);
  t->words = 0;
  return t;
}

bool trie_check(const trie* t, const char* word) {
  node* cur = t->root;

  for (const char* p = word; *p; p++) {
    int c = getLetterIndex(*p);
    node* next = node_getLetter(cur, c);
    if (next == NULL) return false;
    cur = next;
  }
  return node_getEnd(cur);
}

void trie_add(trie* t, const char* word) {
  node* cur = t->root;

  if (trie_check(t, word)) return;

  for (const char* p = word; *p; p++) {
    int c = getLetterIndex(*p);
    node* next = node_getLetter(cur, c);

    if (next == NULL) {
      next = node_new();
      node_addLetter(cur, c, next);
    }

    cur = next;
    node_addPrefixNum(cur);
  }

  if (!node_getEnd(cur)) t->words++;
  node_setEnd(cur);
}

bool trie_remove(trie* t, const char* word) {
  node* cur = t->root;
  node* nodeToRemove = NULL;
  int idToRemove = -1;

  if (!trie_check(t, word)) return false;

  for (const char* p = word; *p; p++) {
    int c = getLetterIndex(*p);
    node* next = node_getLetter(cur, c);

    node_subPrefixNum(next);
    if (nodeToRemove == NULL && node_getPrefixNum(next) == 0) {
      nodeToRemove = cur;
      idToRemove = c;
    }
    cur = next;
  }

  t->words--;
  node_eraseEnd(cur);
  if (nodeToRemove != NULL) node_removeLetterSubTree(nodeToRemove, idToRemove);

  return true;
};

int trie_cnt(const trie* t, const char* word) {
  node* cur = t->root;
  for (const char* p = word; *p; p++) {
    int c = getLetterIndex(*p);
    node* next = node_getLetter(cur, c);
    if (next == NULL) return 0;
    cur = next;
  }
  return node_getPrefixNum(cur);
}

int trie_getWords(const trie* t) { return t->words; }

void trie_free(trie* t) {
  if (t == NULL) return;
  node_free(t->root);
  free(t);
}
