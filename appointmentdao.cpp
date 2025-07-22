#include "appointmentdao.h"
#include <QSqlDatabase>
#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include "appointment.h"

AppointmentDAO::AppointmentDAO() {}

bool AppointmentDAO::insertAppointment(const Appointment &app)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Appointment (datetime, reason, status, fk_patient) VALUES (?, ?, ?, ?)");
    query.addBindValue(app.datetime);
    query.addBindValue(app.reason);
    query.addBindValue(app.status);
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
            Appointment newAppointment;
            newAppointment.id = query.value(0).toInt();
            newAppointment.datetime = query.value(1).toString();
            newAppointment.reason = query.value(2).toString();
            newAppointment.status = query.value(3).toInt();
            newAppointment.fk_patient = query.value(4).toInt();

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
