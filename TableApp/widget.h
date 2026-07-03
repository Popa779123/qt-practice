#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class MyModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onOpenStructure1();
    void onOpenStructure2();
    void onAdd();
    void onRemove();

private:
    Ui::Widget *ui;
    MyModel *m_model;

    void updateFileLabel();
};

#endif
