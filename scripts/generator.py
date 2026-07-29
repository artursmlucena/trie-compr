import random
import os
import time

ALPHABET = "abcdefghijklmnopqrstuvwxyz"
MAX_SUM = 2 * 10**6


def get_word(size: int):
    return "".join(random.choices(ALPHABET, k=size))


def get_test(qntd_word: int, max_size: int):
    words = []
    max_test_sum = min(max_size * qntd_word, MAX_SUM)
    sum = 0

    for i in range(qntd_word):
        max_can = min(max_size, max_test_sum - sum - qntd_word + i + 1)
        max_can = max(1, max_can)
        size = random.randint(1, max_can)

        word = get_word(size)
        sum += len(word)

        words.append(word)

    return words


def main():
    VERY_SMALL, SMALL, MEDIUM, BIG, VERY_BIG = 1, 2, 3, 4, 5
    ENTRADA = (
        "Digite um número entre 1 e 5 para indicar o tipo:\n"
        "1- Caso MUITO PEQUENO\n"
        "2- Caso PEQUENO\n"
        "3- Caso MÉDIO\n"
        "4- Caso GRANDE\n"
        "5- Caso MUITO GRANDE\n> "
    )
    test = None

    while True:
        os.system("clear")

        try:
            choice = int(input(ENTRADA))

        except ValueError:
            print("Digite um número inteiro")
            time.sleep(1)
            continue

        if choice == VERY_SMALL:
            test = get_test(10, 20)
        elif choice == SMALL:
            test = get_test(10**2, 4 * 10**2)
        elif choice == MEDIUM:
            test = get_test(10**3, 4 * 10**3)
        elif choice == BIG:
            test = get_test(10**4, 4 * 10**4)
        elif choice == VERY_BIG:
            test = get_test(10**5, 4 * 10**5)
        else:
            print("Tipo inválido, coloque um número entre 1 e 5")
            time.sleep(1)
            continue

        break

    with open("test.txt", "w", encoding="utf-8") as arquivo:
        arquivo.write(str(len(test)) + "\n")

        for word in test:
            arquivo.write(word + "\n")


if __name__ == "__main__":
    main()
