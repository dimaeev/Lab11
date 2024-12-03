/****************************************************
* Автор: Алексеев Д.К.                              *
* Дата: 03.12.2024                                  *
* Название: Огромные числа                          *
****************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string trimLeadingZeros(string str) {
    while (str.length() > 1 && str[0] == '0') {
        str.erase(0, 1);
    }
    return str;
}

string addBigNumbers(const string& num1, const string& num2) {
    string result = "";
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }

    reverse(result.begin(), result.end());
    return result;
}

string subtractBigNumbers(const string& num1, const string& num2) {
    string result = "";
    int borrow = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result += (digit1 - digit2) + '0';
    }

    reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

string multiplyBigNumbers(const string& num1, const string& num2) {
    int n = num1.size(), m = num2.size();
    vector<int> product(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = product[i + j + 1] + mul;

            product[i + j + 1] = sum % 10;
            product[i + j] += sum / 10;
        }
    }

    string result = "";
    for (int digit : product) {
        result += (digit + '0');
    }

    return trimLeadingZeros(result);
}

int compareBigNumbers(const string& num1, const string& num2) {
    string trimmedNum1 = trimLeadingZeros(num1);
    string trimmedNum2 = trimLeadingZeros(num2);

    if (trimmedNum1.size() != trimmedNum2.size()) {
        return trimmedNum1.size() < trimmedNum2.size() ? -1 : 1;
    }

    return trimmedNum1 < trimmedNum2 ? -1 : (trimmedNum1 > trimmedNum2 ? 1 : 0);
}

string divideBigNumbers(const string& num1, const string& num2) {
    if (num2 == "0") {
        throw invalid_argument("Деление на ноль невозможно");
    }

    string dividend = "";
    string result = "";
    for (char digit : num1) {
        dividend += digit;
        dividend = trimLeadingZeros(dividend);

        int count = 0;
        while (compareBigNumbers(dividend, num2) >= 0) {
            dividend = subtractBigNumbers(dividend, num2);
            count++;
        }
        result += (count + '0');
    }

    return trimLeadingZeros(result);
}

int main() {
    string num1, num2;

    cout << "Введите первое число: ";
    cin >> num1;

    cout << "Введите второе число: ";
    cin >> num2;

    cout << "Сумма: " << addBigNumbers(num1, num2) << endl;
    cout << "Разность: " << subtractBigNumbers(num1, num2) << endl;
    cout << "Произведение: " << multiplyBigNumbers(num1, num2) << endl;
    cout << "Частное: " << divideBigNumbers(num1, num2) << endl;

    int cmp = compareBigNumbers(num1, num2);
    if (cmp == 0)
        cout << "Числа равны." << endl;
    else if (cmp < 0)
        cout << "Первое число меньше второго." << endl;
    else
        cout << "Первое число больше второго." << endl;

    return 0;
}