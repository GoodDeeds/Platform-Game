#include "diamond.h"


Diamond::Diamond(QGraphicsScene* scene_local , std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate)
{

    scene = scene_local;
  //  QImage(image_location.c_str());

   // pixMapImage = QPixmap::fromImage(QImage();


    if(!this->pixMapImage.load((image_location).c_str()))
    {
        qDebug() << "ERROR(gemtype1.cpp) : Failed To Load Gem Image" << image_location.c_str() <<endl;
        std::exit(EXIT_FAILURE);
    }
    this->pixMapImage = this->pixMapImage.scaled(QSize(width,height));
     this->setPos(x_coordinate , y_coordinate);
}


/*
Diamond::Diamond(QGraphicsScene* scene_local , std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate)
{

    scene = scene_local;
    QImage(image_location.c_str());

    pixMapImage = QPixmap::fromImage(QImage();

    /*
    if(!this->pixMapImage.load((image_location).c_str()))
    {
        qDebug() << "ERROR(gemtype1.cpp) : Failed To Load Gem Image" << image_location.c_str() <<endl;
        std::exit(EXIT_FAILURE);
    }
    this->pixMapImage = this->pixMapImage.scaled(QSize(width,height));
   // this->setPos(x_coordinate , y_coordinate);
}*/
void Diamond::draw()
{
    this->setPixmap(this->pixMapImage);
    scene->addItem(this);
}






























