#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

// Функция умножения больших чисел, представленных строками
string multiply(string x, string y) 
{
    if (x == "0" || y == "0") 
    {
        return "0";
    }

    size_t m = x.size();
    size_t n = y.size();
    vector<int> res(m + n, 0);

    for (int i = m - 1; i >= 0; --i) 
    {
        int carry = 0;
        for (int j = n - 1; j >= 0; --j) 
        {
            int prod = (x[i] - '0') * (y[j] - '0') + carry + res[i + j + 1];
            res[i + j + 1] = prod % 10;
            carry = prod / 10;
        }
        res[i] += carry;
    }

    size_t start = 0;
    while (start < res.size() - 1 && res[start] == 0) 
    {
        ++start;
    }

    string result = "";
    for (size_t i = start; i < res.size(); ++i) 
    {
        result += to_string(res[i]);
    }
    return result;
}

// Функция вычисления факториала большого числа (строки)
string factorial(string n_str) 
{
    if (n_str == "0") 
    {
        return "1";
    }

    string res = "1";
    int n = stoi(n_str);
    for (int i = 1; i <= n; ++i) 
    {
        res = multiply(res, to_string(i));
    }
    return res;
}

// Функция вычисления суперфакториала (n!)!
// Возвращает "ERROR" в случае ошибки
string superfactorial(string n_str) {
    if (n_str.empty() || !all_of(n_str.begin(), n_str.end(), ::isdigit)) 
    {
        return "ERROR: Введённое значение должно быть неотрицательным целым числом.\n";
    }
    
    if (n_str == "0") 
    {
      return "1";
    }
    
    string n_factorial = factorial(n_str);
    
    // дополнительная проверка, если результат факториала не корректен
    if (n_factorial.rfind("ERROR", 0) == 0) 
    {
         return n_factorial;
    }
    
    return factorial(n_factorial);
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Программа для вычисления (n!)!\n";
    while (true) 
    {
        string n_str;
        cout << "Введите неотрицательное целое число n (или 'exit' для выхода): ";
        cin >> n_str;
        if (n_str == "exit") 
        {
            break;
        }
         
        string result = superfactorial(n_str);
        if (result.rfind("ERROR", 0) == 0) 
        {
           cerr << result;
        } 
        else 
        {
            cout << "Результат (" << n_str << "!)! = " << result << "\n";
        }
        cout << "------------------------------\n";
    }
    return 0;
}
