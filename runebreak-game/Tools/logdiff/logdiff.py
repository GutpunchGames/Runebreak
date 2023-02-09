import argparse
from log_reader import LogReader

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('log_1') 
    parser.add_argument('log_2') 
    args = parser.parse_args()
    return args

def main():
    args = parse_args()
    print(args.log_1)
    print(args.log_2)

    reader = LogReader()
    log_1 = reader.read(args.log_1)
    log_1.pretty_print()
    log_2 = reader.read(args.log_2)
    log_2.pretty_print()

if __name__ == "__main__":
    main()