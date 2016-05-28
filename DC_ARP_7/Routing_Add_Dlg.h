#pragma once


// Routing_Add_Dlg 대화 상자입니다.

class Routing_Add_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Routing_Add_Dlg)

public:
	Routing_Add_Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Routing_Add_Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = Routing_AddDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
