#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolButton>
#include <QDebug>
#include "QHexWindow.h"

QHexWindow::QHexWindow(QWidget *parent) : QWidget(parent),
                                           isMousePressed(false),
                                           mIntelHexFile(new QFile)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->setStyleSheet(QLatin1String("QWidget{                             \
        font-family                 : Roboto;                               \
        font-size                   : 10pt;                                 \
        font-style                  : normal;                               \
        font-weight                 : bold;                                 \
        background-color: rgb(15, 15, 15);                                  \
    }                                                                       \
    QLabel{                                                                 \
        color				: rgb(159, 162, 167);                           \
        font-weight         : bold;                                         \
        background-color	: rgb(35,45,54);                                \
        qproperty-alignment	: AlignMiddle;                                  \
        padding         	: 0px 0px 0px 0px;                              \
    }                                                                       \
    QToolButton{                                                            \
        color				: rgb(159, 162, 167);                           \
        font-weight         : bold;                                         \
        background-color	: rgb(35,45,54);                                \
        height              : 30px;                                         \
        padding         	: 0px 0px 0px 0px;                              \
    }                                                                       \
    QToolButton:pressed {                                                   \
          background-color: rgb(0, 176, 156);                               \
      }                                                                     \
    QTextEdit{                                                              \
        background-color            : rgb(16, 29, 37);                      \
        selection-background-color  : rgb(0, 176, 156);                     \
        color                       : rgb(0, 176, 156);                     \
        border                      : 1px solid rgb(35, 45, 54);            \
        border-radius               : 0px;                                  \
        padding                     : 10px 10px 10px 10px;                  \
        margin                      : 0px 0px 0px 0px;                      \
    }                                                                       \
    QScrollBar:vertical {                                                   \
        border: 0px solid grey;                                             \
        background: rgb(15, 15, 15);                                        \
        width: 15px;                                                        \
        margin: 20px 0px 20px 0px;                                          \
        }                                                                   \
    QScrollBar::sub-page:vertical {                                         \
        background: rgb(15, 15, 15);                                        \
        }                                                                   \
                                                                            \
    QScrollBar::add-page:vertical {                                         \
        background: rgb(15, 15, 15);                                        \
        }                                                                   \
    QScrollBar::handle:vertical {                                           \
        background: rgb(45, 45, 45);                                        \
        min-height: 20px;                                                   \
        }                                                                   \
    QScrollBar::add-line:vertical {                                         \
        border: 0px solid grey;                                             \
        background: rgb(25, 25, 25);                                        \
        height: 20px;                                                       \
        subcontrol-position: bottom;                                        \
        subcontrol-origin: margin;                                          \
        }                                                                   \
    QScrollBar::sub-line:vertical {                                         \
        border: 0px solid grey;                                             \
        background: rgb(25, 25, 25);                                        \
        height: 20px;                                                       \
        subcontrol-position: top;                                           \
        subcontrol-origin: margin;                                          \
        }                                                                   \
                                                                            \
        QScrollBar:vertical {                                               \
            border: 0px solid grey;                                         \
            background: #2E2F30;                                            \
            width: 15px;                                                    \
            margin: 20px 0 20px 0;                                          \
        }                                                                   \
        QScrollBar::handle:vertical {                                       \
            background: rgb(0, 176, 156);                                   \
            min-height: 20px;                                               \
        }                                                                   \
        QScrollBar::add-line:vertical {                                     \
            border: 0px solid rgb(0, 176, 156);                             \
            background: rgb(0, 176, 156);                                   \
            height: 20px;                                                   \
            subcontrol-position: bottom;                                    \
            subcontrol-origin: margin;                                      \
        }                                                                   \
                                                                            \
        QScrollBar::sub-line:vertical {                                     \
            border: 0px solid rgb(0, 176, 156);                             \
            background: rgb(0, 176, 156);                                   \
            height: 20px;                                                   \
            subcontrol-position: top;                                       \
            subcontrol-origin: margin;                                      \
        }                                                                   \
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {    \
            border: 0px solid rgb(0, 176, 156);                             \
            width: 11px;                                                    \
            height: 14px;                                                   \
            background: #2E2F30;                                            \
        }                                                                   \
                                                                            \
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {      \
            background: none;                                               \
        }                                                                   \
                                                                            \
                                                                            \
    QPushButton{                                                            \
        text-align      			: center;                               \
        color                       : rgb(35,45,54);                        \
        background-color            : rgb(0, 176, 156);                     \
        border-radius               : 1px;                                  \
        margin                      : 0px 0px 0px 0px;                      \
        padding                     : 0px 0px 0px 0px;                      \
        border-style                : solid;                                \
        border                      : 1px solid rgb(0, 176, 156);           \
        border-radius               : 0px;                                  \
        width                       : 80px;                                 \
        height                      : 30px;                                 \
    }                                                                       \
    QPushButton:pressed{                                                    \
        color                       : rgb(0, 176, 156);                     \
        background-color            : rgb(35,45,54);                        \
    }                                                                       \
                                                                            \
    QPushButton:disabled{                                                   \
        background-color: rgba(255, 255, 255, 37%);                         \
    }"));

    QFont font("Consolas", 11, QFont::Black, false);
    font.setBold(true);
    QFontMetrics fontMetrics(font);

    formatAddress.setFont(font);
    formatAddress.setFontWeight(QFont::Bold);
    formatAddress.setFontLetterSpacing(140);
    formatAddress.setForeground(QBrush(QColor(140, 120, 240)));

    formatHex.setFont(font);
    formatHex.setFontWeight(QFont::Bold);
    formatHex.setFontLetterSpacing(110);
    formatHex.setForeground(QBrush(QColor(0, 176, 156)));

    formatHexAlternate.setFont(font);
    formatHexAlternate.setFontWeight(QFont::Bold);
    formatHexAlternate.setFontLetterSpacing(110);
    formatHexAlternate.setForeground(QBrush(QColor(190, 190, 190)));

    formatASCII.setFont(font);
    formatASCII.setFontWeight(QFont::Bold);
    formatASCII.setFontLetterSpacing(120);
    formatASCII.setForeground(QBrush(QColor(200, 200, 200)));

    mAddressAreaTop = new QTextEdit;
    mAddressAreaTop->setContentsMargins(0, 0, 0, 0);
    mAddressAreaTop->setFixedSize(710,32);
    mAddressAreaTop->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    mAddressAreaTop->setReadOnly(true);
    mAddressAreaTop->setStyleSheet("padding-left : 15px;padding-top : 0px;padding-bottom : 0px;");

    mAddressAreaLeft = new QTextEdit;
    mAddressAreaLeft->setContentsMargins(0, 0, 0, 0);
    mAddressAreaLeft->setFixedWidth(75);
    mAddressAreaLeft->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    mAddressAreaLeft->setReadOnly(true);
    mAddressAreaLeft->setStyleSheet("padding-top : 0px;padding-bottom : 0px;");
    mAddressAreaLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mAddressAreaLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mHexArea = new QTextEdit;
    mHexArea->setObjectName("mHexArea");
    mHexArea->setContentsMargins(0, 0, 0, 0);
    mHexArea->setFixedWidth(445);
    mHexArea->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    mHexArea->setReadOnly(true);
    mHexArea->setStyleSheet("padding-top : 0px;padding-bottom : 0px;");
    mHexArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mHexArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mASCIIArea = new QTextEdit;
    mASCIIArea->setObjectName("mASCIIArea");
    mASCIIArea->setContentsMargins(0, 0, 0, 0);
    mASCIIArea->setFixedWidth(175);
    mASCIIArea->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    mASCIIArea->setReadOnly(true);
    mASCIIArea->setStyleSheet("padding-top : 0px;padding-bottom : 0px;");
    mASCIIArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mASCIIArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mFileStatistics = new QLabel;
    mFileStatistics->setAlignment(Qt::AlignVCenter);
    mFileStatistics->setContentsMargins(0, 0, 0, 0);
    mFileStatistics->setFixedHeight(30);
    mFileStatistics->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    mFileStatistics->setStyleSheet("padding-left : 10px; padding-top : 0px; padding-bottom : 0px;");

    mTitleBar = new QLabel(QString("AVR HEX Viewer"));
    mTitleBar->setAlignment(Qt::AlignCenter);
    mTitleBar->setContentsMargins(0, 0, 0, 0);
    mTitleBar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mTitleBar->setFixedSize(653,30);
    mTitleBar->setStyleSheet("padding-left : 10px; padding-top : 0px; padding-bottom : 0px;");

    mButtonMinimize = new QPushButton;
    mButtonMinimize->setFlat(true);
    mButtonMinimize->setIcon(style()->standardIcon(QStyle::QStyle::SP_TitleBarMinButton));
    mButtonMinimize->setFixedSize(24,24);
    mButtonMinimize->setToolTip(tr("Minimize"));

    mButtonClose = new QPushButton;
    mButtonClose->setIcon(style()->standardIcon(QStyle::QStyle::SP_TitleBarCloseButton));
    mButtonClose->setFixedSize(24,24);
    mButtonClose->setToolTip(tr("Close"));

    mSelectButton = new QPushButton("SELECT");
    mSelectButton->setObjectName("mSelectButton");
    mSelectButton->setToolTip(tr("Select *.hex file"));
    mSelectButton->setFlat(true);
    mSelectButton->setFixedSize(80,30);
    mSelectButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    mRefreshButton = new QPushButton("R");
    mRefreshButton->setObjectName("mRefreshButton");
    mRefreshButton->setToolTip(tr("Refresh"));
    mRefreshButton->setFlat(true);
    mRefreshButton->setFixedSize(30,30);
    mRefreshButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mRefreshButton->setStyleSheet("QPushButton{color : rgb(0, 176, 156); background-color : rgb(35,45,54);}"
                                  "QPushButton:pressed{color : rgb(35,45,54); background-color : rgb(0, 176, 156);}");
    mRefreshButton->hide();

    mRightScrollBar = new QScrollBar(Qt::Vertical);

    QHBoxLayout *h1Layout = new QHBoxLayout;
    h1Layout->setSpacing(0);
    h1Layout->setContentsMargins(0,0,0,0);
    h1Layout->addWidget(mTitleBar,0);
    h1Layout->addItem(new QSpacerItem(0,3,QSizePolicy::Expanding,QSizePolicy::Fixed));
    h1Layout->addWidget(mButtonMinimize,0);
    h1Layout->addItem(new QSpacerItem(0,3,QSizePolicy::Expanding,QSizePolicy::Fixed));
    h1Layout->addWidget(mButtonClose,0);
    h1Layout->addItem(new QSpacerItem(0,3,QSizePolicy::Expanding,QSizePolicy::Fixed));

    QHBoxLayout *h2Layout = new QHBoxLayout;
    h2Layout->setSpacing(0);
    h2Layout->setContentsMargins(0,0,0,0);
    h2Layout->addWidget(mAddressAreaLeft,0);
    h2Layout->addWidget(mHexArea,0);
    h2Layout->addWidget(mASCIIArea,0);
    h2Layout->addWidget(mRightScrollBar);
    h2Layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));


    QHBoxLayout *h3Layout = new QHBoxLayout;
    h3Layout->setSpacing(0);
    h3Layout->setContentsMargins(0,0,0,0);
    h3Layout->addWidget(mFileStatistics,1);
    h3Layout->addWidget(mSelectButton,0);
    h3Layout->addWidget(mRefreshButton,0);
    h3Layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Fixed));


    QVBoxLayout *v1Layout = new QVBoxLayout;
    v1Layout->setContentsMargins(0,0,0,0);
    v1Layout->setSpacing(0);
    v1Layout->setMargin(0);
    v1Layout->addLayout(h1Layout);
    v1Layout->addWidget(mAddressAreaTop);
    v1Layout->addLayout(h2Layout);
    v1Layout->addLayout(h3Layout);

    QHBoxLayout *finalLayout = new QHBoxLayout;
    finalLayout->setContentsMargins(0,0,0,0);
    finalLayout->setSpacing(0);
    finalLayout->setMargin(0);
    finalLayout->addLayout(v1Layout);
    finalLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    setLayout(finalLayout);

    QTextCursor curAddressTop = mAddressAreaTop->textCursor();
    curAddressTop.insertText("        00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F          ASCII",formatHexAlternate);

    connect(mButtonMinimize, &QToolButton::clicked, this, &QHexWindow::minimize);
    connect(mButtonClose, &QToolButton::clicked, this, &QHexWindow::close);

    connect(mSelectButton,SIGNAL(clicked()),this,SLOT(selectHexFile()));
    connect(mRefreshButton,SIGNAL(clicked()),this,SLOT(refreshDisplay()));
    connect(mRightScrollBar,&QScrollBar::valueChanged,mAddressAreaLeft->verticalScrollBar(),&QScrollBar::setValue);
    connect(mRightScrollBar,&QScrollBar::valueChanged,mHexArea->verticalScrollBar(),&QScrollBar::setValue);
    connect(mRightScrollBar,SIGNAL(valueChanged(int)),mASCIIArea->verticalScrollBar(),SLOT(setValue(int)));
}


