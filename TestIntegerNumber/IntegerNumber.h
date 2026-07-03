
#ifndef INTEGERNUMBER_H
#define INTEGERNUMBER_H

#include <QVector>
#include <QString>

class IntegerNumber
{
public:

    IntegerNumber();
    IntegerNumber(int value);
    IntegerNumber(const IntegerNumber &other);
    IntegerNumber(IntegerNumber &&other) noexcept;
    IntegerNumber& operator=(const IntegerNumber &other);
    IntegerNumber& operator=(IntegerNumber &&other) noexcept;
    ~IntegerNumber();
    int getValue() const;
    void setValue(int value);
    int nod(int other) const;
    int nok(int other) const;
    bool isPrime() const;
    QVector<int> factorize() const;



private:
    int m_value;
};
#endif // INTEGERNUMBER_H
