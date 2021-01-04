#define CATCH_CONFIG_RUNNER
#include <QCoreApplication>
#include "catch.hpp" // include after defining CATCH_CONFIG_RUNNER
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const int res = Catch::Session().run(argc, argv);
    return (res < 0xff ? res : 0xff);
}
