#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNum 100

class TimeCal {
public:

    int n;//������
    int ArrivalTime[MaxNum];//���̵���ʱ��T[i]
    int ServiceTime[MaxNum];//���̷���ʱ��S[i]
    int FinishTime[MaxNum];//���ʱ��
    int WholeTime[MaxNum];//��תʱ��
    double WeightWholeTime[MaxNum];//��Ȩ��תʱ��
    double AverageWT = 0;//ƽ����תʱ��
    double AverageWWT = 0;//ƽ����Ȩ��תʱ��
    int isAlgorithm;//�����㷨����ֵ��������֤����,1ΪFCFS��2ΪSJF

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
    }

    //��ȡ�㷨ѡ������
    void InputAlgorithm() {
        cout << endl << "��ѡ����Ҫ��ʹ�õ��㷨��1-FCFS��2-SJF)��";
        cin >> isAlgorithm;
        IsAlgorithm();
    }

    //�㷨�洢
    void IsAlgorithm() {
        if (isAlgorithm == 1) {
            cout << endl << "��ѡ�����1-FCFS�㷨" << endl;
        } else if (isAlgorithm == 2) {
            cout << endl << "��ѡ�����2-SJF�㷨" << endl;
        } else {
            cout << "�㷨ֵ" << isAlgorithm << "����,������������ȷ���㷨���ͣ�1-FCFS��2-SJF��" << endl;
            InputAlgorithm();
        }
    }

    //����FCFS�㷨���е��ȼ���
    void AlgorithmFCFS() {

        //��ʼ��FinishTime[0]
        FinishTime[0] = 0;

        for (int i = 1; i <= n; i++) {
            //�������ʱ��
            FinishTime[i] = FinishTime[i - 1] + ServiceTime[i];

            //������תʱ��
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];

            //�����Ȩ��תʱ��
            WeightWholeTime[i] = (double) WholeTime[i] / ServiceTime[i];

            //����ƽ����תʱ��
            AverageWT += WholeTime[i];

            //����ƽ�ִ�Ȩ��תʱ��
            AverageWWT += WeightWholeTime[i];
        }
        AverageWT = (double) AverageWT / n;
        AverageWWT = (double) AverageWWT / n;
    }

    //����SJF�㷨���е��ȼ���
    void AlgorithmSJF() {

        int QueueServiceTime[MaxNum];//�������ʱ��
        int CopyServiceTime[MaxNum];//���ݷ���ʱ��

        //��ʼ��QueueServiceTime
        for (int i = 1; i <= n; i++) {
            QueueServiceTime[i] = ServiceTime[i];
        }

        //��ʼ��CopyServiceTime
        for (int i = 1; i <= n; i++) {
            CopyServiceTime[i] = ServiceTime[i];
        }

        //��FinishTime[0]����ֵ
        FinishTime[0] = 0;

        //��С����ð������QueueServiceTime
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i; j++) {
                if (QueueServiceTime[j] > QueueServiceTime[j + 1]) {
                    int temp = QueueServiceTime[j];
                    QueueServiceTime[j] = QueueServiceTime[j + 1];
                    QueueServiceTime[j + 1] = temp;
                }
            }
        }

        //�������ʱ��
        int temp = -1, old_process = 0, new_process = 0;//�����ݴ�ֵ����һ�����̡�������

        for (int i = 1; i <= n; i++) {

            old_process = new_process;

            //���ҷ���ʱ����̵Ľ���
            if (i != 1) {
                for (int j = 1; j <= n; j++) {
                    if (QueueServiceTime[j] > 0 && ArrivalTime[j] <= FinishTime[old_process] + 1) {
                        temp = QueueServiceTime[j];
                        QueueServiceTime[j] = -1;
                        break;
                    }
                }
            } else//��Ϊ��1�����̣�ֱ�ӽ�����У����ʱ�伴Ϊ����ʱ��
            {
                for (int j = 1; j <= n; j++) {
                    if (QueueServiceTime[j] == ServiceTime[i]) {
                        temp = QueueServiceTime[j];
                        QueueServiceTime[j] = -1;
                        break;
                    }
                }
            }

            //���Ҹ���̷���ʱ���Ӧ�Ľ��̺�
            for (int j = 1; j <= n; j++) {
                if (CopyServiceTime[j] == temp && CopyServiceTime[j] > 0) {
                    new_process = j;
                    CopyServiceTime[j] = -1;
                    break;
                }
            }

            //����洢���ʱ��
            if (i != 1) {
                FinishTime[new_process] = FinishTime[old_process] + temp;
            } else {
                FinishTime[i] = ArrivalTime[i] + ServiceTime[i];
            }

        }

        for (int i = 1; i <= n; i++) {
            //������תʱ��
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];

            //�����Ȩ��תʱ��
            WeightWholeTime[i] = (double) WholeTime[i] / ServiceTime[i];

            //����ƽ����תʱ��
            AverageWT += WholeTime[i];

            //����ƽ�ִ�Ȩ��תʱ��
            AverageWWT += WeightWholeTime[i];
        }
        cout << endl;

        AverageWT = (double) AverageWT / n;
        AverageWWT = (double) AverageWWT / n;
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
                cout << right << setw(8) << "����" << setw(2) << i;
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
            cout << right << setw(20) << "ƽ����תʱ��:" << setw(10) << AverageWT << endl;

            cout << left << setw(15) << "��Ȩ��תʱ��";
            for (int i = 1; i <= n; i++) {
                cout << right << setw(10) << WeightWholeTime[i];
            }
            cout << right << setw(20) << "ƽ����Ȩ��תʱ��:" << setw(10) << AverageWWT << endl;
        }
    }
};


int main() {
    //����TimeCal��
    TimeCal timeCal{};

    //���������Ϣ
    //�������ArrivalTime��Ϣ��ServiceTime��Ϣ�洢������
    timeCal.InputProcess();

    //��ȡ�㷨ѡ������
    timeCal.InputAlgorithm();

    if (timeCal.isAlgorithm == 1)    //����FCFS�㷨���е��ȼ���
    {
        timeCal.AlgorithmFCFS();
    } else//����SJF�㷨���е��ȼ���
    {
        timeCal.AlgorithmSJF();
    }

    //������ȹ���
    timeCal.PrintSchedule();

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    timeCal.Print();

    return 0;
}