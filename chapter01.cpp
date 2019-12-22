#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNum 100

class TimeCal {
public:

    int n;//进程数
    int ArrivalTime[MaxNum];//进程到达时间T[i]
    int ServiceTime[MaxNum];//进程服务时间S[i]
    int FinishTime[MaxNum];//完成时间
    int WholeTime[MaxNum];//周转时间
    double WeightWholeTime[MaxNum];//带权周转时间
    double AverageWT = 0;//平均周转时间
    double AverageWWT = 0;//平均带权周转时间
    int isAlgorithm;//进程算法输入值，用于验证输入,1为FCFS，2为SJF

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
    }

    //获取算法选择输入
    void InputAlgorithm() {
        cout << endl << "请选择想要先使用的算法（1-FCFS，2-SJF)：";
        cin >> isAlgorithm;
        IsAlgorithm();
    }

    //算法存储
    void IsAlgorithm() {
        if (isAlgorithm == 1) {
            cout << endl << "您选择的是1-FCFS算法" << endl;
        } else if (isAlgorithm == 2) {
            cout << endl << "您选择的是2-SJF算法" << endl;
        } else {
            cout << "算法值" << isAlgorithm << "有误,请重新输入正确的算法类型（1-FCFS，2-SJF）" << endl;
            InputAlgorithm();
        }
    }

    //调用FCFS算法进行调度计算
    void AlgorithmFCFS() {

        //初始化FinishTime[0]
        FinishTime[0] = 0;

        for (int i = 1; i <= n; i++) {
            //计算完成时间
            FinishTime[i] = FinishTime[i - 1] + ServiceTime[i];

            //计算周转时间
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];

            //计算带权周转时间
            WeightWholeTime[i] = (double) WholeTime[i] / ServiceTime[i];

            //计算平均周转时间
            AverageWT += WholeTime[i];

            //计算平局带权周转时间
            AverageWWT += WeightWholeTime[i];
        }
        AverageWT = (double) AverageWT / n;
        AverageWWT = (double) AverageWWT / n;
    }

    //调用SJF算法进行调度计算
    void AlgorithmSJF() {

        int QueueServiceTime[MaxNum];//排序服务时间
        int CopyServiceTime[MaxNum];//备份服务时间

        //初始化QueueServiceTime
        for (int i = 1; i <= n; i++) {
            QueueServiceTime[i] = ServiceTime[i];
        }

        //初始化CopyServiceTime
        for (int i = 1; i <= n; i++) {
            CopyServiceTime[i] = ServiceTime[i];
        }

        //给FinishTime[0]附初值
        FinishTime[0] = 0;

        //从小到大冒泡排序QueueServiceTime
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i; j++) {
                if (QueueServiceTime[j] > QueueServiceTime[j + 1]) {
                    int temp = QueueServiceTime[j];
                    QueueServiceTime[j] = QueueServiceTime[j + 1];
                    QueueServiceTime[j + 1] = temp;
                }
            }
        }

        //计算完成时间
        int temp = -1, old_process = 0, new_process = 0;//定义暂存值、上一个进程、本进程

        for (int i = 1; i <= n; i++) {

            old_process = new_process;

            //查找服务时间最短的进程
            if (i != 1) {
                for (int j = 1; j <= n; j++) {
                    if (QueueServiceTime[j] > 0 && ArrivalTime[j] <= FinishTime[old_process] + 1) {
                        temp = QueueServiceTime[j];
                        QueueServiceTime[j] = -1;
                        break;
                    }
                }
            } else//若为第1个进程，直接进入队列，完成时间即为服务时间
            {
                for (int j = 1; j <= n; j++) {
                    if (QueueServiceTime[j] == ServiceTime[i]) {
                        temp = QueueServiceTime[j];
                        QueueServiceTime[j] = -1;
                        break;
                    }
                }
            }

            //查找该最短服务时间对应的进程号
            for (int j = 1; j <= n; j++) {
                if (CopyServiceTime[j] == temp && CopyServiceTime[j] > 0) {
                    new_process = j;
                    CopyServiceTime[j] = -1;
                    break;
                }
            }

            //计算存储完成时间
            if (i != 1) {
                FinishTime[new_process] = FinishTime[old_process] + temp;
            } else {
                FinishTime[i] = ArrivalTime[i] + ServiceTime[i];
            }

        }

        for (int i = 1; i <= n; i++) {
            //计算周转时间
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];

            //计算带权周转时间
            WeightWholeTime[i] = (double) WholeTime[i] / ServiceTime[i];

            //计算平均周转时间
            AverageWT += WholeTime[i];

            //计算平局带权周转时间
            AverageWWT += WeightWholeTime[i];
        }
        cout << endl;

        AverageWT = (double) AverageWT / n;
        AverageWWT = (double) AverageWWT / n;
    }

    //输出调度过程
    void PrintSchedule() {
        int temp = 0;
        int CopyFinishTime[MaxNum];//备份服务时间

        //初始化CopyServiceTime
        for (int i = 1; i <= n; i++) {
            CopyFinishTime[i] = FinishTime[i];
        }

        if (FinishTime[1] >= 0) {//判断是否已有数据输入
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
    }

    //输出周转时间、带权周转时间、平均周转时间及带权平均周转时间
    void Print() {
        if (FinishTime[1] >= 0)//判断是否已有数据输入
        {
            cout << left << setw(15) << "周转信息如下表：" << endl;

            cout << left << setw(15) << "";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(8) << "Process" << setw(2) << i;
            }
            cout << endl;

            cout << left << setw(15) << "ArrivalTime";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ArrivalTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "ServiceTime";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ServiceTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "FinishTime";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << FinishTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "WholeTime";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WholeTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "WeightWholeTime";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << fixed << setprecision(2) << WeightWholeTime[i];
            }
            cout << endl;

            cout << "平均周转时间:" << setw(10) << setprecision(2) << AverageWT << endl;
            cout << "平均带权周转时间:" << setw(10) << setprecision(2) << AverageWWT << endl;
        }
    }
};


int main() {
    //创建TimeCal类
    TimeCal timeCal{};

    //输入进程信息
    //将输入的ArrivalTime信息与ServiceTime信息存储进数组
    timeCal.InputProcess();

    //获取算法选择输入
    timeCal.InputAlgorithm();

    if (timeCal.isAlgorithm == 1)    //调用FCFS算法进行调度计算
    {
        timeCal.AlgorithmFCFS();
    } else//调用SJF算法进行调度计算
    {
        timeCal.AlgorithmSJF();
    }

    //输出调度过程
    timeCal.PrintSchedule();

    //输出周转时间、带权周转时间、平均周转时间及带权平均周转时间
    timeCal.Print();

    return 0;
}