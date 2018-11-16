import numpy as np 
from math import sinh,exp,cosh
import matplotlib.pyplot as plt 

# Plotting style
plt.style.use('bmh')
font = {'size'   : 12}
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

    axE.set_title(r"Mean energy per MC cycle")
    axE.set_xscale("log")
    axE.set_xlabel(r"$MC$")
    axE.set_ylabel(r'$\langle E \rangle(MC)$')
    
    axM.set_title("Mean magnetisation per MC cycle")
    axM.set_xscale("log")
    axM.set_xlabel(r"$MC$")
    axM.set_ylabel(r'$\langle |M|  \rangle (MC)$')

    axA.set_xscale("log")
    for T in temps:
        for init in initial:
            print("Loading ", path + init + "_T_" + T + Ename + str(MCcycles) + ".bin")
            print("Loading ", path + init + "_T_" + T + Mname + str(MCcycles) + ".bin")
            energies = np.fromfile(path + init + "_T_" + T + Ename + str(MCcycles) + ".bin")
            absMagnetic = np.fromfile(path + init + "_T_" + T + Mname + str(MCcycles) + ".bin")
            Accept = np.fromfile(path + init + "_T_" + T + Aname + str(MCcycles) + ".bin")
            cycles = np.arange(0,len(energies),1)

            axE.plot(cycles[1:],energies[1:],'-o',alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axE.legend()
            plt.tight_layout()

            axM.plot(cycles[1:],absMagnetic[1:],'-o',alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axM.legend()
            plt.tight_layout()

            axA.plot(cycles[1:],Accept[1:],alpha= 0.5,label="T={:.2f}, {:s}".format(float(T),init))
            axA.legend()
            plt.tight_layout()

plotting(60000)
plt.show()