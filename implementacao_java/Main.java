import java.util.*;
class Main {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    StandartTrie trie = new StandartTrie();

    int n = Integer.parseInt(sc.nextLine());
    for(int i = 0; i < n; i++) {
      trie.add(sc.nextLine());
    }
    
  }

}
