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
    os.system("python3 operation_generator.py")

    os.chdir("..")
    os.chdir("implementations/c_impl")
    os.system("make -s")
    run_command("./main < ~/trie-compr/scripts/cases.txt")
    os.chdir("..")
    os.chdir("..")
    os.chdir("scripts")

    os.chdir("..")
    os.chdir("implementations/java_impl")
    os.system("javac Main.java")
    time_java = run_command("java Main < ~/trie-compr/scripts/cases.txt")
    os.chdir("..")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_java.txt", time_java)

    os.chdir("..")
    os.chdir("implementations/rust_impl")
    os.system("rustc main.rs")
    time_rust = run_command("./main < ~/trie-compr/scripts/cases.txt")
    os.chdir("..")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_rust.txt", time_rust)

    os.chdir("..")
    os.chdir("implementations/python_impl")
    time_py = run_command("python3 main.py < ~/trie-compr/scripts/cases.txt")
    os.chdir("..")
    os.chdir("..")
    os.chdir("scripts")
    save_time("time_py.txt", time_py)


if __name__ == "__main__":
    main()
