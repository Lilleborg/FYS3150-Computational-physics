import numpy as np
import matplotlib.pyplot as plt

def exact_sol(x):
	return 1-(1-np.exp(-10.0))*x-np.exp(-10.0*x)

test = "gauss_elim_"
plt.figure(1)
for k in range(1,3):
	try:
		numerical = np.loadtxt("build/"+test+str(k)+"sol.dat")
		x = np.loadtxt("build/"+test+str(k)+"points.dat")
	except:
		print "Failed in loading datafiles"
		exit()

	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
LU = np.loadtxt("build/LU_decompsol.dat")
plt.plot(x,LU,"ro",label="LU")
exact = exact_sol(x)
plt.plot(x,exact,"r--",label="Exact")
plt.xlabel("$x$")
plt.ylabel("$u(x)$")
plt.title("General numerical solution with varying number of points of the Poisson equation")
plt.legend()

# plt.figure(2)
# for k in range(1,4):
# 	try:
# 		numerical = np.loadtxt("build/"+test+str(k)+"simpl"+"sol.dat")
# 		x = np.loadtxt("build/"+test+str(k)+"simpl"+"points.dat")
# 	except:
# 		print "Failed in loading datafiles"
# 		exit()

# 	plt.plot(x,numerical,label= "Numerical, n= "+str(10**k))
# plt.plot(x,exact,"r--",label="Exact")
# plt.xlabel("$x$")
# plt.ylabel("$u(x)$")
# plt.title("Special numerical solution with varying number of points of the Poisson equation")
# plt.legend()
plt.show()