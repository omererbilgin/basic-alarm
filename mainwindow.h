#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool check_convenience(int);


private slots:
    void on_time3_textEdited(const QString &arg1);

    void on_time2_textEdited(const QString &arg1);

    void on_time1_textEdited(const QString &arg1);

    void on_settings_clicked();

    void on_browse_clicked();

    void on_time3_textChanged(const QString &arg1);

    void on_go_clicked();

    void countdown();

    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
    QTimer * timer;
    QMediaPlayer * player;

};
#endif // MAINWINDOW_H
