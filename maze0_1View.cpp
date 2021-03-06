
// maze0_1View.cpp: Cmaze01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "maze0_1.h"
#endif


#include "maze0_1Doc.h"
#include "maze0_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmaze01View

IMPLEMENT_DYNCREATE(Cmaze01View, CView)

BEGIN_MESSAGE_MAP(Cmaze01View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, OnOnePlayerClicked)
	ON_BN_CLICKED(102, OnTwoPlayerClicked)
	ON_BN_CLICKED(103, OnRankingClicked)
	ON_BN_CLICKED(104, OnHowToPlayClicked)
	ON_BN_CLICKED(105, OnEasyClicked)
	ON_BN_CLICKED(106, OnNormalClicked)
	ON_BN_CLICKED(107, OnHardClicked)
	ON_BN_CLICKED(108, OnBackClicked)
	ON_BN_CLICKED(109, OnReturnPageClicked)
	ON_BN_CLICKED(110, OnWriteRankClicked)
	ON_BN_CLICKED(111, OnMusicButtonClicked)
	ON_BN_CLICKED(112, OnMusicoffButtonClicked)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Cmaze01View 생성/소멸

Cmaze01View::Cmaze01View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//시작 페이지
	page = 1;
	infopage = 1;
	//음악
	onoff = 0;
	//버튼 좌표 설정
	oneplayer = CRect(900 / 2 - 150, 500 / 3 - 30, 900 / 2 + 150, 500 / 3 + 30);
	twoplayer = CRect(900 / 2 - 150, 500 / 2 - 30, 900 / 2 + 150, 500 / 2 + 30);
	ranking = CRect(900 / 2 - 150, 500 / 1.5 - 30, 900 / 2 - 10, 500 / 1.5 + 10);
	howtoplay = CRect(900 / 2 + 10, 500 / 1.5 - 30, 900 / 2 + 150, 500 / 1.5 + 10);
	back = CRect(850, 10, 890, 50);
	easy = CRect(900 / 2 - 150, 500 / 3 - 30, 900 / 2 + 150, 500 / 3 + 30);
	normal = CRect(900 / 2 - 150, 500 / 2 - 30, 900 / 2 + 150, 500 / 2 + 30);
	hard = CRect(900 / 2 - 150, 500 / 1.5 - 30, 900 / 2 + 150, 500 / 1.5 + 30);
	returnpage = CRect(900 / 2 - 150, 500 / 1.5 - 30, 900 / 2 - 10, 500 / 1.5 + 10);
	returnpage2 = CRect(900 / 2 -70, 500 / 1.5 - 30, 900 / 2 + 70, 500 / 1.5 + 10);
	writerank = CRect(900 / 2 + 10, 500 / 1.5 - 30, 900 / 2 + 150, 500 / 1.5 + 10);
	namewrite = CRect(900/2-95,500/2-25,900/2+115,500/2+25);
	namestatic = CRect(900/2-110,500/2-75 ,900/2+110,500/2-25);
	music = CRect(850,60,890,100);
	//미로 설정
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			m1[i][j] = 0;
	for (int i = 0; i < 13; i++) {
		m1[0][i] = 1;
		m1[i][0] = 1;
		m1[i][12] = 1;
		m1[12][i] = 1;
	}
	
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			m2[i][j] = 0;
	for (int i = 0; i < 15; i++) {
		m2[0][i] = 1;
		m2[i][0] = 1;
		m2[i][14] = 1;
		m2[14][i] = 1;
	}
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 17; j++)
			m3[i][j] = 0;
	for (int i = 0; i < 17; i++) {
		m3[0][i] = 1;
		m3[i][0] = 1;
		m3[i][16] = 1;
		m3[16][i] = 1;
	}

	//미로 입력
	for (int i = 1; i < 12; i++)
		for (int j = 1; j < 12; j++) {
			if (j % 2 == 0 && i % 2 == 0)
				m1[i][j] = 1;
		}
	for(int i = 1; i < 14;i++)
		for (int j = 1; j < 14; j++) {
			if (j % 2 == 0 && i % 2 == 0)
				m2[i][j] = 1;
		}
	for (int i = 1; i < 16; i++)
		for (int j = 1; j < 16; j++) {
			if (j % 2 == 0 && i % 2 == 0)
				m3[i][j] = 1;
		}
	p1.turn = p2.turn = false;
	p1.turncount = p2.turncount = 0;
	stage = 1;
	//사운드 불러오기
	SoundPath = ".\\res\\mazeimage\\배경음.wav";
	PlaySound(SoundPath, AfxGetInstanceHandle(),SND_ASYNC|SND_LOOP);
	//이미지 불러오기
	background.Load(CString(".\\res\\mazeimage\\background1.jpg"));
	maze_1p_6.Load(CString(".\\res\\mazeimage\\1인모드6-360px.jpg"));
	maze_1p_7.Load(CString(".\\res\\mazeimage\\1인모드7-420px.jpg"));
	maze_1p_8.Load(CString(".\\res\\mazeimage\\1인모드8-480px.jpg"));
	maze_2p_6.Load(CString(".\\res\\mazeimage\\2인모드6-360px.jpg"));
	maze_2p_7.Load(CString(".\\res\\mazeimage\\2인모드7-420px.jpg"));
	maze_2p_8.Load(CString(".\\res\\mazeimage\\2인모드8-480px.jpg"));
	title.Load(CString(".\\res\\mazeimage\\title1.jpg"));
	char1white.Load(CString(".\\res\\mazeimage\\흰뚱.png"));
	char1black.Load(CString(".\\res\\mazeimage\\검뚱.png"));
	char2white.Load(CString(".\\res\\mazeimage\\흰스.png"));
	char2black.Load(CString(".\\res\\mazeimage\\검스.png"));
	oneplayerbuttonimage.Load(CString(".\\res\\mazeimage\\1인모드.jpg"));
	twoplayerbuttonimage.Load(CString(".\\res\\mazeimage\\2인모드.jpg"));
	rankingbuttonimage.Load(CString(".\\res\\mazeimage\\랭킹.jpg"));
	howtoplaybuttonimage.Load(CString(".\\res\\mazeimage\\조작방법.png"));
	backbuttonimage.Load(CString(".\\res\\mazeimage\\뒤로가기.png"));
	easybuttonimage.Load(CString(".\\res\\mazeimage\\쉬움.jpg"));
	normalbuttonimage.Load(CString(".\\res\\mazeimage\\보통.jpg"));
	hardbuttonimage.Load(CString(".\\res\\mazeimage\\어려움.jpg"));
	returnpagebuttonimage.Load(CString(".\\res\\mazeimage\\처음으로.jpg"));
	writerankbuttonimage.Load(CString(".\\res\\mazeimage\\랭킹등록.jpg"));
	infoimage1.Load(CString(".\\res\\mazeimage\\설명1.png"));
	infoimage2.Load(CString(".\\res\\mazeimage\\설명2.png"));
	infoimage3.Load(CString(".\\res\\mazeimage\\설명3.png"));
	musiconimage.Load(CString(".\\res\\mazeimage\\musicon.jpg"));
	musicoffimage.Load(CString(".\\res\\mazeimage\\musicoff.jpg"));
	rankpaper.Load(CString(".\\res\\mazeimage\\파피루스.jpg"));

	//버튼이미지 설정
	oneplayerbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	oneplayerbutton.m_bDrawFocus = FALSE;
	oneplayerbutton.m_bTransparent = TRUE;
	oneplayerbutton.SetImage(oneplayerbuttonimage);
	twoplayerbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	twoplayerbutton.m_bDrawFocus = FALSE;
	twoplayerbutton.m_bTransparent = TRUE;
	twoplayerbutton.SetImage(twoplayerbuttonimage);
	rankingbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	rankingbutton.m_bDrawFocus = FALSE;
	rankingbutton.m_bTransparent = TRUE;
	rankingbutton.SetImage(rankingbuttonimage);
	howtoplaybutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	howtoplaybutton.m_bDrawFocus = FALSE;
	howtoplaybutton.m_bTransparent = TRUE;
	howtoplaybutton.SetImage(howtoplaybuttonimage);
	backbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	backbutton.m_bDrawFocus = FALSE;
	backbutton.m_bTransparent = TRUE;
	backbutton.SetImage(backbuttonimage);
	easybutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	easybutton.m_bDrawFocus = FALSE;
	easybutton.m_bTransparent = TRUE;
	easybutton.SetImage(easybuttonimage);
	normalbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	normalbutton.m_bDrawFocus = FALSE;
	normalbutton.m_bTransparent = TRUE;
	normalbutton.SetImage(normalbuttonimage);
	hardbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	hardbutton.m_bDrawFocus = FALSE;
	hardbutton.m_bTransparent = TRUE;
	hardbutton.SetImage(hardbuttonimage);
	returnpagebutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	returnpagebutton.m_bDrawFocus = FALSE;
	returnpagebutton.m_bTransparent = TRUE;
	returnpagebutton.SetImage(returnpagebuttonimage);
	writerankbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	writerankbutton.m_bDrawFocus = FALSE;
	writerankbutton.m_bTransparent = TRUE;
	writerankbutton.SetImage(writerankbuttonimage);
	musicbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	musicbutton.m_bDrawFocus = FALSE;
	musicbutton.m_bTransparent = TRUE;
	musicbutton.SetImage(musiconimage);
	musicoffbutton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	musicoffbutton.m_bDrawFocus = FALSE;
	musicoffbutton.m_bTransparent = TRUE;
	musicoffbutton.SetImage(musicoffimage);
	//랭킹
	timetext.Format(_T("시간 : 000초"));
	CFile file;
	CFileException e;

	if (!file.Open(_T("record.txt"), CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate, &e)) {
		e.ReportError();
		return;
	}

	for (int i = 0; i < 10; i++) {
		name[i][0] = ' ';
		name[i][1] = ' ';
		name[i][2] = ' ';
		record[i] = 10001.0;
	}
	if (file.GetLength() == 0) {
		for (int i = 0; i < 10; i++) {
			file.Write(&name[i][0], sizeof(name[i][0]));
			file.Write(&name[i][1], sizeof(name[i][1]));
			file.Write(&name[i][2], sizeof(name[i][2]));
			file.Write(&record[i], sizeof(record[i]));
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			file.Read(&name[i][0], sizeof(name[i][0]));
			file.Read(&name[i][1], sizeof(name[i][1]));
			file.Read(&name[i][2], sizeof(name[i][2]));
			file.Read(&record[i], sizeof(record[i]));
		}
	}
	file.Close();
	writerankcheck = 0;
	m_str.RemoveAll();
	winner = 0;
}

