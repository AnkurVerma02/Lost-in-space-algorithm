import numpy as np

s = "sm_Reference_Star_Catalogue_4SM.csv"
print(s)
stars= np.loadtxt(s, delimiter=',',dtype=int,
                       skiprows=1)
print(stars)
np.savetxt("kvec2",stars,delimiter='_', fmt="%i")
    
    