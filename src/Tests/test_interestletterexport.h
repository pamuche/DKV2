#ifndef TEST_INTERESTLETTEREXPORT_H
#define TEST_INTERESTLETTEREXPORT_H

#include <QtTest/QtTest>

class test_interestletterexport : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase(){};
    void cleanupTestCase(){};
    void init(){};
    void cleanup(){};

    void test_zinsbuchungen_template_renders_yearly_interest();
};

#endif // TEST_INTERESTLETTEREXPORT_H
