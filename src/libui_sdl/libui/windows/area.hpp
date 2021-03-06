// 18 december 2015

// TODOs
// - things look very wrong on initial draw
// - initial scrolling is not set properly
// - should background be inherited from parent control?

struct uiArea {
	uiWindowsControl c;
	HWND hwnd;
	uiAreaHandler *ah;

	int width, height;

	BOOL scrolling;
	int scrollWidth;
	int scrollHeight;
	int hscrollpos;
	int vscrollpos;
	int hwheelCarry;
	int vwheelCarry;

	clickCounter cc;
	BOOL capturing;

	BOOL inside;
	BOOL tracking;

	int bgR, bgG, bgB;

	int openGL;
	uiGLContext* glcontext;

	ID2D1HwndRenderTarget *rt;
};

// areadraw.cpp
extern BOOL areaDoDraw(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
extern void areaDrawOnResize(uiArea *, RECT *);

// areascroll.cpp
extern BOOL areaDoScroll(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
extern void areaScrollOnResize(uiArea *, RECT *);
extern void areaUpdateScroll(uiArea *a);

// areaevents.cpp
extern BOOL areaDoEvents(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);

// areautil.cpp
extern void loadAreaSize(uiArea *a, double *width, double *height);
extern void pixelsToDIP(uiArea *a, double *x, double *y);
extern void dipToPixels(uiArea *a, double *x, double *y);

// gl.cpp
extern uiGLContext* createGLContext(uiArea* a, int vermajor, int verminor);
extern void freeGLContext(uiGLContext* c);
