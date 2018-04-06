#
# Autogenerated by Thrift Compiler (0.11.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py:slots
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
from thrift.TRecursive import fix_spec

import sys
import logging
from .ttypes import *
from thrift.Thrift import TProcessor
from thrift.transport import TTransport
all_structs = []


class Iface(object):
    def subscribe(self, block_id, ops):
        """
        Parameters:
         - block_id
         - ops
        """
        pass

    def unsubscribe(self, block_id, ops):
        """
        Parameters:
         - block_id
         - ops
        """
        pass


class Client(Iface):
    def __init__(self, iprot, oprot=None):
        self._iprot = self._oprot = iprot
        if oprot is not None:
            self._oprot = oprot
        self._seqid = 0

    def subscribe(self, block_id, ops):
        """
        Parameters:
         - block_id
         - ops
        """
        self.send_subscribe(block_id, ops)

    def send_subscribe(self, block_id, ops):
        self._oprot.writeMessageBegin('subscribe', TMessageType.ONEWAY, self._seqid)
        args = subscribe_args()
        args.block_id = block_id
        args.ops = ops
        args.write(self._oprot)
        self._oprot.writeMessageEnd()
        self._oprot.trans.flush()

    def unsubscribe(self, block_id, ops):
        """
        Parameters:
         - block_id
         - ops
        """
        self.send_unsubscribe(block_id, ops)

    def send_unsubscribe(self, block_id, ops):
        self._oprot.writeMessageBegin('unsubscribe', TMessageType.ONEWAY, self._seqid)
        args = unsubscribe_args()
        args.block_id = block_id
        args.ops = ops
        args.write(self._oprot)
        self._oprot.writeMessageEnd()
        self._oprot.trans.flush()


class Processor(Iface, TProcessor):
    def __init__(self, handler):
        self._handler = handler
        self._processMap = {}
        self._processMap["subscribe"] = Processor.process_subscribe
        self._processMap["unsubscribe"] = Processor.process_unsubscribe

    def process(self, iprot, oprot):
        (name, type, seqid) = iprot.readMessageBegin()
        if name not in self._processMap:
            iprot.skip(TType.STRUCT)
            iprot.readMessageEnd()
            x = TApplicationException(TApplicationException.UNKNOWN_METHOD, 'Unknown function %s' % (name))
            oprot.writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
            x.write(oprot)
            oprot.writeMessageEnd()
            oprot.trans.flush()
            return
        else:
            self._processMap[name](self, seqid, iprot, oprot)
        return True

    def process_subscribe(self, seqid, iprot, oprot):
        args = subscribe_args()
        args.read(iprot)
        iprot.readMessageEnd()
        try:
            self._handler.subscribe(args.block_id, args.ops)
        except TTransport.TTransportException:
            raise
        except Exception:
            logging.exception('Exception in oneway handler')

    def process_unsubscribe(self, seqid, iprot, oprot):
        args = unsubscribe_args()
        args.read(iprot)
        iprot.readMessageEnd()
        try:
            self._handler.unsubscribe(args.block_id, args.ops)
        except TTransport.TTransportException:
            raise
        except Exception:
            logging.exception('Exception in oneway handler')

# HELPER FUNCTIONS AND STRUCTURES


class subscribe_args(object):
    """
    Attributes:
     - block_id
     - ops
    """

    __slots__ = (
        'block_id',
        'ops',
    )


    def __init__(self, block_id=None, ops=None,):
        self.block_id = block_id
        self.ops = ops

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.block_id = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.LIST:
                    self.ops = []
                    (_etype3, _size0) = iprot.readListBegin()
                    for _i4 in range(_size0):
                        _elem5 = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                        self.ops.append(_elem5)
                    iprot.readListEnd()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('subscribe_args')
        if self.block_id is not None:
            oprot.writeFieldBegin('block_id', TType.I32, 1)
            oprot.writeI32(self.block_id)
            oprot.writeFieldEnd()
        if self.ops is not None:
            oprot.writeFieldBegin('ops', TType.LIST, 2)
            oprot.writeListBegin(TType.STRING, len(self.ops))
            for iter6 in self.ops:
                oprot.writeString(iter6.encode('utf-8') if sys.version_info[0] == 2 else iter6)
            oprot.writeListEnd()
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, getattr(self, key))
             for key in self.__slots__]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        for attr in self.__slots__:
            my_val = getattr(self, attr)
            other_val = getattr(other, attr)
            if my_val != other_val:
                return False
        return True

    def __ne__(self, other):
        return not (self == other)
all_structs.append(subscribe_args)
subscribe_args.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'block_id', None, None, ),  # 1
    (2, TType.LIST, 'ops', (TType.STRING, 'UTF8', False), None, ),  # 2
)


class unsubscribe_args(object):
    """
    Attributes:
     - block_id
     - ops
    """

    __slots__ = (
        'block_id',
        'ops',
    )


    def __init__(self, block_id=None, ops=None,):
        self.block_id = block_id
        self.ops = ops

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.block_id = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.LIST:
                    self.ops = []
                    (_etype10, _size7) = iprot.readListBegin()
                    for _i11 in range(_size7):
                        _elem12 = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                        self.ops.append(_elem12)
                    iprot.readListEnd()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('unsubscribe_args')
        if self.block_id is not None:
            oprot.writeFieldBegin('block_id', TType.I32, 1)
            oprot.writeI32(self.block_id)
            oprot.writeFieldEnd()
        if self.ops is not None:
            oprot.writeFieldBegin('ops', TType.LIST, 2)
            oprot.writeListBegin(TType.STRING, len(self.ops))
            for iter13 in self.ops:
                oprot.writeString(iter13.encode('utf-8') if sys.version_info[0] == 2 else iter13)
            oprot.writeListEnd()
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, getattr(self, key))
             for key in self.__slots__]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        for attr in self.__slots__:
            my_val = getattr(self, attr)
            other_val = getattr(other, attr)
            if my_val != other_val:
                return False
        return True

    def __ne__(self, other):
        return not (self == other)
all_structs.append(unsubscribe_args)
unsubscribe_args.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'block_id', None, None, ),  # 1
    (2, TType.LIST, 'ops', (TType.STRING, 'UTF8', False), None, ),  # 2
)
fix_spec(all_structs)
del all_structs

