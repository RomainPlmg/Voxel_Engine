//
// Created by Romain on 20/12/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

class Window;
class Renderer;
class GUI;
class Event;

class Application {
   public:
    /* Destructor */
    ~Application() = default;

    /* Delete copy constructor and affectation operator */
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;

    void Init();
    void Run();

    void OnEvent(const Event &event);

    /* Getters */
    std::shared_ptr<Window> GetWindow() const { return m_Window; }
    std::shared_ptr<Renderer> GetRenderer() const { return m_Renderer; }
    bool IsPaused() const { return m_PauseMode; }
    static Application *GetInstance();

   private:
    Application();

    std::shared_ptr<Window> m_Window;
    std::shared_ptr<Renderer> m_Renderer;
    std::shared_ptr<GUI> m_GUI;
    bool m_PauseMode;

    static Application *m_Instance;
};

#endif  // APPLICATION_H
