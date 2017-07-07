/********************************************************
* * Copyright (c) 2012, �������ͨ�Ź����ͨ�豸���޹�˾
* * All rights reserved.
* 
* �ļ����ƣ�ReaderDlg.cpp
* ����������Ӧ�ó���
* 
* ��ǰ�汾��	V1.0
* ��    �ߣ�	�Ż�
* ������ڣ�	2012.03.05
* 
* ���ļ�¼����
*********************************************************/

#include "stdafx.h"
#include "Reader.h"
#include "ReaderDlg.h"
#include "direct.h"
#include <iostream>
#include <fstream>
#include "windows.h"  
#include <stdio.h> 
//#include "mmsys.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


long baudrate[]={300,600,1200,2400,4800,9600,19200,38400,43000,56000,57600,115200};
int databit[]={8,7,6};

/* CRC��λ�ֽ�ֵ��*/ 
const unsigned char auchCRCHi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
} ; 

/* CRC��λ�ֽ�ֵ��*/ 
const unsigned char auchCRCLo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
		0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
		0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
		0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
		0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
		0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
		0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
		0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
		0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
		0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
		0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
		0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
		0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
		0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
		0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
		0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
		0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
		0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
		0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
		0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
		0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
		0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
} ;


UINT ComProce(LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDlg dialog

CReaderDlg::CReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReaderDlg)
	m_SeriouStr = _T("");
	m_BaudStr = _T("");
	m_StopStr = _T("");
	m_savefilename = _T("");
	m_savefilenamecopy=_T("");
	m_strTXData = _T("");
	m_filepath = _T("");
	m_strRXData = _T("");
	m_JiaoyanStr = _T("");
	m_DataStr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_txlen=0;
	m_rxlen=0;
	m_bConnected=1;
	m_bAutoSend=FALSE;
	m_portstatu_but=TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderDlg)
	DDX_Control(pDX, IDC_BUTTON_EMPTYRX, m_emptyrx);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_filename);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_cHexSend);
	DDX_Control(pDX, IDC_BUTTON_EMPTYTEXT, m_emptytx);
	DDX_Control(pDX, IDC_BUTTON_TRANSFILE, m_transfile);
	DDX_Control(pDX, IDC_BUTTEN_MENUALSEND, m_sendbutten);
	DDX_Control(pDX, IDC_EDIT_TXDATA, m_edittxdata);
	DDX_Control(pDX, IDC_EDIT_FRUINFO, m_EditFruinfo);
	DDX_Control(pDX, IDC_EDIT_POWER, m_EditPower);
	DDX_Control(pDX, IDC_STATIC_FILEPAHT, m_sFilePath);
	DDX_Control(pDX, IDC_EDIT_RXDATA, m_EditRXData);
	DDX_Control(pDX, IDC_CHECK_HEXDISPLAY, m_ctrlHexDisplay);
	DDX_Control(pDX, IDC_CHECK_WRITETOFILE, m_judgesend);
	DDX_Control(pDX, IDC_COMBO_STOP, m_ComboStop);
	DDX_Control(pDX, IDC_COMBO_JIAOYAN, m_ComboJiaoyan);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ComboData);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_ComboBaud);
	DDX_Control(pDX, IDC_COMBO_SERIOU, m_ComboSeriou);
	DDX_Control(pDX, IDC_COMBO_WORKSTATUS, m_ComboWorkerstatus);
	DDX_Control(pDX, IDC_COMBO_READDISTANCE, m_ComboReaddistance);
	DDX_Control(pDX, IDC_COMBO_BUZZER, m_ComboBuzzer);
	DDX_CBString(pDX, IDC_COMBO_SERIOU, m_SeriouStr);
	DDX_CBString(pDX, IDC_COMBO_BAUD, m_BaudStr);
	DDX_CBString(pDX, IDC_COMBO_STOP, m_StopStr);
	DDX_CBString(pDX, IDC_COMBO_JIAOYAN, m_JiaoyanStr);
	DDX_CBString(pDX, IDC_COMBO_DATA, m_DataStr);
	DDX_CBString(pDX, IDC_COMBO_WORKSTATUS, m_Workerstatustr);
	DDX_CBString(pDX, IDC_COMBO_READDISTANCE, m_Readdistancestr);
	DDX_CBString(pDX, IDC_COMBO_BUZZER, m_Buzzerstr);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_savefilename);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	DDX_Text(pDX, IDC_STATIC_FILEPAHT, m_filepath);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_Text(pDX, IDC_EDIT_FRUINFO, m_Fruinfostr);
	DDX_Text(pDX, IDC_EDIT_POWER, m_Powerstr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReaderDlg, CDialog)
	//{{AFX_MSG_MAP(CReaderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_SERIOU, OnSelchangeComboSeriou)
	ON_BN_CLICKED(IDC_BUTTEN_MENUALSEND, OnButtenMenualsend)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFILE, OnButtonTransfile)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutosend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EMPTYTEXT, OnButtonEmptytext)
	ON_BN_CLICKED(IDC_CHECK_WRITETOFILE, OnCheckWritetofile)
	ON_BN_CLICKED(IDC_BUTTON_FILENAME, OnButtonFilename)
	ON_BN_CLICKED(IDC_BUTTON_SAVEEDIT, OnButtonSaveedit)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYRX, OnButtonEmptyrx)
	ON_BN_CLICKED(IDC_BUTTON_PORTSTATU, OnButtonPortstatu)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, OnSelchangeComboBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_JIAOYAN, OnSelchangeComboJiaoyan)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_CBN_SELCHANGE(IDC_COMBO_WORKSTATUS, OnSelchangeComboWorkstatus)
	ON_CBN_SELCHANGE(IDC_COMBO_READDISTANCE, OnSelchangeComboReaddistance)
	ON_CBN_SELCHANGE(IDC_COMBO_BUZZER, OnSelchangeComboBuzzer)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	//}}AFX_MSG_MAP
