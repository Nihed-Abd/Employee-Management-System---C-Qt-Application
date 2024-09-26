#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Client
{
public:
    int id;
    QString nom, poste, email;
    int salaire;

public:
    Client();
    Client(int, QString, QString, QString, int);

    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPoste() const { return poste; }
    QString getEmail() const { return email; }
    int getSalaire() const { return salaire; }

    // Setters
    void setId(int id_c) { id = id_c; }
    void setNom(QString nom_c) { nom = nom_c; }
    void setPoste(QString poste_c) { poste = poste_c; }
    void setEmail(QString email_c) { email = email_c; }
    void setSalaire(int salaire_c) { salaire = salaire_c; }

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier();
    int calculerSommeSalaires();
    void sendEmail();
};

#endif // CLIENT_H
