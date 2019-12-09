#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	TModel* Model = new SoftLandingModel();
    MainWindow::showResult(Model);
    delete Model;

}

void MainWindow::showResult(TModel* model){

    TIntegrator* Integrator = new TDormandPrinceIntegrator();
		Integrator->setPrecision(static_cast<long double>(1e-5));
        Integrator->Run( model );

    TMatrix Result = model->getResult();

	QVector<double> t(Result.rowCount()),
					h(Result.rowCount()),
					v(Result.rowCount()),
					a(Result.rowCount()),
					m(Result.rowCount());

    for (int i=0; i<Result.rowCount(); i++)
    {
        for (int j=0; j<Result.colCount(); j++)
        {
			if (j == 0) { t[i] = Result(i,j); }
			if (j == 1) { h[i] = Result(i,j); }
			if (j == 2) { v[i] = Result(i,j); }
			if (j == 3) { a[i] = Result(i,j); }
			if (j == 4) { m[i] = Result(i,j); }
        }
    }
		for (int i=0; i<Result.rowCount(); i++){
			for (int j=0; j<Result.colCount(); j++){
				std::cout <<std::setw(13) << Result(i,j);
			}
			std::cout << '\n';
		}
    ui->Graph->clearGraphs();     //Если нужно, то очищаем все графики
    ui->Graph->addGraph();        //Добавляем один график в Graph
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->Graph->graph(0)->setData(t, h);
	ui->Graph->graph(0)->setPen(QColor(Qt::black));   //Цвет линии

	ui->Graph->addGraph();        //Добавляем один график в Graph
	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->Graph->graph(1)->setData(t, v);
	ui->Graph->graph(1)->setPen(QColor(Qt::blue));   //Цвет линии

	ui->Graph->addGraph();        //Добавляем один график в Graph
	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->Graph->graph(2)->setData(t, a);
	ui->Graph->graph(2)->setPen(QColor(Qt::red));   //Цвет линии

	ui->Graph->addGraph();        //Добавляем один график в Graph
	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->Graph->graph(3)->setData(t, m);
	ui->Graph->graph(3)->setPen(QColor(Qt::gray));   //Цвет линии

    //Подписываем оси Ox и Oy
    ui->Graph->xAxis->setLabel("t");
    ui->Graph->yAxis->setLabel("phi");
	// Автоматическое масштабирование тиков по Оси X
	ui->Graph->xAxis->setRange(0, 300);        // Область графика по X
	ui->Graph->yAxis->setRange(-41000, 960000);    // Область графика по Y

    ui->Graph->replot();              // Обновляет график

        delete Integrator;
}
