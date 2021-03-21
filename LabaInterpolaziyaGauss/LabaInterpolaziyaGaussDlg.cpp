﻿
// LabaInterpolaziyaGaussDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "LabaInterpolaziyaGauss.h"
#include "LabaInterpolaziyaGaussDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CLabaInterpolaziyaGaussDlg

double A, B, C, D;
double alpha, beta, gamma;
int n;// кол-во узлов
int N;
double step;
double deltaY[200];//нужные дельты
double RX1 = 50, RY1 = 100, RX2 = 650, RY2 = 600;
CRect rect(RX1, RY1, RX2, RY2);
double DeltasArray[200][200];
double prirash;

CLabaInterpolaziyaGaussDlg::CLabaInterpolaziyaGaussDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LABAINTERPOLAZIYAGAUSS_DIALOG, pParent)
	, m_Func(TRUE),
	m_Polinom(TRUE),
	m_Fault(FALSE),
	m_FuncDerivative(FALSE),
	m_PolinomDerivative(FALSE)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brFunc.CreateSolidBrush(RGB(255, 0, 0));
	m_brPol.CreateSolidBrush(RGB(0, 255, 0));
	m_brFault.CreateSolidBrush(RGB(0, 0, 255));
	m_brDerivativeFunc.CreateSolidBrush(RGB(252, 15, 192));
	m_brDerivativePol.CreateSolidBrush(RGB(255, 165, 0));
}

void CLabaInterpolaziyaGaussDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_A, m_ControlA);
	DDX_Control(pDX, IDC_B, m_ControlB);
	DDX_Control(pDX, IDC_C, m_ControlC);
	DDX_Control(pDX, IDC_D, m_ControlD);
	DDX_Control(pDX, IDC_ALPHA, m_Alpha);
	DDX_Control(pDX, IDC_BETA, m_Beta);
	DDX_Control(pDX, IDC_GAMMA, m_Gamma);
	DDX_Control(pDX, IDC_N, m_N);
	DDX_Check(pDX, IDC_CHECKFUNC, m_Func);
	DDX_Check(pDX, IDC_CHECKPOLINOM, m_Polinom);
	DDX_Check(pDX, IDC_CHECKFAULT, m_Fault);
	DDX_Check(pDX, IDC_CHECKDERIVATIVEFUNK, m_FuncDerivative);
	DDX_Check(pDX, IDC_CHECKCHECKDERIVATIVEPOLINOM, m_PolinomDerivative);
	
		DDX_Control(pDX, IDC_PRIRASHENIE, m_Prirash);
}

