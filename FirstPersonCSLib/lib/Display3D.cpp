#include"Display3D.hpp"
#include"GameMaster.hpp"

Display3D::Display3D(QWidget *parent) : QWidget(parent) {
    game = (GameMaster*)parent;

    setMinimumWidth(300); //optional

}

void Display3D::paintEvent(QPaintEvent *event) {
    QPainter painter(this);


    float FieldOfView = 60 * 2 * M_PI / 360; //60deg in Rad for fov

    //This is The Ankatete of the FieldofView/2 Triangle.
    //Results in our Distance where we want to draw.

    float DisplayDistance = (static_cast<float>(width())/2) / std::tan(FieldOfView / 2);
    float AngelPerPixel = FieldOfView / static_cast<float>(width());

    float StartAngel = FieldOfView/2 ;


    // drawing seeling
    painter.fillRect(0, 0, width(), height() / 2, QColor(224, 224, 224));

    //drawing floor
    painter.fillRect(0, height() / 2, width(), height(), QColor(102, 51, 0));

    for(int x = 0; x < width() ; ++x) {

        float RelativeAngle = StartAngel -x * AngelPerPixel;

        dda CurrentRay = game->calculateWallHit(RelativeAngle);

        float DisplayAngel = RelativeAngle - game->player.getDirectionAngle();


        // Calculating Wallheight based on Raylenth and DisplayDistance (Fiewfield Factor)
        int WallHeight = static_cast<int>((1 / CurrentRay.Raylength3D) * DisplayDistance);


        // Draws The Wall alway at the middle of the screen
        int WallStart = (height()/2) -(WallHeight / 2);
        int WallEnd = WallStart + WallHeight;

        //Low level lighting for an more 3d like experience.

        if(CurrentRay.HorizontalHit) {
            painter.setPen(QColor(255, 0, 0));
        }

        else {

            painter.setPen(QColor(200, 0, 0));
        }
        painter.drawLine(x, WallStart, x, WallEnd);





    }
}





