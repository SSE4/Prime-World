﻿#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <System/systemStdAfx.h>
#include <System/CmdLine.h>

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND              g_hWnd       = NULL;
HWND              g_hWndFade       = NULL;
HWND              g_hWndParent       = NULL;
LPDIRECT3D9       g_pD3D       = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

struct Vertex
{
	float x, y, z; // Position of vertex in 3D space
  DWORD color;   // Color of vertex
};
#define D3DFVF_MY_VERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE )

void EnableCursor(bool enable)
{
  if (enable)
  {
    OutputDebugString("Cursor ON\n");
  } else
  {
    OutputDebugString("Cursor OFF\n");
  }
  ShowCursor(enable);
}

bool SendData(HWND sender, HWND reciever, int id, void* data=0, int size=0)
{
  COPYDATASTRUCT copyData;
  copyData.dwData = id;          // function identifier
  copyData.cbData = size;  
  copyData.lpData = data ;           // data structure

  if( reciever != NULL )
  {
    SendMessage( reciever,
                 WM_COPYDATA,
                 (WPARAM)(HWND) sender,
                 (LPARAM) (LPVOID) &copyData );
    return true;
  }
  return false;
}

struct TriangleFan
{
  TriangleFan(LPDIRECT3DDEVICE9 _device):
  device(_device),
  opacity(1.f),
  needToSet(false)
  {
  }

  ~TriangleFan() 
  {
    	if( vertexBuffer != NULL ) 
        vertexBuffer->Release(); 
  }

  void SetOpacity(float _opacity)
  {
    opacity = _opacity;
    needToSet = true;
  }

  void Fill(Vertex* vertices, int bufferSize)
  {
    vertexCount = bufferSize/sizeof(Vertex);
	  Vertex *pVertices = NULL;
	  g_pd3dDevice->CreateVertexBuffer( bufferSize, 0, D3DFVF_MY_VERTEX,
									    D3DPOOL_DEFAULT, &vertexBuffer,
									    NULL );

	  pVertices = NULL;
	  vertexBuffer->Lock( 0, bufferSize, (void**)&pVertices, 0 );
    memcpy( pVertices, vertices, bufferSize );
    vertexBuffer->Unlock();
  }

  D3DCOLORVALUE ConvertDWORDToColor(DWORD color)
  {
    D3DCOLORVALUE result;
    const float OO_255 = 1.f / 255.f;
    result.r = ((color & 0x00FF0000) >> 16) * OO_255;
    result.g = ((color & 0x0000FF00) >> 8) * OO_255;
    result.b = (color & 0x000000FF) * OO_255;
    result.a = ((color & 0xFF000000) >> 24 ) * OO_255;
    return result;
  }

  DWORD ConvertColorToDWORD(const D3DCOLORVALUE& color)
  {
    return D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);
  }


  void Render()
  {
    if (needToSet)
    {
  	  Vertex *pVertices = NULL;
  	  vertexBuffer->Lock( 0, vertexCount*sizeof(Vertex), (void**)&pVertices, 0 );
      for (int i=0;i<vertexCount;++i)
      {
        D3DCOLORVALUE color = ConvertDWORDToColor(pVertices[i].color);
        color.a = opacity;
        pVertices[i].color = ConvertColorToDWORD(color);
      }
      vertexBuffer->Unlock();
      needToSet = false;
    }

		device->SetStreamSource( 0, vertexBuffer, 0, sizeof(Vertex) );
		device->SetFVF( D3DFVF_MY_VERTEX );
		device->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, vertexCount-2 );
  }

  LPDIRECT3DDEVICE9 device;
  LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
  int vertexCount;
  float opacity;
  bool needToSet;
};

TriangleFan* gOnScreenFan = 0;
TriangleFan* gOnScreenFanFS = 0;

uint desiredWidth = 1024;
uint desiredHeight = 768;

uint userModeWidth = 1024;
uint userModeHeight = 768;

bool gIsFullScreen = false;
bool gIsChild = false;

bool g_bRenderInWireFrame = false;

void EnableDecorator(bool enable)
{
  if (enable)
  {
    OutputDebugString("Decorator ON\n");
  } else
  {
    OutputDebugString("Decorator OFF\n");
  }
  if (gIsFullScreen)
  {
    ShowWindow(g_hWndFade, enable);
    if (enable)
    {
      UpdateWindow(g_hWndFade);
    }
  }
}

