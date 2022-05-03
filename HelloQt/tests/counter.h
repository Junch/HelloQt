#include <QObject>
#include <QDebug>

class Counter : public QObject
{
    /*
     * All classes that contain signals or slots must mention Q_OBJECT
     * at the top of their declaration.
     * They must also derive (directly or indirectly) from QObject.
     */
    Q_OBJECT

public:
    Counter(QObject *parent = 0) : QObject(parent)
    {
        m_value = 0;

        /*
         * The most important line: connect the signal to the slot.
         */
        connect(this, &Counter::valueChanged, this, &Counter::printValue);
    }

    void setValue(int value)
    {
        if (value != m_value)
        {
            m_value = value;
            /*
             * The emit line emits the signal valueChanged() from
             * the object, with the new value as argument.
             */
            emit valueChanged(m_value);
        }
    }

public slots:
    void printValue(int value)
    {
        qDebug() << "new value: " << value;
    }

signals:
    void valueChanged(int newValue);

private:
    int m_value;
};
