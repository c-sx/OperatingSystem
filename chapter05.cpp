#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class virtualMemoryPageReplacementAlgorithm {
public:

    int PageOrder[MaxNumber];//ҳ������
    int Simulate[MaxNumber][MaxNumber];//ģ�����
//    int PageCount[MaxNumber];//��ǰ�ڴ������һ�γ��ֵľ���
    int PageNum;//ҳ����
    int MinBlockNum;//��С�������
    int LackNum;//ȱҳ��
    double LackPageRate;//ȱҳ��
    bool found;
    int isAlgorithm;//�㷨ѡ��

    //������з����������еķ�����С����������������Ҫ�ķ�����С
    void Input() {
        cout << "��������С�������MinBlockNum��";
        cin >> MinBlockNum;
        cout << "������ҳ�����PageNum��";
        cin >> PageNum;

        for (int i = 1; i <= PageNum; i++) {
            cout << "������ҳ��" << i << "���" << "PageOrder[" << i << "]��";
            cin >> PageOrder[i];
        }

        InputAlgorithm();
    }

    //��ȡ�㷨ѡ������
    void InputAlgorithm() {
        cout << endl
             << "��ѡ����Ҫ��ʹ�õ��㷨�� 1-�Ƚ��ȳ�(FIFO)ҳ���û��㷨��2-���(OPI)ҳ���û��㷨��3-������δʹ��(LRU)ҳ���û��㷨 ����";
        cin >> isAlgorithm;
        IsAlgorithm();
    }

    //�㷨�洢ȷ��
    void IsAlgorithm() {
        switch (isAlgorithm) {
            case 1:
                cout << endl << "��ѡ�����1-�Ƚ��ȳ�(FIFO)ҳ���û��㷨" << endl;
                AlgorithmFIFO();
                break;
            case 2:
                cout << endl << "��ѡ�����2-���(OPI)ҳ���û��㷨" << endl;
                AlgorithmOPI();
                break;
            case 3:
                cout << endl << "��ѡ�����3-������δʹ��(LRU)ҳ���û��㷨" << endl;
                AlgorithmLRU();
                break;
            default:
                cout << "�㷨ֵ��" << isAlgorithm
                     << "����,������������ȷ���㷨���ͣ� 1-�Ƚ��ȳ�(FIFO)ҳ���û��㷨��2-���(OPI)ҳ���û��㷨��3-������δʹ��(LRU)ҳ���û��㷨 ��"
                     << endl;
                InputAlgorithm();
        }
    }

    //ѯ���Ƿ�Ҫ���������㷨
    void NextAlgorithm() {
        cout << endl
             << "�����Ƿ�Ҫ���������㷨�����ǣ������루1-3ֵ�������������������ַ��� 1-�Ƚ��ȳ�(FIFO)ҳ���û��㷨��2-���(OPI)ҳ���û��㷨��3-������δʹ��(LRU)ҳ���û��㷨 ����";
        cin >> isAlgorithm;
        if (isAlgorithm != 1 && isAlgorithm != 2 && isAlgorithm != 3) {
            return;
        }
        IsAlgorithm();
    }

    //���ҳ���û��㷨ģ����̼�ȱҳ������ȱҳ��
    void Print() {

        cout << endl << "ҳ���û��㷨ģ��������£�" << endl;

        //ģ�����
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

        cout << endl << "ҳ���û��㷨ȱҳ����Ϊ��" << LackNum << endl;

        cout << "ҳ���û��㷨ȱҳ��Ϊ��" << setprecision(2) << LackPageRate * 100 << "%" << endl;

    }

    //�����Ƚ��ȳ�(FIFO)ҳ���û��㷨���е��ȼ���
    void AlgorithmFIFO() {
        //��ʼ��ȱҳ����
        LackNum = 0;
        //�������ָ�룬ָ����һ��������ҳ��
        int pointer = 0;

        for (int i = 1; i <= PageNum; i++) {
            //��ʼ��found
            found = false;

            //����ǵ�һ��ҳ�棬ֱ�����ҳ�棬ȱҳ��+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                pointer = 1;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //�ж��Ƿ���������У������ڣ����ҳ��δȱҳ
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //��ȱҳ���п�����飬���û���ֱ������
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
                cout << "ҳ��" << i << "������" << pointer << "������е�ҳ��" << endl;
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

    //�������(OPI)ҳ���û��㷨���е��ȼ���
    void AlgorithmOPI() {
        //��ʼ��ȱҳ����
        LackNum = 0;

        for (int i = 1; i <= PageNum; i++) {
            //��ʼ��found
            found = false;
            //��ʼ������ָ�룬ָ����һ��������ҳ��
            int pointer = 0;
            //��ʼ����Զ����
            int distance = 0;

            //����ǵ�һ��ҳ�棬ֱ�����ҳ�棬ȱҳ��+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //�ж��Ƿ���������У������ڣ����ҳ��δȱҳ
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //��ȱҳ���п�����飬���û���ֱ������
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
                    //Ѱ�������û�λ
                    for (int k = i + 1; k <= PageNum; k++) {
                        if (Simulate[j][i] == PageOrder[k]) {
                            if (k - i > distance) {
                                distance = k - i;
                                pointer = j;
                            }
                            break;
                        }
                        //�ж�ҳ�б����޴�����ֱ�ӽ���ҳ����Ϊ�滻ҳ��
                        if (k == PageNum && distance < MaxNumber) {
                            distance = MaxNumber;
                            pointer = j;
                        }
                    }
                }

                cout << "ҳ��" << i << "����Զ����" << distance << "������" << pointer << "������е�ҳ��" << endl;

                Simulate[pointer][i] = PageOrder[i];
                LackNum++;
            }
        }

        LackPageRate = (double) LackNum / (double) PageNum;

        Print();

        NextAlgorithm();
    }

    //����������δʹ��(LRU)ҳ���û��㷨���е��ȼ���
    void AlgorithmLRU() {
        //��ʼ��ȱҳ����
        LackNum = 0;

        for (int i = 1; i <= PageNum; i++) {
            //��ʼ��found
            found = false;
            //��ʼ������ָ�룬ָ����һ��������ҳ��
            int pointer = 0;
            //��ʼ����Զ����
            int distance = 0;

            //����ǵ�һ��ҳ�棬ֱ�����ҳ�棬ȱҳ��+1
            if (i == 1) {
                Simulate[1][i] = PageOrder[i];
                LackNum++;
                continue;
            }

            for (int j = 1; j <= MinBlockNum; j++) {
                //�ж��Ƿ���������У������ڣ����ҳ��δȱҳ
                if (Simulate[j][i - 1] == PageOrder[i]) {
                    for (int k = 1; k <= MinBlockNum; k++) {
                        Simulate[k][i] = Simulate[k][i - 1];
                    }
                    found = true;
                    break;
                }

                //��ȱҳ���п�����飬���û���ֱ������
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
                    //Ѱ�������û�λ
                    for (int k = i - 1; k > 0; k--) {
                        if (Simulate[j][i] == PageOrder[k]) {
                            if (i - k > distance) {
                                distance = i - k;
                                pointer = j;
                            }
                            break;
                        }
                        //�ж�ҳ�б����޴�����ֱ�ӽ���ҳ����Ϊ�滻ҳ��
                        if (k == 1 && distance < MaxNumber) {
                            distance = MaxNumber;
                            pointer = j;
                        }
                    }
                }

                cout << "ҳ��" << i << "����Զ����" << distance << "������" << pointer << "������е�ҳ��" << endl;

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