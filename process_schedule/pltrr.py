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
 
#plt.show()

















fig1, (ax11,ax21) = plt.subplots(2)

info1=convert(file.readline())
li1=[]
for i in range(0,int(info1[0])):
    li1.append(convert(file.readline()))
    print(li1[i])

pname1=[]
pdata1=[]
for i in range(int(info1[0])-1,-1,-1):
    pname1.append(li1[i][0])
    tlist1=[]
    for j in range(4,len(li[i])-1,2):
        tup1=(float(li1[i][j]),float(li1[i][j+1]))
        tlist1.append(tup1)
        if(li1[i][0][0]=='C'):
            ax11.broken_barh(tlist1,((((int(info1[0])-i)*2)-1.5),1),facecolors='tab:orange')
        else:
            ax11.broken_barh(tlist1,((((int(info1[0])-i)*2)-1.5),1),facecolors='tab:grey')


name1=[]
wt1=[]
bt1=[]
high1=0.0
avgtt1=0.0
avgwt1=0.0
for i in range(0,int(info1[0])):
    name1.append(li1[i][0])
    wt1.append(float(li1[i][2]))
    avgwt1=avgwt1+float(li1[i][2])
    avgtt1=avgtt1+float(li1[i][2])+(float(li1[i][3])-float(li1[i][2]))
    bt1.append(float(li1[i][3])-float(li1[i][2]))
    if(float(li1[i][3])>high1):
        high1=float(li1[i][3])

avgwt1=avgwt1/float(int(info1[0]))
avgtt1=avgtt1/float(int(info1[0]))

high1=int(high1)+5
wide1=high1/5
wide1=int(wide1)+1



#ax.broken_barh([(110,30), (150, 10)], (10, 2), facecolors='tab:blue')
#ax.broken_barh([(10, 50), (100, 20), (130, 10)], (20, 9),
               #facecolors=('tab:orange'))

a_list1 = list(range(1, 2*int(info1[0]),2))
b_list1=list(range(0,int(float(info1[1]))+1,5))
ax11.set_xticks(b_list1)
ax11.set_ylim(0,2*int(info1[0]))
ax11.set_xlim(0, int(float(info1[1]))+1,auto=False)
ax11.set_xlabel('Time')
ax11.set_title('When time slice is Halved')
ax11.set_ylabel('Processess')
ax11.set_yticks(a_list1)
ax11.set_yticklabels(pname1)
ax11.grid(True)

legend_elements1 = [Line2D([0], [0], color='grey', lw=4, label='IO Bound'),Line2D([0], [0], color='orange', lw=4, label='CPU Bound')]
ax11.legend(handles=legend_elements1, loc='upper right')



N1= int(info1[0])
ttlist1 = list(range(1, high1,wide1))
 

ind1 = np.arange(N1)  
width1 = 0.35 
 
#fig = plt.subplots(figsize =(10, 7))
p11 = ax21.bar(ind1, bt1, width1)
p21 = ax21.bar(ind1, wt1, width1,
             bottom = bt1,color='yellow')
 


ax21.set_xlabel('Processes')
ax21.set_ylabel('Total turnaround time')
ax21.set_title('Simulation Statistics')
ax21.set_xticks(list(range(0,int(info1[0]))))
ax21.set_xticklabels(name1)
ax21.text(N1-1, -2, "average waiting time: "+str(avgwt1)+"\n average turnaroundtime: "+str(avgtt1),
        horizontalalignment="right",
        verticalalignment="top")
ax21.set_yticks(ttlist)
ax21.legend((p11[0], p21[0]), ('burst time', 'waiting time'))
ax21.grid(True)

for i in range(0,int(info1[0])):
    if(li1[i][0][0]=="I"):
        p11[i].set_color('grey')
 
#plt.show()























fig2, (ax12,ax22) = plt.subplots(2)
info2=convert(file.readline())
print(info2)
li2=[]
for i in range(0,int(info2[0])):
    li2.append(convert(file.readline()))
    print(li2[i])

pname2=[]
pdata2=[]
for i in range(int(info2[0])-1,-1,-1):
    pname2.append(li2[i][0])
    tlist2=[]
    for j in range(4,len(li2[i])-1,2):
        tup2=(float(li2[i][j]),float(li2[i][j+1]))
        tlist2.append(tup2)
        if(li2[i][0][0]=='C'):
            ax12.broken_barh(tlist2,((((int(info2[0])-i)*2)-1.5),1),facecolors='tab:orange')
        else:
            ax12.broken_barh(tlist2,((((int(info2[0])-i)*2)-1.5),1),facecolors='tab:grey')


name2=[]
wt2=[]
bt2=[]
high2=0.0
avgtt2=0.0
avgwt2=0.0
for i in range(0,int(info2[0])):
    name2.append(li2[i][0])
    wt2.append(float(li2[i][2]))
    avgwt2=avgwt2+float(li2[i][2])
    avgtt2=avgtt2+float(li2[i][2])+(float(li2[i][3])-float(li2[i][2]))
    bt2.append(float(li2[i][3])-float(li2[i][2]))
    if(float(li2[i][3])>high2):
        high2=float(li2[i][3])

avgwt2=avgwt2/float(int(info2[0]))
avgtt2=avgtt2/float(int(info2[0]))

high2=int(high2)+5
wide2=high2/5
wide2=int(wide2)+1



#ax.broken_barh([(110,30), (150, 10)], (10, 2), facecolors='tab:blue')
#ax.broken_barh([(10, 50), (100, 20), (130, 10)], (20, 9),
               #facecolors=('tab:orange'))

a_list2 = list(range(1, 2*int(info2[0]),2))
b_list2=list(range(0,int(float(info2[1]))+1,5))
ax12.set_xticks(b_list2)
ax12.set_ylim(0,2*int(info2[0]))
ax12.set_xlim(0, int(float(info2[1]))+1,auto=False)
ax12.set_title('When time slice is doubled')
ax12.set_xlabel('Time')
ax12.set_ylabel('Processess')
ax12.set_yticks(a_list2)
ax12.set_yticklabels(pname2)
ax12.grid(True)

legend_elements2 = [Line2D([0], [0], color='grey', lw=4, label='IO Bound'),Line2D([0], [0], color='orange', lw=4, label='CPU Bound')]
ax12.legend(handles=legend_elements2, loc='upper right')



N2 = int(info2[0])
ttlist2 = list(range(1, high2,wide2))
 

ind2 = np.arange(N2)  
width2 = 0.35 
 
#fig = plt.subplots(figsize =(10, 7))
p12 = ax22.bar(ind2, bt2, width2)
p22 = ax22.bar(ind2, wt2, width2,
             bottom = bt,color='yellow')
 


ax22.set_xlabel('Processes')
ax22.set_ylabel('Total turnaround time')
ax22.set_title('Simulation Statistics')
ax22.set_xticks(list(range(0,int(info2[0]))))
ax22.set_xticklabels(name2)
ax22.text(N2-1, -2, "average waiting time: "+str(avgwt2)+"\n average turnaroundtime: "+str(avgtt2),
        horizontalalignment="right",
        verticalalignment="top")
ax22.set_yticks(ttlist2)
ax22.legend((p12[0], p22[0]), ('burst time', 'waiting time'))
ax22.grid(True)

for i in range(0,int(info2[0])):
    if(li2[i][0][0]=="I"):
        p12[i].set_color('grey')
 
plt.show()

