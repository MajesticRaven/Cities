#include "game.h"
#include "ui_game.h"

QString lang = "en_US";
QString username = "Guest";
QList<QString> notOriginal;
int botScore, playerScore, player2Score;
int picindex = 1;

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->setStyleSheet("QStackedWidget { border-image: url(" + qApp->applicationDirPath() + "/resources/backgrounds/" + QString::number(picindex) + ".jpg);}");

    db = QSqlDatabase::addDatabase("QSQLITE");

    ui->comboBox->addItems(QStringList() << "en_US" << "ru_RU");
    connect(ui->comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
               [=](const QString &str){
           translator.load("QtLanguage_" + str);
           lang = str;
           qApp->installTranslator(&translator);
       });

    ui->usernameText->setText(username);
}

Game::~Game()
{
    delete ui;
}

void Game::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void Game::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Game::on_backSetButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Game::on_exitButton_clicked()
{
    exit(0);
}

void Game::on_aboutButton_clicked()
{
    QMessageBox::about(this, "About", "This game was created by Pavlenkoxx "
                                      "\n https://vk.com/pavlenkoxx");
}

void Game::on_usernameText_textChanged(const QString &arg1)
{
    username = ui->usernameText->text();
    ui->youLabel1->setText(username);
}

void Game::on_goMenuButton_clicked()
{
    if(QMessageBox::question(this, "Go to menu", "Are you sure?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Game::on_singleGameButton_clicked()
{
    playerScore = 0;
    botScore = 0;
    notOriginal.clear();
    if(lang == "ru_RU")
        ui->poleText->setText("йцукенгшщзджхлорпавыфячсить");
    else
        ui->poleText->setText("qwertyuioplkjhgfdsazxcvbnm");
    ui->poleText->setText(ui->poleText->text().mid(0, rand() % 20));
    ui->lineEdit->clear();
    ui->stackedWidget->setCurrentIndex(2);
    botTime();
}

void Game::on_lineEdit_returnPressed()
{
    QString str = ui->lineEdit->text();
    QString res = ui->poleText->text();
    str.toLower();
    db.setDatabaseName(qApp->applicationDirPath() + "/cities_" + lang + ".db");

    if(db.open())
    {
        QSqlQuery query(db);
        while(res.size())
        {
            query.exec("Select town from cities WHERE lower(town) LIKE '" + res[res.size() - 1] + "%'");

            if(!query.first())
            {
                res = res.mid(0, res.size()-1);
            }
            else {
                break;
            }
        }

        query.exec("Select town from cities WHERE lower(town) LIKE '" + str + "'");
        if(query.first() && notOriginal.indexOf(str) == -1 && str[0] == res[res.size() - 1])
        {
            notOriginal.push_back(str);
            playerScore++;
            ui->poleText->setText(str);
            ui->yourScore->setText(QString::number(playerScore));
            botTime();
        }
    }
    db.close();
}

void Game::botTime()
{
    QString res = ui->poleText->text();
    res.toLower();
    db.setDatabaseName(qApp->applicationDirPath() + "/cities_" + lang + ".db");
    QString str;

    if(db.open())
    {
        QSqlQuery query(db);

        while(res.size())
        {
            query.exec("Select town from cities WHERE lower(town) LIKE '" + res[res.size() - 1] + "%'");

            if(!query.first())
            {
                res = res.mid(0, res.size()-1);
            }
            else {
                break;
            }
        }

        query.exec("Select town from cities WHERE lower(town) LIKE '" + res[res.size() - 1] + "%'");

        for(int i = 0; i < rand() % 10; i++) {
            query.next();
        }
        while(query.next())
        {
            str = query.value(0).toString();

            if(notOriginal.indexOf(str) == -1)
            {
                ui->poleText->setText(str);
                notOriginal.push_back(str);
                botScore++;
                ui->botScore->setText(QString::number(botScore));
                ui->lineEdit->clear();
                break;
            }
            else
            {
                query.next();
            }
        }
    }
    db.close();
}

void Game::on_multiplayerGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    playerScore = 0;
    playerScore = 0;
    notOriginal.clear();
    if(lang == "ru_RU")
        ui->poleText_2->setText("йцукенгшщзджхлорпавыфячсить");
    else
        ui->poleText_2->setText("qwertyuioplkjhgfdsazxcvbnm");
    ui->poleText_2->setText(ui->poleText_2->text().mid(0, rand() % 20));
    ui->poleText_2->setText(ui->poleText_2->text().at(ui->poleText_2->text().size() - 1));
    ui->user1text->clear();
    ui->user2text->clear();
    ui->user2name->setText(username);
    ui->user2text->setEnabled(false);
    ui->youLabel1_2->setText(username);
}


void Game::on_user1text_returnPressed()
{
    QString str = ui->user1text->text();
    QString res = ui->poleText_2->text();
    str.toLower();
    db.setDatabaseName(qApp->applicationDirPath() + "/cities_" + lang + ".db");

    if(db.open())
    {
        QSqlQuery query(db);
        while(res.size())
        {
            query.exec("Select town from cities WHERE lower(town) LIKE '" + res[res.size() - 1] + "%'");

            if(!query.first())
            {
                res = res.mid(0, res.size()-1);
            }
            else {
                break;
            }
        }

        query.exec("Select town from cities WHERE lower(town) LIKE '" + str + "'");
        if(query.first() && notOriginal.indexOf(str) == -1 && str[0] == res[res.size() - 1])
        {
            notOriginal.push_back(str);
            playerScore++;
            ui->poleText_2->setText(str);
            ui->multiScoreUser1->setText(QString::number(playerScore));
            ui->user1text->setEnabled(false);
            ui->user2text->setEnabled(true);
        }
    }
    db.close();
}

void Game::on_user2text_returnPressed()
{
    QString str = ui->user2text->text();
    QString res = ui->poleText_2->text();
    str.toLower();
    db.setDatabaseName(qApp->applicationDirPath() + "/cities_" + lang + ".db");

    if(db.open())
    {
        QSqlQuery query(db);
        while(res.size())
        {
            query.exec("Select town from cities WHERE lower(town) LIKE '" + res[res.size() - 1] + "%'");

            if(!query.first())
            {
                res = res.mid(0, res.size()-1);
            }
            else {
                break;
            }
        }

        query.exec("Select town from cities WHERE lower(town) LIKE '" + str + "'");
        if(query.first() && notOriginal.indexOf(str) == -1 && str[0] == res[res.size() - 1])
        {
            notOriginal.push_back(str);
            player2Score++;
            ui->poleText_2->setText(str);
            ui->multiScoreUser2->setText(QString::number(player2Score));
            ui->user1text->setEnabled(true);
            ui->user2text->setEnabled(false);
        }
    }
    db.close();
}

void Game::on_goMenuButton_2_clicked()
{
    if(QMessageBox::question(this, "Go to menu", "Are you sure?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Game::on_backgroundButton_clicked()
{
    if(picindex == 12) {
        picindex = 0;
    }
    picindex++;
    ui->stackedWidget->setStyleSheet("QStackedWidget { border-image: url(" + qApp->applicationDirPath() + "/resources/backgrounds/" + QString::number(picindex) + ".jpg);}");
}
