#include <QDebug>
#include <bt/MultipleFileInfo.h>

#include "MetaInfoWidget.h"


MetaInfoWidget::MetaInfoWidget(QWidget* parent) : QWidget(parent), mUi(new Ui::MetaInfoWidget){
    mUi->setupUi(this);
}


void MetaInfoWidget::display(const bt::MetaInfo& metaInfo){
    mUi->file->setText( metaInfo.getFilePath() );

    mUi->announce->setText( metaInfo.getAnnounce() );

    mUi->author->setText( metaInfo.getAuthor() );

    mUi->comment->setText( metaInfo.getComment() );

    mUi->creationDate->setText( metaInfo.getCreationDate().toString("d/M/yy - h:m:s:z") );

    mUi->encoding->setText( metaInfo.getEncoding() );

    mUi->private_2->setText(metaInfo.getInfo()->isPrivate() ? "True" : "False");

    mUi->pieceLength->setText(QString::number(metaInfo.getInfo()->getPieceLength()));

    mUi->mode->setText(metaInfo.getInfo()->getMode() == bt::Info::eMODE_MULTIPLE_FILE ? "multiple-file" : "single-file");

    if(metaInfo.getInfo()->getMode() == bt::Info::eMODE_MULTIPLE_FILE){
        const bt::MultipleFileInfo* info = dynamic_cast<const bt::MultipleFileInfo*>(metaInfo.getInfo());

        for(QList<bt::MultipleFileInfo::FileEntry>::const_iterator iter=info->getFiles().cbegin(); iter!=info->getFiles().cend(); iter++){
            QTreeWidgetItem* treeItem = new QTreeWidgetItem(mUi->files);

            const bt::MultipleFileInfo::FileEntry entry = *iter;

            treeItem->setText(0, entry.path);
            treeItem->setText(1, QString::number(entry.length));
            treeItem->setText(2, entry.md5sum);

            mUi->files->addTopLevelItem(treeItem);
        }
    }
}

