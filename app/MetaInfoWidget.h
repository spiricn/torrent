#ifndef METAINFOVIEW
#define METAINFOVIEW

#include <bt/MetaInfo.h>

#include <QWidget>

#include "ui_MetaInfoWidget.h"

class MetaInfoWidget: public QWidget{
    Q_OBJECT

public:
    MetaInfoWidget(QWidget* parent);

    void display(const bt::MetaInfo& metaInfo);

private:
    Ui::MetaInfoWidget* mUi;
};

#endif // METAINFOVIEW

