#include "appointment.h"

Appointment::Appointment() {}

QString Appointment::getStatusText()
{
    if(status == 0)
    {
        return "Created/Pending";
    }

    else if(status == 1)
    {
        return "Completed";
    }

    else if(status == 2)
    {
        return "Canceled";
    }

    else
    {
        return "Unknown";
    }
}
