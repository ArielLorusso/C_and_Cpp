#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_conectar_clicked();

    void on_Enviar_clicked();

    void newConnection(void);
    void disconnected(void);
    void readyRead(void);


private:
    Ui::MainWindow *ui;

    QTcpServer * socket;
    QTcpSocket * cliente;

};

#endif // MAINWINDOW_H
