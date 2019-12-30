#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
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
	Model->setSamplingIncrement(1e-2);
	double eps[] = {850, 374, 330};
	double t0 = 0.0l,			//время начала интегрирования
				t1 = 171.2,		//время конца интегрирования
				tStart = 32.687,	//время запуска двигателя
				step = Model->getSamplingIncrement();	//шаг интегрирования
	double		psi1 = 32.687,		//Пси 1
				psi2 = 32.687,		//Пси 2
				psi3 = 32.687,		//Пси 3
				psi3_T = 1.0;		//Конечное значение Пси 3
	bool flag = false;
	TIntegrator* Integrator = new TDormandPrinceIntegrator();
	Integrator->setPrecision(static_cast<double>(1e-15));
	Model->setT0(t0);
	TMatrix Result;

double funNevjazki[2] = {50,10000000};

	for(int i = 0; i<3; i++){
		Model->setT1(t1);
		Model->setTStart(tStart);
		Integrator->Run( Model );
		Result = Model->getResult();
		while (funNevjazki[1] >= eps[i]){
			while (Result(Result.rowHigh(),1) > 0){
				t1 +=step;
				if (flag == false) //сколько времени нужно, чтобы упасть с выкл. двигателем
					tStart = t1;
				Model->setT1(t1);
				Model->setTStart(tStart);		//лечу с выкл. двигателем (не удаляй)
				Integrator->Run( Model );
				Result = Model->getResult();
				std::cout <<"[1] t1 = " << t1<< "; tStart = " << double(tStart) << "; h = " << Result(Result.rowHigh(),1)<< "; v = " << Result(Result.rowHigh(),2) << std::endl;
			}
			do{
				tStart -= step;
				Model->setTStart(tStart);
				Integrator->Run( Model );
				Result = Model->getResult();
				std::cout <<"[2] t1 = " << t1<< "; tStart = " << double(tStart) << "; h = " << Result(Result.rowHigh(),1)<< "; v = " << Result(Result.rowHigh(),2) << std::endl;

			}while ((t1 - tStart > 0) && (tStart >= 0)/* && (Result(Result.rowHigh(),2) <= 0)*/ && (Result(Result.rowHigh(),1) <= 0));
			funNevjazki[0] = funNevjazki[1];
			funNevjazki[1] = sqrt(pow(Result(Result.rowHigh(),1),2) + pow(Result(Result.rowHigh(),2),2));
			flag = true;
			tStart += step;
		}
		step *= 0.1;
		Model->setSamplingIncrement(step);
	}


	Model->setT1(t1);
	Model->setTStart(tStart);
	Model->setPsi1(psi1);
	Model->setPsi2(psi2);
	Model->setPsi3(psi3);
	Integrator->Run( Model );
	Result = Model->getResult();




	double step_psi = 0;
	double opt_psi3 = 10000;
	//Для пси 1
	while(step_psi < 10){
		Model->setPsi1(step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi1 = step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		Model->setPsi1(-step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi1 = -step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		step_psi += 0.01;
		std::cout <<step_psi << '\n';
	}
	//Для пси 2
	opt_psi3 = 10000;
	step_psi = 5.0;
	Model->setPsi1(psi1);
	while(step_psi > 0){
		Model->setPsi2(step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi2 = step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		Model->setPsi2(-step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi2 = -step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		step_psi -= 0.01;
	}

	//Для пси 3
	opt_psi3 = 10000;
	step_psi = 5.0;
	//Model->setPsi1(psi1);
	Model->setPsi2(psi2);
	while(step_psi > 0){
		Model->setPsi3(step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi3 = step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		Model->setPsi3(-step_psi);
		Integrator->Run( Model );
		Result = Model->getResult();
		if (abs(Result(Result.rowHigh(),7) - psi3_T) <= abs(opt_psi3 - psi3_T)){
			psi3 = -step_psi;
			opt_psi3 = Result(Result.rowHigh(),7);
		}
		step_psi -= 0.01;
	}

	//Model->setPsi1(psi1);
	//Model->setPsi2(psi2);
	Model->setPsi3(psi3);
	//Model->setT1(t1);
	//Model->setTStart(tStart);
	Integrator->Run( Model );
	Result = Model->getResult();

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
				std::cout <<std::setw(15) << Result(i,j);
			}
			std::cout << '\n';
		}

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