Cmaze01View::~Cmaze01View()
{
}

BOOL Cmaze01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	
	return CView::PreCreateWindow(cs);
}

// Cmaze01View 그리기

void Cmaze01View::OnDraw(CDC* pDC)
{
	Cmaze01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);
	background.Draw(*pDC, 0, 0);
	if (page == 1) {
		pDC->SetTextAlign(TA_CENTER);
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(180, _T("맑은 고딕"));
		pDC->SelectObject(&font);
		pDC->TextOut(rect.right / 2, rect.bottom / 1.4, CString("[클릭하세요]"));
		title.Draw(*pDC, rect.right / 2-150, rect.bottom / 5);
	}
	else if (page == 2) {
		(GetDlgItem(101))->ShowWindow(TRUE);
		(GetDlgItem(102))->ShowWindow(TRUE);
		(GetDlgItem(103))->ShowWindow(TRUE);
		(GetDlgItem(104))->ShowWindow(TRUE);
		(GetDlgItem(108))->ShowWindow(TRUE);
		if(onoff == 0)
			(GetDlgItem(111))->ShowWindow(TRUE);
		else
			(GetDlgItem(112))->ShowWindow(TRUE);
	}
	else if (page == 3) {
		(GetDlgItem(108))->ShowWindow(TRUE);
		CFont font;
		font.CreatePointFont(150, _T("맑은 고딕"));
		pDC->SelectObject(&font);
		if (stage == 1) {
			maze_1p_6.Draw(*pDC, 900 / 2 - 180, 500 / 2 - 180);
			if ((p1.x + p1.y) % 4 == 0)
				char1white.Draw(*pDC, (p1.x / 2) * 60 + 270 + 7.5, (p1.y / 2) * 60 + 70);
			else
				char1black.Draw(*pDC, (p1.x / 2) * 60 + 270 + 7.5, (p1.y / 2) * 60 + 70);
		}
		else if (stage == 2) {
			maze_1p_7.Draw(*pDC, 240, 40);
			if ((p1.x + p1.y) % 4 == 0)
				char1white.Draw(*pDC, (p1.x / 2) * 60 + 240 + 7.5, (p1.y / 2) * 60 + 40);
			else
				char1black.Draw(*pDC, (p1.x / 2) * 60 + 240 + 7.5, (p1.y / 2) * 60 + 40);
		}
		else if (stage == 3) {
			maze_1p_8.Draw(*pDC, 900 / 2 - 240, 500 / 2 - 240);
			if ((p1.x + p1.y) % 4 == 0)
				char1white.Draw(*pDC, (p1.x / 2) * 60 + 210 + 7.5, (p1.y / 2) * 60 + 10);
			else
				char1black.Draw(*pDC, (p1.x / 2) * 60 + 210 + 7.5, (p1.y / 2) * 60 + 10);
		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(10, 10, timetext);
	}
	else if (page == 4) {
		(GetDlgItem(105))->ShowWindow(TRUE);
		(GetDlgItem(106))->ShowWindow(TRUE);
		(GetDlgItem(107))->ShowWindow(TRUE);
		(GetDlgItem(108))->ShowWindow(TRUE);
	}
	else if (page == 5) {
		//pDC->SetBkMode(TRANSPARENT);
		//pDC->TextOut(0, 0, CString("랭킹 화면"));
		rankpaper.Draw(*pDC,0,0);
		(GetDlgItem(108))->ShowWindow(TRUE);
		CFile file;
		CFileException e;
		if (!file.Open(_T("record.txt"), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate, &e)) {
			e.ReportError();
			return;
		}
		for (int i = 0; i < 10; i++) {
			file.Read(&name[i][0], sizeof(name[i][0]));
			file.Read(&name[i][1], sizeof(name[i][1]));
			file.Read(&name[i][2], sizeof(name[i][2]));
			file.Read(&record[i], sizeof(record[i]));
		}
		pDC->SetTextAlign(TA_CENTER);
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(180, _T("맑은 고딕"));
		pDC->SelectObject(&font);
		for (int i = 0; i < 10; i++) {
			if (record[i] < 10000) {
				CString rank;
				rank.Format(_T("%d위 %c%c%c %.2lf초"), i + 1, name[i][0], name[i][1], name[i][2], record[i]);
				pDC->SetBkMode(TRANSPARENT);
				pDC->TextOut(460, 130 + i * 30, rank);
			}
			else {
				CString rank;
				rank.Format(_T("---------"));
				pDC->TextOut(460, 130 + i * 30, rank);
			}
		}
		file.Close();
		CFont font1;
		font1.CreatePointFont(300, _T("맑은 고딕"));
		pDC->SelectObject(&font1);
		CString rankstr = _T("위대한 개척자");
		pDC->TextOut(460,50,rankstr);
	}
	else if (page == 6) {
		pDC->SetBkMode(TRANSPARENT);
		//pDC->TextOut(0, 0, CString("조작 설명 화면"));
		(GetDlgItem(108))->ShowWindow(TRUE);
		if (infopage == 1) {
			infoimage1.Draw(*pDC, 0, 0);
			pDC->SetBkMode(TRANSPARENT);
			CFont font;
			font.CreatePointFont(180, _T("맑은 고딕"));
			pDC->SelectObject(&font);
			pDC->DrawText(CString("다음"), CRect(775,425,825,455) , 0);
		}
		else if (infopage == 2) {
			infoimage2.Draw(*pDC, 0, 0);
			pDC->SetBkMode(TRANSPARENT);
			CFont font;
			font.CreatePointFont(180, _T("맑은 고딕"));
			pDC->SelectObject(&font);
			pDC->DrawText(CString("다음"), CRect(775, 425, 825, 455), 0);
		}
		else if (infopage == 3)
			infoimage3.Draw(*pDC,0,0);

	}
	else if (page == 7) {
		(GetDlgItem(108))->ShowWindow(TRUE);
		maze_2p_6.Draw(*pDC, 900 / 2 - 180, 500 / 2 - 180);
		if ((p1.x + p1.y) % 4 == 0)
			char1white.Draw(*pDC, (p1.x / 2) * 60 + 270 + 7.5, (p1.y / 2) * 60 + 70);
		else
			char1black.Draw(*pDC, (p1.x / 2) * 60 + 270 + 7.5, (p1.y / 2) * 60 + 70);
		if ((p2.x + p2.y) % 4 == 0)
			char2white.Draw(*pDC, (p2.x / 2) * 60 + 270, (p2.y / 2) * 60 + 70 + 2);
		else
			char2black.Draw(*pDC, (p2.x / 2) * 60 + 270, (p2.y / 2) * 60 + 70 + 2);
	}
	else if (page == 8) {
		(GetDlgItem(108))->ShowWindow(TRUE);
		maze_2p_7.Draw(*pDC, 240, 40);
		if ((p1.x + p1.y) % 4 == 0)
			char1white.Draw(*pDC, (p1.x / 2) * 60 + 240 + 7.5, (p1.y / 2) * 60 + 40);
		else
			char1black.Draw(*pDC, (p1.x / 2) * 60 + 240 + 7.5, (p1.y / 2) * 60 + 40);
		if ((p2.x + p2.y) % 4 == 0)
			char2white.Draw(*pDC, (p2.x / 2) * 60 + 240, (p2.y / 2) * 60 + 40+2);
		else
			char2black.Draw(*pDC, (p2.x / 2) * 60 + 240, (p2.y / 2) * 60 + 40+2);
	}
	else if (page == 9) {
		(GetDlgItem(108))->ShowWindow(TRUE);
		maze_2p_8.Draw(*pDC, 900 / 2 - 240, 500 / 2 - 240);
		if ((p1.x + p1.y) % 4 == 0)
			char1white.Draw(*pDC, (p1.x / 2) * 60 + 210 + 7.5, (p1.y / 2) * 60 + 10);
		else
			char1black.Draw(*pDC, (p1.x / 2) * 60 + 210 + 7.5, (p1.y / 2) * 60 + 10);
		if ((p2.x + p2.y) % 4 == 0)
			char2white.Draw(*pDC, (p2.x / 2) * 60 + 210, (p2.y / 2) * 60 + 10 + 2);
		else
			char2black.Draw(*pDC, (p2.x / 2) * 60 + 210, (p2.y / 2) * 60 + 10 + 2);
	}
	else if (page == 10) {
		pDC->SetBkMode(TRANSPARENT);
		CFont font1;
		font1.CreatePointFont(400, _T("맑은 고딕"));
		pDC->SelectObject(&font1);
		pDC->DrawText(CString("1인 모드 클리어!"), CRect(900/2-200, 100,900/2+200, 200), DT_CENTER);
		returnpagebutton.MoveWindow(returnpage);
		(GetDlgItem(109))->ShowWindow(TRUE);
		(GetDlgItem(110))->ShowWindow(TRUE);
		KillTimer(0);
		timetext.Format(_T("시간 : 000초"));
		CFont font2;
		font2.CreatePointFont(150,_T("맑은 고딕"));
		pDC->SelectObject(&font2);
		pDC->DrawText(CString("이니셜을 입력해주세요."), &namestatic, DT_CENTER);
		CFont font3;
		font3.CreatePointFont(300,_T("맑은 고딕"));
		pDC->SelectObject(&font3);
		if (writerankcheck == 0)
			pDC->DrawText(m_str.GetData(), m_str.GetSize(), &namewrite, DT_CENTER);
		else
			pDC->DrawText(CString("등록 완료!"), &namewrite, 0);
	}
	else if (page == 11) {
		pDC->SetBkMode(TRANSPARENT);
		CFont font1;
		font1.CreatePointFont(400, _T("맑은 고딕"));
		pDC->SelectObject(&font1);
		if (winner == 1)
			pDC->DrawText(CString("뚱이 승리!"), CRect(900 / 2 - 200, 150, 900 / 2 + 200, 250), DT_CENTER);
		else if(winner == 2)
			pDC->DrawText(CString("스폰지밥 승리!"), CRect(900 / 2 - 200, 150, 900 / 2 + 200, 250), DT_CENTER);
		returnpagebutton.MoveWindow(returnpage2);
		(GetDlgItem(109))->ShowWindow(TRUE);
	}
	
}


