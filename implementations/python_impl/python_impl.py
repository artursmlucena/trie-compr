class Trie:
    def __init__(self):
        self.root = Node()

    def add(self, word):
        current = self.root
        current.occurrence += 1

        for c in word:
            pos = ord(c) - ord('a')
            if current.children[pos] is None:
                current.children[pos] = Node()

            current = current.children[pos]
            current.occurrence += 1

        current.isEnd += 1

    def countPrefix(self, word):
        current = self.root

        for c in word:
            pos = ord(c) - ord('a')
            if current.children[pos] is None:
                return 0

            current = current.children[pos]

        return current.occurrence

    def checkWord(self, word):
        current = self.root

        for c in word:
            pos = ord(c) - ord('a')
            if current.children[pos] is None:
                return False

            current = current.children[pos]

        return current.isEnd > 0

    def remove(self, word):
        if not self.checkWord(word):
            return

        current = self.root
        current.occurrence -= 1
        for c in word:
            pos = ord(c) - ord('a')
            next = current.children[pos]
            next.occurrence -= 1

            if next.occurrence == 0:
                current.children[pos] = None
                return

            current = next

        current.isEnd -= 1


class Node:
    def __init__(self):
        self.children = [None] * 26
        self.occurrence = 0
        self.isEnd = 0
