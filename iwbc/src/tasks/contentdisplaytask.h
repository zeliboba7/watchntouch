#ifndef CONTENTDISPLAYTASK_H
#define CONTENTDISPLAYTASK_H

#include <QWidget>
#include <QStackedLayout>
#include <QImage>
#include <contentdisplay.h>
#include <annotationwidget.h>
#include <contextmenu.h>

class ContentDisplayTask : public QWidget
{
    Q_OBJECT
public:
    explicit ContentDisplayTask(QWidget *parent = 0);

    ContentDisplay * getContentDisplay();
    AnnotationWidget * getAnnotationWidget();
    ContextMenu * getContextMenu();
    virtual ContentType getContentType() = 0;

    virtual void activate();
    virtual void deactivate();

protected:
    ContextMenu * m_contextMenu;
    AnnotationWidget * m_annotationWidget;
    ContentDisplay * m_contentDisplay;

    virtual void setAnnotationWidget(AnnotationWidget * newWidget);
    virtual void setContentDisplay(ContentDisplay * newDisplay);
    virtual void setContextMenu(ContextMenu *newMenu);

    void resizeEvent(QResizeEvent *);

signals:

public slots:
    QImage getTaskScreenshot();

private slots:
    void showContextMenu(QPoint p);

};

#endif // CONTENTDISPLAYTASK_H
