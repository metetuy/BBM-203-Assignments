#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue()
{
    front = -1;
    rear = -1;
    for (int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        data[i] = -1;
    }
}

// Adds a province to the end of the queue
void Queue::enqueue(int province)
{
    // If queue full
    if ((rear + 1) % MAX_QUEUE_SIZE == front)
    {
        std::cout << "Queue Full" << std::endl;
        return;
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == -1)
    {
        front++;
    }
    // Add the province
    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue()
{
    if (isEmpty())
    {
        std::cout << "Queue Empty" << std::endl;
        return -1;
    }
    if (front == rear)
    {
        int temp = data[front];
        front = rear = -1;
        return temp;
    }
    int x = data[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    return x;
}

// Returns the front province without removing it
int Queue::peek() const
{
    if (isEmpty())
    {
        return -1;
    }
    else
    {
        return data[front];
    }
}

// Checks if the queue is empty
bool Queue::isEmpty() const
{
    if (front == -1 && rear == -1)
    {

        return true;
    }
    else
    {
        return false;
    }
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province)
{
    // If the queue is full
    if ((rear + 1) % MAX_QUEUE_SIZE == front)
    {
        std::cout << "Queue full" << std::endl;
        return;
    }

    // First province insert
    if (isEmpty())
    {
        front = 0;
        rear = 0;
        data[rear] = province;
        return;
    }

    int i = rear;
    while (true)
    {
        int next = (i + 1) % MAX_QUEUE_SIZE;
        data[next] = data[i];
        if (i == front)
        {
            break;
        }
        // Move backward in the circular array
        i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    }

    data[front] = province;

    rear = (rear + 1) % MAX_QUEUE_SIZE;
}
