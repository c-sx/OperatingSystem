#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class DiskSchedulingAlgorithm {
public:

    int TrackNum;//�ŵ���
    int TrackOrder[MaxNumber];//���̷�������
//    int MoveDistance[MaxNumber];//��ͷ�ƶ�����
//    double AverageDistance;//ƽ��Ѱ������
    bool direction;//��ͷ�ƶ�����
    int isAlgorithm;//�㷨ѡ��
    int StartTrack;//��ʼ���̺�

    //����ģ����̵����ݽṹ
    typedef struct {
        int TrackIndex;//��ǰ�ŵ�
        int TrackNext;//��һ���ŵ�
        bool Direction;//��ͷ�ƶ�����
        int MoveDistance;//��ͷ�ƶ�����
        double AverageDistance;//ƽ��Ѱ������
    } Simulate;

    Simulate simulate[MaxNumber];

    //������з����������еķ�����С����������������Ҫ�ķ�����С
    void Input() {
        cout << "������ŵ�����TrackNum��";
        cin >> TrackNum;

        cout << "�����뿪ʼ���̺�StartTrack��";
        cin >> StartTrack;

        for (int i = 1; i <= TrackNum; i++) {
            cout << "��������̵�" << i << "�����ʴŵ�" << "TrackOrder[" << i << "]��";
            cin >> TrackOrder[i];
        }

        InputAlgorithm();
    }

    //��ȡ�㷨ѡ������
    void InputAlgorithm() {
        cout << endl
             << "��ѡ����Ҫ��ʹ�õ��㷨�� 1-FCFS��2-SSTF��3-SCAN��4-ѭ��SCAN ��";
        cin >> isAlgorithm;

        if (isAlgorithm != 1) {
            cout << "�������ͷ�ƶ�����direction��!0Ϊ���⣬0Ϊ���ڣ���";
            cin >> direction;
        }

        IsAlgorithm();
    }

    //�㷨�洢ȷ��
    void IsAlgorithm() {
        switch (isAlgorithm) {
            case 1:
                cout << endl << "��ѡ�����1-�����ȷ���FCFS�㷨" << endl;
                AlgorithmFCFS();
                break;
            case 2:
                cout << endl << "��ѡ�����2-���Ѱ��ʱ������SSTF�㷨" << endl;
                AlgorithmSSTF();
                break;
            case 3:
                cout << endl << "��ѡ�����3-SCAN�㷨" << endl;
                AlgorithmSCAN();
                break;
            case 4:
                cout << endl << "��ѡ�����4-ѭ��SCAN�㷨" << endl;
                AlgorithmCycleSCAN();
                break;
            default:
                cout << "�㷨ֵ��" << isAlgorithm
                     << "����,������������ȷ���㷨���ͣ� 1-FCFS��2-SSTF��3-SCAN��4-ѭ��SCAN ��"
                     << endl;
                InputAlgorithm();
        }
    }

    //ѯ���Ƿ�Ҫ���������㷨
    void NextAlgorithm() {
        cout << endl
             << "�����Ƿ�Ҫ���������㷨�����ǣ������루1-4ֵ�������������������ַ��� 1-FCFS��2-SSTF��3-SCAN��4-ѭ��SCAN ����";
        cin >> isAlgorithm;
        if (isAlgorithm != 1 && isAlgorithm != 2 && isAlgorithm != 3 && isAlgorithm != 4) {
            return;
        }
        IsAlgorithm();
    }

    //���ҳ���û��㷨ģ����̼�ȱҳ������ȱҳ��
    void Print() {

        cout << endl << "������̵����㷨ģ��������£�" << endl;

        for (int i = 1; i <= TrackNum; i++) {
            cout << "��ǰ�ŵ�Ϊ��" << right << setw(3) << simulate[i].TrackIndex << "����һ�ŵ�Ϊ��" << right << setw(3)
                 << simulate[i].TrackNext << "��Ѱ������" << (simulate[i].Direction ? "����" : "����") << "��Ѱ������Ϊ��"
                 << simulate[i].MoveDistance << "������ƽ��Ѱ������Ϊ��" << fixed << setprecision(2) << simulate[i].AverageDistance
                 << endl;
        }

        cout << endl << "������̵����㷨ģ�������£�" << endl;
        //ģ�����
        cout << left << setw(15) << "";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(12) << "Simulate" << setw(3) << i;
        }

        cout << left << setw(15) << "TrackIndex";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].TrackIndex;
        }

        cout << left << setw(15) << "TrackNext";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].TrackNext;
        }

        cout << left << setw(15) << "Direction";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << (simulate[i].Direction ? "Outward" : "Inward");
        }

        cout << left << setw(15) << "MoveDistance";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << simulate[i].MoveDistance;
        }

        cout << left << setw(15) << "AverageDistance";
        for (int i = 1; i <= TrackNum; i++) {
            cout << right << setw(15) << setprecision(2) << simulate[i].AverageDistance;
        }

        cout << endl << "�㷨ƽ��Ѱ������Ϊ��" << setprecision(2) << simulate[TrackNum].AverageDistance << endl;

    }

    //�������������ȷ���FCFS�㷨���е��ȼ���
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

    //�������Ѱ��ʱ������SSTF�㷨���е��ȼ���
    void AlgorithmSSTF() {

        Print();

        NextAlgorithm();
    }

    //����SCAN�㷨���е��ȼ���
    void AlgorithmSCAN() {


        Print();

        NextAlgorithm();
    }

    //����ѭ��SCAN�㷨���е��ȼ���
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