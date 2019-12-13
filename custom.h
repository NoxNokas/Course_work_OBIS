#pragma once//---------------------------------------------------------------------------



#include "model.h"

//---------------------------------------------------------------------------
// ������ ���������� (��������� ������� 1)

class SoftLandingModel  : public TModel
{
protected:
	const long double
			R_p = 6371000,		//������ ������� ������
			MStart = 26000,		//26 ���� ����� ������������ 1-� ������� Falcon 9 � ������������� (����� �����)
			J = 28200,			//�������� ������� = 282 c;
			Fuel = 517700,		//��������� ����� ������� �� (� ������ ������ �������)
			H_0 = 200000,		//������ ����������� ������ 160-2000��
			dm = 236,			//������ ������� ��/c � ������ ��������� � Falcon 9 v1.1 Stage 1
			g_0 = 9.80666,		//��������� ���������� ������� �/�^2
			v_0 = 10000;		//��������� �������� �/�
public:
		SoftLandingModel(  );
		~SoftLandingModel() {}
		void getRight(const TVector& X, long double t, TVector& Y);
		long double getG(const long double H);
		long double getP(const long double beta);
};
