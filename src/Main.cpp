#include "Engine.h"
#include "Game.h"

int main()
{
  Engine& oEngine = Engine::GetInstance();
  if (oEngine.Init(960, 640, "DGL - PANG"))
  {
    // Game initial configuration
    if (Game::Init())
    {
      // Update time
      double dLastTime = oEngine.Time();
      while (oEngine.IsRunning())
      {
        // Update time and fps
        double dNow = oEngine.Time();
        double dDeltatime = dNow - dLastTime;
        dLastTime = dNow;
        // Process input
        oEngine.ProcessInput();
        // Clear screen
        oEngine.Clear();
        // Update engine
        oEngine.Update(dDeltatime);
        // Render engine
        oEngine.Render();
      }
    }
    // Unload engine
    oEngine.Quit();
    Engine::Destroy();
  }
}