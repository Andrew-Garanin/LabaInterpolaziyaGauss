
// LabaInterpolaziyaGaussDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CLabaInterpolaziyaGaussDlg
class CLabaInterpolaziyaGaussDlg : public CDialog
{
// Создание
public:
	CLabaInterpolaziyaGaussDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABAINTERPOLAZIYAGAUSS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	// Кисти для раскрашивания прямоугольничков на окне
	CBrush m_brFunc;
	CBrush m_brPol;
	CBrush m_brFault;
	CBrush m_brDerivativeFunc;
	CBrush m_brDerivativePol;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//Размеры рассматриваемой области
	CEdit m_ControlA;
	CEdit m_ControlB;
	CEdit m_ControlC;
	CEdit m_ControlD;
	// Параметры самой функции
	CEdit m_Alpha;
	CEdit m_Beta;
	CEdit m_Gamma;
	// Кол-во узлов
	CEdit m_N;
	// Маленькое число - приращение аргумента, при подсчете производных
	CEdit m_Prirash;
	// Переменные для чекбоксов
	BOOL m_Func;
	BOOL m_Polinom;
	BOOL m_Fault;
	BOOL m_FuncDerivative;
	BOOL m_PolinomDerivative;

	afx_msg void OnUpdateA();
	afx_msg void OnUpdateB();
	afx_msg void OnUpdateC();
	afx_msg void OnChangeD();
	afx_msg void OnUpdateAlpha();
	afx_msg void OnUpdateBeta();
	afx_msg void OnChangeGamma();
	afx_msg void OnUpdateN();
	afx_msg void OnEnChangePrirashenie();
	afx_msg void OnBnClickedCreate();
	afx_msg void OnClickedCheckfunc();
	afx_msg void OnBnClickedCheckpolinom();
	afx_msg void OnBnClickedCheckfault();
	afx_msg void OnBnClickedCheckderivativefunk();
	afx_msg void OnBnClickedCheckcheckderivativepolinom();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