QHexWindow::~QHexWindow()
{
}

void QHexWindow::processFile(const QString &fileName)
{
    mIntelHexAddress.clear();
    mIntelHexData.clear();

    mIntelHexFile->setFileName(fileName);
    if (!mIntelHexFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit fileOpenError();
        return;
    }

    QTextStream inputText(mIntelHexFile);
    QString HEXLine;
    qint32 LineNumber = 0;
    qint8 byteValue;
    quint8 CHKSum;
    qint8 index;
    qint8 recordLength;
    qint32 BaseAddress=0;
    qint32 AddressOffset;
    qint32 AbsoluteAddress;
    RecordType recordType;
    qint8 charStart;
    mTotalBytes = 0;
    mIntelHexData.clear();
    mIntelHexAddress.clear();
    mFileErrors.clear();
    SegmentAddress.exists = false;
    LinearAddress.exists = false;
    foundEOF = false;

    while(!inputText.atEnd())
    {
        HEXLine.clear();
        CHKSum = 0;
        charStart = 1;
        HEXLine = inputText.readLine();
        if (HEXLine.length() > 1)
        {
            LineNumber++;
            if (HEXLine[0] != ':')
            {
                addError(LineNumber,SOF_RECORD_NOT_FOUND);
                charStart = 0;
            }
            if((HEXLine.length() % 2) != charStart)
            {
                addError(LineNumber,ODD_NO_OF_CHARACTERS);
            }

            for(int i=charStart; i<(HEXLine.length()); i=i+2)
            {
                bool ok;
                quint8 hexValue = static_cast<quint8>(HEXLine.mid(i,2).toInt(&ok,16));
                if(ok)
                {
                    CHKSum = CHKSum + hexValue;
                }
                else
                {
                    addError(LineNumber,NON_HEX_CHAR);
                }
            }

            if(CHKSum != 0)
            {
                addError(LineNumber,CHKSUM_MISMATCH);
            }
            recordLength = static_cast<qint8>(HEXLine.mid(charStart,2).toInt(nullptr,16));
            if(HEXLine.length() != 10 + 2*recordLength + charStart)
            {
                addError(LineNumber,LENGTH_MISMATCH);
            }

            recordType = static_cast<RecordType>(HEXLine.mid(charStart+6,2).toInt(nullptr,16));

            switch (recordType)
            {
                case DATA_RECORD:

                    AddressOffset   = HEXLine.mid(charStart+2,4).toInt(nullptr,16);
                    AbsoluteAddress = BaseAddress + AddressOffset;

                    for(index = charStart + 8; index < HEXLine.length()-2; index = index +2)
                    {
                        byteValue = static_cast<qint8>(HEXLine.mid(index,2).toInt(nullptr,16));
                        if(!mIntelHexAddress.contains(AbsoluteAddress))
                        {
                            mIntelHexAddress.append(AbsoluteAddress);
                            mIntelHexData.append(byteValue);
                            mTotalBytes = mTotalBytes + 1;
                        }
                        else if(mIntelHexAddress.value(AbsoluteAddress) != byteValue)
                        {
                             addError(LineNumber,DATA_OVERWRITE);
                        }
                        AbsoluteAddress = AbsoluteAddress + 1;
                    }
                    break;

                case END_OF_FILE_RECORD:
                    if (foundEOF == false)
                    {
                        foundEOF = true;
                    }
                    else
                    {
                        addError(LineNumber,MULTIPLE_EOF);
                    }
                    break;

                case EXTENDED_SEGMENT_ADDRESS:
                    if (recordLength == 2)
                    {
                        BaseAddress = HEXLine.mid(charStart+8,4).toInt(nullptr,16);
                        BaseAddress <<= 4;                                                             // Right shift by 4 bits
                    }
                    else
                    {
                        addError(LineNumber,EXT_SEG_LEN_ERROR);
                    }
                    break;

                case START_SEGMENT_ADDRESS:
                    if (SegmentAddress.exists == true)
                    {
                        addError(LineNumber,MULTIPLE_START_SEG);
                    }
                    if (recordLength != 4)
                    {
                        addError(LineNumber,START_SEG_LEN_ERROR);
                    }
                    if (recordLength == 4 && SegmentAddress.exists == false)
                    {
                        SegmentAddress.exists = true;
                        SegmentAddress.CS = HEXLine.mid(charStart+8,4).toInt(nullptr,16);
                        SegmentAddress.IP = HEXLine.mid(charStart+12,4).toInt(nullptr,16);
                    }
                    break;

                case EXTENDED_LINEAR_ADDRESS:
                    if (recordLength == 2)
                    {
                        long extLinAddress = 0;
                        extLinAddress = HEXLine.mid(charStart+8,4).toInt(nullptr,16);
                        extLinAddress <<= 16;                                                             // Right shift by 16 bits
                        BaseAddress = extLinAddress;
                    }
                    else
                    {
                        addError(LineNumber,EXT_LINER_LEN_ERROR);
                    }
                    break;

                case START_LINEAR_ADDRESS:
                    if (LinearAddress.exists == true)
                    {
                        addError(LineNumber,MULTIPLE_START_LINEAR);
                    }
                    if (recordLength != 4)
                    {
                        addError(LineNumber,START_LINEAR_LEN_ERROR);
                    }
                    if (recordLength == 4 && LinearAddress.exists == false)
                    {
                        LinearAddress.exists = true;
                        LinearAddress.EIP = HEXLine.mid(charStart+8,8).toInt(nullptr,16);
                    }
                    break;

                default:
                    addError(LineNumber,UNKNOWN_TYPE);
                    break;
            }
        }
    }
    mIntelHexFile->close();
    emit updateFirmwareSize(mTotalBytes);
}

