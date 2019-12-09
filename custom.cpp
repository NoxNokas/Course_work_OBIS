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
	X0[2] = 0;					//��������� ���������
	X0[3] = MStart + Fuel;		//��������� ����� ��

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
	//������� ���������
		Y[0] = X[1];								//������
		Y[1] = X[2];								//��������
		Y[2] = getP(dm) / X[3] - getG(X[0]);		//���������
		Y[3] = -dm;									//������� ����� ��
		//���������� �������
		Y[4] = 0;
		Y[5] = 0;
		Y[6] = 0;
	}
//	static int i = 0;
//	qDebug() << ++i << "X: " << X[0] << X[1] << X[2] << X[3];
//	qDebug() << i << "Y: " << Y[0] << Y[1] << Y[2] << Y[3];
}
