import numpy as np
import matplotlib.pyplot as plt


loadfile = np.genfromtxt("problem3_w0_eigenvec.txt")
#print loadfile[:,0]
N = len(loadfile[:,0])
#print N
rho = np.linspace(0,1,N+2)


#u[:,0] = column1 = eigenvector corresponding to first eigenvalue

for i in range(4):
    u = np.genfromtxt("problem3_w%g_eigenvec.txt" % i)
    u_new = np.zeros((N+2,N))
    for k in range(N):
        u_new[:,k] = np.concatenate([[0],u[:,k],[0]])
    
    for j in range(4):
        #np.concatenate([[0],u[:,j],[0]])
        #print u[:,j]
        plt.plot(rho,u_new[:,j], label=j)
        plt.xlabel(r"$\rho$")
        plt.ylabel("u")
        plt.title(r"Wavefunction for $\omega_%g$" % i)
    plt.legend()
    plt.savefig("plot_omega_%g.pdf" % i)
    plt.show()
    



u1 = np.genfromtxt("problem3_w0_eigenvec.txt")
u2 = np.genfromtxt("problem3_w3_eigenvec.txt")


"""
a = np.array([3,4,5])
a = np.concatenate([[0],a,[0]])
print a
"""
