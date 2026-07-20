class Trie :
    def __init__(self):
        self.root = Node()
    
    def add(self,word):
        current = self.root
        current.occurrence += 1

        for c in word:
            if c not in current.children:
                current.children[c] = Node()
            
            current = current.children[c]
            current.occurrence += 1

        current.isEnd += 1

    def countPrefix(self,word):
        current = self.root

        for c in word:
            if c not in current.children:
                return 0

            current = current.children[c]
        
        return current.occurrence

    def checkWord(self,word):
        current = self.root

        for c in word:
            if c not in current.children:
                return False

            current = current.children[c]

        return current.isEnd > 0

    def remove(self,word):
        if not self.checkWord(word):
            return

        current = self.root
        current.occurrence -= 1
        for c in word:
            next = current.children[c]
            next.occurrence -= 1

            if next.occurrence == 0:
                del current.children[c]
                return

            current = next
        
        current.isEnd -= 1


class Node :
    def __init__(self):
        self.children = {}
        self.occurrence = 0
        self.isEnd = 0