//	ON_MESSAGE(WM_COMMNOTIFY,ProcessCOMMNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDlg message handlers

BOOL CReaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	addall();
//	OnSelchangeComboSeriou();
	m_dwordtimecha=0;
	LastDateTime=new   SYSTEMTIME;
	m_curtime=0;
	m_lasttime=0;
	m_timech=0;

	OpenComm(1);
	//��ʼ���ص����¼����ص�д�¼�

	memset(&m_osRead,0,sizeof(OVERLAPPED));
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osRead.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_osRead.hEvent==NULL)
	{
		AfxMessageBox("wrong2");
		return FALSE;
	}
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_osWrite.hEvent==NULL)
	{
		AfxMessageBox("wrong3");
		return FALSE;
	}

	//�ؼ�Ĭ��״̬�ͱ�����ʼ��
	m_ctrlHexDisplay.SetCheck(1);
	m_judgesend.SetCheck(1);
	m_judgesend.SetState(FALSE);
	m_cHexSend.SetCheck(1);
	mkdir("d:\\readertest");
	m_savefilename="d:\\readertest\\reader.txt";
	m_savefilenamecopy=m_savefilename;
	m_NULL=" ";
	m_crclen=0;
	m_counter=0;
	m_lostframe=0;
	b_fileopen=FALSE;
	m_sendworks=0x80;
	m_sendreadd=0x30;
	m_sendbuzz=0x00;
	m_framehead="fc0c0411";  //�̶�ͷ��ֵ
	m_counters=0;
	m_framesequence="11";    //Ĭ��֡Ƶ��
	m_framenull="0102030405060708090a0b";  //�м�հײ�ֵ
	m_maohao=":";
	m_intfilenamecounter=0;
	m_intrxcounter=0;

	DispStatus();
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReaderDlg::addall()
{
	//�貨��������б��
	TCHAR baudbuffer[][7]={"300","600","1200","2400","4800","9600","19200","38400","43000","56000","57600","115200"};

    for(int i=0;i<12;i++)
	{
		int judge_tf=m_ComboBaud.AddString(baudbuffer[i]);

		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))

           MessageBox("build baud error!");
	}

	m_ComboBaud.SetCurSel(11);

    //�贮������б��
	TCHAR seriou[][5]={"COM1","COM2","COM3","COM4"};

	for(i=0;i<4;i++)
	{
		m_ComboSeriou.AddString(seriou[i]);
	}

	m_ComboSeriou.SetCurSel(1);

	//��У��λ����б��
	TCHAR jiaoyan[][7]={"N","O","E"};

	for(i=0;i<3;i++)
	{
		m_ComboJiaoyan.AddString(jiaoyan[i]);
	}

	m_ComboJiaoyan.SetCurSel(0);

	//������λ����б��
	TCHAR data[][2]={"8","7","6"};

	for(i=0;i<3;i++)
	{
		m_ComboData.AddString(data[i]);
	}

	m_ComboData.SetCurSel(0);

	//��ֹͣλ����б��
	TCHAR stop[][2]={"1","2"};

	for(i=0;i<2;i++)
	{
		m_ComboStop.AddString(stop[i]);
	}

	m_ComboStop.SetCurSel(0);

	//�蹤��״̬�б��
	TCHAR workstatus[][9]={"��������","����״̬","����֡"};

	for(i=0;i<3;i++)
	{
		m_ComboWorkerstatus.AddString(workstatus[i]);
	}

	m_ComboWorkerstatus.SetCurSel(0);

	//���Ķ������б��
	TCHAR readdistance[][5]={"���","��","С","��С"};

	for(i=0;i<4;i++)
	{
		m_ComboReaddistance.AddString(readdistance[i]);
	}

	m_ComboReaddistance.SetCurSel(0);

	//��������б��
	TCHAR buzzer[][9]={"��������","������"};

	for(i=0;i<2;i++)
	{
		m_ComboBuzzer.AddString(buzzer[i]);
	}

	m_ComboBuzzer.SetCurSel(0);

}

void CReaderDlg::OnSelchangeComboSeriou() 
{
	// TODO: Add your control notification handler code here
	if (m_bConnected)
	{
		CloseConnection();
	}

	if(m_portstatu_but)
	{
		int i=m_ComboSeriou.GetCurSel();

		OpenComm(i);
	}

	DispStatus();

}

