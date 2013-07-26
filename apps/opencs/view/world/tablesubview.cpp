
#include "tablesubview.hpp"

#include <QVBoxLayout>

#include "../../model/doc/document.hpp"

#include "table.hpp"
#include "tablebottombox.hpp"
#include "creator.hpp"

CSVWorld::TableSubView::TableSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document,
    Creator *creator)
: SubView (id)
{
    bool createAndDelete = creator!=0;
    delete creator;

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setContentsMargins (QMargins (0, 0, 0, 0));

    layout->addWidget (
        mTable = new Table (id, document.getData(), document.getUndoStack(), createAndDelete), 2);

    layout->addWidget (mBottom = new TableBottomBox (this), 0);

    QWidget *widget = new QWidget;

    widget->setLayout (layout);

    setWidget (widget);

    connect (mTable, SIGNAL (editRequest (int)), this, SLOT (editRequest (int)));

    connect (mTable, SIGNAL (selectionSizeChanged (int)),
        mBottom, SLOT (selectionSizeChanged (int)));
    connect (mTable, SIGNAL (tableSizeChanged (int, int, int)),
        mBottom, SLOT (tableSizeChanged (int, int, int)));

    mTable->tableSizeUpdate();
    mTable->selectionSizeUpdate();
}

void CSVWorld::TableSubView::setEditLock (bool locked)
{
    mTable->setEditLock (locked);
}

void CSVWorld::TableSubView::editRequest (int row)
{
    focusId (mTable->getUniversalId (row));
}

void CSVWorld::TableSubView::updateEditorSetting(const QString &settingName, const QString &settingValue)
{
    mTable->updateEditorSetting(settingName, settingValue);
}

void CSVWorld::TableSubView::setStatusBar (bool show)
{
    mBottom->setStatusBar (show);
}