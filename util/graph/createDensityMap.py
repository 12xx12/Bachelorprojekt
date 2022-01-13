
import argparse
import matplotlib.pyplot as plt
import numpy as np
from numpy import sqrt


def main():
    parser = argparse.ArgumentParser(
        description='Create a graph from a tsv file')
    parser.add_argument('path', help='Path to the tsv file', type=str)
    args = parser.parse_args()

    val = []
    with open(args.path, 'r') as f:
        inner_val = []
        for line in f:
            if line == "\n":
                val.append(inner_val)
                inner_val = []
                continue
            inner_val.append(float(line.replace('\n', '')))

    val.reverse()

    plt.imshow(val, cmap='viridis', interpolation='nearest')

    plt.xticks([])
    plt.yticks([])
    plt.colorbar()

    # giving a title to my graph
    plt.title('Density in the fluid')

    # function to show the plot
    plt.show()


if __name__ == '__main__':
    main()
