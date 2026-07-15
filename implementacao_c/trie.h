#ifndef TRIE_H
#define TRIE_H
#include <stdbool.h>

struct trie;
typedef struct trie trie;
trie* trie_new();
void trie_add(trie* t, const char* word);
bool trie_check(const trie* t, const char* word);
bool trie_remove(trie* t, const char* word);

void trie_free(trie* t);

int trie_cnt(const trie* t, const char* word);
int trie_getWords(const trie* t);

#endif  // !TRIE_H
