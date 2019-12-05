#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qfiledialog.h>
#include "ui_QtBayer.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <omp.h>
#include <iostream>

using namespace std;
using namespace cv;

class QtBayer : public QMainWindow
{
	Q_OBJECT

public:
	QtBayer(QWidget *parent = Q_NULLPTR);
	QImage convertOpenCVMatToQtQImage(cv::Mat mat);
	void seq_data_copy_short(unsigned char* buffer, unsigned short* data, int size);
	void Interp_rggb_ushort_seq_ser(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void Interp_rggb_ushort_seq_sec(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void Interp_rggb_ushort_seq_for(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void Interp_rggb_ushort_seq_ser_rd(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void Interp_rggb_ushort_seq_sec_rd(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void Interp_rggb_ushort_seq_for_rd(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
		int w, int h, int st_row, int end_row, int st_col, int end_col);
	void SaveRawFile10bit(char* filename, unsigned short* data, int dataWidth, int dataHeight);
	void SaveBmpFile(char* filename, cv::Mat RGB, int dataWidth, int dataHeight);
private slots:	// ��ư Ŭ�� �ڵ��ϱ� ���� �� �Լ� ����
	void LoadRawImage();
	void serial();
	void pa_section();
	void pa_for();
	void serial_save();
	void section_save();
	void for_save();
	void inputzoom();
	void serialzoom();
	void sectionzoom();
	void forzoom();
	void show_info();
	void check_round();
private:
	Ui::QtBayerClass ui;
	int w = 3264;						// ���� width
	int h = 2448;						// ���� height
	FILE* pFile;						// File pointer
	long ISize;							// int ������ ũ�⺸�� ũ�ų� ���� ���� �迭 ����
	unsigned char* raw;					// �о� �� ������(8bit)
	unsigned short* RGB;				// serial������ short�� RGB
	unsigned short* RGB_sec;			// section������ short�� RGB
	unsigned short* RGB_for;            // for������ short�� RGB
	unsigned short* R, *B, *G;			// ���� �� ������(10bit)
	unsigned short* R_sec, *B_sec, *G_sec;
	unsigned short* R_for, *B_for, *G_for;
	unsigned short* data_sh;
	size_t result;
	// ��°� bitmap ������ ���� ������ Mat ������
	Mat src, data, data_shpa;
	Mat RGB_f, RGB_fsec, RGB_ffor;
	Mat info_fi;
	// ����ó���� ���� ���� ����
	bool isfile = false;
	bool isinput = false;
	bool isserial = false;
	bool issection = false;
	bool isfor = false;
	bool isinfo = false;
	bool isrd = false;
};
