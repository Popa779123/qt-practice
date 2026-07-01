#include "mymodel.h"
#include <QFile>
#include <QTextStream>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent),
    currentMode(Structure1Mode)
{
}

void MyModel::setMode(Mode m)
{
    beginResetModel();
    currentMode = m;
    endResetModel();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (currentMode == Structure1Mode)
        return data1.size();
    else
        return data2.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (currentMode == Structure1Mode)
        {
            switch (section)
            {
            case 0: return "Name";
            case 1: return "Telephon1";
            case 2: return "Telephon2";
            }
        }
        else
        {
            switch (section)
            {
            case 0: return "Name";
            case 1: return "Address";
            case 2: return "Telephon1";
            }
        }
    }

    return section + 1;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if (index.row() < 0)
        return QVariant();

    if (currentMode == Structure1Mode)
    {
        if (index.row() >= data1.size())
            return QVariant();

        const Structure1 &item = data1.getData()[index.row()];
        switch (index.column())
        {
        case 0: return item.name;
        case 1: return item.tel1;
        case 2: return item.tel2;
        }
    }
    else
    {
        if (index.row() >= data2.size())
            return QVariant();

        const Structure2 &item = data2.getData()[index.row()];
        switch (index.column())
        {
        case 0: return item.name;
        case 1: return item.address;
        case 2: return item.tel1;
        }
    }

    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    if (index.row() < 0)
        return false;

    if (currentMode == Structure1Mode)
    {
        if (index.row() >= data1.size())
            return false;

        Structure1 &item = data1.getData()[index.row()];
        switch (index.column())
        {
        case 0: item.name = value.toString(); break;
        case 1: item.tel1 = value.toLongLong(); break;
        case 2: item.tel2 = value.toLongLong(); break;
        default: return false;
        }
    }
    else
    {
        if (index.row() >= data2.size())
            return false;

        Structure2 &item = data2.getData()[index.row()];
        switch (index.column())
        {
        case 0: item.name = value.toString(); break;
        case 1: item.address = value.toString(); break;
        case 2: item.tel1 = value.toLongLong(); break;
        default: return false;
        }
    }

    emit dataChanged(index, index);

    autoSave();

    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void MyModel::loadStructure1(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream ts(&file);

    beginResetModel();
    currentMode = Structure1Mode;
    ts >> data1;
    endResetModel();

    file.close();

    m_currentFilePath = fileName;
}

void MyModel::loadStructure2(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream ts(&file);

    beginResetModel();
    currentMode = Structure2Mode;
    ts >> data2;
    endResetModel();

    file.close();

    m_currentFilePath = fileName;
}

void MyModel::addRow()
{
    int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);

    if (currentMode == Structure1Mode)
    {
        Structure1 item;
        item.name = "";
        item.tel1 = 0;
        item.tel2 = 0;
        data1.getData().push_back(item);
    }
    else
    {
        Structure2 item;
        item.name = "";
        item.address = "";
        item.tel1 = 0;
        data2.getData().push_back(item);
    }

    endInsertRows();

    autoSave();
}

void MyModel::removeRow(int row)
{
    if (row < 0 || row >= rowCount())
        return;

    beginRemoveRows(QModelIndex(), row, row);

    if (currentMode == Structure1Mode)
        data1.getData().removeAt(row);
    else
        data2.getData().removeAt(row);

    endRemoveRows();

    autoSave();
}

QString MyModel::currentFile() const
{
    return m_currentFilePath;
}

void MyModel::autoSave()
{
    if (m_currentFilePath.isEmpty())
        return;

    QFile file(m_currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream ts(&file);

    if (currentMode == Structure1Mode)
        ts << data1;
    else
        ts << data2;

    file.close();
}
