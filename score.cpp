#include "score.h"
#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsView>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    this->score = 0;

    setPlainText(QString("Score: ") + QString::number(this->score)); // Score: 0
    // setDefaultTextColor(Qt::blue);
    // setFont(QFont("times",16));
}

void Score::increaseScore(){
    this->score++;
    setPlainText(QString("Score: ") + QString::number(this->score)); // Score: 1
}

int Score::returnScore(){
    return this->score;
}
