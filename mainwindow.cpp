#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OnHebraicos();
    OnFeriados();
    connect(ui->chkMarcar, SIGNAL(clicked(bool)), this, SLOT(OnMark(bool)));
    //qDebug() << PROFIT ;
    //DEBUG_MSG(VERSAO) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MudandoMes(int inAno, int inMes)
{
    if(!ui->rbtHebraicos->isChecked()) {
        //_DateTimeDetail DtTemporaria;

        CDateTime       DtData;
        QString         szData;
        int             inDia;
        //int             inMes;

        DtData = CDateTime(inAno, 1, 1); // _getNow();

        int inLinha = -1;
        CStr    szNomeFeriado;
        //ui->tblFeriados->setRowCount(19);

        ui->tblFeriados->setColumnWidth(0, 113);
        ui->tblFeriados->setColumnWidth(1, 226);
        ui->tblFeriados->setColumnWidth(2, 0);

        for(int inConta = 0; inConta < 365; inConta++) {
            if(DtData.isHoliday(&szNomeFeriado)) {
                inLinha++;
                ui->tblFeriados->setRowCount(inLinha+2);
                inDia = DtData.getDay();
                inMes = DtData.getMonth();
                szData  = QString("%1/%2/%3").arg(inDia, 2, 10, QChar('0')).arg(inMes, 2, 10, QChar('0')).arg(inAno);
                ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
                ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString((char*)szNomeFeriado)));
                ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(QString("")));
            }
            DtData = DtData.addDays(1);
        }

    } else {
        ui->tblFeriados->setRowCount(2);
        ui->tblFeriados->setColumnWidth(0, 113);
        ui->tblFeriados->setColumnWidth(1, 125);
        ui->tblFeriados->setColumnWidth(2, 102);

        _DateTimeDetail DtTemporaria;

        CDateTime       DtData;
        QString         szData;
        CStr            szNomeFeriado;
        int             inLinha = -1;

        DtData = CDateTime::getNow();

        QDate      DtTemp = QDate(inAno, inMes, 1).addMonths(1);
        DtTemp = DtTemp.addDays(-1); //Pega o ultimo dia do mes...

        //qDebug() << DtTemp;
        DtData.setDate(inAno, inMes, DtTemp.day());

        DtData.civ2heb(&DtTemporaria);
        //**** Rosh Hashana ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 1;
        DtTemporaria.m_inHMonth = 7;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Yom Kippur ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 10;
        DtTemporaria.m_inHMonth = 7;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Sukkot ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 15;
        DtTemporaria.m_inHMonth = 7;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (9d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Chanukkah ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 25;
        DtTemporaria.m_inHMonth = 9;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (8d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** T´u B´Shvat ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 15;
        DtTemporaria.m_inHMonth = 11;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Ta'anit Ester ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 13;
        DtTemporaria.m_inHMonth = 12;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        if(DtData.getWeekDay() == 7) {
            DtTemporaria.m_inHDay = 11;
            DtData.heb2civ(DtTemporaria);
            DtData.isHHoliday(&szNomeFeriado);
        }
        if(!DtData.isHHoliday()) {
            DtTemporaria.m_inHDay = 13;
            DtTemporaria.m_inHMonth = 13;
            DtData.heb2civ(DtTemporaria);
            DtData.isHHoliday(&szNomeFeriado);
            if(DtData.getWeekDay() == 7) {
                DtTemporaria.m_inHDay = 11;
                DtData.heb2civ(DtTemporaria);
                DtData.isHHoliday(&szNomeFeriado);
            }
        }
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Purim ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 14;
        DtTemporaria.m_inHMonth = 12;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        if(!DtData.isHHoliday()) {
            DtTemporaria.m_inHDay = 14;
            DtTemporaria.m_inHMonth = 13;
            DtData.heb2civ(DtTemporaria);
            DtData.isHHoliday(&szNomeFeriado);
            //DtData = DtData.addDays(29);
            //szData = DtData.format("dd/mm/yyyy");
            //szData = DtData.civ2heb(&DtTemporaria);;
        }
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (2d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Ta'anit Bechorot ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 14;
        DtTemporaria.m_inHMonth = 1;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        if(DtTemporaria.m_inWeekDay == 1) {
            qDebug() << "Corrigindo Ta'anit Bechorot por ser sabado";
            DtTemporaria.m_inHDay = 12;
            DtTemporaria.m_inHMonth = 1;
            DtData.heb2civ(DtTemporaria);
        }
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString("Ta'anit Bechorot")));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Pessach ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 15;
        DtTemporaria.m_inHMonth = 1;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (8d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Yom Hazikaron ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 4;
        DtTemporaria.m_inHMonth = 2;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Yom Ha'Atzmaut ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 5;
        DtTemporaria.m_inHMonth = 2;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Pessach Sheni ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 14;
        DtTemporaria.m_inHMonth = 2;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Yom Yerushalaim ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 28;
        DtTemporaria.m_inHMonth = 2;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        if(szData >= QDateTime::currentDateTime().toString("dd/MM/yyyy")) {
            ui->tblFeriados->selectRow(inLinha+1);
        }
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        //qDebug() << szData << " / " << szNomeFeriado;
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Shavuot ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 6;
        DtTemporaria.m_inHMonth = 3;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (8d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));

        //**** Yom HaHuledet Sheli ****
        inLinha++;
        ui->tblFeriados->setRowCount(inLinha+2);
        DtTemporaria.m_inHDay = 6; // 11/09/1967 - 06/06/5727
        DtTemporaria.m_inHMonth = 6;
        DtData.heb2civ(DtTemporaria);
        DtData.isHHoliday(&szNomeFeriado);
        DtData = DtData.addDays(-1);
        szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        szData  = QString("%1/%2/%3 (1d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));
        //qDebug() << "Terminei.";


        ui->tblFeriados->setCurrentCell(0,0);
        /////////////////////////////////////////////////////////
        ////**** Nova data a Considerar ****
        //inLinha++;
        //ui->tblFeriados->setRowCount(inLinha+2);
        //DtTemporaria.m_inHDay = novoDia;
        //DtTemporaria.m_inHMonth = NovoMes;
        //DtData.heb2civ(DtTemporaria);
        //DtData.isHHoliday(&szNomeFeriado);
        //DtData = DtData.addDays(-1);
        //szData  = QString("%1/%2/%3").arg(DtData.getDay(), 2, 10, QChar('0')).arg(DtData.getMonth(), 2, 10, QChar('0')).arg(DtData.getYear());
        //ui->tblFeriados->setItem(inLinha, 0, new QTableWidgetItem(szData));
        //ui->tblFeriados->setItem(inLinha, 1, new QTableWidgetItem(QString(szNomeFeriado)));
        //szData  = QString("%1/%2/%3 (8d)").arg(DtTemporaria.m_inHDay, 2, 10, QChar('0')).arg(DtTemporaria.m_inHMonth, 2, 10, QChar('0')).arg(DtTemporaria.m_inHYear);
        //ui->tblFeriados->setItem(inLinha, 2, new QTableWidgetItem(szData));
        /////////////////////////////////////////////////////////
    }
}

void MainWindow::OnHebraicos(void)
{
    //CDateTime       DtData;

    //DtData = CDateTime(ui->calendarWidget->yearShown(), ui->calendarWidget->monthShown(), ui->calendarWidget->selectedDate().day());
    ui->tblFeriados->setToolTip("A Data indica a VÉSPERA do Feriado (Pôr-do-Sol)");
    MudandoMes(ui->calendarWidget->yearShown(), ui->calendarWidget->monthShown());
}

void MainWindow::OnCivis(void)
{
    //CDateTime       DtData;

    // CDateTime::getNow();
    //DtData = CDateTime(ui->calendarWidget->yearShown(), ui->calendarWidget->monthShown(), ui->calendarWidget->selectedDate().day());
    ui->tblFeriados->setToolTip("A Data indica o feriado em si!!");
    MudandoMes(ui->calendarWidget->yearShown(), ui->calendarWidget->monthShown());
}

void MainWindow::OnFeriados()
{
    ui->tblFeriados->show(); // 10/270/381/131
    ui->lblDataCivil->hide();
    ui->lblDataHebraica->hide();
    ui->lblDataConvertida->hide();

    ui->edtDataCivil->hide();
    ui->edtDataHebraica->hide();
    ui->edtDataConvertida->hide();
}

void MainWindow::OnConversao()
{
    ui->tblFeriados->hide(); // 10/270/381/131
    ui->lblDataConvertida->setText("Data Convertida:");
    ui->lblDataCivil->setText("Data Civil:");
    ui->lblDataHebraica->setText("Data Hebraica:");

    ui->lblDataCivil->show();
    ui->lblDataHebraica->show();
    ui->lblDataConvertida->show();

    ui->edtDataCivil->setText("");
    ui->edtDataHebraica->setText("");
    ui->edtDataConvertida->setText("");

    ui->edtDataCivil->show();
    ui->edtDataHebraica->show();
    ui->edtDataConvertida->show();

}

void MainWindow::OnDiferenca()
{
    ui->tblFeriados->hide(); // 10/270/381/131
    ui->lblDataConvertida->setText("Diferença:");
    ui->lblDataCivil->setText("Data Inicial:");
    ui->lblDataHebraica->setText("Data Final:");

    ui->lblDataCivil->show();
    ui->lblDataHebraica->show();
    ui->lblDataConvertida->show();

    ui->edtDataCivil->setText("");
    ui->edtDataHebraica->setText("");
    ui->edtDataConvertida->setText("");

    ui->edtDataCivil->show();
    ui->edtDataHebraica->show();
    ui->edtDataConvertida->show();

}

void MainWindow::OnOk()
{
    if(ui->rbtConversao->isChecked()) {
        if(ui->edtDataCivil->text() != "") {
            CDateTime  AConverter(ui->edtDataCivil->text().toStdString().c_str());
            _DateTimeDetail DtDetail;
            CStr szHoliday;
            //(char*)AConverter.civ2heb(DtDetail);
            ui->edtDataConvertida->setText((char*)AConverter.civ2heb(&DtDetail));
            ui->edtDataHebraica->setText(QString("%1/%2/%3").arg(DtDetail.m_inHDay, 2, 10, QChar('0')).arg(DtDetail.m_inHMonth+1, 2, 10, QChar('0')).arg(DtDetail.m_inHYear, 4, 10, QChar('0')));
            if(AConverter.isHHoliday(&szHoliday)) {
                QString szTempo = ui->edtDataConvertida->text() + " (" + QString((char*)szHoliday) + ")";
                ui->edtDataConvertida->setText(szTempo);
            }
        } else {
            CDateTime  AConverter(ui->edtDataHebraica->text().toStdString().c_str());
            _DateTimeDetail DtDetail;
            DtDetail.m_inHDay   = AConverter.getDay();
            DtDetail.m_inHMonth = AConverter.getMonth();
            DtDetail.m_inHYear  = AConverter.getYear();
            //(char*)AConverter.civ2heb(DtDetail)
            ui->edtDataCivil->setText((char*)AConverter.heb2civ(DtDetail));
            ui->edtDataConvertida->setText((char*)AConverter.format("dd \\d\\e mmmm \\d\\e yyyy"));
            //ui->edtDataHebraica->setText(QString("%1/%2/%3").arg(AConverter.getDay(),2).arg(AConverter.getMonth(),2).arg(AConverter.getYear(),4));
        }
    } else if(ui->rbtDiferenca->isChecked()) {
        QString szExtenso ;
        CDateTime  dtInicial(ui->edtDataCivil->text().toStdString().c_str());
        CDateTime  dtFinal(ui->edtDataHebraica->text().toStdString().c_str());
        qDebug() << dtFinal.format("dd/mm/yyyy") << " / " << dtFinal.isEmpty() << " / " << ui->edtDataHebraica->text().toStdString().c_str() << endl;
        if(dtFinal.isEmpty()) {
            int inQtde = atoi(ui->edtDataHebraica->text().toStdString().c_str());
            dtFinal = dtInicial.addDays(inQtde);
            szExtenso = QString("%1 dias entre %2 e %3").arg(dtFinal.getDiff(dtInicial)).arg((char*)dtInicial.format("dd/mm/yyyy")).arg((char*)dtFinal.format("dd/mm/yyyy"));
        } else {
            szExtenso = QString("%1 dias entre %2 e %3").arg(dtFinal.getDiff(dtInicial)).arg((char*)dtInicial.format("dd/mm/yyyy")).arg((char*)dtFinal.format("dd/mm/yyyy"));
        }
        ui->edtDataConvertida->setText(szExtenso);
    }
}

void MainWindow::OnEditFinishDtCivil()
{
    if(ui->rbtConversao->isChecked()) {
        ui->edtDataHebraica->setText("");
    }
}

void MainWindow::OnEditFinishDtHebraica()
{
    if(ui->rbtConversao->isChecked()) {
        ui->edtDataCivil->setText("");
    }
}

void MainWindow::OnMark(bool boValor)
{
    OnHebraicos();
}






