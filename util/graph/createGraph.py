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
            x.append(float(values[0].replace('\n', '')))
            y.append(float(values[1].replace('\n', '')))

    # plotting the points
    plt.plot(x, y)

    plt.plot([0, 3000], [1100, 1100], color='black',
             linestyle='dashed', label='initial density')
    plt.legend()
    plt.ylim([1060, 1250])

    # naming the x axis
    plt.xlabel('time')
    # naming the y axis
    plt.ylabel('density')

    # giving a title to my graph
    plt.title('Average density across time')

    # function to show the plot
    plt.show()


if __name__ == '__main__':
    main()
