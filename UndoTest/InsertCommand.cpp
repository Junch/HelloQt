#include "InsertCommand.h"

#include <QStringListModel>

InsertCommand::InsertCommand(const QModelIndex& theIndex, QStringListModel* theModel)
    : QUndoCommand(("Insert ") + QString::number(theIndex.row()))
    , mIndex(theIndex)
    , mModel(theModel)
{
}

InsertCommand::~InsertCommand()
{
}

void InsertCommand::undo()
{
    mModel->removeRows(mIndex.row(), 1);
}

void InsertCommand::redo()
{
    mModel->insertRows(mIndex.row(), 1);
    mModel->setData(mIndex, QString("Insert string " + QString::number(mIndex.row())));
}
