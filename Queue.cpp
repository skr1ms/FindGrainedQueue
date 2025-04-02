#include "Queue.hpp"

// Метод для вставки нового узла в середину списка на заданную позицию
void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    if (pos < 0) {
        throw invalid_argument("Position cannot be negative.");
    }

    // Создаем новый узел с заданным значением
    Node* newNode = new Node(value);

    // Блокируем доступ к голове списка с помощью мьютекса
    unique_lock<mutex> queueLock(queue_mutex);

    // Если список пуст или позиция вставки — 0, вставляем новый узел в начало
    if (head == nullptr || pos == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Начинаем обход списка с головы
    Node* current = head;
    int currentPos = 0;

    // Перемещаемся по списку до позиции, предшествующей целевой
    while (current->next != nullptr && currentPos < pos - 1)
    {
        current = current->next;
        currentPos++;
    }

    // Блокируем текущий узел для безопасного доступа
    unique_lock<mutex> currentLock(current->node_mutex);

    // Если следующий узел существует, блокируем его
    if (current->next != nullptr) {
        unique_lock<mutex> nextLock(current->next->node_mutex);
    }

    // Вставляем новый узел в середину списка
    newNode->next = current->next;
    current->next = newNode;
}

// Метод для вывода содержимого списка
void FineGrainedQueue::printQueue()
{
    // Блокируем доступ к списку для безопасного вывода
    lock_guard<mutex> lock(queue_mutex);

    // Начинаем обход списка с головы
    Node* current = head;

    // Выводим значения всех узлов списка
    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}