BOOL CReaderDlg::SetCommParameter()
{
	DCB dcb;

	if(!GetCommState(m_hCom,&dcb))
	{
		return FALSE;
	}

	//���û�������
	int baudindex=m_ComboBaud.GetCurSel();

	m_ComboBaud.GetLBText(baudindex,m_BaudStr);

	dcb.BaudRate=baudrate[baudindex];

	int dataindex=m_ComboData.GetCurSel();

	m_ComboData.GetLBText(dataindex,m_DataStr);

	dcb.ByteSize=databit[dataindex];

	int jiaoyanindex=m_ComboJiaoyan.GetCurSel();

	m_ComboJiaoyan.GetLBText(jiaoyanindex,m_JiaoyanStr);

	switch(jiaoyanindex)
	{
		case 0:
			dcb.Parity=NOPARITY;
			break;
		case 1:
			dcb.Parity=ODDPARITY;
			break;
		case 2:
			dcb.Parity=EVENPARITY;
			break;
		default:;
	}

	int stopindex=m_ComboStop.GetCurSel();

	m_ComboStop.GetLBText(stopindex,m_StopStr);

	switch(stopindex)
	{
		case 0:
			dcb.StopBits=ONESTOPBIT;
			break;
		case 1:
			dcb.StopBits=TWOSTOPBITS;
			break;
		default:;
	}

	//������
	dcb.fInX=FALSE;
	dcb.fOutX=FALSE;
	dcb.XonChar=XON;
	dcb.XoffChar=XOFF;
	dcb.XonLim=50;
	dcb.XoffLim=50;
	
	dcb.fNull=FALSE;
	
	return(SetCommState(m_hCom,&dcb));
}

