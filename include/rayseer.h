
//NOTE : collisiion detection MIN MAX

#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
// windows.h の Rectangle/DrawText/CloseWindow と raylib の衝突を避ける。
#define NOGDI
#define NOUSER
#endif

//effekseer
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

//raylib
#include <raylib.h>
#include <rlgl.h>

//STL
#include <filesystem>
#include <optional>
#include <system_error>
#include <vector>

#include <string>
#include <cstdint>

#define RAYSEER_API

//NOTE : this repo file is single header




#ifndef RAYSEER_H
#define RAYSEER_H



//NOTE  : maybe change to namespace name...
namespace Rayseer
{


	inline std::u16string Utf8ToUtf16(const char* text)
	{
		if (text == nullptr)
			return {};

		std::u16string result;

		const unsigned char* p =
			reinterpret_cast<const unsigned char*>(text);

		while (*p != '\0')
		{
			uint32_t cp = 0;

			if (*p < 0x80)
			{
				cp = *p++;
			}
			else if ((*p & 0xE0) == 0xC0)
			{
				if (p[1] == 0)
					return {};

				cp =
					((p[0] & 0x1F) << 6) |
					(p[1] & 0x3F);

				p += 2;
			}
			else if ((*p & 0xF0) == 0xE0)
			{
				if (p[1] == 0 || p[2] == 0)
					return {};

				cp =
					((p[0] & 0x0F) << 12) |
					((p[1] & 0x3F) << 6) |
					(p[2] & 0x3F);

				p += 3;
			}
			else if ((*p & 0xF8) == 0xF0)
			{
				if (p[1] == 0 ||
					p[2] == 0 ||
					p[3] == 0)
				{
					return {};
				}

				cp =
					((p[0] & 0x07) << 18) |
					((p[1] & 0x3F) << 12) |
					((p[2] & 0x3F) << 6) |
					(p[3] & 0x3F);

				p += 4;
			}
			else
			{
				return {};
			}

			// UTF-16 BMP
			if (cp <= 0xFFFF)
			{
				// surrogate領域そのものは不正
				if (cp >= 0xD800 && cp <= 0xDFFF)
					return {};

				result.push_back(
					static_cast<char16_t>(cp)
				);
			}
			// surrogate pair
			else if (cp <= 0x10FFFF)
			{
				cp -= 0x10000;

				result.push_back(
					static_cast<char16_t>(
						0xD800 + (cp >> 10)
						)
				);

				result.push_back(
					static_cast<char16_t>(
						0xDC00 + (cp & 0x3FF)
						)
				);
			}
			else
			{
				return {};
			}
		}
		return result;
	}




	//TODO : change place define to detail namespace
	//for effekseer->raylib encoding
	inline std::string Utf16ToUtf8(const char16_t* text)
	{
		if (text == nullptr)
			return {};

		std::vector<int> codepoints;

		for (std::size_t i = 0; text[i] != u'\0'; ++i)
		{
			uint32_t cp = text[i];

			// UTF-16 surrogate pair
			if (cp >= 0xD800 && cp <= 0xDBFF)
			{
				const uint32_t low = text[i + 1];

				if (low >= 0xDC00 && low <= 0xDFFF)
				{
					cp =
						0x10000 +
						((cp - 0xD800) << 10) +
						(low - 0xDC00);

					++i;
				}
			}

			codepoints.push_back(static_cast<int>(cp));
		}

		char* utf8 = LoadUTF8(
			codepoints.data(),
			static_cast<int>(codepoints.size())
		);

		//check
		if (utf8 == nullptr)
			return {};

		std::string result = utf8;

		UnloadUTF8(utf8);

		return result;
	}




	//define class
	class RaySeerContext;
	class RaySeerEffectAsset;
	class RaySeerEffectInstance;

	//define enum class
	enum class OPENGLVERSION;

	//define struct
	struct EffectHandle;
	struct State;





	class RaySeerContext
	{
	public:
		bool Initialize(int kMaxParticleCount = 8000)
		{
			//TODO : thingking syntax move Init
			int kMaxParticleCount_ = kMaxParticleCount;



			m_renderer = EffekseerRendererGL::Renderer::Create(
				kMaxParticleCount,
				EffekseerRendererGL::OpenGLDeviceType::OpenGL3); //TODO : user would like wanna change opengl version...

			if (m_renderer == nullptr)
			{
				TraceLog(LOG_ERROR, "EffekseerRendererGL initialization failed");
				IsInitialize = false;
				return false;
			}

			m_renderer->SetRestorationOfStatesFlag(true);

			m_manager = Effekseer::Manager::Create(kMaxParticleCount);
			if (m_manager == nullptr)
			{
				TraceLog(LOG_ERROR, "Effekseer manager initialization failed");
				IsInitialize = false;
				return false;
			}


			//Set Effekseer Renderers
			m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
			m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
			m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
			m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
			m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

			//Set Effekseer Loaders
			m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
			m_manager->SetModelLoader(m_renderer->CreateModelLoader());
			m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
			m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

			IsInitialize = true;

			return true;
		}
		void ShutDown()
		{
			m_manager->StopAllEffects();
		}


