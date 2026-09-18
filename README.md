# raylib-effekseer

> [!IMPORTANT]
> raylib-effekseer is a bridge library for using **Effekseer with raylib**.
>
> Requirements:
> - C++17 or later
> - [raylib v6.0 or later](https://github.com/raysan5/raylib)
> - [Effekseer v1.80.6 or later](https://effekseer.github.io/en/index.html)
> - [EffekseerRendererGL](https://effekseer.github.io/en/download.html)


## Example

![Example GIF](docs/raylib-effekseer-demo.gif)

## Example Code

> [!IMPORTANT]
> Rayseer::Draw() should be called outside BeginMode3D() / EndMode3D().

```cpp
#include "rayseer.h"

#include "raylib.h" //もし必要なら 

int main()
{
    InitWindow(1280, 720, "Rayseer Example");

    if (!Rayseer::Initialize())
    {
        CloseWindow();
        return 1;
    }

    Rayseer::EffectAsset effect =
        Rayseer::LoadEffect("resource/FireBall.efkefc");

    if (!Rayseer::IsEffectLoaded(effect))
    {
        Rayseer::Shutdown();
        CloseWindow();
        return 1;
    }

    Camera3D camera{};
    camera.position = { 8.0f, 6.0f, 10.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Rayseer::PlayEffect(effect, { 0.0f, 1.0f, 0.0f });

    while (!WindowShouldClose())
    {
        Rayseer::Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);

        Rayseer::Draw(camera);

        EndDrawing();
    }

    Rayseer::UnloadEffect(effect);
    Rayseer::Shutdown();

    CloseWindow();
    return 0;
}
```