import numpy as np
import matplotlib.pyplot as plt
import sys

def exact_sol(x):
	return 1-(1-np.exp(-10.0))*x-np.exp(-10.0*x)

test = "gauss_elim_"
plt.figure(1)
for k in range(1,int(sys.argv[1])):
	try:
		numerical = np.loadtxt("build/"+test+str(k)+"sol.dat")
		x = np.loadtxt("build/"+test+str(k)+"points.dat")
		LU = np.loadtxt("build/LU_decomp"+str(k)+"sol.dat")
	except:
		print "Failed in loading datafiles"
		exit()

	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
	plt.plot(x,LU,"--",label="LU, n= "+str(10**k))
exact = exact_sol(x)
plt.plot(x,exact,"r-.",label="Exact")
plt.xlabel("$x$")
plt.ylabel("$u(x)$")
plt.title("General numerical solution with varying number of points of the Poisson equation")
plt.legend()
plt.show()