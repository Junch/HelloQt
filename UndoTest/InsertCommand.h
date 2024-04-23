
#ifndef _INSERTCOMMAND_H_
#define _INSERTCOMMAND_H_

#include <QUndoCommand>
#include <QModelIndex>

class QStringListModel;

class InsertCommand : public QUndoCommand
{
public:
    InsertCommand(const QModelIndex& theIndex, QStringListModel* theModel);
    ~InsertCommand();

public:
    virtual void undo();
    virtual void redo();

private:
    QModelIndex mIndex;
    QStringListModel* mModel;
};

#endif // _INSERTCOMMAND_H_