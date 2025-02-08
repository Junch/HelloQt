#include "catch.hpp"
#include <QString>
#include <QDebug>

TEST_CASE("QString", "[QString]")
{
    SECTION("sprintf", "")
    {
        QString str;
        str.asprintf("%s %.1f%%", "perfect competition", 100.0);
        CHECK(str == QString("perfect competition 100.0%"));
        qDebug() << str;
    }
}
