
// lyj_mfc_opencv_workDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lyj_mfc_opencv_work.h"
#include "lyj_mfc_opencv_workDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClyjmfcopencvworkDlg 对话框



ClyjmfcopencvworkDlg::ClyjmfcopencvworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LYJ_MFC_OPENCV_WORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClyjmfcopencvworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClyjmfcopencvworkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClyjmfcopencvworkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ClyjmfcopencvworkDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ClyjmfcopencvworkDlg 消息处理程序

BOOL ClyjmfcopencvworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	VideoCapture capture;
	Mat frame;
	frame = capture.open("./1.mp4");
	if (!capture.isOpened())
	{
		return FALSE;
	}
	capture.read(frame);
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(rect); //获取picture control控件变量的rect
	namedWindow("imgshow", CV_WINDOW_NORMAL);//可以改变窗口大小
	resizeWindow("imgshow", rect.Width(), rect.Height());//根据piccontrol的大下设置opencv窗口的大小
	HWND hWnd = (HWND)cvGetWindowHandle("imgshow");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	imshow("imgshow", frame);
	
	/*GetDlgItem(IDC_STATIC_DST)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_DST)->ShowWindow(TRUE);*/

	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetWindowRect(rect); //获取picture control控件变量的rect
	//namedWindow("imgshow", CV_WINDOW_NORMAL);//可以改变窗口大小
	//resizeWindow("imgshow", rect.Width(), rect.Height());//根据piccontrol的大下设置opencv窗口的大小

	//Mat mat = imread("./1.jpg");//opencv读取图片
	//CRect rect;
	//GetDlgItem(IDC_STATIC1)->GetWindowRect(rect); //获取picture control控件变量的rect
	//namedWindow("imgshow", CV_WINDOW_NORMAL);//可以改变窗口大小
	//resizeWindow("imgshow", rect.Width(), rect.Height());//根据piccontrol的大下设置opencv窗口的大小

	//HWND hWnd = (HWND)cvGetWindowHandle("imgshow");//嵌套opencv窗口
	//HWND hParent = ::GetParent(hWnd);
	//::SetParent(hWnd, GetDlgItem(IDC_STATIC1)->m_hWnd);
	//::ShowWindow(hParent, SW_HIDE);
	//imshow("imgshow", mat);//opencv显示图片

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClyjmfcopencvworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ClyjmfcopencvworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ClyjmfcopencvworkDlg::OnBnClickedButton1()
{
	VideoCapture capture;
	Mat frame;
	frame = capture.open("./1.mp4");
	if (!capture.isOpened())
	{
		return;
	}
	CImage image;
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->m_hDC;
	CRect rect_frame;
	pWnd->GetClientRect(&rect_frame);
	while (capture.read(frame))
	{
		MatToCImage(frame, image);

		//image.Load(L"./1.jpg");
		::SetStretchBltMode(hDC, HALFTONE);
		::SetBrushOrgEx(hDC, 0, 0, NULL);
		image.Draw(hDC, rect_frame);
		
		if (waitKey(1) > 0)
		{
			break;
		}
	}
	ReleaseDC(pDC);
	image.Destroy();
	return;
}

void ClyjmfcopencvworkDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	VideoCapture capture;
	Mat frame;
	frame = capture.open("./1.mp4");
	if (!capture.isOpened())
	{
		return;
	}
	CImage image;
	CWnd* pWnd = GetDlgItem(IDABORT);
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->m_hDC;
	CRect rect_frame;
	pWnd->GetClientRect(&rect_frame);
	while (capture.read(frame))
	{
		cv::Mat gray = frame.clone();
		cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);
		MatToCImage(gray, image);

		//image.Load(L"./1.jpg");
		::SetStretchBltMode(hDC, HALFTONE);
		::SetBrushOrgEx(hDC, 0, 0, NULL);
		image.Draw(hDC, rect_frame);

		if (waitKey(1) > 0)
		{
			break;
		}
	}
	ReleaseDC(pDC);
	image.Destroy();
	return;
}


void ClyjmfcopencvworkDlg::MatToCImage(Mat& mat, CImage& cimage)
{
	if (0 == mat.total())
	{
		return;
	}


	int nChannels = mat.channels();
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = mat.cols;
	int nHeight = mat.rows;


	//重建cimage
	cimage.Destroy();
	cimage.Create(nWidth, nHeight, 8 * nChannels);


	//拷贝数据


	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负


	if (1 == nChannels)								//对于单通道的图像需要初始化调色板
	{
		RGBQUAD* rgbquadColorTable;
		int nMaxColors = 256;
		rgbquadColorTable = new RGBQUAD[nMaxColors];
		cimage.GetColorTable(0, nMaxColors, rgbquadColorTable);
		for (int nColor = 0; nColor < nMaxColors; nColor++)
		{
			rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;
			rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;
			rgbquadColorTable[nColor].rgbRed = (uchar)nColor;
		}
		cimage.SetColorTable(0, nMaxColors, rgbquadColorTable);
		delete[]rgbquadColorTable;
	}


	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				*(pucImage + nRow * nStep + nCol) = pucRow[nCol];
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					*(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];
				}
			}
		}
	}
}

void ClyjmfcopencvworkDlg::CImageToMat(CImage& cimage, Mat& mat)
{
	if (true == cimage.IsNull())
	{
		return;
	}


	int nChannels = cimage.GetBPP() / 8;
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = cimage.GetWidth();
	int nHeight = cimage.GetHeight();


	//重建mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if (3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}


	//拷贝数据


	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负


	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				pucRow[nCol] = *(pucImage + nRow * nStep + nCol);
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					pucRow[nCol * 3 + nCha] = *(pucImage + nRow * nStep + nCol * 3 + nCha);
				}
			}
		}
	}
}


