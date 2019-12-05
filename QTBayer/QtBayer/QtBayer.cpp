#include "QtBayer.h"

QtBayer::QtBayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPixmap saveicon("zoom.png");
	QIcon SButtonICON(saveicon);
	ui.input_z->setIcon(SButtonICON);
	ui.serial_z->setIcon(SButtonICON);
	ui.section_z->setIcon(SButtonICON);
	ui.for_z->setIcon(SButtonICON);
	QPixmap developicon("developer.png");
	QIcon DButtonICON(developicon);
	ui.pushButton_info->setIcon(DButtonICON);
}
// Mat���� QImage�� �ٲٴ� �Լ�
QImage QtBayer::convertOpenCVMatToQtQImage(cv::Mat mat)
{
	// �� ä�κ��� �ڵ鸵
	if (mat.channels() == 1)
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_Indexed8);
	else if (mat.channels() == 3)
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_RGB888);
	return QImage();
}
// Raw image load �Լ�
void QtBayer::LoadRawImage()
{
	// load �� �� �˾� ����
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Raw File"), "",
		tr("raw image (*.raw *.RAW)"));

	char* rawname = strdup((fileName.toStdString()).c_str());;
	pFile = fopen(rawname, "rb");
	// �̹��� �ε� ������ �ʱ�ȭ
	ui.textBrowser_h->clear();
	ui.textBrowser_w->clear();
	ui.textBrowser_ser->clear();
	ui.textBrowser_sec->clear();
	ui.textBrowser_for->clear();
	ui.label_input->clear();
	ui.label_serial->clear();
	ui.label_section->clear();
	ui.label_for->clear();
	isserial = false;
	issection = false;
	isfor = false;
	// ���࿡ ���� ������ return
	if (pFile == NULL)
	{
		return;
	}
	// ���� ������ isfile�� isinput true��
	isfile = true;
	isinput = true;
	// obtain file size
	fseek(pFile, 0, SEEK_END);	// ���� �� ã��
	ISize = ftell(pFile);		// ���� ũ�� ã�´�
	rewind(pFile);				// �ٽ� ������ �� ���� ������ ���� ����

	// allocate memory to contain the whole file
	raw = (unsigned char*)malloc(sizeof(unsigned char)*ISize);
	if (raw == NULL) { fputs("Memory error", stderr);	exit(2); }
	RGB = (unsigned short*)malloc(sizeof(unsigned short)*ISize * 3);
	memset(RGB, 0, sizeof(unsigned short)*h*w * 3);
	R = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(R, 0, sizeof(unsigned short)*h*w);
	G = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(G, 0, sizeof(unsigned short)*h*w);
	B = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(B, 0, sizeof(unsigned short)*h*w);
	// parallel section�� ���� �޸� �Ҵ�
	RGB_sec = (unsigned short*)malloc(sizeof(unsigned short)*ISize * 3);
	memset(RGB_sec, 0, sizeof(unsigned short)*h*w * 3);
	R_sec = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(R_sec, 0, sizeof(unsigned short)*h*w);
	G_sec = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(G_sec, 0, sizeof(unsigned short)*h*w);
	B_sec = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(B_sec, 0, sizeof(unsigned short)*h*w);
	// parallel for�� ���� �޸� �Ҵ�
	RGB_for = (unsigned short*)malloc(sizeof(unsigned short)*ISize * 3);
	memset(RGB_for, 0, sizeof(unsigned short)*h*w * 3);
	R_for = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(R_for, 0, sizeof(unsigned short)*h*w);
	G_for = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(G_for, 0, sizeof(unsigned short)*h*w);
	B_for = (unsigned short*)malloc(sizeof(unsigned short)*ISize);
	memset(B_for, 0, sizeof(unsigned short)*h*w);
	data_sh = (unsigned short*)malloc(sizeof(unsigned short)*h*w);
	// copy the file into the buffer
	result = fread(raw, 1, ISize, pFile);	// result�� ����
	if (result != ISize) { fputs("Reading error", stderr);	exit(3); }

	// 8bit data to 10 bit data (raw->data)
	seq_data_copy_short(raw, data_sh, w*h);

	// short data�� ������ Mat file
	src = Mat(h, w, CV_16UC1, data_sh);

	// data_shpa�� short���� padding ��� ����
	data_shpa = Mat(h, w, CV_16UC1, data_sh);
	copyMakeBorder(data_shpa, data_shpa, 1, 1, 1, 1, BORDER_DEFAULT);

	normalize(src, src, 0, 255, NORM_MINMAX, CV_8UC3);
	QImage qimgOutput = convertOpenCVMatToQtQImage(src);
	ui.label_input->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_input->setScaledContents(true);
	// ui.label_input->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	// ui.label_input->show();
	// �̹����� height, width ���
	QString hs = QString::number(h);
	QString ws = QString::number(w);
	ui.textBrowser_h->setText(hs);
	ui.textBrowser_w->setText(ws);
	fclose(pFile);
	free(raw);
}
// short �� ������ ����
void QtBayer::seq_data_copy_short(unsigned char* buffer, unsigned short* data, int size)
{
	// for 10 bit
	// i,j = 0,0
	// data[0] = (buffer[0]<<2)+((buffer[4]>>0)&3)
	// data[1] = (buffer[1]<<2)+((buffer[4]>>2)&3)
	// data[2] = (buffer[2]<<2)+((buffer[4]>>4)&3)
	// data[3] = (buffer[3]<<2)+((buffer[4]>>6)&3)
	// i,j = 4,5
	// data[4] = (buffer[5]<<2)+((buffer[9]>>0)&3)
	// data[5] = (buffer[6]<<2)+((buffer[9]>>2)&3)
	// data[6] = (buffer[7]<<2)+((buffer[9]>>4)&3)
	// data[7] = (buffer[8]<<2)+((buffer[9]>>6)&3)
	for (int i = 0, j = 0; i < size; i += 4, j += 5)
	{
		data[i] = (buffer[j] << 2) + ((buffer[j + 4] >> 0) & 3);
		data[i + 1] = (buffer[j + 1] << 2) + ((buffer[j + 4] >> 2) & 3);
		data[i + 2] = (buffer[j + 2] << 2) + ((buffer[j + 4] >> 4) & 3);
		data[i + 3] = (buffer[j + 3] << 2) + ((buffer[j + 4] >> 6) & 3);
	}
}
// serial bayer interpolation �Լ�
void QtBayer::Interp_rggb_ushort_seq_ser(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	// ���� ������ ����
	if (!isfile)
		return;
	// ���� ������ serial �����ϰ�  isserial true��(���� ���� ����)
	isserial = true;
	// ���� �ð� ����
	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();

	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	for (int j = st_row; j < end_row; j++)
	{
		for (int i = st_col; i < end_col; i++)
		{
			// j ¦��
			if (j % 2 == 0)
			{
				// j ¦�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r[w*j + i] = ((rgb_data[w1*(j + 1) + i + 1]));
					// G
					g[w*j + i] = (((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
					// B
					b[w*j + i] = (((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
				}
				// j ¦�� i Ȧ��
				else
				{
					// R
					r[w*j + i] = (((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
					// G
					g[w*j + i] = ((rgb_data[w1*(j + 1) + i + 1]));
					// B
					b[w*j + i] = (((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
				}
			}
			// j Ȧ��
			else
			{
				// j Ȧ�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r[w*j + i] = (((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
					// G
					g[w*j + i] = ((rgb_data[w1*(j + 1) + i + 1]));
					// B
					b[w*j + i] = (((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
				}
				// j Ȧ�� i Ȧ��
				else
				{
					// R
					r[w*j + i] = (((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4));
					// G
					g[w*j + i] = (((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4));
					// B
					b[w*j + i] = ((rgb_data[w1*(j + 1) + i + 1]));
					// b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;
	// �� ä�κ��� Mat ���� ����(����ϰ����� �� ��밡��)
	Mat srcR = Mat(h, w, CV_16UC1, r);
	Mat srcB = Mat(h, w, CV_16UC1, b);
	Mat srcG = Mat(h, w, CV_16UC1, g);
	// �� ä�� ��ħ
	Mat srcBGR[3];
	RGB_f = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_f);
	// normalization���� �̹��� ��� Ȯ��
	normalize(RGB_f, RGB_f, 0, 255, NORM_MINMAX, CV_8UC3);
	// BGR ���� RGB�� 
	cvtColor(RGB_f, RGB_f, CV_BGR2RGB);
	// ���� ������ ����
	for (int i = 0; i < 3 * h*w; i += 3)
	{
		RGB[i] = r[i/3];
		RGB[i + 1] = g[i/3];
		RGB[i + 2] = b[i/3];
	}
	// ��� ���
	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_f);
	ui.label_serial->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_serial->setScaledContents(true);
	ui.label_serial->show();
	//QString proc = QString::number(fprocTime)+"ms";
	QString proc = QString::number(fprocTime);
	ui.textBrowser_ser->setText(proc);
}
// parallel section �Լ�(serial�� ������ �κ��� �ּ� ����)
void QtBayer::Interp_rggb_ushort_seq_sec(cv::Mat data, unsigned short* r_sec, unsigned short* g_sec, unsigned short* b_sec,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	if (!isfile)
		return;
	issection = true;
	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();
	// parallel section ����� ����
#pragma omp parallel sections
	{
#pragma omp section
		for (int j = 0; j < h / 2 - 1; j++)
		{
			for (int i = st_col; i < end_col; i++)
			{
				// j ¦��
				if (j % 2 == 0)
				{
					// j ¦�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// G
						g_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
						// B
						b_sec[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
					}
					// j ¦�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
						// G
						g_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// B
						b_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
					}
				}
				// j Ȧ��
				else
				{
					// j Ȧ�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
						// G
						g_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// B
						b_sec[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
					}
					// j Ȧ�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
						// G
						g_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
						// B
						b_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
					}
				}
			}
		}
#pragma omp section
		for (int j = h / 2 - 1; j < h; j++)
		{
			for (int i = st_col; i < end_col; i++)
			{
				// j ¦��
				if (j % 2 == 0)
				{
					// j ¦�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// G
						g_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
						// B
						b_sec[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
					}
					// j ¦�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
						// G
						g_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// B
						b_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
					}
				}
				// j Ȧ��
				else
				{
					// j Ȧ�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
						// G
						g_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
						// B
						b_sec[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
					}
					// j Ȧ�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
						// G
						g_sec[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
						// B
						b_sec[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
					}
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;
	QString proc = QString::number(fprocTime);
	ui.textBrowser_sec->setText(proc);
	Mat srcR = Mat(h, w, CV_16UC1, r_sec);
	Mat srcB = Mat(h, w, CV_16UC1, b_sec);
	Mat srcG = Mat(h, w, CV_16UC1, g_sec);

	Mat srcBGR[3];
	RGB_fsec = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_fsec);
	normalize(RGB_fsec, RGB_fsec, 0, 255, NORM_MINMAX, CV_8UC3);
	cvtColor(RGB_fsec, RGB_fsec, CV_BGR2RGB);
	for (int i = 0; i < 3*h*w; i+=3)
	{
		RGB_sec[i] = r_sec[i/3];
		RGB_sec[i+1] = g_sec[i/3];
		RGB_sec[i+2] = b_sec[i/3];
	}

	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_fsec);
	ui.label_section->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_section->setScaledContents(true);
	ui.label_section->show();
}
// parallel for �Լ�(serial�� ������ �κ��� �ּ� ����)
void QtBayer::Interp_rggb_ushort_seq_for(cv::Mat data, unsigned short* r_for, unsigned short* g_for, unsigned short* b_for,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	if (!isfile)
		return;
	isfor = true;
	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();
	// parallel for ����� ����
#pragma omp parallel for
	for (int j = st_row; j < end_row; j++)
	{
		for (int i = st_col; i < end_col; i++)
		{
			// j ¦��
			if (j % 2 == 0)
			{
				// j ¦�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r_for[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
					// G
					g_for[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
					// B
					b_for[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] 
						+ rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
				}
				// j ¦�� i Ȧ��
				else
				{
					// R
					r_for[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
					// G
					g_for[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
					// B
					b_for[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
				}
			}
			// j Ȧ��
			else
			{
				// j Ȧ�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r_for[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]) / 2;
					// G
					g_for[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
					// B
					b_for[w*j + i] = (rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 2;
				}
				// j Ȧ�� i Ȧ��
				else
				{
					// R
					r_for[w*j + i] = (rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2]) / 4;
					// G
					g_for[w*j + i] = (rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2]) / 4;
					// B
					b_for[w*j + i] = rgb_data[w1*(j + 1) + i + 1];
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;

	Mat srcR = Mat(h, w, CV_16UC1, r_for);
	Mat srcB = Mat(h, w, CV_16UC1, b_for);
	Mat srcG = Mat(h, w, CV_16UC1, g_for);

	Mat srcBGR[3];
	RGB_ffor = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_ffor);
	normalize(RGB_ffor, RGB_ffor, 0, 255, NORM_MINMAX, CV_8UC3);
	cvtColor(RGB_ffor, RGB_ffor, CV_BGR2RGB);
	
	for (int i = 0; i < 3 * h*w; i += 3)
	{
		RGB_for[i] = r_for[i/3];
		RGB_for[i + 1] = g_for[i/3];
		RGB_for[i + 2] = b_for[i/3];
	}
	
	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_ffor);
	ui.label_for->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_for->setScaledContents(true);
	ui.label_for->show();
	//QString proc = QString::number(fprocTime)+"ms";
	QString proc = QString::number(fprocTime);
	ui.textBrowser_for->setText(proc);
}

// round&double serial bayer interpolation �Լ�
void QtBayer::Interp_rggb_ushort_seq_ser_rd(cv::Mat data, unsigned short* r, unsigned short* g, unsigned short* b,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	// ���� ������ ����
	if (!isfile)
		return;
	// ���� ������ serial �����ϰ�  isserial true��(���� ���� ����)
	isserial = true;
	// ���� �ð� ����
	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();

	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	for (int j = st_row; j < end_row; j++)
	{
		for (int i = st_col; i < end_col; i++)
		{
			// j ¦��
			if (j % 2 == 0)
			{
				// j ¦�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// G
					g[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
					// B
					b[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
				}
				// j ¦�� i Ȧ��
				else
				{
					// R
					r[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
					// G
					g[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// B
					b[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
				}
			}
			// j Ȧ��
			else
			{
				// j Ȧ�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
					// G
					g[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// B
					b[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
				}
				// j Ȧ�� i Ȧ��
				else
				{
					// R
					r[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
					// G
					g[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
					// B
					b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;
	// �� ä�κ��� Mat ���� ����(����ϰ����� �� ��밡��)
	Mat srcR = Mat(h, w, CV_16UC1, r);
	Mat srcB = Mat(h, w, CV_16UC1, b);
	Mat srcG = Mat(h, w, CV_16UC1, g);
	// �� ä�� ��ħ
	Mat srcBGR[3];
	RGB_f = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_f);
	// normalization���� �̹��� ��� Ȯ��
	normalize(RGB_f, RGB_f, 0, 255, NORM_MINMAX, CV_8UC3);
	// BGR ���� RGB�� 
	cvtColor(RGB_f, RGB_f, CV_BGR2RGB);
	// ���� ������ ����
	for (int i = 0; i < 3 * h*w; i += 3)
	{
		RGB[i] = r[i / 3];
		RGB[i + 1] = g[i / 3];
		RGB[i + 2] = b[i / 3];
	}
	// ��� ���
	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_f);
	ui.label_serial->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_serial->setScaledContents(true);
	ui.label_serial->show();
	//QString proc = QString::number(fprocTime)+"ms";
	QString proc = QString::number(fprocTime);
	ui.textBrowser_ser->setText(proc);
}
// round&double parallel section �Լ�(serial�� ������ �κ��� �ּ� ����)
void QtBayer::Interp_rggb_ushort_seq_sec_rd(cv::Mat data, unsigned short* r_sec, unsigned short* g_sec, unsigned short* b_sec,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	if (!isfile)
		return;
	issection = true;
	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();
	// parallel section ����� ����
#pragma omp parallel sections
	{
#pragma omp section
		for (int j = 0; j < h / 2 - 1; j++)
		{
			for (int i = st_col; i < end_col; i++)
			{
				// j ¦��
				if (j % 2 == 0)
				{
					// j ¦�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// G
						g_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
					}
					// j ¦�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
						// G
						g_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
					}
				}
				// j Ȧ��
				else
				{
					// j Ȧ�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
						// G
						g_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
					}
					// j Ȧ�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
						// G
						g_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
						// B
						b_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					}
				}
			}
		}
#pragma omp section
		for (int j = h / 2 - 1; j < h; j++)
		{
			for (int i = st_col; i < end_col; i++)
			{
				// j ¦��
				if (j % 2 == 0)
				{
					// j ¦�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// G
						g_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
					}
					// j ¦�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
						// G
						g_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
					}
				}
				// j Ȧ��
				else
				{
					// j Ȧ�� i ¦��
					if (i % 2 == 0)
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
						// G
						g_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// B
						b_sec[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
					}
					// j Ȧ�� i Ȧ��
					else
					{
						// R
						r_sec[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
							rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
						// G
						g_sec[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
							+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
						// B
						b_sec[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
						// b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					}
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;
	QString proc = QString::number(fprocTime);
	ui.textBrowser_sec->setText(proc);
	Mat srcR = Mat(h, w, CV_16UC1, r_sec);
	Mat srcB = Mat(h, w, CV_16UC1, b_sec);
	Mat srcG = Mat(h, w, CV_16UC1, g_sec);

	Mat srcBGR[3];
	RGB_fsec = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_fsec);
	normalize(RGB_fsec, RGB_fsec, 0, 255, NORM_MINMAX, CV_8UC3);
	cvtColor(RGB_fsec, RGB_fsec, CV_BGR2RGB);
	for (int i = 0; i < 3 * h*w; i += 3)
	{
		RGB_sec[i] = r_sec[i / 3];
		RGB_sec[i + 1] = g_sec[i / 3];
		RGB_sec[i + 2] = b_sec[i / 3];
	}

	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_fsec);
	ui.label_section->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_section->setScaledContents(true);
	ui.label_section->show();
}
// round&double parallel for �Լ�(serial�� ������ �κ��� �ּ� ����)
void QtBayer::Interp_rggb_ushort_seq_for_rd(cv::Mat data, unsigned short* r_for, unsigned short* g_for, unsigned short* b_for,
	int w, int h, int st_row, int end_row, int st_col, int end_col)
{
	if (!isfile)
		return;
	isfor = true;
	// data ���� ���� ����
	unsigned short* rgb_data = (unsigned short*)data.data;
	// w1�� padding �� width
	int w1 = w + 2;

	double fstart, fend, fprocTime, fps;
	fstart = omp_get_wtime();
	// parallel for ����� ����
#pragma omp parallel for
	for (int j = st_row; j < end_row; j++)
	{
		for (int i = st_col; i < end_col; i++)
		{
			// j ¦��
			if (j % 2 == 0)
			{
				// j ¦�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r_for[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// G
					g_for[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
					// B
					b_for[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
				}
				// j ¦�� i Ȧ��
				else
				{
					// R
					r_for[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
					// G
					g_for[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// B
					b_for[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
				}
			}
			// j Ȧ��
			else
			{
				// j Ȧ�� i ¦��
				if (i % 2 == 0)
				{
					// R
					r_for[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1])) / 2);
					// G
					g_for[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// B
					b_for[w*j + i] = round(double((rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 2);
				}
				// j Ȧ�� i Ȧ��
				else
				{
					// R
					r_for[w*j + i] = round(double((rgb_data[w1*j + i] + rgb_data[w1*j + i + 2] +
						rgb_data[w1*(j + 2) + i] + rgb_data[w1*(j + 2) + i + 2])) / 4);
					// G
					g_for[w*j + i] = round(double((rgb_data[w1*j + i + 1] + rgb_data[w1*(j + 2) + i + 1]
						+ rgb_data[w1*(j + 1) + i] + rgb_data[w1*(j + 1) + i + 2])) / 4);
					// B
					b_for[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
					// b[w*j + i] = round(double(rgb_data[w1*(j + 1) + i + 1]));
				}
			}
		}
	}

	fend = omp_get_wtime();
	fprocTime = (fend - fstart) * 1000;

	Mat srcR = Mat(h, w, CV_16UC1, r_for);
	Mat srcB = Mat(h, w, CV_16UC1, b_for);
	Mat srcG = Mat(h, w, CV_16UC1, g_for);

	Mat srcBGR[3];
	RGB_ffor = Mat(h, w, CV_16UC3);
	srcBGR[0] = srcB;
	srcBGR[1] = srcG;
	srcBGR[2] = srcR;

	merge(srcBGR, 3, RGB_ffor);
	normalize(RGB_ffor, RGB_ffor, 0, 255, NORM_MINMAX, CV_8UC3);
	cvtColor(RGB_ffor, RGB_ffor, CV_BGR2RGB);

	for (int i = 0; i < 3 * h*w; i += 3)
	{
		RGB_for[i] = r_for[i / 3];
		RGB_for[i + 1] = g_for[i / 3];
		RGB_for[i + 2] = b_for[i / 3];
	}

	QImage qimgOutput = convertOpenCVMatToQtQImage(RGB_ffor);
	ui.label_for->setPixmap(QPixmap::fromImage(qimgOutput));
	ui.label_for->setScaledContents(true);
	ui.label_for->show();
	//QString proc = QString::number(fprocTime)+"ms";
	QString proc = QString::number(fprocTime);
	ui.textBrowser_for->setText(proc);
}
// ��� �̹��� raw�� ����
void QtBayer::SaveRawFile10bit(char* filename, unsigned short* data, int dataWidth, int dataHeight)
{
	if (!isfile || !isserial || !issection || !isfor)
		return;
	FILE* fp;
	fp = fopen(filename, "wb");
	fwrite(data, sizeof(unsigned short), dataHeight*dataWidth, fp);
	fclose(fp);
}
// ��� �̹��� bmp�� ����
void QtBayer::SaveBmpFile(char* filename, cv::Mat RGBB, int dataWidth, int dataHeight)
{
	if (!isfile || !isserial || !issection || !isfor)
		return;
	Mat BGR;
	cvtColor(RGBB, BGR, CV_RGB2BGR);
	imwrite(filename, BGR);
}
// serial ��ư ���� �� ���
void QtBayer::serial()
{
	//Mat data_shpa_fl;
	//flip(data_shpa, data_shpa_fl, 0);
	if(isrd)
		Interp_rggb_ushort_seq_ser_rd(data_shpa, R, G, B, w, h, 0, h, 0, w);
	else
		Interp_rggb_ushort_seq_ser(data_shpa, R, G, B, w, h, 0, h , 0, w);
}
// parallel section ��ư ���� �� ���
void QtBayer::pa_section()
{
	if(isrd)
		Interp_rggb_ushort_seq_sec_rd(data_shpa, R, G, B, w, h, 0, h, 0, w);
	else
		Interp_rggb_ushort_seq_sec(data_shpa, R, G, B, w, h, 0, h, 0, w);
}
// parallel for ��ư ���� �� ���
void QtBayer::pa_for()
{
	if(isrd)
		Interp_rggb_ushort_seq_for_rd(data_shpa, R, G, B, w, h, 0, h, 0, w);
	else
		Interp_rggb_ushort_seq_for(data_shpa, R, G, B, w, h, 0, h, 0, w);
}
// serial save ��ư ���� �� ���
void QtBayer::serial_save()
{
	if (!isrd)
	{
		SaveRawFile10bit("irgb_serial.raw", (unsigned short*)RGB, w, h * 3);
		SaveBmpFile("result_serial.bmp", RGB_f, w, h);
	}
	else
	{
		SaveRawFile10bit("irgb_serial_rd.raw", (unsigned short*)RGB, w, h * 3);
		SaveBmpFile("result_serial_rd.bmp", RGB_f, w, h);
	}
}
// parallel section save ��ư ���� �� ���
void QtBayer::section_save()
{
	if (!isrd)
	{
		SaveRawFile10bit("irgb_section.raw", (unsigned short*)RGB_sec, w, h * 3);
		SaveBmpFile("result_section.bmp", RGB_fsec, w, h);
	}
	else
	{
		SaveRawFile10bit("irgb_section_rd.raw", (unsigned short*)RGB_sec, w, h * 3);
		SaveBmpFile("result_section_rd.bmp", RGB_fsec, w, h);
	}
}
// parallel for save ��ư ���� �� ���
void QtBayer::for_save()
{
	if (!isrd)
	{
		SaveRawFile10bit("irgb_for.raw", (unsigned short*)RGB_for, w, h * 3);
		SaveBmpFile("result_for.bmp", RGB_ffor, w, h);
	}
	else
	{
		SaveRawFile10bit("irgb_for_rd.raw", (unsigned short*)RGB_for, w, h * 3);
		SaveBmpFile("result_for_rd.bmp", RGB_ffor, w, h);
	}

}
// input zoom Ű�� ������ ��
void QtBayer::inputzoom()
{
	if (!isinput)
		return;
	Mat src_v;
	cv::resize(src, src_v, cv::Size(1632, 1224), 0, 0, CV_INTER_CUBIC);
	namedWindow("input", WINDOW_NORMAL);
	resizeWindow("input", 1632, 1224);
	imshow("input", src_v);
	cvWaitKey(0);
}
// serial result zoom Ű�� ������ ��
void QtBayer::serialzoom()
{
	if (!isserial)
		return;
	Mat serial_v;
	cv::resize(RGB_f, serial_v, cv::Size(1632, 1224), 0, 0, CV_INTER_CUBIC);
	cvtColor(serial_v, serial_v, CV_RGB2BGR);
	namedWindow("serial result", WINDOW_NORMAL);
	resizeWindow("serial result", 1632, 1224);
	imshow("serial result", serial_v);
	cvWaitKey(0);
}
// parallel section result zoom Ű�� ������ ��
void QtBayer::sectionzoom()
{
	if (!issection)
		return;
	Mat section_v;
	cv::resize(RGB_fsec, section_v, cv::Size(1632, 1224), 0, 0, CV_INTER_CUBIC);
	cvtColor(section_v, section_v, CV_RGB2BGR);
	namedWindow("parallel section result", WINDOW_NORMAL);
	resizeWindow("parallel section result", 1632, 1224);
	imshow("parallel section result", section_v);
	cvWaitKey(0);
}
// parallel for result zoom Ű�� ������ ��
void QtBayer::forzoom()
{
	if (!isfor)
		return;
	Mat for_v;
	cv::resize(RGB_ffor, for_v, cv::Size(1632, 1224), 0, 0, CV_INTER_CUBIC);
	cvtColor(for_v, for_v, CV_RGB2BGR);
	namedWindow("parallel for result", WINDOW_NORMAL);
	resizeWindow("parallel for result", 1632, 1224);
	imshow("parallel for result", for_v);
	cvWaitKey(0);
}
// show information
void QtBayer::show_info()
{
	if (!isinfo)
	{
		info_fi = imread("info.png", 1);
		isinfo = true;
	}
	
	cv::resize(info_fi, info_fi, cv::Size(742, 302), 0, 0, CV_INTER_CUBIC);
	//cvtColor(for_v, for_v, CV_RGB2BGR);
	namedWindow("Developer", WINDOW_NORMAL);
	resizeWindow("Developer", 742, 302);
	imshow("Developer", info_fi);
	cvWaitKey(0);
}
// checkbox ������ �� round�� �ٲٱ�
void QtBayer::check_round()
{
	isrd = !isrd;
	ui.textBrowser_ser->clear();
	ui.textBrowser_sec->clear();
	ui.textBrowser_for->clear();
	ui.label_serial->clear();
	ui.label_section->clear();
	ui.label_for->clear();
}