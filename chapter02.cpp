#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;
#define MaxNum 100

class RRSchedule {
public:

    int n{};//进程数
    int q{};//时间片大小
    int ArrivalTime[MaxNum]{};//进程到达时间T[i]
    int ServiceTime[MaxNum]{};//进程服务时间S[i]
/*    int PServiceTime[MaxNum]{};//剩余进程服务时间P[i]
    int FinishTime[MaxNum]{};//完成时间
    int WholeTime[MaxNum]{};//周转时间
    double WeightWholeTime[MaxNum]{};//带权周转时间*/
    double AverageWT = 0;//平均周转时间
    double AverageWWT = 0;//平均带权周转时间
//    bool Finished[MaxNum]{};//完成状态

    typedef struct {
        int number;
        int ArrivalTime;//进程到达时间
        int ServiceTime;//进程服务时间
        int PServiceTime;//剩余进程服务时间P[i]
        int FinishedTime;//完成时间
        int WholeTime;//周转时间
        double WeightWholeTime;//带权周转时间
        bool Finished;//完成状态
    } Progress;

    queue<Progress> queueRR;
    Progress progress[MaxNum]{};

    //输入进程信息
    //将输入的ArrivalTime信息与ServiceTime信息存储进数组
    void InputProcess() {
        cout << "请输入进程数量：";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cout << "请输入进程" << i << "的到达时间ArrivalTime[" << i << "]：";
            cin >> ArrivalTime[i];
            cout << "请输入进程" << i << "的服务时间ServiceTime[" << i << "]：";
            cin >> ServiceTime[i];
        }
        cout << "请输入时间片大小：";
        cin >> q;
    }

    void InitQueue() {
        for (int i = 1; i <= n; i++) {
            progress[i].number = i;
            progress[i].ArrivalTime = ArrivalTime[i];
            progress[i].ServiceTime = ServiceTime[i];
            progress[i].PServiceTime = progress[i].ServiceTime;
            progress[i].Finished = false;
            progress[i].FinishedTime = -1;
            queueRR.push(progress[i]);
        }
    }

    //调用RR算法进行调度计算
    void ArithRR() {
        int finishTime = 0;
        while (!queueRR.empty()) {
            //按进程顺序读取队列首值进行操作，并出队列，判断其是否完成，若无，则插入队列尾，并在执行过程中输出调度过程
            int x = queueRR.front().number;
            if (progress[x].PServiceTime > q) {//进程未结束
                if (finishTime != 0) {
                    cout << "时刻" << finishTime + 1 << "进程" << x << "开始运行" << endl;
                } else {
                    cout << "时刻" << finishTime << "进程" << x << "开始运行" << endl;
                }
                finishTime += q;
                progress[x].PServiceTime -= q;
                queueRR.pop();
                queueRR.push(progress[x]);
            } else {//进程结束
                if (finishTime != 0) {
                    cout << "时刻" << finishTime + 1 << "进程" << x << "开始运行" << endl;
                } else {
                    cout << "时刻" << finishTime << "进程" << x << "开始运行" << endl;
                }
                progress[x].Finished = true;
                finishTime += progress[x].PServiceTime;
                progress[x].PServiceTime = 0;
                progress[x].FinishedTime = finishTime;
                cout << "时刻" << finishTime << "进程" << x << "结束运行" << endl;
                queueRR.pop();
            }

            //计算属性
            for (int i = 1; i <= n; i++) {
                //计算周转时间
                progress[i].WholeTime = progress[i].FinishedTime - progress[i].ArrivalTime;

                //计算带权周转时间
                progress[i].WeightWholeTime = (double) progress[i].WholeTime / progress[i].ServiceTime;

                //计算平均周转时间
                AverageWT += progress[i].WholeTime;

                //计算平局带权周转时间
                AverageWWT += progress[i].WeightWholeTime;
            }
        }
    }

    //输出周转时间、带权周转时间、平均周转时间及带权平均周转时间
    void Print() {
        if (progress[1].FinishedTime >= 0)//判断是否已有数据输入
        {
            cout << left << setw(15) << "周转信息如下表：" << endl;

            cout << left << setw(15) << "";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << "进程" << i;
            }
            cout << endl;

            cout << left << setw(15) << "到达时间";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ArrivalTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "服务时间";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ServiceTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "完成时间";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << FinishTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "周转时间";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WholeTime[i];
            }
            cout << right << setw(30) << "平均周转时间:" << AverageWT << endl;

            cout << left << setw(15) << "带权周转时间";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WeightWholeTime[i];
            }
            cout << right << setw(30) << "平均带权周转时间:" << AverageWWT << endl;
        }
    }


};

int main() {
    RRSchedule rrSchedule;
    rrSchedule.InputProcess();
    rrSchedule.InitQueue();
    rrSchedule.ArithRR();
    rrSchedule.Print();
    return 0;
}