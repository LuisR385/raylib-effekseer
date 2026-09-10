#include "rayseer.h"

#include <filesystem>
#include <optional>
#include <system_error>
#include <vector>

//NOTE : 
namespace
{
constexpr int kMaxParticleCount = 8000;
constexpr float kEffectHeight = 1.0f;

std::optional<std::filesystem::path> FindFireBall()
{
    namespace fs = std::filesystem;

    std::error_code error;
    std::vector<fs::path> searchRoots;
    searchRoots.emplace_back(fs::current_path(error));
    searchRoots.emplace_back(GetApplicationDirectory());

    // Visual Studio では exe が build/Debug などに置かれるため、
    // カレントディレクトリと exe の場所から数階層上まで探す。
    for (auto root : searchRoots)
    {
        for (int depth = 0; depth < 4 && !root.empty(); ++depth)
        {
            const auto candidate = root / "resource" / "FireBall.efkefc";
            error.clear();
            if (fs::is_regular_file(candidate, error))
            {
                error.clear();
                const auto canonical = fs::weakly_canonical(candidate, error);
                return error ? candidate : canonical;
            }

            const auto parent = root.parent_path();
            if (parent == root)
            {
                break;
            }
            root = parent;
        }
    }

    return std::nullopt;
}

int RunExample()
{
    if (!Rayseer::Initialize(kMaxParticleCount))
    {
        return 1;
    }

    const auto effectPath = FindFireBall();
    if (!effectPath)
    {
        TraceLog(LOG_ERROR, "resource/FireBall.efkefc was not found");
        Rayseer::Shutdown();
        return 1;
    }

    Rayseer::EffectAsset effect = Rayseer::LoadEffect(*effectPath);
    if (!Rayseer::IsEffectLoaded(effect))
    {
        TraceLog(LOG_ERROR, "Failed to load FireBall.efkefc");
        Rayseer::Shutdown();
        return 1;
    }

    Camera3D camera{};
    camera.position = Vector3{8.0f, 6.0f, 10.0f};
    camera.target = Vector3{0.0f, kEffectHeight, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Rayseer::EffectHandle handle = Rayseer::PlayEffect(
        effect,
        Vector3{0.0f, kEffectHeight, 0.0f});

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE) || !Rayseer::IsEffectPlaying(handle))
        {
            Rayseer::StopEffect(handle);
            handle = Rayseer::PlayEffect(
                effect,
                Vector3{0.0f, kEffectHeight, 0.0f});
        }

        Rayseer::Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(Color{18, 20, 26, 255});

        // Rayseer owns the renderer boundary. Do not call this between
        // BeginMode3D() and EndMode3D().
        Rayseer::Draw(camera);

        DrawText(
            "raylib 6.0 + Effekseer",
            20,
            20,
            24,
            RAYWHITE
        );

        DrawText(
            "SPACE: replay FireBall",
            20,
            52,
            18,
            LIGHTGRAY
        );

        DrawFPS(20, 82);

        EndDrawing();
    }

    Rayseer::StopEffect(handle);
    Rayseer::UnloadEffect(effect);
    Rayseer::Shutdown();
    return 0;
}
} // namespace

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "raylib 6.0 + Effekseer");

    // RunExample 内の Effekseer オブジェクトを OpenGL context より先に破棄する。
    const int result = RunExample();

    CloseWindow();
    return result;
}