BOOL CReaderDlg::OpenComm(int Num)
{
	COMMTIMEOUTS TimeOuts;

	m_ComboSeriou.GetLBText(Num,m_SeriouStr);

	m_hCom=CreateFile(m_SeriouStr,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);

	if(m_hCom==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("�򿪴���ʧ��!");

		m_bConnected=0;

		return FALSE;
	}

	//���ù������߳���Ӧ���¼�
	SetCommMask(m_hCom,EV_RXCHAR);

	//���ö�д������
	SetupComm(m_hCom,MAXBLOCK,MAXBLOCK);

	//���ó�ʱ
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	TimeOuts.WriteTotalTimeoutMultiplier=0;
	SetCommTimeouts(m_hCom,&TimeOuts);

	//�����������߳�
	if(SetCommParameter())
	{
		m_pThread=AfxBeginThread(ComProce,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);

		if(m_pThread==NULL)
		{
			CloseHandle(m_hCom);

			AfxMessageBox("�̴߳���ʧ��!");

			m_bConnected=0;

			return FALSE;
		}
		else
		{
			m_pThread->ResumeThread();
		}
	}
	else
	{
		CloseHandle(m_hCom);

		AfxMessageBox("��������ʧ��!");

		m_bConnected=0;

		return FALSE;
	}

	m_bConnected=1;

	return TRUE;
}
UINT ComProce(LPVOID pParam)
{

	OVERLAPPED os;
	DWORD dwMask,dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	
	CReaderDlg *pDlg=(CReaderDlg *)pParam;

	memset(&os,0,sizeof(OVERLAPPED));

	os.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	if(os.hEvent==NULL)
	{
		AfxMessageBox("���ܽ����¼�����!");

		return (UINT)-1;
	}

	while(pDlg->m_bConnected)
	{
		ClearCommError(pDlg->m_hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			pDlg->ProcessCOMMNotification(EV_RXCHAR,0);
		}

		dwMask=0;

		if(!WaitCommEvent(pDlg->m_hCom,&dwMask,&os))
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{
				GetOverlappedResult(pDlg->m_hCom,&os,&dwTrans,TRUE);
			}
			else
			{
				CloseHandle(os.hEvent);

				return(UINT)-1;
			}
		}
	}
	CloseHandle(os.hEvent);
	return 0;
}
BOOL CReaderDlg::ProcessCOMMNotification (UINT wParam,long lParam)
{
	CFileException e;

	m_strcrcData="";
	//�õ�ϵͳʱ�䣬�����浽�ı��ļ���
	m_time.Empty();

	SYSTEMTIME   *curDateTime=new   SYSTEMTIME; 
    //::GetSystemTime(); 
    ::GetLocalTime(curDateTime); 
//    DWORD   year=curDateTime-> wYear; 
//	DWORD   month=curDateTime-> wMonth; 
//	DWORD   day=curDateTime-> wDay; 
    DWORD   hour=curDateTime-> wHour; 
    DWORD   minute=curDateTime-> wMinute; 
    DWORD   second=curDateTime-> wSecond; 
    DWORD   millisecond=curDateTime-> wMilliseconds;   //���� 

//	m_curtime=timeGetTime();
	QueryPerformanceFrequency(&tc); 
	//	,m_lasttime,m_timech;
	int m_int;
	m_int=tc.QuadPart;

    delete   curDateTime; 
	CString m_timetemp="";
	CString m_timefilename="";
	m_timetemp.Format("%d",hour);
	m_time+=m_timetemp;
	m_timefilename+=m_timetemp;
	m_time+=":";

	m_timetemp.Format("%d",minute);
	m_time+=m_timetemp;
	m_timefilename+=m_timetemp;
	m_time+=":";

	m_timetemp.Format("%d",second);
	m_time+=m_timetemp;
	m_timefilename+=m_timetemp;
	m_time+=":";

	m_timetemp.Format("%d",millisecond);
	m_time+=m_timetemp;
	m_timefilename+=m_timetemp;

	BOOL judgefile=m_judgesend.GetCheck();

	//�жϴ����Ƿ��ѹر�
	if(!m_bConnected)
	{
		return FALSE;
	}

	//�ж��յ����Ƿ��������Ϣ
	if((EV_RXCHAR&wParam)!=EV_RXCHAR)
	{
		return FALSE;
	}

	//�����ݶ���CString������
	CString StrTemp;

	BYTE abIn[MAXBLOCK];

	int len=0;

//	AcceptRead.Empty();//���CString����,�����¶�����ַ�
	len=ReadBlock(abIn,MAXBLOCK);

	if(!len)
	{
		AfxMessageBox("���ַ��������顣");

		return FALSE;
	}

	for(int i=0;i<len;i++)
	{
		BYTE bt=abIn[i];

		if(m_ctrlHexDisplay.GetCheck())
		{
			StrTemp.Format("%02X",bt);
		}
		else
		{
		    StrTemp.Format("%c",bt);
		}
		m_strRXData+=StrTemp+m_NULL;
		m_strcrcData+=StrTemp;

	}
	m_rxlen+=len;   //������ʾ�������ݳ���
	m_intrxcounter+=len;
	//���ַ���ʾ��ָ��λ��
	m_EditRXData.SetWindowText(m_strRXData);

	int   nLen   =   m_EditRXData.SendMessage(WM_GETTEXTLENGTH);

	m_EditRXData.SetSel(nLen,   nLen,   FALSE); 

	if (nLen>2400)
	{
		m_strRXData.Empty();
	}
	//����CRC16
	char strtochar[44]; 
	CString   m_crctoeq;
	CString	  m_crcrx;
	//ȡ����5���ֽڣ�����֡������
	CString	  m_strcounter,m_strcounter1,m_strcounter2;
	int Cframecounter;
	char strtocounter[2];
	char * str;

	m_strcounter1=m_strcrcData.GetAt(8);

	m_strcounter2=m_strcrcData.GetAt(9);

	m_strcounter=m_strcounter1+m_strcounter2;

	::strcpy(strtocounter,m_strcounter);

	Cframecounter=(int)strtol(strtocounter,&str,16);

	m_counter=Cframecounter;

	unsigned char * strchar;  //����ת��ΪCRC16�����ɵ��õ�����
	unsigned short int  m_crc16;      //CRC16 ���㷵�ؽ��
	int m_crcresultlenth=0;			//CRC16������λ��
	CString m_crcresultzero="0";

	::strcpy(strtochar,m_strcrcData);

	strchar=(unsigned char *)strtochar;

	m_crc16=Get_CRC16_Code(strchar, 22);

	m_crctoeq.Format("%02X",m_crc16);  //������������ΪCSting���ͣ����ڱȶ�

	m_crcrx=m_strcrcData.Right(4);

	m_crcresultlenth=m_crctoeq.GetLength();

	if(m_crcresultlenth!=4)
	{
		switch(m_crcresultlenth)
		{
			case 3:
			{
				m_crcresultzero+=m_crctoeq;
				m_crctoeq=m_crcresultzero;
				break;
			}
			case 2:
			{
				m_crcresultzero+=m_crctoeq;
				m_crcresultzero+=m_crctoeq;
				m_crctoeq=m_crcresultzero;
				break;
			}
			case 1:
			{
				m_crcresultzero+=m_crctoeq;
				m_crcresultzero+=m_crctoeq;
				m_crcresultzero+=m_crctoeq;
				m_crctoeq=m_crcresultzero;
				break;
			}

			default:
			{
				AfxMessageBox("CRC16�������");
			}
		}
	}

	/*
	**��������λ��ǰ����λ�ں�
	*/
	CString m_crcleft2="";
	CString m_crcright2="";
	m_crcleft2=m_crctoeq.Left(2);
	m_crcright2=m_crctoeq.Right(2);

	m_crcright2+=m_crcleft2;

	m_crctoeq=m_crcright2;
	


	if (m_crctoeq!=m_crcrx)
	{
		m_crclen++;
	}

	m_strcrcData+=m_time;

	DispStatus();

	//������д�뵽�ı��ļ�
	if(judgefile)
	{		
		//�ļ�д���ֽڴ�С������ֵ�����������ļ���д��
		if (m_intrxcounter>240000)
		{
			getdatafile.Close();

			m_savefilename=m_savefilenamecopy;

			m_savefilename.Insert(20,m_timefilename);

			b_fileopen=false;

			m_intrxcounter=0;
		}
		//�ж��Ƿ�д���ļ�,�����ļ�,��ָ�붨���ļ�ĩβ

		if (b_fileopen==FALSE)
		{
			m_countertodispatch=Cframecounter;

			getdatafile.Open(m_savefilename,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

			b_fileopen=TRUE;
		}

 		CString enter="\r\n";
		CString testall;
		CString m_nullspace=" ";

		int charlength;

 		getdatafile.SeekToEnd();   //��д��λ�ö�λ���ı�ĩβ

		/*
		**Ϊ���ڹۿ�������ͷ������֮�����ո�У����֮�����ո�
		*/

		m_strcrcData.Insert(12,m_nullspace);
		m_strcrcData.Insert(45,m_nullspace);
		m_strcrcData.Insert(50,m_nullspace);

		testall=m_strcrcData+enter;

		charlength=testall.GetLength();

		getdatafile.Write(m_strcrcData+enter,charlength);
		
	}

	int lostframecounter;

	Cframecounter++;

	lostframecounter=Cframecounter-m_countertodispatch;

	if (1!=lostframecounter)
	{
		int m_resault; //ģ�����

		if (0==lostframecounter)
		{
			m_resault=256;
		}
		else
		{
			m_resault=lostframecounter % 255;
		}
		
		m_lostframe+=m_resault;
	}

	m_countertodispatch=Cframecounter;

//	SetEvent(hPostToWnd);//�����ٴη����¼�
	return TRUE;
}

int CReaderDlg::ReadBlock(BYTE *abIn, int MaxLength)
{
	BOOL JudgeRead;
	COMSTAT ComStat;
	DWORD dwErrorFlags,dwLength;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);

	if(dwErrorFlags>0)
	{
		AfxMessageBox("�����ڴ�����������á�");

		PurgeComm(m_hCom,PURGE_RXABORT|PURGE_RXCLEAR);

		return 0;
	}

	dwLength=((DWORD)MaxLength<ComStat.cbInQue?MaxLength:ComStat.cbInQue);

	memset(abIn,0,MaxLength);

	//������ַ�������
	if(dwLength)
	{
		JudgeRead=ReadFile(m_hCom,abIn,dwLength,&dwLength,&m_osRead);//�����ַ���abIn��

		if(!JudgeRead)
		{
			//����ص�����δ���,�ȴ�ֱ���������
			if(GetLastError()==ERROR_IO_PENDING)
			{
				GetOverlappedResult(m_hCom,&m_osRead,&dwLength,TRUE);

				m_osRead.Offset=0;
			}
			else
			{
				dwLength=0;
			}
		}
	}

	return dwLength;
}

