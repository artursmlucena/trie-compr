#ifndef TRIE_H
#define TRIE_H
#include <stdbool.h>

typedef struct trie trie;
trie* trie_new();

void trie_add(trie* t, const char* word);
bool trie_check_word(const trie* t, const char* word);
bool trie_remove(trie* t, const char* word);

void trie_free(trie* t);

int trie_count_prefix(const trie* t, const char* word);

#endif  // !TRIE_H
