#include "appointmentdao.h"
#include <QSqlDatabase>
#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include "appointment.h"

AppointmentDAO::AppointmentDAO() {}

Appointment AppointmentDAO::loadFromQueryRow(const QSqlQuery& query)
{
    Appointment app;
    app.id = query.value("id").toInt();
    app.datetime = query.value("datetime").toString();
    app.reason = query.value("reason").toString();
    app.fk_status = query.value("fk_status").toInt();
    app.fk_patient = query.value("fk_patient").toInt();

    return app;
}

Appointment AppointmentDAO::getAppointmentFromId(int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Appointment WHERE id = ?");
    query.addBindValue(id);

    if(query.exec())
    {
        query.next();
        return loadFromQueryRow(query);
    }

    else
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getAllPlaces";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return {};
}

bool AppointmentDAO::insertAppointment(const Appointment &app)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Appointment (datetime, reason, fk_status, fk_patient) VALUES (?, ?, ?, ?)");
    query.addBindValue(app.datetime);
    query.addBindValue(app.reason);
    query.addBindValue(app.fk_status);
    query.addBindValue(app.fk_patient);
    return query.exec();
}

QList<Appointment> AppointmentDAO::getAppointmentsFromDateSorted(QString date)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Appointment WHERE DATE(datetime) = :date ORDER BY datetime ASC");
    query.bindValue(":date", date);

    QList<Appointment> appointments;

    if(query.exec())
    {
        while(query.next())
        {
            Appointment newAppointment = loadFromQueryRow(query);
            appointments.append(newAppointment);
        }
    }

    else
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getAllPlaces";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return appointments;
}

void AppointmentDAO::updateAppointment(const Appointment& newAppointment)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE Appointment SET datetime=:datetime, reason=:reason, fk_status=:fk_status, fk_patient=:fk_patient WHERE id = :id");
    query.bindValue(":datetime", newAppointment.datetime);
    query.bindValue(":reason", newAppointment.reason);
    query.bindValue(":fk_status", newAppointment.fk_status);
    query.bindValue(":fk_patient", newAppointment.fk_patient);
    query.bindValue(":id", newAppointment.id);

    if(!query.exec())
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getAllPlaces";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }
}
