import numpy as np 
import matplotlib.pyplot as plt 


n = 8
error = np.loadtxt("../build/max_rel_errors_"+str(n)+".dat",unpack=True)


plt.figure(1)
plt.loglog(error[1],error[0])
plt.gca().invert_xaxis()
plt.xlabel("Stepsize, "+r"$h$")
plt.ylabel("Max relative error, "+r"$\frac{|v-u|}{|u|}$")
plt.title("Relative error between Gaussian elimination and exact solution")
plt.grid("on")
plt.tight_layout()
plt.savefig("plot_error.pdf")
plt.show()