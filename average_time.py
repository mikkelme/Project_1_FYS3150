# Stygg kode som finner gjennomsnittstidene

# for bruk kjør bash kommando for average_time.txt med ønsket N og n 
# og legg til eventuelle averages linjer og endre N og n etter forholdene.

import numpy as np

# change directory/filename if needed, according to bash filename
with open("general_solution/average_time.txt") as f:
    content = f.readlines()
content = [x.strip() for x in content]

N = 10 #number of times running bash command
#bash command example: for i in {1..10}; do ./general_solution/gen 4; done > ./general_solution/average_time.txt
n = 4 # 10^n, 

times = np.zeros(N*n) 
averages = np.zeros((N,n))

for i in range(N*n):
    times[i] = content[i].split()[5] 

for i in range(N):
    averages[i,0] = times[n*i] # time for n = 1
    averages[i,1] = times[n*i+1]
    averages[i,2] = times[n*i+2]
    averages[i,3] = times[n*i+3]
    # averages[i,4] = times[n*i+4] # if adding n = 5
    # averages[i,5] = times[n*i+5] 
    # averages[i,6] = times[n*i+6] 

for i in range(n):
    print("Average time = {:.2e}s, n = {}, N = {}".format(np.sum(averages[:,i])/N,i+1,N))