		//lifecycle
		void Update(float dt)
		{
			m_manager->Update(dt/*GetFrameTime() * 60.0f*/);
		}


		inline void SetEffekseerCamera(const Camera3D& camera)const
		{
			const int renderWidth = GetRenderWidth();
			const int renderHeight = GetRenderHeight();
			const float aspect = renderHeight > 0 ? static_cast<float>(renderWidth) / static_cast<float>(renderHeight) : 1.0f;

			m_renderer->SetProjectionMatrix(
				Effekseer::Matrix44().PerspectiveFovRH_OpenGL(
					camera.fovy * DEG2RAD,
					aspect,
					RL_CULL_DISTANCE_NEAR,
					RL_CULL_DISTANCE_FAR));

			m_renderer->SetCameraMatrix(
				Effekseer::Matrix44().LookAtRH(
					Effekseer::Vector3D(camera.position.x, camera.position.y, camera.position.z),
					Effekseer::Vector3D(camera.target.x, camera.target.y, camera.target.z),
					Effekseer::Vector3D(camera.up.x, camera.up.y, camera.up.z)));
		}


		void Draw(const Camera3D& camera) const
		{
			rlDrawRenderBatchActive();
			SetEffekseerCamera(camera);
			m_renderer->ResetRenderState();
			m_renderer->BeginRendering();
			m_manager->Draw();
			m_renderer->EndRendering();
			//深度テストの有効化にしないとおかしくなる(最大化などのウィンドウリサイズ時)
			rlEnableDepthTest();
			rlEnableDepthMask();

		}
		bool Exits(); //TODO : handleぶちこむ

		void StopEffect(); //TODO : handleぶちこむ
		void Play();

		//TODO : change to place this API function. EffectInstance API
		void SetPosition(Vector3 pos);
		void SetRotation(Vector3 rot);
		void SetScale(Vector3 scale);




		EffekseerRendererGL::RendererRef GetNativeRendererRef() { return m_renderer; }
		Effekseer::ManagerRef GetNativeManagerRef() { return m_manager; }


		//helper
		//TODO : 今のところ初期化しているかどうかのチェックのみ
		explicit operator bool() const
		{
			return IsInitialize;
		}

	private:
		EffekseerRendererGL::RendererRef m_renderer;
		Effekseer::ManagerRef			 m_manager;
		bool IsInitialize = false;

	};






	RaySeerContext g_context;

	//TODO : バージョンを選択できるようにする
	/*enum class OPENGLVERSION : uint8_t
	{

	};*/

	struct EffectHandle
	{
	public:

		bool IsValid() const 
		{
			return m_isValid;
		}

		bool IsPlaying(const Effekseer::ManagerRef& manager) const
		{
			if (!IsValid() || !manager) { return false; }
			return manager->Exists(m_isValid);
		}

		//utf8限定
		bool Load(const char* path)
		{
			if (!path) {
				return false;
			}

			std::u16string u16path = Utf8ToUtf16(path);

			if (u16path.empty())
				return false;

			auto manager =
				g_context.GetNativeManagerRef();

			if (!manager)
				return false;

			m_effect =
				Effekseer::Effect::Create(
					manager,
					u16path.c_str()
				);


			//これと同じ意味 - > m_isValid = (m_effect != nullptr);
			if (m_effect == nullptr)
			{
				m_isValid = false;
			}
			else {
				m_isValid = true;
			}


			return true;
		}

		//Ideas? for operator bool helper...
		explicit operator bool() const
		{
			return IsValid();
		}


	private:
		Effekseer::EffectRef m_effect; //effectHandle(ref) Value
		bool m_isValid = false;


	};


	class RaySeerEffectAsset
	{
	public:
		RaySeerEffectAsset() = default;
		~RaySeerEffectAsset() = default;

		RaySeerEffectAsset(const char* path)
		{
			Load(path);
		}

		using RSEffectAsset = RaySeerEffectAsset;

		
		bool Load(const char* path)
		{

			if (!path) { return false; }
			
			//TODO : utf16->utf8 encoding.
			//TODO : Create Effect

			//when not succeuss return false.
			return false;
		}
		
