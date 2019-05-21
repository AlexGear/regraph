#include "regraph.h"

int COLOR(int r, int g, int b) { return RGB(r, g, b); }
int initwindow(int width, int height, const char *title, int, int, bool, bool closeflag) {
    return Regraph::initwindow(width, height, title, closeflag);
}
void closegraph(int windowID)      { Regraph::closegraph(windowID); }
void setcurrentwindow(int window)  { Regraph::setcurrentwindow(window); }
int getcurrentwindow()             { return Regraph::getcurrentwindow(); }

void delay(int ms)                 { Sleep(ms); }

void sector(int x, int y, int stangle, int endangle, int xrad, int yrad)     { Regraph::sector(x, y, stangle, endangle, xrad, yrad); }
void pieslice(int x, int y, int stangle, int endangle, int radius)           { sector(x, y, stangle, endangle, radius, radius); }
void ellipse(int x, int y, int stangle, int endangle, int xrad, int yrad)    { Regraph::ellipse(x, y, stangle, endangle, xrad, yrad); }
void arc(int x, int y, int stangle, int endangle, int radius)                { ellipse(x, y, stangle, endangle, radius, radius); }
void circle(int x, int y, int radius)                                        { Regraph::circle(x, y, radius); }
void rectangle(int left, int top, int right, int bottom)                     { Regraph::rectangle(left, top, right, bottom); }
void bar(int left, int top, int right, int bottom)                           { Regraph::bar(left, top, right, bottom); }
void bar3d(int left, int top, int right, int bottom, int depth, int topflag) { Regraph::bar3d(left, top, right, bottom, depth, topflag); }
void drawpoly(int n_points, int *points)                                     { Regraph::drawpoly(n_points, points); }
void fillpoly(int n_points, int *points)                                     { Regraph::fillpoly(n_points, points); }
void fillellipse(int x, int y, int xradius, int yradius)                     { Regraph::fillellipse(x, y, xradius, yradius); }
void floodfill(int x, int y, int border)                                     { Regraph::floodfill(x, y, border); }

void outtext(const char *textstring)                                       { Regraph::outtext(textstring); }
void outtextxy(int x, int y, const char *textstring)                       { Regraph::outtextxy(x, y, textstring); }
void settextjustify(int horiz, int vert)                                   { Regraph::settextjustify(horiz, vert); }
void settextstyle(int font, int direction, int charsize)                   { Regraph::settextstyle(font, direction, charsize); }
void settextstyle(const char *fontface, int attr, int angle, int charsize) { Regraph::settextstyle(fontface, attr, angle, charsize); }
int textheight(const char *textstring)                                     { return Regraph::textheight(textstring); }
int textwidth(const char *textstring)                                      { return Regraph::textwidth(textstring); }

void cleardevice()                                      { Regraph::cleardevice(); }
void moveto(int x, int y)                               { Regraph::moveto(x, y); }
void moverel(int dx, int dy)                            { Regraph::moverel(dx, dy); }
void lineto(int x, int y)                               { Regraph::lineto(x, y); }
void linerel(int dx, int dy)                            { Regraph::linerel(dx, dy); }
void line(int startx, int starty, int endx, int endy)   { Regraph::line(startx, starty, endx, endy); }

void putpixel(int x, int y, int color)   { Regraph::putpixel(x, y, color); }
int getpixel(int x, int y)               { return Regraph::getpixel(x, y); }
void setcolor(int color)                 { Regraph::setcolor(color); }
int getcolor()                           { return Regraph::getcolor(); }
void setbkcolor(int bkcolor)             { Regraph::setbkcolor(bkcolor); }
int getbkcolor()                         { return Regraph::getbkcolor(); }

void setbktransparent(bool transparent)                            { Regraph::setbktransparent(transparent); }
bool getbktransparent()                                            { return Regraph::getbktransparent(); }
void setlinestyle(int linestyle, unsigned upattern, int thickness) { Regraph::setlinestyle(linestyle, upattern, thickness); }
void setfillstyle(int pattern, int color, bool transparentBk)      { Regraph::setfillstyle(pattern, color, transparentBk); }
void setfillpattern(char *upattern, int color, bool transparentBk) { Regraph::setfillpattern(upattern, color, transparentBk); }
void getfillpattern(char *pattern)                                 { Regraph::getfillpattern(pattern); }

unsigned imagesize(int left, int top, int right, int bottom) {
    unsigned width = right - left + 1;
    unsigned height = bottom - top + 1;
    return sizeof(int) * (1 + width*height);
}
void getimage(int left, int top, int right, int bottom, void *bitmap) { Regraph::getimage(left, top, right, bottom, bitmap); }
void putimage(int left, int top, void *bitmap, int op)                { Regraph::putimage(left, top, bitmap, op); }

int mousex()                                 { return Regraph::mousex(); }
int mousey()                                 { return Regraph::mousey(); }
int ismouseclick(int kind)                   { return Regraph::ismouseclick(kind); }
void clearmouseclick(int kind)               { Regraph::clearmouseclick(kind); }
void getmouseclick(int kind, int &x, int &y) { Regraph::getmouseclick(kind, x, y); }

int getx()             { return Regraph::getx(); }
int gety()             { return Regraph::gety(); }
int getmaxheight()     { return GetSystemMetrics(SM_CXSCREEN); }
int getmaxwidth()      { return GetSystemMetrics(SM_CYSCREEN); }
int getwindowwidth()   { return Regraph::getwindowwidth(); }
int getwindowheight()  { return Regraph::getwindowheight(); }
int getmaxx()          { return Regraph::getmaxx(); }
int getmaxy()          { return Regraph::getmaxy(); }