BEGIN_MESSAGE_MAP(CLabaInterpolaziyaGaussDlg, CDialog)
	
	ON_EN_CHANGE(IDC_PRIRASHENIE, &CLabaInterpolaziyaGaussDlg::OnEnChangePrirashenie)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE(IDC_A, &CLabaInterpolaziyaGaussDlg::OnUpdateA)
	ON_EN_UPDATE(IDC_B, &CLabaInterpolaziyaGaussDlg::OnUpdateB)
	ON_EN_UPDATE(IDC_C, &CLabaInterpolaziyaGaussDlg::OnUpdateC)
	ON_BN_CLICKED(IDC_CHECKCHECKDERIVATIVEPOLINOM, &CLabaInterpolaziyaGaussDlg::OnBnClickedCheckcheckderivativepolinom)
	ON_BN_CLICKED(IDC_CHECKDERIVATIVEFUNK, &CLabaInterpolaziyaGaussDlg::OnBnClickedCheckderivativefunk)
	ON_BN_CLICKED(IDC_CHECKFAULT, &CLabaInterpolaziyaGaussDlg::OnBnClickedCheckfault)
	ON_EN_CHANGE(IDC_D, &CLabaInterpolaziyaGaussDlg::OnChangeD)
	ON_EN_UPDATE(IDC_ALPHA, &CLabaInterpolaziyaGaussDlg::OnUpdateAlpha)
	ON_EN_UPDATE(IDC_BETA, &CLabaInterpolaziyaGaussDlg::OnUpdateBeta)
	ON_BN_CLICKED(IDC_CHECKPOLINOM, &CLabaInterpolaziyaGaussDlg::OnBnClickedCheckpolinom)
	ON_EN_CHANGE(IDC_GAMMA, &CLabaInterpolaziyaGaussDlg::OnChangeGamma)
	ON_EN_UPDATE(IDC_N, &CLabaInterpolaziyaGaussDlg::OnUpdateN)
	ON_BN_CLICKED(IDC_CHECKFUNC, &CLabaInterpolaziyaGaussDlg::OnClickedCheckfunc)
	ON_BN_CLICKED(IDC_CREATE, &CLabaInterpolaziyaGaussDlg::OnBnClickedCreate)
	ON_BN_CLICKED(IDOK, &CLabaInterpolaziyaGaussDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Обработчики сообщений CLabaInterpolaziyaGaussDlg

BOOL CLabaInterpolaziyaGaussDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	m_ControlA.SetWindowTextW(L"-1");
	m_ControlB.SetWindowTextW(L"7");
	m_ControlC.SetWindowTextW(L"-2");
	m_ControlD.SetWindowTextW(L"3");
	m_Alpha.SetWindowTextW(L"1");
	m_Beta.SetWindowTextW(L"1");
	m_Gamma.SetWindowTextW(L"1");
	m_N.SetWindowTextW(L"15");
	m_Prirash.SetWindowTextW(L"0.01");

	this->SetWindowText(L"Интерполяция методом Гаусса. Гаранин Андрей ИВТ-31");
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CLabaInterpolaziyaGaussDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.


double Function(double x) {
	//return sin(x);
	return alpha*sin(tan(beta*x))*sin(gamma*x);
}

double Polinom(double x)
{
	double paperY= deltaY[1];
	double QandFact[200];
	QandFact[0] = 1;
	for (int i = 1; i < N+1; i++)
	{
		if (i % 2 != 0)
			QandFact[i] = (((x - DeltasArray[0][N / 2]) / step + i/2) * QandFact[i - 1])/i;
		else
			QandFact[i] = (((x - DeltasArray[0][N / 2]) / step - i/2) * QandFact[i - 1])/i;
	}
	for (int i = 1; i < N; i++)
	{
		paperY += deltaY[i+1] * QandFact[i];
	}
	return paperY;
}

double Perer(double x) {
	return RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));
}

void fillingArray(){
	N = 2 * n + 1;
	if (N <= 1)
		step = 0;
	else
		step = (B - A) / (N-1);
	for (int i = 0; i < N;i++)
	{
		DeltasArray[0][i] = A + step * i;
		DeltasArray[1][i] = Function(DeltasArray[0][i]);
	}

	for (int i = 2; i < N+1; i++)
		for (int j = 0; j < N - i+1; j++)
			DeltasArray[i][j] = DeltasArray[i - 1][j + 1] - DeltasArray[i - 1][j];

	for (int i = 1; i < N+1; i++)
		deltaY[i] = DeltasArray[i][(N - i+1)/2];
}

