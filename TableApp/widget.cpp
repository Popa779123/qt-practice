#include "widget.h"
#include "ui_widget.h"
#include "mymodel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_model = new MyModel(this);

    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->openBtn1, &QPushButton::clicked, this, &Widget::onOpenStructure1);
    connect(ui->openBtn2, &QPushButton::clicked, this, &Widget::onOpenStructure2);
    connect(ui->addBtn, &QPushButton::clicked, this, &Widget::onAdd);
    connect(ui->removeBtn, &QPushButton::clicked, this, &Widget::onRemove);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onOpenStructure1()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Structure1"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    m_model->loadStructure1(fileName);

    updateFileLabel();

    QMessageBox::information(this, tr("Loaded"), tr("Structure1 loaded. All changes will be auto-saved."));
}

void Widget::onOpenStructure2()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Structure2"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    m_model->loadStructure2(fileName);

    updateFileLabel();

    QMessageBox::information(this, tr("Loaded"), tr("Structure2 loaded. All changes will be auto-saved."));
}

void Widget::onAdd()
{
    m_model->addRow();
}

void Widget::onRemove()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid())
    {
        QMessageBox::information(this, tr("Info"), tr("Please select a row."));
        return;
    }

    m_model->removeRow(index.row());
}

void Widget::updateFileLabel()
{
    QString filePath = m_model->currentFile();
    if (filePath.isEmpty())
    {
        ui->fileLabel->setText("No file opened");
    }
    else
    {
        ui->fileLabel->setText("Current file: " + filePath);
    }
}
