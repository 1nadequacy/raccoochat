#!/usr/local/bin/python

import RaccooChatClient
import argparse
import sys

def main():
    parser = argparse.ArgumentParser(description = 'Server address.')
    parser.add_argument('--host', help = 'host', default = 'localhost')
    parser.add_argument('--port', help = 'port', type = int, default = 9090)
    args = parser.parse_args()

    client = RaccooChatClient.ConnectToServer(args.host, args.port)
    client.work_with_server()

if __name__ == '__main__':
    main()

