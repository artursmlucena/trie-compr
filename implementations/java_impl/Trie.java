class Trie {

  Vertex root = new Vertex();

  public void insert(String key) {
    Vertex aux = root;
    for(char c : key.toCharArray()) {

      if(aux.next[c - 'a'] == null) {
        aux.next[c - 'a'] = new Vertex();
      }

      aux.freq[c - 'a'] += 1;
      aux = aux.next[c - 'a'];
    }

    aux.out = true;
  }


  public boolean search(String key) {
    Vertex aux = root;
    for(char c : key.toCharArray()) {
      if(aux.next[c - 'a'] == null) return false;

      aux = aux.next[c - 'a'];
    }

    return aux.out;
    }

  public boolean isPrefix(String key) {
    Vertex aux = root;
    for(char c : key.toCharArray()) {
      if(aux.next[c - 'a'] == null) return false;

      aux = aux.next[c - 'a'];
    }

    return true;
  }

  public void remove(String key) {
    Vertex aux = root;
    if(!search(key)) {
      System.out.println("Não está na trie");
      return;
    }
    for(char c : key.toCharArray()) {
      if(aux.freq[c - 'a'] == 1) {
        aux.freq[c - 'a'] = 0;
        Vertex prox = aux.next[c - 'a'];
        aux.next[c - 'a'] = null;
        aux = prox;
        continue;
      }
      aux.freq[c - 'a'] -= 1;
      aux = aux.next[c - 'a'];
    }
  }
}

class Vertex {
  Vertex[] next;
  boolean out;
  int[] freq;

  public Vertex() {
    next = new Vertex[26];
    freq = new int[26];
    out = false;
  }
}