int getch()            { return Regraph::getch(); }
int kbhit()            { return Regraph::kbhit(); }



int Regraph::currentWindowID = -1;
int Regraph::currentWindowIndex = -1;
std::vector<RegraphWindow> Regraph::windowList;

void RegraphWindow::refreshWindow()           { InvalidateRect(windowHandle, NULL, false); }
void RegraphWindow::refreshWindow(RECT rect)  { InvalidateRect(windowHandle, &rect, false); }

void RegraphWindow::putCopy(HDC dc, int x, int y, int color) { SetPixel(dc, x, y, 0xFFFFFF & (color)); }
void RegraphWindow::putXor(HDC dc, int x, int y, int color)  { SetPixel(dc, x, y, 0xFFFFFF & (color ^ GetPixel(dc, x, y))); }
void RegraphWindow::putOr(HDC dc, int x, int y, int color)   { SetPixel(dc, x, y, 0xFFFFFF & (color | GetPixel(dc, x, y))); }
void RegraphWindow::putAnd(HDC dc, int x, int y, int color)  { SetPixel(dc, x, y, 0xFFFFFF & (color & GetPixel(dc, x, y))); }
void RegraphWindow::putNot(HDC dc, int x, int y, int color)  { SetPixel(dc, x, y, 0xFFFFFF & (~color)); }

RECT RegraphWindow::getWindowRect()      { return RECT { 0, 0, width, height }; }
HWND RegraphWindow::getWindowHandle()    { return windowHandle; }
HDC& RegraphWindow::getDeviceContext()   { return memDC; }
int  RegraphWindow::getID()              { return id; }

void RegraphWindow::floodFill(int x, int y, int borderColor) {
    SYNCHRONIZED(drawMutex, FloodFill(memDC, x, y, borderColor));
    refreshWindow();
}

void RegraphWindow::moveTo(int x, int y) {
    SYNCHRONIZED(drawMutex, MoveToEx(memDC, x, y, NULL));
}

void RegraphWindow::setPixel(int x, int y, int color) {
    SYNCHRONIZED(drawMutex, SetPixel(memDC, x, y, color));
    refreshWindow(RECT{x-1, y-1, x+1, y+1});
}

int RegraphWindow::getPixel(int x, int y) {
    return GetPixel(memDC, x, y);
}

int RegraphWindow::getColor()   { return mainColor; }
int RegraphWindow::getBkColor() { return backgroundColor; }
int RegraphWindow::getMouseX()  { return mouseX; }
int RegraphWindow::getMouseY()  { return mouseY; }
int RegraphWindow::getMaxX()    { return width - 1; }
int RegraphWindow::getMaxY()    { return height - 1; }


RegraphWindow* Regraph::currentWindow() { return currentWindowIndex >= 0 ? &windowList[currentWindowIndex] : NULL; }
HDC* Regraph::currentDC()               { return currentWindowIndex >= 0 ?  &currentWindow()->getDeviceContext() : NULL; }

void Regraph::setcurrentwindow(int window)                  { if(findWindowByID(window, &currentWindowIndex)) currentWindowID = window; }
int  Regraph::getcurrentwindow()                            { return currentWindowID; }

void Regraph::sector(int x, int y, int sa, int ea, int xr, int yr)   { IF_WND( currentWindow()->sector(x, y, sa, ea, xr, yr) ); }
void Regraph::circle(int x, int y, int radius)                       { IF_WND( currentWindow()->circle(x, y, radius) ); }
void Regraph::ellipse(int x, int y, int sa, int ea, int xr, int yr)  { IF_WND( currentWindow()->ellipse(x, y, sa, ea, xr, yr) ); }
void Regraph::rectangle(int left, int top, int right, int bottom)    { IF_WND( currentWindow()->rectangle(left, top, right, bottom) ); }
void Regraph::bar(int left, int top, int right, int bottom)          { IF_WND( currentWindow()->bar(left, top, right, bottom) ); }
void Regraph::bar3d(int l, int tp, int r, int bt, int dep, int topf) { IF_WND( currentWindow()->bar3d(l, tp, r, bt, dep, topf) ); }
void Regraph::drawpoly(int numpoints, int *points)                   { IF_WND( currentWindow()->drawPoly(numpoints, points) ); }
void Regraph::fillpoly(int numpoints, int *points)                   { IF_WND( currentWindow()->fillPoly(numpoints, points) ); }
void Regraph::fillellipse(int x, int y, int xrad, int yrad)          { IF_WND( currentWindow()->fillEllipse(x, y, xrad, yrad) ); }
void Regraph::floodfill(int x, int y, int borderColor)               { IF_WND( currentWindow()->floodFill(x, y, borderColor) );}

void Regraph::cleardevice()                                      { IF_WND( currentWindow()->clearDevice() ); }
void Regraph::moveto(int x, int y)                               { IF_WND( currentWindow()->moveTo(x, y) ); }
void Regraph::moverel(int dx, int dy)                            { IF_WND( currentWindow()->moveRel(dx, dy) ); }
void Regraph::lineto(int x, int y)                               { IF_WND( currentWindow()->lineTo(x, y) ); }
void Regraph::linerel(int dx, int dy)                            { IF_WND( currentWindow()->lineRel(dx, dy) ); }
void Regraph::line(int startx, int starty, int endx, int endy)   { IF_WND( currentWindow()->line(startx, starty, endx, endy) ); }

