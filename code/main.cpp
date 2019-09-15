#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define elif else if
#define vc vector 
#define u_map unordered_map 
#define loop(a,x,n) for(int x = a; x < n; ++x)
void initial_comp(u_map<char,vc<char>>&first,u_map<char,vc<char>>&follow_follow,u_map<char,vc<char>>&follow,string &str,vc<char>&nt,u_map<char,vc<char>>&follow_first)
{

	nt.pb(str[0]);
	int flag=1;

	loop(1,i,str.length()-1)
	{

		if(isupper(str[i]))
			nt.pb(str[i]);
		if(isupper(str[i]) && !isupper(str[i+1]))
		{
			follow[str[i]].pb(str[i+1]);
			if(str[i]!=str[0])
				follow_follow[str[i]].pb(str[0]);
		}
		elif(isupper(str[i]) && isupper(str[i+1]))
		{
			for(int j=0;j<first[str[i+1]].size();j++)
			{
				follow[str[i]].pb(first[str[i+1]][j]);
			}

		}
	}   
}
void removeDuplicateNonTerminals(vc<char>&nt,vc<char>&nt_unique)
{
	loop(0,i,nt.size()-1)
	{
		if(nt[i]!=nt[i+1])
		{
			nt_unique.pb(nt[i]);        
		}
	}
	nt_unique.pb(nt[nt.size()-1]);
}
void followContributionsToFollow(u_map<char,vc<char>>&follow_follow,u_map<char,vc<char>>&follow,vc<char>&nt_unique)
{
	loop(0,i,nt_unique.size())
	{

		loop(0,j,follow_follow[nt_unique[i]].size())
		{
			loop(0,k,follow[follow_follow[nt_unique[i]][j]].size())
			{
				follow[nt_unique[i]].pb(follow[follow_follow[nt_unique[i]][j]][k]);
			}
		}

	}
}
void removeDuplicate(u_map<char,vc<char>>&follow,u_map<char,vc<char>>&follow_final,vc<char>&nt_unique)
{
	loop(0,i,nt_unique.size())
	{
		if(follow[nt_unique[i]].size()==0)
			continue;
		loop(0,j,follow[nt_unique[i]].size()-1)
		{
			if(follow[nt_unique[i]][j]!=follow[nt_unique[i]][j+1])
				follow_final[nt_unique[i]].pb(follow[nt_unique[i]][j]);
		}
		follow_final[nt_unique[i]].pb(follow[nt_unique[i]][follow[nt_unique[i]].size()-1]);
	}
}
void calc_first(char val,string str,int index,u_map<string,bool>&visited,u_map<char,u_map<int,string>>&exp,u_map<char,int>&cnt,u_map<char,vc<char>>&first)
{
       // cout<<index<<endl;
	if(isupper(str[index]))
	{

		loop(0,y,cnt[str[index]])
		{
			if(!visited[exp[str[index]][y]])
			{
				visited[exp[str[index]][y]]=true;
				calc_first(str[index],exp[str[index]][y],1,visited,exp,cnt,first);
                // cout<<cnt[str[index]]<<" "<<y<<endl;
			}
		}
		int flag=0;
            //cout<<"cool"<<endl;
		if(val!=str[index])
		{
			loop(0,i,first[str[index]].size())
			{
				first[val].push_back(first[str[index]][i]);
			}
		}
            //cout<<"wow"<<endl;
	}
	else
	{
            //cout<<"Success"<<endl;
		first[val].push_back(str[index]);
	}
}
void print(vc<char>nt_unique,u_map<char,vc<char>>&follow_final)
{
	loop(0,i,nt_unique.size())
	{
		cout<<nt_unique[i]<<" -----------> ";
		loop(0,j,follow_final[nt_unique[i]].size())
		{
			cout<<follow_final[nt_unique[i]][j]<<" ";
		}
		cout<<endl;
	} 
}
int main()
{
	vc<string>productions;
	int  num_productions;
	cin>>num_productions;;
	vc<char>nt;
	u_map<char,vc<char>>follow;
	u_map<char,vc<char>>follow_follow;
	u_map<char,vc<char>>follow_first;
	u_map<char,vc<char>>follow_final;
	u_map<char,vc<char>>first;
	u_map<char,vc<char>>first_final;
    //  u_map<char,u_map<int,string>>exp;
	u_map<char,int>cnt;
	u_map<char,bool>mp;
	int nt_c=0;
	vector<string>prod;
	u_map<char,u_map<int,string>>exp;
	loop(0,i,num_productions)
	{
		string str;
		cin>>str;
		exp[str[0]][cnt[str[0]]]=str;
		cnt[str[0]]++;
		prod.push_back(str);
	}

    // u_map<char,bool>visited;
	u_map<string,bool>visited;
	loop(0,i,num_productions)
	{
		if(!visited[prod[i]])
		{
			visited[prod[i]]=true;
			calc_first(prod[i][0],prod[i],1,visited,exp,cnt,first);
            // cout<<i<<endl;
		}
	}

	loop(0,i,num_productions)
	initial_comp(first,follow_follow,follow,prod[i],nt,follow_first);
	sort(nt.begin(),nt.end());
	vc<char>nt_unique;
	removeDuplicateNonTerminals(nt,nt_unique);
      //calcfollow using follow of next LHS
	followContributionsToFollow(follow_follow,follow,nt_unique);

	loop(0,i,nt_unique.size())
	sort(follow[nt[i]].begin(),follow[nt[i]].end());

	removeDuplicate(follow,follow_final,nt_unique);
	removeDuplicate(first,first_final,nt_unique);
	cout<<"Follow:"<<endl;
	print(nt_unique,follow_final);
	cout<<"First"<<endl;
	print(nt_unique,first_final);
}
// 