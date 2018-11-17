import numpy as np 
from math import sinh,exp,cosh
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt 
import sys



def sinus(x,weight,constant):
    return weight*np.sin(x) + constant
a = 1e-5
b = exp(200)
x = np.linspace(0,2*np.pi,10)
y = sinus(x,a,b)

par,parcov = curve_fit(sinus,x,y)
print(par[0]/a,par[1]/a)


plt.plot(x,y,x,sinus(x,*par))


plt.show()