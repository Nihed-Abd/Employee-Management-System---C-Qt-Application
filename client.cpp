#include "client.h"

Client::Client() {}

Client::Client(int id, QString nom, QString poste, QString email, int salaire)
{
    this->id = id;
    this->nom = nom;
    this->poste = poste;
    this->email = email;
    this->salaire = salaire;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString salaire_string = QString::number(salaire);

    query.prepare("INSERT INTO CLIENT (ID, NOM, POSTE, EMAIL, SALAIRE) "
                  "VALUES (:id, :nom, :poste, :email, :salaire)");

    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);
    query.bindValue(":salaire", salaire_string);

    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString salaire_string = QString::number(salaire);
    query.prepare("UPDATE CLIENT SET NOM=:nom, POSTE=:poste, EMAIL=:email, SALAIRE=:salaire WHERE ID=:id");

    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);
    query.bindValue(":salaire", salaire_string);

    return query.exec();
}

QSqlQueryModel *Client::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));

    return model;
}

bool Client::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM CLIENT WHERE ID=:id");
    query.bindValue(":id", id);

    return query.exec();
}

int Client::calculerSommeSalaires()
{
    QSqlQuery query;
    int sommeSalaires = 0;

    if (query.exec("SELECT SUM(SALAIRE) FROM CLIENT")) {
        if (query.next()) {
            sommeSalaires = query.value(0).toInt();
        }
    }

    return sommeSalaires;
}
void sendEmail() {
    // Create an SmtpClient object
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // Set the username (your email address) and the password for SMTP authentication
    smtp.setUser("your_email_address@gmail.com");
    smtp.setPassword("your_password");

    // Create a MimeMessage object for the email
    MimeMessage message;

    EmailAddress sender("your_email_address@gmail.com", "Your Name");
    message.setSender(&sender);

    EmailAddress recipient("recipient@host.com", "Recipient's Name");
    message.addRecipient(&recipient);
    message.setSubject("Subject of the email");

    // Create a MimeText object for the email body
    MimeText text;
    text.setText("Hello,\nThis is a sample email sent using SmtpMime library.\n");

    // Add the text to the email message
    message.addPart(&text);

    // Connect to the SMTP server, login, send the email, and quit
    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();
}


