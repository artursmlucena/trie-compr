import java.util.HashMap;
import java.util.Map;

class Node {
    Map<Character, Node> children = new HashMap<>();
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
            current.children.putIfAbsent(c, new Node());
            current = current.children.get(c);
            current.occurrence++;
        }
        current.isEnd++;
    }

    public int countPrefix(String word) {
        Node current = root;
        for (char c : word.toCharArray()) {
            if (!current.children.containsKey(c)) {
                return 0;
            }
            current = current.children.get(c);
        }
        return current.occurrence;
    }

    public boolean checkWord(String word) {
        Node current = root;
        for (char c : word.toCharArray()) {
            if (!current.children.containsKey(c)) {
                return false;
            }
            current = current.children.get(c);
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
            Node next = current.children.get(c);
            next.occurrence--;
            if (next.occurrence == 0) {
                current.children.remove(c);
                return;
            }
            current = next;
        }
        current.isEnd--;
    }
}
