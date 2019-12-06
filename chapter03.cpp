#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class BankerAlgorithm {
public:

    int n;//���̸���n
    int m;//��Դ����m
    int Available[MaxNumber];//������Դ����
    int Request[MaxNumber];//�����������Դ����
    int SafeOrder[MaxNumber];//��ȫ��������

    //������̵����ݽṹ
    typedef struct {
        int Max[MaxNumber];
        int Allocation[MaxNumber];
        int Need[MaxNumber];
        bool Finished;//���״̬
    } Progress;

    Progress progress[MaxNumber];

    //�������������Դ���ࡢ�������й���Դ��Max��Allocation��Need����
    void Input() {
        cout << "��������̸���n��";
        cin >> n;
        cout << "��������Դ����m��";
        cin >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << "���������" << i << "����Դ" << j << "�������������Max[" << j << "]��";
                cin >> progress[i].Max[j];
            }
            for (int j = 1; j <= m; j++) {
                cout << "���������" << i << "����Դ" << j << "���ѷ�������Allocation[" << j << "]��";
                cin >> progress[i].Allocation[j];
            }
            for (int j = 1; j <= m; j++) {
                progress[i].Need[j] = progress[i].Max[j] - progress[i].Allocation[j];
            }
        }

        for (int i = 1; i <= m; i++) {
            cout << "�����������Դ" << i << "�Ŀ���������";
            cin >> Available[i];
        }

        cout << endl;
    }

    //�ж��Ƿ����������������˳���������������������Դ��
    void NewRequest(Progress pg[MaxNumber], int a[MaxNumber]) {
        int newRequest;

        //ʣ����Դ�����ο�
        cout << endl << "ʣ����Դ���Ϊ��";
        for (int i = 1; i <= m; i++) {
            cout << setw(6) << "��Դ" << setw(2) << i << setw(6) << "ʣ�ࣺ" << setw(2) << a[i];
        }

        //�ж�������
        cout << endl << "�Ƿ���������,���������������ţ�����������0��";
        cin >> newRequest;
        if (newRequest != 0) {
            for (int i = 1; i <= m; i++) {
                cout << "���������" << newRequest << "�������Դ" << i << "������:";
                cin >> Request[i];
                if (Request[i] > a[i]) {
                    cout << "�ɷ�����Դ���㣬����������" << endl;
                    NewRequest(pg, a);
                }
                if (Request[i] > pg[newRequest].Need[i]) {
                    cout << "������������������" << endl;
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
        //�����±���
        int orderNum = 0;

        //���ƽ��̲���
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= n; i++) {
            progressCopy[i] = pg[i];
        }

        //���ƿ���������
        int available[MaxNumber];
        for (int i = 1; i <= m; i++) {
            available[i] = a[i];
        }

        while (!NewFinish(progressCopy)) {//����
            if (IsSafe(progressCopy, available)) {
                for (int i = 1; i <= n; i++) {
                    if (!progressCopy[i].Finished &&
                        IsExecutable(progressCopy[i], available)) {//ֻ��ͬʱ�������δ��ɡ��ɷ��������㹻�Ž��з���
                        progressCopy[i].Finished = true;
                        for (int j = 1; j <= m; j++) {
                            available[j] += progressCopy[i].Allocation[j];
                        }
                        SafeOrder[++orderNum] = i;
                    }
                }
            } else {
                cout << "����ȫ" << endl;
                exit(0);
            }
        }

        //���SafeOrder
        cout << "SafeOrderΪ��";
        for (int i = 1; i <= n; i++) {
            cout << setw(12) << "����" << setw(4) << SafeOrder[i];
        }

        NewRequest(pg, a);
    }

    //�ж����н����Ƿ����
    bool NewFinish(Progress pg[MaxNumber]) {
        bool finished = true;
        for (int i = 1; i <= n; i++) {
            finished *= pg[i].Finished;
        }
        return finished;
    }

    //�жϿɷ�����Դ�ɷ�����ý���
    bool IsExecutable(Progress pg, const int a[MaxNumber]) {
        bool isExecutable = true;
        for (int i = 1; i <= m; i++) {
            isExecutable *= (pg.Need[i] <= a[i]);
        }
        return isExecutable;
    }

    //�ж������Ƿ�ȫ
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