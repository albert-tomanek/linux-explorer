#pragma once

#include <QList>
#include <QPointer>
#include <QWidget>

#include <KFileItem>

class QLabel;
namespace KIO { class PreviewJob; }

// Win7's preview pane, whose rendering is the desktop's own, so anything it can
// preview appears here, falling back to the item's icon where it cannot
class PreviewPane : public QWidget {
    Q_OBJECT

public:
    explicit PreviewPane(QWidget *parent = nullptr);
    ~PreviewPane() override;

    // Anything but a single item gets a placeholder, as in Windows
    void setItems(const QList<KFileItem> &items);

private:
    void showPlaceholder(const QString &text);

    // Or arrowing through a folder of photos leaves a thumbnailer running per
    // item passed over
    void cancelPreview();

    QLabel *m_image = nullptr;
    QLabel *m_name = nullptr;
    QLabel *m_detail = nullptr;

    // So a job landing after the selection moved on can be discarded
    QUrl m_pending;

    QPointer<KIO::PreviewJob> m_job;
};
