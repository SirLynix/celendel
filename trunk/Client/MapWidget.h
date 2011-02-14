#ifndef DEF_MAPWIDGET
#define DEF_MAPWIDGET

#include "..\Shared\Constants.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class QTimer;
class MapEditor;
class QGraphicsRectItem;

void swp (int& x1, int& x2);

struct MapArea
{
    MapArea(QPoint lup=QPoint(0,0), QPoint ldown=QPoint(0,0)):leftUp(lup), rightDown(ldown) {}
    void normalise() {if(leftUp.x()>rightDown.x()) {swp(rightDown.rx(),leftUp.rx());} if(leftUp.y()>rightDown.y()) {swp(rightDown.ry(),leftUp.ry());}}

    QPoint size() const {return QPoint(abs(rightDown.x()-leftUp.x())+1,abs(rightDown.y()-leftUp.y())+1); }

    QPoint leftUp; QPoint rightDown;
};

class MapWidget : public QGraphicsView
{
    Q_OBJECT

    friend class MapEditor;
    friend class MapWidgetScroll;

    public:

    MapWidget(QWidget* Parent);
    ~MapWidget();

    void clearRessources();

    const MapInformations* getMap() const { return m_map.get(); }


    bool isHightlighEnabled() const { return m_highlightEnabled; }
    void setHighlight(bool highlight);

    void setMultiSelectionEnabled(bool d) { m_multiSelectionEnabled=d; }
    bool isMultiSelectionEnabled() const { return m_multiSelectionEnabled; }

    bool setMap(const QString& fileName) { bool b=(m_map=loadMap(fileName)).get()==NULL;adjustSize(); return b; }

    static std::auto_ptr<MapInformations> loadMap(QString fileName);
    static std::auto_ptr<MapInformations> makeMap(QPoint size, RSID defaultRSID);
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

    void repaintBackground();

    void openMapInfoDialog();
    void setMap(MapPtr);

    private slots:

    void onUpdate();

    signals:

    void mapClicked(QPoint newCase);
    void highlightedCaseChanged(QPoint newCase);
    void mapAreaSelected(MapArea area);

    protected:

    virtual void mousePressEvent (QMouseEvent* event);
    virtual void mouseReleaseEvent (QMouseEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void scrollContentsBy (int dx, int dy);

    virtual void leaveEvent (QEvent *event);
    virtual void enterEvent (QEvent *event);


    private:

    void drawBloc(QPoint casePos, RSID id, const QColor& hue= QColor(255,255,255));
    void drawBloc(int caseX, int caseY, RSID id, const QColor& hue= QColor(255,255,255));
    void drawBlockHighlight(const QPoint& casePos, const QColor& color, float width);
    void drawBlockHighlight(int x, int y, const QColor& color, float width, bool noDelete=false);
    void drawBlockBox(QPoint casePos, QPoint caseEndPos, const QColor& color, float width);
    void drawBlockBox(QPointF casePos, QPointF caseEndPos, const QColor& color, float width);
    void drawBlockHighlight(const QPointF& casePos, const QColor& color, float width);


    QPoint posToMap(int x, int y) { return posToMap(QPoint(x,y)); }
    QPoint posToMap(QPoint pos);

    bool pixelCanBeSeen(QPoint pixel) const;
    bool caseCanBeSeen(QPoint casePos) const;
    bool pixelCanBeSeen(int x,int y) const;
    bool caseCanBeSeen(int x,int y) const;

    bool m_multiSelectionEnabled;
    bool m_mouseDown;
    QPoint m_mouseDownPos;
    QPoint m_mouseUpPos;

    QPoint m_highlightedCase;
    bool m_mouseInside;

    QPoint m_selectedCase;

    bool m_highlightEnabled;

    QMap<RSID, RSID> concatenateRessources(const QMap<RSID, QString>& other);


    std::auto_ptr<MapInformations> m_map;

    RSID m_loadedRessources;

    QMap<RSID, QPixmap*> m_ressources;
    QMap<QString, RSID> m_loadedRessourcesName;

    QGraphicsScene m_scene;

    QGraphicsRectItem* m_highLightRect;
    QGraphicsRectItem* m_selectedRect;

    QTimer* m_timer;
    QTimer* m_timerBG;

    bool m_repaintBG;

    QList<QGraphicsRectItem*> m_tempItems;
    void clearTemporaryItems();

};

#endif // DEF_MAPWIDGET
