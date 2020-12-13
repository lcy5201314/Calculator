#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clac.h"
#include <QString>
#include <QDebug>
#include <string>
#include "QDebug"
#include <stack>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //清空a，b
    a.clear();
    b.clear();

    //绑定按键0与处理函数
        connect(ui->pushButton_0,&QPushButton::clicked,[=](){btn_logic(0);});
        //绑定按键1与处理函数
        connect(ui->pushButton_1,&QPushButton::clicked,[=](){btn_logic(1);});
        //绑定按键2与处理函数
        connect(ui->pushButton_2,&QPushButton::clicked,[=](){btn_logic(2);});
        //绑定按键3与处理函数
        connect(ui->pushButton_3,&QPushButton::clicked,[=](){btn_logic(3);});
        //绑定按键4与处理函数
        connect(ui->pushButton_4,&QPushButton::clicked,[=](){btn_logic(4);});
        //绑定按键5与处理函数
        connect(ui->pushButton_5,&QPushButton::clicked,[=](){btn_logic(5);});
        //绑定按键6与处理函数
        connect(ui->pushButton_6,&QPushButton::clicked,[=](){btn_logic(6);});
        //绑定按键7与处理函数
        connect(ui->pushButton_7,&QPushButton::clicked,[=](){btn_logic(7);});
        //绑定按键8与处理函数
        connect(ui->pushButton_8,&QPushButton::clicked,[=](){btn_logic(8);});
        //绑定按键9与处理函数
        connect(ui->pushButton_9,&QPushButton::clicked,[=](){btn_logic(9);});
        //绑定按键点与处理函数
        connect(ui->pushButton_dot,&QPushButton::clicked,[=](){btn_logic(0,".");});

        //绑定按键+与处理函数
        connect(ui->pushButton_addition,&QPushButton::clicked,[=](){btn_logic(0,"+");});
        //绑定按键-与处理函数
        connect(ui->pushButton_subtraction,&QPushButton::clicked,[=](){btn_logic(0,"-");});
        //绑定按键*与处理函数
        connect(ui->pushButton_multiplication,&QPushButton::clicked,[=](){btn_logic(0,"*");});
        //绑定按键/与处理函数
        connect(ui->pushButton_division,&QPushButton::clicked,[=](){btn_logic(0,"/");});
        //绑定按键%与处理函数
        connect(ui->pushButton_percent,&QPushButton::clicked,[=](){btn_logic(0,"%");});
        //绑定按键^与处理函数
        connect(ui->pushButton_pow,&QPushButton::clicked,[=](){btn_logic(0,"^");});

        //绑定按键(与处理函数
        connect(ui->pushButton_LeftParenthesis,&QPushButton::clicked,[=](){btn_logic(0,"(");});
        //绑定按键)与处理函数
        connect(ui->pushButton_ClosingParenthesis,&QPushButton::clicked,[=](){btn_logic(0,")");});

        //绑定按键e与处理函数
        connect(ui->pushButton_e,&QPushButton::clicked,[=](){btn_logic(0,"e");});
        //绑定按键根号与处理函数
        connect(ui->pushButton_root,&QPushButton::clicked,[=](){btn_logic(0,"root");});
        //绑定按键1/x与处理函数
        connect(ui->pushButton_fraction,&QPushButton::clicked,[=](){btn_logic(0,"pushButton_fraction");});

        //绑定按键AC与处理函数
        connect(ui->pushButton_clear,&QPushButton::clicked,[=](){
            a.clear();
            b.clear();
            ui->lineEdit->setText(a);
        });

        //绑定按键退格->与处理函数
        connect(ui->pushButton_backspace,&QPushButton::clicked,[=](){
            //删除a.pop
            a.chop(1);
            ui->lineEdit->setText(a);
        });

        //绑定按键=与处理函数
        connect(ui->pushButton_equal,&QPushButton::clicked,[=](){den_logic();});



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::btn_logic(int x , QString i)
{
    if(i != " " )
    {
        if(i == "pushButton_fraction")
        {
            a += "^(-1)";
        }
        else if (i == "root")
        {
            a += "^(0.5)";
        }
        else
        {
            a += i;
        }
    }
    else
    {
        a += QString::number(x);
    }
    ui->lineEdit->setText(a);
}



void MainWindow::den_logic()
{
    string s = a.toStdString();
    a.clear();
    check chk;
    if (chk.valid(s))
        s = chk.getResult();
    else
    {
        calc::writeResult("#");
        a += "输入错误";
    }

    size_t len = s.size();
    calc c;
    for (size_t i = 0; i < len; ++i)
    {
        if (isdigit(s[i]))
        {
            double num;
            size_t i1 = i + 1;
            while (i1 < len && (isdigit(s[i1]) || s[i1] == '.'))
                ++i1;
            istringstream input(s.substr(i, i1));
            input >> num;
            i = i1 - 1;
            c.push(num);
        }
        else if (s[i] == '}' || s[i] == ']' || s[i] == ')')
        {
            char sign;
            char start = (s[i] == '}' ? '{' : (s[i] == ']' ? '[' : '('));
            while ((sign = c.get()) != start)
                c.calculate();
            c.pop();
        }
        else if(s[i] == 'p' || s[i] == 'e')
        {
            double number;
            if(s[i] == 'e')
            {
                number = 2.71828182846;
                c.push(number);
            }
            else
            {
                number = 3.14159265;
                c.push(number);
            }
        }
        else                          //s[i]  is  [ ( {  + - * / ^ %
        {
            while (c.canCalculate(s[i]))
                c.calculate();
            c.push(s[i]);
        }
    }
    while (!c.empty())
    {
        c.calculate();
    }
    a += QString::number(c.final_result);

    ui->lineEdit->setText(a);
}


