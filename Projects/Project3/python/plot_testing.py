import numpy as np
import matplotlib.pyplot as plt
import sys

def unpack(solver):
	path = "../build/"+solver + "_testing/"
	filetypes = ["ang_momentum_1e-","kinetic_1e-","potential_1e-"]
	list_of_files = []
	for file in filetypes:
		for i in range(1,7):
			list_of_filenames.append(path + file + str(i) + ".txt")
	print list_of_filenames

	
	# list_names = [i.strip(path)  for i in list_of_files]
	# list_names = [i.strip(".txt")  for i in list_names]
	# list_objects_pos = []
	# for files in list_of_files:
	# 	print files
	# 	list_objects_pos.append(np.loadtxt(files,unpack=True))
	#return list_objects_pos,list_names

unpack("Verlet")