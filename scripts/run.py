import os
import time


def run_command(command: str):
    start = time.perf_counter()

    os.system(command)

    end = time.perf_counter()

    return end - start


def save_time(name: str, time: float):
    with open(name, "w", encoding="utf-8") as arquivo:
        arquivo.write(f"{time:.6f}\n")


def main():
    os.system("python3 generator.py")

    os.chdir("..")
    os.chdir("implementacao_c")
    os.system("make -s clean")
    time_c = run_command("./main < ~/trie-compr/scripts/test.txt")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_c.txt", time_c)

    os.chdir("..")
    os.chdir("implementacao_java")
    os.system("javac Main.java")
    time_java = run_command("java Main < ~/trie-compr/scripts/test.txt")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_java.txt", time_java)

    os.chdir("..")
    os.chdir("rust_impl")
    os.system("rustc main.rs")
    time_rust = run_command("./main < ~/trie-compr/scripts/test.txt")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_rust.txt", time_rust)

    os.chdir("..")
    os.chdir("python_impl")
    time_py = run_command("python3 main.py < ~/trie-compr/scripts/test.txt")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_py.txt", time_py)


if __name__ == "__main__":
    main()
