# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from gpr_collect/GprTrace.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy

class GprTrace(genpy.Message):
  _md5sum = "b4513f925d00b8c1929dd5775e542a50"
  _type = "gpr_collect/GprTrace"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """time rosTime_
int64 traceSize_
uint16 headerSize_
string headerID_
uint32 stampCount_
uint32 traceNumber_
uint32 odoTick_
float64 tracePos_
float64 duration_
uint32 traceStatusFlag_
uint16 numStacks_
uint16 hardwareFlag_
int16[] traceData_
int32 dataSize_
string sampleInterval_
string frequency_
"""
  __slots__ = ['rosTime_','traceSize_','headerSize_','headerID_','stampCount_','traceNumber_','odoTick_','tracePos_','duration_','traceStatusFlag_','numStacks_','hardwareFlag_','traceData_','dataSize_','sampleInterval_','frequency_']
  _slot_types = ['time','int64','uint16','string','uint32','uint32','uint32','float64','float64','uint32','uint16','uint16','int16[]','int32','string','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       rosTime_,traceSize_,headerSize_,headerID_,stampCount_,traceNumber_,odoTick_,tracePos_,duration_,traceStatusFlag_,numStacks_,hardwareFlag_,traceData_,dataSize_,sampleInterval_,frequency_

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GprTrace, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.rosTime_ is None:
        self.rosTime_ = genpy.Time()
      if self.traceSize_ is None:
        self.traceSize_ = 0
      if self.headerSize_ is None:
        self.headerSize_ = 0
      if self.headerID_ is None:
        self.headerID_ = ''
      if self.stampCount_ is None:
        self.stampCount_ = 0
      if self.traceNumber_ is None:
        self.traceNumber_ = 0
      if self.odoTick_ is None:
        self.odoTick_ = 0
      if self.tracePos_ is None:
        self.tracePos_ = 0.
      if self.duration_ is None:
        self.duration_ = 0.
      if self.traceStatusFlag_ is None:
        self.traceStatusFlag_ = 0
      if self.numStacks_ is None:
        self.numStacks_ = 0
      if self.hardwareFlag_ is None:
        self.hardwareFlag_ = 0
      if self.traceData_ is None:
        self.traceData_ = []
      if self.dataSize_ is None:
        self.dataSize_ = 0
      if self.sampleInterval_ is None:
        self.sampleInterval_ = ''
      if self.frequency_ is None:
        self.frequency_ = ''
    else:
      self.rosTime_ = genpy.Time()
      self.traceSize_ = 0
      self.headerSize_ = 0
      self.headerID_ = ''
      self.stampCount_ = 0
      self.traceNumber_ = 0
      self.odoTick_ = 0
      self.tracePos_ = 0.
      self.duration_ = 0.
      self.traceStatusFlag_ = 0
      self.numStacks_ = 0
      self.hardwareFlag_ = 0
      self.traceData_ = []
      self.dataSize_ = 0
      self.sampleInterval_ = ''
      self.frequency_ = ''

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2IqH.pack(_x.rosTime_.secs, _x.rosTime_.nsecs, _x.traceSize_, _x.headerSize_))
      _x = self.headerID_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I2dI2H.pack(_x.stampCount_, _x.traceNumber_, _x.odoTick_, _x.tracePos_, _x.duration_, _x.traceStatusFlag_, _x.numStacks_, _x.hardwareFlag_))
      length = len(self.traceData_)
      buff.write(_struct_I.pack(length))
      pattern = '<%sh'%length
      buff.write(struct.pack(pattern, *self.traceData_))
      buff.write(_struct_i.pack(self.dataSize_))
      _x = self.sampleInterval_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.frequency_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.rosTime_ is None:
        self.rosTime_ = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 18
      (_x.rosTime_.secs, _x.rosTime_.nsecs, _x.traceSize_, _x.headerSize_,) = _struct_2IqH.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.headerID_ = str[start:end].decode('utf-8')
      else:
        self.headerID_ = str[start:end]
      _x = self
      start = end
      end += 36
      (_x.stampCount_, _x.traceNumber_, _x.odoTick_, _x.tracePos_, _x.duration_, _x.traceStatusFlag_, _x.numStacks_, _x.hardwareFlag_,) = _struct_3I2dI2H.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sh'%length
      start = end
      end += struct.calcsize(pattern)
      self.traceData_ = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (self.dataSize_,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.sampleInterval_ = str[start:end].decode('utf-8')
      else:
        self.sampleInterval_ = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.frequency_ = str[start:end].decode('utf-8')
      else:
        self.frequency_ = str[start:end]
      self.rosTime_.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2IqH.pack(_x.rosTime_.secs, _x.rosTime_.nsecs, _x.traceSize_, _x.headerSize_))
      _x = self.headerID_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I2dI2H.pack(_x.stampCount_, _x.traceNumber_, _x.odoTick_, _x.tracePos_, _x.duration_, _x.traceStatusFlag_, _x.numStacks_, _x.hardwareFlag_))
      length = len(self.traceData_)
      buff.write(_struct_I.pack(length))
      pattern = '<%sh'%length
      buff.write(self.traceData_.tostring())
      buff.write(_struct_i.pack(self.dataSize_))
      _x = self.sampleInterval_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.frequency_
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.rosTime_ is None:
        self.rosTime_ = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 18
      (_x.rosTime_.secs, _x.rosTime_.nsecs, _x.traceSize_, _x.headerSize_,) = _struct_2IqH.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.headerID_ = str[start:end].decode('utf-8')
      else:
        self.headerID_ = str[start:end]
      _x = self
      start = end
      end += 36
      (_x.stampCount_, _x.traceNumber_, _x.odoTick_, _x.tracePos_, _x.duration_, _x.traceStatusFlag_, _x.numStacks_, _x.hardwareFlag_,) = _struct_3I2dI2H.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sh'%length
      start = end
      end += struct.calcsize(pattern)
      self.traceData_ = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=length)
      start = end
      end += 4
      (self.dataSize_,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.sampleInterval_ = str[start:end].decode('utf-8')
      else:
        self.sampleInterval_ = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.frequency_ = str[start:end].decode('utf-8')
      else:
        self.frequency_ = str[start:end]
      self.rosTime_.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2IqH = struct.Struct("<2IqH")
_struct_i = struct.Struct("<i")
_struct_3I2dI2H = struct.Struct("<3I2dI2H")
