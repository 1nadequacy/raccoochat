import RaccooChatClient
import argparse
import sys

def main():
    parser = argparse.ArgumentParser(description = 'Server address.')
    parser.add_argument('--host', help = 'localhost')
    parser.add_argument('--port', help = 'port')
    args = parser.parse_args()

    client = RaccooChatClient.ConnectServer(args.host, args.port)
    client.work_with_server()

if __name__ == '__main__':
    #try:
        main()
    #except Thrift.TException as tx:
        #print('%s' % tx.error_msg)
