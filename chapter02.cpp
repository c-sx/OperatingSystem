#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;
#define MaxNum 100

class RRSchedule {
public:

    int n;//������
    int q;//ʱ��Ƭ��С
    int ArrivalTime[MaxNum];//���̵���ʱ��T[i]
    int ServiceTime[MaxNum];//���̷���ʱ��S[i]
    double AverageWT = 0;//ƽ����תʱ��
    double AverageWWT = 0;//ƽ����Ȩ��תʱ��

    //������̵����ݽṹ
    typedef struct {
        int index;
        int ArrivalTime;//���̵���ʱ��
        int ServiceTime;//���̷���ʱ��
        int PServiceTime;//ʣ����̷���ʱ��P[i]
        int FinishedTime;//���ʱ��
        int WholeTime;//��תʱ��
        double WeightWholeTime;//��Ȩ��תʱ��
        bool Finished;//���״̬
    } Progress;

    queue<Progress> queueRR;
    Progress progress[MaxNum];

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
        cout << endl;
    }

    void InitQueue() {
        for (int i = 1; i <= n; i++) {
            progress[i].index = i;
            progress[i].ArrivalTime = ArrivalTime[i];
            progress[i].ServiceTime = ServiceTime[i];
            progress[i].PServiceTime = progress[i].ServiceTime;
            progress[i].Finished = false;
            progress[i].FinishedTime = -1;
            queueRR.push(progress[i]);
        }
    }

    //����RR�㷨���е��ȼ���
    void AlgorithmRR() {
        int finishTime = 0;
        while (!queueRR.empty()) {
            //������˳���ȡ������ֵ���в������������У��ж����Ƿ���ɣ����ޣ���������β������ִ�й�����������ȹ���
            int x = queueRR.front().index;
            if (progress[x].PServiceTime > q) {//����δ����
                cout << "ʱ��" << finishTime + 1 << "����" << x << "��ʼ����" << endl;
                finishTime += q;
                progress[x].PServiceTime -= q;
                queueRR.pop();
                queueRR.push(progress[x]);
            } else {//���̽���
                cout << "ʱ��" << finishTime + 1 << "����" << x << "��ʼ����" << endl;
                progress[x].Finished = true;
                finishTime += progress[x].PServiceTime;
                progress[x].PServiceTime = 0;
                progress[x].FinishedTime = finishTime;
                cout << "ʱ��" << finishTime << "����" << x << "��������" << endl;
                queueRR.pop();
            }
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

        //����ƽ����תʱ��
        AverageWT /= (double) n;

        //����ƽ�ִ�Ȩ��תʱ��
        AverageWWT /= (double) n;
    }

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    void Print() {
        cout << endl << left << setw(15) << "��ת��Ϣ���±�" << endl;

        cout << left << setw(15) << "";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(8) << "����" << setw(2) << i;
        }
        cout << endl;

        cout << left << setw(15) << "����ʱ��";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(10) << progress[i].ArrivalTime;
        }
        cout << endl;

        cout << left << setw(15) << "����ʱ��";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(10) << progress[i].ServiceTime;
        }
        cout << endl;

        cout << left << setw(15) << "���ʱ��";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(10) << progress[i].FinishedTime;
        }
        cout << endl;

        cout << left << setw(15) << "��תʱ��";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(10) << progress[i].WholeTime;
        }
        cout << right << setw(30) << "ƽ����תʱ��:" << AverageWT << endl;

        cout << left << setw(15) << "��Ȩ��תʱ��";
        for (int i = 1; i <= n; i++) {
            cout << right << setw(10) << progress[i].WeightWholeTime;
        }
        cout << right << setw(30) << "ƽ����Ȩ��תʱ��:" << AverageWWT << endl;
    }


};

int main() {
    RRSchedule rrSchedule{};
    rrSchedule.InputProcess();
    rrSchedule.InitQueue();
    rrSchedule.AlgorithmRR();
    rrSchedule.Print();
    return 0;
}