// Cmaze01View 진단

#ifdef _DEBUG
void Cmaze01View::AssertValid() const
{
	CView::AssertValid();
}

void Cmaze01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmaze01Doc* Cmaze01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmaze01Doc)));
	return (Cmaze01Doc*)m_pDocument;
}
#endif //_DEBUG


// Cmaze01View 메시지 처리기


void Cmaze01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CString str;
	str.Format(_T("x : %d, y : %d, page : %d"), rect.right, rect.bottom, page);
	if (page == 1) {
		page = 2;
		Invalidate();
	}
	else if (page == 6) {
		if (infopage == 1 || infopage == 2) {
			if (point.x <= 825 && point.x >= 775 && point.y <= 455 && point.y >= 425)
				infopage++;
			Invalidate();
		}
	}
	
	CView::OnLButtonDown(nFlags, point);
}


BOOL Cmaze01View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nHitTest == HTCLIENT) {
		if (page == 1)
		{
			::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			return TRUE;
		}
		else if (page == 2) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1, rgn2, rgn3, rgn4, rgn5, rgn6;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0,0,1,1);
			rgn1.CreateRectRgn(oneplayer.left, oneplayer.top, oneplayer.right, oneplayer.bottom);
			rgn2.CreateRectRgn(twoplayer.left, twoplayer.top, twoplayer.right, twoplayer.bottom);
			rgn3.CreateRectRgn(ranking.left, ranking.top, ranking.right, ranking.bottom);
			rgn4.CreateRectRgn(howtoplay.left, howtoplay.top, howtoplay.right, howtoplay.bottom);
			rgn5.CreateRectRgn(back.left,back.top,back.right,back.bottom);
			rgn6.CreateRectRgn(music.left, music.top, music.right, music.bottom);
			rgn.CombineRgn(&rgn1,&rgn2, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn3, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn4, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn5, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn6, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
				return TRUE;
		}
		else if (page == 3) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 4) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1, rgn2, rgn3, rgn4;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn2.CreateRectRgn(easy.left, easy.top, easy.right, easy.bottom);
			rgn3.CreateRectRgn(normal.left, normal.top, normal.right, normal.bottom);
			rgn4.CreateRectRgn(hard.left, hard.top, hard.right, hard.bottom);
			rgn.CombineRgn(&rgn1, &rgn2, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn3, RGN_OR);
			rgn.CombineRgn(&rgn, &rgn4, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 5) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 6) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1, rgn2;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			if (infopage == 1 || infopage == 2) {
				rgn2.CreateRectRgn(775, 425, 825, 455);
				rgn.CombineRgn(&rgn1, &rgn2, RGN_OR);
			}
			else
				rgn.CombineRgn(&rgn,&rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 7) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 8) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 9) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(back.left, back.top, back.right, back.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 10) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1, rgn2;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(returnpage.left, returnpage.top, returnpage.right, returnpage.bottom);
			rgn2.CreateRectRgn(writerank.left, writerank.top, writerank.right, writerank.bottom);
			rgn.CombineRgn(&rgn1, &rgn2, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
		else if (page == 11) {
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			CRgn rgn, rgn1;
			CRect rect;
			GetClientRect(&rect);
			rgn.CreateRectRgn(0, 0, 1, 1);
			rgn1.CreateRectRgn(returnpage2.left, returnpage2.top, returnpage2.right, returnpage2.bottom);
			rgn.CombineRgn(&rgn, &rgn1, RGN_OR);
			if (rgn.PtInRegion(point))
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\click.ani")));
			else
				::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
			return TRUE;
		}
	}
	else
	{
		::SetCursor(LoadCursorFromFile(_T(".\\res\\mazeimage\\arrow.cur")));
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void Cmaze01View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
}


