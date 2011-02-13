#ifndef DEF_MAPEDITOR
#define DEF_MAPEDITOR

#include <QMainWindow>
#include "MapWidget.h"

class QSpinBox;
class QLabel;
class QTableWidget;
class QPushButton;
class QListWidget;
class QColorViewer;
class QModelIndex;

class MapEditor : public QMainWindow
{
    Q_OBJECT
    public:
        MapEditor(QWidget* parent = NULL, const QString& map = QString(), const QString& ressourceList = QString());

        void setSendingButtonEnabled(bool b);
        bool isSendingButtonEnabled();

        bool needSave() const;

        bool isMapValid() const;

    public slots:
        bool loadMap(QString map = QString(), QString ressPack = QString());
        bool saveMap();
        bool saveMapAs(QString fileName = QString());

        bool newMap();

        bool saveRessourcePackAs(QString fileName=QString());
        bool saveRessourcePack();

        bool replaceRSID();
        bool replaceRSID(RSID before, RSID after);

        bool saveAll();
        bool saveAllAs(QString mapName=QString(), QString ressName=QString());

        void copy();
        void paste(QPoint pos);
        void paste();

    private slots:

        void changeCasePos(QPoint newCase);
        void changeSelectedArea(MapArea newArea);
        void changeCurrentCase(QPoint newCase);
        void refreshMapObjectsList(QPoint newCase);
        void refreshObjetsList();
        void refreshGlobalObjetsList();
        bool selectMapItem(int index);
        bool selectMapItem(const QModelIndex& index);

        void addMapObject();

        void changeCurrentCaseRSID(int n);

        void updateRessourcesList();

        void btnMapSend();

        void modifyRssMngr();
        void addRssMngr();

        void modified();
        void unmodified();

        void resetCopy();

        void enableMapSystem(bool b);

        bool createEmptyMap(QPoint size, const QString& name, const QString& ressPack, RSID defaultRSID);

    signals:
            void mapSendingRequested(const MapInformations* const);

    protected:
        virtual void closeEvent (QCloseEvent *event);

    private:

        bool saveCheck(); // Returns true if the user choosed to abort. False if the user agreed to continue (map saved or not, it doesn't matter)

        bool m_needSave;

        QPushButton* m_sendingBtn;

        MapWidgetScroll* m_mapWidgetScroll;

        QSpinBox* m_mapSizeX;
        QSpinBox* m_mapSizeY;

        QString m_mapName;
        QString m_ressourcePackName;

        QLabel *m_mapNameLabel;

        QListWidget *m_mapItemList;

        QSpinBox* m_mapItemRSID;
        QColorViewer* m_mapItemColorViewer;
        QLabel* m_mapItemName;
        QLabel* m_mapItemPos;
        int m_currentItemIndex;

        QListWidget *m_mapCaseItemList;
        QPushButton *m_addItem;

        QTableWidget* m_rsMngrWidget;
        QPushButton* m_rsMngrEdit;
        QPushButton* m_rsMngrAdd;

        QLabel* m_selectedCaseLabel;
        QSpinBox* m_selectedCaseRSID;
        QPoint m_selectedCase;
        MapArea m_selectedArea;
        MapArea m_copyArea;
        bool m_copyReady;

        QLabel* m_hoveredCaseLabel;
};

#endif // DEF_MAPEDITOR