Vertex g_triangleFan[] = 
{
    { 0.0f, -1.0f, 0.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ) },
    {-1.0f, 0.0f, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ) },
    {-0.5f, 0.5f, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 1.0, 1.0 ) },
    { 0.0f, 1.0f, 0.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ) },
    { 0.5f, 0.5f, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ) },
    { 1.0f, 0.0f, 0.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ) }
};

const float edge = 2.1f;

Vertex g_triangleFanFS[] = 
{
    { edge, -edge, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 0.0, 0.0 ) },
    {-edge, -edge, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 0.0, 0.0 ) },
    {-edge, edge, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 0.0, 0.0 ) },
    { edge, edge, 0.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 0.0, 0.0 ) },
};

enum ApplicationMode
{
  Idle,
  FadingOut,
  Starting,
  PendingStart,
  PendingExit,
  ParentWaitingChildQuit,
  Started,
  FadingIn,
  Exit,
};

enum ChildState
{
  ChildDeviceCreated,
  ParentDecoratorShowed,
  ChildPendingExit,
};

ApplicationMode gMode = Idle;
float gOpacity = 0.f;
NHPTimer::STime gStart;
//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcFADE(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int init(bool);
void shutDown(void);
void render(void);
void ErrorExit(LPTSTR lpszFunction) ;

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpCmdLine,
                    int       nCmdShow )
{
    EnableCursor(FALSE);
    userModeWidth = GetSystemMetrics(SM_CXSCREEN);
    userModeHeight = GetSystemMetrics(SM_CYSCREEN);
    desiredWidth = userModeWidth;
    desiredHeight = userModeHeight;
    NCmdLine::CCmdLine cmd("FullScreenTest");
    cmd.AddOption("--fullscreen", &gIsFullScreen, "Start in full screen");
    cmd.AddOption("--width", &desiredWidth, "Desired width");
    cmd.AddOption("--height", &desiredHeight, "Desired height");
    cmd.AddOption("--child", &gIsChild, "Start in child mode");
    NCmdLine::CCmdLine::EProcessResult result = cmd.Process( lpCmdLine );
    if ( result != NCmdLine::CCmdLine::PROC_RESULT_OK && result != NCmdLine::CCmdLine::PROC_RESULT_NO_ARGUMENTS)
    {
      cmd.PrintUsage("Usage:");
      return 1;
    }

    if (gIsFullScreen) 
    {
      WNDCLASSEX winClassFade;
      winClassFade.lpszClassName = "MY_WINDOWS_CLASS_FADE";
      winClassFade.cbSize        = sizeof(WNDCLASSEX);
      winClassFade.style         = CS_HREDRAW | CS_VREDRAW;
      winClassFade.lpfnWndProc   = WindowProc;
      winClassFade.hInstance     = hInstance;
      winClassFade.hIcon         = 0;
      winClassFade.hIconSm       = 0;
      winClassFade.hCursor       = LoadCursor(NULL, IDC_ARROW);
      winClassFade.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
      winClassFade.lpszMenuName  = NULL;
      winClassFade.cbClsExtra    = 0;
      winClassFade.cbWndExtra    = 0;

      if( RegisterClassEx(&winClassFade) == 0 )
          return E_FAIL;
      DWORD flag = 0;
      if (gIsChild)
      {
        flag = WS_VISIBLE;
      }
      g_hWndFade = CreateWindowEx( WS_EX_TOPMOST, "MY_WINDOWS_CLASS_FADE", 
                               "FullScreenTestDecoration",
                               WS_POPUP | WS_SYSMENU | flag,
                               0, 0, userModeWidth, userModeHeight, NULL, NULL, hInstance, NULL );
      
      if( g_hWndFade == NULL )
          return E_FAIL;
      if (gIsChild)
      {
        ShowWindow(g_hWndFade, SW_SHOW);
        UpdateWindow(g_hWndFade);
      }
    }


    const char* parentClassName = "NIVAL_CASTLE_WINDOW";
    const char* childClassName = "NIVAL_BATTLEGROUND_WINDOW";

    WNDCLASSEX winClass;
    winClass.lpszClassName = gIsChild?childClassName:parentClassName;
    winClass.cbSize        = sizeof(WNDCLASSEX);
    winClass.style         = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc   = WindowProc;
    winClass.hInstance     = hInstance;
    winClass.hIcon         = 0;
    winClass.hIconSm       = 0;
    winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    winClass.lpszMenuName  = NULL;
    winClass.cbClsExtra    = 0;
    winClass.cbWndExtra    = 0;

    if( RegisterClassEx(&winClass) == 0 )
        return E_FAIL;

    if (gIsChild)
    {
      g_hWndParent = FindWindow(parentClassName, 0);
    }

    DWORD flags = WS_SYSMENU;
    if (gIsFullScreen)
    {
      flags |= WS_POPUP;
    } else
    {
      flags |= WS_OVERLAPPED | WS_VISIBLE;
    }
    STARTUPINFO info;
    GetStartupInfo(&info);
    int x = gIsFullScreen?0:CW_USEDEFAULT;
    int y = (gIsFullScreen?0:CW_USEDEFAULT);
    if (info.dwFlags & STARTF_USEPOSITION)
    {
      x = info.dwX;
      y = info.dwY;
    }

    g_hWnd = CreateWindowEx( NULL, gIsChild?childClassName:parentClassName, 
                             "FullScreen Test",
                              flags,
                             x, y, 
                             gIsFullScreen?userModeWidth:desiredWidth, 
                             gIsFullScreen?userModeHeight:desiredHeight, 
                             NULL, NULL, hInstance, NULL );

    if( g_hWnd == NULL )
    {
      ErrorExit("CreateWindowEx");
    }

    ShowWindow( g_hWnd, SW_SHOW );
    UpdateWindow( g_hWnd );

    int iresult = init(gIsFullScreen);
    if (iresult != 0)
    {
      char buffer[256];
      sprintf_s(buffer, 256, "Display initialization error %d", iresult);
      MessageBox(NULL, (LPCTSTR)buffer, TEXT("Error"), MB_OK); 
      return E_FAIL;
    }
    if (g_hWndParent)
    {
      SendData(g_hWnd, g_hWndParent, ChildDeviceCreated);
    }
    if (!gIsChild)
    {
      EnableCursor(TRUE);
    } else
    {
      EnableDecorator(false);
    }

    MSG        uMsg;
    memset(&uMsg,0,sizeof(uMsg));
    while( uMsg.message != WM_QUIT )
    {
        if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &uMsg );
            DispatchMessage( &uMsg );
        }
        else
            render();
    }

    shutDown();

    UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );

    return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
                             UINT   msg, 
                             WPARAM wParam, 
                             LPARAM lParam )
{
    switch( msg )
    {
        case WM_KEYDOWN:
		    {
			    switch( wParam )
			    {
				    case VK_ESCAPE:
					    PostQuitMessage(0);
				    break;
            case VK_SPACE:
              if (gMode == Idle)
              {
                NHPTimer::GetTime(gStart);
                gMode = FadingOut;
                EnableCursor(FALSE);
              } else
              if (gMode == FadingOut)
              {
                NHPTimer::GetTime(gStart);
                gMode = FadingIn;
              } else
              if (gMode == FadingIn)
              {
                NHPTimer::GetTime(gStart);
                gMode = FadingOut;
              }
            break;

				    case VK_F2:
                        g_bRenderInWireFrame = !g_bRenderInWireFrame;
                        if( g_bRenderInWireFrame == true )
                            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
                        else
                            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
			    }
		    }
        break;

      case WM_CLOSE:
        {
            PostQuitMessage(0);
        }
        break;
      case WM_COPYDATA:
        {
          PCOPYDATASTRUCT copyData = (PCOPYDATASTRUCT) lParam;
           switch( copyData->dwData )
           {
              case ChildDeviceCreated:
                EnableDecorator(false);
                gMode = Started;
                break; 
              case ChildPendingExit:
                EnableDecorator(true);
                gMode = ParentWaitingChildQuit;
                g_hWndParent = (HWND)wParam;
                break;
              case ParentDecoratorShowed:
                PostQuitMessage(0);
                break;
           }
        }
        break;
        case WM_WINDOWPOSCHANGED:
          {
            if (g_hWndParent)
            {
              RECT rect;
              GetWindowRect(g_hWnd, &rect);
              //MoveWindow(g_hWndParent, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, FALSE);
            }
          }
          break;
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;

        default:
        {
            return DefWindowProc( hWnd, msg, wParam, lParam );
        }
        break;
    }

    return 0;
}

