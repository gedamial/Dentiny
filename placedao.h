#ifndef PLACEDAO_H
#define PLACEDAO_H
#include "place.h"
#include <QList>

class PlaceDAO
{
public:
    PlaceDAO();

    Place getPlaceFromId(unsigned int id);
    int getIdFromBelfiore(const QString& belfiore);
    QList<Place> getAllPlaces();
};

#endif // PLACEDAO_H
