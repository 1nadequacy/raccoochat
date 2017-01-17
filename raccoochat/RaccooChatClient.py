import readline
import sys
import time
import thread
import datetime
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
        for msg in message_array:
            shift = 10 - len(msg.userName)
            print '[%s] %s %s : %s ' % (msg.time, ' ' * shift, msg.userName, msg.textMessage)

    def print_users(self, users_array):
        print 'Users online: %s.' % (', '.join(map(str, users_array)))

    def print_commands(self):
        for val in MAP_COMMAND.values():
            print val

    def get_current_time(self, time):
        """
        current_time = str(time.hour) + ':'
        if len(str(time.minute)) == 1: current_time += '0'
        current_time += str(time.minute)
        return current_time
        """
        return '%d:%d' % (time.hour, time.minute)

    def get_messages(self, user):
        while True:
            time.sleep(1)
            sys.stdout.write('\r' + ' ' * (len(readline.get_line_buffer()) + 2) + '\r')
            self.print_messages(self.client.getNewMessages(user))
            sys.stdout.write(readline.get_line_buffer())
            sys.stdout.flush()

    def work_with_server(self):
        while True:
            user_nickname = raw_input('Input your nickname: ')
            if self.client.connectUser(user_nickname):
                print 'Welcome to main chat.'
                print 'Write "/command" for more information'
                break

        thread.start_new_thread(self.get_messages, (user_nickname,))
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
                    self.client.disconnectUser(user_nickname)
                    break
                else:
                    print 'Incorrect command. Write "/command" for more information'
            else:
                new_message = Message()
                new_message.time = self.get_current_time(datetime.datetime.now())
                new_message.userName = user_nickname
                new_message.textMessage = input_text
                self.client.addMessage(new_message)
                self.print_messages(self.client.getNewMessages(user_nickname))

    def __del__(self):
        self.transport.close()
