import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import rcParams
import sys
import glob

def unpack(massfolder):
	path = "../build/Earth_Jupiter/"+massfolder + "/"
	list_objects = []
	list_conserved = []
	names = ["Earth","Sun","Jupiter"]
	quantity = ["ang_momentum","kinetic","potential"]
	for i,name in enumerate(names):
		print '---Loading file---'
		list_objects.append(np.loadtxt(path+"positions_"+name+".txt",unpack=True))
		print path+"positions_"+name+".txt"
		print '---Loading file---'
		list_conserved.append(np.loadtxt(path+quantity[i]+".txt",unpack=True))
		print path+quantity[i]+".txt"
	return list_objects,names,list_conserved,quantity

masses = ["1","10","1000"]
# Looping different jupiter masses
for mass in masses:
	posistion,names,conserved_quantity,names_quantity = unpack("mass_"+mass)

	# Plotting position
	plt.figure()
	for pos,name in zip(posistion,names):
		if name == "Sun":
			plt.plot(pos[0,0],pos[1,0],'o',label=name)	
		else:
			plt.plot(pos[0],pos[1],label=name)

	plt.axis('equal')
	plt.title("Earth affected by Jupiter with mass "+mass)
	plt.xlabel('x [AU]')
	plt.ylabel('y [AU]')
	plt.legend(loc="best")
	plt.tight_layout()
	plt.savefig("plot_earth_jupiter"+mass + ".pdf")

	# Plotting 3D
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	plt.title("Earth affected by Jupiter with mass "+mass)
	for pos,name in zip(posistion,names):
		if name == "Sun":
			plt.plot(pos[0],pos[1],pos[2],'o',label=name)	
		else:
			plt.plot(pos[0],pos[1],pos[2],label=name)
	
	ax.set_xlabel('x [AU]')
	ax.set_ylabel('y [AU]')
	ax.set_zlabel('z [AU]')
	plt.legend(loc="best")
	plt.tight_layout()
	ax.set_zlim(-.3,.3)
	plt.savefig("3Dplot_earth_jupiter"+mass + ".pdf")

	# Plotting coserved quantity
	time = np.linspace(0,25,10)
	maxerror = 0
	for values in conserved_quantity:
		max_in_this = np.max(np.abs(values))
		if max_in_this>maxerror:
			maxerror = max_in_this
	plt.figure()
	for i,values in enumerate(conserved_quantity):
		plt.plot(time,values,label=names_quantity[i])
			
	plt.ylabel("Relative error")
	plt.xlabel("Years")
	plt.tight_layout()
	plt.title("Relative errors in the conserved quantities, jupiter mass " +mass)
	plt.legend(loc="best")
	plt.ylim(-maxerror*1.1,maxerror*1.1)
	plt.tight_layout()
	plt.savefig("plot_errors_jupiter"+mass+".pdf")
plt.show()