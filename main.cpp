#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
using namespace std;
#define ll long long 
ll filesize;

class priority_queue
{
private:
	vector<pair<ll,int>>heap;

public:
        void heapify(ll i)
		{
            ll l=2*i+1, r=2*i+2;
            ll smallest=i;
            if(l<heap.size() && heap[l].first<heap[i].first)
			{
				smallest=l; 
            }
			if(r<heap.size() && heap[r].first<heap[smallest].first)
			{
				smallest=r;
        	}
			if(smallest!=i)
			{
                swap(heap[i],heap[smallest]);
                heapify(smallest);
            }
        }

        void insert(pair<ll,int> item)
		{
            heap.push_back(item);
            long long index = heap.size()-1;
            long long pindex = index%2==0 ? (index/2)-1:(index/2);       
            while(pindex >= 0 && heap[pindex].first > heap[index].first)
			{
                swap(heap[pindex], heap[index]);
                index = pindex;
                pindex = index%2==0 ? (index/2)-1:(index/2); 
        	}
    	}

        pair<ll,int> extract_min()
		{
            ll temp1=heap[0].first;
            int temp2=heap[0].second;
            swap(heap[0],heap[heap.size()-1]);
            heap.pop_back();
            heapify(0);
            pair<ll,int>temp;
            temp.first=temp1;
            temp.second=temp2;
            return temp;
        }
};

int run(string input_file,string output_file)
{
	ifstream file(input_file);
    string data="";
    filesize=0;
    while(getline(file, data,','))
	{
		filesize++;
	}
	ifstream myfile(input_file);
	int count=0,temp_files=0;
	data="";
	vector<ll>numbers,sorted;
	while(getline(myfile,data,','))
	{
		ll current_num=stoll(data,nullptr,10);
		count++;
		numbers.push_back(current_num);
		if(count==100000)
		{
			string tempfile="temp"+to_string(temp_files+1);
			sorted=numbers;
			sort(sorted.begin(),sorted.end());
			FILE* f=fopen(tempfile.c_str(),"w");
			for(ll i=0;i<sorted.size();i++)
			{
				fprintf(f,"%lld ",sorted[i]);
			}
			fclose(f);
			count=0;
			temp_files++;
			numbers.clear();
		}
	}
	if(count>0)
	{
		string tempfile="temp"+to_string(temp_files+1);
		sorted=numbers;
		sort(sorted.begin(),sorted.end());
		FILE* f=fopen(tempfile.c_str(),"w");
		for(ll i=0;i<sorted.size();i++)
		{
			fprintf(f,"%lld ",sorted[i]);
		}
		fclose(f);
		count=0;
		temp_files++;
		numbers.clear();
	}
	return temp_files;
}

void kway_merge(int k,string output_file)
{
    priority_queue pq;
	FILE* f=fopen(output_file.c_str(),"w");

    if(f)
	{	
        FILE* tempFiles[k];
        for(int i=0;i<k;i++)
		{
            string tempfile="temp"+to_string(i+1);
            tempFiles[i]=fopen(tempfile.c_str(),"r");
        }
		pair<ll,int>temp_pair;
        for(int i=0;i<k;i++)
		{
            if(fscanf(tempFiles[i],"%lld ", &temp_pair.first)!=EOF)
            {
			    temp_pair.second=i;
			}
            else
			{
				break;
			}
			pq.insert(temp_pair);
        }

        int end=1,files_completed=0;
        while(files_completed!=k)
		{
            pair<ll,int> item = pq.extract_min();
            ll num=item.first;
            int ID=item.second;
            if(end!=filesize)
            {
				fprintf(f,"%lld,",num);
            }
			else
			{
                fprintf(f,"%lld",num);
            }
            end++;
            pair<ll,int>new_num;
            if(fscanf(tempFiles[ID],"%lld ",&new_num.first)==1)
			{
                new_num.second=ID;
                pq.insert(new_num);
            }
            else
			{
				files_completed++;
			}
        }

        for(int i=0;i<k;i++)
		{ 
        	fclose(tempFiles[i]);
        	remove(("temp"+to_string(i+1)).c_str());
		}
        fclose(f);
    }
    else
	{
        cout<<"Unable to open output file.\n";
    }
}

int main(int argc,char *argv[])
{
	if(argc==3)
	{
		string input_file=argv[1];
        string output_file=argv[2];
		kway_merge(run(input_file,output_file),output_file);	
    }
	else
	{
        cout<<"Invalid inputs.\n";
    }
	return 0;
}
