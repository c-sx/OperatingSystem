#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;
#define MaxNum 100

class RRSchedule {
public:

    int n;//进程数
    int q;//时间片大小
    int ArrivalTime[MaxNum];//进程到达时间T[i]
    int ServiceTime[MaxNum];//进程服务时间S[i]
    int PServiceTime[MaxNum];//剩余进程服务时间P[i]
    int FinishTime[MaxNum];//完成时间
    int WholeTime[MaxNum];//周转时间
    double WeightWholeTime[MaxNum];//带权周转时间
    double AverageWT;//平均周转时间
    double AverageWWT;//平均带权周转时间
    bool Finished[MaxNum];

    typedef struct {
        int number;
        int ArrivalTime;//进程到达时间
        int ServiceTime;//进程服务时间
        int PServiceTime;//剩余进程服务时间P[i]
        int FinishedTime;//完成时间
        int WholeTime;//周转时间
        double WeightWholeTime;//带权周转时间
    } Progress;

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

    void InitQueqe(){
        for (int i = 1; i <= n; i++) {

        }
    }

    //调用RR算法进行调度计算
    void ArithRR() {

    }

    //输出调度过程
    void PrintSchedule() {
        int temp = 0;
        int CopyFinishTime[MaxNum];//备份服务时间

        //初始化CopyServiceTime
        for (int i = 1; i <= n; i++) {
            CopyFinishTime[i] = FinishTime[i];
        }

        if (FinishTime[1] >= 0)//判断是否已有数据输入
            //根据完成时间排序输出
            for (int i = 1; i <= n; i++) {

                if (i != 1) {
                    for (int j = 1; j <= n; j++) {
                        if (temp != 0) {
                            if (CopyFinishTime[j] > 0) {
                                temp = (CopyFinishTime[temp] < CopyFinishTime[j] ? temp : j);
                            }
                        } else {
                            if (CopyFinishTime[j] > 0) {
                                temp = j;
                            }
                        }
                    }
                    if (i != 2) { cout << "进程" << temp << "开始运行" << endl; }
                    cout << "时刻" << FinishTime[temp] + 1;
                    if (i == n) {
                        for (int j = 1; j < n; j++) {
                            if (CopyFinishTime[j] > 0) {
                                temp = j;
                            }
                        }
                        cout << "进程" << temp << "开始运行" << endl << endl;
                    }
                    CopyFinishTime[temp] = -1;
                    temp = 0;
                } else {
                    cout << "时刻0进程" << i << "开始运行" << endl;
                }
            }
    }

    //输出周转时间、带权周转时间、平均周转时间及带权平均周转时间
    void Print() {
        if (FinishTime[1] >= 0)//判断是否已有数据输入
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

int main() {}