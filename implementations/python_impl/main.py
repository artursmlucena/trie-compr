from python_impl import Trie
import time
import sys

input = sys.stdin.readline

def main():
    t = int(input())

    while t != 0:
        n = int(input())
        trie = Trie()
        for _ in range(n):
            inp = input().strip().split(" ")
            k = int(inp[0])
            if k == 1:
                trie.add(inp[1])
            if k == 2:
                if trie.checkWord(inp[1]):
                    print("YES")
                else:
                    print("NO")
            if k == 3:
                print(trie.countPrefix(inp[1]))
            if k == 4:
                trie.remove(inp[1])
        t -= 1


main()
