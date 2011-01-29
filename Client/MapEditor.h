#ifndef DEF_MAPEDITOR
#define DEF_MAPEDITOR

#include <QMainWindow>
#include "MapWidget.h"


class MapEditor : public QMainWindow
{
    Q_OBJECT
    public:
        MapEditor(QWidget* parent = NULL, const QString& map = QString());

    public slots:
        bool loadMap(QString map = QString());

    private:

        MapWidgetScroll* m_mapWidgetScroll;

        QString m_mapName;
};

#endif // DEF_MAPEDITOR
