#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class DiskSchedulingAlgorithm {
public:

    int TrackNum;//磁道数
    int TrackOrder[MaxNumber];//磁盘访问序列
//    int MoveDistance[MaxNumber];//磁头移动距离
//    double AverageDistance;//平均寻道长度
    bool direction;//磁头移动方向
    int isAlgorithm;//算法选择
    int StartTrack;//开始磁盘号

    //定义模拟过程的数据结构
    typedef struct {
        int TrackIndex;//当前磁道
        int TrackNext;//下一个磁道
        bool Direction;//磁头移动方向
        int MoveDistance;//磁头移动距离
        double AverageDistance;//平均寻道长度
    } Simulate;

    Simulate simulate[MaxNumber];

    //定义移动距离数据结构
    typedef struct {
        int TrackIndex;//磁道
        int MoveDistance;//磁头移动距离
    } Distance;

    Distance distance[MaxNumber];

    //输入空闲分区数、空闲的分区大小、进程数、进程需要的分区大小
    void Input() {
        cout << "请输入磁道个数TrackNum：";
        cin >> TrackNum;

        cout << "请输入开始磁盘号StartTrack：";
        cin >> StartTrack;

        for (int i = 1; i <= TrackNum; i++) {
            cout << "请输入磁盘第" << i << "个访问磁道" << "TrackOrder[" << i << "]：";
            cin >> TrackOrder[i];
        }

        InputAlgorithm();
    }

    //获取算法选择输入
    void InputAlgorithm() {
        cout << endl
             << "请选择想要先使用的算法（ 1-FCFS，2-SSTF，3-SCAN，4-循环SCAN ：";
        cin >> isAlgorithm;

        if (isAlgorithm != 1) {
            cout << "请输入磁头移动方向direction（!0为向外，0为向内）：";
            cin >> direction;
        }

        IsAlgorithm();
    }

    //算法存储确认
    void IsAlgorithm() {
        switch (isAlgorithm) {
            case 1:
                cout << endl << "您选择的是1-先来先服务FCFS算法" << endl;
                AlgorithmFCFS();
                break;
            case 2:
                cout << endl << "您选择的是2-最短寻道时间优先SSTF算法" << endl;
                AlgorithmSSTF();
                break;
            case 3:
                cout << endl << "您选择的是3-SCAN算法" << endl;
                AlgorithmSCAN();
                break;
            case 4:
                cout << endl << "您选择的是4-循环SCAN算法" << endl;
                AlgorithmCycleSCAN();
                break;
            default:
                cout << "算法值：" << isAlgorithm
                     << "有误,请重新输入正确的算法类型（ 1-FCFS，2-SSTF，3-SCAN，4-循环SCAN ）"
                     << endl;
                InputAlgorithm();
        }
    }

    //询问是否还要进行其余算法
    void NextAlgorithm() {
        cout << endl
             << "请问是否还要进行其余算法，若是，请输入（1-4值）；若否，请输入任意字符（ 1-FCFS，2-SSTF，3-SCAN，4-循环SCAN ）：";
        cin >> isAlgorithm;
        if (isAlgorithm != 1 && isAlgorithm != 2 && isAlgorithm != 3 && isAlgorithm != 4) {
            return;
        }
        IsAlgorithm();
    }

    //输出页面置换算法模拟过程及缺页次数与缺页率
    void Print() {

        cout << endl << "输出磁盘调度算法模拟过程如下：" << endl;

        for (int i = 1; i <= TrackNum; i++) {
            cout << "当前磁道为：" << right << setw(3) << simulate[i].TrackIndex << "，下一磁道为：" << right << setw(3)
                 << simulate[i].TrackNext << "，寻道方向：" << (simulate[i].Direction ? "向外" : "向内") << "，寻道距离为："
                 << simulate[i].MoveDistance << "，至此平均寻道距离为：" << fixed << setprecision(2) << simulate[i].AverageDistance
                 << endl;
        }

        cout << endl << "输出磁盘调度算法模拟表格如下：" << endl;
        //模拟过程
        cout << endl << left << setw(15) << "";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(12) << "Simulate" << setw(3) << i;
        }

        cout << endl << left << setw(15) << "TrackIndex";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].TrackIndex;
        }

        cout << endl << left << setw(15) << "TrackNext";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].TrackNext;
        }

        cout << endl << left << setw(15) << "Direction";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << (simulate[i].Direction ? "Outward" : "Inward");
        }

        cout << endl << left << setw(15) << "MoveDistance";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].MoveDistance;
        }

        cout << endl << left << setw(15) << "AverageDistance";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << setprecision(2) << simulate[i].AverageDistance;
        }

        cout << endl << "算法平均寻道长度为：" << setprecision(2) << simulate[TrackNum].AverageDistance << endl;

    }

    //调用利用先来先服务FCFS算法进行调度计算
    void AlgorithmFCFS() {

        for (int i = 1; i <= TrackNum; i++) {
            if (i == 1) {
                simulate[i].TrackIndex = StartTrack;
                simulate[i].Direction = (simulate[i].TrackIndex < TrackOrder[i]);
                simulate[i].MoveDistance =
                        simulate[i].TrackIndex > TrackOrder[i] ? simulate[i].TrackIndex - TrackOrder[i] :
                        TrackOrder[i] - simulate[i].TrackIndex;
                simulate[i].AverageDistance = simulate[i].MoveDistance;
                simulate[i].TrackNext = TrackOrder[i];
                continue;
            }
            simulate[i].TrackIndex = TrackOrder[i - 1];
            simulate[i].Direction = (simulate[i].TrackIndex < TrackOrder[i]);
            simulate[i].MoveDistance =
                    simulate[i].TrackIndex > TrackOrder[i] ? simulate[i].TrackIndex - TrackOrder[i] : TrackOrder[i] -
                                                                                                      simulate[i].TrackIndex;
            simulate[i].AverageDistance = ((simulate[i - 1].AverageDistance * (double) (i - 1) / (double) i) +
                                           ((double) simulate[i].MoveDistance / (double) i));
            simulate[i].TrackNext = TrackOrder[i];
        }

        Print();

        NextAlgorithm();
    }

    //调用最短寻道时间优先SSTF算法进行调度计算
    void AlgorithmSSTF() {

        for (int i = 1; i <= TrackNum; i++) {

            //计算当前磁道到其它磁道的移动距离
            for (int j = 1; j <= TrackNum; j++) {
                distance[j].TrackIndex = TrackOrder[j];
                if (i == 1) {
                    distance[j].MoveDistance =
                            StartTrack > TrackOrder[j] ? StartTrack - TrackOrder[j] : TrackOrder[j] - StartTrack;
                } else if (i == j) {
                    distance[j].MoveDistance = MaxNumber;
                } else {
                    distance[j].MoveDistance =
                            TrackOrder[i] > TrackOrder[j] ? TrackOrder[i] - TrackOrder[j] : TrackOrder[j] -
                                                                                            TrackOrder[i];
                }
            }

            //按MoveDistance从小到大冒泡排序Distance序列
            for (int j = 1; j <= TrackNum; j++) {
                for (int k = 1; k <= TrackNum - j; k++) {
                    if (distance[k].MoveDistance > distance[k + 1].MoveDistance) {
                        Distance temp = distance[k];
                        distance[k].MoveDistance = distance[k + 1].MoveDistance;
                        distance[k + 1] = temp;
                    }
                }
            }

            //xie写入simulate模拟数组
            if (i == 1) {
                simulate[i].TrackIndex = StartTrack;
                simulate[i].Direction = (simulate[i].TrackIndex < distance[1].TrackIndex);
                simulate[i].MoveDistance = distance[1].MoveDistance;
                simulate[i].AverageDistance = simulate[i].MoveDistance;
                simulate[i].TrackNext = distance[1].TrackIndex;
                continue;
            }
            simulate[i].TrackIndex = simulate[i - 1].TrackNext;
            simulate[i].Direction = (simulate[i].TrackIndex < distance[1].TrackIndex);
            simulate[i].MoveDistance = distance[1].MoveDistance;
            simulate[i].AverageDistance = ((simulate[i - 1].AverageDistance * (double) (i - 1) / (double) i) +
                                           ((double) simulate[i].MoveDistance / (double) i));
            simulate[i].TrackNext = distance[1].TrackIndex;
        }

        Print();

        NextAlgorithm();
    }

    //调用SCAN算法进行调度计算
    void AlgorithmSCAN() {


        Print();

        NextAlgorithm();
    }

    //调用循环SCAN算法进行调度计算
    void AlgorithmCycleSCAN() {


        Print();

        NextAlgorithm();
    }
};

int main() {
    DiskSchedulingAlgorithm diskSchedulingAlgorithm{};

    diskSchedulingAlgorithm.Input();

    return 0;
}