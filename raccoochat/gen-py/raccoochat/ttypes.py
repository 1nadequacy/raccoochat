#
# Autogenerated by Thrift Compiler (0.10.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
import sys

from thrift.transport import TTransport


class UserData(object):
    """
    Attributes:
     - userName
     - userPassword
     - status
     - messagesId
     - privateMessagesId
    """

    thrift_spec = (
        None,  # 0
        (1, TType.STRING, 'userName', 'UTF8', None, ),  # 1
        (2, TType.STRING, 'userPassword', 'UTF8', None, ),  # 2
        (3, TType.I32, 'status', None, None, ),  # 3
        (4, TType.I32, 'messagesId', None, None, ),  # 4
        (5, TType.I32, 'privateMessagesId', None, None, ),  # 5
    )

    def __init__(self, userName=None, userPassword=None, status=None, messagesId=None, privateMessagesId=None,):
        self.userName = userName
        self.userPassword = userPassword
        self.status = status
        self.messagesId = messagesId
        self.privateMessagesId = privateMessagesId

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, (self.__class__, self.thrift_spec))
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.STRING:
                    self.userName = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.STRING:
                    self.userPassword = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.status = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.messagesId = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 5:
                if ftype == TType.I32:
                    self.privateMessagesId = iprot.readI32()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, (self.__class__, self.thrift_spec)))
            return
        oprot.writeStructBegin('UserData')
        if self.userName is not None:
            oprot.writeFieldBegin('userName', TType.STRING, 1)
            oprot.writeString(self.userName.encode('utf-8') if sys.version_info[0] == 2 else self.userName)
            oprot.writeFieldEnd()
        if self.userPassword is not None:
            oprot.writeFieldBegin('userPassword', TType.STRING, 2)
            oprot.writeString(self.userPassword.encode('utf-8') if sys.version_info[0] == 2 else self.userPassword)
            oprot.writeFieldEnd()
        if self.status is not None:
            oprot.writeFieldBegin('status', TType.I32, 3)
            oprot.writeI32(self.status)
            oprot.writeFieldEnd()
        if self.messagesId is not None:
            oprot.writeFieldBegin('messagesId', TType.I32, 4)
            oprot.writeI32(self.messagesId)
            oprot.writeFieldEnd()
        if self.privateMessagesId is not None:
            oprot.writeFieldBegin('privateMessagesId', TType.I32, 5)
            oprot.writeI32(self.privateMessagesId)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class Message(object):
    """
    Attributes:
     - sendingTime
     - userId
     - textMessage
    """

    thrift_spec = (
        None,  # 0
        (1, TType.STRING, 'sendingTime', 'UTF8', None, ),  # 1
        (2, TType.I32, 'userId', None, None, ),  # 2
        (3, TType.STRING, 'textMessage', 'UTF8', None, ),  # 3
    )

    def __init__(self, sendingTime=None, userId=None, textMessage=None,):
        self.sendingTime = sendingTime
        self.userId = userId
        self.textMessage = textMessage

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, (self.__class__, self.thrift_spec))
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.STRING:
                    self.sendingTime = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.userId = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.STRING:
                    self.textMessage = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, (self.__class__, self.thrift_spec)))
            return
        oprot.writeStructBegin('Message')
        if self.sendingTime is not None:
            oprot.writeFieldBegin('sendingTime', TType.STRING, 1)
            oprot.writeString(self.sendingTime.encode('utf-8') if sys.version_info[0] == 2 else self.sendingTime)
            oprot.writeFieldEnd()
        if self.userId is not None:
            oprot.writeFieldBegin('userId', TType.I32, 2)
            oprot.writeI32(self.userId)
            oprot.writeFieldEnd()
        if self.textMessage is not None:
            oprot.writeFieldBegin('textMessage', TType.STRING, 3)
            oprot.writeString(self.textMessage.encode('utf-8') if sys.version_info[0] == 2 else self.textMessage)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class InvalidNameException(TException):
    """
    Attributes:
     - errorCode
     - errorMessage
    """

    thrift_spec = (
        None,  # 0
        (1, TType.I32, 'errorCode', None, None, ),  # 1
        (2, TType.STRING, 'errorMessage', 'UTF8', None, ),  # 2
    )

    def __init__(self, errorCode=None, errorMessage=None,):
        self.errorCode = errorCode
        self.errorMessage = errorMessage

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, (self.__class__, self.thrift_spec))
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.errorCode = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.STRING:
                    self.errorMessage = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, (self.__class__, self.thrift_spec)))
            return
        oprot.writeStructBegin('InvalidNameException')
        if self.errorCode is not None:
            oprot.writeFieldBegin('errorCode', TType.I32, 1)
            oprot.writeI32(self.errorCode)
            oprot.writeFieldEnd()
        if self.errorMessage is not None:
            oprot.writeFieldBegin('errorMessage', TType.STRING, 2)
            oprot.writeString(self.errorMessage.encode('utf-8') if sys.version_info[0] == 2 else self.errorMessage)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __str__(self):
        return repr(self)

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