LRESULT CALLBACK WindowProcFADE( HWND   hWnd, 
                             UINT   msg, 
                             WPARAM wParam, 
                             LPARAM lParam )
{
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------
int init( bool isFullScreen )
{
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    if( g_pD3D == NULL )
    {
        // TO DO: Respond to failure of Direct3DCreate8
        return 1;
    }

    //
    // For the default adapter, examine all of its display modes to see if any 
    // of them can give us the hardware support we desire.
    //

    int nMode = 0;
    D3DDISPLAYMODE d3ddm;
    bool bDesiredAdapterModeFound = false;

    int nMaxAdapterModes = g_pD3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, 
                                                        D3DFMT_X8R8G8B8 );

    for( nMode = 0; nMode < nMaxAdapterModes; ++nMode )
    {
        if( FAILED( g_pD3D->EnumAdapterModes( D3DADAPTER_DEFAULT, 
                                              D3DFMT_X8R8G8B8, nMode, &d3ddm ) ) )
        {
            // TO DO: Respond to failure of EnumAdapterModes
            return 2;
        }

        // Does this adapter mode support a mode of desiredWidth x desiredHeight?
        if( d3ddm.Width != desiredWidth || d3ddm.Height != desiredHeight )
            continue;

        // Does this adapter mode support a 32-bit RGB pixel format?
        if( d3ddm.Format != D3DFMT_X8R8G8B8 )
            continue;

        // Does this adapter mode support a refresh rate of 75 MHz?
        if( d3ddm.RefreshRate != 60 )
            continue;

        // We found a match!
        bDesiredAdapterModeFound = true;
        break;
    }

    if( bDesiredAdapterModeFound == false )
    {
        // TO DO: Handle lack of support for desired adapter mode...
        return 3;
    }

    //
    // Here's the manual way of verifying hardware support.
    //

    // Can we get a 32-bit back buffer?
    if( FAILED( g_pD3D->CheckDeviceType( D3DADAPTER_DEFAULT,
                                         D3DDEVTYPE_HAL,
                                         D3DFMT_X8R8G8B8,
                                         D3DFMT_X8R8G8B8,
                                         FALSE ) ) )
    {
        // TO DO: Handle lack of support for a 32-bit back buffer...
        return 4;
    }

    // Can we get a z-buffer that's at least 16 bits?
    if( FAILED( g_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT,
                                           D3DDEVTYPE_HAL,
                                           D3DFMT_X8R8G8B8,
                                           D3DUSAGE_DEPTHSTENCIL,
                                           D3DRTYPE_SURFACE,
                                           D3DFMT_D16 ) ) )
    {
        // TO DO: Handle lack of support for a 16-bit z-buffer...
        return 5;
    }

    //
    // Do we support hardware vertex processing? if so, use it. 
    // If not, downgrade to software.
    //

    D3DCAPS9 d3dCaps;

    if( FAILED( g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT,
                                       D3DDEVTYPE_HAL, &d3dCaps ) ) )
    {
        // TO DO: Respond to failure of GetDeviceCaps
        return 6;
    }

    DWORD flags = 0;

    if( d3dCaps.VertexProcessingCaps != 0 )
        flags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        flags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    //
    // Everything checks out - create a simple, full-screen device.
    //

    D3DPRESENT_PARAMETERS d3dpp;
    memset(&d3dpp, 0, sizeof(d3dpp));
    
    d3dpp.Windowed               = !isFullScreen;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferWidth        = desiredWidth;
    d3dpp.BackBufferHeight       = desiredHeight;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                                      flags, &d3dpp, &g_pd3dDevice ) ) )
    {
        // TO DO: Respond to failure of CreateDevice
        return 7;
    }

	  g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	  g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_pd3dDevice->SetRenderState( D3DRS_COLORVERTEX, TRUE );
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,0.0f), 1.0f, 0 );

	  D3DXMATRIX mProjection;
    D3DXMatrixPerspectiveFovLH( &mProjection, D3DXToRadian( 45.0f ), 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &mProjection );

	  //
	  // Triangle Fan
	  //
    gOnScreenFan = new TriangleFan(g_pd3dDevice);
    gOnScreenFan->Fill(g_triangleFan, sizeof(g_triangleFan));
    gOnScreenFanFS = new TriangleFan(g_pd3dDevice);
    if (!gIsChild)
    {
      gOpacity = 0.f;
      gMode = Idle;
    } else
    {
      gOpacity = 1.0f;
      gMode = FadingIn;
      NHPTimer::GetTime(gStart);
    }
    gOnScreenFanFS->SetOpacity(gOpacity);
    gOnScreenFanFS->Fill(g_triangleFanFS, sizeof(g_triangleFanFS));
    return 0;
}

