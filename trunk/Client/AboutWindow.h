#ifndef DEF_ABOUTWINDOW
#define DEF_ABOUTWINDOW

#include <QDialog>

class AboutWindow : public QDialog
{
    Q_OBJECT
    public:
        AboutWindow(const QString& text, QWidget* parent=0);

    private:
};

#endif // DEF_ABOUTWINDOW
