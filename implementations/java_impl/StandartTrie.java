import java.util.HashMap;
import java.util.Map;

class Node {
  Node[] children = new Node[26];
  int occurrence = 0;
  int isEnd = 0;
}

public class StandartTrie {
  private Node root;

  public StandartTrie() {
      root = new Node();
  }

  public void add(String word) {
    Node current = root;
    current.occurrence++;
    for (char c : word.toCharArray()) {

      if(current.children[c - 'a'] == null) {
        current.children[c - 'a'] = new Node();
      }

      current = current.children[c - 'a'];
      current.occurrence++;
    }
    current.isEnd++;
  }

  public int countPrefix(String word) {
    Node current = root;
    for (char c : word.toCharArray()) {
        if (current.children[c - 'a'] == null) {
            return 0;
        }
        current = current.children[c - 'a'];
    }
    return current.occurrence;
  }

  public boolean checkWord(String word) {
    Node current = root;
    for (char c : word.toCharArray()) {

        if (current.children[c - 'a'] == null) {
            return false;
        }

        current = current.children[c - 'a'];
    }

    return current.isEnd > 0;
  }

  public void remove(String word) {
    if (!checkWord(word)) {
        return;
    }

    Node current = root;
    current.occurrence--;
    for (char c : word.toCharArray()) {
        Node next = current.children[c - 'a'];
        next.occurrence--;
        if (next.occurrence == 0) {
            current.children[c - 'a'] = null;
            return;
        }
        current = next;
    }
    current.isEnd--;
  }
}
