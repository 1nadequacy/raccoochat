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
        self.current_user = 'Guest'

        self.transport.open()
        print '---------- Welcome to RaccooChat ----------\n'

    def print_messages(self, message_array):
        for message in message_array:
            shift = self.client.getMaxUserNameSize() - len(message.userName)
            print '[%s]%s %s : %s ' % (message.time, ' ' * shift, message.userName, message.textMessage)

    def print_private_messages(self, message_array):
        for message in message_array:
            shift = self.client.getMaxUserNameSize() - len(message.userName)
            print '[%s] From%s - %s : %s ' % (message.time, ' ' * shift, message.userName, message.textMessage)

    def print_users(self, users_array):
        print 'Users online: %s.' % (', '.join(map(str, users_array)))

    def print_commands(self):
        for key, value in MAP_COMMANDS.items():
            print '%s - %s' % (key, value)

    def create_new_message(self, text_message):
        new_message = SimpleMessage()
        new_message.time = time.strftime('%H:%M')
        new_message.userName = self.current_user
        new_message.textMessage = text_message
        return new_message

    def get_messages(self):
        while True:
            time.sleep(1)
            sys.stdout.write('\r' + ' ' * (len(readline.get_line_buffer()) + 2) + '\r')
            self.print_messages(self.client.getNewMessages(self.current_user))
            self.print_private_messages(self.client.getNewPrivateMessages(self.current_user))
            sys.stdout.write(readline.get_line_buffer())
            sys.stdout.flush()

    def login_user(self):
        while True:
            command_line = raw_input('Hello. Do you have an account? [y/n]: ')
            if command_line == 'y':
                while True:
                    user_name = raw_input('Enter your login: ')
                    try:
                        self.client.findUser(user_name)
                        self.client.checkIfUserOffline(user_name)
                        while True:
                            self.current_user = user_name
                            user_password = raw_input('Enter your password: ')
                            try:
                                self.client.checkPassword(user_name, user_password)
                                self.client.connectUser(user_name)
                                print 'Welcome to the chat.'
                                return
                            except InvalidNameException as e:
                                print e.errorMessage
                    except InvalidNameException as e:
                        print e.errorMessage
            elif command_line == 'n':
                while True:
                    user_name = raw_input('Enter your new login: ')
                    try:
                        self.client.validateName(user_name)
                        while True:
                            self.current_user = user_name
                            user_password = raw_input('Also you need to enter your new password: ')
                            try:
                                self.client.validatePassword(user_password)
                                self.client.registerUser(user_name, user_password)
                                self.client.connectUser(user_name)
                                print 'You have been registered. Welcome to the chat.'
                                return
                            except InvalidNameException as e:
                                print e.errorMessage
                    except InvalidNameException as e:
                        print e.errorMessage

    def work_with_server(self):
        self.login_user()
        thread.start_new_thread(self.get_messages, ())
        while True:
            input_text = raw_input()
            if input_text[0] == '/':
                command = input_text[1:]
                if command == 'command':
                    self.print_commands()
                elif command == 'users':
                    self.print_users(self.client.getAllOnlineUsers())
                elif command == 'history':
                    print '---------- Chat History ----------'
                    self.print_messages(self.client.getHistory())
                    print '----------------------------------'
                elif command == 'exit':
                    self.client.disconnectUser(self.current_user)
                    break
                else:
                    print 'Incorrect command. Write "/command" for more information'
            elif input_text[0] == '.':
                input_data = input_text[1:].split()
                destination = input_data[0]
                text_message = ' ' .join(map(str, input_data[1:]))
                if destination == self.current_user:
                    print 'You can\'t send a message to yourself.'
                else:
                    try:
                        self.client.findUser(destination)
                        try:
                            self.client.checkIfUserOnline(destination)
                        except:
                            print 'Message will be delivered when %s will be online' % destination
                        self.client.addPrivateMessage(self.create_new_message(text_message), destination)
                    except:
                        print 'User %s doesn\'t exist.' % destination
            else:
                self.client.addMessage(self.create_new_message(input_text))

            self.print_messages(self.client.getNewMessages(self.current_user))
            self.print_private_messages(self.client.getNewPrivateMessages(self.current_user))

    def __del__(self):
        self.client.disconnectUser(self.current_user)
        self.transport.close()
