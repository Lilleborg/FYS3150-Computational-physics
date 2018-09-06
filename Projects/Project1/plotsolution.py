import numpy as np
import matplotlib.pyplot as plt

test = "generalmethod"
def exact_sol(x):
	return 1-(1-np.exp(-10.0))*x-np.exp(-10.0*x)

for k in range(1,4):
	try:
		numerical = np.loadtxt("build/"+test+str(k)+"sol.dat")
		x = np.loadtxt("build/"+test+str(k)+"points.dat")
	except:
		print "Failed in loading datafiles"
		exit()

	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
exact = exact_sol(x)
plt.plot(x,exact,"r--",label="Exact")
plt.xlabel("$x$")
plt.ylabel("$u(x)$")
plt.title("Numerical solution with varying number of points of the Poisson equation")
plt.legend()
plt.show()