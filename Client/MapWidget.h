#ifndef DEF_MAPWIDGET
#define DEF_MAPWIDGET

#include "..\Shared\Constants.h"
#include "QSFMLCanvas.hpp"
#include <QScrollArea>

class QTimer;
class MapEditor;

class MapWidget : public QSFMLCanvas
{
    Q_OBJECT

    friend class MapEditor;
    friend class MapWidgetScroll;

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
    static bool saveMap(const MapInformations*, QString fileName);

    bool saveMap(const QString& fileName) const;

    RSID loadRessource(QString fileName); //Return 0, if the image is already loaded it returns it RSID.
    QList<RSID> loadRessourcesPack(QString fileName); //Return the RSID of succefully loaded ressources. Will free previous ressources.
    QList<QPair<QString, RSID> > loadRessources(const QStringList& list);
    QList<QPair<QString, RSID> > loadRessourcesPack(const QList<QPair<QString, RSID> >& list);
    bool loadRessource(QString fileName, RSID id); //Force to load the fileName image with the id RSID. True on error.

    bool saveRessources(QString fileName); //Save the loaded ressources in a ressource pack. True on error.

    RSID ressourceRSID(const QString& fileName) const;

    bool isRSIDUsed(RSID id) const { return m_ressources.contains(id); }

    bool isMapValid() const;

    QPoint selectedCase() const { return m_selectedCase; }

    public slots:

    void openMapInfoDialog();
    void setMap(MapPtr);
    void setView(int x, int y, int w, int h);

    signals:

    void mapClicked(QPoint newCase);
    void highlightedCaseChanged(QPoint newCase);

    protected:

    virtual void mouseReleaseEvent (QMouseEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void leaveEvent (QEvent *event);
    virtual void enterEvent (QEvent *event);


    private:

    QPoint posToMap(int x, int y) { return posToMap(QPoint(x,y)); }
    QPoint posToMap(QPoint pos);

    int m_x, m_y, m_w, m_h;

    QPoint m_highlightedCase;
    bool m_mouseInside;

    QPoint m_selectedCase;

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

    friend class MapEditor;

    public:
    MapWidgetScroll(QWidget* parent=0);
    MapWidget* getMapWidget() { return &map; }

    private slots:

    void ref();
    void sizeUpdate();

    private:
    MapWidget map;
    QTimer timer;
};

#endif // DEF_MAPWIDGET
