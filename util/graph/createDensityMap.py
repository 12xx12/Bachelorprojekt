
import argparse
from PIL import Image


def main():
    parser = argparse.ArgumentParser(
        description='Create a graph from a tsv file')
    parser.add_argument('path', help='Path to the tsv file', type=str)
    args = parser.parse_args()
    val = []
    with open(args.path, 'r') as f:
        for line in f:
            if line == "\n":
                break
            values = line.split('\t')
            val.append((float(values[0].replace('\n', '')),
                        float(values[1].replace('\n', '')),
                        float(values[2].replace('\n', ''))))

    minimum = min(val, key=lambda x: x[2])
    maximum = max(val, key=lambda x: x[2])

    img = Image.new('RGB', (len(val), len(val)), 'white')



    img.save('densityMap.png')


if __name__ == '__main__':
    main()
