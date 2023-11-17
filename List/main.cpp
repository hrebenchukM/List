#include <iostream>
using namespace std;

template <typename T>
struct Elem
{
    T data;       // данные
    Elem* next, * prev;
};

template <typename T>
class List
{
private:
    Elem<T>* Head, * Tail;  // Голова, хвост
    int Count;              // Количество элементов

public:
    // Конструктор
    List();
    // Конструктор копирования
    List(const List&);
    // Деструктор
    ~List();

    // Получить количество
    int GetCount();
    // Получить элемент списка
    Elem<T>* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(T n);

    // Добавление в начало списка
    void AddHead(T n);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);

    List<T>& operator = (const List&);
    // сложение двух списков (дописывание)
    List<T> operator + (const List&);

    // сравнение по элементам
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // переворачивание списка
    List<T> operator - ();
};

template <typename T>
List<T>::List()
{
    Head = Tail = nullptr;
    Count = 0;
}

template <typename T>
List<T>::List(const List& L)
{
    Head = Tail = nullptr;
    Count = 0;

    Elem<T>* temp = L.Head;

    while (temp != nullptr)
    {
        AddTail(temp->data);
        temp = temp->next;
    }
}

template <typename T>
List<T>::~List()
{
    DelAll();
}

template <typename T>
void List<T>::AddHead(T n)
{
    Elem<T>* temp = new Elem<T>;

    temp->prev = nullptr;
    temp->data = n;
    temp->next = Head;

    if (Head != nullptr)
        Head->prev = temp;

    if (Count == 0)
        Head = Tail = temp;
    else
        Head = temp;

    Count++;
}

template <typename T>
void List<T>::AddTail(T n)
{
    Elem<T>* temp = new Elem<T>;

    temp->next = nullptr;
    temp->data = n;
    temp->prev = Tail;

    if (Tail != nullptr)
        Tail->next = temp;

    if (Count == 0)
        Head = Tail = temp;
    else
        Tail = temp;

    Count++;
}

template <typename T>
void List<T>::Insert(int pos)
{
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    if (pos < 1 || pos > Count + 1)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    if (pos == Count + 1)
    {
        T data;
        cout << "Input new data: ";
        cin >> data;
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        T data;
        cout << "Input new data: ";
        cin >> data;
        AddHead(data);
        return;
    }

    int i = 1;
    Elem<T>* Ins = Head;

    while (i < pos)
    {
        Ins = Ins->next;
        i++;
    }

    Elem<T>* PrevIns = Ins->prev;
    Elem<T>* temp = new Elem<T>;

    cout << "Input new data: ";
    cin >> temp->data;

    if (PrevIns != nullptr && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

template <typename T>
void List<T>::Del(int pos)
{
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    int i = 1;
    Elem<T>* Del = Head;

    while (i < pos)
    {
        Del = Del->next;
        i++;
    }

    Elem<T>* PrevDel = Del->prev;
    Elem<T>* AfterDel = Del->next;

    if (PrevDel != nullptr && Count != 1)
        PrevDel->next = AfterDel;

    if (AfterDel != nullptr && Count != 1)
        AfterDel->prev = PrevDel;

    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    delete Del;

    Count--;
}

template <typename T>
void List<T>::Print(int pos)
{
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<T>* temp;

    if (pos <= Count / 2)
    {
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
    }
    else
    {
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            temp = temp->prev;
            i++;
        }
    }

    cout << pos << " element: ";
    cout << temp->data << endl;
}

template <typename T>
void List<T>::Print()
{
    if (Count != 0)
    {
        Elem<T>* temp = Head;
        cout << "( ";
        while (temp->next != nullptr)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}

template <typename T>
void List<T>::DelAll()
{
    while (Count != 0)
        Del(1);
}

template <typename T>
int List<T>::GetCount()
{
    return Count;
}

template <typename T>
Elem<T>* List<T>::GetElem(int pos)
{
    Elem<T>* temp = Head;

    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return nullptr;
    }

    int i = 1;
    while (i < pos && temp != nullptr)
    {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr)
        return nullptr;
    else
        return temp;
}

template <typename T>
List<T>& List<T>::operator = (const List& L)
{
    if (this == &L)
        return *this;

    this->~List();

    Elem<T>* temp = L.Head;

    while (temp != nullptr)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}

template <typename T>
List<T> List<T>::operator + (const List& L)
{
    List<T> Result(*this);

    Elem<T>* temp = L.Head;

    while (temp != nullptr)
    {
        Result.AddTail(temp->data);
        temp = temp->next;
    }

    return Result;
}

template <typename T>
bool List<T>::operator == (const List& L)
{
    if (Count != L.Count)
        return false;

    Elem<T>* t1 = Head;
    Elem<T>* t2 = L.Head;

    while (t1 != nullptr)
    {
        if (t1->data != t2->data)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }

    return true;
}

template <typename T>
bool List<T>::operator != (const List& L)
{
    return !(*this == L);
}

template <typename T>
bool List<T>::operator >= (const List& L)
{
    if (Count > L.Count)
        return true;
    if (*this == L)
        return true;

    return false;
}

template <typename T>
bool List<T>::operator <= (const List& L)
{
    if (Count < L.Count)
        return true;
    if (*this == L)
        return true;

    return false;
}

template <typename T>
bool List<T>::operator > (const List& L)
{
    if (Count > L.Count)
        return true;

    return false;
}

template <typename T>
bool List<T>::operator < (const List& L)
{
    if (Count < L.Count)
        return true;

    return false;
}

template <typename T>
List<T> List<T>::operator - ()
{
    List<T> Result;

    Elem<T>* temp = Head;
    while (temp != nullptr)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }

    return Result;
}

int main()
{
    List<int> L;

    const int n = 10;
    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.AddHead(a[i]);
        else
            L.AddTail(a[i]);

    cout << "List L:\n";
    L.Print();

    cout << endl;

    L.Insert();
    cout << "List L:\n";
    L.Print();

    L.Print(2);
    L.Print(8);

    List<int> T;
    T = L;
    cout << "List T:\n";
    T.Print();

    List<int> Sum = -L + T;
    cout << "List Sum:\n";
    Sum.Print();

    return 0;
}