		//RaySeerEffectAsset bool check helper
		operator bool() const
		{
			return m_isvalid;
		}
		

	private:
		Effekseer::EffectRef effect;
		bool m_isvalid = false;
	};


	//info some class

	




	//========================================================
	// 
	// 
	// Simple API
	// 
	// 
	// 
	//========================================================


	//global variable
	//NOTE : because for do one single header / easy to way simple api 
	//メモ : グローバルな理由は使いやすさ重視のためです。
	inline Rayseer::RaySeerContext g_RaySeerContext;

	//NOTE : 

	//TODO : inline 変数のconstepxrにするか検討中(17以上)
	inline bool InitializeRaySeer(int kMaxParticleCount = 8000)
	{
		return g_context.Initialize(kMaxParticleCount);
	}

	inline void ShutdownRaySeer()
	{
		g_context.ShutDown();
	}



	inline void CreateEffect()
	{

	}

	inline void Update(float deltaTime) 
	{
		g_context.Update(deltaTime);
	}

	inline void Draw(const Camera3D& camera)
	{
		g_context.Draw(camera);
	}

	//Native(low) api
	inline void SetRayseerCamera3D(const Camera3D& camera)
	{
		const int renderWidth = GetRenderWidth();
		const int renderHeight = GetRenderHeight();
		const float aspect = renderHeight > 0 ? static_cast<float>(renderWidth) / static_cast<float>(renderHeight) : 1.0f;


		auto renderer = g_context.GetNativeRendererRef();
	
		//クラッシュ防止/早期描画キャンセル
		if (!renderer) {
			TraceLog(LOG_WARNING, "Rayseer renderer is nullptr!");
			//TODO : ここにわかりやすいように初期されているかとか詳細に。
			return;
		}


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

	inline void SetRayseerCamera3D(const Camera3D& camera, RaySeerContext& context)
	{
		context.SetEffekseerCamera(camera);
	}

	inline void SetRayseerCamera2D(const Camera2D& camera)
	{
		const int renderWidth = GetRenderWidth();
		const int renderHeight = GetRenderHeight();
		const float aspect = renderHeight > 0 ? static_cast<float>(renderWidth) / static_cast<float>(renderHeight) : 1.0f;


		auto renderer = g_RaySeerContext.GetNativeRendererRef();

		Effekseer::Matrix44 projection;
		projection.OrthographicRH(
			static_cast<float>(renderWidth),
			static_cast<float>(renderHeight),
			-1000.0f,
			1000.0f);
		
		const float rad = camera.rotation * DEG2RAD;
		const float s = std::sin(rad);
		const float c = std::cos(rad);

		Effekseer::Matrix44 cameraMatrix;
		cameraMatrix.Indentity();

		//zoom + rotation
		cameraMatrix.Values[0][0] = c * camera.zoom;
		cameraMatrix.Values[0][1] = -s * camera.zoom;

		cameraMatrix.Values[1][0] = c * camera.zoom;
		cameraMatrix.Values[1][1] = -s * camera.zoom;

		//
   // target を原点側へ移動
   //
		cameraMatrix.Values[3][0] =
			-(camera.target.x * cameraMatrix.Values[0][0]
				+ camera.target.y * cameraMatrix.Values[1][0]);

		cameraMatrix.Values[3][1] =
			-(camera.target.x * cameraMatrix.Values[0][1]
				+ camera.target.y * cameraMatrix.Values[1][1]);

		//
		// raylib Camera2D.offset
		//
		// OrthographicRH が画面中央基準なので、
		// offset を中央との差分として扱う
		//
		cameraMatrix.Values[3][0] +=
			camera.offset.x - static_cast<float>(renderWidth) * 0.5f;

		cameraMatrix.Values[3][1] +=
			camera.offset.y - static_cast<float>(renderHeight) * 0.5f;

		renderer->SetCameraMatrix(cameraMatrix);
		renderer->SetProjectionMatrix(projection);

		// 2Dなのでカメラ方向は固定
		renderer->SetCameraParameter(
			Effekseer::Vector3D{ 0.0f, 0.0f, 1.0f },
			Effekseer::Vector3D{ 0.0f, 0.0f, 0.0f });

	}

	//auto resize
	//use to raylib bool api of "IsWindowResized()"
	inline void Resize()
	{
		const int width = GetRenderWidth();
		const int height = GetRenderHeight();

		if (width <= 0 || height <= 0)
			return;

		rlDrawRenderBatchActive();
		rlViewport(0, 0, width, height);

	}


}



#endif //!RAYSEER_H end


