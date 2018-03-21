import ctypes
import os
import matplotlib.pyplot as matlab


class point(ctypes.Structure):
	_fields_ = [('x', ctypes.c_float),
				('y', ctypes.c_float)]

class ground(object):

	

	_file = 'lib/range_kutta.dll'
	_path = os.path.join(*(os.path.split(__file__)[:-1]+(_file,)))
	_mod_1  = ctypes.cdll.LoadLibrary(_path)
	_mod_1.range_kutta.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int)
	

	_file = 'lib/ground.dll'
	_path = os.path.join(*(os.path.split(__file__)[:-1]+(_file,)))
	_mod  = ctypes.cdll.LoadLibrary(_path)
	_mod.many_rand_point.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.c_float)
	_mod.circleEdgeCreate.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.c_float)
	_mod.filt_many_1.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int)
	_mod.filt_many_1.restypes = (ctypes.c_int)
	_mod.filt_many_2.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point))
	_mod.filt_many_3.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int)
	_mod.filt_many_3.restypes = (ctypes.c_int)
	_mod.filt_many_4.argtypes = (ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point),ctypes.c_int,ctypes.POINTER(point))
	many_rand_point = _mod.many_rand_point
	circleEdgeCreate = _mod.circleEdgeCreate
	filt_many_1 = _mod.filt_many_1
	filt_many_2 = _mod.filt_many_2
	filt_many_3 = _mod.filt_many_3
	filt_many_4 = _mod.filt_many_4

	def __init__(self,random_points_number,edge_points_number1,edge_points_number2,R,r1,r2):
		self.m=random_points_number
		self.R=R

		self.n1=edge_points_number1
		self.n2=edge_points_number2
		self.r1=r1
		self.r2=r2


		_random_points = (self.m*point)()
		self.random_points = ctypes.cast(_random_points,ctypes.POINTER(point))
		self.many_rand_point(self.random_points,self.m,R);


		_edge_points1 = (self.n1*point)()
		self.edge_points1 = ctypes.cast(_edge_points1,ctypes.POINTER(point))
		self.circleEdgeCreate(self.edge_points1, self.n1, self.r1);


		_edge_points2 = (self.n2*point)()
		self.edge_points2 = ctypes.cast(_edge_points2,ctypes.POINTER(point))
		self.circleEdgeCreate(self.edge_points2, self.n2, self.r2);


		self.c=self.filt_many_3(self.random_points,self.m,self.edge_points1,self.n1,self.edge_points2,self.n2)
		_filtered_points = (self.c*point)()
		self.filtered_points = ctypes.cast(_filtered_points,ctypes.POINTER(point))
		self.filt_many_4(self.random_points,self.m,self.edge_points1,self.n1,self.edge_points2,self.n2,self.filtered_points)

		_arranged_points = (self.c*point)()
		self.arranged_points = ctypes.cast(_arranged_points,ctypes.POINTER(point))
		for i in range(self.c):
			self.arranged_points[i].x=self.filtered_points[i].x
			self.arranged_points[i].y=self.filtered_points[i].y
		self._mod_1.range_kutta(self.arranged_points,self.c,self.edge_points1,self.n1,self.edge_points2,self.n2)


	def output(self,file_name):
		a='';b=''
		for i in range(self.c):
			a += '%.4f' % self.filtered_points[i].x + '\n'
			b += '%.4f' % self.filtered_points[i].y + '\n'		
		f = open(file_name, 'w')
		f.write(a);
		f.write(b);
		f.close();


def paint(points,n):
	for i in range(n):
			matlab.plot(points[i].x,points[i].y,'r.')
	matlab.show()