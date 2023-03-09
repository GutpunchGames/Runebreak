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

    log_1_checksums = {}
    for tick in log_1.ticks:
        checksum_frame = int(tick.checksum.split('>')[0])
        checksum = tick.checksum
        log_1_checksums[checksum_frame] = checksum

    log_2_checksums = {}
    for tick in log_2.ticks:
        checksum_frame = int(tick.checksum.split('>')[0])
        checksum = tick.checksum
        log_2_checksums[checksum_frame] = checksum

    latest_synced_frame = -1
    for frame in log_1_checksums:
        if (frame in log_2_checksums and log_1_checksums[frame] == log_2_checksums[frame]):
            latest_synced_frame = max(latest_synced_frame, frame)

    print('latest synced frame: {}'.format(latest_synced_frame))

if __name__ == "__main__":
    main()