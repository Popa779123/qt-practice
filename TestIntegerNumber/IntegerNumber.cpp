#include "IntegerNumber.h"
#include <cmath>
#include <stdexcept>
#include <climits>
#include <QDebug>

IntegerNumber::IntegerNumber()
    : m_value(0)
{
    qDebug() << "Default constructor:" << m_value;
}

IntegerNumber::IntegerNumber(int value)
    : m_value(value)
{
    qDebug() << "Param constructor:" << m_value;
}

IntegerNumber::IntegerNumber(const IntegerNumber &other)
    : m_value(other.m_value)
{
    qDebug() << "Copy constructor:" << m_value;
}

IntegerNumber::IntegerNumber(IntegerNumber &&other) noexcept
    : m_value(other.m_value)
{
    other.m_value = 0;
    qDebug() << "Move constructor:" << m_value;
}

IntegerNumber& IntegerNumber::operator=(const IntegerNumber &other)
{
    if (this != &other)
    {
        m_value = other.m_value;
    }
    return *this;
}

IntegerNumber& IntegerNumber::operator=(IntegerNumber &&other) noexcept
{
    if (this != &other)
    {
        m_value = other.m_value;
        other.m_value = 0;
    }
    return *this;
}

IntegerNumber::~IntegerNumber()
{
    qDebug() << "Destructor:" << m_value;
}

int IntegerNumber::getValue() const
{
    return m_value;
}

void IntegerNumber::setValue(int value)
{
    m_value = value;
}

int IntegerNumber::nod(int other) const
{
    int a = qAbs(m_value);
    int b = qAbs(other);

    if (a == 0 && b == 0) return 0;
    if (a == 0) return b;
    if (b == 0) return a;

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int IntegerNumber::nok(int other) const
{
    int a = qAbs(m_value);
    int b = qAbs(other);

    if (a == 0 || b == 0) return 0;

    long long result = static_cast<long long>(a / nod(other)) * b;

    if (result > INT_MAX)
    {
        throw std::overflow_error("NOK overflow");
    }

    return static_cast<int>(result);
}

bool IntegerNumber::isPrime() const
{
    int n = qAbs(m_value);

    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= static_cast<int>(std::sqrt(n)); i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

QVector<int> IntegerNumber::factorize() const
{
    QVector<int> factors;
    int n = qAbs(m_value);

    if (n < 2)

    {

        return factors;
    }
    while (n % 2 == 0)
    {
        factors.append(2);
        n /= 2;
    }

    for (int i = 3; i <= static_cast<int>(std::sqrt(n)); i += 2)
    {
        while (n % i == 0)
        {
            factors.append(i);
            n /= i;
        }
    }

    if (n > 1)
    {
        factors.append(n);
    }

    return factors;
}
