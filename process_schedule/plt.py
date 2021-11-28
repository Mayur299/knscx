import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import sys
import numpy as np

def convert(string):
    li = list(string.split(" "))
    return li


fig, (ax1,ax2) = plt.subplots(2)
file=open(sys.argv[1],"r")
info=convert(file.readline())
li=[]
for i in range(0,int(info[0])):
    li.append(convert(file.readline()))
    print(li[i])

pname=[]
pdata=[]
for i in range(int(info[0])-1,-1,-1):
    pname.append(li[i][0])
    tlist=[]
    for j in range(4,len(li[i])-1,2):
        tup=(float(li[i][j]),float(li[i][j+1]))
        tlist.append(tup)
        if(li[i][0][0]=='C'):
            ax1.broken_barh(tlist,((((int(info[0])-i)*2)-1.5),1),facecolors='tab:orange')
        else:
            ax1.broken_barh(tlist,((((int(info[0])-i)*2)-1.5),1),facecolors='tab:grey')


name=[]
wt=[]
bt=[]
high=0.0
avgtt=0.0
avgwt=0.0
for i in range(0,int(info[0])):
    name.append(li[i][0])
    wt.append(float(li[i][2]))
    avgwt=avgwt+float(li[i][2])
    avgtt=avgtt+float(li[i][2])+(float(li[i][3])-float(li[i][2]))
    bt.append(float(li[i][3])-float(li[i][2]))
    if(float(li[i][3])>high):
        high=float(li[i][3])

avgwt=avgwt/float(int(info[0]))
avgtt=avgtt/float(int(info[0]))




high=int(high)+5
wide=high/5
wide=int(wide)+1



#ax.broken_barh([(110,30), (150, 10)], (10, 2), facecolors='tab:blue')
#ax.broken_barh([(10, 50), (100, 20), (130, 10)], (20, 9),
               #facecolors=('tab:orange'))

a_list = list(range(1, 2*int(info[0]),2))
b_list=list(range(0,int(float(info[1]))+1,5))
ax1.set_xticks(b_list)
ax1.set_ylim(0,2*int(info[0]))
ax1.set_xlim(0, int(float(info[1]))+1,auto=False)
ax1.set_xlabel('Time')
ax1.set_ylabel('Processess')
ax1.set_yticks(a_list)
ax1.set_yticklabels(pname)
ax1.grid(True)

legend_elements = [Line2D([0], [0], color='grey', lw=4, label='IO Bound'),Line2D([0], [0], color='orange', lw=4, label='CPU Bound')]
ax1.legend(handles=legend_elements, loc='upper right')



N = int(info[0])
ttlist = list(range(1, high,wide))
 

ind = np.arange(N)  
width = 0.35 
 
#fig = plt.subplots(figsize =(10, 7))
p1 = ax2.bar(ind, bt, width)
p2 = ax2.bar(ind, wt, width,
             bottom = bt,color='yellow')
 


ax2.set_xlabel('Processes')
ax2.set_ylabel('Total turnaround time')
ax2.set_title('Simulation Statistics')
ax2.set_xticks(list(range(0,int(info[0]))))
ax2.set_xticklabels(name)
ax2.set_yticks(ttlist)
ax2.text(N-1, -2, "average waiting time: "+str(avgwt)+"\n average turnaroundtime: "+str(avgtt),
        horizontalalignment="right",
        verticalalignment="top")
ax2.legend((p1[0], p2[0]), ('burst time', 'waiting time'))
ax2.grid(True)

for i in range(0,int(info[0])):
    if(li[i][0][0]=="I"):
        p1[i].set_color('grey')
 
plt.show()





 


