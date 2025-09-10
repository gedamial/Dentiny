#ifndef ATTACHMENTMODEL_H
#define ATTACHMENTMODEL_H
#include "attachment.h"
#include "attachmentdao.h"

#include <QList>
#include <QString>

class AttachmentModel
{
public:
    AttachmentModel();

    bool insertAttachment(const Attachment& attachment);
    QList<Attachment> getAttachmentsOfReport(const Report &report);
    void deleteAttachment(const Attachment& attachment);

private:
    AttachmentDAO attachmentDao;
};

#endif // ATTACHMENTMODEL_H
