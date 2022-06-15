#pragma once
#include<vector>
// CMapDialog 对话框

class CMapDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMapDialog)

public:
	CMapDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMapDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 输入起点位置的下拉列表框对象
	CComboBox m_ComboStart;
	// 输入终点位置的下拉列表框对象
	CComboBox m_ComboEnd;
	std::vector<CString> StartDeletedString;
	std::vector<CString> EndDeletedString;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnEditchangeComboStart();
	afx_msg void OnCbnEditchangeComboEnd();
	afx_msg void OnCbnSetfocusComboStart();
	afx_msg void OnCbnSetfocusComboEnd();
};
