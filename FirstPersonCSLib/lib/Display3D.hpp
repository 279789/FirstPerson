#include"FirstPerson.hpp"
class GameMaster;


class Display3D : public QWidget {

private:
    GameMaster *game;

public:

    explicit Display3D(QWidget *parent = nullptr);

protected:


// Verstehen!!!


    void paintEvent(QPaintEvent *event) override;


};
