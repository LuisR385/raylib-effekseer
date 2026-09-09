#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
// windows.h の Rectangle/DrawText/CloseWindow と raylib の衝突を避ける。
#define NOGDI
#define NOUSER
#endif

#include <Effekseer.h>
#include <EffekseerRendererGL.h>
#include <raylib.h>
#include <rlgl.h>

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

void SetEffekseerCamera(const EffekseerRendererGL::RendererRef& renderer, const Camera3D& camera)
{
    const int renderWidth = GetRenderWidth();
    const int renderHeight = GetRenderHeight();
    const float aspect = renderHeight > 0 ? static_cast<float>(renderWidth) / static_cast<float>(renderHeight) : 1.0f;

    renderer->SetProjectionMatrix(
        Effekseer::Matrix44().PerspectiveFovRH_OpenGL(
            camera.fovy * DEG2RAD,
            aspect,
            RL_CULL_DISTANCE_NEAR,
            RL_CULL_DISTANCE_FAR));

    renderer->SetCameraMatrix(
        Effekseer::Matrix44().LookAtRH(
            Effekseer::Vector3D(camera.position.x, camera.position.y, camera.position.z),
            Effekseer::Vector3D(camera.target.x, camera.target.y, camera.target.z),
            Effekseer::Vector3D(camera.up.x, camera.up.y, camera.up.z)));
}

int RunExample()
{
    auto renderer = EffekseerRendererGL::Renderer::Create(
        kMaxParticleCount,
        EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
    if (renderer == nullptr)
    {
        TraceLog(LOG_ERROR, "EffekseerRendererGL initialization failed");
        return 1;
    }

    renderer->SetRestorationOfStatesFlag(true);

    auto manager = Effekseer::Manager::Create(kMaxParticleCount);
    if (manager == nullptr)
    {
        TraceLog(LOG_ERROR, "Effekseer manager initialization failed");
        return 1;
    }

    manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
    manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
    manager->SetRingRenderer(renderer->CreateRingRenderer());
    manager->SetTrackRenderer(renderer->CreateTrackRenderer());
    manager->SetModelRenderer(renderer->CreateModelRenderer());

    manager->SetTextureLoader(renderer->CreateTextureLoader());
    manager->SetModelLoader(renderer->CreateModelLoader());
    manager->SetMaterialLoader(renderer->CreateMaterialLoader());
    manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

    const auto effectPath = FindFireBall();
    if (!effectPath)
    {
        TraceLog(LOG_ERROR, "resource/FireBall.efkefc was not found");
        return 1;
    }

    const std::u16string effectPath16 = effectPath->u16string();
    auto effect = Effekseer::Effect::Create(manager, effectPath16.c_str());
    if (effect == nullptr)
    {
        TraceLog(LOG_ERROR, "Failed to load FireBall.efkefc");
        return 1;
    }

    TraceLog(LOG_INFO, "Loaded effect: %s", effectPath->string().c_str());

    Camera3D camera{};
    camera.position = Vector3{8.0f, 6.0f, 10.0f};
    camera.target = Vector3{0.0f, kEffectHeight, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Effekseer::Handle handle = manager->Play(effect, 0.0f, kEffectHeight, 0.0f);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE) || !manager->Exists(handle))
        {
            if (manager->Exists(handle))
            {
                manager->StopEffect(handle);
            }

            handle = manager->Play(
                effect,
                0.0f,
                kEffectHeight,
                0.0f
            );
        }

        // Effekseer update
        manager->Update(GetFrameTime() * 60.0f);

        BeginDrawing();

        ClearBackground(Color{ 18, 20, 26, 255 });

        BeginMode3D(camera);

        //
        // raylib側が正常か確認
        //
        DrawGrid(10, 1.0f);

        //
        // raylib -> Effekseer
        //
        rlDrawRenderBatchActive();

        SetEffekseerCamera(renderer, camera);

        //
        // Effekseer用
        //
        renderer->ResetRenderState();

        renderer->BeginRendering();
        manager->Draw();
        renderer->EndRendering();

        
        //深度テストの有効化
        rlEnableDepthTest();
        rlEnableDepthMask();

        //
        // Effekseerの後にraylib 3Dを描いてみよう
        //
        DrawCube(
            Vector3{ 0.0f, 1.0f, 0.0f },
            1.0f,
            1.0f,
            1.0f,
            RED
        );

        DrawGrid(10, 1.0f);


        EndMode3D();

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

    manager->StopAllEffects();
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
