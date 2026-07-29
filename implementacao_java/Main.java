import java.util.*;
import java.io.*;
class Main {

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StandartTrie trie = new StandartTrie();
    int n = Integer.parseInt(br.readLine());
    for(int i = 0; i < n; i++) {
     trie.add(br.readLine()); 
    }
    
  }

}