void Regraph::outtext(const char *textstring)                         { IF_WND( currentWindow()->outText(textstring) ); }
void Regraph::outtextxy(int x, int y, const char *textstring)         { IF_WND( currentWindow()->outTextXY(x, y, textstring) ); }
void Regraph::settextjustify(int horiz, int vert)                     { IF_WND( currentWindow()->setTextJustify(horiz, vert) ); }
void Regraph::settextstyle(int font, int direction, int charsize)     { IF_WND( currentWindow()->setTextStyle(font, direction, charsize) ); }
void Regraph::settextstyle(const char *fac, int at, int ang, int siz) { IF_WND( currentWindow()->setTextStyle(fac, at, ang, siz) ); }
int  Regraph::textheight(const char *textstring)                      { return IF_WND_0( currentWindow()->textHeight(textstring)); }
int  Regraph::textwidth(const char *textstring)                       { return IF_WND_0( currentWindow()->textWidth(textstring) ); }

int  Regraph::getpixel(int x, int y)              { return IF_WND_0( currentWindow()->getPixel(x, y) ); }
void Regraph::putpixel(int x, int y, int color)   { IF_WND( currentWindow()->setPixel(x, y, color) ); }
void Regraph::setcolor(int color)                 { IF_WND( currentWindow()->setColor(color) ); }
int  Regraph::getcolor()                          { return IF_WND_0( currentWindow()->getColor() ); }
void Regraph::setbkcolor(int bkcolor)             { IF_WND( currentWindow()->setBkColor(bkcolor) ); }
int  Regraph::getbkcolor()                        { return IF_WND_0( currentWindow()->getBkColor() ); }

void Regraph::setbktransparent(bool transparent)          { IF_WND( SetBkMode(*currentDC(), transparent ? TRANSPARENT : OPAQUE) ); }
bool Regraph::getbktransparent()                          { return IF_WND_0( GetBkMode(*currentDC()) == TRANSPARENT ); }
void Regraph::setlinestyle(int style, unsigned pattern, int thick) { IF_WND( currentWindow()->setLineStyle(style, pattern, thick) ); }
void Regraph::setfillstyle(int style, int color, bool trnspBk)     { IF_WND( currentWindow()->setFillStyle(style, color, trnspBk) ); }
void Regraph::setfillpattern(char *upattern, int color, bool trBk) { IF_WND( currentWindow()->setFillPattern(upattern, color, trBk) ); }
void Regraph::getfillpattern(char *pattern)                        { IF_WND( currentWindow()->getFillPattern(pattern) ); }

void Regraph::getimage(int l, int t, int r, int b, void *bitmap)   { IF_WND( currentWindow()->getImage(l, t, r, b, bitmap) ); }
void Regraph::putimage(int l, int t, void *bitmap, int op)         { IF_WND( currentWindow()->putImage(l, t, bitmap, op) ); }

int  Regraph::mousex()                                  { return IF_WND_0( currentWindow()->getMouseX() ); }
int  Regraph::mousey()                                  { return IF_WND_0( currentWindow()->getMouseY() ); }
int  Regraph::ismouseclick(int kind)                    { return IF_WND_0( currentWindow()->isMouseClick(kind) ); }
void Regraph::clearmouseclick(int kind)                 { IF_WND( currentWindow()->clearMouseClick(kind) ); }
void Regraph::getmouseclick(int kind, int &x, int &y)   { IF_WND( currentWindow()->getMouseClick(kind, x, y) ); }

int Regraph::getx()               { POINT currentPos;   GetCurrentPositionEx(*currentDC(), &currentPos);   return currentPos.x; }
int Regraph::gety()               { POINT currentPos;   GetCurrentPositionEx(*currentDC(), &currentPos);   return currentPos.y; }
int Regraph::getwindowwidth()     { return IF_WND_0( currentWindow()->getWindowRect().right ); }
int Regraph::getwindowheight()    { return IF_WND_0( currentWindow()->getWindowRect().bottom ); }
int Regraph::getmaxx()            { return IF_WND_0( currentWindow()->getMaxX() ); }
int Regraph::getmaxy()            { return IF_WND_0( currentWindow()->getMaxY() ); }

int Regraph::getch()              { return IF_WND_EX( currentWindow()->getch() , _getch() ); }
int Regraph::kbhit()              { return IF_WND_0( currentWindow()->kbhit() ); }

bool RegraphWindow::initialize(int id, int width, int height, const char *title, bool closeflag, void (*onDestroyedFunc)(int)) {
    this->id = id;
    this->width = width;
    this->height = height;
    this->closeFlag = closeflag;
    this->onDestroyedFunc = onDestroyedFunc;
    strcpy(this->title, title);

    state = INIT_PROCESS;
    keyboardMutex = CreateMutex(NULL, false, NULL);
    mouseMutex = CreateMutex(NULL, false, NULL);
    drawMutex = CreateMutex(NULL, false, NULL);
    thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)createAndProcess, this, 0, NULL);
    while(state == INIT_PROCESS)
        Sleep(10);
    return state == INIT_SUCCESS;
}

void RegraphWindow::clearDevice() {
    RECT rect = getWindowRect();
    SYNCHRONIZED(drawMutex, FillRect(memDC, &rect, backgroundBrush));
    refreshWindow();
}

