#include "placemodel.h"

PlaceModel::PlaceModel() {}

QList<Place> PlaceModel::getAllPlaces()
{
    return placeDao.getAllPlaces();
}

int PlaceModel::getPlaceIdFromBelfiore(const QString &belfiore)
{
    return placeDao.getPlaceIdFromBelfiore(belfiore);
}
