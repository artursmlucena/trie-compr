import java.util.*;
import java.io.*;
class Main {

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StandartTrie trie = new StandartTrie();
    int n = Integer.parseInt(br.readLine());
    for(int i = 0; i < n; i++) {
      String[] in = br.readLine().split(" ");
      int query = Integer.parseInt(in[0]);
      String palavra = in[1];
      

      if (query == 1) {
        trie.add(palavra);

      }else if (query == 2) {
        trie.checkWord(palavra);

      }else if (query == 3) {
        trie.countPrefix(palavra);

      }else if (query == 4) {
        trie.remove(palavra);
      }
    }
  }
}