int CReaderDlg::WriteBlock(char *abOut, int MaxLength)
{
	BOOL JudgeWrite;
	COMSTAT ComStat;
	DWORD dwErrorFlags,dwLength,lentest;
	m_osWrite.Offset=0;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);

	if(dwErrorFlags>0)
	{
		AfxMessageBox("д���ڴ�����������á�");

		PurgeComm(m_hCom,PURGE_TXABORT|PURGE_TXCLEAR);

		return 0;
	}

	dwLength=MaxLength;
	lentest=0;

	JudgeWrite=WriteFile(m_hCom,abOut,dwLength,&lentest,&m_osWrite);

	if(!JudgeWrite)
	{

		if(GetLastError()==ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hCom,&m_osWrite,&lentest,TRUE);
		}
		else
		{
			lentest=0;
		}
	}

	return lentest;
}

void CReaderDlg::OnButtenMenualsend() 
{

	CString m_enter="\r\n";
//	m_strTXData+=m_senddateall;

	m_senddateall="";// ����ϴη�������

	//�õ������������
	//�õ��ı�������Ƶ����Ϣ�����޵�ѹ
	CString m_strfru="";
	CString m_strpower="";

	GetDlgItem(IDC_EDIT_FRUINFO)->GetWindowText(m_strfru);

	GetDlgItem(IDC_EDIT_POWER)->GetWindowText(m_strpower);

	if (m_strpower=="")
	{
		m_strpower="ffff";	//�����õ����޵�ƽΪ��14��15���ֽ�
	}

	if (m_strpower.GetLength()!=4)
	{
		AfxMessageBox("��������ȷ�����޵�ѹ!");
		return;
	}
	if (m_strfru=="")
	{
		m_strfru="05"; //�ڶ����ֽ�����
	}
	if (m_strfru.GetLength()!=2)
	{
		AfxMessageBox("��������ȷ��Ƶ���ŵ�!");
		return;
	}
	//�õ�ѡ����Ϣ
	CString m_strcounter;
	char	m_charcounter;
	CString m_zero="0";

	m_strcounter=itoa(Counters(),&m_charcounter,16);

	if (m_counters<=15)
	{
		m_strcounter=m_zero+m_strcounter;
	}

	//��ʼ���������ֽ�
	CString	m_strbyte1;
	CString m_strbyte;
	int m_byte1=0x00;
	m_byte1=m_sendworks+m_sendreadd;	//��һ���Լ����ݺϳ�
	m_strbyte1=itoa(m_byte1,&m_charcounter,16);
	if (m_strbyte1.GetLength()!=2)
	{
		AfxMessageBox("���ֽڳ��ȴ���!");
		return;
	}


//	m_strbyte+=m_strfru;
	//������
	CString m_strsendbuzz;
	m_strsendbuzz=itoa(m_sendbuzz,&m_charcounter,16);
	m_strsendbuzz=m_zero+m_strsendbuzz;
 
	m_senddateall+=m_framehead;     //�̶�ͷ 
	m_senddateall+=m_strcounter;	// ���� 
	m_senddateall+=m_framesequence;	//֡����
	m_senddateall+=m_strbyte1;		//�ֽ�1�趨ֵ
	m_senddateall+=m_strfru;		//�ֽ�2
	m_senddateall+=m_framenull;		//�ֽ�3-13 
	m_senddateall+=m_strpower;		//���޵�ѹ �ֽ�14��15 
	m_senddateall+=m_strsendbuzz;	//�ֽ�16

	//��ʼCRC����
	CString m_crcresult="";
	char m_sendstrtochar[48];
	unsigned char * m_sendstrchar;  //����ת��ΪCRC16�����ɵ��õ�����
	unsigned short int  m_sendcrc16;      //CRC16 ���㷵�ؽ��

	::strcpy(m_sendstrtochar,m_senddateall);

	m_sendstrchar=(unsigned char *)m_sendstrtochar;

	m_sendcrc16=Get_CRC16_Code(m_sendstrchar, 22);

	m_crcresult.Format("%02x",m_sendcrc16);  //������������ΪCSting���ͣ����ڱȶ�
	
	//CRC16�������п�����3λ�������λΪ0������������ʾ
	int m_crcresultclenth=4;
	int m_crcresultdlenth=m_crcresult.GetLength();

	if (m_crcresultclenth!=m_crcresultdlenth)
	{
		if (3==m_crcresultdlenth)
		{
			m_crcresult=m_zero+m_crcresult;
		}
		else if (2==m_crcresultdlenth)
		{
			m_crcresult=m_zero+m_zero+m_crcresult;
		}
		else if (1==m_crcresultdlenth)
		{
			m_crcresult=m_zero+m_zero+m_zero+m_crcresult;
		}
		else if (0==m_crcresultdlenth)
		{
			m_crcresult=m_zero+m_zero+m_zero+m_zero+m_zero;
		}
		else if (m_crcresultdlenth>4)
		{
			AfxMessageBox("CRC У�����!");
		}
	
	}

	m_senddateall+=m_crcresult;

	m_strTXData+=m_senddateall;

	m_strTXData+=m_enter;
	//���ݴ�����ϣ�����
	m_edittxdata.SetWindowText(m_strTXData);
	//ʹ�ؼ�ʼ����ʾ���һ����Ϣ
	int   nLen   =   m_edittxdata.SendMessage(WM_GETTEXTLENGTH);

	m_edittxdata.SetSel(nLen,   nLen,   FALSE); 

	m_txlen+=m_senddateall.GetLength();

	if(!m_bConnected)
	{
		AfxMessageBox("����δ�򿪣�");

		return;
	}

	int m_sendlenth;
	char SendOut[MAXBLOCK];
	int len;
	//���ѡ����ʮ�����Ʒ��ͣ���ת��Ϊ�ַ���ʽ���ͳ�ȥ,����ֱ�ӷ����ַ�����
	if(m_cHexSend.GetCheck())
	{
		//��CStringת��Ϊʮ�������ַ���
		m_sendlenth=m_senddateall.GetLength();

		len=String2Hex(m_senddateall,SendOut);

		m_sendlenth=WriteBlock(SendOut,len);
	}

	else
	{
		//�ַ�����ʽ����
		len=m_senddateall.GetLength();

		char * m_senddatastrtochar;  //����ת��   

		char m_charsend[48];

		::strcpy(m_charsend,m_senddateall);

		m_senddatastrtochar=(char *)m_charsend;

		m_sendlenth=WriteBlock(m_senddatastrtochar,len);

	}

	DispStatus();  //���¼�������ʾ

	return;

}

