#ifndef PLACEMODEL_H
#define PLACEMODEL_H

#include "place.h"
#include "placedao.h"
#include <QList>
#include <QString>

class PlaceModel
{
public:
    PlaceModel();

    QList<Place> getAllPlaces();
    int getPlaceIdFromBelfiore(const QString& belfiore);

private:
    PlaceDAO placeDao;
};

#endif // PLACEMODEL_H
