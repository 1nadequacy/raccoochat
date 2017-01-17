#!/usr/local/bin/python

import sys
import time, readline, thread
import datetime
sys.path.append('./gen-py')

from raccoochat import RaccooChat
from raccoochat.ttypes import *
from raccoochat.constants import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def printMessages(messageArray):
    for msg in messageArray:
        shift = 10 - len(msg.userName)
        print "[%s] %s %s : %s " % (msg.time, ' ' * shift, msg.userName, msg.textMessage)

def printUsers(usersArray):
    print "Users online: %s." % (', '.join(map(str, usersArray)))

def printCommands():
    for val in MAP_COMMAND.values():
        print val

def getCurrentTime(now):
    current_time = str(now.hour) + ':'
    if len(str(now.minute)) == 1: current_time += '0'
    current_time += str(now.minute)
    return current_time

# thread that get all new messages
def getMessages(client, user):
    while True:
        time.sleep(1)
        sys.stdout.write('\r' + ' ' * (len(readline.get_line_buffer()) + 2) + '\r')
        printMessages(client.getNewMessages(user))
        sys.stdout.write(readline.get_line_buffer())
        sys.stdout.flush()

def main():
    transport = TSocket.TSocket('localhost', 9090)
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = RaccooChat.Client(protocol)

    transport.open()

    while (True):
        user_nickname = raw_input("Input your nickname: ")
        if client.connectUser(user_nickname):
            print "Welcome to main chat."
            print "Write '/command' for more information"
            break

    thread.start_new_thread(getMessages, (client, user_nickname,))
    while (True):
        input_text = raw_input()
        if input_text[0] == '/':
            command = input_text[1:]
            if command == 'command':
                printCommands()
            elif command == 'users':
                printUsers(client.getAllOnlineUsers())
            elif command == 'last':
                printMessages(client.getLastFiveMessages())
            elif command == 'exit':
                client.disconnectUser(user_nickname)
                break
            else:
                print "Incorrect command. Write '/command' for more information"
        else:
            new_message = Message()
            new_message.time = getCurrentTime(datetime.datetime.now())
            new_message.user_name = user_nickname
            new_message.text = input_text
            client.addMessage(new_message)
            printMessages(client.getNewMessages(user_nickname))

    transport.close()

if __name__ == '__main__':
    try:
        main()
    except Thrift.TException as tx:
        print('%s' % tx.errorMessage)
