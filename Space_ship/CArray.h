#pragma once
#include <iostream>
#include <new>

using namespace std;

template <typename T>
class CArray
{
public:
    // конструктор по умолчанию
    CArray()
    {
        count = 0;
    }

    // конструктор копирования - обязателен
    CArray(const CArray& _A)
    {
        try {
            // попытка выделить память для массива типа T
            A = new T[_A.count];
            count = _A.count;

            for (int i = 0; i < count; i++)
                A[i] = _A.A[i];
        }
        catch (bad_alloc e)
        {
            count = 0;
            cout << "Error. Cannot allocate memory." << endl;
            cout << e.what() << endl;
        }
    }

    // оператор копирования
    CArray& operator=(const CArray& _A)
    {
        // освободить предварительно выделенную память
        if (count > 0)
            delete[] A;

        // выделить память по новому
        try {
            A = new T[_A.count];
            count = _A.count;

            for (int i = 0; i < count; i++)
                A[i] = _A.A[i];
        }
        catch (bad_alloc e)
        {
            count = 0;
            cout << "Error. Cannot allocate memory." << endl;
            cout << e.what() << endl;
        }
        return *this;
    }

    // деструктор
    ~CArray()
    {
        // освободить предварительно выделенную память
        if (count > 0)
            delete[] A;
    }

    // добавить элемент в конец массива
    void push_back(T value)
    {
        T* A2; // дополнительный указатель на массив

        // попытка выделить память
        try {
            A2 = new T[count + 1];

            // если память выделена, то увеличить на 1 число элементов
            count++;

            // скопировать массив A в массив A2
            for (int i = 0; i < count - 1; i++)
                A2[i] = A[i];

            // добавить элемент value
            A2[count - 1] = value;

            // освободить память, выделенную под массив A
            if ((count - 1) > 0)
                delete[] A;

            // перенаправить указатель A на массив A2
            A = A2;
        }
        catch (bad_alloc e)
        {
            cout << "Error. Cannot allocate memory." << endl;
            cout << e.what() << endl;
        }
    }

    // метод, который виводит массив A - нужен для тестирования
    void print()
    {
        cout << "Array A: " << endl;

        if (!count)
        {
            cout << "Array is empty." << endl;
            return;
        }

        for (int i = 0; i < count; i++)
            cout << A[i] << " ";
        cout << endl;
    }

    // добавить элемент в массив по заданному индексу
    void insert(int _index, const T& _value)
    {
        // проверка на корректность индекса
        if (!CheckIndex(_index))
        {
            cout << "Error. Bad index. ";
            return;
        }

        T* A2;
        A2 = Alloc(count + 1); // попытка выделить память
        if (A2 == nullptr)
        {
            cout << "Error. Method insert(). Cannot allocate memory." << endl;
            return;
        }

        // копирование A в A2 до позиции _index
        for (int i = 0; i < _index; i++)
            A2[i] = A[i];

        // вставка в позиции _index
        A2[_index] = _value;

        // копирование A в A2 после позиции _index
        for (int i = _index + 1; i < count + 1; i++)
            A2[i] = A[i - 1];

        // освободить предварительно выделенную пам'ять для массива A
        if (count > 1)
            delete[] A;

        count++; // увеличить количество элементов массива на 1

        // перенаправить указатель A на массив A2
        A = A2;
    }

    // метод erase() - удаляет элемент из массива по заданному индексу _index
    void erase(int _index)
    {
        // проверка, корректен ли индекс
        if (!CheckIndex(_index))
        {
            cout << "Bad index." << endl;
            return;
        }

        // цикл удаления из массива элемента в позиции _index
        for (int i = _index; i < count - 1; i++)
            A[i] = A[i + 1];

        count--; // уменьшить количество элементов массива на 1

        // перераспределить память
        T* A2 = Alloc(count); // выделить память по новому

        // скопировать A в A2
        for (int i = 0; i < count; i++)
            A2[i] = A[i];

        // освободить память, выделенную для массива A
        if (count > 0)
            delete[] A;

        // перенаправить указатель A на A2
        A = A2;
    }

    // метод, возвращающий размер массива
    int size()
    {
        return count;
    }

    // метод, очищающий массив
    void clear()
    {
        if (count > 0)
        {
            delete[] A;
            count = 0;
        }
    }

    // операторная функция operator[], перегружает оператор индексирования массива
    T &operator[](int _index)
    {
        if (CheckIndex(_index))
            return A[_index];
        /*else
        {
            T value = 0;
            cout << "Bad index." << endl;
            return value;
        }*/
    }

protected:
    T* A; // массив данных
    int count; // количество элементов в массиве

    // внутренний метод, который проверяет, есть ли значение индекса в допустимых пределах
    // возвращает true, если индекс _index корректен
    bool CheckIndex(int _index)
    {
        if ((_index < 0) || (_index >= count))
            return false;
        return true;
    }

    // метод, выделяющий память для массива типа T,
    // метод возвращает указатель на выделеный массив
    T* Alloc(int _count)
    {
        T* A2 = nullptr;

        try {
            A2 = new T[_count];
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
            return nullptr;
        }
        return A2; // вернуть указатель на выделенный фрагмент
    }
};