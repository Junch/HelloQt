#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QColor>

struct CellInfo
{
    QString content;        //显示的内容
    QString toolTip;        //tooltips
    QColor bgColor;         //背景色
};

Q_DECLARE_METATYPE(CellInfo*)   //注册元数据类型

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = nullptr);
    void setInitData(QList<CellInfo*>& data);
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex& index, const QVariant &value, int role=Qt::EditRole) override;

private:
    int m_columnNum;                        //列大小
    int m_rowNum;                           //行大小
    QList<CellInfo*> m_data;                //数据
};

#endif // MYTABLEMODEL_H
