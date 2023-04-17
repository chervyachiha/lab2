#include <iostream>
#include <cstring>

struct String
{
private:
    size_t m_size;
    char* m_str = nullptr;
public:
    //конструктор по умолчанию (базовый конструктор)
    String(){
        m_size = 0;
        m_str = new char[0];
    };

    //неявное преобразование из int в char
    String(char c, size_t size) : m_size(size++), m_str(new char[size])
    {
       std::fill(m_str, m_str+m_size,c);
       m_str[m_size]=0;
    }

    String(int c, size_t size) = delete;

    //список инициализации членов класса
    String(char* str) : m_size(strlen(str)), m_str(new char[m_size+1])
    {
        std::copy(str, str+m_size, m_str);
        m_str[m_size]=0;
    }

    //конструктор копирования+делегирующий конструктор
    String(const String& other) : String(other.m_str) {}

    //оператор присваиваивания копирования
    String& operator = (String temp)
    {
        //идиома copy-and-swap
        std::swap(m_size,temp.m_size);
        std::swap(m_str, temp.m_str);
        return *this;
    }

    //деструктор
    ~String()
    {
        if(m_str!=nullptr)
             delete[] m_str;
    }

    //Оператор +=
    String& operator+=(const String& other)
    {
        char* mas = new char[m_size];
        int massize = m_size;
        for (int i = 0; i < m_size; i++)
            mas[i] = m_str[i];
        delete[] m_str;
        m_size = m_size + other.m_size;
        m_str = new char[m_size+1];
        int index;
        for (int i = 0; i < massize; i++)
        {
            m_str[i] = mas[i];
            index = i + 1;
        }
        for (int i = 0; i < other.m_size; i++)
            m_str[index + i] = other.m_str[i];
        delete[] mas;
        return *this;
    }
    //Оператор [] – чтение и изменение элемента
    char& operator[](int index)
    {
        return m_str[index];
    }
    //оператор <
    bool operator<(const String& other)
    {
        return (m_size < other.m_size);
    }
    // оператор >
    bool operator>(const String& other)
    {
        return (m_size > other.m_size);
    }
    // оператор ==
    bool operator==(const String& other)
    {
        return (m_size == other.m_size);
    }



    //Метод find – поиск первого вхождения символа в строку слева
    int Find(char a)
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_str[i] == a)
                return i;
        }
        return -1;
    }
    // Метод length – длина строки
    int Length()
    {
        return m_size;
    }
    // Метод c_str – получить массив char
    char& c_str()
    {
        return *m_str;
    }
    // Метод at для получения доступа (чтение и изменение) к элементу
    // строки с проверкой на выход за пределы строки
    char& at(int index)
    {
        if(0<=index && index < strlen(m_str))
            return m_str[index];
    }
    void Print() const
    {
        for(int i=1; i<m_size;i++)
            std::cout<<m_str[i];
    }
    friend std::ostream& operator<<(std::ostream& out, String& s);
    friend std::istream& operator>>(std::istream& in, String& s);
};
//оператор +
String operator+(const String& z1, const String& z2)
{
    String temp =z1;
    temp+=z2;
    return temp;
}
// Оператор вывода в поток
std::ostream& operator<<(std::ostream& out, String& s)
{
    for (int i = 0; i < s.m_size; i++)
        out << s.m_str[i];
    out << std::endl;
    return out;
}
//Оператор ввода в поток
std::istream& operator>>(std::istream& in, String& s)
{
    char a;
    while (in.get(a))
    {
        if (a == ' ' || a == '\n')
            break;
        char* mas = new char[s.m_size];
        for (int i = 0; i < s.m_size; i++)
            mas[i] = s.m_str[i];
        delete[] s.m_str;
        s.m_size++;
        s.m_str = new char[s.m_size];
        for (int i = 0; i < s.m_size-1; i++)
            s.m_str[i] = mas[i];
        s.m_str[s.m_size - 1] = a;
        delete[] mas;
    }
    return in;
}

int main()
{
    String s1('a', 10);
    String s2;
    std::cin >> s2;
    String s3 = s1+s2;
    std::cout << s3;
}
