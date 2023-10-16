// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "GameTimer.h"
#include "InputHandler.h"
#include "EntitySystem/EntitySystem.h"
#include "../ScriptSystem/ScriptSystem.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();
    CScriptSystem* scriptSystem = new CScriptSystem();


    EntitySystem* entitySystem = new EntitySystem(renderEngine, inputHandler, scriptSystem);

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            inputHandler->Update();
            entitySystem->Update();
            timer.Tick();

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}

/*
* В цикле while происходит обработка сообщений. Если в очереди сообщений есть сообщения, они обрабатываются 
* с помощью функций PeekMessage, TranslateMessage и DispatchMessage. Если очередь сообщений пуста, 
* то обновляются inputHandler и entitySystem, выполнение хода таймера с помощью функции Tick, и вызывается метод 
* OnEndFrame объекта renderThread для завершения кадра рендеринга. Цикл продолжается, пока не поступит сообщение 
* о закрытии приложения. 
* Наконец, функция возвращает значение msg.wParam в качестве кода завершения приложения.
*/