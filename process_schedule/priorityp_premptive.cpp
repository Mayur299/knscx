#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<algorithm>

using namespace std;

class node
{
    public:
    int pid;
    string name;
    int type;
    int priority;
    int at;
    int bt;
    int wt;
    int tt;
    int ct;
    int rt;
    int index;
    vector<pair<int,int>>time;
};

bool comp(const node& lhs,const node& rhs){

  return lhs.at < rhs.at;
}

vector<string> parse(string s)
{
  vector<string> res;
  int len = s.length();
  int i = 0;
  string temp = "";
  while (i != len)
  {
    if (s[i] != ' ')
    {
      temp.push_back(s[i]);
      i++;
    }

    else
    {
      res.push_back(temp);
      temp = "";
      i++;
    }
  }
  res.push_back(temp);

  return res;
}


int main(int argc, char *argv[])
{
    ifstream f(argv[1]);
    string temp;
    getline(f,temp);
    vector<string> parsetemp=parse(temp);
    int total_process=stoi(parsetemp[0]);
    int total_process1=stoi(parsetemp[0]);

    int i=0;
    node* processes=new node[total_process];
    node* processes1=new node[total_process1];
    int cpu_count=0;
    int cpu_count1=0;
    while(i!=total_process)
    {
        string info;
        getline(f,info);
        vector<string>tokens=parse(info);
        processes[i].pid=stoi(tokens[0]);
        processes1[i].pid=stoi(tokens[0]);
        processes[i].name=tokens[1];
        processes1[i].name=tokens[1];
        if(tokens[1][0]=='C')
        {
            processes[i].type=1;
            processes1[i].type=1;
            cpu_count++;
            cpu_count1++;
        }
        else
        {
           
        processes[i].type=0;
        processes1[i].type=0;
        }

        processes[i].priority=stoi(tokens[2]);
        processes[i].at=stoi(tokens[3]);
        processes[i].bt=stoi(tokens[4]);
        processes[i].wt=0;
        processes[i].ct=0;
        processes[i].tt=0;
        processes[i].index=i;
        processes[i].rt=stoi(tokens[4]);



        processes1[i].priority=stoi(tokens[2]);
        processes1[i].at=stof(tokens[3]);
        processes1[i].bt=stof(tokens[4]);
        processes1[i].wt=0.0;
        processes1[i].ct=0.0;
        processes1[i].tt=0.0;
        processes1[i].rt=stof(tokens[4]);
        processes1[i].index=i;

        i++;


    }

    f.close();


    int current_time=0;
    int idle_time;
   
     node* cpu=new node[cpu_count];
     int k=0;
    for(i=0;i<total_process;i++)
    {
       
         if(processes[i].type==0)
        {
            processes[i].tt=processes[i].bt;
            processes[i].ct=processes[i].at+processes[i].bt;
            processes[i].wt=0;
            processes[i].time.push_back({0,processes[i].bt});
        }

        else
        {
            cpu[k]=processes[i];
            k++;

        }
    }
    

    sort(cpu,cpu+cpu_count,comp);
    
    if(cpu[0].at!=0)
    {
      current_time=cpu[0].at;
    }


    while(1){

      int hp = -1;
    	int hpindex= -1;
    	

    	bool done = true;

    	for(int i=0;i<cpu_count;i++){
    		if(cpu[i].rt > 0){
    			done = false;
                if(cpu[i].at <= current_time){
                    if(cpu[i].priority > hp){
                        hp = cpu[i].priority;
                        hpindex = i;
                    }
                }
    			
    		}
    	}

    	if(done){
    		break;
    	}

    	cpu[hpindex].rt--;
      processes[cpu[hpindex].index].time.push_back({current_time,1});
        current_time++;

		if(cpu[hpindex].rt == 0){
			cpu[hpindex].ct = current_time;
      processes[cpu[hpindex].index].ct=current_time;
      processes[cpu[hpindex].index].tt=cpu[hpindex].ct-cpu[hpindex].at;
      processes[cpu[hpindex].index].wt=processes[cpu[hpindex].index].tt-cpu[hpindex].bt;


		}
    }


   /*

    for(i=0;i<cpu_count;i++)
    {
      int ind=cpu[i].index;
      processes[ind].ct=cpu[i].ct;
      processes[ind].tt=cpu[i].ct-cpu[i].at;
      processes[ind].wt=cpu[i].tt-cpu[i].bt;
     
    }

   */
    for(i=0;i<total_process;i++)
    {
         
         
        
        cout<<processes[i].ct<<endl;
         cout<<processes[i].wt<<endl;
         
         cout<<processes[i].tt<<endl;
       
        cout<<endl<<endl;
    }

   

    









    


  

  ofstream log_file(argv[2], ios_base::out | ios_base::app );
  string s="";
  s+=to_string(total_process);
  s+=" ";
  s+=to_string(current_time);
  log_file<<s.c_str()<<endl;

  

  for(i=0;i<total_process;i++)
  {
    string stemp="";
    stemp+=processes[i].name;
    stemp+=" ";
     stemp+=to_string(processes[i].ct);
       stemp+=" ";
        stemp+=to_string(processes[i].wt);
       stemp+=" ";
       stemp+=to_string(processes[i].tt);
        stemp+=" ";

    

    for(auto it=processes[i].time.begin();it!=processes[i].time.end();it++)
    {
      stemp+=to_string(it->first);
      stemp+=" ";
      stemp+=to_string(it->second);
      stemp+=" ";
    }

    log_file<<stemp.c_str()<<endl;


  }
















  int current_time1=0;
    int idle_time1;
   
     node* cpu1=new node[cpu_count1];
     int k1=0;
    for(i=0;i<total_process1;i++)
    {
       
         if(processes1[i].type==0)
        {
            processes1[i].tt=processes1[i].bt;
            processes1[i].ct=processes1[i].at+processes1[i].bt;
            processes1[i].wt=0;
            processes1[i].time.push_back({0,processes1[i].bt});
        }

        else
        {
            cpu1[k1]=processes1[i];
            k1++;

        }
    }
    

    sort(cpu1,cpu1+cpu_count1,comp);
    
    if(cpu1[0].at!=0)
    {
      current_time1=cpu1[0].at;
    }


    while(1){

      int hp1 = INT_MAX;
    	int hpindex1= -1;
    	

    	bool done1 = true;

    	for(int i=0;i<cpu_count1;i++){
    		if(cpu1[i].rt > 0){
    			done1 = false;
                if(cpu1[i].at <= current_time1){
                    if(cpu1[i].priority < hp1){
                        hp1 = cpu1[i].priority;
                        hpindex1= i;
                    }
                }
    			
    		}
    	}

    	if(done1){
    		break;
    	}

    	cpu1[hpindex1].rt--;
      processes1[cpu1[hpindex1].index].time.push_back({current_time1,1});
        current_time1++;

		if(cpu1[hpindex1].rt == 0){
			cpu1[hpindex1].ct = current_time1;
      processes1[cpu1[hpindex1].index].ct=current_time1;
      processes1[cpu1[hpindex1].index].tt=cpu1[hpindex1].ct-cpu1[hpindex1].at;
      processes1[cpu1[hpindex1].index].wt=processes1[cpu1[hpindex1].index].tt-cpu1[hpindex1].bt;


		}
    }


   /*

    for(i=0;i<cpu_count;i++)
    {
      int ind=cpu[i].index;
      processes[ind].ct=cpu[i].ct;
      processes[ind].tt=cpu[i].ct-cpu[i].at;
      processes[ind].wt=cpu[i].tt-cpu[i].bt;
     
    }

   */
    for(i=0;i<total_process1;i++)
    {
         
         
        
        cout<<processes1[i].ct<<endl;
         cout<<processes1[i].wt<<endl;
         
         cout<<processes1[i].tt<<endl;
       
        cout<<endl<<endl;
    }

   

    









    


  

  //ofstream log_file(argv[2], ios_base::out | ios_base::app );
  string s1="";
  s1+=to_string(total_process1);
  s1+=" ";
  s1+=to_string(current_time1);
  log_file<<s1.c_str()<<endl;

  

  for(i=0;i<total_process1;i++)
  {
    string stemp1="";
    stemp1+=processes1[i].name;
    stemp1+=" ";
     stemp1+=to_string(processes1[i].ct);
       stemp1+=" ";
        stemp1+=to_string(processes1[i].wt);
       stemp1+=" ";
       stemp1+=to_string(processes1[i].tt);
        stemp1+=" ";

    

    for(auto it=processes1[i].time.begin();it!=processes1[i].time.end();it++)
    {
      stemp1+=to_string(it->first);
      stemp1+=" ";
      stemp1+=to_string(it->second);
      stemp1+=" ";
    }

    log_file<<stemp1.c_str()<<endl;


  }


  
    



    return 0;
        
    

}

