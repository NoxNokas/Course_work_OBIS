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
	Model->setSamplingIncrement(1e-1l);
	long double eps[] = {850, 374, 330};
	long double t0 = 0l,			//����� ������ ��������������
				t1 = 1.2l,		//����� ����� ��������������
				tStart = t1,	//����� ������� ���������
				pci1 = 0,		//��� 1
				pci2 = 0,		//��� 2
				pci3 = 0,		//��� 3
				step = Model->getSamplingIncrement();	//��� ��������������
	bool flag = false;
	TIntegrator* Integrator = new TDormandPrinceIntegrator();
	Integrator->setPrecision(static_cast<long double>(1e-15));
	Model->setT0(t0);
	TMatrix Result;
long double funNevjazki[2] = {50,10000000};

	for(int i = 0; i<3; i++){
		Model->setT1(t1);
		Model->setTStart(tStart);
		Integrator->Run( Model );
		Result = Model->getResult();
		while (funNevjazki[1] >= eps[i]){
			while (Result(Result.rowHigh(),1) > 0){
				t1 +=step;
				if (flag == false) //������� ������� �����, ����� ������ � ����. ����������
					tStart = t1;
				Model->setT1(t1);
				Model->setTStart(tStart);		//���� � ����. ���������� (�� ������)
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
			funNevjazki[1] = sqrtl(powl(Result(Result.rowHigh(),1),2) + powl(Result(Result.rowHigh(),2),2));
			flag = true;
			tStart += step;
		}
		//t1 += step;
		//tStart += step;
		step *= 0.1l;
		Model->setSamplingIncrement(step);
		//eps /= 2.5l;
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

	ui->Graph->clearGraphs();     //���� �����, �� ������� ��� �������
	ui->Graph->addGraph();        //��������� ���� ������ � Graph
	//�������, ��� ���������� ����� ������ �� ����� ���� �������� x � y
	ui->Graph->graph(0)->setData(t, h);
	ui->Graph->graph(0)->setPen(QColor(Qt::black));   //���� �����

	ui->Graph->addGraph();        //��������� ���� ������ � Graph
	//�������, ��� ���������� ����� ������ �� ����� ���� �������� x � y
	ui->Graph->graph(1)->setData(t, v);
	ui->Graph->graph(1)->setPen(QColor(Qt::blue));   //���� �����

	ui->Graph->addGraph();        //��������� ���� ������ � Graph
	//�������, ��� ���������� ����� ������ �� ����� ���� �������� x � y
	ui->Graph->graph(2)->setData(t, a);
	ui->Graph->graph(2)->setPen(QColor(Qt::red));   //���� �����

	ui->Graph->addGraph();        //��������� ���� ������ � Graph
	//�������, ��� ���������� ����� ������ �� ����� ���� �������� x � y
	ui->Graph->graph(3)->setData(t, m);
	ui->Graph->graph(3)->setPen(QColor(Qt::gray));   //���� �����

	//����������� ��� Ox � Oy
	ui->Graph->xAxis->setLabel("t");
	ui->Graph->yAxis->setLabel("phi");
	// �������������� ��������������� ����� �� ��� X
	ui->Graph->xAxis->setRange(t0, t1);        // ������� ������� �� X
	ui->Graph->yAxis->setRange(-400, 550000);    // ������� ������� �� Y

	ui->Graph->replot();              // ��������� ������

	delete Integrator;
	delete Model;

}

