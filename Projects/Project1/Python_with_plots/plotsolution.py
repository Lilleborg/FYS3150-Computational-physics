import numpy as np
import matplotlib.pyplot as plt
import sys

def exact_sol(x):
	return 1-(1-np.exp(-10.0))*x-np.exp(-10.0*x)
test = "gauss_elim_"
n = 3
for k in range(1,n+1):
	try:
		numerical = np.loadtxt("../build/"+test+str(k)+"sol.dat")
		x = np.loadtxt("../build/"+test+str(k)+"points.dat")
		
	except:
		print "Failed in loading datafiles"
		exit()
	plt.figure(1)
	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
	

exact = exact_sol(x)
plt.plot(x,exact,"r-.",label="Exact")
plt.xlabel(r"$x$")
plt.ylabel(r"$u(x)$")
plt.title("Gaussian elimination with varying number of grid points\n of the Poisson equation")
plt.legend()
plt.grid("on")
plt.savefig("plot_solution_vs_exact.pdf")
plt.tight_layout()

plt.figure(2)
for k in range(1,n+1):
	try:
		numerical = np.loadtxt("../build/"+test+str(k)+"sol.dat")
		x = np.loadtxt("../build/"+test+str(k)+"points.dat")
		LU = np.loadtxt("../build/LU_decomp"+str(k)+"sol.dat")
	except:
		print "Failed in loading datafiles"
		exit()
	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
	plt.plot(x,LU,"--",label="LU, n= "+str(10**k))
plt.xlabel(r"$x$")
plt.ylabel(r"$u(x)$")
plt.title("Gaussian elimination vs LU-decomposition \nwith varying number of grid points of the Poisson equation")
plt.legend()
plt.grid("on")
plt.savefig("plot_gauss_vs_LU.pdf")
plt.tight_layout()

plt.show()