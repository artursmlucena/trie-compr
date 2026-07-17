/*
 * Código inicial implementado para AC no problema
 * [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree)
 * do LeetCode
 */
#[derive(Debug)]
struct Node {
    pointers: [Option<Box<Node>>; 26],
    is_leaf: bool,
}

impl Node {
    fn new() -> Self {
        Self {
            pointers: std::array::from_fn(|_| None),
            is_leaf: false,
        }
    }
}

struct Trie {
    root: Node,
}

impl Trie {
    fn new() -> Self {
        let mut root = Node::new();
        root.is_leaf = true;

        Self { root }
    }

    fn insert(&mut self, word: &str) {
        let mut current = &mut self.root;

        for b in word.bytes() {
            let index = (b - b'a') as usize;
            current = current.pointers[index]
                .get_or_insert_with(|| Box::new(Node::new()))
                .as_mut();
        }

        current.is_leaf = true;
    }

    fn search(&self, word: &str) -> bool {
        let mut current = &self.root;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            match current.pointers[index].as_ref() {
                Some(node) => current = node,
                None => return false,
            }
        }

        current.is_leaf
    }

    fn starts_with(&self, prefix: &str) -> bool {
        let mut current = &self.root;

        for b in prefix.bytes() {
            let index = (b - b'a') as usize;

            match current.pointers[index].as_ref() {
                Some(node) => current = node,
                None => return false,
            }
        }

        true
    }
}
