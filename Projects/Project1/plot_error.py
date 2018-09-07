import numpy as np 
import matplotlib.pyplot as plt 


n = 7
error = np.loadtxt("build/max_rel_errors_"+str(n)+".dat",unpack=True)


plt.figure(1)
plt.loglog(error[1],error[0])
plt.gca().invert_xaxis()
plt.xlabel("Stepsize, "+r"$log_{10}(h)$")
plt.ylabel("Max relative error, "+r"$log_{10}\left(\frac{v-u}{u}\right)$")
plt.title("Relative error between Gaussian elimination and exact solution")
plt.grid("on")
plt.tight_layout()
plt.savefig("plot_error.pdf")
plt.show()