//�ַ�ת��Ϊ16������ʾ��ʽ
int CReaderDlg::String2Hex(CString str, char *SendOut)
{
	int hexdata,lowhexdata; 
	int hexdatalen=0;
	int len=str.GetLength();
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' '||hstr=='\r'||hstr=='\n')
		{
			i++;

			continue;
		}
		i++;
		if (i>=len)
		{
			break;
		}
		lstr=str[i];
		hexdata=ConvertHexData(hstr);

		lowhexdata=ConvertHexData(lstr);

		if((hexdata==16)||(lowhexdata==16))
		{
			break;
		}
		else
		{
			hexdata=hexdata*16+lowhexdata;
		}

		i++;

		SendOut[hexdatalen]=(char)hexdata;

		hexdatalen++;
	}

	return hexdatalen;
}

char CReaderDlg::ConvertHexData(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30; //1��ASCIIΪ0x31
	if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
    else return(-1);
}

void CReaderDlg::OnButtonTransfile() //ѡ���ļ���ť�¼�����
{

	CFile transfile;

	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "�ı��ļ�(*.txt)|*.txt|All Files (*.*)|*.*| |", AfxGetMainWnd());

    if(mFileDlg.DoModal()==IDOK)
	{
        char outputbuffer[512];

		CFileException e;

		BOOL file;

		int outnum;

        m_strTXData.Empty();//��ʼ����ʾ�ļ�����

        m_edittxdata.SetWindowText(m_strTXData);

	    m_filepath=mFileDlg.GetPathName();//������ʾ·������

		m_sFilePath.SetWindowText(m_filepath);

		file=transfile.Open(m_filepath,CFile::modeRead,&e);

		outnum=transfile.Read(outputbuffer,sizeof(outputbuffer)-1);

		while(outnum)
		{
			outputbuffer[outnum]=NULL;

			m_strTXData+=CString(outputbuffer);

			outnum=transfile.Read(outputbuffer,sizeof(outputbuffer)-1);
        }
        
		transfile.Close();

        m_edittxdata.SetWindowText(m_strTXData);

		m_strTXData.Empty();
			        
	}
}

void CReaderDlg::OnCheckAutosend() 
{
	m_bAutoSend=!m_bAutoSend;

	if(m_bAutoSend)
	{
		SetTimer(1,1000,NULL);
	}
	else
	{
		KillTimer(1);
	}
}

void CReaderDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnButtenMenualsend();

	CDialog::OnTimer(nIDEvent);
}

void CReaderDlg::OnButtonEmptytext() 
{
	// TODO: Add your control notification handler code here
	m_strTXData.Empty();

    m_filepath.Empty();

	GetDlgItem(IDC_STATIC_FILEPAHT)->SetWindowText(m_filepath);

	m_edittxdata.SetWindowText(m_strTXData);	
}

void CReaderDlg::OnCheckWritetofile() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("�˹����ѽ���!");
// 	if(m_judgesend.GetCheck())
// 	{
//         mkdir("d:\\readertest");
// 	   	m_savefilename="d:\\readertest\\reader.txt";
// 	}
// 	else
// 	{
// 		m_savefilename.Empty();
// 	}

