#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class Connection
{
    QSqlDatabase db;

public:
    Connection();
    QSqlDatabase getdb()
    {
        return db;
    }
    bool createconnect();
    void closeConnection();
};


#endif // CONNECTION_H
