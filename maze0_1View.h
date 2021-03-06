
// maze0_1View.h: Cmaze01View 클래스의 인터페이스
//

#pragma comment(lib, "winmm")
#include <afxtempl.h>
#include <mmsystem.h>
class Cmaze01View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cmaze01View();
	DECLARE_DYNCREATE(Cmaze01View)

// 특성입니다.
public:
	//페이지 
	int page;
	int infopage;
	//버튼 좌표
	CRect oneplayer;
	CRect twoplayer;
	CRect ranking;
	CRect howtoplay;
	CRect back;
	CRect easy;
	CRect normal;
	CRect hard;
	CRect returnpage;
	CRect returnpage2;
	CRect writerank;
	CRect namewrite;
	CRect namestatic;
	CRect music;
	//버튼
	CMFCButton oneplayerbutton;
	CMFCButton twoplayerbutton;
	CMFCButton rankingbutton;
	CMFCButton howtoplaybutton;
	CMFCButton backbutton;
	CMFCButton easybutton;
	CMFCButton normalbutton;
	CMFCButton hardbutton;
	CMFCButton returnpagebutton;
	CMFCButton writerankbutton;
	CMFCButton musicbutton;
	CMFCButton musicoffbutton;
	//버튼이미지
	CImage oneplayerbuttonimage;
	CImage twoplayerbuttonimage;
	CImage rankingbuttonimage;
	CImage howtoplaybuttonimage;
	CImage backbuttonimage;
	CImage easybuttonimage;
	CImage normalbuttonimage;
	CImage hardbuttonimage;
	CImage returnpagebuttonimage;
	CImage writerankbuttonimage;
	CImage musiconimage;
	CImage musicoffimage;
	//게임 플레이 좌표
	typedef struct{
		int x;
		int y;
		int turncount;
		BOOL turn;
	}player;
	player p1, p2;
	int x_max, y_max;
	int m1[13][13];
	int m2[15][15];
	int m3[17][17];
	int winner;
	int stage;
	//이미지
	CImage background;
	CImage maze_1p_6;
	CImage maze_1p_7;
	CImage maze_1p_8;
	CImage maze_2p_6;
	CImage maze_2p_7;
	CImage maze_2p_8;
	CImage title;
	CImage char1white;
	CImage char1black;
	CImage char2white;
	CImage char2black;
	CImage infoimage1;
	CImage infoimage2;
	CImage infoimage3;
	CImage rankpaper;
	//InvalidateRect용 좌표
	CRect inval1;
	CRect inval2;
	Cmaze01Doc* GetDocument() const;
	//타이머
	clock_t starttime, counttime, endtime;
	CString timetext;
	double timer, counttimer;
	//랭킹
	char name[10][3];
	double record[10];
	double newrecord;
	int writerankcheck;
	CArray<TCHAR, TCHAR> m_str;
	//사운드
	CString SoundPath;
	int onoff;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~Cmaze01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnOnePlayerClicked();
	void OnTwoPlayerClicked();
	void OnRankingClicked();
	void OnHowToPlayClicked();
	void OnEasyClicked();
	void OnNormalClicked();
	void OnHardClicked();
	void OnBackClicked();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnReturnPageClicked();
	void OnWriteRankClicked();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnMusicButtonClicked();
	void OnMusicoffButtonClicked();
};

#ifndef _DEBUG  // maze0_1View.cpp의 디버그 버전
inline Cmaze01Doc* Cmaze01View::GetDocument() const
   { return reinterpret_cast<Cmaze01Doc*>(m_pDocument); }
#endif

