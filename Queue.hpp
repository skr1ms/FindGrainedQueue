#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <stdexcept> 

using namespace std;

// ��������� Node ������������ ���� � ��������� ������.
struct Node
{
    int value;         
    Node* next;        
    // ������� ��� ������������� ������� � ����
    mutex node_mutex;  

    // ����������� ����
    Node(int val) : value(val), next(nullptr) {}
};

// ����� FineGrainedQueue ��������� ��������� ������ � ������ �����������.
class FineGrainedQueue
{
private:
    Node* head;        
    // ������� ��� ������������� ������� � ������ ������
    mutex queue_mutex; 

public:
    // �����������, ���������������� ������ � ����� �����
    FineGrainedQueue() : head(nullptr) {}

    // ���������� ��� ������������ ������
    ~FineGrainedQueue() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // ����� ��� ������� ������ ���� � �������� ������ �� �������� �������
    void insertIntoMiddle(int value, int pos);

    // ����� ��� ������ ����������� ������
    void printQueue();
};