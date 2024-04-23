#ifndef UNDOTEST_H
#define UNDOTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_undotest.h"

class QStringListModel;
class QListView;
class QUndoView;
class QUndoStack;

class undoTest : public QMainWindow
{
    Q_OBJECT

public:
    undoTest(QWidget *parent = 0);
    ~undoTest();

protected:
    void initModel(void);
    void createActions(void);
    void createMenus(void);
    void createToolBar(void);

private slots:
    void insertString(void);

private:
    Ui::undoTestClass ui;

    QDockWidget* mDockCommand;

    QStringListModel* mListModel;

    QUndoStack* mUndoStack;

    QListView* mListView;
    QUndoView* mUndoView;

    QAction* mExitAction;
    QAction* mUndoAction;
    QAction* mRedoAction;
    QAction* mInsertAction;
};

#endif // UNDOTEST_H
