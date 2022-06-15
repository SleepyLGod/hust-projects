// CMapDialog.cpp: 实现文件
//

#include "pch.h"
#include "HustMap.h"
#include "CMapDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "HustMapDoc.h"
#include"CMapModel.h"
#include"HustMapView.h"
// CMapDialog 对话框

#define N 1000

IMPLEMENT_DYNAMIC(CMapDialog, CDialogEx)

CMapDialog::CMapDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_DIALOG, pParent)
{

}

CMapDialog::~CMapDialog()
{
}

void CMapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_START, m_ComboStart);
	DDX_Control(pDX, IDC_COMBO_END, m_ComboEnd);
}


BEGIN_MESSAGE_MAP(CMapDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapDialog::OnBnClickedOk)
	ON_CBN_EDITCHANGE(IDC_COMBO_START, &CMapDialog::OnCbnEditchangeComboStart)
	ON_CBN_EDITCHANGE(IDC_COMBO_END, &CMapDialog::OnCbnEditchangeComboEnd)
	ON_CBN_SETFOCUS(IDC_COMBO_START, &CMapDialog::OnCbnSetfocusComboStart)
	ON_CBN_SETFOCUS(IDC_COMBO_END, &CMapDialog::OnCbnSetfocusComboEnd)
END_MESSAGE_MAP()


// CMapDialog 消息处理程序


BOOL CMapDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox* pComboBoxStart = dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_START));
	CComboBox* pComboBoxEnd = dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_END));
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CHustMapView* pHustMapView = dynamic_cast<CHustMapView*>(pMainFrm->GetActiveView());
	pHustMapView->SetHaveDrawLine();
	pHustMapView->Invalidate();
	CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(pMainFrm->GetActiveDocument());
	if (pHustDoc->m_MapModel.GetOrgFilePath() != _T("")) {
		for (int i = 0; i < pHustDoc->m_MapModel.Organization.size(); i++)
		{
			pComboBoxStart->AddString(pHustDoc->m_MapModel.Organization[i]);
			pComboBoxEnd->AddString(pHustDoc->m_MapModel.Organization[i]);
		}
		this->UpdateData(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMapDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csStart, csEnd;
	int selIndex = this->m_ComboStart.GetCurSel();
	this->m_ComboStart.GetLBText(selIndex, csStart);
	int endIndex = this->m_ComboEnd.GetCurSel();
	this->m_ComboEnd.GetLBText(endIndex, csEnd);
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("起始位置为") + csStart);
	pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("终点位置为") + csEnd);
	CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(pMainFrm->GetActiveDocument());
	CPoint start = pHustDoc->m_MapModel.FindPositionByOrg(csStart);
	CPoint end= pHustDoc->m_MapModel.FindPositionByOrg(csEnd);
	std::vector<CPoint>	path = pHustDoc->m_MapModel.FindShortestPath(start, end);
	CHustMapView* pHustMapView = dynamic_cast<CHustMapView*>(pMainFrm->GetActiveView());
	//pHustMapView->Invalidate();
	for (int i = 0; i < path.size()-1; i++)
	{
		pHustMapView->DrawCircle(path[i], 5,1); pHustMapView->DrawCircle(path[i+1], 5,1);
		pHustMapView->DrawLine(path[i], path[i+1]);
	}
	CDialogEx::OnOK();
}

wchar_t str1[N], str2[N];
wchar_t lcs[N];
int c[N][N];
int flag[N][N];

int getLCSlength(const wchar_t* s1, const wchar_t* s2)
{
	for (int i = 0; i < N; i++)
	{
		str1[i] = 0;
		str2[i] = 0;
		lcs[i] = 0;
		for (int j = 0; j < N; j++)
		{
			c[i][j] = 0;
			flag[i][j] = 0;
		}
	}
	int i;
	int len1 = wcslen(s1);
	int len2 = wcslen(s2);
	for (i = 1; i <= len1; i++)
		c[i][0] = 0;
	for (i = 0; i <= len2; i++)
		c[0][i] = 0;
	int j;
	for (i = 1; i <= len1; i++)
		for (j = 1; j <= len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				flag[i][j] = 0;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				flag[i][j] = 1;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				flag[i][j] = -1;
			}
		}
	return c[len1][len2];
}

void CMapDialog::OnCbnEditchangeComboStart()
{
	//m_ComboStart.ShowDropDown(TRUE);
	//SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW))); //显示鼠标
	CString v_EditText =_T("");//用来保存当前编辑框的字符串
	m_ComboStart.GetWindowText(v_EditText);
	if (v_EditText != (_T(""))) {
		int num = m_ComboStart.GetCount();
		for (int i = 0; i < num; ++i) {
			CString temp;
			m_ComboStart.GetLBText(num - i - 1, temp);
			if (getLCSlength(v_EditText, temp) < v_EditText.GetLength())
			{
				StartDeletedString.push_back(temp);
				m_ComboStart.DeleteString(num - i - 1);
			}
		}
		for(int i=0;i<StartDeletedString.size();i++)
			if (getLCSlength(v_EditText, StartDeletedString[i])>=v_EditText.GetLength())
			{
				m_ComboStart.AddString(StartDeletedString[i]);
				for (std::vector<CString>::iterator it = StartDeletedString.begin(); it != StartDeletedString.end();it++)
					if (StartDeletedString[i] == *it)
					{
						StartDeletedString.erase(it);
						break;
					}
			}
		if (m_ComboStart.GetCount() == 1)	m_ComboStart.SetCurSel(0);
	}
	else {
		while (StartDeletedString.size() > 0) {
			m_ComboStart.AddString(StartDeletedString[StartDeletedString.size()-1]);
			StartDeletedString.pop_back();
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMapDialog::OnCbnEditchangeComboEnd()
{
	CString v_EditText = _T("");//用来保存当前编辑框的字符串
	m_ComboEnd.GetWindowText(v_EditText);
	if (v_EditText != (_T(""))) {
		int num = m_ComboEnd.GetCount();
		for (int i = 0; i < num; ++i) {
			CString temp;
			m_ComboEnd.GetLBText(num - i - 1, temp);
			if (getLCSlength(v_EditText, temp) < v_EditText.GetLength())
			{
				EndDeletedString.push_back(temp);
				m_ComboEnd.DeleteString(num - i - 1);
			}
		}
		for (int i = 0; i < EndDeletedString.size(); i++)
			if (getLCSlength(v_EditText, EndDeletedString[i]) >= v_EditText.GetLength())
			{
				m_ComboEnd.AddString(EndDeletedString[i]);
				for (std::vector<CString>::iterator it = EndDeletedString.begin(); it != EndDeletedString.end(); it++)
					if (EndDeletedString[i] == *it)
					{
						EndDeletedString.erase(it);
						break;
					}
			}
		if (m_ComboEnd.GetCount() == 1)	m_ComboEnd.SetCurSel(0);
	}
	else {
		while (EndDeletedString.size() > 0) {
			m_ComboEnd.AddString(EndDeletedString[EndDeletedString.size() - 1]);
			EndDeletedString.pop_back();
		}
	}
}


void CMapDialog::OnCbnSetfocusComboStart()
{
	m_ComboStart.ShowDropDown(TRUE);
	m_ComboEnd.ShowDropDown(FALSE);
	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW))); //显示鼠标
	// TODO: 在此添加控件通知处理程序代码
}


void CMapDialog::OnCbnSetfocusComboEnd()
{
	m_ComboStart.ShowDropDown(FALSE);
	m_ComboEnd.ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW))); //显示鼠标
	// TODO: 在此添加控件通知处理程序代码
}