int Cmaze01View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	oneplayerbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, oneplayer, this, 101);
	twoplayerbutton.Create(_T(""),WS_CHILD | BS_PUSHBUTTON, twoplayer, this, 102);
	rankingbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, ranking, this, 103);
	howtoplaybutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, howtoplay, this, 104);
	easybutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, easy, this, 105);
	normalbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, normal, this, 106);
	hardbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, hard, this, 107);
	backbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, back, this, 108);
	returnpagebutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, returnpage, this, 109);
	writerankbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, writerank, this, 110);
	musicbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, music, this, 111);
	musicoffbutton.Create(_T(""), WS_CHILD | BS_PUSHBUTTON, music, this, 112);
	return 0;
}


void Cmaze01View::OnOnePlayerClicked()
{
	starttime = clock();
	page = 3;
	p1.x = p1.y = 11;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			m1[i][j] = 0;
	for (int i = 0; i < 13; i++) {
		m1[0][i] = 1;
		m1[i][0] = 1;
		m1[i][12] = 1;
		m1[12][i] = 1;
	}
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			m2[i][j] = 0;
	for (int i = 0; i < 15; i++) {
		m2[0][i] = 1;
		m2[i][0] = 1;
		m2[i][14] = 1;
		m2[14][i] = 1;
	}
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 17; j++)
			m3[i][j] = 0;
	for (int i = 0; i < 17; i++) {
		m3[0][i] = 1;
		m3[i][0] = 1;
		m3[i][16] = 1;
		m3[16][i] = 1;
	}
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
	SetTimer(0, 1000, NULL);
	int j = rand() % 3 + 1; //맵 종류 결정
	int k = rand()*(rand()+1) % 3 + 1;
	int l = rand()*(rand()+1)*(rand()+2) % 3 + 1;
	if (j == 1)			//벽설정
	{
		MessageBox(_T("6 - 1번 벽"));
		m1[1][2] = m1[1][6] = m1[1][10] = 1;
		m1[2][5] = 1;
		m1[3][2] = m1[3][8] = 1;
		m1[4][7] = m1[4][11] = 1;
		m1[5][4] = m1[5][6] = m1[5][8] = 1;
		m1[6][3] = m1[6][9] = 1;
		m1[7][4] = 1;
		m1[8][1] = m1[8][7] = m1[8][11] = 1;
		m1[9][4] = m1[9][6] = 1;
		m1[11][6] = m1[11][8] = 1;
	}
	else if (j == 2)	//벽설정
	{
		MessageBox(_T("6 - 2번 벽"));
		m1[2][1] = m1[2][5] = m1[2][9] = 1;
		m1[3][11] = 1;
		m1[4][3] = m1[4][7] = 1;
		m1[5][2] = m1[5][6] = m1[5][10] = 1;
		m1[6][1] = m1[6][5] = m1[6][11] = 1;
		m1[7][6] = m1[7][10] = 1;
		m1[8][1] = m1[8][3] = 1;
		m1[9][2] = m1[9][8] = 1;
		m1[10][9] = m1[10][11] = 1;
		m1[11][4] = 1;
	}
	else if (j == 3)	//벽설정
	{
		MessageBox(_T("6 - 3번 벽"));
		m1[1][2] = 1;
		m1[2][3] = m1[2][5] = m1[2][9] = 1;
		m1[3][4] = 1;
		m1[4][7] = m1[4][9] = 1;
		m1[5][2] = m1[5][8] = 1;
		m1[6][3] = m1[6][5] = m1[6][11] = 1;
		m1[7][2] = m1[7][10] = 1;
		m1[8][3] = m1[8][7] = m1[8][9] = 1;
		m1[9][4] = 1;
		m1[10][9] = 1;
		m1[11][2] = m1[11][6] = 1;
	}
	if (k == 1)
	{
		MessageBox(_T("7 -1번 벽"));
		m2[1][2] = m2[1][8] = m2[1][12] = 1;
		m2[2][3] = 1;
		m2[3][2] = m2[3][6] = m2[3][10] = m2[3][12] = 1;
		m2[4][5] = 1;
		m2[5][8] = 1;
		m2[6][1] = m2[6][9] = m2[6][13] = 1;
		m2[7][4] = m2[7][8] = 1;
		m2[8][1] = m2[8][5] = m2[8][7] = m2[8][9] = m2[8][11] = 1;
		m2[9][4] = m2[9][8] = 1;
		m2[10][3] = m2[10][13] = 1;
		m2[11][4] = m2[11][6] = m2[11][8] = m2[11][10] = m2[11][12] = 1;
		m2[12][1] = 1;
		m2[13][6] = m2[13][10] = 1;
	}
	else if (k == 2)
	{
		MessageBox(_T("7 -2번 벽"));
		m2[1][2] = m2[1][6] = 1;
		m2[2][11] = m2[2][13] = 1;
		m2[3][4] = m2[3][6] = m2[3][8] = 1;
		m2[4][1] = m2[4][9] = m2[4][11] = 1;
		m2[5][2] = m2[5][4] = 1;
		m2[6][7] = m2[6][13] = 1;
		m2[7][6] = m2[7][10] = 1;
		m2[8][1] = m2[8][5] = m2[8][9] = m2[8][11] = 1;
		m2[9][2] = m2[9][4] = m2[9][12] = 1;
		m2[10][7] = m2[10][13] = 1;
		m2[11][6] = m2[11][11] = 1;
		m2[12][1] = m2[12][3] = m2[12][11] = 1;
		m2[13][6] = m2[13][8] = 1;
	}
	else if (k == 3)
	{
		MessageBox(_T("7 - 3번 벽"));
		m2[1][8] = m2[1][12] = 1;
		m2[2][1] = m2[2][5] = m2[2][11] = 1;
		m2[3][2] = m2[3][6] = m2[3][10] = 1;
		m2[4][3] = m2[4][9] = m2[4][13] = 1;
		m2[5][6] = m2[5][12] = 1;
		m2[6][1] = m2[6][5] = m2[6][11] = m2[6][13] = 1;
		m2[7][4] = m2[7][8] = m2[7][12] = 1;
		m2[8][3] = m2[8][5] = 1;
		m2[10][1] = m2[10][7] = 1;
		m2[11][2] = m2[11][6] = m2[11][10] = 1;
		m2[12][5] = m2[12][9] = m2[12][11] = 1;
		m2[13][6] = m2[13][10] = 1;
	}
	if (l == 1)
	{
		MessageBox(_T("8 - 1번 벽"));
		m3[1][2] = m3[1][8] = 1;
		m3[2][3] = m3[2][7]= m3[2][13] = m3[2][15] = 1;
		m3[3][10] = m3[3][14] = 1;
		m3[4][5] = m3[4][7] = 1;
		m3[5][2] = m3[5][6] = m3[5][12] = 1;
		m3[6][1] = m3[6][11] = m3[6][13] = 1;
		m3[7][4] = m3[7][6] = m3[7][12] = 1;
		m3[8][3] = m3[8][7] = m3[8][15] = 1;
		m3[9][2] = m3[9][12] = 1;
		m3[10][5] = m3[10][11] = m3[10][13] = 1;
		m3[11][6] = m3[11][10] = 1;
		m3[12][3] = m3[12][7] = m3[12][15]= 1;
		m3[13][1] = m3[13][8] = m3[13][12] = 1;
		m3[14][3] = m3[14][7] = m3[14][13] = 1;
		m3[15][6] = 1;
	}
	else if (l == 2)
	{
		MessageBox(_T("8 - 2번 벽"));
		m3[1][8] = 1;
		m3[2][5] = m3[2][9] = m3[2][15] = 1;
		m3[3][2] = m3[3][6] = m3[3][12] = 1;
		m3[4][1] = m3[4][9] = m3[4][13] = 1;
		m3[5][2] = m3[5][6] = m3[5][10] = 1;
		m3[6][5] = m3[6][7] = 1;
		m3[7][2] = m3[7][6] = m3[7][14] = 1;
		m3[8][3] = m3[8][9] = m3[8][13] = m3[8][15] = 1;
		m3[9][10] = 1;
		m3[10][1] = m3[10][9] = m3[10][11] = m3[10][15] = 1;
		m3[11][6] = m3[11][10] = m3[11][14] = 1;
		m3[12][1] = m3[12][13] = 1;
		m3[13][4] = m3[13][8] = m3[13][14] = 1;
		m3[14][3] = m3[14][7] = 1;
		m3[15][6] = m3[15][10] = 1;
	}
	else if (l == 3)
	{
		MessageBox(_T("8 - 3번 벽"));
		m3[1][2] = m3[1][6] = m3[1][10] = 1;
		m3[2][3] = m3[2][15] = 1;
		m3[3][8] = m3[3][12] = 1;
		m3[4][3] = m3[4][5] = m3[4][11] = m3[4][13] = 1;
		m3[5][6] = m3[5][8] = 1;
		m3[6][1] = m3[6][3] = m3[6][13] = 1;
		m3[7][6] = m3[7][10] = m3[7][12] = 1;
		m3[8][5] = m3[8][9] = m3[8][15] = 1;
		m3[9][2] = m3[9][4] = m3[9][12] = 1;
		m3[10][1] = m3[10][7] = m3[10][15] = 1;
		m3[11][2] = m3[11][10] = m3[11][14] = 1;
		m3[12][9] = m3[12][13] = 1;
		m3[13][4] = m3[13][8] = 1;
		m3[14][5] = m3[14][1] = 1;
		m3[15][8] = m3[15][12] = 1;
	}

}


