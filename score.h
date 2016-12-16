#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsView>

class Score: public QGraphicsTextItem{

protected:
/* empty */

public:
    Score(QGraphicsItem * parent=0);

    void increaseScore();

    int returnScore();

private:
    int score;

signals:
/* empty */

public slots:
/* empty */

};

#endif // SCORE_H
