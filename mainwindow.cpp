#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
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
	Model->setSamplingIncrement(1e-1l);
	unsigned long int i = 0;					//ограничение для итерации
	long double t0 = 0,			//время начала интегрирования
				t1 = 80l,		//время конца интегрирования
				tStart = 0l,	//время запуска двигателя
				pci1 = 0,		//Пси 1
				pci2 = 0,		//Пси 2
				pci3 = 0,		//Пси 3
				step = Model->getSamplingIncrement();	//шаг интегрирования
	bool flag = false;
	TIntegrator* Integrator = new TDormandPrinceIntegrator();
	Integrator->setPrecision(static_cast<long double>(1e-15));
	Model->setT0(t0);
	Model->setT1(t1);
	Model->setTStart(tStart);
	Integrator->Run( Model );
	TMatrix Result = Model->getResult();


	while (sqrtl(powl(Result(Result.rowHigh(),1),2) + powl(Result(Result.rowHigh(),2),2)) > 100l){
	tStart = t1;
		while (Result(Result.rowHigh(),1) > 0){
			t1 +=step;
			Model->setT1(t1);
			Model->setTStart(tStart);		//лечу с выкл. двигателем (не удаляй)
			Integrator->Run( Model );
			Result = Model->getResult();
			std::cout <<"t1 = " << t1 << "; h = " << Result(Result.rowHigh(),1) << std::endl;
		}
		while ((t1 - tStart > 0) && (abs(Result(Result.rowHigh(),2)) > 10) && (Result(Result.rowHigh(),1) < 0)){
			tStart -= step;
			Model->setTStart(tStart);
			Integrator->Run( Model );
			Result = Model->getResult();
			std::cout << "tStart = " << double(tStart) << "; t1 = " << t1 << std::endl;
			std::cout << "h = " << Result(Result.rowHigh(),1) << "; v = " << Result(Result.rowHigh(),2) << std::endl;
		}
	}



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
//		for (int i=0; i<Result.rowCount(); i++){
//			for (int j=0; j<Result.colCount(); j++){
//				std::cout <<std::setw(15) << Result(i,j);
//			}
//			std::cout << '\n';
//		}
//		std::cout <<"i = " << i << "; t0 = " << t0 << "; tStart = " << t1 - tStart << "; t1 = " << t1 << std::endl;

		std::ofstream out("results.txt");
		for (int i=0; i<Result.rowCount(); i++){
			for (int j=0; j<Result.colCount(); j++){
				out << Result(i,j) << ';';
			}
			out << std::endl;
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
	ui->Graph->xAxis->setRange(t0, t1);        // Область графика по X
	ui->Graph->yAxis->setRange(-400, 550000);    // Область графика по Y

	ui->Graph->replot();              // Обновляет график

	delete Integrator;
	delete Model;

}

