#include <iostream>
#include <iomanip>

using namespace std;
#define MaxNumber 100

class PartitionAlgorithm {
public:

    int FreePartition[MaxNumber];//���з�����С
    int PartitionNum;//���з�������
    int ProcessNum;//���̸���
    int isAlgorithm;//�㷨ѡ��

    //������̵����ݽṹ
    typedef struct {
        int FirstPartition;//�״���Ӧ����
        int CycleFirstPartition;//ѭ���״���Ӧ����
        int BestPartition;//�����Ӧ����
        int WorstPartition;//���Ӧ����
        int ProcessNeed;//������Ҫ�ķ�����С
    } Progress;

    Progress progress[MaxNumber];

    //������з����������еķ�����С����������������Ҫ�ķ�����С
    void Input() {
        cout << "��������з�������PartitionNum��";
        cin >> PartitionNum;

        for (int i = 1; i <= PartitionNum; i++) {
            cout << "��������з���" << i << "��С" << "FreePartition[" << i << "]��";
            cin >> FreePartition[i];
        }

        cout << "��������̸���ProcessNum��";
        cin >> ProcessNum;

        for (int i = 1; i <= ProcessNum; i++) {
            cout << "���������" << i << "��Ҫ�ķ�����С" << "progress[" << i << "].ProcessNeed��";
            cin >> progress[i].ProcessNeed;
        }

        cout << endl;

        InputAlgorithm();
    }

    //��ȡ�㷨ѡ������
    void InputAlgorithm() {
        cout << endl
             << "��ѡ����Ҫ��ʹ�õ��㷨��1-�״���Ӧ�����㷨��FirstPartition����2-ѭ���״���Ӧ�����㷨��CycleFirstPartition����3-�����Ӧ�����㷨��BestPartition����4-���Ӧ�����㷨��WorstPartition������";
        cin >> isAlgorithm;
        IsAlgorithm();
    }

    //�㷨�洢ȷ��
    void IsAlgorithm() {
        switch (isAlgorithm) {
            case 1:
                cout << endl << "��ѡ�����1-�״���Ӧ�����㷨��FirstPartition��" << endl;
                AlgorithmFirstPartition();
                break;
            case 2:
                cout << endl << "��ѡ�����2-ѭ���״���Ӧ�����㷨��CycleFirstPartition��" << endl;
                AlgorithmCycleFirstPartitionS();
                break;
            case 3:
                cout << endl << "��ѡ�����3-�����Ӧ�����㷨��BestPartition��" << endl;
                AlgorithmBestPartition();
                break;
            case 4:
                cout << endl << "��ѡ�����4-���Ӧ�����㷨��WorstPartition��" << endl;
                AlgorithmWorstPartition();
                break;
            default:
                cout << "�㷨ֵ��" << isAlgorithm
                     << "����,������������ȷ���㷨���ͣ�1-�״���Ӧ�����㷨��FirstPartition����2-ѭ���״���Ӧ�����㷨��CycleFirstPartition����3-�����Ӧ�����㷨��BestPartition����4-���Ӧ�����㷨��WorstPartition����"
                     << endl;
                InputAlgorithm();
        }
    }

    //������з���ʣ������������̷������
    void Print(Progress pg[MaxNumber], int fp[MaxNumber]) {

        cout << endl << left << setw(15) << "���̷���������±�" << endl;

        //����״��
        cout << left << setw(15) << "";
        for (int i = 1; i <= PartitionNum; i++) {
            cout << right << setw(8) << "����" << setw(2) << i;
        }
        cout << endl << left << setw(15) << "�ѷ�������";
        for (int i = 1; i <= PartitionNum; i++) {
            cout << right << setw(10) << FreePartition[i] - fp[i];
        }
        cout << endl << left << setw(15) << "ʣ������";
        for (int i = 1; i <= PartitionNum; i++) {
            cout << right << setw(10) << fp[i];
        }
        cout << endl;

        //���̷���״��
        cout << left << setw(15) << "";
        for (int i = 1; i <= ProcessNum; i++) {
            cout << right << setw(8) << "����" << setw(2) << i;
        }
        cout << endl << left << setw(15) << "�����������";
        for (int i = 1; i <= ProcessNum; i++) {
            switch (isAlgorithm) {
                case 1:
                    cout << right << setw(10) << pg[i].FirstPartition;
                    break;
                case 2:
                    cout << right << setw(10) << pg[i].CycleFirstPartition;
                    break;
                case 3:
                    cout << right << setw(10) << pg[i].BestPartition;
                    break;
                case 4:
                    cout << right << setw(10) << pg[i].WorstPartition;
                    break;
            }
        }
        cout << endl;

    }

