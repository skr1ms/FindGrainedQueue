#include "Queue.hpp"

// ����� ��� ������� ������ ���� � �������� ������ �� �������� �������
void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    if (pos < 0) {
        throw invalid_argument("Position cannot be negative.");
    }

    // ������� ����� ���� � �������� ���������
    Node* newNode = new Node(value);

    // ��������� ������ � ������ ������ � ������� ��������
    unique_lock<mutex> queueLock(queue_mutex);

    // ���� ������ ���� ��� ������� ������� � 0, ��������� ����� ���� � ������
    if (head == nullptr || pos == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // �������� ����� ������ � ������
    Node* current = head;
    int currentPos = 0;

    // ������������ �� ������ �� �������, �������������� �������
    while (current->next != nullptr && currentPos < pos - 1)
    {
        current = current->next;
        currentPos++;
    }

    // ��������� ������� ���� ��� ����������� �������
    unique_lock<mutex> currentLock(current->node_mutex);

    // ���� ��������� ���� ����������, ��������� ���
    if (current->next != nullptr) {
        unique_lock<mutex> nextLock(current->next->node_mutex);
    }

    // ��������� ����� ���� � �������� ������
    newNode->next = current->next;
    current->next = newNode;
}

// ����� ��� ������ ����������� ������
void FineGrainedQueue::printQueue()
{
    // ��������� ������ � ������ ��� ����������� ������
    lock_guard<mutex> lock(queue_mutex);

    // �������� ����� ������ � ������
    Node* current = head;

    // ������� �������� ���� ����� ������
    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}