#pragma once


// Routing_Add_Dlg ��ȭ �����Դϴ�.

class Routing_Add_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Routing_Add_Dlg)

public:
	Routing_Add_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Routing_Add_Dlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = Routing_AddDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
