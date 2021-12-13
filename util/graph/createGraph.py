import matplotlib.pyplot as plt
import argparse


def main():
    parser = argparse.ArgumentParser(
        description='Create a graph from a tsv file')
    parser.add_argument('path', help='Path to the tsv file', type=str)
    args = parser.parse_args()
    x = []
    y = []
    with open(args.path, 'r') as f:
        for line in f:
            values = line.split('\t')
            x.append(values[0])
            y.append(values[1])

    # plotting the points
    plt.plot(x, y)

    # naming the x axis
    plt.xlabel('x - axis')
    # naming the y axis
    plt.ylabel('y - axis')

    # giving a title to my graph
    plt.title('My first graph!')

    # function to show the plot
    plt.show()


if __name__ == '__main__':
    main()
