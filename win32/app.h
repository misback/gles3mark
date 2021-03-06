/**
  *  gles3mark v1.0
  *
  *  \date   2014-05-28
  *  \author Tomas Kimer <xkimer00@stud.fit.vutbr.cz>
  */

#pragma once

#include <string>
#include <stdexcept>

#include "baseapp.h"

const std::string DLLPATH("gles3mark.dll");

/**
 * \brief Benchmark windows app.
 */
class App : public BaseApp {

    /**
     * \brief DLL Imported functions.
     */
    class DLL {
        using DLLPreInitT   = void(*)(                  );
        using DLLInitT      = bool(*)(HWND              );   // typedef void(*DLLInitT  )(HWND    );
        using DLLResizeT    = void(*)(int, int          );   // typedef void(*DLLResizeT)(int, int);
        using DLLStepT      = bool(*)(                  );   // typedef bool(*DLLStepT  )(        );
        using DLLKeyDownT   = void(*)(int               );
        using DLLKeyUpT     = void(*)(int               );
        using DLLMouseMoveT = void(*)(int, int, int, int);

        HINSTANCE   dllHandle;
    public:
        DLLPreInitT   DllPreInit;
        DLLInitT      DllInit;
        DLLResizeT    DllResize;
        DLLStepT      DllStep;
        DLLKeyDownT   DllKeyDown;
        DLLKeyUpT     DllKeyUp;
        DLLMouseMoveT DllMouseMove;

        DLL() : dllHandle(nullptr) {}
        void Init(const std::string& path);
        void Free();
    } dll;

    virtual void    OnStartup()            override;
    virtual void    OnQuit(int code = 0)   override;
    virtual bool    OnIdle()               override;
    virtual void    OnResize(int w, int h) override;
    virtual void    OnKeyDown(int key)     override;
    virtual void    OnKeyUp(int key)       override;
    virtual void    OnMouseMove(int x, int y, int dx, int dy) override;

public:
    App(HINSTANCE hInstance, LPSTR cmdLine)
        : BaseApp(hInstance, cmdLine) {}    
};