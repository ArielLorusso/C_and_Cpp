#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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
    void on_Enviar_clicked();

    void disconnected(void);
    void readyRead(void);
    void connected(void);

    void on_conectar_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket * cliente;
};

#endif // MAINWINDOW_H
