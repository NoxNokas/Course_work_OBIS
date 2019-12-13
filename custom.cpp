//---------------------------------------------------------------------------

#include "custom.h"
#include <math.h>
#include <QDebug>
#include "array.h"
//---------------------------------------------------------------------------
// ������ ���������� (��������� ������� 1)


SoftLandingModel::SoftLandingModel() : TModel()
{
	X0.resize(7);
	X0[0] = H_0;				//��������� ������
	X0[1] = v_0;				//��������� ��������
	X0[2] = - g_0 * pow(R_p / (R_p + H_0), 2);					//��������� ���������
	X0[3] = MStart + Fuel;		//��������� ����� ��

	X0[4] = 4;
	X0[5] = 2;
	X0[6] = 1;
}

//---------------------------------------------------------------------------

long double    SoftLandingModel::getG(const long double H){
	return g_0 * pow(R_p / (R_p + H), 2);
}

long double   SoftLandingModel::getP(const long double beta){
	return (J*beta);
}

void SoftLandingModel::getRight(const TVector& X, long double t, TVector& Y)
{
	Y.resize(7);
	//������� ���������
	Y[0] = X[1];								//������
	Y[1] = X[2];								//��������
	if (t < tStart){
		Y[2] = - getG(X[0]);
		Y[3] = 0.0l;
	} else {
		Y[2] = (getP(dm) / X[3]) - getG(X[0]);		//���������
		Y[3] = -dm;
	}
	//���������� �������
	Y[4] = (-2 * X[5] * g_0 * R_p * R_p) / ((R_p + X[0]) * (R_p + X[0]) * (R_p + X[0]));
	Y[5] = - X[4];
	Y[6] = X[5] * (getP(dm) / (X[3] * X[3]));
	//qDebug() << "t = " << static_cast<int>(t) << "Y[0] = " << Y[0] << "X[3] = " << X[0];
}