//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void shutDown( void )
{
  if (gOnScreenFan)
  {
    delete gOnScreenFan;
    gOnScreenFan = 0;
  }
  if (gOnScreenFanFS)
  {
    delete gOnScreenFanFS;
    gOnScreenFanFS = 0;
  }
  if( g_pd3dDevice != NULL )
  {
        g_pd3dDevice->Release();
        g_pd3dDevice = 0;
  }

    if( g_pD3D != NULL )
    {
        g_pD3D->Release();
        g_pD3D = 0;
    }
}

//-----------------------------------------------------------------------------
// Name: render()
// Desc: 
//-----------------------------------------------------------------------------

void ErrorExit(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    sprintf_s((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

static PROCESS_INFORMATION pinfo;


void render( void )
{
  if (gMode != Idle)
  {
    NHPTimer::STime current;
    NHPTimer::GetTime(current);
    float delta = NHPTimer::Time2Seconds(current-gStart);
    const float fadeSpeed = 0.5f;
    gStart = current;
    if (gMode == FadingOut)
    {
      gOpacity += fadeSpeed*delta;
      if (gOpacity >= 1.f)
      {
        gOpacity = 1.f;
        gMode = Starting;
      }
      gOnScreenFanFS->SetOpacity(gOpacity);
    } else
    if (gMode == FadingIn)
    {
      gOpacity -= fadeSpeed*delta;
      if (gOpacity <= 0.f)
      {
        gOpacity = 0.f;
        gMode = Idle;
        EnableCursor(TRUE);
      }
      gOnScreenFanFS->SetOpacity(gOpacity);
    } else
    if (gMode == Starting)
    {
      if (!gIsChild)
      {
        RECT rect;
        GetWindowRect(g_hWnd, &rect);

        DWORD flags = 0;
        STARTUPINFO info;
        memset(&info, 0, sizeof(STARTUPINFO));
        info.cb = sizeof(STARTUPINFO);
        info.lpReserved = 0;
        info.lpDesktop = 0;
        info.lpTitle = 0;
        info.dwX = rect.left;
        info.dwY = rect.top;
        info.dwXSize = rect.right-rect.left;
        info.dwYSize = rect.bottom-rect.top;
        info.dwXCountChars = 0;
        info.dwYCountChars = 0;
        info.dwFillAttribute = 0;
        info.dwFlags = STARTF_FORCEOFFFEEDBACK | STARTF_USEPOSITION | STARTF_USESIZE; 
        info.wShowWindow = 0;
        info.cbReserved2 = 0;
        info.lpReserved2 = 0;
        info.hStdError = 0;
        info.hStdOutput = 0;
        EnableDecorator(true);
        shutDown();
        char buffer[256];
        sprintf_s(buffer, 256,  "main.exe --child 1 --fullscreen %d --width %d --height %d", int(gIsFullScreen), desiredWidth, desiredHeight);
        if (CreateProcess(0,  buffer, 0, 0, FALSE, flags, 0, 0, &info, &pinfo))
        {
          gMode = PendingStart;
        } else
        {
          ErrorExit("StartProcess");
        }
      } else
      {
          EnableDecorator(true);
          if (g_hWndParent)
          {
            SendData(g_hWnd, g_hWndParent, ChildPendingExit);
            gMode = PendingExit;
          } else
          {
            PostQuitMessage(0);
            gMode = Exit;
          }
      }
      
    } else
    if (gMode == PendingStart || gMode == Started || gMode == ParentWaitingChildQuit)
    {
      if (WaitForSingleObject( pinfo.hProcess, 0 ) == WAIT_OBJECT_0)
      {
        init(gIsFullScreen);
        EnableDecorator(false);
        gMode = FadingIn;
        gOpacity = 1.f;
        gOnScreenFanFS->SetOpacity(gOpacity);
        NHPTimer::GetTime(gStart);
      }
      if (gMode == ParentWaitingChildQuit)
      {
        if (g_hWndParent)
        {
          SendData(g_hWnd, g_hWndParent, ParentDecoratorShowed);
        }
        gMode = Started;
      }
    } 
  }
  if (g_pd3dDevice)
  {
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
      (!gIsChild)?D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,0.0f):D3DCOLOR_COLORVALUE(0.0f,1.0f,1.0f,0.0f), 1.0f, 0 );
    g_pd3dDevice->BeginScene();

      // Render geometry here...
	  D3DXMATRIX mWorld;
	  D3DXMatrixTranslation( &mWorld, 0.0f, 0.0f, 5.0f );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &mWorld );

    gOnScreenFan->Render();
    gOnScreenFanFS->Render();

    g_pd3dDevice->EndScene();

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
  }
}
