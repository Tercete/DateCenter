#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include "CDatatypes.h"
//#include <BTC.h>

#define VERSAO      "2.0.0." SVN_REV


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
    void OnCivis(void);
    void OnHebraicos(void);
    void MudandoMes(int inAno, int inMes);
    void OnMark(bool boValor);

    void OnFeriados();
    void OnConversao();
    void OnDiferenca();
    void OnOk();

    void OnEditFinishDtCivil();
    void OnEditFinishDtHebraica();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
