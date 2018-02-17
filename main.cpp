
#include <cstdio>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "para.h"

using namespace std;

void Normalize(std::vector<struct Result> &Final)
{
	struct Result tmp;

	if(DA > Final.size()-1)
		return;

	tmp = Final[DA];

	for(int i = 0; i < Final.size(); i++)
	{
//		Final[i].value[RAW_TRACE] /=  tmp.value[RAW_TRACE];
//		Final[i].value[ALL_REQ_READ] /=  tmp.value[ALL_REQ_READ];
//		Final[i].value[ALL_REQ_READ_RAN] /=  tmp.value[ALL_REQ_READ_RAN];
//		Final[i].value[ALL_RANDOM] /=  tmp.value[ALL_RANDOM];
	//   printf("%-2d %-15s %10.5f %10.5f %10.5f\n", Final[i].policy, Final[i].p_name, Final[i].value[ALL_REQ_READ], Final[i].value[ALL_REQ_READ_RAN], Final[i].value[ALL_RANDOM]);
//	    printf("%-2d %-5s %10.5f %10.5f %10.5f %10.5f %10.5f\n", Final[i].policy, Final[i].cache_name, (float)Final[i].total_latency / tmp.total_latency, Final[i].value[RAW_TRACE], Final[i].value[ALL_REQ_READ], Final[i].value[ALL_REQ_READ_RAN], Final[i].value[ALL_RANDOM]);
	}

}


int main(int argc, char** argv) 
{

	trace = atoi(argv[10]);
//	trace = 0;

	if(trace == 0)//
	{
		file_prefix = (char *)"mobi.trace.";
		cout << "Debug trace" << endl;
	}
	else if(trace == 1)//desktop  4& 5
	{
		file_prefix = (char *)"trace-desktop-ubuntu-";
		file_suffix = (char *)".sha1";
		cout << "Trace: Desktop[4| 5]" << endl;
	}
	else if(trace == 2)// hadoop 2,3,6 8-18,20,21
	{
		file_prefix = (char *)"hivetpch";
		file_suffix = (char *)"-ubuntu.trace";
		cout << "Trace: Hadoop [2,3,6 8-18,20,21]" << endl;

	}else if(trace == 3)//transaction  1 & 2
	{
		file_prefix = (char *)"tpcc-config";
		file_suffix = (char *)".sha1";
		cout << "Trace: Transaction [1 & 2]" << endl;
	}
	else
	{
		printf("Wrong trace!\n");
		return 0;
	}


    char **default_setting;
    Create_Default_Setting(&default_setting);
    Argv_Parse(10, default_setting, file_prefix, file_suffix);
    C_Policy = atoi(default_setting[9]);


//	Argv_Parse(argc, argv, file_prefix, file_suffix);
//	C_Policy = atoi(argv[9]);


    Policy = 0;
    int degraded = atoi(argv[11]);


    cout << "P_Policy is: " << Policy << " C_policy= "<< C_Policy << "  degraded is: " << degraded << "  IO queues are:  "<< QUEUE_NUM <<endl;

    if(ec_node < NODE_NUM)
    {
    	ec_node = NODE_NUM;
    }

    EC_Para(ec_node);
    
    struct Result t;

    std::vector< std::vector<long long> >cdf;
    R_trace_CDF.resize(6);
    W_trace_CDF.resize(6);
    R_Map.clear();

    R_Req_Tbl.resize(Policy+1);
    W_Req_Tbl.resize(Policy+1);

    for(int i = 0; i < C_Policy; i++)
    {
    	Init(ec_node, 0);

    	Init_F_cache(i);

    	t = Process(files, trace_start, trace_end, &T_line, ERASURE, Policy, 200, degraded, i);

        if(file_exist == 1)
        {
//        	printf("Output_Relationship\n");
//        	Output_Relationship(file_prefix);
        }
//    	cdf.push_back(CDF);
    	Final.push_back(t);
    	Reset_all(ec_node, 0);
    	Free_F_cache(i);
    }
    
    printf("\n");
    printf("%-20s: %10s %8s %8s %8s %8s\n",  "Type", "Ave_latency", "Requests", "Hits", "Ajusts", "Hit_Ratio");
    for(int i = 0; i < Final.size(); i++)
    {
    	printf("%-20s: %10lld  %8lu %8lu %8lu %8.2f\n",  Final[i].cache_name, Final[i].total_latency, Final[i].requests, Final[i].hits, Final[i].adjusts, Final[i].hits*100/(float)Final[i].requests);
    }




    return 0;
}
