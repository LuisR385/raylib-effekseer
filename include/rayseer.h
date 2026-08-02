
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


//namespace or C like base

//NOTE  : maybe change to namespace name...
namespace Rayseer
{


	//define class
	class RaySeerContext;
	class RaySeerEffectAsset;
	class RaySeerEffectInstance;

	//define enum class
	enum class OPENGLVERSION;

	//define struct
	struct EffectHandle;
	struct State;

	//TODO : バージョンを選択できるようにする
	/*enum class OPENGLVERSION : uint8_t
	{

	};*/

	struct EffectHandle
	{
		Effekseer::Handle value{};
	};

	//info some class

	class RaySeerContext
	{
	public:
		void Init();
		void ShutDown();
		
		//lifecycle
		void Update();
		void Draw();
		bool Exits(); //TODO : handleぶちこむ
		
		void StopEffect(); //TODO : handleぶちこむ
		void Play();
		
		void SetPosition(Vector3 pos);
		void SetRotation(Vector3 rot);
		void SetScale(Vector3 scale);

		

	private:
		EffekseerRendererGL::RendererRef m_renderer;
		Effekseer::ManagerRef			 m_manager;

	};







	//global variable
	//NOTE : because for do one single header / easy to way simple api 

	inline Rayseer::RaySeerContext g_RaySeerContext;

	//NOTE : 

	//TODO : inline 変数のconstepxrにするか検討中(17以上)
	inline void InitializeRaySeer()
	{

	}

	inline void ShutdownRaySeer()
	{

	}

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


	inline void CreateEffect()
	{

	}



	inline void SetRayseerCamera3D(const Camera3D& camera)
	{

	}

	inline void SetRayseerCamera2D(const Camera2D& camera)
	{

	}

	//auto resize
	inline void Resize()
	{

	}

	inline void Resize(
		int width = GetRenderWidth(), 
		int height = GetRenderHeight())
	{

	}


}



#endif //!RAYSEER_H end


