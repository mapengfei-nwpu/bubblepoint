

#如果当前文件夹内有x.txt文件或者x_new.txt文件，则可以绘出点状图

import os
import matplotlib.pyplot as matlab

x=[]
y=[]
with open('x_new.txt','r') as file:
	for i in file:
		x.append(float(i))


with open('y_new.txt','r') as file:
	for i in file:
		y.append(float(i))


for i in range(719):
	matlab.plot(x[i],y[i],'r.')

matlab.show()