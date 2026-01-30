#include"FirstPerson.hpp"
class GameMaster;

class Map : public QWidget {

private:
    GameMaster *game;

public:

    explicit Map(QWidget *parent= nullptr);

protected:


    void paintEvent(QPaintEvent *event) override;
};
