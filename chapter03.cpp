#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class BankerAlgorithm {
public:

    int n;//进程个数n
    int m;//资源种类m
    int Available[MaxNumber];//可用资源数量
    int Request[MaxNumber];//进程请求的资源数量
    int SafeOrder[MaxNumber];//安全进程序列

    //定义进程的数据结构
    typedef struct {
        int Max[MaxNumber];
        int Allocation[MaxNumber];
        int Need[MaxNumber];
        bool Finished;//完成状态
    } Progress;

    Progress progress[MaxNumber];

    //输入进程数、资源种类、各进程有关资源的Max、Allocation、Need数量
    void Input() {
        cout << "请输入进程个数n：";
        cin >> n;
        cout << "请输入资源种类m：";
        cin >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << "请输入进程" << i << "的资源" << j << "的最大允许数量Max[" << j << "]：";
                cin >> progress[i].Max[j];
            }
            for (int j = 1; j <= m; j++) {
                cout << "请输入进程" << i << "的资源" << j << "的已分配数量Allocation[" << j << "]：";
                cin >> progress[i].Allocation[j];
            }
            for (int j = 1; j <= m; j++) {
                progress[i].Need[j] = progress[i].Max[j] - progress[i].Allocation[j];
            }
        }

        for (int i = 1; i <= m; i++) {
            cout << "请输入可用资源" << i << "的可用数量：";
            cin >> Available[i];
        }

        cout << endl;
    }

    //判断是否有新请求，若无则退出，若有则输入其请求资源数
    void NewRequest(Progress pg[MaxNumber], int a[MaxNumber]) {
        int newRequest;

        //剩余资源数量参考
        cout << endl << "剩余资源情况为：";
        for (int i = 1; i <= m; i++) {
            cout << setw(6) << "资源" << setw(2) << i << setw(6) << "剩余：" << setw(2) << a[i];
        }

        //判断新请求
        cout << endl << "是否还有新请求,若有请输入进程序号，若无请输入0：";
        cin >> newRequest;
        if (newRequest != 0) {
            for (int i = 1; i <= m; i++) {
                cout << "请输入进程" << newRequest << "需求的资源" << i << "的数量:";
                cin >> Request[i];
                if (Request[i] > a[i]) {
                    cout << "可分配资源不足，请重新输入" << endl;
                    NewRequest(pg, a);
                }
                if (Request[i] > pg[newRequest].Need[i]) {
                    cout << "超出需求，请重新输入" << endl;
                    NewRequest(pg, a);
                }
            }

            for (int i = 1; i <= m; i++) {
                a[i] -= Request[i];
                pg[newRequest].Allocation[i] += Request[i];
                pg[newRequest].Need[i] -= Request[i];
            }
            Order(pg, a);
        } else {
            return;
        }
    }

    void Order(Progress pg[MaxNumber], int a[MaxNumber]) {
        //定义下标数
        int orderNum = 0;

        //复制进程操作
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= n; i++) {
            progressCopy[i] = pg[i];
        }

        //复制可用需求数
        int available[MaxNumber];
        for (int i = 1; i <= m; i++) {
            available[i] = a[i];
        }

        while (!NewFinish(progressCopy)) {//若有
            if (IsSafe(progressCopy, available)) {
                for (int i = 1; i <= n; i++) {
                    if (!progressCopy[i].Finished &&
                        IsExecutable(progressCopy[i], available)) {//只有同时满足进程未完成、可分配需求足够才进行分配
                        progressCopy[i].Finished = true;
                        for (int j = 1; j <= m; j++) {
                            available[j] += progressCopy[i].Allocation[j];
                        }
                        SafeOrder[++orderNum] = i;
                    }
                }
            } else {
                cout << "不安全" << endl;
                exit(0);
            }
        }

        //输出SafeOrder
        cout << "SafeOrder为：";
        for (int i = 1; i <= n; i++) {
            cout << setw(12) << "进程" << setw(4) << SafeOrder[i];
        }

        NewRequest(pg, a);
    }

    //判断所有进程是否完成
    bool NewFinish(Progress pg[MaxNumber]) {
        bool finished = true;
        for (int i = 1; i <= n; i++) {
            finished *= pg[i].Finished;
        }
        return finished;
    }

    //判断可分配资源可否满足该进程
    bool IsExecutable(Progress pg, const int a[MaxNumber]) {
        bool isExecutable = true;
        for (int i = 1; i <= m; i++) {
            isExecutable *= (pg.Need[i] <= a[i]);
        }
        return isExecutable;
    }

    //判断现在是否安全
    bool IsSafe(Progress pg[MaxNumber], int a[MaxNumber]) {
        bool isExecutable = false;
        for (int i = 1; i <= n; i++) {
            if (IsExecutable(pg[i], a)) {
                isExecutable = true;
                return isExecutable;
            }
        }
        return isExecutable;
    }
};

int main() {
    BankerAlgorithm bankerAlgorithm{};
    bankerAlgorithm.Input();
    bankerAlgorithm.Order(bankerAlgorithm.progress, bankerAlgorithm.Available);

    return 0;
}