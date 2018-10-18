import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

def unpack(nr_objects,read_array):
	list_of_objects = []
	for i in range(nr_objects):
		list_of_objects.append(read_array[:,i::nr_objects])
	return list_of_objects

def plotbody(pos,ax):
	ax.plot(pos[0],pos[1],pos[2])



if __name__ == '__main__':
	positions = np.loadtxt('../build/positions_euler.txt', unpack=True)
	nr_objects = 3
	
	sun = positions[:,::nr_objects]
	earth = positions[:,1::nr_objects]
	jupiter = positions[:,2::nr_objects]
	#earth2 = positions[:,2::nr_objects]
	
	fig = plt.figure(2)
	ax = fig.gca(projection='3d')
	ax.plot(earth[0,::100],earth[1,::100],earth[2,::100],label = 'earth')
	ax.plot(jupiter[0,::100],jupiter[1,::100],jupiter[2,::100],label = 'Jupiter')
	#ax.plot(earth2[0,::100],earth2[1,::100],earth2[2,::100])
	ax.plot(sun[0,::100],sun[1,::100],sun[2,::100],'ro')
	#ax.plot([rvec[0,0]],[rvec[1,0]],[rvec[2,0]],'yo')
	plt.legend()
	ax.set_xlabel('x [m]')
	ax.set_ylabel('y [m]')
	ax.set_zlabel('z [m]')
	plt.show()