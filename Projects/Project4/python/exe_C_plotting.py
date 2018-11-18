import numpy as np 
from math import sinh,exp,cosh
import matplotlib.pyplot as plt 

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

def plotting(MCcycles):
    path = "../datafiles/ExerciseC/"
    temps = ["1.000000","2.400000"]
    Ename = "Energy_per_mc_"
    Mname = "Magnetic_per_mc_"
    Aname = "Accept_per_mc_"
    initial = ["Up","Random"]

    figE = plt.figure("Energy_per_MC")
    axE = plt.gca()
    figM = plt.figure("Abs_Magnetic_per_MC")
    axM = plt.gca()
    figA = plt.figure("Accept_per_MC")
    axA = plt.gca()

    axE.set_title(r"Mean energy")
    axE.set_xscale("log")
    axE.set_xlabel(r"$MC$",fontsize = 15)
    axE.set_ylabel(r'$\langle E \rangle(MC)$',fontsize = 15)
    
    axM.set_title("Mean magnetisation")
    axM.set_xscale("log")
    axM.set_xlabel(r"$MC$",fontsize = 15)
    axM.set_ylabel(r'$\langle |M|  \rangle (MC)$',fontsize = 15)

    axA.set_title("Accepted configurations")
    axA.set_xscale("log")
    axA.set_xlabel(r"$MC$",fontsize = 15)
    axA.set_ylabel(r'Number of accepted energies',fontsize = 15)

    for T in temps:
        for init in initial:
            Efile = path + init + "_T_" + T + Ename + str(MCcycles) + ".bin"
            Mfile = path + init + "_T_" + T + Mname + str(MCcycles) + ".bin"
            Afile = path + init + "_T_" + T + Aname + str(MCcycles) + ".bin"
            print("Loading ", Efile)
            print("Loading ", Mfile)
            print("Loading ", Afile)
            energies = np.fromfile(Efile)
            absMagnetic = np.fromfile(Mfile)
            Accept = np.fromfile(Afile)
            cycles = np.arange(0,len(energies),1)

            axE.plot(cycles[1:],energies[1:],'-o',alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axE.legend()

            axM.plot(cycles[1:],absMagnetic[1:],'-o',alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axM.legend()

            axA.plot(cycles[1:],Accept[1:],alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axA.legend(loc =1,fontsize=14)

    figE.tight_layout()
    figE.savefig('../plots/plot_C_mean_energy.pdf')
    figM.tight_layout()
    figM.savefig('../plots/plot_C_mean_abs_magnetic.pdf')
    figA.tight_layout()
    figA.savefig('../plots/plot_C_number_accepted_energies.pdf')

plotting(60000)
plt.show()
