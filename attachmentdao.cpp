#include "attachmentdao.h"
#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

AttachmentDAO::AttachmentDAO() {}

bool AttachmentDAO::insertAttachment(const Attachment& attachment)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Attachment (filename, fk_report) VALUES (:filename, :fk_report)");
    query.bindValue(":filename", attachment.filename);
    query.bindValue(":fk_report", attachment.fk_report);

    return query.exec();
}

Attachment AttachmentDAO::LoadFromQueryRow(const QSqlQuery &query)
{
    Attachment att;
    att.id = query.value("id").toInt();
    att.filename = query.value("filename").toString();
    att.fk_report = query.value("fk_report").toInt();

    return att;
}

QList<Attachment> AttachmentDAO::getAttachmentsOfReport(const Report &report)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Attachment WHERE fk_report = :fk_report");
    query.bindValue(":fk_report", report.id);
    query.exec();

    QList<Attachment> attachments;

    if(query.exec())
    {
        while (query.next())
        {
            Attachment att = LoadFromQueryRow(query);
            attachments.append(att);
        }
    }

    else
    {
        // print error
        qDebug() << "query exec error in AttachmentDAO::getAttachmentsOfReport";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return attachments;
}

void AttachmentDAO::deleteAttachment(const Attachment &attachment)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM Attachment WHERE id = :id");
    query.bindValue(":id", attachment.id);
    query.exec();
}
