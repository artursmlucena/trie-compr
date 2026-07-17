import java.util.*;
class Main {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Trie trie = new Trie();
    while(true) {
      String in = sc.nextLine();
      if(in.equals("para")) break;
      trie.insert(in);
    }

    while(true) {
      String in = sc.nextLine();
      if(in.equals("para")) break;
      if(in.equals("remove")) {
        trie.remove(sc.nextLine());
      }
      System.out.println(trie.search(in));
    }
  }

}
