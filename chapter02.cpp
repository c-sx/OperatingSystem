#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;
#define MaxNum 100

class RR {
    int n;//进程数
    int ArrivalTime[MaxNum];//进程到达时间T[i]
    int ServiceTime[MaxNum];//进程服务时间S[i]
    int PServiceTime[MaxNum];
    int FinishTime[MaxNum];//完成时间
    int WholeTime[MaxNum];//周转时间
    double WeightWholeTime[MaxNum];//带权周转时间
    double AverageWT, AverageWWT;
    bool Finished[MaxNum];

    typedef struct {
        char name;
        int ArrivalTime;
        int ServiceTime;
        int FinishedTime;
        int WholeTime;
        double WeightWholeTime;
    } thanksBai;

    int main() {}
};