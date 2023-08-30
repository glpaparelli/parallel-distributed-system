import argparse
import csv
import matplotlib.pyplot as plt

# Define the command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument('filename', nargs='+', help='the name of the CSV file(s) to plot')
parser.add_argument('-c', '--compare', action='store_true', help='compare CSV files in the same plot, pass at least 2 filenames')
args = parser.parse_args()

if args.compare:
    if len(args.filename) < 2:
        parser.error('The --compare option requires at least two CSV files.')

    x = [1, 5, 10, 50, 100]

    # Define a list of line styles and markers
    markers = ['o', 's', '^', 'D', 'v', '<', '>', '*', 'p', 'h', '8', 'X', 'd']    
    # Plot each column as a separate line graph from each file
    for i, filename in enumerate(args.filename):
        # Open the CSV file and create a reader object
        with open(filename, 'r') as file:
            reader = csv.reader(file)

            # Read the data rows and store them in a matrix
            matrix = []
            for row in reader:
                matrix.append(row)

            # Plot each column as a separate line graph
            for j in range(len(matrix[0])-1, len(matrix[0])):
                y = [float(matrix[k][j]) for k in range(1, len(matrix))]
                marker = markers[(j-1) % len(markers)]
                markers.remove(marker)
                plt.plot(x, y, color="black", marker=marker, linestyle="-", label=matrix[0][j] + ", " + filename)

                # Add text annotations and projection lines for each point
                for k in range(len(x)):
                    plt.plot([x[k], x[k]], [0, y[k]], color='gray', linestyle='--')
                    plt.plot([0, x[k]], [y[k], y[k]], color='gray', linestyle='--')
                    plt.text(x[k], 0, f'{x[k]}', ha='center', va='top')
                    plt.text(0, y[k], f'{y[k]:.2f}', ha='right', va='center')

    # Set the x and y axis labels and add a legend
    plt.xlabel('Megabytes', fontsize=12)
    plt.ylabel('Seconds', fontsize=12)
    # Add a legend above the plot
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.1))

    # Get the current figure and set its size to match the screen resolution
    fig = plt.gcf()
    fig.set_size_inches(2560/100, 1440/100)
    plt.show()
else:
    # Open the CSV file and create a reader object
    with open(args.filename[0], 'r') as file:
        reader = csv.reader(file)

        # Read the data rows and store them in a matrix
        matrix = []
        for row in reader:
            matrix.append(row)

        x = [1, 5, 10, 50, 100]

        # Plot each column as a separate line graph
        for j in range(len(matrix[0])-1, len(matrix[0])):
            y = [float(matrix[i][j]) for i in range(1, len(matrix))]
            plt.plot(x, y, color='black', marker='*', linestyle="-", label=matrix[0][j] + ", " + args.filename[0])

            # Add text annotations and projection lines for each point
            for i in range(len(x)):
                plt.plot([x[i], x[i]], [0, y[i]], color='gray', linestyle='--')
                plt.plot([0, x[i]], [y[i], y[i]], color='gray', linestyle='--')
                plt.text(x[i], 0, f'{x[i]}', ha='center', va='top')
                plt.text(0, y[i], f'{y[i]:.2f}', ha='right', va='center')

        # Set the x and y axis labels and add a legend
        plt.xlabel('Megabytes', fontsize=12)
        plt.ylabel('Seconds', fontsize=12)
        # Add a legend above the plot
        plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.1))

        fig = plt.gcf()
        fig.set_size_inches(2560/100, 1440/100)
        # Show the plot
        plt.show()