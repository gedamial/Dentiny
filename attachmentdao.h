#ifndef ATTACHMENTDAO_H
#define ATTACHMENTDAO_H
#include "attachment.h"
#include "report.h"
#include <QSqlQuery>

class AttachmentDAO
{
public:
    AttachmentDAO();

    bool insertAttachment(const Attachment& attachment);
    Attachment LoadFromQueryRow(const QSqlQuery& query);
    QList<Attachment> getAttachmentsOfReport(const Report &report);
    void deleteAttachment(const Attachment& attachment);
};

#endif // ATTACHMENTDAO_H
