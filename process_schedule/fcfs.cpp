#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class node
{
    public:
    int pid;
    string name;
    int type;
    int priority;
    float at;
    float bt;
    float wt;
    float tt;
    float ct;
    int index;
    vector<pair<float,float>>time;
};

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
    vector<string>content=parse(temp);
    int total_process=stoi(content[0]);

    int i=0;
    node* processes=new node[total_process];
    while(i!=total_process)
    {
        string info;
        getline(f,info);
        vector<string>tokens=parse(info);
        processes[i].pid=stoi(tokens[0]);
        processes[i].name=tokens[1];
        if(tokens[1][0]=='C')
        {
            processes[i].type=1;
        }
        else
        processes[i].type=0;

        processes[i].priority=stoi(tokens[2]);
        processes[i].at=stof(tokens[3]);
        processes[i].bt=stof(tokens[4]);
        processes[i].wt=0.0;
        processes[i].ct=0.0;
        processes[i].tt=0.0;
        processes[i].index=i;

        i++;


    }

    f.close();

struct Lessbyat
{
  bool operator()(const node& lhs, const node& rhs) const
  {
    if(lhs.at==lhs.at)
    {
        return lhs.index > rhs.index;
    }
    return lhs.at > rhs.at;
  }
};
    float current_time=0;
    float idle_time;
    priority_queue<node, std::vector<node>, Lessbyat> pq;

    for(i=0;i<total_process;i++)
    {
        if(processes[i].type==1)
        {
            pq.push(processes[i]);
        }
        else
        {
            processes[i].tt=processes[i].bt;
            processes[i].ct=processes[i].at+processes[i].bt;
            processes[i].wt=0.0;
            processes[i].time.push_back({0.0,processes[i].bt});
        }
    }

    while(!pq.empty())
    {
        node smallest=pq.top();
        pq.pop();
        if(current_time<smallest.at)
        {
           idle_time+=(smallest.at-current_time);
           current_time=smallest.at;


        }


        else
        {
             processes[smallest.index].wt=current_time-smallest.at;
        }


           // processes[smallest.index].wt=current_time-smallest.bt;
            processes[smallest.index].time.push_back({current_time,smallest.bt});
            current_time+=smallest.bt;
            processes[smallest.index].ct=current_time;
            processes[smallest.index].tt=processes[smallest.index].ct-processes[smallest.index].at;
            


    }

    for(i=0;i<total_process;i++)
    {
         cout<<processes[i].index<<endl;
         
        
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



    



    return 0;
        
    

}