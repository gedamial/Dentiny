#ifndef ATTACHMENT_H
#define ATTACHMENT_H
#include <QString>

class Attachment
{
public:
    Attachment();

    int id;
    QString filename;
    int fk_report;
};

#endif // ATTACHMENT_H
