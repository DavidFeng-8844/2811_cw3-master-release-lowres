//
//
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;
    int currentIndex = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(1); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) ); // if state changes, run playStateChanged

        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between each shuffle
        mTimer->start();
        // connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

private slots:

    // change the image and video for one button every one second
    void shuffle();
    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void playNext();
    void playPrevious();
    void handlePauseToggle(bool paused);
};

#endif //CW2_THE_PLAYER_H
