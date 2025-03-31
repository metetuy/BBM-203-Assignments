#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack()
{
    // at first top is -1
    top = -1;
    // fill the stack with -1's
    for (int i = 0; i < MAX_SIZE; i++)
    {
        data[i] = -1;
    }
}

// Adds a province to the top of the stack
void Stack::push(int province)
{
    if (top + 1 < MAX_SIZE) // isFull
    {
        data[++top] = province;
    }
    else
    {
        std::cerr << "Error: Stack Overflow" << std::endl;
    }
}

// Removes and returns the top province from the stack
int Stack::pop()
{
    if (isEmpty())
    {
        return -1;
    }
    else
    {
        int x = data[top];
        data[top] = -1;
        top--;
        return x;
    }
}

// Returns the top province without removing it
int Stack::peek() const
{
    if (isEmpty())
    {
        return -1;
    }
    else
    {
        return data[top];
    }
}

// Checks if the stack is empty
bool Stack::isEmpty() const
{
    return top == -1;
}

// Function to get the current size of the stack
int Stack::getSize() const
{
    return top + 1;
}
