#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <stdexcept> 

using namespace std;

// Структура Node представляет узел в связанном списке.
struct Node
{
    int value;         
    Node* next;        
    // Мьютекс для синхронизации доступа к узлу
    mutex node_mutex;  

    // Конструктор узла
    Node(int val) : value(val), next(nullptr) {}
};

// Класс FineGrainedQueue реализует связанный список с тонкой блокировкой.
class FineGrainedQueue
{
private:
    Node* head;        
    // Мьютекс для синхронизации доступа к голове списка
    mutex queue_mutex; 

public:
    // Конструктор, инициализирующий список с одним узлом
    FineGrainedQueue() : head(nullptr) {}

    // Деструктор для освобождения памяти
    ~FineGrainedQueue() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Метод для вставки нового узла в середину списка на заданную позицию
    void insertIntoMiddle(int value, int pos);

    // Метод для вывода содержимого списка
    void printQueue();
};