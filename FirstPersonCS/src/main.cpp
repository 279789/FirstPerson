#include"GameMaster.hpp"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameMaster window;
    window.show();

    return app.exec();
}
