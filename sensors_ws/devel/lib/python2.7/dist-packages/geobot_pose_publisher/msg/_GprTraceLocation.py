# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from geobot_pose_publisher/GprTraceLocation.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy

class GprTraceLocation(genpy.Message):
  _md5sum = "ad9b5784e3da422663d2055d98f6046f"
  _type = "geobot_pose_publisher/GprTraceLocation"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """		time stamp
		string CoordinateFormat
		float64 Longitude
		float64 Latitude
		float64 Altitude
		string latitude_label
		string longitude_label
		string UTMZone"""
  __slots__ = ['stamp','CoordinateFormat','Longitude','Latitude','Altitude','latitude_label','longitude_label','UTMZone']
  _slot_types = ['time','string','float64','float64','float64','string','string','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       stamp,CoordinateFormat,Longitude,Latitude,Altitude,latitude_label,longitude_label,UTMZone

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GprTraceLocation, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.stamp is None:
        self.stamp = genpy.Time()
      if self.CoordinateFormat is None:
        self.CoordinateFormat = ''
      if self.Longitude is None:
        self.Longitude = 0.
      if self.Latitude is None:
        self.Latitude = 0.
      if self.Altitude is None:
        self.Altitude = 0.
      if self.latitude_label is None:
        self.latitude_label = ''
      if self.longitude_label is None:
        self.longitude_label = ''
      if self.UTMZone is None:
        self.UTMZone = ''
    else:
      self.stamp = genpy.Time()
      self.CoordinateFormat = ''
      self.Longitude = 0.
      self.Latitude = 0.
      self.Altitude = 0.
      self.latitude_label = ''
      self.longitude_label = ''
      self.UTMZone = ''

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
      buff.write(_struct_2I.pack(_x.stamp.secs, _x.stamp.nsecs))
      _x = self.CoordinateFormat
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3d.pack(_x.Longitude, _x.Latitude, _x.Altitude))
      _x = self.latitude_label
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.longitude_label
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.UTMZone
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
      if self.stamp is None:
        self.stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 8
      (_x.stamp.secs, _x.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.CoordinateFormat = str[start:end].decode('utf-8')
      else:
        self.CoordinateFormat = str[start:end]
      _x = self
      start = end
      end += 24
      (_x.Longitude, _x.Latitude, _x.Altitude,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.latitude_label = str[start:end].decode('utf-8')
      else:
        self.latitude_label = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.longitude_label = str[start:end].decode('utf-8')
      else:
        self.longitude_label = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.UTMZone = str[start:end].decode('utf-8')
      else:
        self.UTMZone = str[start:end]
      self.stamp.canon()
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
      buff.write(_struct_2I.pack(_x.stamp.secs, _x.stamp.nsecs))
      _x = self.CoordinateFormat
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3d.pack(_x.Longitude, _x.Latitude, _x.Altitude))
      _x = self.latitude_label
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.longitude_label
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.UTMZone
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
      if self.stamp is None:
        self.stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 8
      (_x.stamp.secs, _x.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.CoordinateFormat = str[start:end].decode('utf-8')
      else:
        self.CoordinateFormat = str[start:end]
      _x = self
      start = end
      end += 24
      (_x.Longitude, _x.Latitude, _x.Altitude,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.latitude_label = str[start:end].decode('utf-8')
      else:
        self.latitude_label = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.longitude_label = str[start:end].decode('utf-8')
      else:
        self.longitude_label = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.UTMZone = str[start:end].decode('utf-8')
      else:
        self.UTMZone = str[start:end]
      self.stamp.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2I = struct.Struct("<2I")
_struct_3d = struct.Struct("<3d")
