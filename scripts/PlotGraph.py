from typing import List
from matplotlib import pyplot as plt
import csv

def plot_SoE(data_file_name: str):
    numbers: List[int] = []
    sieve_1: List[int] = []
    sieve_2: List[int] = []
    sieve_3: List[int] = []

    with open(data_file_name, 'r') as file:
        plots = csv.reader(file, delimiter=',')
        for row in plots:
            numbers.append(int(row[0]))
            sieve_1.append(int(row[1]))
            sieve_2.append(int(row[2]))
            sieve_3.append(int(row[3]))

    plt.plot(numbers, sieve_1, label='sieve 1')
    plt.plot(numbers, sieve_2, label='sieve 2')
    plt.plot(numbers, sieve_3, label='sieve 3')
    plt.xlabel('Numbers')
    plt.ylabel('Times(ms)')
    plt.grid(color='gray', linestyle='dashed')

    plt.title('Time comparison')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    plot_SoE('./soe_data.csv');
