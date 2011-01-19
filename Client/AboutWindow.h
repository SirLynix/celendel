#ifndef DEF_ABOUTWINDOW
#define DEF_ABOUTWINDOW

#include <QDialog>

class AboutWindow : public QDialog
{
    Q_OBJECT
    public:
        AboutWindow(const QString& text, QWidget* parent=0);

        static int open(const QString& text, QWidget* parent=0);
};

#endif // DEF_ABOUTWINDOW
