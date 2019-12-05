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
private slots:	// 버튼 클릭 핸들하기 위해 각 함수 선언
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
	int w = 3264;						// 파일 width
	int h = 2448;						// 파일 height
	FILE* pFile;						// File pointer
	long ISize;							// int 형식의 크기보다 크거나 같은 정수 계열 형식
	unsigned char* raw;					// 읽어 온 데이터(8bit)
	unsigned short* RGB;				// serial에서의 short형 RGB
	unsigned short* RGB_sec;			// section에서의 short형 RGB
	unsigned short* RGB_for;            // for에서의 short형 RGB
	unsigned short* R, *B, *G;			// 저장 할 데이터(10bit)
	unsigned short* R_sec, *B_sec, *G_sec;
	unsigned short* R_for, *B_for, *G_for;
	unsigned short* data_sh;
	size_t result;
	// 출력과 bitmap 저장을 위한 각각의 Mat 데이터
	Mat src, data, data_shpa;
	Mat RGB_f, RGB_fsec, RGB_ffor;
	Mat info_fi;
	// 예외처리를 위한 변수 선언
	bool isfile = false;
	bool isinput = false;
	bool isserial = false;
	bool issection = false;
	bool isfor = false;
	bool isinfo = false;
	bool isrd = false;
};
