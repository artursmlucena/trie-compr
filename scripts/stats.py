import math


def truncate(number: float) -> float:
    return math.trunc(number * 10 ** 6) / 10 ** 6


def fetch_numbers(filepath: str) -> list[float]:
    with open(filepath, "r") as file:
        return [float(line.strip()) for line in file if line.strip()]


def main():
    print(":: Calculating statistics from 'benched_time'...")

    data: list[float] = fetch_numbers("benched-time-java")
    data_size: int = len(data)
    print(f"  -> Data points: {data_size} numbers")

    average: float = sum(data) / data_size
    print(f"  -> Average: {truncate(average)}")

    minimum: float = min(data)
    print(f"  -> Minimum: {minimum}")

    sorted_data: list[float] = sorted(data)
    mid: int = data_size // 2
    if data_size % 2 == 0:
        median: float = (sorted_data[mid - 1] + sorted_data[mid]) / 2
    else:
        median: float = sorted_data[mid]
    print(f"  -> Median: {truncate(median)}")

    variance = sum((k - average) ** 2 for k in data) / data_size
    print(f"  -> Variance: {truncate(variance)}")

    standard_deviation = math.sqrt(variance)
    print(f"  -> Standard deviation: {truncate(standard_deviation)}")

    coefficient_variation = (standard_deviation / average)
    print(f"  -> Coefficient of variation: {truncate(coefficient_variation)}")

    print(f"| {data_size} | {truncate(average)} | {minimum} | {truncate(median)} | {truncate(variance)} | {truncate(standard_deviation)} | {truncate(coefficient_variation)}")


if __name__ == "__main__":
    main()