    //����FirstPartition�㷨���е��ȼ���
    void AlgorithmFirstPartition() {
        //���ƽ���
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= ProcessNum; i++) {
            progressCopy[i] = progress[i];
        }

        //���ƿ��з�����С
        int freePartition[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartition[i] = FreePartition[i];
        }

        //���̷���
        for (int i = 1; i <= ProcessNum; i++) {
            for (int j = 1; j <= PartitionNum; j++) {
                if (freePartition[j] >= progressCopy[i].ProcessNeed) {
                    freePartition[j] -= progressCopy[i].ProcessNeed;
                    progressCopy[i].FirstPartition = j;
                    break;
                }
            }
        }

        Test(progressCopy);

        Print(progressCopy, freePartition);

        NextAlgorithm();
    }

    //����CycleFirstPartition�㷨���е��ȼ���
    void AlgorithmCycleFirstPartitionS() {
        //���ƽ���
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= ProcessNum; i++) {
            progressCopy[i] = progress[i];
        }

        //���ƿ��з�����С
        int freePartition[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartition[i] = FreePartition[i];
        }

        //���̷���
        int i = 1;
        while (i <= ProcessNum) {
            for (int j = 1; j <= PartitionNum; j++) {
                if (freePartition[j] >= progressCopy[i].ProcessNeed) {
                    freePartition[j] -= progressCopy[i].ProcessNeed;
                    progressCopy[i].CycleFirstPartition = j;
                    i++;
                    if (i > ProcessNum) {
                        break;
                    }
                }
            }
            if (i > ProcessNum) {
                break;
            }
        }

        Test(progressCopy);

        Print(progressCopy, freePartition);

        NextAlgorithm();
    }

    //����BestPartition�㷨���е��ȼ���
    void AlgorithmBestPartition() {
        //���ƽ���
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= ProcessNum; i++) {
            progressCopy[i] = progress[i];
        }

        //���ƿ��з�����С
        int freePartition[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartition[i] = FreePartition[i];
        }

        //���̷���
        for (int i = 1; i <= ProcessNum; i++) {
            for (int j = 1; j <= PartitionNum; j++) {
                if (freePartition[AscendingBubbleSort(freePartition, j)] >= progressCopy[i].ProcessNeed) {
                    progressCopy[i].BestPartition = AscendingBubbleSort(freePartition, j);
                    freePartition[AscendingBubbleSort(freePartition, j)] -= progressCopy[i].ProcessNeed;
                    break;
                }
            }
        }

        Test(progressCopy);

        Print(progressCopy, freePartition);

        NextAlgorithm();


    }

    //�����㷨������ð�������㷨��������ʣ���С��С����ð�����򣬷��ظ�index�����ֵ
    int AscendingBubbleSort(const int freePartition[MaxNumber], int index) {
        //���ƿ��з���
        int freePartitionCopy[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartitionCopy[i] = freePartition[i];
        }

        //������ʣ���С��С����ð������
        for (int i = 1; i <= PartitionNum; i++) {
            for (int j = 1; j <= PartitionNum - i; j++) {
                if (freePartitionCopy[j] > freePartitionCopy[j + 1]) {
                    int temp = freePartitionCopy[j];
                    freePartitionCopy[j] = freePartitionCopy[j + 1];
                    freePartitionCopy[j + 1] = temp;
                }
            }
        }

        //���Ҹ���̷���ʱ���Ӧ�Ľ��̺�
        for (int j = 1; j <= PartitionNum; j++) {
            if (freePartition[j] == freePartitionCopy[index]) {
                return j;
            }
        }

        return 0;
    }

    //����WorstPartition�㷨���е��ȼ���
    void AlgorithmWorstPartition() {
        //���ƽ���
        Progress progressCopy[MaxNumber];
        for (int i = 1; i <= ProcessNum; i++) {
            progressCopy[i] = progress[i];
        }

        //���ƿ��з�����С
        int freePartition[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartition[i] = FreePartition[i];
        }

        //���̷���
        for (int i = 1; i <= ProcessNum; i++) {
            for (int j = 1; j <= PartitionNum; j++) {
                if (freePartition[DescendingBubbleSort(freePartition, j)] >= progressCopy[i].ProcessNeed) {
                    progressCopy[i].WorstPartition = DescendingBubbleSort(freePartition, j);
                    freePartition[DescendingBubbleSort(freePartition, j)] -= progressCopy[i].ProcessNeed;
                    break;
                }
            }
        }

        Test(progressCopy);

        Print(progressCopy, freePartition);

        NextAlgorithm();
    }

    //�����㷨������ð�������㷨��������ʣ���С�Ӵ�Сð�����򣬷��ظ�index�����ֵ
    int DescendingBubbleSort(const int freePartition[MaxNumber], int index) {
        //���ƿ��з���
        int freePartitionCopy[MaxNumber];//���з�����С
        for (int i = 1; i <= PartitionNum; i++) {
            freePartitionCopy[i] = freePartition[i];
        }

        //������ʣ���С�Ӵ�Сð������
        for (int i = 1; i <= PartitionNum; i++) {
            for (int j = 1; j <= PartitionNum - i; j++) {
                if (freePartitionCopy[j] < freePartitionCopy[j + 1]) {
                    int temp = freePartitionCopy[j];
                    freePartitionCopy[j] = freePartitionCopy[j + 1];
                    freePartitionCopy[j + 1] = temp;
                }
            }
        }

        //���Ҹ���̷���ʱ���Ӧ�Ľ��̺�
        for (int j = 1; j <= PartitionNum; j++) {
            if (freePartition[j] == freePartitionCopy[index]) {
                return j;
            }
        }

        return 0;
    }

    //��֤��������֤���з����Ƿ��㹻����
    void Test(Progress pg[MaxNumber]) {
        switch (isAlgorithm) {
            case 1:
                for (int i = 1; i <= ProcessNum; i++) {
                    if (pg[i].FirstPartition < 0) {
                        cout << "���з������㱾�㷨����" << endl;
                        exit(0);
                    }
                }
                break;
            case 2:
                for (int i = 1; i <= ProcessNum; i++) {
                    if (pg[i].CycleFirstPartition < 0) {
                        cout << "���з������㱾�㷨����" << endl;
                        exit(0);
                    }
                }
                break;
            case 3:
                for (int i = 1; i <= ProcessNum; i++) {
                    if (pg[i].BestPartition < 0) {
                        cout << "���з������㱾�㷨����" << endl;
                        exit(0);
                    }
                }
                break;
            case 4:
                for (int i = 1; i <= ProcessNum; i++) {
                    if (pg[i].WorstPartition < 0) {
                        cout << "���з������㱾�㷨����" << endl;
                        exit(0);
                    }
                }
                break;
        }
    }

    //ѯ���Ƿ�Ҫ���������㷨
    void NextAlgorithm() {
        cout << endl
             << "�����Ƿ�Ҫ���������㷨�����ǣ������루1-4ֵ�������������������ַ���1-�״���Ӧ�����㷨��FirstPartition����2-ѭ���״���Ӧ�����㷨��CycleFirstPartition����3-�����Ӧ�����㷨��BestPartition����4-���Ӧ�����㷨��WorstPartition������";
        cin >> isAlgorithm;
        if (isAlgorithm != 1 && isAlgorithm != 2 && isAlgorithm != 3 && isAlgorithm != 4) {
            return;
        }
        IsAlgorithm();
    }
};

int main() {
    PartitionAlgorithm partitionAlgorithm{};

    partitionAlgorithm.Input();

    return 0;
}