#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;
#define MaxNum 100

class RRSchedule {
public:

    int n{};//������
    int q{};//ʱ��Ƭ��С
    int ArrivalTime[MaxNum]{};//���̵���ʱ��T[i]
    int ServiceTime[MaxNum]{};//���̷���ʱ��S[i]
    int PServiceTime[MaxNum]{};//ʣ����̷���ʱ��P[i]
    int FinishTime[MaxNum]{};//���ʱ��
    int WholeTime[MaxNum]{};//��תʱ��
    double WeightWholeTime[MaxNum]{};//��Ȩ��תʱ��
    double AverageWT{};//ƽ����תʱ��
    double AverageWWT{};//ƽ����Ȩ��תʱ��
    bool Finished[MaxNum]{};//���״̬

    typedef struct {
        int number;
        int ArrivalTime;//���̵���ʱ��
        int ServiceTime;//���̷���ʱ��
        int PServiceTime;//ʣ����̷���ʱ��P[i]
        int FinishedTime;//���ʱ��
        int WholeTime;//��תʱ��
        double WeightWholeTime;//��Ȩ��תʱ��
        bool Finished[MaxNum];//���״̬
    } Progress;

    queue<Progress> queueRR;
    Progress progress[MaxNum]{};

    //���������Ϣ
    //�������ArrivalTime��Ϣ��ServiceTime��Ϣ�洢������
    void InputProcess() {
        cout << "���������������";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cout << "���������" << i << "�ĵ���ʱ��ArrivalTime[" << i << "]��";
            cin >> ArrivalTime[i];
            cout << "���������" << i << "�ķ���ʱ��ServiceTime[" << i << "]��";
            cin >> ServiceTime[i];
        }
        cout << "������ʱ��Ƭ��С��";
        cin >> q;
    }

    void InitQueue() {
        for (int i = 1; i <= n; i++) {
            progress[i].number = i;
            progress[i].ArrivalTime = ArrivalTime[i];
            progress[i].ServiceTime = ServiceTime[i];
            progress[i].PServiceTime = progress[i].ServiceTime;
            queueRR.push(progress[i]);
        }
    }

    //����RR�㷨���е��ȼ���
    void ArithRR() {

    }

    //������ȹ���
    void PrintSchedule() {
        int temp = 0;
        int CopyFinishTime[MaxNum];//���ݷ���ʱ��

        //��ʼ��CopyServiceTime
        for (int i = 1; i <= n; i++) {
            CopyFinishTime[i] = FinishTime[i];
        }

        if (FinishTime[1] >= 0)//�ж��Ƿ�������������
            //�������ʱ���������
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
                    if (i != 2) { cout << "����" << temp << "��ʼ����" << endl; }
                    cout << "ʱ��" << FinishTime[temp] + 1;
                    if (i == n) {
                        for (int j = 1; j < n; j++) {
                            if (CopyFinishTime[j] > 0) {
                                temp = j;
                            }
                        }
                        cout << "����" << temp << "��ʼ����" << endl << endl;
                    }
                    CopyFinishTime[temp] = -1;
                    temp = 0;
                } else {
                    cout << "ʱ��0����" << i << "��ʼ����" << endl;
                }
            }
    }

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    void Print() {
        if (FinishTime[1] >= 0)//�ж��Ƿ�������������
        {
            cout << left << setw(15) << "��ת��Ϣ���±�" << endl;

            cout << left << setw(15) << "";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << "����" << i;
            }
            cout << endl;

            cout << left << setw(15) << "����ʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ArrivalTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "����ʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << ServiceTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "���ʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << FinishTime[i];
            }
            cout << endl;

            cout << left << setw(15) << "��תʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WholeTime[i];
            }
            cout << right << setw(30) << "ƽ����תʱ��:" << AverageWT << endl;

            cout << left << setw(15) << "��Ȩ��תʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WeightWholeTime[i];
            }
            cout << right << setw(30) << "ƽ����Ȩ��תʱ��:" << AverageWWT << endl;
        }
    }


};

int main() {
    RRSchedule rrSchedule;
    rrSchedule.InputProcess();
    rrSchedule.InitQueue();

    return 0;
}