#ifndef RAYSEER_H
#define RAYSEER_H

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// Avoid collisions between windows.h and raylib names such as Rectangle,
// DrawText, and CloseWindow.
#ifndef NOGDI
#define NOGDI
#endif
#ifndef NOUSER
#define NOUSER
#endif
#endif

#include <Effekseer.h>
#include <EffekseerRendererGL.h>

#include <raylib.h>
#include <rlgl.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <limits>
#include <string>
#include <vector>

namespace Rayseer
{
    namespace Detail
    {
    inline bool IsUtf8ContinuationByte(unsigned char value) noexcept
    {
    return (value & 0xC0u) == 0x80u;
    }

    inline std::uint32_t NextGeneration(std::uint32_t generation) noexcept
        {
            ++generation;
            if (generation == 0)
            {
                ++generation;
            }
            return generation;
        }

//有限の数値かどうか(-の負数無限の場合はfalseを返す)
inline bool IsFinite(float value) noexcept
{
    return std::isfinite(value);
}

//有限の数値かどうか(-の負数無限の場合はfalseを返す)
inline bool IsFinite(Vector3 value) noexcept
{
    return IsFinite(value.x) && IsFinite(value.y) && IsFinite(value.z);
}

inline float LengthSquared(Vector3 value) noexcept
{
    return value.x * value.x + value.y * value.y + value.z * value.z;
}

//減算処理
inline Vector3 Subtract(Vector3 lhs, Vector3 rhs) noexcept
{
    return Vector3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

//外積
inline Vector3 Cross(Vector3 lhs, Vector3 rhs) noexcept
{
    return Vector3{
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x};
}

inline bool IsUsableCamera(const Camera3D& camera) noexcept
{
    if (!IsFinite(camera.position) || !IsFinite(camera.target) || !IsFinite(camera.up) ||
        !IsFinite(camera.fovy) || camera.fovy <= 0.0f)
    {
        return false;
    }

    const Vector3 view = Subtract(camera.target, camera.position);
    return LengthSquared(view) > 0.000001f &&
           LengthSquared(camera.up) > 0.000001f &&
           LengthSquared(Cross(view, camera.up)) > 0.000001f;
}

inline Effekseer::Matrix44 MakeOrthographicRHOpenGL(float width, float height, float nearPlane, float farPlane)
{
    Effekseer::Matrix44 result;
    result.Indentity();

    result.Values[0][0] = 2.0f / width;
    result.Values[1][1] = 2.0f / height;
    result.Values[2][2] = -2.0f / (farPlane - nearPlane);
    result.Values[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    return result;
}

inline Effekseer::Matrix44 ToEffekseerMatrix(const Matrix& matrix)
{
    Effekseer::Matrix44 result;

    result.Values[0][0] = matrix.m0;
    result.Values[0][1] = matrix.m1;
    result.Values[0][2] = matrix.m2;
    result.Values[0][3] = matrix.m3;

    result.Values[1][0] = matrix.m4;
    result.Values[1][1] = matrix.m5;
    result.Values[1][2] = matrix.m6;
    result.Values[1][3] = matrix.m7;

    result.Values[2][0] = matrix.m8;
    result.Values[2][1] = matrix.m9;
    result.Values[2][2] = matrix.m10;
    result.Values[2][3] = matrix.m11;

    result.Values[3][0] = matrix.m12;
    result.Values[3][1] = matrix.m13;
    result.Values[3][2] = matrix.m14;
    result.Values[3][3] = matrix.m15;
    return result;
}

inline Effekseer::Matrix43 ToEffekseerMatrix43(const Matrix& matrix)
{
    Effekseer::Matrix43 result = { 0 };

    //      raylib
    // 
    //  | m0  m4  m8   m12 |
    //  | m1  m5  m9   m13 |
    //  | m2  m6  m10  m14 |
    //  | 0   0   0    1   |
    //
    // 
    //      effekseer
    //  | m0   m1   m2  |
    //  | m4   m5   m6  |
    //  | m8   m9   m10 |
    //  | m12  m13  m14 |


    //
    //
    //
    //                    raylib            Effekseer Matrix43

    //座標系              右手系             右手系
    //回転                OpenGL系           反時計回り
    //サイズ              4x4               4x3
    //ベクトル規約        列ベクトル的        行ベクトル
    //                    M * V             V * M
    //
    //Translation         最後の列           最後の行
    //                m12,m13,m14       Value[3][0..2](raylibでいうm12,m13,m14)
 
 
 


    result.Value[0][0] = matrix.m0;
    result.Value[0][1] = matrix.m1;
    result.Value[0][2] = matrix.m2;
    
    result.Value[1][0] = matrix.m4;
    result.Value[1][1] = matrix.m5;
    result.Value[1][2] = matrix.m6;

    result.Value[2][0] = matrix.m8;
    result.Value[2][1] = matrix.m9;
    result.Value[2][2] = matrix.m10;

    result.Value[3][0] = matrix.m12;
    result.Value[3][1] = matrix.m13;
    result.Value[3][2] = matrix.m14;
    
    return result;

}

inline Effekseer::Matrix44 MakeScreenProjection(float width, float height)
{
    constexpr float nearPlane = -1000.0f;
    constexpr float farPlane = 1000.0f;

    Effekseer::Matrix44 result;
    result.Indentity();
    result.Values[0][0] = 2.0f / width;
    result.Values[1][1] = -2.0f / height;
    result.Values[2][2] = -2.0f / (farPlane - nearPlane);
    result.Values[3][0] = -1.0f;
    result.Values[3][1] = 1.0f;
    result.Values[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    return result;
}
} // namespace Detail

// Returns an empty string for null, empty, or malformed UTF-8 input.
inline std::u16string Utf8ToUtf16(const char* text)
{
    if (text == nullptr || *text == '\0')
    {
        return {};
    }

    std::u16string result;
    const auto* cursor = reinterpret_cast<const unsigned char*>(text);

    while (*cursor != '\0')
    {
        std::uint32_t codePoint = 0;
        std::size_t byteCount = 0;

        if (cursor[0] <= 0x7Fu)
        {
            codePoint = cursor[0];
            byteCount = 1;
        }
        else if (cursor[0] >= 0xC2u && cursor[0] <= 0xDFu)
        {
            if (cursor[1] == '\0' || !Detail::IsUtf8ContinuationByte(cursor[1]))
            {
                return {};
            }
            codePoint = ((cursor[0] & 0x1Fu) << 6) | (cursor[1] & 0x3Fu);
            byteCount = 2;
        }
        else if (cursor[0] >= 0xE0u && cursor[0] <= 0xEFu)
        {
            if (cursor[1] == '\0' || cursor[2] == '\0' ||
                !Detail::IsUtf8ContinuationByte(cursor[1]) ||
                !Detail::IsUtf8ContinuationByte(cursor[2]))
            {
                return {};
            }
            if ((cursor[0] == 0xE0u && cursor[1] < 0xA0u) ||
                (cursor[0] == 0xEDu && cursor[1] > 0x9Fu))
            {
                return {};
            }
            codePoint = ((cursor[0] & 0x0Fu) << 12) |
                        ((cursor[1] & 0x3Fu) << 6) |
                        (cursor[2] & 0x3Fu);
            byteCount = 3;
        }
        else if (cursor[0] >= 0xF0u && cursor[0] <= 0xF4u)
        {
            if (cursor[1] == '\0' || cursor[2] == '\0' || cursor[3] == '\0' ||
                !Detail::IsUtf8ContinuationByte(cursor[1]) ||
                !Detail::IsUtf8ContinuationByte(cursor[2]) ||
                !Detail::IsUtf8ContinuationByte(cursor[3]))
            {
                return {};
            }
            if ((cursor[0] == 0xF0u && cursor[1] < 0x90u) ||
                (cursor[0] == 0xF4u && cursor[1] > 0x8Fu))
            {
                return {};
            }
            codePoint = ((cursor[0] & 0x07u) << 18) |
                        ((cursor[1] & 0x3Fu) << 12) |
                        ((cursor[2] & 0x3Fu) << 6) |
                        (cursor[3] & 0x3Fu);
            byteCount = 4;
        }
        else
        {
            return {};
        }

        cursor += byteCount;

        if (codePoint <= 0xFFFFu)
        {
            result.push_back(static_cast<char16_t>(codePoint));
        }
        else
        {
            codePoint -= 0x10000u;
            result.push_back(static_cast<char16_t>(0xD800u + (codePoint >> 10)));
            result.push_back(static_cast<char16_t>(0xDC00u + (codePoint & 0x3FFu)));
        }
    }

    return result;
}

// Returns an empty string for null, empty, or malformed UTF-16 input.
inline std::string Utf16ToUtf8(const char16_t* text)
{
    if (text == nullptr || *text == u'\0')
    {
        return {};
    }

    std::string result;
    for (std::size_t index = 0; text[index] != u'\0'; ++index)
    {
        std::uint32_t codePoint = text[index];

        if (codePoint >= 0xD800u && codePoint <= 0xDBFFu)
        {
            const std::uint32_t low = text[index + 1];
            if (low < 0xDC00u || low > 0xDFFFu)
            {
                return {};
            }
            codePoint = 0x10000u + ((codePoint - 0xD800u) << 10) + (low - 0xDC00u);
            ++index;
        }
        else if (codePoint >= 0xDC00u && codePoint <= 0xDFFFu)
        {
            return {};
        }

        if (codePoint <= 0x7Fu)
        {
            result.push_back(static_cast<char>(codePoint));
        }
        else if (codePoint <= 0x7FFu)
        {
            result.push_back(static_cast<char>(0xC0u | (codePoint >> 6)));
            result.push_back(static_cast<char>(0x80u | (codePoint & 0x3Fu)));
        }
        else if (codePoint <= 0xFFFFu)
        {
            result.push_back(static_cast<char>(0xE0u | (codePoint >> 12)));
            result.push_back(static_cast<char>(0x80u | ((codePoint >> 6) & 0x3Fu)));
            result.push_back(static_cast<char>(0x80u | (codePoint & 0x3Fu)));
        }
        else
        {
            result.push_back(static_cast<char>(0xF0u | (codePoint >> 18)));
            result.push_back(static_cast<char>(0x80u | ((codePoint >> 12) & 0x3Fu)));
            result.push_back(static_cast<char>(0x80u | ((codePoint >> 6) & 0x3Fu)));
            result.push_back(static_cast<char>(0x80u | (codePoint & 0x3Fu)));
        }
    }

    return result;
}

class RaySeerContext;

struct EffectHandle
{
    std::int32_t value = -1;

    bool IsValid() const noexcept
    {
        return value >= 0 && owner_ != nullptr;
    }

    explicit operator bool() const noexcept
    {
        return IsValid();
    }

private:
    const RaySeerContext* owner_ = nullptr;
    std::uint32_t sessionGeneration_ = 0;

    friend class RaySeerContext;
};

class RaySeerEffectAsset
{
public:
    using RSEffectAsset = RaySeerEffectAsset;

    RaySeerEffectAsset() = default;

    // This checks whether the value contains an asset token. Use
    // IsEffectLoaded() when the asset may already have been unloaded.
    bool IsValid() const noexcept
    {
        return owner_ != nullptr && slot_ != InvalidSlot && slotGeneration_ != 0;
    }

    explicit operator bool() const noexcept
    {
        return IsValid();
    }

private:
    static constexpr std::size_t InvalidSlot = std::numeric_limits<std::size_t>::max();

    const RaySeerContext* owner_ = nullptr;
    std::size_t slot_ = InvalidSlot;
    std::uint32_t slotGeneration_ = 0;

    friend class RaySeerContext;
};

using EffectAsset = RaySeerEffectAsset;
using Effect = RaySeerEffectAsset;
using RSEffectAsset = RaySeerEffectAsset;

class RaySeerContext
{
public:
    RaySeerContext() = default;
    RaySeerContext(const RaySeerContext&) = delete;
    RaySeerContext& operator=(const RaySeerContext&) = delete;
    RaySeerContext(RaySeerContext&&) = delete;
    RaySeerContext& operator=(RaySeerContext&&) = delete;

    bool Initialize(int maxParticleCount = 8000)
    {
        if (IsReady())
        {
            return true;
        }
        if (maxParticleCount <= 0)
        {
            TraceLog(LOG_ERROR, "Rayseer maxParticleCount must be greater than zero");
            return false;
        }

        auto renderer = EffekseerRendererGL::Renderer::Create(
            maxParticleCount,
            EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
        if (renderer == nullptr)
        {
            TraceLog(LOG_ERROR, "EffekseerRendererGL initialization failed");
            return false;
        }

        auto manager = Effekseer::Manager::Create(maxParticleCount);
        if (manager == nullptr)
        {
            TraceLog(LOG_ERROR, "Effekseer manager initialization failed");
            return false;
        }

        //state状態を復元する設定をONにする(raylibのAPIとの齟齬を無くすため)
        renderer->SetRestorationOfStatesFlag(true);

        manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
        manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
        manager->SetRingRenderer(renderer->CreateRingRenderer());
        manager->SetTrackRenderer(renderer->CreateTrackRenderer());
        manager->SetModelRenderer(renderer->CreateModelRenderer());

        manager->SetTextureLoader(renderer->CreateTextureLoader());
        manager->SetModelLoader(renderer->CreateModelLoader());
        manager->SetMaterialLoader(renderer->CreateMaterialLoader());
        manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

        m_renderer = renderer;
        m_manager = manager;
        m_sessionGeneration = Detail::NextGeneration(m_sessionGeneration);
        m_isInitialized = true;
        return true;
    }

    void Shutdown()
    {
        if (m_manager != nullptr)
        {
            m_manager->StopAllEffects();
        }

        for (auto& slot : m_effectSlots)
        {
            slot.effect.Reset();
            slot.generation = Detail::NextGeneration(slot.generation);
        }

        // Release in this order while the raylib OpenGL context is still alive.
        //raylibのOpneGLContextはまだ生きているので解放処理をする
        m_manager.Reset();
        m_renderer.Reset();
        m_isInitialized = false;
        m_sessionGeneration = Detail::NextGeneration(m_sessionGeneration);
    }

    // Kept as a source-compatible spelling for early Rayseer users.
    void ShutDown()
    {
        Shutdown();
    }

    bool IsReady() const noexcept
    {
        if (m_isInitialized && m_renderer != nullptr && m_manager != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    explicit operator bool() const noexcept
    {
        return IsReady();
    }

    EffectAsset LoadEffect(const char* utf8Path)
    {
        if (!IsReady() || utf8Path == nullptr || *utf8Path == '\0')
        {
            return {};
        }

        const std::u16string utf16Path = Utf8ToUtf16(utf8Path);
        if (utf16Path.empty())
        {
            TraceLog(LOG_ERROR, "Rayseer effect path is not valid UTF-8");
            return {};
        }
        return LoadEffectUtf16(utf16Path);
    }

    EffectAsset LoadEffect(const std::filesystem::path& path)
    {
        if (!IsReady() || path.empty())
        {
            return {};
        }

        try
        {
            return LoadEffectUtf16(path.u16string());
        }
        catch (const std::filesystem::filesystem_error&)
        {
            TraceLog(LOG_ERROR, "Rayseer failed to convert the effect path to UTF-16");
            return {};
        }
    }

    bool UnloadEffect(EffectAsset& asset)
    {
        EffectSlot* slot = FindEffectSlot(asset);
        if (slot == nullptr)
        {
            return false;
        }

        slot->effect.Reset();
        slot->generation = Detail::NextGeneration(slot->generation);
        asset = {};
        return true;
    }

    //エフェクトが読み込まれているかどうか
    bool IsEffectLoaded(const EffectAsset& asset) const noexcept
    {
        return FindEffectSlot(asset) != nullptr;
    }

    //エフェクト再生
    EffectHandle PlayEffect(const EffectAsset& asset, Vector3 position = Vector3{0.0f, 0.0f, 0.0f})
    {
        if (!Detail::IsFinite(position))
        {
            return {};
        }

        const EffectSlot* slot = FindEffectSlot(asset);
        if (slot == nullptr)
        {
            return {};
        }

        const Effekseer::Handle nativeHandle =
            m_manager->Play(slot->effect, position.x, position.y, position.z);
        if (nativeHandle < 0)
        {
            return {};
        }

        EffectHandle handle;
        handle.value = static_cast<std::int32_t>(nativeHandle);
        handle.owner_ = this;
        handle.sessionGeneration_ = m_sessionGeneration;
        return handle;
    }

    //エフェクトの再生を停止させる
    bool StopEffect(EffectHandle handle)
    {
        if (!IsEffectPlaying(handle))
        {
            return false;
        }
        m_manager->StopEffect(static_cast<Effekseer::Handle>(handle.value));
        return true;
    }

    void StopAllEffects()
    {
        if (m_manager != nullptr)
        {
            m_manager->StopAllEffects();
        }
    }

    bool IsEffectPlaying(EffectHandle handle) const
    {
        return Owns(handle) &&
               m_manager->Exists(static_cast<Effekseer::Handle>(handle.value));
    }

    bool SetEffectPosition(EffectHandle handle, Vector3 position)
    {
        if (!IsEffectPlaying(handle) || !Detail::IsFinite(position))
        {
            return false;
        }
        m_manager->SetLocation(handle.value, position.x, position.y, position.z);
        return true;
    }

    // raylib's public rotation angles are generally expressed in degrees.
    // Effekseer uses radians, so the conversion stays inside Rayseer.
    bool SetEffectRotation(EffectHandle handle, Vector3 rotationDegrees)
    {
        if (!IsEffectPlaying(handle) || !Detail::IsFinite(rotationDegrees))
        {
            return false;
        }
        m_manager->SetRotation(
            handle.value,
            rotationDegrees.x * DEG2RAD,
            rotationDegrees.y * DEG2RAD,
            rotationDegrees.z * DEG2RAD);
        return true;
    }

    bool SetEffectScale(EffectHandle handle, Vector3 scale)
    {
        if (!IsEffectPlaying(handle) || !Detail::IsFinite(scale))
        {
            return false;
        }
        m_manager->SetScale(handle.value, scale.x, scale.y, scale.z);
        return true;
    }
    
    //エフェクトの再生速度を設定する
    bool SetEffectSpeed(EffectHandle handle, float speed)
    {
        if (!IsEffectPlaying(handle) || !Detail::IsFinite(speed))
        {
            return false;
        }
        m_manager->SetSpeed(handle.value, speed);
        return true;
    }

    //更新処理
    void Update(float deltaTimeSeconds)
    {
        if (!IsReady() || !Detail::IsFinite(deltaTimeSeconds) || deltaTimeSeconds < 0.0f)
        {
            return;
        }
        //effekseerの内部は基本60FPSが固定なので、一旦マジックナンバー
        m_manager->Update(deltaTimeSeconds * 60.0f);
    }

    //カメラをセットする(低レベルAPI)
    bool SetEffekseerCamera(const Camera3D& camera)
    {
        if (!IsReady() || !Detail::IsUsableCamera(camera))
        {
            return false;
        }

        const int renderWidth = GetRenderWidth();
        const int renderHeight = GetRenderHeight();
        if (renderWidth <= 0 || renderHeight <= 0)
        {
            return false;
        }

        const float aspect = static_cast<float>(renderWidth) / static_cast<float>(renderHeight);
        Effekseer::Matrix44 projection;
        if (camera.projection == CAMERA_ORTHOGRAPHIC)
        {
            projection = Detail::MakeOrthographicRHOpenGL(
                camera.fovy * aspect,
                camera.fovy,
                RL_CULL_DISTANCE_NEAR,
                RL_CULL_DISTANCE_FAR);
        }
        else
        {
            projection.PerspectiveFovRH_OpenGL(
                camera.fovy * DEG2RAD,
                aspect,
                RL_CULL_DISTANCE_NEAR,
                RL_CULL_DISTANCE_FAR);
        }

        Effekseer::Matrix44 view;
        view.LookAtRH(
            Effekseer::Vector3D(camera.position.x, camera.position.y, camera.position.z),
            Effekseer::Vector3D(camera.target.x, camera.target.y, camera.target.z),
            Effekseer::Vector3D(camera.up.x, camera.up.y, camera.up.z));

        m_renderer->SetProjectionMatrix(projection);
        m_renderer->SetCameraMatrix(view);
        return true;
    }

    // priminalyy low-level Camera2D mapping .
    bool SetEffekseerCamera(const Camera2D& camera)
    {
        if (!IsReady() || !Detail::IsFinite(camera.offset.x) || !Detail::IsFinite(camera.offset.y) ||
            !Detail::IsFinite(camera.target.x) || !Detail::IsFinite(camera.target.y) ||
            !Detail::IsFinite(camera.rotation) || !Detail::IsFinite(camera.zoom) || camera.zoom == 0.0f)
        {
            return false;
        }

        const int renderWidth = GetRenderWidth();
        const int renderHeight = GetRenderHeight();
        if (renderWidth <= 0 || renderHeight <= 0)
        {
            return false;
        }

        const Effekseer::Matrix44 view = Detail::ToEffekseerMatrix(GetCameraMatrix2D(camera));
        const Effekseer::Matrix44 projection = Detail::MakeScreenProjection(
            static_cast<float>(renderWidth),
            static_cast<float>(renderHeight));

        m_renderer->SetCameraMatrix(view);
        m_renderer->SetProjectionMatrix(projection);
        m_renderer->SetCameraParameter(
            Effekseer::Vector3D{0.0f, 0.0f, 1.0f},
            Effekseer::Vector3D{0.0f, 0.0f, 0.0f});
        return true;
    }

    bool SetEffectMatrix(
        EffectHandle handle,
        const Matrix& matrix)
    {
        if (!IsEffectPlaying(handle))
        {
            return false;
        }

        m_manager->SetMatrix(
            static_cast<Effekseer::Handle>(handle.value),
            Detail::ToEffekseerMatrix43(matrix));


        return true;
    }

    bool SetEffectTarget(
        EffectHandle handle,
        Vector3 target)
    {
        //有効値/またはエフェクトが再生中でないか
        if (!IsEffectPlaying(handle) || !Detail::IsFinite(target))
        {
            return false;
        }

        //effekseer側のSetTargetLocationを使用してtargetを直接代入
        m_manager->SetTargetLocation(
            static_cast<Effekseer::Handle>(handle.value),
            target.x,
            target.y,
            target.z);

        return true;
    }

    bool SetEffectVisible(
        EffectHandle handle,
        bool visible)
    {
        if (IsEffectPlaying(handle))
        {
            return false;
        }
        
        m_manager->SetShown(
            static_cast<Effekseer::Handle>(handle.value), 
            visible);


        return true;
    }

    bool SetEffectPaused(
        EffectHandle handle,
        bool paused)
    {
        if (!IsEffectPlaying(handle))
        {
            return false;
        }

        m_manager->SetPaused(
            static_cast<Effekseer::Handle>(handle.value), 
            paused);

        return true;
    }

    // Call outside BeginMode3D()/EndMode3D(). Raylib geometry drawn before this
    // remains in the same depth buffer, while the two renderers keep a clear state boundary.
    //BeginMode3D() / EndMode3D()が終わった後に呼んでください。
    //Example : 
    // int main()
    // while(mainloop)
    // BeginMode3D();
    // //something Draw raylib api.
    // EndMode3D();
    // Rayseer::Draw(camera);
    bool Draw(const Camera3D& camera)
    {
        if (!IsReady())
        {
            return false;
        }

        rlDrawRenderBatchActive();
        if (!SetEffekseerCamera(camera))
        {
            return false;
        }

        // BeginRendering already resets Effekseer's internal render-state cache.
        // Calling ResetRenderState before it would corrupt the state snapshot that
        // EndRendering restores for raylib.
        if (!m_renderer->BeginRendering())
        {
            return false;
        }
        m_manager->Draw();
        return m_renderer->EndRendering();
    }

    EffekseerRendererGL::RendererRef GetNativeRendererRef() const noexcept
    {
        return m_renderer;
    }

    Effekseer::ManagerRef GetNativeManagerRef() const noexcept
    {
        return m_manager;
    }

private:
    struct EffectSlot
    {
        Effekseer::EffectRef effect;
        std::uint32_t generation = 1;
    };

    EffectAsset LoadEffectUtf16(const std::u16string& path)
    {
        if (!IsReady() || path.empty())
        {
            return {};
        }

        Effekseer::EffectRef effect = Effekseer::Effect::Create(m_manager, path.c_str());
        if (effect == nullptr)
        {
            TraceLog(LOG_ERROR, "Rayseer failed to load an effect");
            return {};
        }

        std::size_t slotIndex = 0;
        while (slotIndex < m_effectSlots.size() && m_effectSlots[slotIndex].effect != nullptr)
        {
            ++slotIndex;
        }
        if (slotIndex == m_effectSlots.size())
        {
            m_effectSlots.emplace_back();
        }

        EffectSlot& slot = m_effectSlots[slotIndex];
        slot.effect = effect;

        EffectAsset asset;
        asset.owner_ = this;
        asset.slot_ = slotIndex;
        asset.slotGeneration_ = slot.generation;
        return asset;
    }

    EffectSlot* FindEffectSlot(const EffectAsset& asset) noexcept
    {
        if (!IsReady() || asset.owner_ != this || asset.slot_ >= m_effectSlots.size())
        {
            return nullptr;
        }

        EffectSlot& slot = m_effectSlots[asset.slot_];
        if (slot.generation != asset.slotGeneration_ || slot.effect == nullptr)
        {
            return nullptr;
        }
        return &slot;
    }

    const EffectSlot* FindEffectSlot(const EffectAsset& asset) const noexcept
    {
        if (!IsReady() || asset.owner_ != this || asset.slot_ >= m_effectSlots.size())
        {
            return nullptr;
        }

        const EffectSlot& slot = m_effectSlots[asset.slot_];
        if (slot.generation != asset.slotGeneration_ || slot.effect == nullptr)
        {
            return nullptr;
        }
        return &slot;
    }

    bool Owns(EffectHandle handle) const noexcept
    {
        return IsReady() && handle.IsValid() && handle.owner_ == this &&
               handle.sessionGeneration_ == m_sessionGeneration;
    }

    // Declaration order ensures effect assets, manager, then renderer are released.
    EffekseerRendererGL::RendererRef m_renderer;
    Effekseer::ManagerRef m_manager;
    std::vector<EffectSlot> m_effectSlots;
    std::uint32_t m_sessionGeneration = 0;
    bool m_isInitialized = false;
};


struct EffectTransform
{
    Vector3 position = { 0.0f,0.0f,0.0f };
    Vector3 rotation = { 0.0f,0.0f,0.0f };
    Vector3 scale = { 1.0f,1.0f,1.0f };
};

// Simple API shared context. This is intentionally a C++17 inline global,
// not a Singleton and not a function-local static.
// シングルトンにしなかったのはraylib起動している間はずっと生きているし
// 複数持たせることができることからという利点をもたらせるためです。
inline RaySeerContext g_context;

//初期化
inline bool Initialize(int maxParticleCount = 8000)
{
    return g_context.Initialize(maxParticleCount);
}

//release
inline void Shutdown()
{
    g_context.Shutdown();
}

//初期化(本体のみ使用したい場合はこれを使用する)
inline bool InitializeRaySeer(int maxParticleCount = 8000)
{
    return Initialize(maxParticleCount);
}

inline void ShutdownRaySeer()
{
    Shutdown();
}

inline EffectAsset LoadEffect(const char* utf8Path)
{
    return g_context.LoadEffect(utf8Path);
}

inline EffectAsset LoadEffect(const std::filesystem::path& path)
{
    return g_context.LoadEffect(path);
}

inline bool UnloadEffect(EffectAsset& asset)
{
    return g_context.UnloadEffect(asset);
}

inline bool IsEffectLoaded(const EffectAsset& asset)
{
    return g_context.IsEffectLoaded(asset);
}

inline EffectHandle PlayEffect(const EffectAsset& asset, Vector3 position = Vector3{0.0f, 0.0f, 0.0f})
{
    return g_context.PlayEffect(asset, position);
}

inline bool StopEffect(EffectHandle handle)
{
    return g_context.StopEffect(handle);
}

inline void StopAllEffects()
{
    g_context.StopAllEffects();
}

inline bool IsEffectPlaying(EffectHandle handle)
{
    return g_context.IsEffectPlaying(handle);
}

inline bool SetEffectPosition(EffectHandle handle, Vector3 position)
{
    return g_context.SetEffectPosition(handle, position);
}

inline bool SetEffectRotation(EffectHandle handle, Vector3 rotationDegrees)
{
    return g_context.SetEffectRotation(handle, rotationDegrees);
}

inline bool SetEffectScale(EffectHandle handle, Vector3 scale)
{
    return g_context.SetEffectScale(handle, scale);
}

inline bool SetEffectSpeed(EffectHandle handle, float speed)
{
    return g_context.SetEffectSpeed(handle, speed);
}

inline void Update(float deltaTimeSeconds)
{
    g_context.Update(deltaTimeSeconds);
}

inline bool Draw(const Camera3D& camera)
{
    return g_context.Draw(camera);
}

inline bool SetRayseerCamera3D(const Camera3D& camera)
{
    return g_context.SetEffekseerCamera(camera);
}

inline bool SetRayseerCamera3D(const Camera3D& camera, RaySeerContext& context)
{
    return context.SetEffekseerCamera(camera);
}

inline bool SetRayseerCamera2D(const Camera2D& camera)
{
    return g_context.SetEffekseerCamera(camera);
}

// No explicit resize operation is required. Draw() reads raylib's current
// render dimensions every frame. Kept as a compatibility no-op.
inline void Resize() noexcept
{
}

EffectHandle PlayEffect(
    const EffectAsset& asset,
    const EffectTransform& transform = {})
{
    EffectHandle handle = g_context.PlayEffect(asset, transform.position);

    if (!handle)
    {
        return {};
    }

    //if (!Rayseer::SetEffectTransform(handle, transform))
    //{
    //    StopEffect(handle);
    //    return {};
    //}

    return handle;
}

bool SetEffectTransform(
    EffectHandle handle,
    const EffectTransform& transform)
{

    //TODO : 全体的なTransform型にする


    if (!SetEffectPosition(handle, transform.position))
    {
        return false;
    }

    if (!SetEffectRotation(handle, transform.rotation))
    {
        return false;
    }

    if (!SetEffectScale(handle, transform.scale))
    {
        return false;
    }

    return true;



}

bool SetEffectMatrix(
    EffectHandle handle,
    const Matrix& matrix)
{
    return g_context.SetEffectMatrix(handle, matrix);
}

bool SetEffectTarget(
    EffectHandle handle,
    Vector3 target)
{
    return g_context.SetEffectTarget(handle,target);
}

//dxlibのAPIをエフェクト自体の色合いを変化させることもできるようにしたいり、便利なAPIを参考にしてみる

bool SetEffectColor(
    EffectHandle handle,
    Color color)
{
    return false;
}

bool SetEffectPaused(
    EffectHandle handle,
    bool paused)
{
    return g_context.SetEffectPaused(handle,paused);
}

bool SetEffectVisible(
    EffectHandle handle,
    bool visible)
{
    return g_context.SetEffectVisible(handle, visible);
}

bool SetEffectDynamicInput(
    EffectHandle handle,
    int index,
    float value)
{
    return false;
}

bool SendEffectTrigger(
    EffectHandle handle,
    int index)
{
    return false;
}

} // namespace Rayseer

#endif // RAYSEER_H
