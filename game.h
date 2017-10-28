#ifndef GAME_H
#define GAME_H

#include "libs.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private slots:
    void on_settingsButton_clicked();

    void on_backSetButton_clicked();

    void on_exitButton_clicked();

    void on_aboutButton_clicked();

    void on_usernameText_textChanged(const QString &arg1);

    void on_goMenuButton_clicked();

    void on_singleGameButton_clicked();

    void on_lineEdit_returnPressed();

    void botTime();

    void on_multiplayerGameButton_clicked();

    void on_user1text_returnPressed();

    void on_user2text_returnPressed();

    void on_goMenuButton_2_clicked();

    void on_backgroundButton_clicked();

protected:
    void changeEvent(QEvent * event) override;

private:
    QTranslator translator;
    QSqlDatabase db;
    Ui::Game *ui;
};

#endif // GAME_H