void Cmaze01View::OnTwoPlayerClicked()
{
	page = 4;
	winner = 0;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
}


void Cmaze01View::OnRankingClicked()
{
	page = 5;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
}


void Cmaze01View::OnHowToPlayClicked()
{
	page = 6;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
}


void Cmaze01View::OnEasyClicked()
{
	page = 7;
	p1.x = p1.y = 11;
	p2.x = 1;
	p2.y = 11;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			m1[i][j] = 0;
	for (int i = 0; i < 13; i++) {
		m1[0][i] = 1;
		m1[i][0] = 1;
		m1[i][12] = 1;
		m1[12][i] = 1;
	}
	p1.turn = p2.turn = false;
	p1.turncount = p2.turncount = 0;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
	int i = rand() % 2 + 1;	//선 플레이어 결정 
	int j = rand() % 3 + 1; //맵 종류 결정
	if (i == 1)
	{
		MessageBox(_T("선 플레이어 : 뚱이 "));
		p1.turn = true;
		p2.turn = false;
	}
	else if (i == 2)
	{
		MessageBox(_T("선 플레이어 : 스폰지밥 "));
		p1.turn = false;
		p2.turn = true;
	}
	if (j == 1)			//벽설정
	{
		MessageBox(_T("1번 벽"));
		m1[1][2] = m1[1][6] = m1[1][10] = 1;
		m1[2][5] = 1;
		m1[3][2] = m1[3][8] = 1;
		m1[4][7] = m1[4][11] = 1;
		m1[5][4] = m1[5][6] = m1[5][8] = 1;
		m1[6][3] = m1[6][9] = 1;
		m1[7][4] = 1;
		m1[8][1] = m1[8][7] = m1[8][11] = 1;
		m1[9][4] = m1[9][6] = 1;
		m1[11][6] = m1[11][8] = 1;
	}
	else if (j == 2)	//벽설정
	{
		MessageBox(_T("2번 벽"));
		m1[2][1] = m1[2][5] = m1[2][9] = 1;
		m1[3][11] = 1;
		m1[4][3] = m1[4][7] = 1;
		m1[5][2] = m1[5][6] = m1[5][10] = 1;
		m1[6][1] = m1[6][5] = m1[6][11] = 1;
		m1[7][6] = m1[7][10] = 1;
		m1[8][1] = m1[8][3] = 1;
		m1[9][2] = m1[9][8] = 1;
		m1[10][9] = m1[10][11] = 1;
		m1[11][4] = 1;
	}
	else if (j == 3)	//벽설정
	{
		MessageBox(_T("3번 벽"));
		m1[1][2] = 1;
		m1[2][3] = m1[2][5] = m1[2][9] = 1;
		m1[3][4] = 1;
		m1[4][7] = m1[4][9] = 1;
		m1[5][2] = m1[5][8] = 1;
		m1[6][3] = m1[6][5] = m1[6][11] = 1;
		m1[7][2] = m1[7][10] = 1;
		m1[8][3] = m1[8][7] = m1[8][9] = 1;
		m1[9][4] = 1;
		m1[10][9] = 1;
		m1[11][2] = m1[11][6] = 1;
	}
}


void Cmaze01View::OnNormalClicked()
{
	page = 8;
	p1.x = p1.y = 13;
	p2.x = 1;
	p2.y = 13;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			m2[i][j] = 0;
	for (int i = 0; i < 15; i++) {
		m2[0][i] = 1;
		m2[i][0] = 1;
		m2[i][14] = 1;
		m2[14][i] = 1;
	}
	p1.turn = p2.turn = false;
	p1.turncount = p2.turncount = 0;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
	srand(time(NULL));
	int i = rand() % 2 + 1;	//선 플레이어 결정 
	int j = rand() % 3 + 1; //맵 종류 결정
	if (i == 1)
	{
		MessageBox(_T("선 플레이어 : 뚱이 "));
		p1.turn = true;
		p2.turn = false;
	}
	else if (i == 2)
	{
		MessageBox(_T("선 플레이어 : 스폰지밥 "));
		p1.turn = false;
		p2.turn = true;
	}
	if (j == 1)
	{
		MessageBox(_T("1번 벽"));
		m2[1][2] = m2[1][8] = m2[1][12] = 1;
		m2[2][3] = 1;
		m2[3][2] = m2[3][6] = m2[3][10] = m2[3][12] = 1;
		m2[4][5] = 1;
		m2[5][8] = 1;
		m2[6][1] = m2[6][9] = m2[6][13] = 1;
		m2[7][4] = m2[7][8] = 1;
		m2[8][1] = m2[8][5] = m2[8][7] = m2[8][9] = m2[8][11] = 1;
		m2[9][4] = m2[9][8] = 1;
		m2[10][3] = m2[10][13] = 1;
		m2[11][4] = m2[11][6] = m2[11][8] = m2[11][10] = m2[11][12] = 1;
		m2[12][1] = 1;
		m2[13][6] = m2[13][10] = 1;
	}
	else if (j == 2)
	{
		MessageBox(_T("2번 벽"));
		m2[1][2] = m2[1][6] = 1;
		m2[2][11] = m2[2][13] = 1;
		m2[3][4] = m2[3][6] = m2[3][8] = 1;
		m2[4][1] = m2[4][9] = m2[4][11] = 1;
		m2[5][2] = m2[5][4] = 1;
		m2[6][7] = m2[6][13] = 1;
		m2[7][6] = m2[7][10] = 1;
		m2[8][1] = m2[8][5] = m2[8][9] = m2[8][11] = 1;
		m2[9][2] = m2[9][4] = m2[9][12] = 1;
		m2[10][7] = m2[10][13] = 1;
		m2[11][6] = m2[11][11] = 1;
		m2[12][1] = m2[12][3] = m2[12][11] = 1;
		m2[13][6] = m2[13][8] = 1;
	}
	else if (j == 3)
	{
		MessageBox(_T("3번 벽"));
		m2[1][8] = m2[1][12] = 1;
		m2[2][1] = m2[2][5] = m2[2][11] = 1;
		m2[3][2] = m2[3][6] = m2[3][10] = 1;
		m2[4][3] = m2[4][9] = m2[4][13] = 1;
		m2[5][6] = m2[5][12] = 1;
		m2[6][1] = m2[6][5] = m2[6][11] = m2[6][13] = 1;
		m2[7][4] = m2[7][8] = m2[7][12] = 1;
		m2[8][3] = m2[8][5] = 1;
		m2[10][1] = m2[10][7] = 1;
		m2[11][2] = m2[11][6] = m2[11][10] = 1;
		m2[12][5] = m2[12][9] = m2[12][11] = 1;
		m2[13][6] = m2[13][10] = 1;
	}
}