LRESULT CALLBACK RegraphWindow::windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    RegraphWindow *window = Regraph::findWindowByHWND(hwnd);
    switch(msg) {
        case WM_CLOSE:
            if(window && wParam == CLOSE_FROM_CLOSEGRAPH) {
               window->closeFlag = false;
               window->cleanup();
            }
            PostMessage(hwnd, WM_QUIT, 0, 0);
            return 1;
        case WM_ERASEBKGND: return 1;
    }
    if(!window) {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    bool serviceKey = (msg == WM_KEYDOWN && isServiceKey(wParam));
    if(msg == WM_CHAR || serviceKey) {
        SYNCHRONIZED(window->keyboardMutex, {
            if(serviceKey) {
                if(window->keyboardQueue.size() >= MAX_KQ_SIZE)
                    window->keyboardQueue.pop();
                window->keyboardQueue.push(0);
            }
            if(window->keyboardQueue.size() >= MAX_KQ_SIZE)
                window->keyboardQueue.pop();
            window->keyboardQueue.push(wParam);
        });
    } else if(isMouseEvent(msg)) {
        SYNCHRONIZED(window->mouseMutex, {
            window->mouseX = GET_X_LPARAM(lParam);
            window->mouseY = GET_Y_LPARAM(lParam);
            if(window->mouseVector.size() >= MAX_MV_SIZE)
                window->mouseVector.erase(window->mouseVector.begin());
            window->mouseVector.push_back(mouseEvent{ (int)msg, window->mouseX, window->mouseY });
        });
    } else if(msg == WM_PAINT) {
        PAINTSTRUCT ps;
        Sleep(10);
        SYNCHRONIZED(window->drawMutex, {
            HDC dc = BeginPaint(window->windowHandle, &ps);
            BitBlt(dc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom,
                    window->memDC, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
            ValidateRect(window->windowHandle, &ps.rcPaint);
            EndPaint(window->windowHandle, &ps);
        });
    } else return DefWindowProc(hwnd, msg, wParam, lParam);
    return 1;
}


int RegraphWindow::getch() {
    while(true) {
        WaitForSingleObject(keyboardMutex, INFINITE);
        if(keyboardQueue.empty()) {
            ReleaseMutex(keyboardMutex);
            Sleep(10);
        } else {
            int ch = keyboardQueue.front();
            keyboardQueue.pop();
            ReleaseMutex(keyboardMutex);
            return ch;
        }
    }
}

int RegraphWindow::kbhit() {
    int hit;
    SYNCHRONIZED(keyboardMutex, hit = !keyboardQueue.empty() );
    return hit;
}

bool RegraphWindow::isMouseClick(int kind) {
    bool result = false;
    SYNCHRONIZED(mouseMutex, {
        for(unsigned int i = 0; i < mouseVector.size(); i++)
            if(mouseVector[i].kind == kind) {
                result = true;
                break;
            }
    });
    return result;
}

void RegraphWindow::clearMouseClick(int kind) {
    SYNCHRONIZED(mouseMutex, {
        for(unsigned int i = 0; i < mouseVector.size(); i++)
            if(mouseVector[i].kind == kind) {
                mouseVector.erase(mouseVector.begin() + i);
                break;
            }
    });
}

void RegraphWindow::getMouseClick(int kind, int &x, int &y) {
    SYNCHRONIZED(mouseMutex, {
        for(unsigned int i = 0; i < mouseVector.size(); i++)
            if(mouseVector[i].kind == kind) {
                x = mouseVector[i].x;   y = mouseVector[i].y;
                mouseVector.erase(mouseVector.begin() + i);
                break;
            }
    });
}

bool RegraphWindow::isServiceKey(WPARAM key) {
     return (key >= KEY_LEFT && key <= KEY_DOWN) ||
            (key >= KEY_F1 && key <= KEY_F12) ||
            key == KEY_HOME || key == KEY_END ||
            key == KEY_DELETE || key == KEY_INSERT;
}


bool RegraphWindow::isMouseEvent(UINT msg) {
    return (msg >= WM_MOUSEMOVE && msg <= WM_MBUTTONDBLCLK);
}

void RegraphWindow::showLastError(const char *prefixMessage) {
    unsigned long errorMessageID = GetLastError();
    char *detailMessage = NULL;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&detailMessage, 0, NULL);
    char fullMessage[200];
    sprintf(fullMessage, "%s\nError code: %lu. Message:\n%s", prefixMessage, errorMessageID, detailMessage);
    MessageBox(NULL, fullMessage, "Error!", MB_ICONERROR | MB_OK);
}

