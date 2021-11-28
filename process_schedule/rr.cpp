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
    float rt;
    float lastcpu;
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
    vector<string> parsetemp=parse(temp);
    int total_process=stoi(parsetemp[0]);
    int total_process1=stoi(parsetemp[0]);
    int total_process2=stoi(parsetemp[0]);
    float quantum=stof(parsetemp[1]);
    float quantum1=stof(parsetemp[1]);
    float quantum2=stof(parsetemp[1]);

    int i=0;
    node* processes=new node[total_process];
    node* processes1=new node[total_process1];
    node* processes2=new node[total_process2];

    while(i!=total_process)
    {
        string info;
        getline(f,info);
        vector<string>tokens=parse(info);
        processes[i].pid=stoi(tokens[0]);
        processes1[i].pid=stoi(tokens[0]);
        processes2[i].pid=stoi(tokens[0]);
        processes[i].name=tokens[1];
        processes1[i].name=tokens[1];
        processes2[i].name=tokens[1];
        

        if(tokens[1][0]=='C')
        {
            processes[i].type=1;
            processes1[i].type=1;
            processes2[i].type=1;
        }

        else
        {
        
        processes[i].type=0;
        processes1[i].type=0;
        processes2[i].type=0;
        }

        processes[i].priority=stoi(tokens[2]);
        processes[i].at=stof(tokens[3]);
        processes[i].bt=stof(tokens[4]);
        processes[i].wt=0.0;
        processes[i].ct=0.0;
        processes[i].tt=0.0;
        processes[i].rt=stof(tokens[4]);
        processes[i].index=i;
        processes[i].lastcpu=stof(tokens[3]);


         
        processes1[i].priority=stoi(tokens[2]);
        processes1[i].at=stof(tokens[3]);
        processes1[i].bt=stof(tokens[4]);
        processes1[i].wt=0.0;
        processes1[i].ct=0.0;
        processes1[i].tt=0.0;
        processes1[i].rt=stof(tokens[4]);
        processes1[i].index=i;
        processes1[i].lastcpu=stof(tokens[3]);




         
        processes2[i].priority=stoi(tokens[2]);
        processes2[i].at=stof(tokens[3]);
        processes2[i].bt=stof(tokens[4]);
        processes2[i].wt=0.0;
        processes2[i].ct=0.0;
        processes2[i].tt=0.0;
        processes2[i].rt=stof(tokens[4]);
        processes2[i].index=i;
        processes2[i].lastcpu=stof(tokens[3]);

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
    queue<node>waiting;



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

    while(1)
    {
      if(pq.size()==0 && waiting.size()==0)
      break;

      if(pq.size()!=0&& waiting.size()==0)
      {
          node smallest=pq.top();
          pq.pop();
          if(current_time<smallest.at)
          {
           idle_time+=(smallest.at-current_time);
           current_time=smallest.at;


          }
          waiting.push(smallest);
      }
      else
      {
        /*
        while(1)
        {
            if(pq.empty())
            break;
            node smallest=pq.top();
            if(smallest.at>current_time)
            break;
            else
            {
                pq.pop();
                waiting.push(smallest);
            }
        }
        */

        node latest=waiting.front();
        if(latest.rt<=quantum)
        {
            waiting.pop();
            processes[latest.index].time.push_back({current_time,latest.rt});
            //processes[latest.index].wt=+current_time-(latest.lastcpu);
            current_time+=latest.rt;
            processes[latest.index].ct=current_time;
            processes[latest.index].tt= processes[latest.index].ct-processes[latest.index].at;
            processes[latest.index].wt= processes[latest.index].tt-processes[latest.index].bt;


           // processes[latest.index].tt=processes[latest.index].ct-processes[latest.index].at;
            while(1)
        {
            if(pq.empty())
            break;
            node smallest=pq.top();
            if(smallest.at>current_time)
            break;
            else
            {
                pq.pop();
                waiting.push(smallest);
            }
        }
        }
        else
        {
          waiting.pop();
          processes[latest.index].time.push_back({current_time,quantum});
         // processes[latest.index].wt+=current_time-latest.lastcpu;
          current_time+=quantum;
          latest.rt-=quantum;
          latest.lastcpu=current_time;
          while(1)
        {
            if(pq.empty())
            break;
            node smallest=pq.top();
            if(smallest.at>current_time)
            break;
            else
            {
                pq.pop();
                waiting.push(smallest);
            }
        }
          waiting.push(latest);

        }
        



      }

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













   quantum1=quantum1/2;


  float current_time1=0;
    float idle_time1;
    priority_queue<node, std::vector<node>, Lessbyat> pq1;
    queue<node>waiting1;



    for(i=0;i<total_process1;i++)
    {
        if(processes1[i].type==1)
        {
            pq1.push(processes1[i]);
        }
        else
        {
            processes1[i].tt=processes1[i].bt;
            processes1[i].ct=processes1[i].at+processes1[i].bt;
            processes1[i].wt=0.0;
            processes1[i].time.push_back({0.0,processes1[i].bt});
        }
    }

    while(1)
    {
      if(pq1.size()==0 && waiting1.size()==0)
      break;

      if(pq1.size()!=0&& waiting1.size()==0)
      {
          node smallest1=pq1.top();
          pq1.pop();
          if(current_time1<smallest1.at)
          {
           idle_time1+=(smallest1.at-current_time1);
           current_time1=smallest1.at;


          }
          waiting1.push(smallest1);
      }
      else
      {
        /*
        while(1)
        {
            if(pq.empty())
            break;
            node smallest=pq.top();
            if(smallest.at>current_time)
            break;
            else
            {
                pq.pop();
                waiting.push(smallest);
            }
        }
        */

        node latest1=waiting1.front();
        if(latest1.rt<=quantum1)
        {
            waiting1.pop();
            processes1[latest1.index].time.push_back({current_time1,latest1.rt});
            //processes[latest.index].wt=+current_time-(latest.lastcpu);
            current_time1+=latest1.rt;
            processes1[latest1.index].ct=current_time1;
            processes1[latest1.index].tt= processes1[latest1.index].ct-processes1[latest1.index].at;
            processes1[latest1.index].wt= processes1[latest1.index].tt-processes1[latest1.index].bt;


           // processes[latest.index].tt=processes[latest.index].ct-processes[latest.index].at;
            while(1)
        {
            if(pq1.empty())
            break;
            node smallest1=pq1.top();
            if(smallest1.at>current_time1)
            break;
            else
            {
                pq1.pop();
                waiting1.push(smallest1);
            }
        }
        }
        else
        {
          waiting1.pop();
          processes1[latest1.index].time.push_back({current_time1,quantum1});
         // processes[latest.index].wt+=current_time-latest.lastcpu;
          current_time1+=quantum1;
          latest1.rt-=quantum1;
          latest1.lastcpu=current_time1;
          while(1)
        {
            if(pq1.empty())
            break;
            node smallest1=pq1.top();
            if(smallest1.at>current_time1)
            break;
            else
            {
                pq1.pop();
                waiting1.push(smallest1);
            }
        }
          waiting1.push(latest1);

        }
        



      }

    }

        


       

    for(i=0;i<total_process1;i++)
    {
         cout<<processes1[i].index<<endl;
         
        
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













  quantum2=quantum2*2;


  float current_time2=0;
    float idle_time2;
    priority_queue<node, std::vector<node>, Lessbyat> pq2;
    queue<node>waiting2;



    for(i=0;i<total_process2;i++)
    {
        if(processes2[i].type==1)
        {
            pq2.push(processes2[i]);
        }
        else
        {
            processes2[i].tt=processes2[i].bt;
            processes2[i].ct=processes2[i].at+processes2[i].bt;
            processes2[i].wt=0.0;
            processes2[i].time.push_back({0.0,processes2[i].bt});
        }
    }

    while(1)
    {
      if(pq2.size()==0 && waiting2.size()==0)
      break;

      if(pq2.size()!=0&& waiting2.size()==0)
      {
          node smallest2=pq2.top();
          pq2.pop();
          if(current_time2<smallest2.at)
          {
           idle_time2+=(smallest2.at-current_time2);
           current_time2=smallest2.at;


          }
          waiting2.push(smallest2);
      }
      else
      {
        
        node latest2=waiting2.front();
        if(latest2.rt<=quantum2)
        {
            waiting2.pop();
            processes2[latest2.index].time.push_back({current_time2,latest2.rt});
            //processes[latest.index].wt=+current_time-(latest.lastcpu);
            current_time2+=latest2.rt;
            processes2[latest2.index].ct=current_time2;
            processes2[latest2.index].tt= processes2[latest2.index].ct-processes2[latest2.index].at;
            processes2[latest2.index].wt= processes2[latest2.index].tt-processes2[latest2.index].bt;


           // processes[latest.index].tt=processes[latest.index].ct-processes[latest.index].at;
            while(1)
        {
            if(pq2.empty())
            break;
            node smallest2=pq2.top();
            if(smallest2.at>current_time2)
            break;
            else
            {
                pq2.pop();
                waiting2.push(smallest2);
            }
        }
        }
        else
        {
          waiting2.pop();
          processes2[latest2.index].time.push_back({current_time2,quantum2});
         // processes[latest.index].wt+=current_time-latest.lastcpu;
          current_time2+=quantum2;
          latest2.rt-=quantum2;
          latest2.lastcpu=current_time2;
          while(1)
        {
            if(pq2.empty())
            break;
            node smallest2=pq2.top();
            if(smallest2.at>current_time2)
            break;
            else
            {
                pq2.pop();
                waiting2.push(smallest2);
            }
        }
          waiting2.push(latest2);

        }
        



      }

    }

        


       

    for(i=0;i<total_process2;i++)
    {
         cout<<processes2[i].index<<endl;
         
        
        cout<<processes2[i].ct<<endl;
         cout<<processes2[i].wt<<endl;
         
         cout<<processes2[i].tt<<endl;
       
        cout<<endl<<endl;
    }


  
  
  //ofstream log_file(argv[2], ios_base::out | ios_base::app );
  string s2="";
  s2+=to_string(total_process2);
  s2+=" ";
  s2+=to_string(current_time2);
  log_file<<s2.c_str()<<endl;

  

  for(i=0;i<total_process2;i++)
  {
    string stemp2="";
    stemp2+=processes2[i].name;
    stemp2+=" ";
     stemp2+=to_string(processes2[i].ct);
       stemp2+=" ";
        stemp2+=to_string(processes2[i].wt);
       stemp2+=" ";
       stemp2+=to_string(processes2[i].tt);
        stemp2+=" ";

    

    for(auto it=processes2[i].time.begin();it!=processes2[i].time.end();it++)
    {
      stemp2+=to_string(it->first);
      stemp2+=" ";
      stemp2+=to_string(it->second);
      stemp2+=" ";
    }

    log_file<<stemp2.c_str()<<endl;


  }






   






    



    return 0;
        
    

}