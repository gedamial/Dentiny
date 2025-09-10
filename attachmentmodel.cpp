#include "attachmentmodel.h"

AttachmentModel::AttachmentModel() {}

bool AttachmentModel::insertAttachment(const Attachment &attachment)
{
    return attachmentDao.insertAttachment(attachment);
}

QList<Attachment> AttachmentModel::getAttachmentsOfReport(const Report &report)
{
    return attachmentDao.getAttachmentsOfReport(report);
}

void AttachmentModel::deleteAttachment(const Attachment &attachment)
{
    attachmentDao.deleteAttachment(attachment);
}
