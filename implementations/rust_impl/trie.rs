#[derive(Debug)]
struct Node {
    pointers: [usize; 26],
    pass_count: usize,
    is_end: usize,
}

impl Node {
    fn new() -> Self {
        Self {
            pointers: [0; 26],
            pass_count: 0,
            is_end: 0,
        }
    }
}

pub struct Trie {
    nodes: Vec<Node>,
}

impl Trie {
    pub fn new() -> Self {
        Self { nodes: vec![Node::new()] }
    }

    pub fn add(&mut self, word: &str) {
        let mut current = 0usize;
        self.nodes[current].pass_count += 1;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            let next = self.nodes[current].pointers[index];
            if next == 0 {
                let new_node = self.nodes.len();
                self.nodes.push(Node::new());
                self.nodes[current].pointers[index] = new_node;
            }

            current = self.nodes[current].pointers[index];
            self.nodes[current].pass_count += 1;
        }

        self.nodes[current].is_end += 1;
    }

    pub fn count_prefix(&self, prefix: &str) -> usize {
        let mut current = 0usize;

        for b in prefix.bytes() {
            let index = (b - b'a') as usize;

            let next = self.nodes[current].pointers[index];
            if next == 0 { return 0; }

            current = next;
        }

        return self.nodes[current].pass_count;
    }

    pub fn contains(&self, word: &str) -> bool {
        let mut current = 0usize;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            let next = self.nodes[current].pointers[index];
            if next == 0 { return false; }

            current = next;
        }

        return self.nodes[current].is_end > 0;
    }

    pub fn remove(&mut self, word: &str) {
        if !self.contains(word) { return; }

        let mut current = 0usize;

        self.nodes[current].pass_count -= 1;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            current = self.nodes[current].pointers[index];
            self.nodes[current].pass_count -= 1;
        }

        self.nodes[current].is_end -= 1;
    }
}
