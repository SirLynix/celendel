#ifndef DEF_MAPWIDGET
#define DEF_MAPWIDGET

#include "../Shared/Constants.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class QTimer;
class MapEditor;
class QGraphicsRectItem;
class Flare;

void swp (int& x1, int& x2);

struct MapArea //Represent a area of the map, defined by two corners.
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

    public:

    MapWidget(QWidget* Parent, const double FPS = 1.f);
    ~MapWidget();

    //Unload all ressources
    void clearRessources();

    //The 'FPS' only concerns the background sprites
    void setFPS(double FPS);

    const MapInformations* getMap() const { return m_map.get(); }
    const QMap<QString, RSID>& loadedRessources() const { return m_loadedRessourcesName; }

    //Enable/disable the mouse highlight when overing a case
    bool isHightlighEnabled() const { return m_highlightEnabled; }
    void setHighlight(bool highlight);

    void setMultiSelectionEnabled(bool d) { m_multiSelectionEnabled=d; }
    bool isMultiSelectionEnabled() const { return m_multiSelectionEnabled; }

    //Load a map from a filename, return true on error
    bool setMap(const QString& fileName) { bool b=(m_map=loadMap(fileName)).get()==NULL;adjustSize(); return b; }

    /// Statics map loaders/makers
    static std::auto_ptr<MapInformations> loadMap(QString fileName);
    static std::auto_ptr<MapInformations> makeMap(QPoint size, RSID defaultRSID);
    static bool saveMap(const MapInformations*, QString fileName);

    static void saveCompressedMap(QDataStream& out, const MapInformations& map, const QMap<QString, RSID>& rss);
    static bool saveCompressedMap(QString fileName, const MapInformations& map, const QMap<QString, RSID>& rss);
    bool static loadCompressedMap(QDataStream& in, MapInformations& map, QMap<QString, RSID>& rss);
    bool static loadCompressedMap(QString fileName, MapInformations& map, QMap<QString, RSID>& rss);

    //Save the map under the 'fileName' file. True on error.
    bool saveMap(const QString& fileName) const;
    //Same with the map matrix.
    bool saveMapMatrix(const QString& fileName) const;

    RSID loadRessource(QString fileName); //Return 0, if the image is already loaded it returns it RSID.
    QList<RSID> loadRessourcesPack(QString fileName); //Return the RSID of succefully loaded ressources. Will free previous ressources.
    bool loadRessource(QString fileName, RSID id); //Force to load the fileName image with the id RSID. True on error.


    bool saveRessources(QString fileName); //Save the loaded ressources in a ressource pack. True on error.

    //Return 0 if not found.
    RSID ressourceRSID(const QString& fileName) const;

    bool isRSIDUsed(RSID id) const { return m_ressources.contains(id); }

    bool isMapValid() const;

    QPoint selectedCase() const { return m_selectedCase; }

    public slots:

    //When called, the background will be repainted at next screen update.
    void repaintBackground();

    //Show a blinking colored square
    void flare(QPoint,CLID);
    void flare(QPoint,QColor);

    void openMapInfoDialog();
    void setMap(MapPtr);

    //Make the internal ressources map like the new one - old unused sprites will be removed, new ones loaded, and the old one still in use will be moved.
    void updateRessources(const QMap<QString, RSID>& list);

    private slots:

    void onUpdate();

    signals:

    void mapClicked(QPoint newCase);
    void highlightedCaseChanged(QPoint newCase);
    void mapAreaSelected(MapArea area);

    void ressourceLoadingProgress(int curr, int max);

    protected:

    virtual void mousePressEvent (QMouseEvent* event);
    virtual void mouseReleaseEvent (QMouseEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void scrollContentsBy (int dx, int dy);

    virtual void leaveEvent (QEvent *event);
    virtual void enterEvent (QEvent *event);


    private:

    ///Draw blocks functions - draw a case on the screen
    void drawBloc(QPoint casePos, RSID id, const QColor& hue=QColor(255,255,255), qreal hueStrenght=0.75f);
    void drawBloc(int caseX, int caseY, RSID id, const QColor& hue= QColor(255,255,255), qreal hueStrenght=0.75f);
    void drawBlockHighlight(const QPoint& casePos, const QColor& color, float width);
    void drawBlockHighlight(int x, int y, const QColor& color, float width, bool noDelete=false); //If noDelete == false, the block will be deleted at next loop. Ex : mouse highlight
    void drawBlockBox(QPoint casePos, QPoint caseEndPos, const QColor& color, float width);
    void drawBlockBox(QPointF casePos, QPointF caseEndPos, const QColor& color, float width);
    void drawBlockHighlight(const QPointF& casePos, const QColor& color, float width);


    QPoint posToMap(int xi, int yi) { return posToMap(QPoint(xi,yi)); }
    QPoint posToMap(QPoint pos);

    //Delete unused flares items
    void cleanFlares();

    bool m_multiSelectionEnabled;
    bool m_mouseDown;
    QPoint m_mouseDownPos;
    QPoint m_mouseUpPos;

    QPoint m_highlightedCase;
    bool m_mouseInside;

    QPoint m_selectedCase;

    bool m_highlightEnabled;

    std::auto_ptr<MapInformations> m_map;

    RSID m_loadedRessources;

    QMap<RSID, QPixmap*> m_ressources;
    QMap<QString, RSID> m_loadedRessourcesName;

    QGraphicsScene m_scene;

    QGraphicsRectItem* m_highLightRect;
    QGraphicsRectItem* m_selectedRect;

    QTimer* m_timer;
    QTimer* m_timerBG;

    bool m_repaintBG; //If true, the background will be repainted at next screen update.

    double m_FPS;

    QList<QGraphicsRectItem*> m_tempItems; //Temporary items, like highlight blocks.
    void clearTemporaryItems(); //Remove the temporary items.

    QList<Flare*> m_flares;

};

#endif // DEF_MAPWIDGET