//	GetDlgItem(IDC_STATIC_FILENAME)->SetWindowText(m_savefilename);
}

void CReaderDlg::OnButtonFilename() 
{
	// TODO: Add your control notification handler code here
	if(!m_judgesend.GetCheck())
	{
	   AfxMessageBox("��δָ��д�뵽�ļ��");
	}
	else
	{
       CFileDialog savefiledlg(FALSE,"txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "�ı��ļ�(*.txt)|*.txt| |", AfxGetMainWnd());

       if(savefiledlg.DoModal()==IDOK)
	   {
		   m_savefilename=savefiledlg.GetPathName();

		   GetDlgItem(IDC_STATIC_FILENAME)->SetWindowText(m_savefilename);
	   }
	}	
}

void CReaderDlg::OnButtonSaveedit() 
{
	// TODO: Add your control notification handler code here
    CFile getdatafile;
    CFileException e;

	m_EditRXData.GetWindowText(m_strRXData);

	if(m_savefilename.IsEmpty())
	{
		AfxMessageBox("��ѡ�����ļ�����");
	}
	else
	{
		getdatafile.Open(m_savefilename,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

		getdatafile.Write(m_strRXData,m_strRXData.GetLength());

		getdatafile.Close();
	}	
}

void CReaderDlg::OnButtonEmptyrx() 
{
	// TODO: Add your control notification handler code here
	m_strRXData.Empty();

    m_EditRXData.SetWindowText(m_strRXData);
}

void CReaderDlg::OnButtonPortstatu() 
{
	// TODO: Add your control notification handler code here

		m_portstatu_but=!m_portstatu_but;

	if(!m_portstatu_but)
	{
		GetDlgItem(IDC_BUTTON_PORTSTATU)->SetWindowText("���ڴ�");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PORTSTATU)->SetWindowText("���ڹر�");
	}

    OnSelchangeComboSeriou();

	return;
}

void CReaderDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CloseConnection();

	CDialog::OnOK();	
}

void CReaderDlg::CloseConnection()
{
	if(!m_bConnected)
		return;
	m_bConnected=FALSE;
//	SetEvent(m_hPostMsgEvent);
//	SetEvent(m_osRead.hEvent);
	SetCommMask(m_hCom,0);
//	SetEvent(m_osRead.hEvent);
//	AfxMessageBox("out");
	WaitForSingleObject(m_pThread->m_hThread,INFINITE);
//	AfxMessageBox("yes");
	m_pThread=NULL;
	CloseHandle(m_hCom);
}

void CReaderDlg::DispStatus()
{
	CWnd *static_status=GetDlgItem(IDC_STATIC_PORTSTATU);
	CWnd *static_txlen=GetDlgItem(IDC_STATIC_TXLEN);
	CWnd *static_rxlen=GetDlgItem(IDC_STATIC_RXLEN);
	CWnd *static_crclen=GetDlgItem(IDC_STATIC_CRCFAILD);
	CWnd *static_counterlen=GetDlgItem(IDC_STATIC_COUNTER);
	CWnd *static_lostframelen=GetDlgItem(IDC_STATIC_LOSTFRAME);
    CString status_str,txlen_str,rxlen_str,crclen_str,counter_str,lostframe_str;
	if(m_bConnected)
	{
	    status_str="STATUS:"+m_SeriouStr+" OPENED,"+m_BaudStr+','+m_JiaoyanStr+','+m_DataStr+','+m_StopStr;
	}
    else
	{
        status_str="STATUS:"+m_SeriouStr+" CLOSED,"+m_BaudStr+','+m_JiaoyanStr+','+m_DataStr+','+m_StopStr;
	}
    static_status->SetWindowText(status_str);

	txlen_str.Format("TX:%ld",m_txlen);

	static_txlen->SetWindowText(txlen_str);

	rxlen_str.Format("RX:%ld",m_rxlen);

	static_rxlen->SetWindowText(rxlen_str);

	crclen_str.Format("У��ʧ��:%ld",m_crclen);

	static_crclen->SetWindowText(crclen_str);

	counter_str.Format("������:%ld",m_counter);

	static_counterlen->SetWindowText(counter_str);

	lostframe_str.Format("��֡��:%ld",m_lostframe);

	static_lostframelen->SetWindowText(lostframe_str);

}

void CReaderDlg::OnSelchangeComboBaud() 
{
	// TODO: Add your control notification handler code here
	int baudindex;
	baudindex=m_ComboBaud.GetCurSel();

	if(baudindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboBaud.GetLBText(baudindex,m_BaudStr);

		DispStatus();
	}
}

void CReaderDlg::OnSelchangeComboData() 
{
	// TODO: Add your control notification handler code here
	int dataindex;
	dataindex=m_ComboData.GetCurSel();

	if(dataindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboData.GetLBText(dataindex,m_DataStr);

		DispStatus();
	}
}

void CReaderDlg::OnSelchangeComboJiaoyan() 
{
	// TODO: Add your control notification handler code here
	int jiaoyanindex;
	jiaoyanindex=m_ComboJiaoyan.GetCurSel();

	if(jiaoyanindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboJiaoyan.GetLBText(jiaoyanindex,m_JiaoyanStr);

		DispStatus();
	}
}

void CReaderDlg::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
	int stopindex;
	stopindex=m_ComboStop.GetCurSel();

	if(stopindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboStop.GetLBText(stopindex,m_StopStr);

		DispStatus();
	}
}

