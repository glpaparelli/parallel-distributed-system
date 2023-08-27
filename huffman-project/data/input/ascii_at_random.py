import argparse
import random
import string

def create_file(size, unit):
    # Convert size to bytes
    if unit == 'KB':
        size_bytes = size * 1024
    elif unit == 'MB':
        size_bytes = size * 1024 * 1024
    else:
        raise ValueError('Invalid unit specified')

    # All ASCII characters
    ascii_chars = string.ascii_letters + string.digits + string.punctuation + string.whitespace

    # Open file in write mode and fill it with random ascii characters
    with open(f"./{size}{unit}.txt", 'w') as f:
        while size_bytes > 0:
            # Generate a string of random ASCII chars using a list comprehension
            # - random.choice(string.ascii_letters) chooses a random ASCII char
            #   - the choice is iterated for min(size_bytes, 1024)
            #       - we create random strings of len 1024 except the "last time" where
            #         we need less chars to reach the desired file size
            chars = ''.join(random.choice(ascii_chars) for i in range(min(size_bytes, 1024)))
            # The string is written to the file
            f.write(chars)
            # We need size_bytes - the amount of bytes written now to reach the desired size
            size_bytes -= len(chars)

def main():
    # Creates argument parser object
    parser = argparse.ArgumentParser(description='Create a file of a given size filled with random ASCII characters')
    # Adds a required size arg to the parser
    parser.add_argument('size', type=int, help='Size of the file')
    # Adds an optional unit arg to the parser
    parser.add_argument('--unit', choices=['KB', 'MB'], default='MB', help='Unit of the size argument')
    # Parses the command line args
    args = parser.parse_args()
    create_file(args.size, args.unit)

if __name__ == '__main__':
    main()