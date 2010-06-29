#include "Constants.h"
#include <cstdio>
#include <ctime>
#include <QObject>

#define tr(a) QObject::tr(a)

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

quint32 sizeX(const MapArray& m)  { return (quint32)m.shape()[0];}
quint32 sizeY(const MapArray& m)  { return (quint32)m.shape()[1];}
quint32 sizeX(MapArray* m)  { return (quint32)m->shape()[0];}
quint32 sizeY(MapArray* m)  { return (quint32)m->shape()[1];}

QString ETS(ENUM_TYPE errorCode, QString txt)
{
    static QMap<ENUM_TYPE, QString> stringMap;
    static bool first=true;
    if(first)
    {
        stringMap[ALREADY_VOTED]=tr("Vous avez déjà voté !");
        stringMap[GAME_NOT_LAUNCHED]=tr("La partie n'a pas encore été démarée par le Maître du Jeu.");
        stringMap[NOT_GM]=tr("Vous devez être Maître du Jeu pour effectuer cette action.");
        stringMap[INVALID_PACKET]=tr("Un paquet reçu de votre part par le serveur est invalide.");
        stringMap[INVALID_CANAL]=tr("Le canal demandé n'existe pas.");
        stringMap[CLIENT_DOES_NOT_EXIST]=tr("Ce client n'existe pas !");
        stringMap[CLIENTS_LIMIT_REACHED]=tr("La limite forte du nombre de clients connectés silmutanément a été atteinte. Désolé.");
        stringMap[SANCTION_UNKNOWN]=tr("La sanction demandée est inconnue.");
        first=false;
    }

    return stringMap.contains(errorCode) ? stringMap.value(errorCode).arg(txt) : tr("Une erreur inconnue est arrivée.");
}
