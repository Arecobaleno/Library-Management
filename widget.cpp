#include "ui_widget.h"
#include "searchbar.h"
#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(320,90,1024,725);
    setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setStyleSheet("background-color:#99ccff;");

    //添加最小化按钮
    minimizeBtn=new ToolButton(this);
    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    minimizeBtn->setIcon(minPix);
    minimizeBtn->setStyleSheet("background-color:transparent;");
    minimizeBtn->setGeometry(this->width()-2*40,0,40,40);
    connect(minimizeBtn,SIGNAL(clicked()),this,SLOT(showMinimized()));
    minimizeBtn->show();

    //添加关闭按钮
    closeBtn=new ToolButton(this);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    closeBtn->setGeometry(this->width()-40,0,40,40);
    closeBtn->setStyleSheet("background-color:transparent;");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));
    closeBtn->show();

    //添加搜索条
    searchBar=new SearchBar(this);

    //添加消息中心按钮
    messageCentreBtn= new ToolButton(this);
    messageCentreBtn->setIcon(QPixmap(":/Images/Icons/Message.png").scaled(40,40,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    messageCentreBtn->setStyleSheet("background-color:transparent;");
    messageCentreBtn->setGeometry(this->width()-3*40,0,40,40);
    messageCentreBtn->show();

    //添加登录按钮
    loginBtn=new ToolButton(this);
    loginBtn->setText("登录");
    loginBtn->setFont(QFont("幼圆"));
    loginBtn->setGeometry(this->width()-4*40,0,40,40);
    loginBtn->setStyleSheet("background-color:transparent;");

    //添加图书概览按钮
    overviewBtn=new ToolButton(this);
    overviewBtn->setIcon(QPixmap(":/Images/Icons/OverviewButton.png"));
    overviewBtn->setIconSize(QSize(120,80));
    overviewBtn->setStyleSheet("background-color:transparent; border:none");
    overviewBtn->setGeometry(10,this->height()/6+50,120,90);

    //添加图书管理按钮
    bookManagementBtn=new ToolButton(this);
    bookManagementBtn->setIcon(QPixmap(":/Images/Icons/BooksManagementButton.png"));
    bookManagementBtn->setIconSize(QSize(120,80));
    bookManagementBtn->setStyleSheet("background-color:transparent; border:none");
    bookManagementBtn->setGeometry(10,this->height()/6+50+90*5,120,90);

    //添加读者管理按钮
    readerManagementBtn=new ToolButton(this);
    readerManagementBtn->setIcon(QPixmap(":/Images/Icons/ReaderManagementButton.png"));
    readerManagementBtn->setIconSize(QSize(120,80));
    readerManagementBtn->setStyleSheet("background-color:transparent; border:none");
    readerManagementBtn->setGeometry(10,this->height()/6+50+90*4,120,90);

    //添加借书按钮
    borrowBtn=new ToolButton(this);
    borrowBtn->setIcon(QPixmap(":/Images/Icons/BorrowBooksButton.png"));
    borrowBtn->setIconSize(QSize(120,80));
    borrowBtn->setStyleSheet("background-color:transparent; border:none");
    borrowBtn->setGeometry(10,this->height()/6+50+90,120,90);

    //添加还书按钮
    giveBackBtn=new ToolButton(this);
    giveBackBtn->setIcon(QPixmap(":/Images/Icons/ReturnBooksButton.png"));
    giveBackBtn->setIconSize(QSize(120,80));
    giveBackBtn->setStyleSheet("background-color:transparent; border:none");
    giveBackBtn->setGeometry(10,this->height()/6+50+90*2,120,90);

    //添加个人信息按钮
    personalInfoBtn=new ToolButton(this);
    personalInfoBtn->setIcon(QPixmap(":/Images/Icons/PersonalInfoButton.png"));
    personalInfoBtn->setIconSize(QSize(120,80));
    personalInfoBtn->setStyleSheet("background-color:transparent; border:none");
    personalInfoBtn->setGeometry(10,this->height()/6+50+90*3,120,90);

    //添加中央窗口
    bookExhibitionWindow=new BookExhibition(this);
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow=new BookManageWindow(this);
    bookManagementWindow->setVisible(false);
    //关联信号与槽
    connect(bookManagementBtn,SIGNAL(clicked()),this,SLOT(showBookManagementWindow()));
    connect(searchBar->lineEdit,SIGNAL(returnPressed()),this,SLOT(showSearchResult()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    //设置背景图片
    this->setAutoFillBackground(true);
    QPixmap pixmap(":/Images/WidgetBackground.jpg");
    QPixmap fitpixmap=pixmap.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background,fitpixmap);
   // this->setPalette(palette);//图片不搭

    //重新计算按钮的位置
    minimizeBtn->setGeometry(this->width()-2*40,0,40,40);
    closeBtn->setGeometry(this->width()-40,0,40,40);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //改变并存储鼠标形状
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);

        //计算鼠标位置与界面位置的差值
        offset=event->globalPos()-this->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        //计算需要移动到的新位置
        QPoint temp;
        temp=event->globalPos()-offset;

        //移动界面
        move(temp);
    }
}

void Widget::showBookManagementWindow()
{
    this->bookExhibitionWindow->setVisible(false);
    this->bookManagementWindow->show();
}

void Widget::showSearchResult()
{
    this->bookManagementWindow->setVisible(false);
    this->bookExhibitionWindow->show();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //恢复鼠标形状
    QApplication::restoreOverrideCursor();
}

