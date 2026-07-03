#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include "datatypes.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Mode {
        Structure1Mode,
        Structure2Mode
    };

    explicit MyModel(QObject *parent = nullptr);

    void setMode(Mode m);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void loadStructure1(const QString &fileName);
    void loadStructure2(const QString &fileName);

    void addRow();
    void removeRow(int row);

    QString currentFile() const;

private:
    Mode currentMode;

    TemplateContainer<Structure1> data1;
    TemplateContainer<Structure2> data2;

    QString m_currentFilePath;

    void autoSave();
};

#endif
