#[derive(Debug)]
struct Node {
    pointers: [Option<Box<Node>>; 26],
    pass_count: usize,
    is_end: usize,
}

impl Node {
    fn new() -> Self {
        Self {
            pointers: std::array::from_fn(|_| None),
            pass_count: 0,
            is_end: 0,
        }
    }
}

struct Trie {
    root: Node,
}

impl Trie {
    fn new() -> Self {
        let mut root = Node::new();

        root.pass_count = 0;
        root.is_end = 0;

        Self { root }
    }

    fn add(&mut self, word: &str) {
        let mut current = &mut self.root;
        current.pass_count += 1;

        for b in word.bytes() {
            let index = (b - b'a') as usize;
            current = current.pointers[index]
                .get_or_insert_with(|| Box::new(Node::new()))
                .as_mut();

            current.pass_count += 1;
        }

        current.is_end += 1;
    }

    fn count_prefix(&self, prefix: &str) -> usize {
        let mut current = &self.root;

        for b in prefix.bytes() {
            let index = (b - b'a') as usize;

            match current.pointers[index].as_ref() {
                Some(node) => current = node,
                None => return 0,
            }
        }

        return current.pass_count;
    }

    fn contains(&self, word: &str) -> bool {
        let mut current = &self.root;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            match current.pointers[index].as_ref() {
                Some(node) => current = node,
                None => return false,
            }
        }

        return current.is_end > 0;
    }

    fn remove(&mut self, word: &str) -> bool {
        if !self.contains(word) {
            return false;
        }

        let mut current = &mut self.root;
        current.pass_count -= 1;

        for b in word.bytes() {
            let index = (b - b'a') as usize;

            let should_remove = {
                let child = current.pointers[index]
                        .as_mut()
                        .unwrap();

                child.pass_count -= 1;
                child.pass_count == 0
            };

            if should_remove {
                current.pointers[index] = None;
                return true;
            }

            current = current.pointers[index]
                .as_mut()
                .unwrap();
        }

        current.is_end -= 1;
        return true;
    }
}
