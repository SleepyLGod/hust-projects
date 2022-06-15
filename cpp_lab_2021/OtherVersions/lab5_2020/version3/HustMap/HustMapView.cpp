
// HustMapView.cpp: CHustMapView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include <stdio.h>
#include "CMapDialog.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HustMap.h"
#endif

#include "HustMapDoc.h"
#include "HustMapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CHustMapView

IMPLEMENT_DYNCREATE(CHustMapView, CView)

BEGIN_MESSAGE_MAP(CHustMapView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHustMapView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CHustMapView 构造/析构

CHustMapView::CHustMapView() noexcept
{
	// TODO: 在此处添加构造代码
	LastStart = (0, 0);
	LastEnd = (0, 0);
}

CHustMapView::~CHustMapView()
{
}

BOOL CHustMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHustMapView 绘图
void CHustMapView::OnDraw(CDC* pDC)
{
	CHustMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_MapModel.GetMapFilePath() != _T("")) {
		HBITMAP hBit;
		hBit = (HBITMAP)LoadImage(NULL, pDoc->m_MapModel.GetMapFilePath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		CBitmap cBit;
		cBit.Attach(hBit);
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);

		BITMAP bitmap;
		cBit.GetBitmap(&bitmap);
		CBitmap* oldBit;
		oldBit = MemDC.SelectObject(&cBit);

		CRect rect;
		GetClientRect(&rect);
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	}

	//add by Z
	if (pDoc->m_MapModel.GetLoacationFilePath() != _T("")) {
		for (int i = 0; i < pDoc->m_MapModel.GetLocationNum(); i++)	
			DrawCircle(pDoc->m_MapModel.GetLocation(i),5);

	}

	// TODO: 在此处为本机数据添加绘制代码
}


// CHustMapView 打印


void CHustMapView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHustMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHustMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHustMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHustMapView::OnRButtonUp(UINT /* nFlags */, CPoint point)//调出查询路径对话框
{
	CPoint zero((0, 0));
	if (LastStart == zero) {
		ClientToScreen(&point);
		//OnContextMenu(this, point);
		CMapDialog dlg;
		int ret = dlg.DoModal();
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		if (ret == IDOK) {
			pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("点击了对话框的确定按钮"));
		}
		else if (ret == IDCANCEL) {
			pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("点击了对话框的取消按钮"));
		}
	}
}

void CHustMapView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHustMapView 诊断

#ifdef _DEBUG
void CHustMapView::AssertValid() const
{
	CView::AssertValid();
}

void CHustMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHustMapDoc* CHustMapView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHustMapDoc)));
	return (CHustMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CHustMapView 消息处理程序


void CHustMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (HaveDrawLine == true)
	{
		Invalidate();
		LastStart = LastEnd = (0, 0);
		HaveDrawLine = false;
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString posInfo;
	CString StartOrg;
	CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(this->GetDocument());
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	std::vector<CString> StartLocation;
	StartLocation = pHustDoc->m_MapModel.GetOrganizations(point);
	if (StartLocation.size() > 0) {
		for (std::vector<CString>::iterator start = StartLocation.begin()+1; start != StartLocation.end(); start++) {
			if (start + 1 != StartLocation.end())	StartOrg += *start + CString(_T("\n"));
			else
				StartOrg += *start;
		}
		CPoint Start = pHustDoc->m_MapModel.FindPositionByOrg(StartLocation[1]);
		if (Start != LastStart) {
			pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("起点：")+StartOrg);
			DrawCircle(LastStart, 5);
			DrawCircle(Start, 5,1);
			LastStart = Start;
		}
		else {
			pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("取消起点选择"));
			DrawCircle(Start, 5);
			LastStart = (0, 0);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CHustMapView::DrawCircle(CPoint center, LONG radius,int color) {
	CClientDC dc(this);
	CBrush brush, * oldbrush;
	if (color == 0)	brush.CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
	else	brush.CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
	oldbrush = dc.SelectObject(&brush);
	dc.Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
	dc.SelectObject(oldbrush);
}
void CHustMapView::DrawLine(CPoint start, CPoint end) {
	CClientDC dc(this);
	CPen pen(PS_SOLID, 3, RGB(0xFF, 0x00, 0x00));
	CPen* oldPen;
	oldPen = dc.SelectObject(&pen);
	dc.MoveTo(start.x, start.y);
	dc.LineTo(end.x, end.y);
	dc.SelectObject(oldPen);
}

void CHustMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//this->DrawLine(this->m_LineStart, point);
	//this->m_DraggingState = false;
	CView::OnLButtonUp(nFlags, point);
}


void CHustMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nFlags & MK_LBUTTON)
	//{
	//	if (this->m_DraggingState) {
	//		this->DrawRubberLine(this->m_LineStart, this->m_LastLineEnd);
	//	}
	//	this->DrawRubberLine(this->m_LineStart, point);
	//	this->m_LastLineEnd = point;
	//	this->m_DraggingState = true;
	//}
	//else {
		static CPoint lastPoint(0, 0);
		if (lastPoint == point) {
			return;
		}
		CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(this->GetDocument());
		std::vector<CString> orgs = pHustDoc->m_MapModel.GetOrganizations(point);
		CString posInfo;
		if (orgs.size() > 0) {
			for (std::vector<CString>::iterator start = orgs.begin(); start != orgs.end(); start++) {
				if (start + 1 != orgs.end())	posInfo += *start + CString(_T("\n"));
				else
					posInfo += *start;
			}
		}
		m_Tooltip.UpdateTipText(posInfo, this);
		CPoint pt = point;
		this->ClientToScreen(&pt);
		CToolInfo sTinfo;
		m_Tooltip.GetToolInfo(sTinfo, this);
		sTinfo.uFlags = TTF_TRACK;
		m_Tooltip.SetToolInfo(&sTinfo);
		//设置ToolTip的显示位置
		m_Tooltip.SendMessage(TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x + 5, pt.y + 5));
		if (orgs.size() > 0) {
			m_Tooltip.SendMessage(TTM_TRACKACTIVATE, TRUE, (LPARAM)&sTinfo);
		}
		else {
			m_Tooltip.SendMessage(TTM_TRACKACTIVATE, false, (LPARAM)&sTinfo);
		}
		lastPoint = point;
		if (!m_TrackingState)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			m_TrackingState = _TrackMouseEvent(&tme);
		}
	//}
	CView::OnMouseMove(nFlags, point);
}