void Cmaze01View::OnHardClicked()
{
	page = 9;
	p1.x = p1.y = 15;
	p2.x = 1;
	p2.y = 15;
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 17; j++)
			m3[i][j] = 0;
	for (int i = 0; i < 17; i++) {
		m3[0][i] = 1;
		m3[i][0] = 1;
		m3[i][16] = 1;
		m3[16][i] = 1;
	}
	p1.turn = p2.turn = false;
	p1.turncount = p2.turncount = 0;
	for (int i = 101; i <= 112; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	Invalidate();
	int i = rand() % 2 + 1;	//선 플레이어 결정 
	int j = rand() % 3 + 1; //맵 종류 결정
	if (i == 1)
	{
		MessageBox(_T("선 플레이어 : 뚱이 "));
		p1.turn = true;
		p2.turn = false;
	}
	else if (i == 2)
	{
		MessageBox(_T("선 플레이어 : 스폰지밥 "));
		p1.turn = false;
		p2.turn = true;
	}
	if (j == 1)
	{
		MessageBox(_T("8 - 1번 벽"));
		m3[1][2] = m3[1][8] = 1;
		m3[2][3] = m3[2][7] = m3[2][13] = m3[2][15] = 1;
		m3[3][10] = m3[3][14] = 1;
		m3[4][5] = m3[4][7] = 1;
		m3[5][2] = m3[5][6] = m3[5][12] = 1;
		m3[6][1] = m3[6][11] = m3[6][13] = 1;
		m3[7][4] = m3[7][6] = m3[7][12] = 1;
		m3[8][3] = m3[8][7] = m3[8][15] = 1;
		m3[9][2] = m3[9][12] = 1;
		m3[10][5] = m3[10][11] = m3[10][13] = 1;
		m3[11][6] = m3[11][10] = 1;
		m3[12][3] = m3[12][7] = m3[12][15] = 1;
		m3[13][1] = m3[13][8] = m3[13][12] = 1;
		m3[14][3] = m3[14][7] = m3[14][13] = 1;
		m3[15][6] = 1;
	}
	else if (j == 2)
	{
		MessageBox(_T("8 - 2번 벽"));
		m3[1][8] = 1;
		m3[2][5] = m3[2][9] = m3[2][15] = 1;
		m3[3][2] = m3[3][6] = m3[3][12] = 1;
		m3[4][1] = m3[4][9] = m3[4][13] = 1;
		m3[5][2] = m3[5][6] = m3[5][10] = 1;
		m3[6][5] = m3[6][7] = 1;
		m3[7][2] = m3[7][6] = m3[7][14] = 1;
		m3[8][3] = m3[8][9] = m3[8][13] = m3[8][15] = 1;
		m3[9][10] = 1;
		m3[10][1] = m3[10][9] = m3[10][11] = m3[10][15] = 1;
		m3[11][6] = m3[11][10] = m3[11][14] = 1;
		m3[12][1] = m3[12][13] = 1;
		m3[13][4] = m3[13][8] = m3[13][14] = 1;
		m3[14][3] = m3[14][7] = 1;
		m3[15][6] = m3[15][10] = 1;
	}
	else if (j == 3)
	{
		MessageBox(_T("8 - 3번 벽"));
		m3[1][2] = m3[1][6] = m3[1][10] = 1;
		m3[2][3] = m3[2][15] = 1;
		m3[3][8] = m3[3][12] = 1;
		m3[4][3] = m3[4][5] = m3[4][11] = m3[4][13] = 1;
		m3[5][6] = m3[5][8] = 1;
		m3[6][1] = m3[6][3] = m3[6][13] = 1;
		m3[7][6] = m3[7][10] = m3[7][12] = 1;
		m3[8][5] = m3[8][9] = m3[8][15] = 1;
		m3[9][2] = m3[9][4] = m3[9][12] = 1;
		m3[10][1] = m3[10][7] = m3[10][15] = 1;
		m3[11][2] = m3[11][10] = m3[11][14] = 1;
		m3[12][9] = m3[12][13] = 1;
		m3[13][4] = m3[13][8] = 1;
		m3[14][5] = m3[14][1] = 1;
		m3[15][8] = m3[15][12] = 1;
	}
}


void Cmaze01View::OnBackClicked()
{
	if (page == 2) {
		page = 1;
		for (int i = 101; i <= 112; i++)
			(GetDlgItem(i))->ShowWindow(FALSE);
		Invalidate();
	}
	else if (page == 3) {
		page = 2;
		for (int i = 101; i <= 112; i++)
			(GetDlgItem(i))->ShowWindow(FALSE);
		Invalidate();
		KillTimer(0);
		timetext.Format(_T("시간 : 000초"));
		stage = 1;
	}
	else if ((page == 4) || (page == 5) || (page == 6)) {
		page = 2;
		infopage = 1;
		for(int i = 101; i <= 112; i++)
			(GetDlgItem(i))->ShowWindow(FALSE);
		Invalidate();
	}
	else if ((page == 7) || (page == 8) || (page == 9)) {
		page = 4;
		for (int i = 101; i <= 112; i++)
			(GetDlgItem(i))->ShowWindow(FALSE);
		Invalidate();
	}
}


