#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Alarm");
    this->setFixedSize(407, 68);
    ui->time3->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool toggle_start = false;

bool MainWindow::check_convenience(int op){

    QString digits;

    switch(op){

        case 0: {

            digits = ui->time1->text();
            for(int i = 0; i < digits.size(); i++){
                if(!digits[i].isDigit()){
                    return false;
                }
            }
            break;

        }
        case 1: {

            digits = ui->time2->text();
            for(int i = 0; i < digits.size(); i++){
                if(!digits[i].isDigit()){
                    return false;
                }
            }
            break;

        }
        case 2: {

            digits = ui->time3->text();
            for(int i = 0; i < digits.size(); i++){
                if(!digits[i].isDigit()){
                    return false;
                }
            }
            break;

        }
        default: {
            qDebug("Should never reach here... function: check_convenience()");
        }
    }

    return true;

}




void MainWindow::on_time3_textEdited(const QString &arg1)
{

    if(arg1.length() == 3){
        ui->time3->setText(arg1[2]);
    }

    bool digit = check_convenience(2);

    if(!digit){
        ui->time3->setText(NULL);
    }
    else{
        if(arg1.length() == 2){
            ui->time2->setFocus();
        }
    }
}



void MainWindow::on_time2_textEdited(const QString &arg1)
{

    if(arg1.length() == 3){
        ui->time2->setText(arg1[2]);
    }

    bool digit = check_convenience(1);

    if(!digit){
        ui->time2->setText(NULL);
    }
    else{
        if(arg1.length() == 2){
            ui->time1->setFocus();
        }
    }

}


void MainWindow::on_time1_textEdited(const QString &arg1)
{

    if(arg1.length() > 2){
    if(arg1[0] == '0' && arg1[1] == '0'){
        ui->time1->setText(arg1[2]);
    }
}
    bool digit = check_convenience(0);

    if(!digit){
        ui->time1->setText(NULL);
    }

}


void MainWindow::on_settings_clicked()
{

    if(this->height() == 122){
        this->setFixedSize(407, 68);
    }
    else{
       this->setFixedSize(407, 122);
    }
}


void MainWindow::on_browse_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),"~/", tr("Mp3 Files (*.mp3)"));
    ui->pathe->setText(path);
}


void MainWindow::on_time3_textChanged(const QString &arg1)
{
// testing
    if(arg1 == "#44976"){

    }
}




void MainWindow::on_go_clicked()
{

    if(toggle_start){
        return;
    }
    toggle_start = true;
    int h = 0;
    int m = 0;
    int sec = 0;
    h = ui->time1->text().toInt();
    m = ui->time2->text().toInt();
    sec = ui->time3->text().toInt();

    sec = (h*3600) + (m*60) + sec;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
    timer->start(1000);

}

void MainWindow::countdown(){

    QString h = ui->time1->text();
    QString m = ui->time2->text();
    QString s = ui->time3->text();

    int hr = h.toInt();
    int mn = m.toInt();
    int sc = s.toInt();

    if(sc == 0){

        if(mn == 0){
            mn = 59;
            sc = 59;
            if(hr != 0){
                hr--;
            }
        }
        else{
            sc = 59;
            if(mn != 0){
                mn--;
            }
        }
    }
    else{
        sc--;
    }


    if(sc < 10){
        s = "0" + QString::number(sc);
    }
    else{
        s = QString::number(sc);
    }
    if(mn < 10){
        m = "0" + QString::number(mn);
    }
    else{
        m = QString::number(mn);
    }
    if(hr < 10){
        h = "0" + QString::number(hr);
    }
    else{
        h = QString::number(hr);
    }

    ui->time1->setText(h);
    ui->time2->setText(m);
    ui->time3->setText(s);

    if(h.toInt() == 0 && m.toInt() == 0 && s.toInt() == 0){
        this->timer->stop();
        disconnect(timer, SIGNAL(timeout()), 0, 0);

        player = new QMediaPlayer(this);
        QString path = ui->pathe->text();

        if(!QFile::exists(path)){

            path = "qrc:/alarm.mp3";
            player->setMedia(QUrl(path));
            player->setVolume(50);
            player->play();
        }
        else{
            player->setMedia(QUrl::fromLocalFile(path));
            player->setVolume(50);
            player->play();
        }

        toggle_start = false;
    }

}



void MainWindow::on_stop_clicked()
{
    if(this->timer->isActive()){
        this->timer->stop();
        disconnect(timer, SIGNAL(timeout()), 0, 0);
    }

    ui->time1->setText("00");
    ui->time2->setText("00");
    ui->time3->setText("00");

    toggle_start = false;
}