void QHexWindow::addError(qint32 LineNumber, ErrorType ErrorInfo)
{
    mFileErrors.insert(LineNumber,ErrorInfo);
}

void QHexWindow::selectHexFile()
{
    QString RootDir    = QCoreApplication::applicationDirPath() ;
    mHexFilename = QFileDialog::getOpenFileName(this, tr("Select HEX File"), RootDir,"HEX files (*.hex *.txt)");
    if (!mHexFilename.isEmpty())
    {
        processFile(mHexFilename);
        displayHex();
        listErrors();
    }
}

void QHexWindow::refreshDisplay()
{
    if (!mHexFilename.isEmpty())
    {
        processFile(mHexFilename);
        displayHex();
        listErrors();
    }
}

void QHexWindow::displayHex()
{
    int startAddress;
    int endAddress;
    bool flag = false;

    startAddress    = mIntelHexAddress.first();
    endAddress      = mIntelHexAddress.last();

    quint8 HEXValue;

    QString AddressLine = QString("");
    QString HEXLine     = QString("");
    QString ASCIILine   = QString("");

    mASCIIArea->clear();
    mHexArea->clear();
    mAddressAreaLeft->clear();

    QTextCursor curAddress = mAddressAreaLeft->textCursor();
    QTextCursor curHex = mHexArea->textCursor();
    QTextCursor curASCII = mASCIIArea->textCursor();

    for (int i = startAddress; i < endAddress; i = i + 16)
    {
        AddressLine = QString("%1").arg(i,5,16,QLatin1Char('0')).toUpper();
        ASCIILine   = "";
        HEXLine     = "";
        for (int j=0;j<16;j++)
        {
            int k = mIntelHexAddress.indexOf(i+j);
            if(k!=-1)
            {
                HEXValue = static_cast<quint8>(mIntelHexData.at(k));
            }
            else
            {
                HEXValue = 0;
            }
            HEXLine = HEXLine + ' ' + QString("%1").arg(HEXValue,2,16,QLatin1Char('0')).toUpper();

            if(isprint(HEXValue))       //if(hexValue >31 && hexValue < 127)
            {
                ASCIILine = ASCIILine + static_cast<qint8>(HEXValue);
            }
            else
            {
                ASCIILine = ASCIILine + '.';
            }
        }

        HEXLine.remove(0,1);
        AddressLine.append('\n');
        HEXLine.append('\n');
        ASCIILine.append('\n');

        if(flag)
        {
            curHex.insertText(HEXLine,formatHex);
            curASCII.insertText(ASCIILine,formatHex);
            curAddress.insertText(AddressLine,formatHex);
        }
        else
        {
            curHex.insertText(HEXLine,formatHexAlternate);
            curASCII.insertText(ASCIILine,formatHexAlternate);
            curAddress.insertText(AddressLine,formatHexAlternate);
        }

        flag = not flag;
    }

    mRefreshButton->show();
    mRightScrollBar->setMaximum(mAddressAreaLeft->verticalScrollBar()->maximum());
    QString FileStatistics("%1            Error(s) : %2                         Size : %3 Bytes");
    FileStatistics = FileStatistics.arg(mHexFilename.section('/', -1));
    if(mFileErrors.count()==0)
    {
       FileStatistics = FileStatistics.arg(QString("NONE"));
    }
    else
    {
        FileStatistics = FileStatistics.arg(mFileErrors.count());
    }
    FileStatistics = FileStatistics.arg(mTotalBytes);
    mFileStatistics->setText(FileStatistics);

}

void QHexWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    painter.setRenderHint(QPainter::Antialiasing,true);
}

void QHexWindow::listErrors()
{
    if(mFileErrors.size()==0)
    {
        qDebug() << Q_FUNC_INFO << "No Errors Found";
    }
    else
    {
        qDebug() << "Total Errors : " << mFileErrors.size();
        QMapIterator<qint32,ErrorType> i(mFileErrors);
        while (i.hasNext())
        {
            i.next();
            switch(i.value())
            {
                case SOF_RECORD_NOT_FOUND:
                    qDebug() << i.key() << " : SOF Not found";
                    break;
                case ODD_NO_OF_CHARACTERS:
                    qDebug()  << i.key() << " : ODD number of characters";
                    break;
                case CHKSUM_MISMATCH:
                    qDebug()  << i.key() << " : CHKSUM mismatch";
                    break;
                case LENGTH_MISMATCH:
                    qDebug()  << i.key() << " : Length mismatch";
                    break;
                case DATA_OVERWRITE:
                    qDebug()  << i.key() << " : Data overwrite";
                    break;
                case MULTIPLE_EOF:
                    qDebug()  << i.key() << " : Multiple EOF";
                    break;
                case EXT_SEG_LEN_ERROR:
                    qDebug()  << i.key() << " : Ex. seg. length Error";
                    break;
                case START_SEG_LEN_ERROR:
                    qDebug()  << i.key() << " : St. seg. length Error";
                    break;
                case EXT_LINER_LEN_ERROR:
                    qDebug()  << i.key() << " : Ex. linear length Error";
                    break;
                case START_LINEAR_LEN_ERROR:
                    qDebug()  << i.key() << " : St. linear length Error";
                    break;
                case MULTIPLE_START_SEG:
                    qDebug()  << i.key() << " : Multiple Start Seg. address";
                    break;
                case MULTIPLE_START_LINEAR:
                    qDebug()  << i.key() << " : Multiple Start linear address";
                    break;
                case NON_HEX_CHAR:
                    qDebug()  << i.key() << " : Multiple Start linear address";
                    break;
                case UNKNOWN_TYPE:
                    qDebug()  << i.key() << " : Unknown record type";
                    break;
            }
        }
    }
}

void QHexWindow::minimize()
{
    showMinimized();
}
void QHexWindow::close()
{
    QTimer::singleShot(100 /*ms*/, qApp, &QCoreApplication::quit);
    //connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()), Qt::QueuedConnection);
    //QObject::connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
}

void QHexWindow::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (child!=mTitleBar)
    {
        return;
    }
    isMousePressed = true;
    mStartPos = event->pos();
}

void QHexWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePressed)
    {
        QPoint deltaPos = event->pos() - mStartPos;
        this->move(this->pos()+deltaPos);
    }
}

void QHexWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (child!=mTitleBar)
    {
        return;
    }
    isMousePressed = false;
}

QSize QHexWindow::sizeHint() const
{
    return QSize(710, 712);
}

QSize QHexWindow::minimumSizeHint() const
{
    return QSize(710, 712);
}
