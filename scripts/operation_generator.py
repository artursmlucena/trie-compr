import random

ALPHABET: str = "abcdefghijklmnopqrstuvwxyz"
DEFAULT_MAXIMUM_WORD_LENGTH: int = 10
NUMBER_OF_TEST_CASES: int = 10
MAXIMUM_TOTAL_OPERATIONS: int = 100_000

SEED: int = random.randint(0, 2 ** 32 - 1)
random.seed(SEED)


def get_random_word(max_length: int = DEFAULT_MAXIMUM_WORD_LENGTH) -> str:
    return "".join(
        random.choice(ALPHABET)
        for _ in range(random.randint(1, max_length))
    )


def rnd_int_from_len(arg) -> int:
    return random.randint(0, max(0, len(arg) - 1))


def generate_test_case(number_of_operations: int):
    stored_words: list[str] = []
    pseudo_trie: set[str] = set()
    cases: list[str] = []
    correct_outputs: list[str] = []

    cases.append(f"{number_of_operations}\n")

    for _ in range(number_of_operations):
        operation_type: int = random.randint(0, 99)

        # Test case: add(word) [no output]
        if operation_type < 20:
            if stored_words and random.randint(0, 10) == 0:
                string: str = stored_words[rnd_int_from_len(stored_words)]
            else:
                string: str = get_random_word()

            cases.append(f"1 {string}\n")

            if string not in pseudo_trie:
                pseudo_trie.add(string)
                stored_words.append(string)

        # Test case: contains(word) [YES/NO]
        elif operation_type < 50:
            if stored_words and random.randint(0, 1) == 0:
                string: str = stored_words[rnd_int_from_len(stored_words)]
            else:
                string: str = get_random_word()

            cases.append(f"2 {string}\n")

            if string in pseudo_trie:
                correct_outputs.append("YES\n")
            else:
                correct_outputs.append("NO\n")

        # Test case: count_prefix(prefix) [int]
        elif operation_type < 80:
            prefix: str = get_random_word(
                random.randint(1, DEFAULT_MAXIMUM_WORD_LENGTH)
            )

            if stored_words and random.randint(0, 2) == 0:
                word: str = stored_words[rnd_int_from_len(stored_words)]
                if len(word) > 1:
                    length: int = random.randint(1, len(word) - 1)
                    prefix = word[0:length]
                else:
                    prefix = word

            cases.append(f"3 {prefix}\n")

            count: int = 0
            for word in stored_words:
                if word.startswith(prefix):
                    count += 1
            correct_outputs.append(f"{count}\n")

        # Test case: remove(word) [no output]
        else:
            if stored_words and random.randint(0, 1) == 0:
                i: int = rnd_int_from_len(stored_words)
                string: str = stored_words[i]

                temp: str = stored_words[i]
                stored_words[i] = stored_words[len(stored_words) - 1]
                stored_words[len(stored_words) - 1] = temp

                stored_words.pop()
                pseudo_trie.remove(string)
            else:
                string: str = get_random_word()

            cases.append(f"4 {string}\n")

    return "".join(cases), "".join(correct_outputs)


def main():
    print(":: Generating...")

    all_cases: list[str] = []
    all_outputs: list[str] = []

    to_do: int = MAXIMUM_TOTAL_OPERATIONS

    all_cases.append(f"{NUMBER_OF_TEST_CASES}\n")
    for tc in range(NUMBER_OF_TEST_CASES):
        tests_left: int = NUMBER_OF_TEST_CASES - tc - 1

        max_operations = to_do - tests_left
        operations = random.randint(1, min(50_000, max_operations))

        to_do -= operations
        case_strs, correct_output_strs = generate_test_case(operations)

        all_cases.append(case_strs)
        all_outputs.append(correct_output_strs)

    with open("cases.txt", "w") as file:
        file.write("".join(all_cases))
    with open("correct-outputs.txt", "w") as file:
        file.write("".join(all_outputs))

    print("==> Done!")
    print("  -> Check files 'cases.txt' and 'correct-outputs.txt' for generated tests.")
    print(f"  -> Seed is {SEED}.")


if __name__ == "__main__":
    main()
