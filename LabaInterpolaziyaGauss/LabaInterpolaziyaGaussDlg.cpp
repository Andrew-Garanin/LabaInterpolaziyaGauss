
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
double n;
double RX1 = 50, RY1 = 100, RX2 = 650, RY2 = 600;
CRect rect(RX1, RY1, RX2, RY2);


CLabaInterpolaziyaGaussDlg::CLabaInterpolaziyaGaussDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LABAINTERPOLAZIYAGAUSS_DIALOG, pParent)
	, m_Func(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
}

BEGIN_MESSAGE_MAP(CLabaInterpolaziyaGaussDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE(IDC_A, &CLabaInterpolaziyaGaussDlg::OnUpdateA)
	ON_EN_UPDATE(IDC_B, &CLabaInterpolaziyaGaussDlg::OnUpdateB)
	ON_EN_UPDATE(IDC_C, &CLabaInterpolaziyaGaussDlg::OnUpdateC)
	ON_EN_CHANGE(IDC_D, &CLabaInterpolaziyaGaussDlg::OnChangeD)
	ON_EN_UPDATE(IDC_ALPHA, &CLabaInterpolaziyaGaussDlg::OnUpdateAlpha)
	ON_EN_UPDATE(IDC_BETA, &CLabaInterpolaziyaGaussDlg::OnUpdateBeta)
	ON_EN_CHANGE(IDC_GAMMA, &CLabaInterpolaziyaGaussDlg::OnChangeGamma)
	ON_EN_UPDATE(IDC_N, &CLabaInterpolaziyaGaussDlg::OnUpdateN)
	ON_BN_CLICKED(IDC_CHECKFUNC, &CLabaInterpolaziyaGaussDlg::OnClickedCheckfunc)
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
	m_ControlA.SetWindowTextW(L"1.5");
	m_ControlB.SetWindowTextW(L"1.7");
	m_ControlC.SetWindowTextW(L"-2");
	m_ControlD.SetWindowTextW(L"2");
	m_Alpha.SetWindowTextW(L"1");
	m_Beta.SetWindowTextW(L"1");
	m_Gamma.SetWindowTextW(L"1");
	m_N.SetWindowTextW(L"36");

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
	return alpha*sin(tan(beta*x))*sin(gamma*x);
}

double Perer(double x) {
	return RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));
}

void CLabaInterpolaziyaGaussDlg::OnPaint()
{
	double x0 = RX1,
		   y0 = Perer(A);

	CPoint pStart(x0, y0), pCur;
	CPaintDC ClientDC(this);
	CPen m_NormalPen;
	m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 0, 0));
	ClientDC.SelectObject(&m_NormalPen);

	ClientDC.Rectangle(RX1, RY1, RX2, RY2);
	
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
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnUpdateB()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlB.GetWindowTextW(str);
	B = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnUpdateC()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlC.GetWindowTextW(str);
	C = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnChangeD()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_ControlD.GetWindowTextW(str);
	D = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnUpdateAlpha()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Alpha.GetWindowTextW(str);
	alpha = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnUpdateBeta()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Beta.GetWindowTextW(str);
	beta = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnChangeGamma()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_Gamma.GetWindowTextW(str);
	gamma = _wtof(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnUpdateN()
{
	// TODO:  Добавьте код элемента управления
	CString str;
	m_N.GetWindowTextW(str);
	n = _wtoi(str);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}


void CLabaInterpolaziyaGaussDlg::OnClickedCheckfunc()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_Func = IsDlgButtonChecked(IDC_CHECKFUNC);
	InvalidateRect(rect);
	UpdateWindow();
	CLabaInterpolaziyaGaussDlg::OnPaint();
}
