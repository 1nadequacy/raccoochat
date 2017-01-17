#!/usr/local/bin/python

import readline
import sys
import time
import thread
sys.path.append('./gen-py/')

from raccoochat import RaccooChat
from raccoochat.ttypes import *
from raccoochat.constants import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

class ConnectToServer(object):
    def __init__(self, host, port):
        self.transport = TSocket.TSocket(host, port)
        self.transport = TTransport.TBufferedTransport(self.transport)
        self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
        self.client = RaccooChat.Client(self.protocol)

        self.transport.open()

    def print_messages(self, message_array):
        for message in message_array:
            shift = 10 - len(message.userName)
            print '[%s] %s %s : %s ' % (message.time, ' ' * shift, message.userName, message.textMessage)

    def print_private_messages(self, message_array):
        for message in message_array:
            shift = 10 - len(message.userName)
            print '[%s] From %s - %s : %s ' % (message.time, ' ' * shift, message.userName, message.textMessage)

    def print_users(self, users_array):
        print 'Users online: %s.' % (', '.join(map(str, users_array)))

    def print_commands(self):
        for key, value in MAP_COMMANDS.items():
            print '%s - %s' % (key, value)

    def create_new_message(self, username, text_message):
        new_message = SimpleMessage()
        new_message.time = time.strftime('%H:%M')
        new_message.userName = username
        new_message.textMessage = text_message
        return new_message

    def get_messages(self, user):
        while True:
            time.sleep(1)
            sys.stdout.write('\r' + ' ' * (len(readline.get_line_buffer()) + 2) + '\r')
            self.print_messages(self.client.getNewMessages(user))
            self.print_private_messages(self.client.getNewPrivateMessages(user))
            sys.stdout.write(readline.get_line_buffer())
            sys.stdout.flush()

    def work_with_server(self):
        while True:
            username = raw_input('Input your nickname: ')
            if self.client.connectUser(username):
                print '%s welcome to main chat.' % username
                print 'Write "/command" for more information'
                break
            else:
                print 'Sorry. This nickname has already been taken.'

        thread.start_new_thread(self.get_messages, (username,))
        while True:
            input_text = raw_input()
            if input_text[0] == '/':
                command = input_text[1:]
                if command == 'command':
                    self.print_commands()
                elif command == 'users':
                    self.print_users(self.client.getAllOnlineUsers())
                elif command == 'last':
                    self.print_messages(self.client.getLastFiveMessages())
                elif command == 'exit':
                    self.client.disconnectUser(username)
                    break
                else:
                    print 'Incorrect command. Write "/command" for more information'
            elif input_text[0] == '.':
                input_data = input_text[1:].split()
                destination = input_data[0]
                text_message = ' ' .join(map(str, input_data[1:]))
                if self.client.findUser(destination):
                    self.client.addPrivateMessage(self.create_new_message(username, text_message), destination)
                else:
                    print 'User %s is offline.' % destination
            else:
                self.client.addMessage(self.create_new_message(username, input_text))

            self.print_messages(self.client.getNewMessages(username))
            self.print_private_messages(self.client.getNewPrivateMessages(username))

    def __del__(self):
        self.transport.close()
