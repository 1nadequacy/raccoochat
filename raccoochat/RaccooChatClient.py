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
        self.user_id = None

        self.transport.open()
        print '---------- Welcome to RaccooChat ----------\n'

    def remove_spaces(self, text):
        text = text.strip()
        return " ".join(text.split())

    def print_messages(self, message_array):
        for message in message_array:
            user_name = self.client.getUserName(message.userId)
            shift = 10 - len(user_name)
            print '[%s]%s %s : %s ' % (message.sendingTime, ' ' * shift, user_name, message.textMessage)

    def print_private_messages(self, message_array):
        for message in message_array:
            user_name = self.client.getUserName(message.userId)
            shift = 10 - len(user_name)
            print '[%s] From%s - %s : %s ' % (message.sendingTime, ' ' * shift, user_name, message.textMessage)

    def print_users(self, users_array):
        print 'Users online: %s.' % (', '.join(map(str, users_array)))

    def print_commands(self):
        for key, value in MAP_COMMANDS.items():
            print '%s - %s' % (key, value)

    def create_new_message(self, text_message):
        new_message = Message()
        new_message.sendingTime = time.strftime('%H:%M')
        new_message.userId = self.user_id
        new_message.textMessage = text_message
        return new_message

    def get_messages(self):
        while True:
            time.sleep(1)
            sys.stdout.write('\r' + ' ' * (len(readline.get_line_buffer()) + 2) + '\r')
            self.print_messages(self.client.getNewMessages(self.user_id))
            self.print_private_messages(self.client.getNewPrivateMessages(self.user_id))
            sys.stdout.write(readline.get_line_buffer())
            sys.stdout.flush()

    def login_user(self):
        while True:
            command_line = raw_input('Hello. Do you have an account? [y/n]: ')
            if command_line == 'y':
                while True:
                    user_name = raw_input('Enter your login: ')
                    try:
                        self.client.ifRegisteredUser(user_name)
                        self.client.ifUserOffline(user_name)
                        while True:
                            user_password = raw_input('Enter your password: ')
                            try:
                                self.client.comparePassword(user_name, user_password)
                                self.user_id = self.client.connectUser(user_name)
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
                            user_password = raw_input('Also you need to enter your new password: ')
                            try:
                                self.client.validatePassword(user_password)
                                self.client.registrationUser(user_name, user_password)
                                self.user_id = self.client.connectUser(user_name)
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
                    self.print_messages(self.client.getChatHistory())
                    print '----------------------------------'
                elif command == 'exit':
                    self.client.disconnectUser(self.user_id)
                    break
                else:
                    print 'Incorrect command. Write "/command" for more information'
            elif input_text[0] == '.':
                input_data = input_text[1:].split()
                destination = input_data[0]
                text_message = ' ' .join(map(str, input_data[1:]))
                if destination == self.client.getUserName(self.user_id):
                    print 'You can\'t send a message to yourself.'
                else:
                    try:
                        self.client.ifRegisteredUser(destination)
                        try:
                            self.client.ifUserOnline(destination)
                        except:
                            print 'Message will be delivered when %s will be online' % destination
                        text_message = self.remove_spaces(text_message)
                        self.client.addPrivateMessage(self.client.getUserId(destination), self.create_new_message(text_message))
                    except:
                        print 'User %s doesn\'t exist.' % destination
            else:
                input_text = self.remove_spaces(input_text)
                self.client.addMessage(self.create_new_message(input_text))

            self.print_messages(self.client.getNewMessages(self.user_id))
            self.print_private_messages(self.client.getNewPrivateMessages(self.user_id))

    def __del__(self):
        self.transport.close()
