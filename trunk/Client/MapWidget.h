#ifndef DEF_MAPWIDGET
#define DEF_MAPWIDGET

#include "..\Shared\Constants.h"
#include "QSFMLCanvas.hpp"
#include <QScrollArea>
#include <memory>

#define MAX_LOADED_RESSOURCES 2000000000
#define RESSOURCES_FOLDER "Ressources/"
#define MAP_FOLDER "Maps/"

class QTimer;

typedef std::auto_ptr<MapInformations> MapPtr;

class MapWidget : public QSFMLCanvas
{
    Q_OBJECT
    public:

    MapWidget(QWidget* Parent, const QPoint& Position, const QSize& Size);
    ~MapWidget();

    void clearRessources();

    void adjustSize();

    void setMap(std::auto_ptr<MapInformations> map) { m_map=map; adjustSize(); }
    bool setMap(const QString& fileName) { bool b=(m_map=loadMap(fileName)).get()==NULL;adjustSize(); return b; }

    static std::auto_ptr<MapInformations> loadMap(QString fileName);

    RSID loadRessource(QString fileName); //Return 0, if the image is already loaded it returns it RSID.
    QList<RSID> loadRessourcesPack(QString fileName, bool exclusive=true); //Return the RSID of succefully loaded ressources. If exclusive is set to true, the previous ressources will be freed, and the RSID will restart from 1.
    QList<RSID> loadRessourcesPack(const QStringList& list, bool exclusive=true);
    QList<RSID> loadRessourcesFolder(QString folderName, bool exclusive=true);

    public slots:

    void openMapInfoDialog();
    void setView(int x, int y, int w, int h);

    private:

    int m_x, m_y, m_w, m_h;

    void OnInit() { }

    void OnUpdate();


    std::auto_ptr<MapInformations> m_map;

    RSID m_loadedRessources;

    QMap<RSID, sf::Image*> m_ressources;
    QMap<QString, RSID> m_loadedRessourcesName;

};

class MapWidgetScroll : public QScrollArea
{
    Q_OBJECT

    public:
    MapWidgetScroll(QWidget* parent=0);
    MapWidget* getMapWidget() { return &map; }

    private slots:

    void ref();

    private:
    MapWidget map;
    QTimer timer;
};

#endif // DEF_MAPWIDGET
