#include <iostream>

using namespace std;
#define MaxNum 100

class TimeCal {
public:
    enum Arith {
        FCFS = 1,
        SJF = 2
    };

    int n;//������
    int ArrivalTime[MaxNum];//���̵���ʱ��T[i]
    int ServiceTime[MaxNum];//���̷���ʱ��S[i]
    int FinishTime[MaxNum];//���ʱ��
    int WholeTime[MaxNum];//��תʱ��
    double WeightWholeTime[MaxNum];//��Ȩ��תʱ��
    double AverageWT_FCFS = 0, AverageWT_SJF = 0;//ƽ����תʱ��
    double AverageWWT_FCFS = 0, AverageWWT_SJF = 0;//ƽ����Ȩ��תʱ��

    int isArith;//�����㷨����ֵ��������֤����,1ΪFCFS��2ΪSJF
    Arith arith;//�����㷨ֵ

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
    void InputArith() {
        cout << "��ѡ����Ҫ��ʹ�õ��㷨��1-FCFS��2-SJF)��";
        cin >> isArith;
        IsArith();
    }

    //�㷨�洢
    void IsArith() {
        if (isArith == 1) {
            cout << "��ѡ�����1-FCFS�㷨" << endl;
            arith = FCFS;
        } else if (isArith == 2) {
            cout << "��ѡ�����2-SJF�㷨" << endl;
            arith = SJF;
        } else {
            cout << "�㷨ֵ" << isArith << "����,������������ȷ���㷨���ͣ�1-FCFS��2-SJF��" << endl;
            InputArith();
        }
    }

    //����FCFS�㷨���е��ȼ���
    void ArithFCFS() {

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
            AverageWT_FCFS += WholeTime[i];

            //����ƽ�ִ�Ȩ��תʱ��
            AverageWWT_FCFS += WeightWholeTime[i];
        }
        AverageWT_FCFS = (double) AverageWT_FCFS / n;
        AverageWWT_FCFS = (double) AverageWWT_FCFS / n;
    }

    //����SJF�㷨���е��ȼ���
    void ArithSJF() {

        //��ʼ��FinishTime[0]
        FinishTime[0] = 0;

        int temp[n + 1];//���̷���ʱ��S[i]

        //��С����ð������
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < n - i; j++) {
                if (ServiceTime[j] > ServiceTime[j + 1]) {
                    int temp = nums[j];
                    temp[j] = nums[j + 1];
                    temp[j + 1] = temp;
                }
            }
        }

        for (int i = 1; i <= n; i++) {

            //�������ʱ��
            FinishTime[i] = FinishTime[i - 1] + ServiceTime[i];

        }
/*        for (int i = 1; i <= n; i++) {
            //�������ʱ��
            FinishTime[i] = FinishTime[i - 1] + ServiceTime[i];

            //������תʱ��
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];

            //�����Ȩ��תʱ��
            WeightWholeTime[i] = (double) WholeTime[i] / ServiceTime[i];

            //����ƽ����תʱ��
            AverageWT_FCFS += WholeTime[i];

            //����ƽ�ִ�Ȩ��תʱ��
            AverageWWT_FCFS += WeightWholeTime[i];
        }*/
        AverageWT_FCFS = (double) AverageWT_FCFS / n;
        AverageWWT_FCFS = (double) AverageWWT_FCFS / n;
    }

    //������ȹ���
    void PrintAttemper() {
        if (FinishTime[1] >= 0)//�ж��Ƿ�������������
            for (int i = 1; i <= n; i++) {
                if (i != 1) {
                    cout << "ʱ��" << FinishTime[i - 1] + 1 << "����" << i << "��ʼ����" << endl;
                } else {
                    cout << "ʱ��0����" << i << "��ʼ����" << endl;
                }
            }
    }

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    void Print() {
        if (FinishTime[1] >= 0)//�ж��Ƿ�������������
        {
            cout << "��ת��Ϣ���±�" << endl;

            cout << "������      ";
            for (int i = 1; i <= n; i++) {
                if (0 <= i && i < 10) {
                    cout << "  " << i << " ";
                } else if (10 <= i && i < 100) {
                    cout << " " << i << " ";
                } else {
                    cout << i << " ";
                }
            }
            cout << endl;

            cout << "����ʱ��    ";
            for (int i = 1; i <= n; i++) {
                if (0 <= ArrivalTime[i] && ArrivalTime[i] < 10) {
                    cout << "  " << ArrivalTime[i] << " ";
                } else if (10 <= ArrivalTime[i] && ArrivalTime[i] < 100) {
                    cout << " " << ArrivalTime[i] << " ";
                } else {
                    cout << ArrivalTime[i] << " ";
                }
            }
            cout << endl;

            cout << "����ʱ��    ";
            for (int i = 1; i <= n; i++) {
                if (0 <= ServiceTime[i] && ServiceTime[i] < 10) {
                    cout << "  " << ServiceTime[i] << " ";
                } else if (10 <= ServiceTime[i] && ServiceTime[i] < 100) {
                    cout << " " << ServiceTime[i] << " ";
                } else {
                    cout << ServiceTime[i] << " ";
                }
            }
            cout << endl;

            cout << "���ʱ��    ";
            for (int i = 1; i <= n; i++) {
                if (0 <= FinishTime[i] && FinishTime[i] < 10) {
                    cout << "  " << FinishTime[i] << " ";
                } else if (10 <= FinishTime[i] && FinishTime[i] < 100) {
                    cout << " " << FinishTime[i] << " ";
                } else {
                    cout << FinishTime[i] << " ";
                }
            }
            cout << endl;

            cout << "��תʱ��    ";
            for (int i = 1; i <= n; i++) {
                if (0 <= WholeTime[i] && WholeTime[i] < 10) {
                    cout << "  " << WholeTime[i] << " ";
                } else if (10 <= WholeTime[i] && WholeTime[i] < 100) {
                    cout << " " << WholeTime[i] << " ";
                } else {
                    cout << WholeTime[i] << " ";
                }
            }
            cout << "ƽ����תʱ��:" << AverageWT_FCFS << endl;

            cout << "��Ȩ��תʱ��";
            for (int i = 1; i <= n; i++) {
                if (0 <= WeightWholeTime[i] && WeightWholeTime[i] < 10) {
                    cout << "  " << WeightWholeTime[i] << " ";
                } else if (10 <= WeightWholeTime[i] && WeightWholeTime[i] < 100) {
                    cout << " " << WeightWholeTime[i] << " ";
                } else {
                    cout << WeightWholeTime[i] << " ";
                }
            }
            cout << "ƽ����Ȩ��תʱ��:" << AverageWWT_FCFS << endl;
        }
    }

    //�������
    void TestOut() {
        cout << "���ʱ��    ";
        for (int i = 1; i <= n; i++) {
            if (0 <= FinishTime[i] && FinishTime[i] < 10) {
                cout << "  " << FinishTime[i] << " ";
            }

        }
        cout << endl;
    }
};


int main() {
    //����TimeCal��
    TimeCal timeCal;

    //���������Ϣ
    //�������ArrivalTime��Ϣ��ServiceTime��Ϣ�洢������
    timeCal.InputProcess();

    //��ȡ�㷨ѡ������
    timeCal.InputArith();

    if (timeCal.isArith == 1)    //����FCFS�㷨���е��ȼ���
    {
        timeCal.ArithFCFS();
    } else//����SJF�㷨���е��ȼ���
    {
        timeCal.ArithSJF();
    }

    //������ȹ���
    timeCal.PrintAttemper();

    //�����תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�估��Ȩƽ����תʱ��
    timeCal.Print();

    //timeCal.TestOut();
}