/*
Класс FineGrainedQueue:

Реализует связанный список с тонкой блокировкой (fine-grained locking). Это означает, что блокировка применяется только к тем узлам, которые непосредственно участвуют в операции, что повышает производительность в многопоточной среде.

Метод insertIntoMiddle:

Вставляет новый узел в список на заданную позицию.Использует мьютексы для блокировки узлов, чтобы избежать гонок данных (race conditions) при многопоточной вставке.

Метод printQueue:

Выводит значения всех узлов списка.Использует мьютекс для блокировки доступа к списку во время вывода.
*/

#include "Queue.hpp"

auto main() -> int
{
    // Создаем очередь с тонкой блокировкой
    FineGrainedQueue fineGrainedQueue;

    // Создаем несколько потоков для вставки элементов в список
    thread th1(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 1, 0);
    thread th2(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 2, 1);
    thread th3(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 3, 2);
    thread th4(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 4, 3);
    thread th5(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 5, 3);
    thread th6(&FineGrainedQueue::insertIntoMiddle, &fineGrainedQueue, 6, 3);

    // Ожидаем завершения всех потоков
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();

    // Выводим содержимое списка
    fineGrainedQueue.printQueue();

    return 0;
}