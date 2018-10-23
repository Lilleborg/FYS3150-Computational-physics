import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams
import sys

def unpack(solver):
	path = "../build/"+solver + "_testing/"
	filetypes = ["ang_momentum_1e-","kinetic_1e-","potential_1e-"]
	for j in range(len(filetypes)):
		list_of_files = []
		for i in range(2,7):
			list_of_files.append(np.loadtxt(path + filetypes[j] + str(i) + ".txt"))
		if j == 0:
			angular_moment = np.asarray(list_of_files)
		elif j == 1:
			kinetic_energy = np.asarray(list_of_files)
		else:
			potential_energy = np.asarray(list_of_files)	
	return angular_moment, kinetic_energy, potential_energy

	# Plotting font
	font = {'size'   : 12}
	plt.matplotlib.rc('font', **font)
	rcParams.update({'figure.autolayout': True})

names = ["modulus of angular moment","kinetic energy","potential energy"]
solvers = ["Euler","Verlet"]
time = np.linspace(0,2,10)	# time array
results_Euler = unpack(solvers[0])
results_Verlet = unpack(solvers[1])

# Finding max error for y-limits

for k,results in enumerate([results_Euler,results_Verlet]):
	maxerror = 0
	for values in results:
		max_in_this = np.max(np.abs(values))
		if max_in_this>maxerror:
			maxerror = max_in_this

	plt.figure()
	for i,result in enumerate(results):
		plt.subplot(311+i)
		for j,values in enumerate(result):
			plt.plot(time,values,label="dt = 1e-{:d}".format(j+2))
			
		plt.ylabel("Relative error")
		plt.xlabel("Years")
		plt.tight_layout()
		plt.title("Relative error in the " + names[i])
		plt.legend(loc="lower left")
		plt.ylim(-maxerror*1.1,maxerror*1.1)
	plt.savefig("ugly_plot_error_"+solvers[k]+".pdf")

plt.show()