void Cmaze01View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (page == 3) {
		if (stage == 1) {
			inval1 = CRect((p1.x / 2) * 60 + 270, (p1.y / 2) * 60 + 70, ((p1.x / 2) + 1) * 60 + 270, ((p1.y / 2) + 1) * 60 + 70);
			switch (nChar) {
			case VK_LEFT:
				if (m1[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m1[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 1 클리어!"));
					stage = 2;
					p1.x = p1.y = 13;
					Invalidate();
				}
				break;
			case VK_RIGHT:
				if (m1[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m1[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 1 클리어!"));
					stage = 2;
					p1.x = p1.y = 13;
					Invalidate();
				}
				break;
			case VK_UP:
				if (m1[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m1[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 1 클리어!"));
					stage = 2;
					p1.x = p1.y = 13;
					Invalidate();
				}
				break;
			case VK_DOWN:
				if (m1[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m1[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 1 클리어!"));
					stage = 2;
					p1.x = p1.y = 13;
					Invalidate();
				}
				break;
			}
			InvalidateRect(inval1);
			InvalidateRect(CRect((p1.x / 2) * 60 + 270, (p1.y / 2) * 60 + 70, ((p1.x / 2) + 1) * 60 + 270, ((p1.y / 2) + 1) * 60 + 70));
		}
		else if (stage == 2) {
			inval1 = CRect((p1.x / 2) * 60 + 240, (p1.y / 2) * 60 + 40, ((p1.x / 2) + 1) * 60 + 240, ((p1.y / 2) + 1) * 60 + 40);
			switch (nChar) {
			case VK_LEFT:
				if (m2[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m2[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 2 클리어!"));
					stage = 3;
					p1.x = p1.y = 15;
					Invalidate();
				}
				break;
			case VK_RIGHT:
				if (m2[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m2[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 2 클리어!"));
					stage = 3;
					p1.x = p1.y = 15;
					Invalidate();
				}
				break;
			case VK_UP:
				if (m2[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m2[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 2 클리어!"));
					stage = 3;
					p1.x = p1.y = 15;
					Invalidate();
				}
				break;
			case VK_DOWN:
				if (m2[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m2[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					MessageBox(_T("스테이지 2 클리어!"));
					stage = 3;
					p1.x = p1.y = 15;
					Invalidate();
				}
				break;
			}
			InvalidateRect(inval1);
			InvalidateRect(CRect((p1.x / 2) * 60 + 240, (p1.y / 2) * 60 + 40, ((p1.x / 2) + 1) * 60 + 240, ((p1.y / 2) + 1) * 60 + 40));
		}
		else if (stage == 3) {
			inval1 = CRect((p1.x / 2) * 60 + 210, (p1.y / 2) * 60 + 10, ((p1.x / 2) + 1) * 60 + 210, ((p1.y / 2) + 1) * 60 + 10);
			switch (nChar) {
			case VK_LEFT:
				if (m3[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m3[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 10;
					endtime = clock();
					timer = (double)(endtime - starttime) / CLOCKS_PER_SEC;
					CString str;
					str.Format(_T("도착!\n걸린시간 : %.2lf s"), timer);
					MessageBox(str);
					(GetDlgItem(108))->ShowWindow(FALSE);
					newrecord = timer;
					Invalidate();
				}
				break;
			case VK_RIGHT:
				if (m3[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m3[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 10;
					endtime = clock();
					timer = (double)(endtime - starttime) / CLOCKS_PER_SEC;
					CString str;
					str.Format(_T("도착!\n걸린시간 : %.2lf s"), timer);
					MessageBox(str);
					(GetDlgItem(108))->ShowWindow(FALSE);
					newrecord = timer;
					Invalidate();
				}
				break;
			case VK_UP:
				if (m3[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m3[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 10;
					endtime = clock();
					timer = (double)(endtime - starttime) / CLOCKS_PER_SEC;
					CString str;
					str.Format(_T("도착!\n걸린시간 : %.2lf s"), timer);
					MessageBox(str);
					(GetDlgItem(108))->ShowWindow(FALSE);
					newrecord = timer;
					Invalidate();
				}
				break;
			case VK_DOWN:
				if (m3[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m3[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 10;
					endtime = clock();
					timer = (double)(endtime - starttime) / CLOCKS_PER_SEC;
					CString str;
					str.Format(_T("도착!\n걸린시간 : %.2lf s"), timer);
					MessageBox(str);
					(GetDlgItem(108))->ShowWindow(FALSE);
					newrecord = timer;
					Invalidate();
				}
				break;
			}
			InvalidateRect(inval1);
			InvalidateRect(CRect((p1.x / 2) * 60 + 210, (p1.y / 2) * 60 + 10, ((p1.x / 2) + 1) * 60 + 210, ((p1.y / 2) + 1) * 60 + 10));
		}
	}
	else if (page == 7) {
		inval1 = CRect((p1.x / 2) * 60 + 270, (p1.y / 2) * 60 + 70, ((p1.x / 2) + 1) * 60 + 270, ((p1.y / 2) + 1) * 60 + 70);
		inval2 = CRect((p2.x / 2) * 60 + 270, (p2.y / 2) * 60 + 70, ((p2.x / 2) + 1) * 60 + 270, ((p2.y / 2) + 1) * 60 + 70);

		if (p1.turn == TRUE)
		{
			switch (nChar)
			{
			case VK_LEFT:
				if (m1[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m1[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_RIGHT:
				if (m1[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m1[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_UP:
				if (m1[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m1[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_DOWN:
				if (m1[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m1[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			}
		}
		else if (p2.turn == TRUE)
		{
			switch (nChar)
			{
			case 'a':
			case 'A':
				if (m1[p2.y][p2.x - 1] == 0)
					p2.x = p2.x - 2;
				else if (m1[p2.y][p2.x - 1] == 1) {
					p2.x = 1;
					p2.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 11 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 'd':
			case 'D':
				if (m1[p2.y][p2.x + 1] == 0)
					p2.x = p2.x + 2;
				else if (m1[p2.y][p2.x + 1] == 1) {
					p2.x = 1;
					p2.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 11 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 'w':
			case 'W':
				if (m1[p2.y - 1][p2.x] == 0)
					p2.y = p2.y - 2;
				else if (m1[p2.y - 1][p2.x] == 1) {
					p2.x = 1;
					p2.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 11 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 's':
			case 'S':
				if (m1[p2.y + 1][p2.x] == 0)
					p2.y = p2.y + 2;
				else if (m1[p2.y + 1][p2.x] == 1) {
					p2.x = 1;
					p2.y = 11;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 11 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			}
		}
		InvalidateRect(inval1);
		InvalidateRect(inval2);
		InvalidateRect(CRect((p1.x / 2) * 60 + 270, (p1.y / 2) * 60 + 70, ((p1.x / 2) + 1) * 60 + 270, ((p1.y / 2) + 1) * 60 + 70));
		InvalidateRect(CRect((p2.x / 2) * 60 + 270, (p2.y / 2) * 60 + 70, ((p2.x / 2) + 1) * 60 + 270, ((p2.y / 2) + 1) * 60 + 70));
		if (p1.turncount == 3 && winner==0)
		{
			p1.turn = false;
			p1.turncount = 0;
			p2.turn = true;
			MessageBox(_T("스폰지밥의 턴!"));
		}
		if (p2.turncount == 3 && winner==0)
		{
			p2.turn = false;
			p2.turncount = 0;
			p1.turn = true;
			MessageBox(_T("뚱이의 턴!"));
		}
	}
	else if (page == 8) {
		inval1 = CRect((p1.x / 2) * 60 + 240, (p1.y / 2) * 60 + 40, ((p1.x / 2) + 1) * 60 + 240, ((p1.y / 2) + 1) * 60 + 40);
		inval2 = CRect((p2.x / 2) * 60 + 240, (p2.y / 2) * 60 + 40, ((p2.x / 2) + 1) * 60 + 240, ((p2.y / 2) + 1) * 60 + 40);
		
		if (p1.turn == TRUE)
		{
			switch (nChar)
			{
			case VK_LEFT:
				if (m2[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m2[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_RIGHT:
				if (m2[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m2[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_UP:
				if (m2[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m2[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_DOWN:
				if (m2[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m2[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 13;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			}
		}
		else if (p2.turn == TRUE)
		{
		switch(nChar)
		{
			case 'a':
			case 'A':
			if (m2[p2.y][p2.x - 1] == 0)
				p2.x = p2.x - 2;
			else if (m2[p2.y][p2.x - 1] == 1) {
				p2.x = 1;
				p2.y = 13;
				MessageBox(_T("출발지로 돌아갑니다."));
			}
			if (p2.x == 13 && p2.y == 1) {
				page = 11;
				MessageBox(_T("스폰지밥 도착!"));
				winner = 2;
				(GetDlgItem(108))->ShowWindow(FALSE);
				Invalidate();
			}
			p2.turncount++;
			break;
		case 'd':
		case 'D':
			if (m2[p2.y][p2.x + 1] == 0)
				p2.x = p2.x + 2;
			else if (m2[p2.y][p2.x + 1] == 1) {
				p2.x = 1;
				p2.y = 13;
				MessageBox(_T("출발지로 돌아갑니다."));
			}
			if (p2.x == 13 && p2.y == 1) {
				page = 11;
				MessageBox(_T("스폰지밥 도착!"));
				winner = 2;
				(GetDlgItem(108))->ShowWindow(FALSE);
				Invalidate();
			}
			p2.turncount++;
			break;
		case 'w':
		case 'W':
			if (m2[p2.y - 1][p2.x] == 0)
				p2.y = p2.y - 2;
			else if (m2[p2.y - 1][p2.x] == 1) {
				p2.x = 1;
				p2.y = 13;
				MessageBox(_T("출발지로 돌아갑니다."));
			}
			if (p2.x == 13 && p2.y == 1) {
				page = 11;
				MessageBox(_T("스폰지밥 도착!"));
				winner = 2;
				(GetDlgItem(108))->ShowWindow(FALSE);
				Invalidate();
			}
			p2.turncount++;
			break;
		case 's':
		case 'S':
			if (m2[p2.y + 1][p2.x] == 0)
				p2.y = p2.y + 2;
			else if (m2[p2.y + 1][p2.x] == 1) {
				p2.x = 1;
				p2.y = 13;
				MessageBox(_T("출발지로 돌아갑니다."));
			}
			if (p2.x == 13 && p2.y == 1) {
				page = 11;
				MessageBox(_T("스폰지밥 도착!"));
				winner = 2;
				(GetDlgItem(108))->ShowWindow(FALSE);
				Invalidate();
			}
			p2.turncount++;
			break;
			}
		}
		InvalidateRect(inval1);
		InvalidateRect(inval2);
		InvalidateRect(CRect((p1.x / 2) * 60 + 240, (p1.y / 2) * 60 + 40, ((p1.x / 2) + 1) * 60 + 240, ((p1.y / 2) + 1) * 60 + 40));
		InvalidateRect(CRect((p2.x / 2) * 60 + 240, (p2.y / 2) * 60 + 40, ((p2.x / 2) + 1) * 60 + 240, ((p2.y / 2) + 1) * 60 + 40));
		if (p1.turncount == 3&&winner==0)
		{
			p1.turn = false;
			p1.turncount = 0;
			p2.turn = true;
			MessageBox(_T("스폰지밥의 턴!"));
		}
		if (p2.turncount == 3&&winner==0)
		{
			p2.turn = false;
			p2.turncount = 0;
			p1.turn = true;
			MessageBox(_T("뚱이의 턴!"));
		}
	}

	else if (page == 9) {
		inval1 = CRect((p1.x / 2) * 60 + 210, (p1.y / 2) * 60 + 10, ((p1.x / 2) + 1) * 60 + 210, ((p1.y / 2) + 1) * 60 + 10);
		inval2 = CRect((p2.x / 2) * 60 + 210, (p2.y / 2) * 60 + 10, ((p2.x / 2) + 1) * 60 + 210, ((p2.y / 2) + 1) * 60 + 10);

		if (p1.turn == TRUE)
		{
			switch (nChar)
			{
			case VK_LEFT:
				if (m3[p1.y][p1.x - 1] == 0)
					p1.x = p1.x - 2;
				else if (m3[p1.y][p1.x - 1] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_RIGHT:
				if (m3[p1.y][p1.x + 1] == 0)
					p1.x = p1.x + 2;
				else if (m3[p1.y][p1.x + 1] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_UP:
				if (m3[p1.y - 1][p1.x] == 0)
					p1.y = p1.y - 2;
				else if (m3[p1.y - 1][p1.x] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			case VK_DOWN:
				if (m3[p1.y + 1][p1.x] == 0)
					p1.y = p1.y + 2;
				else if (m3[p1.y + 1][p1.x] == 1) {
					p1.x = p1.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p1.x == 1 && p1.y == 1) {
					page = 11;
					MessageBox(_T("뚱이 도착!"));
					winner = 1;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p1.turncount++;
				break;
			}
		}
		else if (p2.turn == TRUE)
		{
			switch (nChar)
			{
			case 'a':
			case 'A':
				if (m3[p2.y][p2.x - 1] == 0)
					p2.x = p2.x - 2;
				else if (m3[p2.y][p2.x - 1] == 1) {
					p2.x = 1;
					p2.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 15 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 'd':
			case 'D':
				if (m3[p2.y][p2.x + 1] == 0)
					p2.x = p2.x + 2;
				else if (m3[p2.y][p2.x + 1] == 1) {
					p2.x = 1;
					p2.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 15 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 'w':
			case 'W':
				if (m3[p2.y - 1][p2.x] == 0)
					p2.y = p2.y - 2;
				else if (m3[p2.y - 1][p2.x] == 1) {
					p2.x = 1;
					p2.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 15 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			case 's':
			case 'S':
				if (m3[p2.y + 1][p2.x] == 0)
					p2.y = p2.y + 2;
				else if (m3[p2.y + 1][p2.x] == 1) {
					p2.x = 1;
					p2.y = 15;
					MessageBox(_T("출발지로 돌아갑니다."));
				}
				if (p2.x == 15 && p2.y == 1) {
					page = 11;
					MessageBox(_T("스폰지밥 도착!"));
					winner = 2;
					(GetDlgItem(108))->ShowWindow(FALSE);
					Invalidate();
				}
				p2.turncount++;
				break;
			}
		}
		InvalidateRect(inval1);
		InvalidateRect(inval2);
		InvalidateRect(CRect((p1.x / 2) * 60 + 210, (p1.y / 2) * 60 + 10, ((p1.x / 2) + 1) * 60 + 210, ((p1.y / 2) + 1) * 60 + 10));
		InvalidateRect(CRect((p2.x / 2) * 60 + 210, (p2.y / 2) * 60 + 10, ((p2.x / 2) + 1) * 60 + 210, ((p2.y / 2) + 1) * 60 + 10));
		if (p1.turncount == 3&&winner==0)
		{
			p1.turn = false;
			p1.turncount = 0;
			p2.turn = true;
			MessageBox(_T("스폰지밥의 턴!"));
		}
		if (p2.turncount == 3&&winner==0)
		{
			p2.turn = false;
			p2.turncount = 0;
			p1.turn = true;
			MessageBox(_T("뚱이의 턴!"));
		}
	}
	else if (page == 10) {
		if (nChar == _T('\b')) {
			if (m_str.GetSize() > 0)
				m_str.RemoveAt(m_str.GetSize() - 1);
		}
		else if(nChar <= _T('Z') && nChar >= _T('A')){
			if (m_str.GetSize() < 3)
				m_str.Add(nChar);
		}
		InvalidateRect(namewrite);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void Cmaze01View::OnReturnPageClicked()
{
	page = 2;
	for (int i = 109; i <= 110; i++)
		(GetDlgItem(i))->ShowWindow(FALSE);
	writerankcheck = 0;
	stage = 1;
	Invalidate();
}


void Cmaze01View::OnWriteRankClicked()
{
	if (m_str.GetSize() == 3) {
		if (writerankcheck == 0) {

			CFile file;
			CFileException e;
			if (!file.Open(_T("record.txt"), CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate, &e)) {
				e.ReportError();
				return;
			}

			for (int i = 0; i < 10; i++) {
				file.Read(&name[i][0], sizeof(name[i][0]));
				file.Read(&name[i][1], sizeof(name[i][1]));
				file.Read(&name[i][2], sizeof(name[i][2]));
				file.Read(&record[i], sizeof(record[i]));
			}

			file.SeekToBegin();

			for (int i = 0; i < 10; i++) {
				if (newrecord <= record[i]) {
					for (int j = 9; j > i; j--) {
						record[j] = record[j - 1];
						name[j][0] = name[j - 1][0];
						name[j][1] = name[j - 1][1];
						name[j][2] = name[j - 1][2];
					}
					name[i][0] = m_str[0];
					name[i][1] = m_str[1];
					name[i][2] = m_str[2];
					record[i] = newrecord;
					i = 10;
				}
			}
			for (int i = 0; i < 10; i++) {
				file.Write(&name[i][0], sizeof(name[i][0]));
				file.Write(&name[i][1], sizeof(name[i][1]));
				file.Write(&name[i][2], sizeof(name[i][2]));
				file.Write(&record[i], sizeof(record[i]));
			}
			file.Close();
		}
		m_str.RemoveAll();
		writerankcheck = 1;
	}
	else if (m_str.GetSize() != 3 && writerankcheck == 0) {
		MessageBox(_T("이름을 모두 입력해주세요!"));
	}
	else if (m_str.GetSize() != 3 && writerankcheck == 1) {
		MessageBox(_T("등록 완료!"));
	}
	InvalidateRect(namewrite);
}

void Cmaze01View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	counttime = clock();
	counttimer = (double)(counttime - starttime) / CLOCKS_PER_SEC;
	timetext.Format(_T("시간 : %03.0lf초"), counttimer);
	InvalidateRect(CRect(10, 10, 130, 40));
	CView::OnTimer(nIDEvent);
}


void Cmaze01View::OnMusicButtonClicked()
{
	if (onoff == 0) {
		(GetDlgItem(111))->ShowWindow(FALSE);
		onoff = 1;
		PlaySound(NULL,AfxGetInstanceHandle(),NULL);
		//InvalidateRect(music);
	}
	
}


void Cmaze01View::OnMusicoffButtonClicked()
{
	if (onoff == 1) {
		(GetDlgItem(112))->ShowWindow(FALSE);
		onoff = 0;
		PlaySound(SoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);
		//InvalidateRect(music);
	}
}
