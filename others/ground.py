import ctypes
import os
import matplotlib.pyplot as matlab



class point(ctypes.Structure):
	_fields_ = [('x', ctypes.c_float),
				('y', ctypes.c_float)]



class ground(object):

	_file = 'ground.dll'
	_path = os.path.join(*(os.path.split(__file__)[:-1]+(_file,)))
	_mod  = ctypes.cdll.LoadLibrary(_path)
	_ground = _mod.ground
	_ground.argtypes = (ctypes.POINTER(point), ctypes.c_int,ctypes.c_float)


	def __init__(self, numbers, radius):
		self._numbers = numbers
		self._radius  = radius
		self.a = (numbers*point)()
		self.b = ctypes.cast(self.a,ctypes.POINTER(point))
		self._ground(self.b,numbers,radius)
	

	def paint(self):
		for i in range(self._numbers):
			matlab.plot(self.b[i].x,self.b[i].y,'r.')
	
	
	def show(self):
		matlab.show()