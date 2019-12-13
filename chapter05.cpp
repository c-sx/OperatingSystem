#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class virtualMemoryPageReplacementAlgorithm {
public:

    int PageOrder[MaxNumber];//页面序列
    int Simulate[MaxNumber][MaxNumber];//模拟过程
//    int PageCount[MaxNumber];//当前内存距离下一次出现的距离
    int PageNum;//页面数
    int MinBlockNum;//最小物理块数
    int LackNum;//缺页数
    double LackPageRate;//缺页率
    bool found;
    int isAlgorithm;//算法选择

    //输入空闲分区数、空闲的分区大小、进程数、进程需要的分区大小
    void Input() {
        cout << "请输入最小物理块数MinBlockNum：";
        cin >> MinBlockNum;
        cout << "请输入页面个数PageNum：";
        cin >> PageNum;

        for (int i = 1; i <= PageNum; i++) {
            cout << "请输入页面" << i << "编号" << "PageOrder[" << i << "]：";
            cin >> PageOrder[i];
        }

        InputAlgorithm();
    }

    //获取算法选择输入
    void InputAlgorithm() {
        cout << endl
             << "请选择想要先使用的算法（ 1-先进先出(FIFO)页面置换算法，2-最佳(OPI)页面置换算法，3-最近最久未使用(LRU)页面置换算法 ）：";
        cin >> isAlgorithm;
        IsAlgorithm();
    }

    //算法存储确认
    void IsAlgorithm() {
        switch (isAlgorithm) {
            case 1:
                cout << endl << "您选择的是1-先进先出(FIFO)页面置换算法" << endl;
                AlgorithmFIFO();
                break;
            case 2:
                cout << endl << "您选择的是2-最佳(OPI)页面置换算法" << endl;
                AlgorithmOPI();
                break;
            case 3:
                cout << endl << "您选择的是3-最近最久未使用(LRU)页面置换算法" << endl;
                AlgorithmLRU();
                break;
            default:
                cout << "算法值：" << isAlgorithm
                     << "有误,请重新输入正确的算法类型（ 1-先进先出(FIFO)页面置换算法，2-最佳(OPI)页面置换算法，3-最近最久未使用(LRU)页面置换算法 ）"
                     << endl;
                InputAlgorithm();
        }
    }

    //询问是否还要进行其余算法
    void NextAlgorithm() {
        cout << endl
             << "请问是否还要进行其余算法，若是，请输入（1-3值）；若否，请输入任意字符（ 1-先进先出(FIFO)页面置换算法，2-最佳(OPI)页面置换算法，3-最近最久未使用(LRU)页面置换算法 ）：";
        cin >> isAlgorithm;
        if (isAlgorithm != 1 && isAlgorithm != 2 && isAlgorithm != 3) {
            return;
        }
        IsAlgorithm();
    }

    //输出页面置换算法模拟过程及缺页次数与缺页率
    void Print() {

        cout << endl << "页面置换算法模拟过程如下：" << endl;

        //模拟过程
        cout << left << setw(10) << "";
        for (int i = 1; i <= PageNum; i++) {
            cout << right << setw(8) << "Page" << setw(2) << i;
        }

        for (int i = 1; i <= MinBlockNum; i++) {
            cout << endl << left << setw(8) << "BlockNum" << right << setw(2) << i;
            for (int j = 1; j <= PageNum; j++) {
                if (Simulate[i][j] != 0) {
                    cout << right << setw(10) << Simulate[i][j];
                } else {
                    cout << setw(10) << "";
                }
            }
        }

        cout << endl << "页面置换算法缺页次数为：" << LackNum << endl;

        cout << "页面置换算法缺页率为：" << setprecision(2) << LackPageRate * 100 << "%" << endl;

    }

    //调用先进先出(FIFO)页面置换算法进行调度计算
    void AlgorithmFIFO() {
        //初始化缺页次数
        LackNum = 0;
        //定义队列指针，指向下一个换出的页面
        int pointer = 0;

        for (int i = 1; i <= PageNum; i++) {
            //初始化found
            found = false;

            //如果是第一个页面，直接添加页面，缺页数+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                pointer = 1;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //判断是否在物理块中，若存在，则此页面未缺页
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //若缺页且有空物理块，则不置换，直接填入
                if (Simulate[j][i - 1] == 0) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    Simulate[j][i] = PageOrder[i];
                    LackNum++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                for (int j = 1; j <= MinBlockNum; j++) {
                    Simulate[j][i] = Simulate[j][i - 1];
                }
                cout << "页面" << i << "换掉第" << pointer << "物理块中的页面" << endl;
                Simulate[pointer][i] = PageOrder[i];
                LackNum++;
                if (pointer == MinBlockNum) {
                    pointer = 1;
                } else {
                    pointer++;
                }
            }
        }

        LackPageRate = (double) LackNum / (double) PageNum;

        Print();

        NextAlgorithm();
    }

    //调用最佳(OPI)页面置换算法进行调度计算
    void AlgorithmOPI() {
        //初始化缺页次数
        LackNum = 0;

        for (int i = 1; i <= PageNum; i++) {
            //初始化found
            found = false;
            //初始化队列指针，指向下一个换出的页面
            int pointer = 0;
            //初始化最远距离
            int distance = 0;

            //如果是第一个页面，直接添加页面，缺页数+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //判断是否在物理块中，若存在，则此页面未缺页
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //若缺页且有空物理块，则不置换，直接填入
                if (Simulate[j][i - 1] == 0) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    Simulate[j][i] = PageOrder[i];
                    LackNum++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                for (int j = 1; j <= MinBlockNum; j++) {
                    Simulate[j][i] = Simulate[j][i - 1];
                    //寻找最优置换位
                    for (int k = i + 1; k <= PageNum; k++) {
                        if (Simulate[j][i] == PageOrder[k]) {
                            if (k - i > distance) {
                                distance = k - i;
                                pointer = j;
                            }
                            break;
                        }
                        //判断页列表中无此需求，直接将此页面作为替换页面
                        if (k == PageNum && distance < MaxNumber) {
                            distance = MaxNumber;
                            pointer = j;
                        }
                    }
                }

                cout << "页面" << i << "于最远距离" << distance << "换掉第" << pointer << "物理块中的页面" << endl;

                Simulate[pointer][i] = PageOrder[i];
                LackNum++;
            }
        }

        LackPageRate = (double) LackNum / (double) PageNum;

        Print();

        NextAlgorithm();
    }

    //调用最近最久未使用(LRU)页面置换算法进行调度计算
    void AlgorithmLRU() {
        //初始化缺页次数
        LackNum = 0;

        for (int i = 1; i <= PageNum; i++) {
            //初始化found
            found = false;
            //初始化队列指针，指向下一个换出的页面
            int pointer = 0;
            //初始化最远距离
            int distance = 0;

            //如果是第一个页面，直接添加页面，缺页数+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //判断是否在物理块中，若存在，则此页面未缺页
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //若缺页且有空物理块，则不置换，直接填入
                if (Simulate[j][i - 1] == 0) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    Simulate[j][i] = PageOrder[i];
                    LackNum++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                for (int j = 1; j <= MinBlockNum; j++) {
                    Simulate[j][i] = Simulate[j][i - 1];
                    //寻找最优置换位
                    for (int k = i - 1; k > 0; k--) {
                        if (Simulate[j][i] == PageOrder[k]) {
                            if (i - k > distance) {
                                distance = i - k;
                                pointer = j;
                            }
                            break;
                        }
                        //判断页列表中无此需求，直接将此页面作为替换页面
                        if (k == 1 && distance < MaxNumber) {
                            distance = MaxNumber;
                            pointer = j;
                        }
                    }
                }

                cout << "页面" << i << "于最远距离" << distance << "换掉第" << pointer << "物理块中的页面" << endl;

                Simulate[pointer][i] = PageOrder[i];
                LackNum++;
            }
        }

        LackPageRate = (double) LackNum / (double) PageNum;

        Print();

        NextAlgorithm();
    }
};

int main() {
    virtualMemoryPageReplacementAlgorithm virtualMemoryPageReplacementAlgorithm{};

    virtualMemoryPageReplacementAlgorithm.Input();

    return 0;
}