#ifndef DATATYPES_H
#define DATATYPES_H

#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <algorithm>

struct Structure1 {
    QString name;
    long long tel1;
    long long tel2;

    friend QDataStream &operator<<(QDataStream &out, const Structure1 &s) {
        return out << s.name << s.tel1 << s.tel2;
    }
    friend QDataStream &operator>>(QDataStream &in, Structure1 &s) {
        return in >> s.name >> s.tel1 >> s.tel2;
    }
    friend QTextStream &operator<<(QTextStream &out, const Structure1 &s) {
        return out << s.name << " " << s.tel1 << " " << s.tel2;
    }
    friend QTextStream &operator>>(QTextStream &in, Structure1 &s) {
        return in >> s.name >> s.tel1 >> s.tel2;
    }
};

struct Structure2 {
    QString name;
    QString address;
    long long tel1;

    friend QDataStream &operator<<(QDataStream &out, const Structure2 &s) {
        return out << s.name << s.address << s.tel1;
    }
    friend QDataStream &operator>>(QDataStream &in, Structure2 &s) {
        return in >> s.name >> s.address >> s.tel1;
    }
    friend QTextStream &operator<<(QTextStream &out, const Structure2 &s) {
        return out << s.name << " " << s.address << " " << s.tel1;
    }
    friend QTextStream &operator>>(QTextStream &in, Structure2 &s) {
        return in >> s.name >> s.address >> s.tel1;
    }
};

template <typename T>
class TemplateContainer
{
private:
    QVector<T> data;

public:
    const QVector<T>& getData() const { return data; }
    QVector<T>& getData() { return data; }

    int size() const { return data.size(); }
    bool isEmpty() const { return data.isEmpty(); }

    friend QDataStream &operator<<(QDataStream &out, const TemplateContainer<T> &c) {
        for (const auto& item : c.data) out << item;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, TemplateContainer<T> &c) {
        c.data.clear();
        while (!in.atEnd()) {
            T item;
            in >> item;
            if (in.status() != QDataStream::Ok) break;
            c.data.push_back(item);
        }
        return in;
    }

    friend QTextStream &operator<<(QTextStream &out, const TemplateContainer<T> &c) {
        for (const auto& item : c.data) out << item << Qt::endl;
        return out;
    }

    friend QTextStream &operator>>(QTextStream &in, TemplateContainer<T> &c) {
        c.data.clear();
        while (!in.atEnd()) {
            T item;
            in >> item;
            if (in.status() != QTextStream::Ok) break;
            c.data.push_back(item);
        }
        return in;
    }

    void sortByName() {
        std::sort(data.begin(), data.end(), [](const T& a, const T& b) {
            return a.name < b.name;
        });
    }

    void sortByTel1() {
        std::sort(data.begin(), data.end(), [](const T& a, const T& b) {
            return a.tel1 < b.tel1;
        });
    }

    QVector<T> binarySearchByName(const QString& targetName) {
        sortByName();
        QVector<T> results;

        auto lower = std::lower_bound(data.begin(), data.end(), targetName,
                                      [](const T& a, const QString& val) {
                                          return a.name < val;
                                      });

        auto upper = std::upper_bound(data.begin(), data.end(), targetName,
                                      [](const QString& val, const T& a) {
                                          return val < a.name;
                                      });

        for (auto it = lower; it != upper; ++it)
            results.push_back(*it);

        return results;
    }
};

#endif
