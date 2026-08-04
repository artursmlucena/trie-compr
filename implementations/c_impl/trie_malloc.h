#ifndef TRIE_MALLOC_H
#define TRIE_MALLOC_H
#include <stdbool.h>

typedef struct trie trie;
trie* trie_new();

void trie_add_malloc(trie* t, const char* word);
bool trie_check_word_malloc(const trie* t, const char* word);
void trie_remove_malloc(trie* t, const char* word);

void trie_free_malloc(trie* t);

int trie_count_prefix_malloc(const trie* t, const char* word);

#endif  // !TRIE_MALLOD_H