void RegraphWindow::createAndProcess(RegraphWindow *window) {
    sprintf(window->className, "RegraphWindow%d", window->id);

    WNDCLASSEX windowClass;
    windowClass.cbSize        = sizeof(WNDCLASSEX);
    windowClass.style         = CS_DBLCLKS;
    windowClass.lpfnWndProc   = windowProcedure;
    windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;
    windowClass.hInstance     = NULL;
    windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
    windowClass.lpszMenuName  = NULL;
    windowClass.lpszClassName = window->className;
    windowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&windowClass)) {
        showLastError("Window Registration Failed!");
        window->state = INIT_FAIL;
        Regraph::closegraph(ALL_WINDOWS, true);
        return;
    }
    window->windowHandle = CreateWindow(
        window->className, window->title,
        WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZE | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_MINIMIZE),
        (GetSystemMetrics(SM_CXSCREEN) - window->width)/2,
        (GetSystemMetrics(SM_CYSCREEN) - window->height)/2,
        window->width, window->height, NULL, NULL, NULL, NULL);

    if(window->windowHandle == NULL) {
        showLastError("Window Creation Failed!");
        window->state = INIT_FAIL;
        Regraph::closegraph(ALL_WINDOWS, true);
        return;
    }
    window->instanceHandle = GetModuleHandle(NULL);
    ShowWindow(window->windowHandle, SW_SHOWDEFAULT);
    UpdateWindow(window->windowHandle);

    RECT rect;
    GetWindowRect(window->windowHandle, &rect);
    int actualWidth = rect.right - rect.left;
    int actualHeight = rect.bottom - rect.top;
    GetClientRect(window->windowHandle, &rect);
    actualWidth += window->width - rect.right;
    actualHeight += window->height - rect.bottom;
    SetWindowPos(window->windowHandle, HWND_TOP, 0, 0, actualWidth, actualHeight, SWP_NOMOVE);

    window->outputDC = GetDC(window->windowHandle);
    window->memDC = CreateCompatibleDC(window->outputDC);
    window->outputBitmap = CreateCompatibleBitmap(window->outputDC, window->width, window->height);
    SelectObject(window->memDC, window->outputBitmap);

    window->recreateFont();
    window->setColor(window->mainColor);
    window->setBkColor(window->backgroundColor);
    window->setFillStyle(SOLID_FILL, window->brushColor, true);
    window->clearDevice();

    window->state = INIT_SUCCESS;

    MSG msg;
    BOOL result;
    while((result = GetMessage(&msg, window->windowHandle, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if(result == -1) {
        showLastError("GetMessage() failed!");
        Regraph::closegraph(ALL_WINDOWS, true);
        return;
    }

    if(window->closeFlag) {
        Regraph::closegraph(ALL_WINDOWS, true);
    } else {
        Regraph::closegraph(window->id, false);
    }
}

void RegraphWindow::close() {
    SendMessage(windowHandle, WM_CLOSE, CLOSE_FROM_CLOSEGRAPH, 0);
}

void RegraphWindow::cleanup() {
    if(pen)             DeleteObject(pen);
    if(brush)           DeleteObject(brush);
    if(font)            DeleteObject(font);
    if(memDC)   		DeleteDC(memDC);
    if(outputBitmap)    DeleteObject(outputBitmap);
    if(windowHandle) {
        if(outputDC) ReleaseDC(windowHandle, outputDC);
        DestroyWindow(windowHandle);
    }
    if(keyboardMutex)   CloseHandle(keyboardMutex);
    if(mouseMutex)      CloseHandle(mouseMutex);
    if(drawMutex)       CloseHandle(drawMutex);
    if(thread)          CloseHandle(thread);
    if(instanceHandle)  UnregisterClass(className, instanceHandle);

    if(onDestroyedFunc) onDestroyedFunc(id);
}

void RegraphWindow::sector(int x, int y, int stangle, int endangle, int xrad, int yrad) {
    int stx = x + 2000*cos(stangle*DEG2RAD);
    int sty = y - 2000*sin(stangle*DEG2RAD);
    int endx = x + 2000*cos(endangle*DEG2RAD);
    int endy = y - 2000*sin(endangle*DEG2RAD);
    SYNCHRONIZED(drawMutex, Pie(memDC, x-xrad, y-yrad, x+xrad, y+yrad, stx, sty, endx, endy) );
    refreshWindow(RECT{x-xrad-1, y-yrad-1, x+xrad+1, y+yrad+1});
}

void RegraphWindow::circle(int x, int y, int radius) {
    SYNCHRONIZED(drawMutex, {
        SelectObject(memDC, GetStockObject(NULL_BRUSH));
        Ellipse(memDC, x-radius, y-radius, x+radius, y+radius);
        SelectObject(memDC, brush);
    });
    refreshWindow(RECT{x-radius-1, y-radius-1, x+radius+1, y+radius+1});
}

void RegraphWindow::ellipse(int x, int y, int stangle, int endangle, int xrad, int yrad) {
    int stx = x + 2000*cos(stangle*DEG2RAD);
    int sty = y - 2000*sin(stangle*DEG2RAD);
    int endx = x + 2000*cos(endangle*DEG2RAD);
    int endy = y - 2000*sin(endangle*DEG2RAD);
    SYNCHRONIZED(drawMutex,  Arc(memDC, x-xrad, y-yrad, x+xrad, y+yrad, stx, sty, endx, endy) );
    refreshWindow(RECT{x-xrad-1, y-yrad-1, x+xrad+1, y+yrad+1});
}

void RegraphWindow::fillEllipse(int x, int y, int xrad, int yrad) {
    SYNCHRONIZED(drawMutex, Ellipse(memDC, x-xrad, y-yrad, x+xrad, y+yrad) );
    refreshWindow(RECT{x-xrad-1, y-yrad-1, x+xrad+1, y+yrad+1});
}

void RegraphWindow::rectangle(int left, int top, int right, int bottom) {
    SYNCHRONIZED(drawMutex, {
        SelectObject(memDC, GetStockObject(NULL_BRUSH));
        Rectangle(memDC, left, top, right, bottom);
        SelectObject(memDC, brush);
    });
    refreshWindow(RECT{left-1, top-1, right+1, bottom+1});
}

void RegraphWindow::bar(int left, int top, int right, int bottom) {
    SYNCHRONIZED(drawMutex, {
        SelectObject(memDC, GetStockObject(NULL_PEN));
        SetTextColor(memDC, brushColor);
        Rectangle(memDC, left, top, right+2, bottom+2);
        SelectObject(memDC, pen);
        SetTextColor(memDC, mainColor);
    });
    refreshWindow(RECT{left-1, top-1, right+1, bottom+1});
}

void RegraphWindow::bar3d(int left, int top, int right, int bottom, int depth, int topflag) {
    int yshift = depth * TAN_30DEG;
    SYNCHRONIZED(drawMutex, {
        if(topflag) {
            line(left+depth, top-yshift, right+depth, top-yshift);
            line(left, top, left+depth, top-yshift);
        }
        line(right, top, right+depth, top-yshift);
        line(right+depth, top-yshift, right+depth, bottom-yshift);
        line(right+depth, bottom-yshift, right, bottom);
        Rectangle(memDC, left, top, right, bottom);
    });
    refreshWindow(RECT{left-1, top-yshift-1, right+depth+1, bottom+1});
}

void RegraphWindow::drawPoly(int numpoints, int* points) {
    if(numpoints < 2 || !points)
        return;
    POINT startPos;
    SYNCHRONIZED(drawMutex, {
        MoveToEx(memDC, points[0], points[1], &startPos);
        int numcoords = 2*numpoints;
        for(int i = 2; i+1 < numcoords; i += 2) {
            LineTo(memDC, points[i], points[i+1]);
        }
        MoveToEx(memDC, startPos.x, startPos.y, NULL);
    });
    refreshWindow();
}

void RegraphWindow::fillPoly(int numpoints, int* points) {
    if(numpoints < 2 || !points)
        return;
    POINT *pointArray = new POINT[numpoints];
    for(int i = 0; i < numpoints; i++) {
        pointArray[i].x = points[2*i];
        pointArray[i].y = points[2*i + 1];
    }
    SYNCHRONIZED(drawMutex, Polygon(memDC, pointArray, numpoints) );
    delete[] pointArray;
    refreshWindow();
}

void RegraphWindow::outText(const char* textstring) {
    if(!textstring) return;
    POINT currentPos;
    GetCurrentPositionEx(memDC, &currentPos);
    SYNCHRONIZED(drawMutex, TextOutA(memDC, currentPos.x, currentPos.y, textstring, strlen(textstring)) );
    refreshWindow();
}

void RegraphWindow::outTextXY(int x, int y, const char* textstring) {
    if(!textstring) return;
    SYNCHRONIZED(drawMutex, TextOutA(memDC, x, y, textstring, strlen(textstring)) );
    refreshWindow();
}

void RegraphWindow::moveRel(int dx, int dy) {
    POINT currentPos;
    GetCurrentPositionEx(memDC, &currentPos);
    SYNCHRONIZED(drawMutex, MoveToEx(memDC, currentPos.x + dx, currentPos.y + dy, NULL) );
}

void RegraphWindow::lineTo(int x, int y) {
    POINT currentPos;
    GetCurrentPositionEx(memDC, &currentPos);
    SYNCHRONIZED(drawMutex, LineTo(memDC, x, y) );
    int rx1, rx2, ry1, ry2;
    if(currentPos.x < x) { rx1 = currentPos.x; rx2 = x; }
                 else { rx1 = x; rx2 = currentPos.x; }
    if(currentPos.y < y) { ry1 = currentPos.y; ry2 = y; }
                 else { ry1 = y; ry2 = currentPos.y; }
    refreshWindow(RECT{rx1-1, ry1-1, rx2+1, ry2+1});
}

void RegraphWindow::lineRel(int dx, int dy) {
    POINT currentPos;
    GetCurrentPositionEx(memDC, &currentPos);
    SYNCHRONIZED(drawMutex, LineTo(memDC, currentPos.x + dx, currentPos.y + dy) );
    int rx1, rx2, ry1, ry2;
    if(currentPos.x < currentPos.x+dx) { rx1 = currentPos.x; rx2 = currentPos.x+dx; }
                                  else { rx1 = currentPos.x+dx; rx2 = currentPos.x; }
    if(currentPos.y < currentPos.y+dy) { ry1 = currentPos.y; ry2 = currentPos.y+dy; }
                                  else { ry1 = currentPos.y+dy; ry2 = currentPos.y; }
    refreshWindow(RECT{rx1-1, ry1-1, rx2+1, ry2+1});
}

void RegraphWindow::line(int startx, int starty, int endx, int endy) {
    POINT oldPos;
    SYNCHRONIZED(drawMutex, {
        MoveToEx(memDC, startx, starty, &oldPos);
        LineTo(memDC, endx, endy);
        MoveToEx(memDC, oldPos.x, oldPos.y, NULL);
    });
    int rx1, rx2, ry1, ry2;
    if(startx < endx) { rx1 = startx; rx2 = endx; }
                 else { rx1 = endx; rx2 = startx; }
    if(starty < endy) { ry1 = starty; ry2 = endy; }
                 else { ry1 = endy; ry2 = starty; }
    refreshWindow(RECT{rx1-1, ry1-1, rx2+1, ry2+1});
}

void RegraphWindow::recreatePen() {
    LOGBRUSH penBrush;
    penBrush.lbColor = mainColor;
    penBrush.lbStyle = BS_SOLID;
    DWORD patternCount = (penStyle == PS_USERSTYLE ? penPatternCount : 0);
    DWORD *pattern = (penStyle == PS_USERSTYLE ? penPattern : NULL);

    SYNCHRONIZED(drawMutex, {
        if(pen) DeleteObject(pen);
        pen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_ROUND | penStyle, penWidth, &penBrush, patternCount, pattern);
        SelectObject(memDC, pen);
    });
}

void RegraphWindow::setLineStyle(int linestyle, unsigned upattern, int thickness) {
    penWidth = thickness;
    penStyle = linestyle;
    if(penStyle == PS_USERSTYLE) {
        penPatternCount = 0;
        for(int i = 0; i < 16; i++) penPattern[i] = 0;

        unsigned mask = 1;
        const unsigned lastBit = 1 << 16;
        while(!(upattern & mask) && mask < lastBit) mask <<= 1;

        if(mask == lastBit && !(upattern & mask)) {
            recreatePen();
            return;
        }
        unsigned char currentType = 1;
        while(mask < lastBit) {
            unsigned char bit = (upattern & mask) != 0;
            if(bit == currentType) {
                penPattern[penPatternCount]++;
            } else {
                penPattern[penPatternCount] *= thickness;
                (penPattern[++penPatternCount])++;
                currentType = !currentType;
            }
            mask <<= 1;
        }
        penPattern[penPatternCount++] *= thickness;
    }
    recreatePen();
}

void RegraphWindow::setFillPattern(char *pattern, int color, bool transparentBk) {
    if(!pattern) return;
    brushColor = color;
    if(brush) DeleteObject(brush);
    WORD bits[8];
    for(int i = 0; i < 8; i++)
        bits[i] = ~pattern[i];

    fillPattern = pattern;
    brush = CreatePatternBrush(CreateBitmap(8, 8, 1, 1, bits));
    SYNCHRONIZED(drawMutex, {
        SetBkMode(memDC, transparentBk ? TRANSPARENT : OPAQUE);
        SelectObject(memDC, brush);
    });
}

void RegraphWindow::getFillPattern(char* pattern) {
    if(!fillPattern)
        return;
    for(int i = 0; i < 8; i++)
        pattern[i] = fillPattern[i];
}

void RegraphWindow::getImage(int left, int top, int right, int bottom, void* bitmap) {
    int imageWidth = right - left + 1;
    int imageHeight = bottom - top + 1;
    ((int*)bitmap)[0] = imageWidth | (imageHeight << 16);
    int i = 1;
    SYNCHRONIZED(drawMutex, {
        for(int y = bottom; y >= top; y--)
            for(int x = left; x <= right; x++)
                ((int*)bitmap)[i++] = GetPixel(memDC, x, y);
    });
}

void RegraphWindow::putImage(int left, int top, void* bitmap, int op) {
    putFunction putFunc;
    switch(op) {
        case COPY_PUT:  putFunc = putCopy;  break;
        case XOR_PUT:   putFunc = putXor;   break;
        case OR_PUT:    putFunc = putOr;    break;
        case AND_PUT:   putFunc = putAnd;   break;
        case NOT_PUT:   putFunc = putNot;   break;
        default:    return;
    }
    int imageWidth = ((int*)bitmap)[0] & 0xFFFF;
    int imageHeight = (((int*)bitmap)[0] >> 16) & 0xFFFF;
    int right = left + imageWidth - 1;
    int bottom = top + imageHeight - 1;
    int i = 1;
    SYNCHRONIZED(drawMutex, {
    for(int y = bottom; y >= top; y--)
        for(int x = left; x <= right; x++)
            putFunc(memDC, x, y, ((int*)bitmap)[i++]);
    });
    refreshWindow(RECT{left-1, top-1, left+imageWidth+1, top+imageHeight+1});
}

void RegraphWindow::recreateFont() {
    DWORD weight = fontAttr & BOLD ? FW_BOLD : FW_NORMAL;
    bool italic = fontAttr  & ITALIC;
    bool underline = fontAttr  & UNDERLINE;
    bool strikeout = fontAttr  & STRIKEOUT;
    DWORD quality = fontAttr  & ANTIALIASED ? ANTIALIASED_QUALITY : PROOF_QUALITY;
    SYNCHRONIZED(drawMutex, {
        if(font) DeleteObject(font);
        font = CreateFont(fontSize, 0, fontAngle_tenths, fontAngle_tenths, weight, italic, underline, strikeout, DEFAULT_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, quality, VARIABLE_PITCH, fontFace);
        SelectObject(memDC, font);
    });
}

void RegraphWindow::setTextStyle(int font, int direction, int charsize) {
    fontAngle_tenths = (direction == HORIZ_DIR ? 0 : 900);
    fontSize = std::max(10, charsize * 10 + 10);
    fontAttr = 0;
    switch(font) {
        case 1:     strcpy(fontFace, "Times New Roman");                    break;
        case 2:     strcpy(fontFace, "Calibri Light");  fontSize /= 3;      break;
        case 3:     strcpy(fontFace, "MS Sans Serif");                      break;
        case 4:     strcpy(fontFace, "Helvetica");                          break;
        case 5:     strcpy(fontFace, "Giddyup Std");                        break;
        case 6:     strcpy(fontFace, "Cambria");                            break;
        case 7:     strcpy(fontFace, "Brush Script Std");                   break;
        case 8:     strcpy(fontFace, "Courier New");                        break;
        case 9:     strcpy(fontFace, "Century");                            break;
        case 10:    strcpy(fontFace, "Arial Black");                        break;
        case 11:    strcpy(fontFace, "Arail");                              break;
        default:    strcpy(fontFace, "Lucida Console");                     break;
    }
    recreateFont();
}

void RegraphWindow::setTextStyle(const char* face, int attr, int angle, int charsize) {
    strcpy(fontFace, face);
    fontAttr = attr;
    fontAngle_tenths = angle * 10;
    fontSize = std::max(1, charsize);
    recreateFont();
}

void RegraphWindow::setTextJustify(int horiz, int vert) {
    UINT mode = 0;
    switch(horiz) {
        case LEFT_TEXT:     mode = TA_LEFT;     break;
        case CENTER_TEXT:   mode = TA_CENTER;   break;
        case RIGHT_TEXT:    mode = TA_RIGHT;    break;
    }
    switch(vert) {
        case BOTTOM_TEXT:   mode |= TA_BOTTOM;   break;
        case VCENTER_TEXT:  mode |= TA_BASELINE; break;
        case TOP_TEXT:      mode |= TA_TOP;      break;
    }
    SYNCHRONIZED(drawMutex, SetTextAlign(memDC, mode) );
}

int RegraphWindow::textHeight(const char* textstring) {
    SIZE size;
    SYNCHRONIZED(drawMutex, GetTextExtentPoint(memDC, textstring, strlen(textstring), &size) );
    return size.cy;
}

int RegraphWindow::textWidth(const char* textstring) {
    SIZE size;
    SYNCHRONIZED(drawMutex, GetTextExtentPoint(memDC, textstring, strlen(textstring), &size) );
    return size.cx;
}

void RegraphWindow::setFillStyle(int style, int color, bool transparentBk) {
    if(style >= USER_FILL) return;
    brushColor = color;
    LOGBRUSH logBrush;
    logBrush.lbColor = color;
    if(style >= LINE_FILL && style <= XHATCH_FILL)
        logBrush.lbStyle = BS_HATCHED;
    else if(style >= INTERLEAVE_FILL && style <= CLOSE_DOT_FILL)
        logBrush.lbStyle = BS_PATTERN;

    const WORD bitsILF[2] = { 0x80, 0x40 };
    const WORD bitsWDF[8] = { 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    const WORD bitsCDF[4] = { 0x7F, 0xFF, 0xDF, 0xFF };

    switch(style) {
        case EMPTY_FILL:    logBrush.lbStyle = BS_HOLLOW;       break;
        case SOLID_FILL:    logBrush.lbStyle = BS_SOLID;        break;
        case LINE_FILL:     logBrush.lbHatch = HS_HORIZONTAL;   break;
        case STICK_FILL:    logBrush.lbHatch = HS_VERTICAL;     break;
        case HATCH_FILL:    logBrush.lbHatch = HS_CROSS;        break;
        case XHATCH_FILL:   logBrush.lbHatch = HS_DIAGCROSS;    break;
        case LTSLASH_FILL: case SLASH_FILL:     logBrush.lbHatch = HS_BDIAGONAL;    break;
        case BKSLASH_FILL: case LTBKSLASH_FILL: logBrush.lbHatch = HS_FDIAGONAL;    break;
        case INTERLEAVE_FILL:   logBrush.lbHatch = (ULONG_PTR)CreateBitmap(2, 2, 1, 1, bitsILF);    break;
        case WIDE_DOT_FILL:     logBrush.lbHatch = (ULONG_PTR)CreateBitmap(8, 8, 1, 1, bitsWDF);    break;
        case CLOSE_DOT_FILL:    logBrush.lbHatch = (ULONG_PTR)CreateBitmap(4, 4, 1, 1, bitsCDF);    break;
    }
    SYNCHRONIZED(drawMutex, {
        if(brush) DeleteObject(brush);
        brush = CreateBrushIndirect(&logBrush);
        SelectObject(memDC, brush);
        SetBkMode(memDC, transparentBk ? TRANSPARENT : OPAQUE);
    });
}

void RegraphWindow::setColor(int color) {
    mainColor = color;
    SYNCHRONIZED(drawMutex, SetTextColor(memDC, mainColor) );
    recreatePen();
}

void RegraphWindow::setBkColor(int backgroundColor) {
    this->backgroundColor = backgroundColor;
    SYNCHRONIZED(drawMutex, SetBkColor(memDC, backgroundColor) );
    if(backgroundBrush) DeleteObject(backgroundBrush);
    backgroundBrush = CreateSolidBrush(backgroundColor);
}

void Regraph::onWindowDestroyed(int id) {
    for(unsigned int i = 0; i < windowList.size(); i++)
        if(windowList[i].getID() == id) {
            if(windowList.size() > 1) {
                currentWindowID = windowList.back().getID();
                currentWindowIndex = windowList.size() - 1;
            } else currentWindowID = currentWindowIndex = -1;
            windowList.erase(windowList.begin() + i);
        }
}

RegraphWindow* Regraph::findWindowByHWND(HWND hwnd) {
    for(unsigned int i = 0; i < windowList.size(); i++)
        if(windowList[i].getWindowHandle() == hwnd)
            return &windowList[i];
    return NULL;
}

RegraphWindow* Regraph::findWindowByID(int id, int *out_index) {
    for(unsigned int i = 0; i < windowList.size(); i++)
        if(windowList[i].getID() == id) {
            if(out_index) *out_index = i;
            return &windowList[i];
        }
    return NULL;
}

int Regraph::initwindow(int width, int height, const char *title, bool closeflag) {
    if(width <= 0 || height <= 0 || !title)
        return -1;

    int id;
    if(windowList.size() == 0)
        currentWindowID = currentWindowIndex = id = 0;
    else
        id = windowList.back().getID() + 1;

    windowList.push_back(RegraphWindow());
    if(!windowList.back().initialize(id, width, height, title, closeflag, onWindowDestroyed)) {
        windowList.pop_back();
        return -1;
    }
    return id;
}

void Regraph::closegraph(int windowID, bool doExit) {
    if(windowID == ALL_WINDOWS) {
        currentWindowID = currentWindowIndex = -1;
        for(unsigned int i = 0; i < windowList.size(); i++) {
            windowList[i].close();
        }
    } else if(windowID == CURRENT_WINDOW && currentWindowIndex >= 0) {
        currentWindow()->close();
    } else {
        int indexToClose;
        if(RegraphWindow *window = findWindowByID(windowID, &indexToClose)) {
            window->close();
        } else return;
    }
    if(doExit) exit(0);
}
