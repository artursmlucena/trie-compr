import os
import time 

def run_command(command : str):
    start = time.perf_counter()

    os.system(command)

    end = time.perf_counter()

    return end - start

def save_time(name: str, time: float):
    with open(name, "w", encoding="utf-8") as arquivo:
        arquivo.write(f"{time:.6f}\n")

def main():
    os.system("python3 generator.py")

    os.system("gcc main.c -o main")
    time_c = run_command("./main < test.txt")
    save_time("time_c.txt",time_c)

    os.system("javac Main.java")
    time_java = run_command("java Main < test.txt")
    save_time("time_java.txt",time_java)

    os.system("rustc main.rs")
    time_rust = run_command("./main < test.txt")
    save_time("time_rust.txt",time_rust)

    time_py = run_command("python3 main.py < test.txt")
    save_time("time_py.txt",time_py)

if __name__ == "__main__":
    main()
    

    

