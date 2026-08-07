import java.io.*;
import java.time.*;

class Main {

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    FileWriter write = new FileWriter("time_java.txt");

    int t = Integer.parseInt(br.readLine());
    
    long start = System.nanoTime();
    while (t-- != 0)
      test(br, out);
      
    long end = System.nanoTime();
    
    double duracao = (end - start) / 1_000_000.0;

    String output = String.format("%2f", duracao / 1000.0);
    
    write.write(output);
    write.flush();
    write.close();
    out.flush();
  }

  public static void test(BufferedReader br, PrintWriter out) throws IOException {
    int n = Integer.parseInt(br.readLine());
    StandartTrie trie = new StandartTrie();

    for (int i = 0; i < n; i++) {
      String[] in = br.readLine().split(" ");
      int query = Integer.parseInt(in[0]);
      String palavra = in[1];

      if (query == 1) {
        trie.add(palavra);

      } else if (query == 2) {
        if (trie.checkWord(palavra))
          out.println("YES");
        else
          out.println("NO");

      } else if (query == 3) {
        int count = trie.countPrefix(palavra);
        out.println(count);

      } else if (query == 4) {
        trie.remove(palavra);
      }
    }
    out.flush();

  }
}
