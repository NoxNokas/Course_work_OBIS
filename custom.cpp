//---------------------------------------------------------------------------

#include "custom.h"
#include <math.h>
#include <QDebug>
#include "array.h"
//---------------------------------------------------------------------------
// Задача Аренсторфа (начальные условия 1)


SoftLandingModel::SoftLandingModel() : TModel()
{
	X0.resize(7);
	X0[0] = H_0;				//начальная высота
	X0[1] = v_0;				//начальная скорость
	X0[2] = 0;					//начальное ускорение
	X0[3] = MStart + Fuel;		//стартовая масса КА

	X0[4] = 0;
	X0[5] = 0;
	X0[6] = 0;
}

//---------------------------------------------------------------------------

double SoftLandingModel::getG(const double H){
	return (g_0 * (R_p / (R_p + H) ) );
}

double SoftLandingModel::getP(const double beta){
	return (J*beta);
}

void SoftLandingModel::getRight(TVector& X, long double t, TVector& Y)
{
	Y.resize(7);
	if (X[0] <= 0) {
		Y[0] = 0;
		Y[1] = 0;
		Y[2] = 0;
		Y[3] = 0;
	} else {
	//Векторы состояния
		Y[0] = X[1];								//высота
		Y[1] = X[2];								//скорость
		Y[2] = getP(dm) / X[3] - getG(X[0]);		//ускорение
		Y[3] = -dm;									//текущая масса КА
		//Сопряжённые векторы
		Y[4] = 0;
		Y[5] = 0;
		Y[6] = 0;
	}
//	static int i = 0;
//	qDebug() << ++i << "X: " << X[0] << X[1] << X[2] << X[3];
//	qDebug() << i << "Y: " << Y[0] << Y[1] << Y[2] << Y[3];
}
