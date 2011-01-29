#ifndef DEF_MAPWIDGET
#define DEF_MAPWIDGET

#include "..\Shared\Constants.h"
#include "QSFMLCanvas.hpp"
#include <QScrollArea>

#define MAX_LOADED_RESSOURCES 2000000000
#define RESSOURCES_FOLDER "Ressources/"
#define MAP_FOLDER "Maps/"

class QTimer;


class MapWidget : public QSFMLCanvas
{
    Q_OBJECT
    public:

    MapWidget(QWidget* Parent, const QPoint& Position, const QSize& Size);
    ~MapWidget();

    void clearRessources();

    const MapInformations* getMap() const { return m_map.get(); }

    void adjustSize();

    bool isHightlighEnabled() const { return m_highlightEnabled; }
    void setHighlight(bool highlight);

    bool setMap(const QString& fileName) { bool b=(m_map=loadMap(fileName)).get()==NULL;adjustSize(); return b; }

    static std::auto_ptr<MapInformations> loadMap(QString fileName);

    RSID loadRessource(QString fileName); //Return 0, if the image is already loaded it returns it RSID.
    QList<RSID> loadRessourcesPack(QString fileName, bool exclusive=true); //Return the RSID of succefully loaded ressources. If exclusive is set to true, the previous ressources will be freed, and the RSID will restart from 1.
    QList<RSID> loadRessourcesPack(const QStringList& list, bool exclusive=true);
    QList<RSID> loadRessourcesFolder(QString folderName, bool exclusive=true);

    bool isMapValid() const;

    public slots:

    void openMapInfoDialog();
    void setMap(MapPtr);
    void setView(int x, int y, int w, int h);

    signals:

    void mapClicked(int caseX, int caseY);

    protected:

    virtual void mouseReleaseEvent (QMouseEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    private:

    QPoint posToMap(int x, int y) { return posToMap(QPoint(x,y)); }
    QPoint posToMap(QPoint pos);

    int m_x, m_y, m_w, m_h;

    QPoint m_highlightedCase;

    bool m_highlightEnabled;

    void OnInit() { }

    void OnUpdate();

    QMap<RSID, RSID> concatenateRessources(const QMap<RSID, QString>& other);


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