void CHustMapView::DrawRubberLine(CPoint start, CPoint end)
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(PS_SOLID, 3, RGB(0xff, 0x00, 0x00));
	CPen* oldPen;
	oldPen = dc.SelectObject(&pen);
	dc.MoveTo(start.x, start.y);
	dc.LineTo(end.x, end.y);
	dc.SelectObject(oldPen);
}

void CHustMapView::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CToolInfo sTinfo;
	m_Tooltip.GetToolInfo(sTinfo, this);
	sTinfo.uFlags = TTF_TRACK;
	m_Tooltip.SetToolInfo(&sTinfo);
	m_Tooltip.SendMessage(TTM_TRACKACTIVATE, false, (LPARAM)&sTinfo);
	m_TrackingState = FALSE;
	CView::OnMouseLeave();
}


void CHustMapView::OnInitialUpdate()
{
	// TODO: 在此添加专用代码和/或调用基类
	CView::OnInitialUpdate();
	this->EnableToolTips(TRUE);
	m_Tooltip.Create(this);
	m_Tooltip.Activate(TRUE);
	m_Tooltip.AddTool(this, _T("这是Tooltip"));
	m_Tooltip.SetTipTextColor(RGB(0, 0, 255));
	m_Tooltip.SetDelayTime(1000);
	m_Tooltip.SetMaxTipWidth(150);
}


BOOL CHustMapView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_Tooltip.RelayEvent(pMsg);
	return CView::PreTranslateMessage(pMsg);
}


void CHustMapView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint zero((0, 0));
	if (LastStart != zero) {
		CString posInfo;
		CString EndOrg;
		CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(this->GetDocument());
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		std::vector<CString> EndLocation;
		EndLocation = pHustDoc->m_MapModel.GetOrganizations(point);
		if (EndLocation.size() > 0) {
			for (std::vector<CString>::iterator start = EndLocation.begin() + 1; start != EndLocation.end(); start++) {
				if (start + 1 != EndLocation.end())	EndOrg += *start + CString(_T("\n"));
				else
					EndOrg += *start;
			}
			CPoint End = pHustDoc->m_MapModel.FindPositionByOrg(EndLocation[1]);
			if (End != LastEnd) {
				pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("终点：")+EndOrg);
				DrawCircle(LastEnd, 5);
				DrawCircle(End, 5, 1);
				LastEnd = End;
			}
			else {
				pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("取消终点选择"));
				DrawCircle(End, 5);
				LastEnd = (0, 0);
			}
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CHustMapView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (LastStart != CPoint(0, 0) && LastEnd != CPoint(0, 0)) {
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CHustMapDoc* pHustDoc = dynamic_cast<CHustMapDoc*>(pMainFrm->GetActiveDocument());
		std::vector<CPoint>	path = pHustDoc->m_MapModel.FindShortestPath(LastStart, LastEnd);
		CHustMapView* pHustMapView = dynamic_cast<CHustMapView*>(pMainFrm->GetActiveView());
		for (int i = 0; i < path.size() - 1; i++)
		{
			pHustMapView->DrawCircle(path[i], 5, 1); pHustMapView->DrawCircle(path[i + 1], 5, 1);
			pHustMapView->DrawLine(path[i], path[i + 1]);
		}
		HaveDrawLine = true;
		LastStart = LastEnd = (0, 0);
	}
	CView::OnLButtonDblClk(nFlags, point);
}
