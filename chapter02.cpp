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
/*    int PServiceTime[MaxNum]{};//ʣ����̷���ʱ��P[i]
    int FinishTime[MaxNum]{};//���ʱ��
    int WholeTime[MaxNum]{};//��תʱ��
    double WeightWholeTime[MaxNum]{};//��Ȩ��תʱ��*/
    double AverageWT = 0;//ƽ����תʱ��
    double AverageWWT = 0;//ƽ����Ȩ��תʱ��
//    bool Finished[MaxNum]{};//���״̬

    typedef struct {
        int number;
        int ArrivalTime;//���̵���ʱ��
        int ServiceTime;//���̷���ʱ��
        int PServiceTime;//ʣ����̷���ʱ��P[i]
        int FinishedTime;//���ʱ��
        int WholeTime;//��תʱ��
        double WeightWholeTime;//��Ȩ��תʱ��
        bool Finished;//���״̬
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
            progress[i].Finished = false;
            progress[i].FinishedTime = -1;
            queueRR.push(progress[i]);
        }
    }

    //����RR�㷨���е��ȼ���
    void ArithRR() {
        int finishTime = 0;
        while (!queueRR.empty()) {
            //������˳���ȡ������ֵ���в������������У��ж����Ƿ���ɣ����ޣ���������β������ִ�й�����������ȹ���
            int x = queueRR.front().number;
            if (progress[x].PServiceTime > q) {//����δ����
                if (finishTime != 0) {
                    cout << "ʱ��" << finishTime + 1 << "����" << x << "��ʼ����" << endl;
                } else {
                    cout << "ʱ��" << finishTime << "����" << x << "��ʼ����" << endl;
                }
                finishTime += q;
                progress[x].PServiceTime -= q;
                queueRR.pop();
                queueRR.push(progress[x]);
            } else {//���̽���
                if (finishTime != 0) {
                    cout << "ʱ��" << finishTime + 1 << "����" << x << "��ʼ����" << endl;
                } else {
                    cout << "ʱ��" << finishTime << "����" << x << "��ʼ����" << endl;
                }
                progress[x].Finished = true;
                finishTime += progress[x].PServiceTime;
                progress[x].PServiceTime = 0;
                progress[x].FinishedTime = finishTime;
                cout << "ʱ��" << finishTime << "����" << x << "��������" << endl;
                queueRR.pop();
            }

            //��������
            for (int i = 1; i <= n; i++) {
                //������תʱ��
                progress[i].WholeTime = progress[i].FinishedTime - progress[i].ArrivalTime;

                //�����Ȩ��תʱ��
                progress[i].WeightWholeTime = (double) progress[i].WholeTime / progress[i].ServiceTime;

                //����ƽ����תʱ��
                AverageWT += progress[i].WholeTime;

                //����ƽ�ִ�Ȩ��תʱ��
                AverageWWT += progress[i].WeightWholeTime;
            }
        }
    }

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    void Print() {
        if (progress[1].FinishedTime >= 0)//�ж��Ƿ�������������
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
    rrSchedule.ArithRR();
    rrSchedule.Print();
    return 0;
}