void CReaderDlg::OnSelchangeComboWorkstatus() 
{
	// TODO: Add your control notification handler code here
	int workstatusindex=0;
	workstatusindex=m_ComboWorkerstatus.GetCurSel();

	if(workstatusindex!=CB_ERR)
	{
		m_ComboWorkerstatus.GetLBText(workstatusindex,m_Workerstatustr);

		if (workstatusindex==0&&m_Workerstatustr=="��������")
		{
			m_sendworks=0x80;
		}
		else if (workstatusindex==1&&m_Workerstatustr=="����״̬")
		{
			m_sendworks=0x40;
		}
		else if (workstatusindex==2&&m_Workerstatustr=="����֡")
		{
			m_sendworks=0xc0;
		}
		
	}
}

void CReaderDlg::OnSelchangeComboReaddistance() 
{
	// TODO: Add your control notification handler code here
	int readdistanceindex;
	readdistanceindex=m_ComboReaddistance.GetCurSel();

	if(readdistanceindex!=CB_ERR)
	{
		m_ComboReaddistance.GetLBText(readdistanceindex,m_Readdistancestr);

		if ((readdistanceindex==0)&&(m_Readdistancestr=="���"))
		{
			m_sendreadd=0x30;
		}
		else if (readdistanceindex==1&&m_Readdistancestr=="��")
		{
			m_sendreadd=0x20;
		}
		else if (readdistanceindex==2&&m_Readdistancestr=="С")
		{
			m_sendreadd=0x10;
		}
		else if (readdistanceindex==3&&m_Readdistancestr=="��С")
		{
			m_sendreadd=0x00;
		}
	}

	
}

void CReaderDlg::OnSelchangeComboBuzzer() 
{
	// TODO: Add your control notification handler code here
	int buzzerindex;
	buzzerindex=m_ComboBuzzer.GetCurSel();

	if(buzzerindex!=CB_ERR)
	{
		m_ComboBuzzer.GetLBText(buzzerindex,m_Buzzerstr);
		
		if (buzzerindex==0&&m_Buzzerstr=="��������")
		{
			m_sendbuzz=0x01;
		}
		else if (buzzerindex==1&&m_Buzzerstr=="������")
		{
			m_sendbuzz=0x00;
		}
	}
}

void CReaderDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CReaderDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	m_rxlen=0;
	m_txlen=0;
	m_crclen=0;
	m_counter=0;
	m_lostframe=0;

	DispStatus();
}
unsigned short int CReaderDlg::Get_CRC16_Code(unsigned char* pchMsg, unsigned short int wDataLen)
{

	unsigned int CRC;
	unsigned char m_crc[22];
	BYTE m_low,m_high;
	BYTE m_word;
	//ת���ַ�����
	for (int i=0,j=0;i<44,j<22;i++,j++)
	{
		m_high=ConvertHexData(pchMsg[i++]);
		m_low=ConvertHexData(pchMsg[i]);
		m_word=m_high<<4;
		m_word+=m_low;
		m_crc[j]=m_word;
	}

	CRC  = crc16(m_crc, wDataLen);

	return CRC;
}
//������ѭ��0-255
int CReaderDlg::Counters()
{
	if (255!=m_counters)
	{
		m_counters++;
	}
	else
	{
		m_counters=0;
	}

	return m_counters;
}


unsigned int CReaderDlg::crc16(unsigned char *pchMsg, unsigned int wDataLen)
{
/*
    unsigned char uchCRCHi = 0xFF ;                       // ��CRC�ֽڳ�ʼ�� 
    unsigned char uchCRCLo = 0xFF ;                       // ��CRC �ֽڳ�ʼ��
    long unsigned int uIndex ;                            // CRCѭ���е����� 
    while (usDataLen--)                                   // ������Ϣ������  
    { 
        uIndex = uchCRCHi ^ *puchMsg++ ;                  // ����CRC         
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
        uchCRCLo = auchCRCLo[uIndex] ; 
    }          
    return ((uchCRCLo << 8) | uchCRCHi) ; 
*/

 unsigned  int wCRCTalbeAbs[] =
	{
		0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 
		0x3C00, 0x2800, 0xE401, 0xA001, 0x6C00, 
		0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 
		0x4400
	};
	unsigned  int wCRC = 0xFFFF;
	unsigned  int i = 0;
	unsigned char chChar = 0;
	
	for (i = 0; i < wDataLen; i++)
	{
		chChar = *pchMsg++;
		wCRC = wCRCTalbeAbs[(chChar ^ wCRC) & 15] ^ (wCRC >> 4);
		wCRC = wCRCTalbeAbs[((chChar >> 4) ^ wCRC) & 15] ^ (wCRC >> 4);
	}
	
	return wCRC;



}



/*
unsigned int CReaderDlg::crc16(unsigned char* pchMsg, unsigned  int wDataLen)
{
  

 unsigned  int wCRCTalbeAbs[] =
	{
		0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 
		0x3C00, 0x2800, 0xE401, 0xA001, 0x6C00, 
		0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 
		0x4400
	};
	unsigned  int wCRC = 0xFFFF;
	unsigned  int i = 0;
	unsigned char chChar = 0;
	
	for (i = 0; i < wDataLen; i++)
	{
		chChar = *pchMsg++;
		wCRC = wCRCTalbeAbs[(chChar ^ wCRC) & 15] ^ (wCRC >> 4);
		wCRC = wCRCTalbeAbs[((chChar >> 4) ^ wCRC) & 15] ^ (wCRC >> 4);
	}
	
	return wCRC;

}
*/