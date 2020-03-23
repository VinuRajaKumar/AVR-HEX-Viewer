#ifndef Q_DOWNLOAD_WIDGET
#define Q_DOWNLOAD_WIDGET

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QFont>
#include <QFontInfo>
#include <QFontDatabase>
#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QSlider>
#include <QFileDialog>
#include <QDateTime>
#include <QTextEdit>
#include <QStyleOption>
#include <QPainter>
#include <QScrollBar>
#include <QToolButton>
#include <QMouseEvent>
#include <QTimer>
#include <QLineEdit>
#include <QAction>

class QHexWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QHexWindow(QWidget *parent = nullptr);
    ~QHexWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void onFileSelected(QString);
    void fileOpenError(void);
    void updateFirmwareSize(int);

public slots:
    void displayHex();
    void refreshDisplay();
    void showSearchBox();

private slots:
    void selectHexFile();
    void highlightString();
    void minimize();
    void close();
    void handleScroll(int i);

private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
private:
    QString mHexFilename;
    QColor mThemeColor;
    QTextEdit *mHexArea;
    QTextEdit *mASCIIArea;
    QTextEdit *mAddressAreaTop;
    QTextEdit *mAddressAreaLeft;
    QLabel *mFileStatistics;
    QLabel *mTitleBar;
    QPushButton *mSelectButton;
    QPushButton *mRefreshButton;
    QScrollBar *mRightScrollBar;
    QPushButton *mButtonMinimize;
    QPushButton *mButtonClose;

    QWidget *mSearchBar;
    QLineEdit *mSearchBox,*mSearchResult;
    QPushButton *mSearchNext, *mSearchPrev, *mSearchClose;

    int mXo, mYo;
    QPoint mStartPos;
    bool isMousePressed;
    bool isSearchBoxShown;
    QString mDocumentText;
    QTextCharFormat mTextFormat,mTextAlternateFormat;
    QTextCharFormat mSearchHighlightFormat;

    enum RecordType
    {
        DATA_RECORD,
        END_OF_FILE_RECORD,
        EXTENDED_SEGMENT_ADDRESS,
        START_SEGMENT_ADDRESS,
        EXTENDED_LINEAR_ADDRESS,
        START_LINEAR_ADDRESS,
        NO_OF_RECORD_TYPES
    };

    enum ErrorType
    {
        SOF_RECORD_NOT_FOUND,
        ODD_NO_OF_CHARACTERS,
        CHKSUM_MISMATCH,
        LENGTH_MISMATCH,
        DATA_OVERWRITE,
        MULTIPLE_EOF,
        EXT_SEG_LEN_ERROR,
        START_SEG_LEN_ERROR,
        EXT_LINER_LEN_ERROR,
        START_LINEAR_LEN_ERROR,
        MULTIPLE_START_SEG,
        MULTIPLE_START_LINEAR,
        NON_HEX_CHAR,
        UNKNOWN_TYPE
    };

    QFile                           *mIntelHexFile;
    QMultiMap<qint32,ErrorType>     mFileErrors;
    QByteArray                      mIntelHexData;
    QList<qint32>                   mIntelHexAddress;

    struct
    {
        int  CS;
        int  IP;
        bool exists;
    } SegmentAddress;

    struct
    {
        int   EIP;
        bool  exists;
    } LinearAddress;

    bool foundEOF;

    qint32 mTotalBytes;

private:
    void addError(qint32 LineNumber, ErrorType ErrorInfo);
    void processFile(const QString &Filename);
    void listErrors(void);
};

#endif // Q_DOWNLOAD_WIDGET
