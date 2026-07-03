#include <QtTest>
#include "../IntegerNumber.h"

class TestIntegerNumber : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();


    void testDefaultConstructor();
    void testParamConstructor();
    
    void testNod_normal();
    void testNod_withZero();
    void testNod_negative();
    void testNod_sameNumbers();

    
    void testNok_normal();
    void testNok_withZero();
    void testNok_negative();

    
    void testIsPrime_primes();
    void testIsPrime_notPrimes();
    void testIsPrime_edgeCases();

   
    void testFactorize_simple();
    void testFactorize_prime();
    void testFactorize_powerOfTwo();
    void testFactorize_one();
    void testFactorize_zero();
    void testFactorize_negative();
};

// ─────────────────────────────────────────────
void TestIntegerNumber::initTestCase()
{
    qDebug() << "Starting tests";
}

void TestIntegerNumber::cleanupTestCase()
{
    qDebug() << "Tests ended";
}



void TestIntegerNumber::testDefaultConstructor()
{
    IntegerNumber n;
    QCOMPARE(n.getValue(), 0);
}

void TestIntegerNumber::testParamConstructor()
{
    IntegerNumber a(42);
    QCOMPARE(a.getValue(), 42);

    IntegerNumber b(-7);
    QCOMPARE(b.getValue(), -7);

    IntegerNumber c(0);
    QCOMPARE(c.getValue(), 0);
}


void TestIntegerNumber::testNod_normal()
{
    IntegerNumber n(12);
    QCOMPARE(n.nod(8),  4);
    QCOMPARE(n.nod(18), 6);
    QCOMPARE(n.nod(7),  1);
}

void TestIntegerNumber::testNod_withZero()
{
    IntegerNumber n(5);
    QCOMPARE(n.nod(0), 5);

    IntegerNumber zero(0);
    QCOMPARE(zero.nod(0), 0);
    QCOMPARE(zero.nod(9), 9);
}

void TestIntegerNumber::testNod_negative()
{
    IntegerNumber a(-12);
    QCOMPARE(a.nod(8),   4);
    QCOMPARE(a.nod(-18), 6);
}

void TestIntegerNumber::testNod_sameNumbers()
{
    IntegerNumber n(7);
    QCOMPARE(n.nod(7), 7);
}



void TestIntegerNumber::testNok_normal()
{
    IntegerNumber n(4);
    QCOMPARE(n.nok(6),12);

    QCOMPARE(n.nok(5),  20);
    QCOMPARE(n.nok(4),  4);
}

void TestIntegerNumber::testNok_withZero()
{
    IntegerNumber n(5);
    QCOMPARE(n.nok(0), 0);

    IntegerNumber zero(0);
    QCOMPARE(zero.nok(9), 0);
}

void TestIntegerNumber::testNok_negative()
{
    IntegerNumber n(-4);
    QCOMPARE(n.nok(6),  12);
    QCOMPARE(n.nok(-6), 12);
}



void TestIntegerNumber::testIsPrime_primes()
{

    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 97}) {
        IntegerNumber n(p);
        QVERIFY(n.isPrime());
    }
}

void TestIntegerNumber::testIsPrime_notPrimes()
{

    for (int c : {4, 6, 8, 9, 10, 15, 100, 49})
    {
        IntegerNumber n(c);
        QVERIFY(!n.isPrime());
    }
}

void TestIntegerNumber::testIsPrime_edgeCases()
{
    QVERIFY(!IntegerNumber(0).isPrime());
    QVERIFY(!IntegerNumber(1).isPrime());
    QVERIFY(IntegerNumber(5).isPrime());
    QVERIFY(IntegerNumber(2).isPrime());

}


void TestIntegerNumber::testFactorize_simple()
{
    IntegerNumber n(12);
    QVector<int> expected = {2, 2, 3};
    QCOMPARE(n.factorize(), expected);
}

void TestIntegerNumber::testFactorize_prime()
{
    IntegerNumber n(13);
    QVector<int> expected = {13};
    QCOMPARE(n.factorize(), expected);
}

void TestIntegerNumber::testFactorize_powerOfTwo()
{
    IntegerNumber n(16);
    QVector<int> expected = {2, 2, 2, 2};
    QCOMPARE(n.factorize(), expected);
}

void TestIntegerNumber::testFactorize_one()
{
    IntegerNumber n(1);
    QVERIFY(n.factorize().isEmpty()); 
}

void TestIntegerNumber::testFactorize_zero()
{
    IntegerNumber n(0);
    QVERIFY(n.factorize().isEmpty());
}

void TestIntegerNumber::testFactorize_negative()
{

    IntegerNumber n(-12);
    QVector<int> expected = {2, 2, 3};
    QCOMPARE(n.factorize(), expected);
}


QTEST_APPLESS_MAIN(TestIntegerNumber)
#include "tst_integernumber.moc"