void CLabaInterpolaziyaGaussDlg::OnPaint()
{
	fillingArray();
	double x0 = RX1,
		   y0 = Perer(A);

	CPoint pStart(x0, y0), pCur;
	CPaintDC ClientDC(this);
	CPen m_NormalPen;

	ClientDC.Rectangle(RX1, RY1, RX2, RY2);
	m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(255, 0, 0));
	ClientDC.SelectObject(&m_NormalPen);
	ClientDC.IntersectClipRect(RX1, RY1, RX2, RY2);
	ClientDC.MoveTo(pStart);
	
	if (m_Func) {
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1)
		{
			pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
			pCur.y = Perer(x);
			ClientDC.LineTo(pCur);
		}
	}

	if (m_Polinom) {
		double rez = 0;

		m_NormalPen.DeleteObject();
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 255, 0));
		ClientDC.SelectObject(&m_NormalPen);

		pStart.y= RY2 - ((RY2 - RY1) * ((Function(A) - C) / (D - C)));
		ClientDC.MoveTo(pStart);
		for (double x = A; x < B; x += (B - A) / (RX2 - RX1) * 0.1)
		{
			pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
			rez = Polinom(x);
			if (rez > 100000)
				rez = 100000;
			if (rez < -100000)
				rez = -100000;
			pCur.y = RY2 - ((RY2 - RY1) * ((rez - C) / (D - C)));
			ClientDC.LineTo(pCur);
		}
		ClientDC.LineTo(RX2, RY2 - ((RY2 - RY1) * ((Function(B) - C) / (D - C))));
	}

	if (m_Fault) {
		double rez = 0;
		m_NormalPen.DeleteObject();
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 0, 255));
		ClientDC.SelectObject(&m_NormalPen);

		ClientDC.MoveTo(pStart);
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1)
		{
			
			pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
			rez = Polinom(x);
			if (rez > 100000)
				rez = 100000;
			if (rez < -100000)
				rez = -100000;

			pCur.y = RY2 - ((RY2 - RY1) * ((abs(rez-Function(x)) - C) / (D - C)));

			ClientDC.LineTo(pCur);
		}
	}

	if (m_FuncDerivative) {
		m_NormalPen.DeleteObject();
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(252, 15, 192));
		ClientDC.SelectObject(&m_NormalPen);

		ClientDC.MoveTo(pStart);
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1)
		{
			pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
			pCur.y = RY2 - ((RY2 - RY1) * (((Function(x + prirash) - Function(x - prirash)) / (2 * prirash) - C) / (D - C)));
			ClientDC.LineTo(pCur);
		}
	}
	if (m_PolinomDerivative) {
		m_NormalPen.DeleteObject();
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(255, 165, 0));
		ClientDC.SelectObject(&m_NormalPen);
		double rez = 0;
		pStart.y = RY2 - ((RY2 - RY1) * ((Function(A) - C) / (D - C)));
		ClientDC.MoveTo(pStart);
		for (double x = A; x < B; x += (B - A) / (RX2 - RX1) * 0.1)
		{
			
			pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
			rez = (Polinom(x+prirash)-Polinom(x-prirash))/ (2 * prirash);
			if (rez > 100000)
				rez = 100000;
			if (rez < -100000)
				rez = -100000;
			pCur.y = RY2 - ((RY2 - RY1) * ((rez - C) / (D - C)));
			ClientDC.LineTo(pCur);
		}
		ClientDC.LineTo(RX2, RY2 - ((RY2 - RY1) * ((Function(B + prirash) - Function(B - prirash)) / (2 * prirash) - C) / (D - C)));
	}


	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLabaInterpolaziyaGaussDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLabaInterpolaziyaGaussDlg::OnUpdateA()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlA.GetWindowTextW(str);
	A = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnUpdateB()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlB.GetWindowTextW(str);
	B = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnUpdateC()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlC.GetWindowTextW(str);
	C = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnChangeD()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlD.GetWindowTextW(str);
	D = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnUpdateAlpha()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Alpha.GetWindowTextW(str);
	alpha = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnUpdateBeta()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Beta.GetWindowTextW(str);
	beta = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnChangeGamma()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Gamma.GetWindowTextW(str);
	gamma = _wtof(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnUpdateN()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_N.GetWindowTextW(str);
	n = _wtoi(str);
	
}


void CLabaInterpolaziyaGaussDlg::OnClickedCheckfunc()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_Func = IsDlgButtonChecked(IDC_CHECKFUNC);
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedCreate()
{
	// TODO: добавьте свой код обработчика уведомлений
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedCheckpolinom()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_Polinom = IsDlgButtonChecked(IDC_CHECKPOLINOM);
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedCheckfault()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_Fault = IsDlgButtonChecked(IDC_CHECKFAULT);
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedCheckderivativefunk()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_FuncDerivative = IsDlgButtonChecked(IDC_CHECKDERIVATIVEFUNK);
}


void CLabaInterpolaziyaGaussDlg::OnBnClickedCheckcheckderivativepolinom()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_PolinomDerivative = IsDlgButtonChecked(IDC_CHECKCHECKDERIVATIVEPOLINOM);
}

void CLabaInterpolaziyaGaussDlg::OnEnChangePrirashenie()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Prirash.GetWindowTextW(str);
	prirash = _wtof(str);
}


HBRUSH CLabaInterpolaziyaGaussDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Измените любые атрибуты DC
	if (pWnd->GetDlgCtrlID() == IDC_F)
		return m_brFunc;
	if (pWnd->GetDlgCtrlID() == IDC_P)
		return m_brPol;
	if (pWnd->GetDlgCtrlID() == IDC_RN)
		return m_brFault;
	if (pWnd->GetDlgCtrlID() == IDC_DF)
		return m_brDerivativeFunc;
	if (pWnd->GetDlgCtrlID() == IDC_DPN)
		return m_brDerivativePol;
	// TODO:  Вернуть другое значение дескриптора кисти, если оно не определено по умолчанию
	return hbr;
}
