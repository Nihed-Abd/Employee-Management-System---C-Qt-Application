#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSslSocket>
#include <QtGui/QApplication>
#include "mailer/SmtpMime"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tab_norme->setModel(cl.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushAdd_clicked()
{
    int id = ui->le_id_3->text().toInt();
    QString nom = ui->le_nom_3->text();
    QString poste = ui->le_poste->text();
    QString email = ui->le_mail->text();
    int salaire = ui->le_salaire->text().toInt();

    Client cl(id, nom, poste, email, salaire);
    bool test = cl.ajouter();

    if (test) {
        ui->tab_norme->setModel(cl.afficher());
        QMessageBox::information(nullptr, "RDI Center", "Ajout effectué.", QMessageBox::Cancel);

        ui->le_id_3->clear();
        ui->le_nom_3->clear();
        ui->le_poste->clear();
        ui->le_mail->clear();
        ui->le_salaire->clear();
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Ajout non effectué.", QMessageBox::Cancel);
    }
     updateLCDs();
}

void MainWindow::on_pushModify_clicked()
{
    Client cl;
    cl.setId(ui->le_id_10->text().toInt());
    cl.setNom(ui->le_nom_6->text());
    cl.setPoste(ui->le_poste_3->text());
    cl.setEmail(ui->le_mail_3->text());
    cl.setSalaire(ui->le_salaire_3->text().toInt());

    bool check = cl.modifier();

    if (check) {
        ui->tab_norme->setModel(cl.afficher());

        QMessageBox::information(nullptr, "RDI Center", "Modification avec succès.", QMessageBox::Cancel);

        ui->le_id_10->clear();
        ui->le_nom_6->clear();
        ui->le_poste_3->clear();
        ui->le_mail_3->clear();
        ui->le_salaire_3->clear();
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Modification échouée.", QMessageBox::Cancel);
    }
     updateLCDs();
}

void MainWindow::on_pushDelete_clicked()
{
    int id = ui->le_id_5->text().toInt();
    bool test = cl.supprimer(id);

    if (test) {
        ui->tab_norme->setModel(cl.afficher());
        QMessageBox::information(nullptr, "RDI Center", "Suppression effectuée.", QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, "RDI Center", "Suppression non effectuée.", QMessageBox::Cancel);
    }
    ui->le_id_5->clear();
    updateLCDs();
}


void MainWindow::on_pushActualiser_clicked()
{
    ui->tab_norme->setModel(cl.afficher());
     updateLCDs();
}



void MainWindow::on_tab_norme_activated(const QModelIndex &index)
{
    QString value = ui->tab_norme->model()->data(index).toString();
    ui->le_id_5->setText(value);
    ui->pdfLine->setText(value);

    QSqlQuery qry;

    qry.prepare("select * from client where id='" + value + "'");
    if (qry.exec()) {
        while (qry.next()) {
            ui->le_id_10->setText(qry.value(0).toString());
            ui->le_nom_6->setText(qry.value(1).toString());
            ui->le_poste_3->setText(qry.value(2).toString());
            ui->le_mail_3->setText(qry.value(3).toString());
            ui->le_salaire_3->setText(qry.value(4).toString());
        }
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString searchValue = arg1;
    QSqlQueryModel *model = new QSqlQueryModel();

    // Filter the table based on the search value
    model->setQuery("SELECT * FROM CLIENT WHERE ID LIKE '%" + searchValue + "%' OR NOM LIKE '%" + searchValue + "%'");
    ui->tab_norme->setModel(model);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString selectedOption = ui->comboBox->currentText();
    QSqlQueryModel *model = new QSqlQueryModel();

    if (selectedOption == "A-Z") {
        // Sort the table alphabetically by name
        model->setQuery("SELECT * FROM CLIENT ORDER BY NOM ASC");
    } else if (selectedOption == "salaire") {
        // Sort the table by salary from highest to lowest
        model->setQuery("SELECT * FROM CLIENT ORDER BY SALAIRE DESC");
    } else {
        // Display the table normally (no sorting)
        model->setQuery("SELECT * FROM CLIENT");
    }

    ui->tab_norme->setModel(model);
}

void MainWindow::updateLCDs() {
    int clientCount = cl.afficher()->rowCount(); // Get the number of rows in the model
    ui->lcdNumber->display(clientCount);

    int totalSalaires = cl.calculerSommeSalaires(); // Calculate the total sum of salaries
    ui->lcdNumberSalaire->display(totalSalaires);
}

void MainWindow::on_PDF_clicked()
{
    // Get the ID from the pdfLine field
    int id = ui->pdfLine->text().toInt();

    // Query the database to retrieve the data corresponding to the ID
    QSqlQuery qry;
    qry.prepare("SELECT * FROM client WHERE ID=:id");
    qry.bindValue(":id", id);

    if (!qry.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve data from the database.");
        return;
    }

    // Prompt the user to choose a location for saving the PDF file
    QString defaultFileName = "client_" + QString::number(id) + ".pdf";
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath() + "/" + defaultFileName, "PDF Files (*.pdf)");

    // Check if the user canceled or didn't provide a file name
    if (fileName.isEmpty())
        return;

    // Create a PDF printer
    QPdfWriter writer(fileName);
    QPainter painter(&writer);
    QFont font;
    font.setPointSize(12);
    painter.setFont(font);

    // Add a title at the top
    painter.drawText(100, 20, "Client Information");

    // Start drawing on the PDF
    int yPos = 200; // Initial y position below the title
    while (qry.next()) {
        // Draw each field on the PDF
        QString data = "ID: " + qry.value(0).toString() + "\n" +
                       "Nom: " + qry.value(1).toString() + "\n" +
                       "Poste: " + qry.value(2).toString() + "\n" +
                       "Email: " + qry.value(3).toString() + "\n" +
                       "Salaire: " + qry.value(4).toString() + "\n";

        QStringList lines = data.split("\n");
        for (const QString& line : lines) {
            painter.drawText(250, yPos, line);
            yPos += 250; // Increment yPos for the next line
        }

        yPos += 250; // Add extra spacing between client records
    }

    painter.end();

    QMessageBox::information(this, "PDF Created", "PDF has been generated successfully.");
}


