mod trie;

use std::io::{self, BufRead, BufWriter, Write};
use trie::Trie;

fn main() -> io::Result<()> {
    let mut input = io::stdin().lock();
    let mut output = BufWriter::new(io::stdout().lock());
    let mut string = String::new();
    let mut trie_instance = Trie::new();

    input.read_line(&mut string)?;
    let number_of_test_cases: usize = string.trim_end().parse().unwrap();

    for _ in 0..number_of_test_cases {
        string.clear();
        input.read_line(&mut string)?;

        let number_of_operations: usize = string.trim_end().parse().unwrap();

        for _ in 0..number_of_operations {
            string.clear();
            input.read_line(&mut string)?;

            let (operation, word) = string.trim_end().split_once(" ").unwrap();

            match operation {
                "1" => trie_instance.add(word),

                "2" => {
                    let out = if trie_instance.contains(word) {
                        "YES"
                    } else {
                        "NO"
                    };
                    writeln!(output, "{}", out)?;
                }

                "3" => writeln!(output, "{}", trie_instance.count_prefix(word))?,
                "4" => trie_instance.remove(word),
                _ => unreachable!(),
            }
        }
    }
    output.flush()?;

    Ok(())
}
