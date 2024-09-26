#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include "client.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:




    void on_pushAdd_clicked();

    void on_pushModify_clicked();

    void on_pushActualiser_clicked();

    void on_tab_normes_3_activated(const QModelIndex &index);

    void on_pushDelete_clicked();

    void on_tab_norme_activated(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushActualiser_2_clicked();

    void on_PDF_clicked();

    void on_sendMail_clicked();

private:
    Ui::MainWindow *ui;
    Client cl;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumberSalaire;

    // Function to update LCD widgets
    void updateLCDs();
    void onEmailSent(const QString& accessToken);
    void onSocketEncrypted();
    void onSslErrors(const QList<QSslError>& errors);

};


#endif // MAINWINDOW_H
