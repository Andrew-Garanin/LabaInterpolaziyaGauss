
// LabaInterpolaziyaGauss.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLabaInterpolaziyaGaussApp:
// Сведения о реализации этого класса: LabaInterpolaziyaGauss.cpp
//

class CLabaInterpolaziyaGaussApp : public CWinApp
{
public:
	CLabaInterpolaziyaGaussApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLabaInterpolaziyaGaussApp theApp;
