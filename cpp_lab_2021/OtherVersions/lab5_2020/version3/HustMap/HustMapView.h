
// HustMapView.h: CHustMapView 类的接口
//

#pragma once


class CHustMapView : public CView
{
protected: // 仅从序列化创建
	CHustMapView() noexcept;
	DECLARE_DYNCREATE(CHustMapView)
//起点，终点，拖拉状态 Add By Z
protected:
	//CPoint m_LineStart;//鼠标点击画线起点
	//CPoint m_LastLineEnd;//上次画线的终点
	//boolean m_DraggingState = false;//按下鼠标左键的同时是否拖曳鼠标

//绘图时用，add by Z
	CPoint LastStart;//左右键设置起始点时上一次的起始点
	CPoint LastEnd;//左右键设置终点时上一次的终点
	bool HaveDrawLine = false;//记录屏幕上是否已经画过路径

//显示信息时用
	boolean m_TrackingState = false;
	CToolTipCtrl m_Tooltip;

public:
	void SetHaveDrawLine() { HaveDrawLine = true; };//HaveDrawLine的set方法(在Dialog内调用)
// 特性
public:
	CHustMapDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHustMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);//以修改为调出查询路径对话框
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//擦除上次路径，设置起点
	void DrawCircle(CPoint center, LONG radius,int colors=0);//画点，colors为0时画红点，为1时画黄点
	void DrawLine(CPoint start, CPoint end);//画线
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//功能已删除
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);//ToolTip显示地点信息
	void DrawRubberLine(CPoint start, CPoint end);//功能已删除
	afx_msg void OnMouseLeave();//ToolTip取消显示地点信息
	virtual void OnInitialUpdate();//ToolTip显示地点信息
	virtual BOOL PreTranslateMessage(MSG* pMsg);//ToolTip显示地点信息
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);//设置终点信息
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);//查询
};

#ifndef _DEBUG  // HustMapView.cpp 中的调试版本
inline CHustMapDoc* CHustMapView::GetDocument() const
   { return reinterpret_cast<CHustMapDoc*>(m_pDocument); }
#endif

