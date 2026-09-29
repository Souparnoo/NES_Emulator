#pragma region license_and_help

#pragma endregion

#pragma region version_history

#pragma endregion

#pragma region hello_world_example

#pragma endregion

#ifndef V_PGE_DEF
#define V_PGE_DEF

#pragma region std_includes

#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <array>
#include <cstring>
#pragma endregion

#define PGE_VER 223

#pragma region compiler_config
#define USE_EXPERIMENTAL_FS
#if defined(_WIN32)
	#if _MSC_VER >= 1920 && _MSVC_LANG >= 201703L
		#undef USE_EXPERIMENTAL_FS
	#endif
#endif
#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__) || defined(__APPLE__)
	#if __cplusplus >= 201703L
		#undef USE_EXPERIMENTAL_FS
	#endif
#endif

#if !defined(v_KEYBOARD_UK)
	#define v_KEYBOARD_UK
#endif

#if defined(USE_EXPERIMENTAL_FS) || defined(FORCE_EXPERIMENTAL_FS)
	
	#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
	#include <experimental/filesystem>
	namespace _gfs = std::experimental::filesystem::v1;
#else
	
	#include <filesystem>
	namespace _gfs = std::filesystem;
#endif

#if defined(UNICODE) || defined(_UNICODE)
	#define vT(s) L##s
#else
	#define vT(s) s
#endif

#define UNUSED(x) (void)(x)

#if defined(v_PGE_HEADLESS)
	#define v_PLATFORM_HEADLESS
	#define v_GFX_HEADLESS
	#if !defined(v_IMAGE_STB) && !defined(v_IMAGE_GDI) && !defined(v_IMAGE_LIBPNG)
		#define v_IMAGE_HEADLESS
	#endif
#endif

#if !defined(v_PLATFORM_WINAPI) && !defined(v_PLATFORM_X11) && !defined(v_PLATFORM_GLUT) && !defined(v_PLATFORM_EMSCRIPTEN) && !defined(v_PLATFORM_HEADLESS)
	#if !defined(v_PLATFORM_CUSTOM_EX)
		#if defined(_WIN32)
			#define v_PLATFORM_WINAPI
		#endif
		#if defined(__linux__) || defined(__FreeBSD__)
			#define v_PLATFORM_X11
		#endif
		#if defined(__APPLE__)
			#define GL_SILENCE_DEPRECATION
			#define v_PLATFORM_GLUT
		#endif
		#if defined(__EMSCRIPTEN__)
			#define v_PLATFORM_EMSCRIPTEN
		#endif
	#endif
#endif

#if defined(v_PLATFORM_GLUT) || defined(v_PLATFORM_EMSCRIPTEN)
	#define PGE_USE_CUSTOM_START
#endif

#if !defined(v_GFX_OPENGL10) && !defined(v_GFX_OPENGL33) && !defined(v_GFX_DIRECTX10) && !defined(v_GFX_HEADLESS)
	#if !defined(v_GFX_CUSTOM_EX)
		#if defined(v_PLATFORM_EMSCRIPTEN)
			#define v_GFX_OPENGL33
		#else
			#define v_GFX_OPENGL10
		#endif
	#endif
#endif

#if !defined(v_IMAGE_STB) && !defined(v_IMAGE_GDI) && !defined(v_IMAGE_LIBPNG) && !defined(v_IMAGE_HEADLESS)
	#if !defined(v_IMAGE_CUSTOM_EX)
		#if defined(_WIN32)
			#define	v_IMAGE_GDI
		#endif
		#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__EMSCRIPTEN__)
			#define	v_IMAGE_LIBPNG
		#endif
	#endif
#endif

#if !defined(v_PGE_HEADLESS)
#if defined(v_PLATFORM_WINAPI)	
	#define _WINSOCKAPI_ 
		#if !defined(VC_EXTRALEAN)
		#define VC_EXTRALEAN
	#endif
	#if !defined(NOMINMAX)
		#define NOMINMAX
	#endif

	#if !defined(_WIN32_WINNT)
		#ifdef HAVE_MSMF
			#define _WIN32_WINNT 0x0600 
		#else
			#define _WIN32_WINNT 0x0500 
		#endif
	#endif

	#include <windows.h>
	#undef _WINSOCKAPI_
#endif

#if defined(v_PLATFORM_X11)
	namespace X11
	{
		#include <X11/X.h>
		#include <X11/Xlib.h>
	}
#endif

#if defined(v_PLATFORM_GLUT)
	#if defined(__linux__)
		#include <GL/glut.h>
		#include <GL/freeglut_ext.h>
	#endif
	#if defined(__APPLE__)
		#include <GLUT/glut.h>
	#include <objc/message.h>
	#include <objc/NSObjCRuntime.h>
	#endif
#endif
#endif

#if defined(v_PGE_HEADLESS)
#if defined max
#undef max
#endif
#if defined min
#undef min
#endif
#endif
#pragma endregion

#pragma region pge_declaration
namespace v
{
	class PixelGameEngine;
	class Sprite;

	constexpr uint8_t  nMouseButtons = 5;
	constexpr uint8_t  nDefaultAlpha = 0xFF;
	constexpr uint32_t nDefaultPixel = (nDefaultAlpha << 24);
	constexpr uint8_t  nTabSizeInSpaces = 4;
	constexpr size_t v_MAX_VERTS = 128;
	enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };

	struct Pixel
	{
		union
		{
			uint32_t n = nDefaultPixel;
			struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
		};

		enum Mode { NORMAL, MASK, ALPHA, CUSTOM };

		Pixel();
		Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
		Pixel(uint32_t p);
		Pixel& operator = (const Pixel& v) = default;
		bool   operator ==(const Pixel& p) const;
		bool   operator !=(const Pixel& p) const;
		Pixel  operator * (const float i) const;
		Pixel  operator / (const float i) const;
		Pixel& operator *=(const float i);
		Pixel& operator /=(const float i);
		Pixel  operator + (const Pixel& p) const;
		Pixel  operator - (const Pixel& p) const;
		Pixel& operator +=(const Pixel& p);
		Pixel& operator -=(const Pixel& p);
		Pixel  operator * (const Pixel& p) const;
		Pixel& operator *=(const Pixel& p);
		Pixel  inv() const;
	};

	Pixel PixelF(float red, float green, float blue, float alpha = 1.0f);
	Pixel PixelLerp(const v::Pixel& p1, const v::Pixel& p2, float t);

	static const Pixel
		GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
		RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
		YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
		GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
		CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
		BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
		MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
		WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);

	enum Key
	{
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		UP, DOWN, LEFT, RIGHT,
		SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
		BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
		EQUALS, COMMA, MINUS,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
		CAPS_LOCK, ENUM_END
	};

	namespace Mouse
	{
		static constexpr int32_t LEFT = 0;
		static constexpr int32_t RIGHT = 1;
		static constexpr int32_t MIDDLE = 2;
	};

	struct HWButton
	{
		bool bPressed = false;	
		bool bReleased = false;	
		bool bHeld = false;		
	};

#if !defined(v_IGNORE_VEC2D)
	template <class T>
	struct v2d_generic
	{
		T x = 0;
		T y = 0;
		v2d_generic() : x(0), y(0) {}
		v2d_generic(T _x, T _y) : x(_x), y(_y) {}
		v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
		v2d_generic& operator=(const v2d_generic& v) = default;
		T mag() const { return T(std::sqrt(x * x + y * y)); }
		T mag2() const { return x * x + y * y; }
		v2d_generic  norm() const { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
		v2d_generic  perp() const { return v2d_generic(-y, x); }
		v2d_generic  floor() const { return v2d_generic(std::floor(x), std::floor(y)); }
		v2d_generic  ceil() const { return v2d_generic(std::ceil(x), std::ceil(y)); }
		v2d_generic  max(const v2d_generic& v) const { return v2d_generic(std::max(x, v.x), std::max(y, v.y)); }
		v2d_generic  min(const v2d_generic& v) const { return v2d_generic(std::min(x, v.x), std::min(y, v.y)); }
		v2d_generic  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
		v2d_generic  polar() { return { mag(), std::atan2(y, x) }; }
		v2d_generic  clamp(const v2d_generic& v1, const v2d_generic& v2) const { return this->max(v1).min(v2); }
		v2d_generic	 lerp(const v2d_generic& v1, const double t) { return this->operator*(T(1.0 - t)) + (v1 * T(t)); }
		T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
		T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
		v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
		v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
		v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
		v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
		v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
		v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
		v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
		v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
		v2d_generic& operator *= (const v2d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		v2d_generic& operator /= (const v2d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
		v2d_generic  operator +  () const { return { +x, +y }; }
		v2d_generic  operator -  () const { return { -x, -y }; }
		bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
		bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
		const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
		friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
		operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
		operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
		operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
	};

	template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }
	template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }
	template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }

	template<class T, class U> inline bool operator < (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{ return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x); }
	template<class T, class U> inline bool operator > (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{ return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x); }

	typedef v2d_generic<int32_t> vi2d;
	typedef v2d_generic<uint32_t> vu2d;
	typedef v2d_generic<float> vf2d;
	typedef v2d_generic<double> vd2d;
#endif

	struct ResourceBuffer : public std::streambuf
	{
		ResourceBuffer(std::ifstream& ifs, uint32_t offset, uint32_t size);
		std::vector<char> vMemory;
	};

	class ResourcePack : public std::streambuf
	{
	public:
		ResourcePack();
		~ResourcePack();
		bool AddFile(const std::string& sFile);
		bool LoadPack(const std::string& sFile, const std::string& sKey);
		bool SavePack(const std::string& sFile, const std::string& sKey);
		ResourceBuffer GetFileBuffer(const std::string& sFile);
		bool Loaded();
	private:
		struct sResourceFile { uint32_t nSize; uint32_t nOffset; };
		std::map<std::string, sResourceFile> mapFiles;
		std::ifstream baseFile;
		std::vector<char> scramble(const std::vector<char>& data, const std::string& key);
		std::string makeposix(const std::string& path);
	};

	class ImageLoader
	{
	public:
		ImageLoader() = default;
		virtual ~ImageLoader() = default;
		virtual v::rcode LoadImageResource(v::Sprite* spr, const std::string& sImageFile, v::ResourcePack* pack) = 0;
		virtual v::rcode SaveImageResource(v::Sprite* spr, const std::string& sImageFile) = 0;
	};

	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::string& sImageFile, v::ResourcePack* pack = nullptr);
		Sprite(int32_t w, int32_t h);
		Sprite(const v::Sprite&) = delete;
		~Sprite();

	public:
		v::rcode LoadFromFile(const std::string& sImageFile, v::ResourcePack* pack = nullptr);

	public:
		int32_t width = 0;
		int32_t height = 0;
		enum Mode { NORMAL, PERIODIC, CLAMP };
		enum Flip { NONE = 0, HORIZ = 1, VERT = 2 };

	public:
		void SetSampleMode(v::Sprite::Mode mode = v::Sprite::Mode::NORMAL);
		Pixel GetPixel(int32_t x, int32_t y) const;
		bool  SetPixel(int32_t x, int32_t y, Pixel p);
		Pixel GetPixel(const v::vi2d& a) const;
		bool  SetPixel(const v::vi2d& a, Pixel p);
		Pixel Sample(float x, float y) const;
		Pixel Sample(const v::vf2d& uv) const;
		Pixel SampleBL(float u, float v) const;
		Pixel SampleBL(const v::vf2d& uv) const;
		Pixel* GetData();
		v::Sprite* Duplicate();
		v::Sprite* Duplicate(const v::vi2d& vPos, const v::vi2d& vSize);
		v::vi2d Size() const;
		std::vector<v::Pixel> pColData;
		Mode modeSample = Mode::NORMAL;

		static std::unique_ptr<v::ImageLoader> loader;
	};

	class Decal
	{
	public:
		Decal(v::Sprite* spr, bool filter = false, bool clamp = true);
		Decal(const uint32_t nExistingTextureResource, v::Sprite* spr);
		virtual ~Decal();
		void Update();
		void UpdateSprite();

	public: 
		int32_t id = -1;
		v::Sprite* sprite = nullptr;
		v::vf2d vUVScale = { 1.0f, 1.0f };
	};

	enum class DecalMode
	{
		NORMAL,
		ADDITIVE,
		MULTIPLICATIVE,
		STENCIL,
		ILLUMINATE,
		WIREFRAME,
		MODEL3D,
	};

	enum class DecalStructure
	{
		LINE,
		FAN,
		STRIP,
		LIST
	};

	class Renderable
	{
	public:
		Renderable() = default;		
		Renderable(Renderable&& r) : pSprite(std::move(r.pSprite)), pDecal(std::move(r.pDecal)) {}		
		Renderable(const Renderable&) = delete;
		v::rcode Load(const std::string& sFile, ResourcePack* pack = nullptr, bool filter = false, bool clamp = true);
		void Create(uint32_t width, uint32_t height, bool filter = false, bool clamp = true);
		v::Decal* Decal() const;
		v::Sprite* Sprite() const;

	private:
		std::unique_ptr<v::Sprite> pSprite = nullptr;
		std::unique_ptr<v::Decal> pDecal = nullptr;
	};

	struct DecalInstance
	{
		v::Decal* decal = nullptr;
		std::vector<v::vf2d> pos;
		std::vector<v::vf2d> uv;
		std::vector<float> w;
		std::vector<v::Pixel> tint;
		v::DecalMode mode = v::DecalMode::NORMAL;
		v::DecalStructure structure = v::DecalStructure::FAN;
		uint32_t points = 0;
	};

	struct LayerDesc
	{
		v::vf2d vOffset = { 0, 0 };
		v::vf2d vScale = { 1, 1 };
		bool bShow = false;
		bool bUpdate = false;
		v::Renderable pDrawTarget;
		uint32_t nResID = 0;
		std::vector<DecalInstance> vecDecalInstance;
		v::Pixel tint = v::WHITE;
		std::function<void()> funcHook = nullptr;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		virtual void       PrepareDevice() = 0;
		virtual v::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
		virtual v::rcode DestroyDevice() = 0;
		virtual void       DisplayFrame() = 0;
		virtual void       PrepareDrawing() = 0;
		virtual void	   SetDecalMode(const v::DecalMode& mode) = 0;
		virtual void       DrawLayerQuad(const v::vf2d& offset, const v::vf2d& scale, const v::Pixel tint) = 0;
		virtual void       DrawDecal(const v::DecalInstance& decal) = 0;
		virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height, const bool filtered = false, const bool clamp = true) = 0;
		virtual void       UpdateTexture(uint32_t id, v::Sprite* spr) = 0;
		virtual void       ReadTexture(uint32_t id, v::Sprite* spr) = 0;
		virtual uint32_t   DeleteTexture(const uint32_t id) = 0;
		virtual void       ApplyTexture(uint32_t id) = 0;
		virtual void       UpdateViewport(const v::vi2d& pos, const v::vi2d& size) = 0;
		virtual void       ClearBuffer(v::Pixel p, bool bDepth) = 0;
		static v::PixelGameEngine* ptrPGE;
	};

	class Platform
	{
	public:
		virtual ~Platform() = default;
		virtual v::rcode ApplicationStartUp() = 0;
		virtual v::rcode ApplicationCleanUp() = 0;
		virtual v::rcode ThreadStartUp() = 0;
		virtual v::rcode ThreadCleanUp() = 0;
		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) = 0;
		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) = 0;
		virtual v::rcode SetWindowTitle(const std::string& s) = 0;
		virtual v::rcode StartSystemEventLoop() = 0;
		virtual v::rcode HandleSystemEvent() = 0;
		static v::PixelGameEngine* ptrPGE;
	};

	class PGEX;

	static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<Platform> platform;
	static std::map<size_t, uint8_t> mapKeys;

	class PixelGameEngine
	{
	public:
		PixelGameEngine();
		virtual ~PixelGameEngine();
	public:
		v::rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
			bool full_screen = false, bool vsync = false, bool cohesion = false);
		v::rcode Start();

	public: 
		
		virtual bool OnUserCreate();
		
		virtual bool OnUserUpdate(float fElapsedTime);
		
		virtual bool OnUserDestroy();

		virtual void OnTextEntryComplete(const std::string& sText);
		
		virtual bool OnConsoleCommand(const std::string& sCommand);

	public: 
		
		bool IsFocused() const;
		
		HWButton GetKey(Key k) const;
		
		HWButton GetMouse(uint32_t b) const;
		
		int32_t GetMouseX() const;
		
		int32_t GetMouseY() const;
		
		int32_t GetMouseWheel() const;
		
		const v::vi2d& GetWindowMouse() const;
		
		const v::vi2d& GetMousePos() const;

		static const std::map<size_t, uint8_t>& GetKeyMap() { return mapKeys; }

	public: 
		
		int32_t ScreenWidth() const;
		
		int32_t ScreenHeight() const;
		
		int32_t GetDrawTargetWidth() const;
		
		int32_t GetDrawTargetHeight() const;
		
		v::Sprite* GetDrawTarget() const;
		
		void SetScreenSize(int w, int h);

		void SetDrawTarget(Sprite* target);
		
		uint32_t GetFPS() const;
		
		float GetElapsedTime() const;
		
		const v::vi2d& GetWindowSize() const;
		
		const v::vi2d& GetPixelSize() const;
		
		const v::vi2d& GetScreenPixelSize() const;
		
		const v::vi2d& GetScreenSize() const;
		
		const std::vector<std::string>& GetDroppedFiles() const;
		const v::vi2d& GetDroppedFilesPoint() const;

	public: 
		
		void SetDrawTarget(uint8_t layer, bool bDirty = true);
		void EnableLayer(uint8_t layer, bool b);
		void SetLayerOffset(uint8_t layer, const v::vf2d& offset);
		void SetLayerOffset(uint8_t layer, float x, float y);
		void SetLayerScale(uint8_t layer, const v::vf2d& scale);
		void SetLayerScale(uint8_t layer, float x, float y);
		void SetLayerTint(uint8_t layer, const v::Pixel& tint);
		void SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f);

		std::vector<LayerDesc>& GetLayers();
		uint32_t CreateLayer();

		void SetPixelMode(Pixel::Mode m);
		Pixel::Mode GetPixelMode();
		
		void SetPixelMode(std::function<v::Pixel(const int x, const int y, const v::Pixel& pSource, const v::Pixel& pDest)> pixelMode);
		
		void SetPixelBlend(float fBlend);

	public: 
		
		virtual bool Draw(int32_t x, int32_t y, Pixel p = v::WHITE);
		bool Draw(const v::vi2d& pos, Pixel p = v::WHITE);
		
		void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p = v::WHITE, uint32_t pattern = 0xFFFFFFFF);
		void DrawLine(const v::vi2d& pos1, const v::vi2d& pos2, Pixel p = v::WHITE, uint32_t pattern = 0xFFFFFFFF);
		
		void DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p = v::WHITE, uint8_t mask = 0xFF);
		void DrawCircle(const v::vi2d& pos, int32_t radius, Pixel p = v::WHITE, uint8_t mask = 0xFF);
		
		void FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p = v::WHITE);
		void FillCircle(const v::vi2d& pos, int32_t radius, Pixel p = v::WHITE);
		
		void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = v::WHITE);
		void DrawRect(const v::vi2d& pos, const v::vi2d& size, Pixel p = v::WHITE);
		
		void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = v::WHITE);
		void FillRect(const v::vi2d& pos, const v::vi2d& size, Pixel p = v::WHITE);
		
		void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = v::WHITE);
		void DrawTriangle(const v::vi2d& pos1, const v::vi2d& pos2, const v::vi2d& pos3, Pixel p = v::WHITE);
		
		void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = v::WHITE);
		void FillTriangle(const v::vi2d& pos1, const v::vi2d& pos2, const v::vi2d& pos3, Pixel p = v::WHITE);
		
		void FillTexturedTriangle(const std::vector<v::vf2d>& vPoints, std::vector<v::vf2d> vTex, std::vector<v::Pixel> vColour, v::Sprite* sprTex);
		void FillTexturedPolygon(const std::vector<v::vf2d>& vPoints, const std::vector<v::vf2d>& vTex, const std::vector<v::Pixel>& vColour, v::Sprite* sprTex, v::DecalStructure structure = v::DecalStructure::LIST);
		
		void DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale = 1, uint8_t flip = v::Sprite::NONE);
		void DrawSprite(const v::vi2d& pos, Sprite* sprite, uint32_t scale = 1, uint8_t flip = v::Sprite::NONE);

		void DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale = 1, uint8_t flip = v::Sprite::NONE);
		void DrawPartialSprite(const v::vi2d& pos, Sprite* sprite, const v::vi2d& sourcepos, const v::vi2d& size, uint32_t scale = 1, uint8_t flip = v::Sprite::NONE);
		
		void DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col = v::WHITE, uint32_t scale = 1);
		void DrawString(const v::vi2d& pos, const std::string& sText, Pixel col = v::WHITE, uint32_t scale = 1);
		v::vi2d GetTextSize(const std::string& s);
		
		void DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col = v::WHITE, uint32_t scale = 1);
		void DrawStringProp(const v::vi2d& pos, const std::string& sText, Pixel col = v::WHITE, uint32_t scale = 1);
		v::vi2d GetTextSizeProp(const std::string& s);

		void SetDecalMode(const v::DecalMode& mode);
		void SetDecalStructure(const v::DecalStructure& structure);
		
		void DrawDecal(const v::vf2d& pos, v::Decal* decal, const v::vf2d& scale = { 1.0f,1.0f }, const v::Pixel& tint = v::WHITE);
		
		void DrawPartialDecal(const v::vf2d& pos, v::Decal* decal, const v::vf2d& source_pos, const v::vf2d& source_size, const v::vf2d& scale = { 1.0f,1.0f }, const v::Pixel& tint = v::WHITE);
		void DrawPartialDecal(const v::vf2d& pos, const v::vf2d& size, v::Decal* decal, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint = v::WHITE);
		
		void DrawExplicitDecal(v::Decal* decal, const v::vf2d* pos, const v::vf2d* uv, const v::Pixel* col, uint32_t elements = 4);
		
		void DrawWarpedDecal(v::Decal* decal, const v::vf2d(&pos)[4], const v::Pixel& tint = v::WHITE);
		void DrawWarpedDecal(v::Decal* decal, const v::vf2d* pos, const v::Pixel& tint = v::WHITE);
		void DrawWarpedDecal(v::Decal* decal, const std::array<v::vf2d, 4>& pos, const v::Pixel& tint = v::WHITE);
		
		void DrawPartialWarpedDecal(v::Decal* decal, const v::vf2d(&pos)[4], const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint = v::WHITE);
		void DrawPartialWarpedDecal(v::Decal* decal, const v::vf2d* pos, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint = v::WHITE);
		void DrawPartialWarpedDecal(v::Decal* decal, const std::array<v::vf2d, 4>& pos, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint = v::WHITE);
		
		void DrawRotatedDecal(const v::vf2d& pos, v::Decal* decal, const float fAngle, const v::vf2d& center = { 0.0f, 0.0f }, const v::vf2d& scale = { 1.0f,1.0f }, const v::Pixel& tint = v::WHITE);
		void DrawPartialRotatedDecal(const v::vf2d& pos, v::Decal* decal, const float fAngle, const v::vf2d& center, const v::vf2d& source_pos, const v::vf2d& source_size, const v::vf2d& scale = { 1.0f, 1.0f }, const v::Pixel& tint = v::WHITE);
		
		void DrawStringDecal(const v::vf2d& pos, const std::string& sText, const Pixel col = v::WHITE, const v::vf2d& scale = { 1.0f, 1.0f });
		void DrawStringPropDecal(const v::vf2d& pos, const std::string& sText, const Pixel col = v::WHITE, const v::vf2d& scale = { 1.0f, 1.0f });
		
		void DrawRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel col = v::WHITE);
		void FillRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel col = v::WHITE);
		
		void GradientFillRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel colTL, const v::Pixel colBL, const v::Pixel colBR, const v::Pixel colTR);
		
		void DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const v::Pixel tint = v::WHITE);
		void DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<float>& depth, const std::vector<v::vf2d>& uv, const v::Pixel tint = v::WHITE);
		void DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const std::vector<v::Pixel>& tint);
		void DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const std::vector<v::Pixel>& colours, const v::Pixel tint);
		
		void DrawLineDecal(const v::vf2d& pos1, const v::vf2d& pos2, Pixel p = v::WHITE);
		void DrawRotatedStringDecal(const v::vf2d& pos, const std::string& sText, const float fAngle, const v::vf2d& center = { 0.0f, 0.0f }, const v::Pixel col = v::WHITE, const v::vf2d& scale = { 1.0f, 1.0f });
		void DrawRotatedStringPropDecal(const v::vf2d& pos, const std::string& sText, const float fAngle, const v::vf2d& center = { 0.0f, 0.0f }, const v::Pixel col = v::WHITE, const v::vf2d& scale = { 1.0f, 1.0f });
		
		void Clear(Pixel p);
		
		void ClearBuffer(Pixel p, bool bDepth = true);
		
		v::Sprite* GetFontSprite();

		bool ClipLineToScreen(v::vi2d& in_p1, v::vi2d& in_p2);

		void EnablePixelTransfer(const bool bEnable = true);

		void ConsoleShow(const v::Key &keyExit, bool bSuspendTime = true);
		bool IsConsoleShowing() const;
		void ConsoleClear();
		std::stringstream& ConsoleOut();
		void ConsoleCaptureStdOut(const bool bCapture);

		void TextEntryEnable(const bool bEnable, const std::string& sText = "");
		std::string TextEntryGetString() const;
		int32_t TextEntryGetCursor() const;
		bool IsTextEntryEnabled() const;

	private:
		void UpdateTextEntry();
		void UpdateConsole();

	public:

#ifdef v_ENABLE_EXPERIMENTAL
		
		void LW3D_View(const std::array<float, 16>& m);
		
		void LW3D_World(const std::array<float, 16>& m);
		
		void LW3D_Projection(const std::array<float, 16>& m);

		void LW3D_DrawTriangles(v::Decal* decal, const std::vector<std::array<float,3>>& pos, const std::vector<v::vf2d>& tex, const std::vector<v::Pixel>& col);

		void LW3D_ModelTranslate(const float x, const float y, const float z);

		void LW3D_SetCameraAtTarget(const float fEyeX, const float fEyeY, const float fEyeZ,
			const float fTargetX, const float fTargetY, const float fTargetZ,
			const float fUpX = 0.0f, const float fUpY = 1.0f, const float fUpZ = 0.0f);
		void LW3D_SetCameraAlongDirection(const float fEyeX, const float fEyeY, const float fEyeZ,
			const float fDirX, const float fDirY, const float fDirZ,
			const float fUpX = 0.0f, const float fUpY = 1.0f, const float fUpZ = 0.0f);

		void LW3D_EnableDepthTest(const bool bEnableDepth);
		void LW3D_EnableBackfaceCulling(const bool bEnableCull);
#endif
	public: 
		std::string sAppName;

	private: 
		v::Sprite*     pDrawTarget = nullptr;
		Pixel::Mode	nPixelMode = Pixel::NORMAL;
		float		fBlendFactor = 1.0f;
		v::vi2d	vScreenSize = { 256, 240 };
		v::vf2d	vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
		v::vi2d	vPixelSize = { 4, 4 };
		v::vi2d   vScreenPixelSize = { 4, 4 };
		v::vi2d	vMousePos = { 0, 0 };
		int32_t		nMouseWheelDelta = 0;
		v::vi2d	vMousePosCache = { 0, 0 };
		v::vi2d   vMouseWindowPos = { 0, 0 };
		int32_t		nMouseWheelDeltaCache = 0;
		v::vi2d	vWindowSize = { 0, 0 };
		v::vi2d	vViewPos = { 0, 0 };
		v::vi2d	vViewSize = { 0,0 };
		bool		bFullScreen = false;
		v::vf2d	vPixel = { 1.0f, 1.0f };
		bool		bHasInputFocus = false;
		bool		bHasMouseFocus = false;
		bool		bEnableVSYNC = false;
		float		fFrameTimer = 1.0f;
		float		fLastElapsed = 0.0f;
		int			nFrameCount = 0;		
		bool bSuspendTextureTransfer = false;
		Renderable  fontRenderable;
		std::vector<LayerDesc> vLayers;
		uint8_t		nTargetLayer = 0;
		uint32_t	nLastFPS = 0;
		bool        bPixelCohesion = false;
		DecalMode   nDecalMode = DecalMode::NORMAL;
		DecalStructure nDecalStructure = DecalStructure::FAN;
		std::function<v::Pixel(const int x, const int y, const v::Pixel&, const v::Pixel&)> funcPixelMode;
		std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
		std::vector<v::vi2d> vFontSpacing;
		std::vector<std::string> vDroppedFiles;
		std::vector<std::string> vDroppedFilesCache;
		v::vi2d vDroppedFilesPoint;
		v::vi2d vDroppedFilesPointCache;

		bool bConsoleShow = false;
		bool bConsoleSuspendTime = false;
		v::Key keyConsoleExit = v::Key::F1;
		std::stringstream ssConsoleOutput;
		std::streambuf* sbufOldCout = nullptr;
		v::vi2d vConsoleSize;
		v::vi2d vConsoleCursor = { 0,0 };
		v::vf2d vConsoleCharacterScale = { 1.0f, 2.0f };
		std::vector<std::string> sConsoleLines;
		std::list<std::string> sCommandHistory;
		std::list<std::string>::iterator sCommandHistoryIt;

		bool bTextEntryEnable = false;
		std::string sTextEntryString = "";
		int32_t nTextEntryCursor = 0;
		std::vector<std::tuple<v::Key, std::string, std::string>> vKeyboardMap;

		bool		pKeyNewState[256] = { 0 };
		bool		pKeyOldState[256] = { 0 };
		HWButton	pKeyboardState[256] = { 0 };

		bool		pMouseNewState[nMouseButtons] = { 0 };
		bool		pMouseOldState[nMouseButtons] = { 0 };
		HWButton	pMouseState[nMouseButtons] = { 0 };

		void		EngineThread();

		static std::atomic<bool> bAtomActive;

	public:
		
		void v_UpdateMouse(int32_t x, int32_t y);
		void v_UpdateMouseWheel(int32_t delta);
		void v_UpdateWindowSize(int32_t x, int32_t y);
		void v_UpdateViewport();
		void v_ConstructFontSheet();
		void v_CoreUpdate();
		void v_PrepareEngine();
		void v_UpdateMouseState(int32_t button, bool state);
		void v_UpdateKeyState(int32_t key, bool state);
		void v_UpdateMouseFocus(bool state);
		void v_UpdateKeyFocus(bool state);
		void v_Terminate();
		void v_DropFiles(int32_t x, int32_t y, const std::vector<std::string>& vFiles);
		void v_Reanimate();
		bool v_IsRunning();

		virtual void v_ConfigureSystem();

	public: 
		friend class PGEX;
		void pgex_Register(v::PGEX* pgex);

	private:
		std::vector<v::PGEX*> vExtensions;
	};

	class PGEX
	{
		friend class v::PixelGameEngine;
	public:
		PGEX(bool bHook = false);

	protected:
		virtual void OnBeforeUserCreate();
		virtual void OnAfterUserCreate();
		virtual bool OnBeforeUserUpdate(float &fElapsedTime);
		virtual void OnAfterUserUpdate(float fElapsedTime);

	protected:
		static PixelGameEngine* pge;
	};
}

#pragma endregion

#pragma region opengl33_iface

#if defined(v_GFX_OPENGL33)

	#if defined(v_PLATFORM_WINAPI)
		#include <gl/GL.h>
		#define CALLSTYLE __stdcall
	#endif

	#if defined(__linux__) || defined(__FreeBSD__)
		#include <GL/gl.h>
	#endif

	#if defined(v_PLATFORM_X11)
		namespace X11 {
			#include <GL/glx.h>
		}
		#define CALLSTYLE 
	#endif

	#if defined(__APPLE__)
		#define GL_SILENCE_DEPRECATION
		#include <OpenGL/OpenGL.h>
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
	#endif

	#if defined(v_PLATFORM_EMSCRIPTEN)
		#include <EGL/egl.h>
		#include <GLES2/gl2.h>
		#define GL_GLEXT_PROTOTYPES
		#include <GLES2/gl2ext.h>
		#include <emscripten/emscripten.h>
		#define CALLSTYLE
		#define GL_CLAMP GL_CLAMP_TO_EDGE
	#endif

namespace v
{
	typedef char GLchar;
	typedef ptrdiff_t GLsizeiptr;

	typedef GLuint CALLSTYLE locCreateShader_t(GLenum type);
	typedef GLuint CALLSTYLE locCreateProgram_t(void);
	typedef void CALLSTYLE locDeleteShader_t(GLuint shader);
	typedef void CALLSTYLE locCompileShader_t(GLuint shader);
	typedef void CALLSTYLE locLinkProgram_t(GLuint program);
	typedef void CALLSTYLE locDeleteProgram_t(GLuint program);
	typedef void CALLSTYLE locAttachShader_t(GLuint program, GLuint shader);
	typedef void CALLSTYLE locBindBuffer_t(GLenum target, GLuint buffer);
	typedef void CALLSTYLE locBufferData_t(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	typedef void CALLSTYLE locGenBuffers_t(GLsizei n, GLuint* buffers);
	typedef void CALLSTYLE locVertexAttribPointer_t(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	typedef void CALLSTYLE locEnableVertexAttribArray_t(GLuint index);
	typedef void CALLSTYLE locUseProgram_t(GLuint program);
	typedef void CALLSTYLE locBindVertexArray_t(GLuint array);
	typedef void CALLSTYLE locGenVertexArrays_t(GLsizei n, GLuint* arrays);
	typedef void CALLSTYLE locGetShaderInfoLog_t(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
	typedef GLint CALLSTYLE locGetUniformLocation_t(GLuint program, const GLchar* name);
	typedef void CALLSTYLE locUniform1f_t(GLint location, GLfloat v0);
	typedef void CALLSTYLE locUniform1i_t(GLint location, GLint v0);
	typedef void CALLSTYLE locUniform2fv_t(GLint location, GLsizei count, const GLfloat* value);
	typedef void CALLSTYLE locActiveTexture_t(GLenum texture);
	typedef void CALLSTYLE locGenFrameBuffers_t(GLsizei n, GLuint* ids);
	typedef void CALLSTYLE locBindFrameBuffer_t(GLenum target, GLuint fb);
	typedef GLenum CALLSTYLE locCheckFrameBufferStatus_t(GLenum target);
	typedef void CALLSTYLE locDeleteFrameBuffers_t(GLsizei n, const GLuint* fbs);
	typedef void CALLSTYLE locFrameBufferTexture2D_t(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	typedef void CALLSTYLE locDrawBuffers_t(GLsizei n, const GLenum* bufs);
	typedef void CALLSTYLE locBlendFuncSeparate_t(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

#if defined(v_PLATFORM_WINAPI)
	typedef void __stdcall locSwapInterval_t(GLsizei n);
#endif

#if defined(v_PLATFORM_X11)
	typedef int(locSwapInterval_t)(X11::Display* dpy, X11::GLXDrawable drawable, int interval);
#endif

#if defined(v_PLATFORM_EMSCRIPTEN)
	typedef void CALLSTYLE locShaderSource_t(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
	typedef EGLBoolean(locSwapInterval_t)(EGLDisplay display, EGLint interval);
#else
	typedef void CALLSTYLE locShaderSource_t(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
#endif

} 
#endif 
#pragma endregion

#endif 

#ifdef V_PGE_APPLICATION
#undef V_PGE_APPLICATION

#pragma region pge_implementation
namespace v
{

	Pixel::Pixel()
	{ r = 0; g = 0; b = 0; a = nDefaultAlpha; }

	Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	{ n = red | (green << 8) | (blue << 16) | (alpha << 24); } 

	Pixel::Pixel(uint32_t p)
	{ n = p; }

	bool Pixel::operator==(const Pixel& p) const
	{ return n == p.n; }

	bool Pixel::operator!=(const Pixel& p) const
	{ return n != p.n; }

	Pixel  Pixel::operator * (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) * i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) * i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) * i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel  Pixel::operator / (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) / i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) / i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) / i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel& Pixel::operator *=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * i)));
		return *this;
	}

	Pixel& Pixel::operator /=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) / i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) / i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) / i)));
		return *this;
	}

	Pixel  Pixel::operator + (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel  Pixel::operator - (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel& Pixel::operator += (const Pixel& p)
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return *this;
	}

	Pixel& Pixel::operator -= (const Pixel& p) 
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return *this;
	}

	Pixel Pixel::operator * (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * float(p.r) / 255.0f)));
		uint8_t nG = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * float(p.g) / 255.0f)));
		uint8_t nB = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * float(p.b) / 255.0f)));
		uint8_t nA = uint8_t(std::min(255.0f, std::max(0.0f, float(a) * float(p.a) / 255.0f)));
		return Pixel(nR, nG, nB, nA);
	}

	Pixel& Pixel::operator *=(const Pixel& p)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * float(p.r) / 255.0f)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * float(p.g) / 255.0f)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * float(p.b) / 255.0f)));
		this->a = uint8_t(std::min(255.0f, std::max(0.0f, float(a) * float(p.a) / 255.0f)));
		return *this;
	}

	Pixel Pixel::inv() const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, 255 - int(r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, 255 - int(g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, 255 - int(b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel PixelF(float red, float green, float blue, float alpha)
	{ return Pixel(uint8_t(red * 255.0f), uint8_t(green * 255.0f), uint8_t(blue * 255.0f), uint8_t(alpha * 255.0f)); }

	Pixel PixelLerp(const v::Pixel& p1, const v::Pixel& p2, float t)
	{ return (p2 * t) + p1 * (1.0f - t); }

	Sprite::Sprite()
	{ width = 0; height = 0; }

	Sprite::Sprite(const std::string& sImageFile, v::ResourcePack* pack)
	{ LoadFromFile(sImageFile, pack); }

	Sprite::Sprite(int32_t w, int32_t h)
	{		
		width = w;		height = h;
		pColData.resize(width * height);
		pColData.resize(width * height, nDefaultPixel);
	}

	Sprite::~Sprite()
	{ pColData.clear();	}

	void Sprite::SetSampleMode(v::Sprite::Mode mode)
	{ modeSample = mode; }

	Pixel Sprite::GetPixel(const v::vi2d& a) const
	{ return GetPixel(a.x, a.y); }

	bool Sprite::SetPixel(const v::vi2d& a, Pixel p)
	{ return SetPixel(a.x, a.y, p); }

	Pixel Sprite::GetPixel(int32_t x, int32_t y) const
	{
		if (modeSample == v::Sprite::Mode::NORMAL)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
				return pColData[y * width + x];
			else
				return Pixel(0, 0, 0, 0);
		}
		else
		{
			if (modeSample == v::Sprite::Mode::PERIODIC)
				return pColData[abs(y % height) * width + abs(x % width)];
			else
				return pColData[std::max(0, std::min(y, height-1)) * width + std::max(0, std::min(x, width-1))];
		}
	}

	bool Sprite::SetPixel(int32_t x, int32_t y, Pixel p)
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			pColData[y * width + x] = p;
			return true;
		}
		else
			return false;
	}

	Pixel Sprite::Sample(float x, float y) const
	{
		int32_t sx = std::min((int32_t)((x * (float)width)), width - 1);
		int32_t sy = std::min((int32_t)((y * (float)height)), height - 1);
		return GetPixel(sx, sy);
	}

	Pixel Sprite::Sample(const v::vf2d& uv) const
	{
		return Sample(uv.x, uv.y);
	}

	Pixel Sprite::SampleBL(float u, float v) const
	{
		u = u * width - 0.5f;
		v = v * height - 0.5f;
		int x = (int)floor(u); 
		int y = (int)floor(v); 
		float u_ratio = u - x;
		float v_ratio = v - y;
		float u_opposite = 1 - u_ratio;
		float v_opposite = 1 - v_ratio;

		v::Pixel p1 = GetPixel(std::max(x, 0), std::max(y, 0));
		v::Pixel p2 = GetPixel(std::min(x + 1, (int)width - 1), std::max(y, 0));
		v::Pixel p3 = GetPixel(std::max(x, 0), std::min(y + 1, (int)height - 1));
		v::Pixel p4 = GetPixel(std::min(x + 1, (int)width - 1), std::min(y + 1, (int)height - 1));

		return v::Pixel(
			(uint8_t)((p1.r * u_opposite + p2.r * u_ratio) * v_opposite + (p3.r * u_opposite + p4.r * u_ratio) * v_ratio),
			(uint8_t)((p1.g * u_opposite + p2.g * u_ratio) * v_opposite + (p3.g * u_opposite + p4.g * u_ratio) * v_ratio),
			(uint8_t)((p1.b * u_opposite + p2.b * u_ratio) * v_opposite + (p3.b * u_opposite + p4.b * u_ratio) * v_ratio));
	}

	Pixel Sprite::SampleBL(const v::vf2d& uv) const
	{
		return SampleBL(uv.x, uv.y);
	}

	Pixel* Sprite::GetData()
	{ return pColData.data(); }

	v::rcode Sprite::LoadFromFile(const std::string& sImageFile, v::ResourcePack* pack)
	{
		UNUSED(pack);
		return loader->LoadImageResource(this, sImageFile, pack);
	}

	v::Sprite* Sprite::Duplicate()
	{
		v::Sprite* spr = new v::Sprite(width, height);
		std::memcpy(spr->GetData(), GetData(), width * height * sizeof(v::Pixel));
		spr->modeSample = modeSample;
		return spr;
	}

	v::Sprite* Sprite::Duplicate(const v::vi2d& vPos, const v::vi2d& vSize)
	{
		v::Sprite* spr = new v::Sprite(vSize.x, vSize.y);
		for (int y = 0; y < vSize.y; y++)
			for (int x = 0; x < vSize.x; x++)
				spr->SetPixel(x, y, GetPixel(vPos.x + x, vPos.y + y));
		return spr;
	}

	v::vi2d v::Sprite::Size() const
	{
		return { width, height };
	}

	Decal::Decal(v::Sprite* spr, bool filter, bool clamp)
	{
		id = -1;
		if (spr == nullptr) return;
		sprite = spr;
		id = renderer->CreateTexture(sprite->width, sprite->height, filter, clamp);
		Update();
	}

	Decal::Decal(const uint32_t nExistingTextureResource, v::Sprite* spr)
	{
		if (spr == nullptr) return;
		id = nExistingTextureResource;
	}

	void Decal::Update()
	{
		if (sprite == nullptr) return;
		vUVScale = { 1.0f / float(sprite->width), 1.0f / float(sprite->height) };
		renderer->ApplyTexture(id);
		renderer->UpdateTexture(id, sprite);
	}

	void Decal::UpdateSprite()
	{
		if (sprite == nullptr) return;
		renderer->ApplyTexture(id);
		renderer->ReadTexture(id, sprite);
	}

	Decal::~Decal()
	{
		if (id != -1)
		{
			renderer->DeleteTexture(id);
			id = -1;
		}
	}

	void Renderable::Create(uint32_t width, uint32_t height, bool filter, bool clamp)
	{
		pSprite = std::make_unique<v::Sprite>(width, height);
		pDecal = std::make_unique<v::Decal>(pSprite.get(), filter, clamp);
	}

	v::rcode Renderable::Load(const std::string& sFile, ResourcePack* pack, bool filter, bool clamp)
	{
		pSprite = std::make_unique<v::Sprite>();
		if (pSprite->LoadFromFile(sFile, pack) == v::rcode::OK)
		{
			pDecal = std::make_unique<v::Decal>(pSprite.get(), filter, clamp);
			return v::rcode::OK;
		}
		else
		{
			pSprite.release();
			pSprite = nullptr;
			return v::rcode::NO_FILE;
		}
	}

	v::Decal* Renderable::Decal() const
	{ return pDecal.get(); }

	v::Sprite* Renderable::Sprite() const
	{ return pSprite.get(); }

	ResourceBuffer::ResourceBuffer(std::ifstream& ifs, uint32_t offset, uint32_t size)
	{
		vMemory.resize(size);
		ifs.seekg(offset); ifs.read(vMemory.data(), vMemory.size());
		setg(vMemory.data(), vMemory.data(), vMemory.data() + size);
	}

	ResourcePack::ResourcePack() { }
	ResourcePack::~ResourcePack() { baseFile.close(); }

	bool ResourcePack::AddFile(const std::string& sFile)
	{
		const std::string file = makeposix(sFile);

		if (_gfs::exists(file))
		{
			sResourceFile e;
			e.nSize = (uint32_t)_gfs::file_size(file);
			e.nOffset = 0; 
			mapFiles[file] = e;
			return true;
		}
		return false;
	}

	bool ResourcePack::LoadPack(const std::string& sFile, const std::string& sKey)
	{
		
		baseFile.open(sFile, std::ifstream::binary);
		if (!baseFile.is_open()) return false;

		uint32_t nIndexSize = 0;
		baseFile.read((char*)&nIndexSize, sizeof(uint32_t));

		std::vector<char> buffer(nIndexSize);
		for (uint32_t j = 0; j < nIndexSize; j++)
			buffer[j] = baseFile.get();

		std::vector<char> decoded = scramble(buffer, sKey);
		size_t pos = 0;
		auto read = [&decoded, &pos](char* dst, size_t size) {
			memcpy((void*)dst, (const void*)(decoded.data() + pos), size);
			pos += size;
		};

		auto get = [&read]() -> int { char c; read(&c, 1); return c; };

		uint32_t nMapEntries = 0;
		read((char*)&nMapEntries, sizeof(uint32_t));
		for (uint32_t i = 0; i < nMapEntries; i++)
		{
			uint32_t nFilePathSize = 0;
			read((char*)&nFilePathSize, sizeof(uint32_t));

			std::string sFileName(nFilePathSize, ' ');
			for (uint32_t j = 0; j < nFilePathSize; j++)
				sFileName[j] = get();

			sResourceFile e;
			read((char*)&e.nSize, sizeof(uint32_t));
			read((char*)&e.nOffset, sizeof(uint32_t));
			mapFiles[sFileName] = e;
		}

		return true;
	}

	bool ResourcePack::SavePack(const std::string& sFile, const std::string& sKey)
	{
		
		std::ofstream ofs(sFile, std::ofstream::binary);
		if (!ofs.is_open()) return false;

		uint32_t nIndexSize = 0; 
		ofs.write((char*)&nIndexSize, sizeof(uint32_t));
		uint32_t nMapSize = uint32_t(mapFiles.size());
		ofs.write((char*)&nMapSize, sizeof(uint32_t));
		for (auto& e : mapFiles)
		{
			
			size_t nPathSize = e.first.size();
			ofs.write((char*)&nPathSize, sizeof(uint32_t));
			ofs.write(e.first.c_str(), nPathSize);

			ofs.write((char*)&e.second.nSize, sizeof(uint32_t));
			ofs.write((char*)&e.second.nOffset, sizeof(uint32_t));
		}

		std::streampos offset = ofs.tellp();
		nIndexSize = (uint32_t)offset;
		for (auto& e : mapFiles)
		{
			
			e.second.nOffset = (uint32_t)offset;

			std::vector<uint8_t> vBuffer(e.second.nSize);
			std::ifstream i(e.first, std::ifstream::binary);
			i.read((char*)vBuffer.data(), e.second.nSize);
			i.close();

			ofs.write((char*)vBuffer.data(), e.second.nSize);
			offset += e.second.nSize;
		}

		std::vector<char> stream;
		auto write = [&stream](const char* data, size_t size) {
			size_t sizeNow = stream.size();
			stream.resize(sizeNow + size);
			memcpy(stream.data() + sizeNow, data, size);
		};

		write((char*)&nMapSize, sizeof(uint32_t));
		for (auto& e : mapFiles)
		{
			
			size_t nPathSize = e.first.size();
			write((char*)&nPathSize, sizeof(uint32_t));
			write(e.first.c_str(), nPathSize);

			write((char*)&e.second.nSize, sizeof(uint32_t));
			write((char*)&e.second.nOffset, sizeof(uint32_t));
		}
		std::vector<char> sIndexString = scramble(stream, sKey);
		uint32_t nIndexStringLen = uint32_t(sIndexString.size());

		ofs.seekp(0, std::ios::beg);
		ofs.write((char*)&nIndexStringLen, sizeof(uint32_t));
		ofs.write(sIndexString.data(), nIndexStringLen);
		ofs.close();
		return true;
	}

	ResourceBuffer ResourcePack::GetFileBuffer(const std::string& sFile)
	{ return ResourceBuffer(baseFile, mapFiles[sFile].nOffset, mapFiles[sFile].nSize); }

	bool ResourcePack::Loaded()
	{ return baseFile.is_open(); }

	std::vector<char> ResourcePack::scramble(const std::vector<char>& data, const std::string& key)
	{
		if (key.empty()) return data;
		std::vector<char> o;
		size_t c = 0;
		for (auto s : data)	o.push_back(s ^ key[(c++) % key.size()]);
		return o;
	};

	std::string ResourcePack::makeposix(const std::string& path)
	{
		std::string o;
		for (auto s : path) o += std::string(1, s == '\\' ? '/' : s);
		return o;
	};

	PixelGameEngine::PixelGameEngine()
	{
		sAppName = "Undefined";
		v::PGEX::pge = this;

		v_ConfigureSystem();
	}

	PixelGameEngine::~PixelGameEngine()
	{}

	v::rcode PixelGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync, bool cohesion)
	{
		bPixelCohesion = cohesion;
		vScreenSize = { screen_w, screen_h };
		vInvScreenSize = { 1.0f / float(screen_w), 1.0f / float(screen_h) };
		vPixelSize = { pixel_w, pixel_h };
		vWindowSize = vScreenSize * vPixelSize;
		bFullScreen = full_screen;
		bEnableVSYNC = vsync;
		vPixel = 2.0f / vScreenSize;

		if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
			return v::FAIL;
		return v::OK;
	}

	void PixelGameEngine::SetScreenSize(int w, int h)
	{
		vScreenSize = { w, h };
		vInvScreenSize = { 1.0f / float(w), 1.0f / float(h) };
		for (auto& layer : vLayers)
		{
			layer.pDrawTarget.Create(vScreenSize.x, vScreenSize.y);
			layer.bUpdate = true;
		}
		SetDrawTarget(nullptr);
		renderer->ClearBuffer(v::BLACK, true);
		renderer->DisplayFrame();
		renderer->ClearBuffer(v::BLACK, true);
		renderer->UpdateViewport(vViewPos, vViewSize);
	}

#if !defined(PGE_USE_CUSTOM_START)
	v::rcode PixelGameEngine::Start()
	{
		if (platform->ApplicationStartUp() != v::OK) return v::FAIL;

		if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != v::OK) return v::FAIL;
		v_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		bAtomActive = true;
		std::thread t = std::thread(&PixelGameEngine::EngineThread, this);

		platform->StartSystemEventLoop();

		t.join();

		if (platform->ApplicationCleanUp() != v::OK) return v::FAIL;

		return v::OK;
	}
#endif

	void PixelGameEngine::SetDrawTarget(Sprite* target)
	{
		if (target)
		{
			pDrawTarget = target;
		}
		else
		{
			nTargetLayer = 0;
			pDrawTarget = vLayers[0].pDrawTarget.Sprite();
		}
	}

	void PixelGameEngine::SetDrawTarget(uint8_t layer, bool bDirty)
	{
		if (layer < vLayers.size())
		{
			pDrawTarget = vLayers[layer].pDrawTarget.Sprite();
			vLayers[layer].bUpdate = bDirty;
			nTargetLayer = layer;
		}
	}

	void PixelGameEngine::EnableLayer(uint8_t layer, bool b)
	{ if (layer < vLayers.size()) vLayers[layer].bShow = b; }

	void PixelGameEngine::SetLayerOffset(uint8_t layer, const v::vf2d& offset)
	{ SetLayerOffset(layer, offset.x, offset.y); }

	void PixelGameEngine::SetLayerOffset(uint8_t layer, float x, float y)
	{ if (layer < vLayers.size()) vLayers[layer].vOffset = { x, y }; }

	void PixelGameEngine::SetLayerScale(uint8_t layer, const v::vf2d& scale)
	{ SetLayerScale(layer, scale.x, scale.y); }

	void PixelGameEngine::SetLayerScale(uint8_t layer, float x, float y)
	{ if (layer < vLayers.size()) vLayers[layer].vScale = { x, y }; }

	void PixelGameEngine::SetLayerTint(uint8_t layer, const v::Pixel& tint)
	{ if (layer < vLayers.size()) vLayers[layer].tint = tint; }

	void PixelGameEngine::SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f)
	{ if (layer < vLayers.size()) vLayers[layer].funcHook = f; }

	std::vector<LayerDesc>& PixelGameEngine::GetLayers()
	{ return vLayers; }

	uint32_t PixelGameEngine::CreateLayer()
	{
		LayerDesc ld;
		ld.pDrawTarget.Create(vScreenSize.x, vScreenSize.y);
		vLayers.push_back(std::move(ld));
		return uint32_t(vLayers.size()) - 1;
	}

	Sprite* PixelGameEngine::GetDrawTarget() const
	{ return pDrawTarget; }

	int32_t PixelGameEngine::GetDrawTargetWidth() const
	{
		if (pDrawTarget)
			return pDrawTarget->width;
		else
			return 0;
	}

	int32_t PixelGameEngine::GetDrawTargetHeight() const
	{
		if (pDrawTarget)
			return pDrawTarget->height;
		else
			return 0;
	}

	uint32_t PixelGameEngine::GetFPS() const
	{ return nLastFPS; }

	bool PixelGameEngine::IsFocused() const
	{ return bHasInputFocus; }

	HWButton PixelGameEngine::GetKey(Key k) const
	{ return pKeyboardState[k];	}

	HWButton PixelGameEngine::GetMouse(uint32_t b) const
	{ return pMouseState[b]; }

	int32_t PixelGameEngine::GetMouseX() const
	{ return vMousePos.x; }

	int32_t PixelGameEngine::GetMouseY() const
	{ return vMousePos.y; }

	const v::vi2d& PixelGameEngine::GetMousePos() const
	{ return vMousePos; }

	int32_t PixelGameEngine::GetMouseWheel() const
	{ return nMouseWheelDelta; }

	int32_t PixelGameEngine::ScreenWidth() const
	{ return vScreenSize.x; }

	int32_t PixelGameEngine::ScreenHeight() const
	{ return vScreenSize.y; }

	float PixelGameEngine::GetElapsedTime() const
	{ return fLastElapsed; }

	const v::vi2d& PixelGameEngine::GetWindowSize() const
	{ return vWindowSize; }

	const v::vi2d& PixelGameEngine::GetPixelSize() const
	{ return vPixelSize; }

	const v::vi2d& PixelGameEngine::GetScreenPixelSize() const
	{ return vScreenPixelSize; }

	const v::vi2d& PixelGameEngine::GetScreenSize() const
	{ return vScreenSize;	}

	const v::vi2d& PixelGameEngine::GetWindowMouse() const
	{ return vMouseWindowPos; }

	bool PixelGameEngine::Draw(const v::vi2d& pos, Pixel p)
	{ return Draw(pos.x, pos.y, p); }

	bool PixelGameEngine::Draw(int32_t x, int32_t y, Pixel p)
	{
		if (!pDrawTarget) return false;

		if (nPixelMode == Pixel::NORMAL)
		{
			return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::MASK)
		{
			if (p.a == 255)
				return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::ALPHA)
		{
			Pixel d = pDrawTarget->GetPixel(x, y);
			float a = (float)(p.a / 255.0f) * fBlendFactor;
			float c = 1.0f - a;
			float r = a * (float)p.r + c * (float)d.r;
			float g = a * (float)p.g + c * (float)d.g;
			float b = a * (float)p.b + c * (float)d.b;
			return pDrawTarget->SetPixel(x, y, Pixel((uint8_t)r, (uint8_t)g, (uint8_t)b));
		}

		if (nPixelMode == Pixel::CUSTOM)
		{
			return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, p, pDrawTarget->GetPixel(x, y)));
		}

		return false;
	}

	void PixelGameEngine::DrawLine(const v::vi2d& pos1, const v::vi2d& pos2, Pixel p, uint32_t pattern)
	{ DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, p, pattern); }

	void PixelGameEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p, uint32_t pattern)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1; dy = y2 - y1;

		auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };

		v::vi2d p1(x1, y1), p2(x2, y2);

		x1 = p1.x; y1 = p1.y;
		x2 = p2.x; y2 = p2.y;

		if (dx == 0) 
		{
			if (y2 < y1) std::swap(y1, y2);
			for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, p);
			return;
		}

		if (dy == 0) 
		{
			if (x2 < x1) std::swap(x1, x2);
			for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, p);
			return;
		}

		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
	}

	void PixelGameEngine::DrawCircle(const v::vi2d& pos, int32_t radius, Pixel p, uint8_t mask)
	{ DrawCircle(pos.x, pos.y, radius, p, mask); }

	void PixelGameEngine::DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p, uint8_t mask)
	{ 
		if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius)
			return;

		if (radius > 0)
		{
			int x0 = 0;
			int y0 = radius;
			int d = 3 - 2 * radius;

			while (y0 >= x0) 
			{
				
				if (mask & 0x01) Draw(x + x0, y - y0, p);
				if (mask & 0x04) Draw(x + y0, y + x0, p);
				if (mask & 0x10) Draw(x - x0, y + y0, p);
				if (mask & 0x40) Draw(x - y0, y - x0, p);
				if (x0 != 0 && x0 != y0)
				{
					if (mask & 0x02) Draw(x + y0, y - x0, p);
					if (mask & 0x08) Draw(x + x0, y + y0, p);
					if (mask & 0x20) Draw(x - y0, y + x0, p);
					if (mask & 0x80) Draw(x - x0, y - y0, p);
				}

				if (d < 0)
					d += 4 * x0++ + 6;
				else
					d += 4 * (x0++ - y0--) + 10;
			}
		}
		else
			Draw(x, y, p);
	}

	void PixelGameEngine::FillCircle(const v::vi2d& pos, int32_t radius, Pixel p)
	{ FillCircle(pos.x, pos.y, radius, p); }

	void PixelGameEngine::FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p)
	{ 
		if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius)
			return;

		if (radius > 0)
		{
			int x0 = 0;
			int y0 = radius;
			int d = 3 - 2 * radius;

			auto drawline = [&](int sx, int ex, int y)
			{
				for (int x = sx; x <= ex; x++)
					Draw(x, y, p);
			};

			while (y0 >= x0)
			{
				drawline(x - y0, x + y0, y - x0);
				if (x0 > 0)	drawline(x - y0, x + y0, y + x0);

				if (d < 0)
					d += 4 * x0++ + 6;
				else
				{
					if (x0 != y0)
					{
						drawline(x - x0, x + x0, y - y0);
						drawline(x - x0, x + x0, y + y0);
					}
					d += 4 * (x0++ - y0--) + 10;
				}
			}
		}
		else
			Draw(x, y, p);
	}

	void PixelGameEngine::DrawRect(const v::vi2d& pos, const v::vi2d& size, Pixel p)
	{ DrawRect(pos.x, pos.y, size.x, size.y, p); }

	void PixelGameEngine::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		DrawLine(x, y, x + w, y, p);
		DrawLine(x + w, y, x + w, y + h, p);
		DrawLine(x + w, y + h, x, y + h, p);
		DrawLine(x, y + h, x, y, p);
	}

	void PixelGameEngine::Clear(Pixel p)
	{
		int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
		Pixel* m = GetDrawTarget()->GetData();
		for (int i = 0; i < pixels; i++) m[i] = p;
	}

	void PixelGameEngine::ClearBuffer(Pixel p, bool bDepth)
	{ renderer->ClearBuffer(p, bDepth);	}

	v::Sprite* PixelGameEngine::GetFontSprite()
	{ return fontRenderable.Sprite(); }

	bool PixelGameEngine::ClipLineToScreen(v::vi2d& in_p1, v::vi2d& in_p2)
	{
		
		static constexpr int SEG_I = 0b0000, SEG_L = 0b0001, SEG_R = 0b0010, SEG_B = 0b0100, SEG_T = 0b1000;
		auto Segment = [&vScreenSize = vScreenSize](const v::vi2d& v)
		{
			int i = SEG_I;
			if (v.x < 0) i |= SEG_L; else if (v.x > vScreenSize.x) i |= SEG_R;
			if (v.y < 0) i |= SEG_B; else if (v.y > vScreenSize.y) i |= SEG_T;
			return i;
		};

		int s1 = Segment(in_p1), s2 = Segment(in_p2);

		while (true)
		{
			if (!(s1 | s2))	  return true;
			else if (s1 & s2) return false;
			else
			{
				int s3 = s2 > s1 ? s2 : s1;
				v::vi2d n;
				if (s3 & SEG_T) { n.x = in_p1.x + (in_p2.x - in_p1.x) * (vScreenSize.y - in_p1.y) / (in_p2.y - in_p1.y); n.y = vScreenSize.y; }
				else if (s3 & SEG_B) { n.x = in_p1.x + (in_p2.x - in_p1.x) * (0 - in_p1.y) / (in_p2.y - in_p1.y); n.y = 0; }
				else if (s3 & SEG_R) { n.x = vScreenSize.x; n.y = in_p1.y + (in_p2.y - in_p1.y) * (vScreenSize.x - in_p1.x) / (in_p2.x - in_p1.x); }
				else if (s3 & SEG_L) { n.x = 0; n.y = in_p1.y + (in_p2.y - in_p1.y) * (0 - in_p1.x) / (in_p2.x - in_p1.x); }
				if (s3 == s1) { in_p1 = n; s1 = Segment(in_p1); }
				else { in_p2 = n; s2 = Segment(in_p2); }
			}
		}
		return true;
	}

	void PixelGameEngine::EnablePixelTransfer(const bool bEnable)
	{
		bSuspendTextureTransfer = !bEnable;
	}

	void PixelGameEngine::FillRect(const v::vi2d& pos, const v::vi2d& size, Pixel p)
	{ FillRect(pos.x, pos.y, size.x, size.y, p); }

	void PixelGameEngine::FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		int32_t x2 = x + w;
		int32_t y2 = y + h;

		if (x < 0) x = 0;
		if (x >= (int32_t)GetDrawTargetWidth()) x = (int32_t)GetDrawTargetWidth();
		if (y < 0) y = 0;
		if (y >= (int32_t)GetDrawTargetHeight()) y = (int32_t)GetDrawTargetHeight();

		if (x2 < 0) x2 = 0;
		if (x2 >= (int32_t)GetDrawTargetWidth()) x2 = (int32_t)GetDrawTargetWidth();
		if (y2 < 0) y2 = 0;
		if (y2 >= (int32_t)GetDrawTargetHeight()) y2 = (int32_t)GetDrawTargetHeight();

		for (int i = x; i < x2; i++)
			for (int j = y; j < y2; j++)
				Draw(i, j, p);
	}

	void PixelGameEngine::DrawTriangle(const v::vi2d& pos1, const v::vi2d& pos2, const v::vi2d& pos3, Pixel p)
	{ DrawTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p); }

	void PixelGameEngine::DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		DrawLine(x1, y1, x2, y2, p);
		DrawLine(x2, y2, x3, y3, p);
		DrawLine(x3, y3, x1, y1, p);
	}

	void PixelGameEngine::FillTriangle(const v::vi2d& pos1, const v::vi2d& pos2, const v::vi2d& pos3, Pixel p)
	{ FillTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p); }

	void PixelGameEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw(i, ny, p); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		
		if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
		if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
		if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

		t1x = t2x = x1; y = y1;   
		dx1 = (int)(x2 - x1);
		if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1);
		if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
		if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

		e2 = (int)(dx2 >> 1);
		
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			
		next1:
			
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);    
										
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;
		}
	next:
		
		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   
			std::swap(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}

	void PixelGameEngine::FillTexturedTriangle(const std::vector<v::vf2d>& vPoints, std::vector<v::vf2d> vTex, std::vector<v::Pixel> vColour, v::Sprite* sprTex)
	{
		v::vi2d p1 = vPoints[0];
		v::vi2d p2 = vPoints[1];
		v::vi2d p3 = vPoints[2];

		if (p2.y < p1.y){std::swap(p1.y, p2.y); std::swap(p1.x, p2.x); std::swap(vTex[0].x, vTex[1].x); std::swap(vTex[0].y, vTex[1].y); std::swap(vColour[0], vColour[1]);}
		if (p3.y < p1.y){std::swap(p1.y, p3.y); std::swap(p1.x, p3.x); std::swap(vTex[0].x, vTex[2].x); std::swap(vTex[0].y, vTex[2].y); std::swap(vColour[0], vColour[2]);}
		if (p3.y < p2.y){std::swap(p2.y, p3.y); std::swap(p2.x, p3.x); std::swap(vTex[1].x, vTex[2].x); std::swap(vTex[1].y, vTex[2].y); std::swap(vColour[1], vColour[2]);}

		v::vi2d dPos1 = p2 - p1;
		v::vf2d dTex1 = vTex[1] - vTex[0];
		int dcr1 = vColour[1].r - vColour[0].r;
		int dcg1 = vColour[1].g - vColour[0].g;
		int dcb1 = vColour[1].b - vColour[0].b;
		int dca1 = vColour[1].a - vColour[0].a;

		v::vi2d dPos2 = p3 - p1;
		v::vf2d dTex2 = vTex[2] - vTex[0];
		int dcr2 = vColour[2].r - vColour[0].r;
		int dcg2 = vColour[2].g - vColour[0].g;
		int dcb2 = vColour[2].b - vColour[0].b;
		int dca2 = vColour[2].a - vColour[0].a;

		float dax_step = 0, dbx_step = 0, dcr1_step = 0, dcr2_step = 0,	dcg1_step = 0, dcg2_step = 0, dcb1_step = 0, dcb2_step = 0,	dca1_step = 0, dca2_step = 0;
		v::vf2d vTex1Step, vTex2Step;

		if (dPos1.y)
		{
			dax_step = dPos1.x / (float)abs(dPos1.y);
			vTex1Step = dTex1 / (float)abs(dPos1.y);
			dcr1_step = dcr1 / (float)abs(dPos1.y);
			dcg1_step = dcg1 / (float)abs(dPos1.y);
			dcb1_step = dcb1 / (float)abs(dPos1.y);
			dca1_step = dca1 / (float)abs(dPos1.y);
		}

		if (dPos2.y)
		{
			dbx_step = dPos2.x / (float)abs(dPos2.y);
			vTex2Step = dTex2 / (float)abs(dPos2.y);
			dcr2_step = dcr2 / (float)abs(dPos2.y);
			dcg2_step = dcg2 / (float)abs(dPos2.y);
			dcb2_step = dcb2 / (float)abs(dPos2.y);
			dca2_step = dca2 / (float)abs(dPos2.y);
		}

		v::vi2d vStart;
		v::vi2d vEnd;
		int vStartIdx;

		for (int pass = 0; pass < 2; pass++)
		{
			if (pass == 0)
			{
				vStart = p1; vEnd = p2;	vStartIdx = 0;
			}
			else
			{
				dPos1 = p3 - p2;
				dTex1 = vTex[2] - vTex[1];
				dcr1 = vColour[2].r - vColour[1].r;
				dcg1 = vColour[2].g - vColour[1].g;
				dcb1 = vColour[2].b - vColour[1].b;
				dca1 = vColour[2].a - vColour[1].a;
				dcr1_step = 0; dcg1_step = 0; dcb1_step = 0; dca1_step = 0;

				if (dPos2.y) dbx_step = dPos2.x / (float)abs(dPos2.y);
				if (dPos1.y)
				{
					dax_step = dPos1.x / (float)abs(dPos1.y);
					vTex1Step = dTex1 / (float)abs(dPos1.y);
					dcr1_step = dcr1 / (float)abs(dPos1.y);
					dcg1_step = dcg1 / (float)abs(dPos1.y);
					dcb1_step = dcb1 / (float)abs(dPos1.y);
					dca1_step = dca1 / (float)abs(dPos1.y);
				}

				vStart = p2; vEnd = p3; vStartIdx = 1;
			}

			if (dPos1.y)
			{
				for (int i = vStart.y; i <= vEnd.y; i++)
				{
					int ax = int(vStart.x + (float)(i - vStart.y) * dax_step);
					int bx = int(p1.x + (float)(i - p1.y) * dbx_step);

					v::vf2d tex_s(vTex[vStartIdx].x + (float)(i - vStart.y) * vTex1Step.x, vTex[vStartIdx].y + (float)(i - vStart.y) * vTex1Step.y);
					v::vf2d tex_e(vTex[0].x + (float)(i - p1.y) * vTex2Step.x, vTex[0].y + (float)(i - p1.y) * vTex2Step.y);

					v::Pixel col_s(vColour[vStartIdx].r + uint8_t((float)(i - vStart.y) * dcr1_step), vColour[vStartIdx].g + uint8_t((float)(i - vStart.y) * dcg1_step),
						vColour[vStartIdx].b + uint8_t((float)(i - vStart.y) * dcb1_step), vColour[vStartIdx].a + uint8_t((float)(i - vStart.y) * dca1_step));

					v::Pixel col_e(vColour[0].r + uint8_t((float)(i - p1.y) * dcr2_step), vColour[0].g + uint8_t((float)(i - p1.y) * dcg2_step),
						vColour[0].b + uint8_t((float)(i - p1.y) * dcb2_step), vColour[0].a + uint8_t((float)(i - p1.y) * dca2_step));

					if (ax > bx) { std::swap(ax, bx); std::swap(tex_s, tex_e); std::swap(col_s, col_e); }

					float tstep = 1.0f / ((float)(bx - ax));
					float t = 0.0f;

					for (int j = ax; j < bx; j++)
					{
						v::Pixel pixel = PixelLerp(col_s, col_e, t);
						if (sprTex != nullptr) pixel *= sprTex->Sample(tex_s.lerp(tex_e, t));
						Draw(j, i, pixel);
						t += tstep;
					}
				}
			}
		}			
	}

	void PixelGameEngine::FillTexturedPolygon(const std::vector<v::vf2d>& vPoints, const std::vector<v::vf2d>& vTex, const std::vector<v::Pixel>& vColour, v::Sprite* sprTex, v::DecalStructure structure)
	{
		if (structure == v::DecalStructure::LINE)
		{
			return; 
		}

		if (vPoints.size() < 3 || vTex.size() < 3 || vColour.size() < 3)
			return;

		if (structure == v::DecalStructure::LIST)
		{			
			for (int tri = 0; tri < vPoints.size() / 3; tri++)
			{
				std::vector<v::vf2d> vP = { vPoints[tri * 3 + 0], vPoints[tri * 3 + 1], vPoints[tri * 3 + 2] };
				std::vector<v::vf2d> vT = { vTex[tri * 3 + 0], vTex[tri * 3 + 1], vTex[tri * 3 + 2] };
				std::vector<v::Pixel> vC = { vColour[tri * 3 + 0], vColour[tri * 3 + 1], vColour[tri * 3 + 2] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}

		if (structure == v::DecalStructure::STRIP)
		{
			for (int tri = 2; tri < vPoints.size(); tri++)
			{
				std::vector<v::vf2d> vP = { vPoints[tri - 2], vPoints[tri-1], vPoints[tri] };
				std::vector<v::vf2d> vT = { vTex[tri - 2], vTex[tri - 1], vTex[tri] };
				std::vector<v::Pixel> vC = { vColour[tri - 2], vColour[tri - 1], vColour[tri] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}

		if (structure == v::DecalStructure::FAN)
		{
			for (int tri = 2; tri < vPoints.size(); tri++)
			{
				std::vector<v::vf2d> vP = { vPoints[0], vPoints[tri - 1], vPoints[tri] };
				std::vector<v::vf2d> vT = { vTex[0], vTex[tri - 1], vTex[tri] };
				std::vector<v::Pixel> vC = { vColour[0], vColour[tri - 1], vColour[tri] };
				FillTexturedTriangle(vP, vT, vC, sprTex);
			}
			return;
		}
	}

	void PixelGameEngine::DrawSprite(const v::vi2d& pos, Sprite* sprite, uint32_t scale, uint8_t flip)
	{ DrawSprite(pos.x, pos.y, sprite, scale, flip); }

	void PixelGameEngine::DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip)
	{
		if (sprite == nullptr)
			return;

		int32_t fxs = 0, fxm = 1, fx = 0;
		int32_t fys = 0, fym = 1, fy = 0;
		if (flip & v::Sprite::Flip::HORIZ) { fxs = sprite->width - 1; fxm = -1; }
		if (flip & v::Sprite::Flip::VERT) { fys = sprite->height - 1; fym = -1; }

		if (scale > 1)
		{
			fx = fxs;
			for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < sprite->height; j++, fy += fym)
					for (uint32_t is = 0; is < scale; is++)
						for (uint32_t js = 0; js < scale; js++)
							Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx, fy));
			}
		}
		else
		{
			fx = fxs;
			for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < sprite->height; j++, fy += fym)
					Draw(x + i, y + j, sprite->GetPixel(fx, fy));
			}
		}
	}

	void PixelGameEngine::DrawPartialSprite(const v::vi2d& pos, Sprite* sprite, const v::vi2d& sourcepos, const v::vi2d& size, uint32_t scale, uint8_t flip)
	{ DrawPartialSprite(pos.x, pos.y, sprite, sourcepos.x, sourcepos.y, size.x, size.y, scale, flip); }

	void PixelGameEngine::DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip)
	{
		if (sprite == nullptr)
			return;

		int32_t fxs = 0, fxm = 1, fx = 0;
		int32_t fys = 0, fym = 1, fy = 0;
		if (flip & v::Sprite::Flip::HORIZ) { fxs = w - 1; fxm = -1; }
		if (flip & v::Sprite::Flip::VERT) { fys = h - 1; fym = -1; }

		if (scale > 1)
		{
			fx = fxs;
			for (int32_t i = 0; i < w; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < h; j++, fy += fym)
					for (uint32_t is = 0; is < scale; is++)
						for (uint32_t js = 0; js < scale; js++)
							Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx + ox, fy + oy));
			}
		}
		else
		{
			fx = fxs;
			for (int32_t i = 0; i < w; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < h; j++, fy += fym)
					Draw(x + i, y + j, sprite->GetPixel(fx + ox, fy + oy));
			}
		}
	}

	void PixelGameEngine::SetDecalMode(const v::DecalMode& mode)
	{ nDecalMode = mode; }

	void PixelGameEngine::SetDecalStructure(const v::DecalStructure& structure)
	{ nDecalStructure = structure; }

	void PixelGameEngine::DrawPartialDecal(const v::vf2d& pos, v::Decal* decal, const v::vf2d& source_pos, const v::vf2d& source_size, const v::vf2d& scale, const v::Pixel& tint)
	{
		v::vf2d vScreenSpacePos =
		{
			  (pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			-((pos.y * vInvScreenSize.y) * 2.0f - 1.0f)
		};

		v::vf2d vScreenSpaceDim =
		{
			  ((pos.x + source_size.x * scale.x) * vInvScreenSize.x) * 2.0f - 1.0f,
			-(((pos.y + source_size.y * scale.y) * vInvScreenSize.y) * 2.0f - 1.0f)
		};

		v::vf2d vWindow = v::vf2d(vViewSize);
		v::vf2d vQuantisedPos = ((vScreenSpacePos * vWindow) + v::vf2d(0.5f, 0.5f)).floor() / vWindow;
		v::vf2d vQuantisedDim = ((vScreenSpaceDim * vWindow) + v::vf2d(0.5f, -0.5f)).ceil() / vWindow;

		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vQuantisedPos.x, vQuantisedPos.y }, { vQuantisedPos.x, vQuantisedDim.y }, { vQuantisedDim.x, vQuantisedDim.y }, { vQuantisedDim.x, vQuantisedPos.y } };
		v::vf2d uvtl = (source_pos + v::vf2d(0.0001f, 0.0001f)) * decal->vUVScale;
		v::vf2d uvbr = (source_pos + source_size - v::vf2d(0.0001f, 0.0001f)) * decal->vUVScale;
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.w = { 1,1,1,1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialDecal(const v::vf2d& pos, const v::vf2d& size, v::Decal* decal, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint)
	{
		v::vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		v::vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * size.x * vInvScreenSize.x),
			vScreenSpacePos.y - (2.0f * size.y * vInvScreenSize.y)
		};

		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vScreenSpacePos.x, vScreenSpacePos.y }, { vScreenSpacePos.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpacePos.y } };
		v::vf2d uvtl = (source_pos) * decal->vUVScale;
		v::vf2d uvbr = uvtl + ((source_size) * decal->vUVScale);
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.w = { 1,1,1,1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawDecal(const v::vf2d& pos, v::Decal* decal, const v::vf2d& scale, const v::Pixel& tint)
	{
		v::vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		v::vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * (float(decal->sprite->width) * vInvScreenSize.x)) * scale.x,
			vScreenSpacePos.y - (2.0f * (float(decal->sprite->height) * vInvScreenSize.y)) * scale.y
		};

		DecalInstance di;
		di.decal = decal;
		di.points = 4;
		di.tint = { tint, tint, tint, tint };
		di.pos = { { vScreenSpacePos.x, vScreenSpacePos.y }, { vScreenSpacePos.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpaceDim.y }, { vScreenSpaceDim.x, vScreenSpacePos.y } };
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		di.w = { 1, 1, 1, 1 };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawExplicitDecal(v::Decal* decal, const v::vf2d* pos, const v::vf2d* uv, const v::Pixel* col, uint32_t elements)
	{
		DecalInstance di;
		di.decal = decal;
		di.pos.resize(elements);
		di.uv.resize(elements);
		di.w.resize(elements);
		di.tint.resize(elements);
		di.points = elements;
		for (uint32_t i = 0; i < elements; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = col[i];
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const v::Pixel tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint;
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const std::vector<v::Pixel> &tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint[i];
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<v::vf2d>& uv, const std::vector<v::Pixel>& colours, const v::Pixel tint)
	{
		std::vector<v::Pixel> newColours(colours.size(), v::WHITE);
		std::transform(colours.begin(), colours.end(), newColours.begin(),
			[&tint](const v::Pixel pin) {	return pin * tint; });
		DrawPolygonDecal(decal, pos, uv, newColours);
	}

	void PixelGameEngine::DrawPolygonDecal(v::Decal* decal, const std::vector<v::vf2d>& pos, const std::vector<float>& depth, const std::vector<v::vf2d>& uv, const v::Pixel tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			di.uv[i] = uv[i];
			di.tint[i] = tint;
			di.w[i] = 1.0f;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

#ifdef v_ENABLE_EXPERIMENTAL
	
	void PixelGameEngine::LW3D_DrawTriangles(v::Decal* decal, const std::vector<std::array<float, 3>>& pos, const std::vector<v::vf2d>& tex, const std::vector<v::Pixel>& col)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = uint32_t(pos.size());
		di.pos.resize(di.points);
		di.uv.resize(di.points);
		di.w.resize(di.points);
		di.tint.resize(di.points);
		for (uint32_t i = 0; i < di.points; i++)
		{
			di.pos[i] = { pos[i][0], pos[i][1] };
			di.w[i] = pos[i][2];
			di.uv[i] = tex[i];
			di.tint[i] = col[i];			
		}
		di.mode = DecalMode::MODEL3D;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}
#endif

	void PixelGameEngine::DrawLineDecal(const v::vf2d& pos1, const v::vf2d& pos2, Pixel p)
	{
		auto m = nDecalMode;
		nDecalMode = v::DecalMode::WIREFRAME;
		DrawPolygonDecal(nullptr, { pos1, pos2 }, { {0, 0}, {0,0} }, p);
		nDecalMode = m;

	}

	void PixelGameEngine::DrawRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel col)
	{
		auto m = nDecalMode;
		SetDecalMode(v::DecalMode::WIREFRAME);
		v::vf2d vNewSize = size;
		std::array<v::vf2d, 4> points = { { {pos}, {pos.x, pos.y + vNewSize.y}, {pos + vNewSize}, {pos.x + vNewSize.x, pos.y} } };
		std::array<v::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<v::Pixel, 4> cols = { {col, col, col, col} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
		SetDecalMode(m);

	}

	void PixelGameEngine::FillRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel col)
	{
		v::vf2d vNewSize = size;
		std::array<v::vf2d, 4> points = { { {pos}, {pos.x, pos.y + vNewSize.y}, {pos + vNewSize}, {pos.x + vNewSize.x, pos.y} } };
		std::array<v::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<v::Pixel, 4> cols = { {col, col, col, col} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
	}

	void PixelGameEngine::GradientFillRectDecal(const v::vf2d& pos, const v::vf2d& size, const v::Pixel colTL, const v::Pixel colBL, const v::Pixel colBR, const v::Pixel colTR)
	{
		std::array<v::vf2d, 4> points = { { {pos}, {pos.x, pos.y + size.y}, {pos + size}, {pos.x + size.x, pos.y} } };
		std::array<v::vf2d, 4> uvs = { {{0,0},{0,0},{0,0},{0,0}} };
		std::array<v::Pixel, 4> cols = { {colTL, colBL, colBR, colTR} };
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data(), 4);
	}

	void PixelGameEngine::DrawRotatedDecal(const v::vf2d& pos, v::Decal* decal, const float fAngle, const v::vf2d& center, const v::vf2d& scale, const v::Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		di.w = { 1, 1, 1, 1 };
		di.tint = { tint, tint, tint, tint };
		di.points = 4;
		di.pos[0] = (v::vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (v::vf2d(0.0f, float(decal->sprite->height)) - center) * scale;
		di.pos[2] = (v::vf2d(float(decal->sprite->width), float(decal->sprite->height)) - center) * scale;
		di.pos[3] = (v::vf2d(float(decal->sprite->width), 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + v::vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - v::vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
			di.w[i] = 1;
		}
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialRotatedDecal(const v::vf2d& pos, v::Decal* decal, const float fAngle, const v::vf2d& center, const v::vf2d& source_pos, const v::vf2d& source_size, const v::vf2d& scale, const v::Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.points = 4;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.pos[0] = (v::vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (v::vf2d(0.0f, source_size.y) - center) * scale;
		di.pos[2] = (v::vf2d(source_size.x, source_size.y) - center) * scale;
		di.pos[3] = (v::vf2d(source_size.x, 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + v::vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - v::vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
		}

		v::vf2d uvtl = source_pos * decal->vUVScale;
		v::vf2d uvbr = uvtl + (source_size * decal->vUVScale);
		di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };
		di.mode = nDecalMode;
		di.structure = nDecalStructure;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(v::Decal* decal, const v::vf2d* pos, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint)
	{
		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		v::vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			v::vf2d uvtl = source_pos * decal->vUVScale;
			v::vf2d uvbr = uvtl + (source_size * decal->vUVScale);
			di.uv = { { uvtl.x, uvtl.y }, { uvtl.x, uvbr.y }, { uvbr.x, uvbr.y }, { uvbr.x, uvtl.y } };

			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];	for (int i = 0; i < 4; i++)	d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q; di.w[i] *= q;
				di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			}
			di.mode = nDecalMode;
			di.structure = nDecalStructure;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(v::Decal* decal, const v::vf2d* pos, const v::Pixel& tint)
	{

		DecalInstance di;
		di.points = 4;
		di.decal = decal;
		di.tint = { tint, tint, tint, tint };
		di.w = { 1, 1, 1, 1 };
		di.pos.resize(4);
		di.uv = { { 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} };
		v::vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];	for (int i = 0; i < 4; i++)	d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q; di.w[i] *= q;
				di.pos[i] = { (pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f };
			}
			di.mode = nDecalMode;
			di.structure = nDecalStructure;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(v::Decal* decal, const std::array<v::vf2d, 4>& pos, const v::Pixel& tint)
	{ DrawWarpedDecal(decal, pos.data(), tint); }

	void PixelGameEngine::DrawWarpedDecal(v::Decal* decal, const v::vf2d(&pos)[4], const v::Pixel& tint)
	{ DrawWarpedDecal(decal, &pos[0], tint); }

	void PixelGameEngine::DrawPartialWarpedDecal(v::Decal* decal, const std::array<v::vf2d, 4>& pos, const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint)
	{ DrawPartialWarpedDecal(decal, pos.data(), source_pos, source_size, tint); }

	void PixelGameEngine::DrawPartialWarpedDecal(v::Decal* decal, const v::vf2d(&pos)[4], const v::vf2d& source_pos, const v::vf2d& source_size, const v::Pixel& tint)
	{ DrawPartialWarpedDecal(decal, &pos[0], source_pos, source_size, tint); }

	void PixelGameEngine::DrawStringDecal(const v::vf2d& pos, const std::string& sText, const Pixel col, const v::vf2d& scale)
	{
		v::vf2d spos = { 0.0f, 0.0f };
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0; spos.y += 8.0f * scale.y;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontRenderable.Decal(), {float(ox) * 8.0f, float(oy) * 8.0f}, {8.0f, 8.0f}, scale, col);
				spos.x += 8.0f * scale.x;
			}
		}
	}

	void PixelGameEngine::DrawStringPropDecal(const v::vf2d& pos, const std::string& sText, const Pixel col, const v::vf2d& scale)
	{
		v::vf2d spos = { 0.0f, 0.0f };
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0; spos.y += 8.0f * scale.y;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontRenderable.Decal(), { float(ox) * 8.0f + float(vFontSpacing[c - 32].x), float(oy) * 8.0f }, { float(vFontSpacing[c - 32].y), 8.0f }, scale, col);
				spos.x += float(vFontSpacing[c - 32].y) * scale.x;
			}
		}
	}
	
	void PixelGameEngine::DrawRotatedStringDecal(const v::vf2d& pos, const std::string& sText, const float fAngle, const v::vf2d& center, const Pixel col, const v::vf2d& scale)
	{
		v::vf2d spos = center;
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = center.x; spos.y -= 8.0f;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialRotatedDecal(pos, fontRenderable.Decal(), fAngle, spos, { float(ox) * 8.0f, float(oy) * 8.0f }, { 8.0f, 8.0f }, scale, col);
				spos.x -= 8.0f;
			}
		}
	}

	void PixelGameEngine::DrawRotatedStringPropDecal(const v::vf2d& pos, const std::string& sText, const float fAngle, const v::vf2d& center, const Pixel col, const v::vf2d& scale)
	{
		v::vf2d spos = center;
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = center.x; spos.y -= 8.0f;
			}
			else if (c == '\t')
			{
				spos.x += 8.0f * float(nTabSizeInSpaces) * scale.x;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialRotatedDecal(pos, fontRenderable.Decal(), fAngle, spos, { float(ox) * 8.0f + float(vFontSpacing[c - 32].x), float(oy) * 8.0f }, { float(vFontSpacing[c - 32].y), 8.0f }, scale, col);
				spos.x -= float(vFontSpacing[c - 32].y);
			}
		}
	}

	v::vi2d PixelGameEngine::GetTextSize(const std::string& s)
	{
		v::vi2d size = { 0,1 };
		v::vi2d pos = { 0,1 };
		for (auto c : s)
		{
			if (c == '\n') { pos.y++;  pos.x = 0; }
			else if (c == '\t') { pos.x += nTabSizeInSpaces; }
			else pos.x++;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}
		return size * 8;
	}

	void PixelGameEngine::DrawString(const v::vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{ DrawString(pos.x, pos.y, sText, col, scale); }

	void PixelGameEngine::DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;
		
		if (m != Pixel::CUSTOM) 
		{
			if (col.a != 255)		SetPixelMode(Pixel::ALPHA);
			else					SetPixelMode(Pixel::MASK);
		}
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0; sy += 8 * scale;
			}
			else if (c == '\t')
			{
				sx += 8 * nTabSizeInSpaces * scale;
			}
			else			
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								for (uint32_t is = 0; is < scale; is++)
									for (uint32_t js = 0; js < scale; js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += 8 * scale;
			}
		}
		SetPixelMode(m);
	}

	v::vi2d PixelGameEngine::GetTextSizeProp(const std::string& s)
	{
		v::vi2d size = { 0,1 };
		v::vi2d pos = { 0,1 };
		for (auto c : s)
		{
			if (c == '\n') { pos.y += 1;  pos.x = 0; }
			else if (c == '\t') { pos.x += nTabSizeInSpaces * 8; }
			else pos.x += vFontSpacing[c - 32].y;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}

		size.y *= 8;
		return size;
	}

	void PixelGameEngine::DrawStringProp(const v::vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{ DrawStringProp(pos.x, pos.y, sText, col, scale); }

	void PixelGameEngine::DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;

		if (m != Pixel::CUSTOM)
		{
			if (col.a != 255)		SetPixelMode(Pixel::ALPHA);
			else					SetPixelMode(Pixel::MASK);
		}
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0; sy += 8 * scale;
			}
			else if (c == '\t')
			{
				sx += 8 * nTabSizeInSpaces * scale;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								for (int32_t is = 0; is < int(scale); is++)
									for (int32_t js = 0; js < int(scale); js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontRenderable.Sprite()->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += vFontSpacing[c - 32].y * scale;
			}
		}
		SetPixelMode(m);
	}

	void PixelGameEngine::SetPixelMode(Pixel::Mode m)
	{ nPixelMode = m; }

	Pixel::Mode PixelGameEngine::GetPixelMode()
	{ return nPixelMode; }

	void PixelGameEngine::SetPixelMode(std::function<v::Pixel(const int x, const int y, const v::Pixel&, const v::Pixel&)> pixelMode)
	{
		funcPixelMode = pixelMode;
		nPixelMode = Pixel::Mode::CUSTOM;
	}

	void PixelGameEngine::SetPixelBlend(float fBlend)
	{
		fBlendFactor = fBlend;
		if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
		if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
	}

	std::stringstream& PixelGameEngine::ConsoleOut()
	{ return ssConsoleOutput; }

	bool PixelGameEngine::IsConsoleShowing() const
	{ return bConsoleShow; }

	void PixelGameEngine::ConsoleShow(const v::Key& keyExit, bool bSuspendTime)
	{
		if (bConsoleShow)
			return;

		bConsoleShow = true;		
		bConsoleSuspendTime = bSuspendTime;
		TextEntryEnable(true);
		keyConsoleExit = keyExit;
		pKeyboardState[keyConsoleExit].bHeld = false;
		pKeyboardState[keyConsoleExit].bPressed = false;
		pKeyboardState[keyConsoleExit].bReleased = true;
	}
	
	void PixelGameEngine::ConsoleClear()
	{ sConsoleLines.clear(); }

	void PixelGameEngine::ConsoleCaptureStdOut(const bool bCapture)
	{
		if(bCapture)
			sbufOldCout = std::cout.rdbuf(ssConsoleOutput.rdbuf());
		else
			std::cout.rdbuf(sbufOldCout);
	}

	void PixelGameEngine::UpdateConsole()
	{
		if (GetKey(keyConsoleExit).bPressed)
		{
			TextEntryEnable(false);
			bConsoleSuspendTime = false;
			bConsoleShow = false;
			return;
		}

		vConsoleCharacterScale = v::vf2d(1.0f, 2.0f) / (v::vf2d(vViewSize) * vInvScreenSize);
		vConsoleSize = (vViewSize / v::vi2d(8, 16)) - v::vi2d(2, 4);

		if (vConsoleSize.y != sConsoleLines.size())
		{
			vConsoleCursor = { 0,0 };
			sConsoleLines.clear();
			sConsoleLines.resize(vConsoleSize.y);
		}

		auto TypeCharacter = [&](const char c)
		{
			if (c >= 32 && c < 127)
			{
				sConsoleLines[vConsoleCursor.y].append(1, c);
				vConsoleCursor.x++;
			}

			if( c == '\n' || vConsoleCursor.x >= vConsoleSize.x)
			{
				vConsoleCursor.y++; vConsoleCursor.x = 0;				
			}			

			if (vConsoleCursor.y >= vConsoleSize.y)
			{
				vConsoleCursor.y = vConsoleSize.y - 1;
				for (size_t i = 1; i < vConsoleSize.y; i++)
					sConsoleLines[i - 1] = sConsoleLines[i];
				sConsoleLines[vConsoleCursor.y].clear();
			}
		};

		while (ssConsoleOutput.rdbuf()->sgetc() != -1)
		{
			char c = ssConsoleOutput.rdbuf()->sbumpc();
			TypeCharacter(c);
		}

		GradientFillRectDecal({ 0,0 }, v::vf2d(vScreenSize), v::PixelF(0, 0, 0.5f, 0.5f), v::PixelF(0, 0, 0.25f, 0.5f), v::PixelF(0, 0, 0.25f, 0.5f), v::PixelF(0, 0, 0.25f, 0.5f));

		SetDecalMode(v::DecalMode::NORMAL);
		for (int32_t nLine = 0; nLine < vConsoleSize.y; nLine++)
			DrawStringDecal(v::vf2d( 1, 1 + float(nLine) ) * vConsoleCharacterScale * 8.0f, sConsoleLines[nLine], v::WHITE, vConsoleCharacterScale);

		FillRectDecal(v::vf2d(1 + float((TextEntryGetCursor() + 1)), 1 + float((vConsoleSize.y - 1))) * vConsoleCharacterScale * 8.0f, v::vf2d(8, 8) * vConsoleCharacterScale, v::DARK_CYAN);
		DrawStringDecal(v::vf2d(1, 1 + float((vConsoleSize.y - 1))) * vConsoleCharacterScale * 8.0f, std::string(">") + TextEntryGetString(), v::YELLOW, vConsoleCharacterScale);		
	}

	const std::vector<std::string>& PixelGameEngine::GetDroppedFiles() const
	{ return vDroppedFiles;	}

	const v::vi2d& PixelGameEngine::GetDroppedFilesPoint() const
	{ return vDroppedFilesPoint; }

	void PixelGameEngine::TextEntryEnable(const bool bEnable, const std::string& sText)
	{
		if (bEnable)
		{
			nTextEntryCursor = int32_t(sText.size());
			sTextEntryString = sText;
			bTextEntryEnable = true;
		}
		else
		{
			bTextEntryEnable = false;
		}
	}

	std::string PixelGameEngine::TextEntryGetString() const
	{ return sTextEntryString; }

	int32_t PixelGameEngine::TextEntryGetCursor() const
	{ return nTextEntryCursor; }

	bool PixelGameEngine::IsTextEntryEnabled() const
	{ return bTextEntryEnable; }

	void PixelGameEngine::UpdateTextEntry()
	{
		
		for (const auto& key : vKeyboardMap)
			if (GetKey(std::get<0>(key)).bPressed)
			{
				sTextEntryString.insert(nTextEntryCursor, GetKey(v::Key::SHIFT).bHeld ? std::get<2>(key) : std::get<1>(key));
				nTextEntryCursor++;
			}

		if (GetKey(v::Key::LEFT).bPressed)
			nTextEntryCursor = std::max(0, nTextEntryCursor - 1);
		if (GetKey(v::Key::RIGHT).bPressed)
			nTextEntryCursor = std::min(int32_t(sTextEntryString.size()), nTextEntryCursor + 1);
		if (GetKey(v::Key::BACK).bPressed && nTextEntryCursor > 0)
		{
			sTextEntryString.erase(nTextEntryCursor-1, 1);
			nTextEntryCursor = std::max(0, nTextEntryCursor - 1);
		}
		if (GetKey(v::Key::DEL).bPressed && nTextEntryCursor < sTextEntryString.size())
			sTextEntryString.erase(nTextEntryCursor, 1);	

		if (GetKey(v::Key::UP).bPressed)
		{
			if (!sCommandHistory.empty())
			{
				if (sCommandHistoryIt != sCommandHistory.begin())
					sCommandHistoryIt--;

				nTextEntryCursor = int32_t(sCommandHistoryIt->size());
				sTextEntryString = *sCommandHistoryIt;
			}
		}

		if (GetKey(v::Key::DOWN).bPressed)
		{	
			if (!sCommandHistory.empty())
			{
				if (sCommandHistoryIt != sCommandHistory.end())
				{
					sCommandHistoryIt++;
					if (sCommandHistoryIt != sCommandHistory.end())
					{
						nTextEntryCursor = int32_t(sCommandHistoryIt->size());
						sTextEntryString = *sCommandHistoryIt;
					}
					else
					{
						nTextEntryCursor = 0;
						sTextEntryString = "";
					}
				}
			}
		}

		if (GetKey(v::Key::ENTER).bPressed)
		{
			if (bConsoleShow)
			{
				std::cout << ">" + sTextEntryString + "\n";
				if (OnConsoleCommand(sTextEntryString))
				{
					sCommandHistory.push_back(sTextEntryString);
					sCommandHistoryIt = sCommandHistory.end();
				}
				sTextEntryString.clear();
				nTextEntryCursor = 0;
			}
			else
			{
				OnTextEntryComplete(sTextEntryString);
				TextEntryEnable(false);
			}
		}
	}

	bool PixelGameEngine::OnUserCreate()
	{ return false;	}

	bool PixelGameEngine::OnUserUpdate(float fElapsedTime)
	{ UNUSED(fElapsedTime);  return false; }

	bool PixelGameEngine::OnUserDestroy()
	{ return true; }

	void PixelGameEngine::OnTextEntryComplete(const std::string& sText) { UNUSED(sText); }
	bool PixelGameEngine::OnConsoleCommand(const std::string& sCommand) { UNUSED(sCommand); return false; }

	void PixelGameEngine::v_UpdateViewport()
	{
		int32_t ww = vScreenSize.x * vPixelSize.x;
		int32_t wh = vScreenSize.y * vPixelSize.y;
		float wasp = (float)ww / (float)wh;

		if (bPixelCohesion)
		{
			vScreenPixelSize = (vWindowSize / vScreenSize);
			vViewSize = (vWindowSize / vScreenSize) * vScreenSize;
		}
		else
		{
			vViewSize.x = (int32_t)vWindowSize.x;
			vViewSize.y = (int32_t)((float)vViewSize.x / wasp);

			if (vViewSize.y > vWindowSize.y)
			{
				vViewSize.y = vWindowSize.y;
				vViewSize.x = (int32_t)((float)vViewSize.y * wasp);
			}
		}

		vViewPos = (vWindowSize - vViewSize) / 2;
	}

	void PixelGameEngine::v_UpdateWindowSize(int32_t x, int32_t y)
	{
		vWindowSize = { x, y };
		v_UpdateViewport();
	}

	void PixelGameEngine::v_UpdateMouseWheel(int32_t delta)
	{ nMouseWheelDeltaCache += delta; }

	void PixelGameEngine::v_UpdateMouse(int32_t x, int32_t y)
	{

		bHasMouseFocus = true;
		vMouseWindowPos = { x, y };
		
		x -= vViewPos.x;
		y -= vViewPos.y;
		vMousePosCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
		vMousePosCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
		if (vMousePosCache.x >= (int32_t)vScreenSize.x)	vMousePosCache.x = vScreenSize.x - 1;
		if (vMousePosCache.y >= (int32_t)vScreenSize.y)	vMousePosCache.y = vScreenSize.y - 1;
		if (vMousePosCache.x < 0) vMousePosCache.x = 0;
		if (vMousePosCache.y < 0) vMousePosCache.y = 0;
	}

	void PixelGameEngine::v_UpdateMouseState(int32_t button, bool state)
	{ pMouseNewState[button] = state; }

	void PixelGameEngine::v_UpdateKeyState(int32_t key, bool state)
	{ pKeyNewState[key] = state; }

	void PixelGameEngine::v_UpdateMouseFocus(bool state)
	{ bHasMouseFocus = state; }

	void PixelGameEngine::v_UpdateKeyFocus(bool state)
	{ bHasInputFocus = state; }

	void PixelGameEngine::v_DropFiles(int32_t x, int32_t y, const std::vector<std::string>& vFiles)
	{ 
		x -= vViewPos.x;
		y -= vViewPos.y;
		vDroppedFilesPointCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
		vDroppedFilesPointCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
		if (vDroppedFilesPointCache.x >= (int32_t)vScreenSize.x)	vDroppedFilesPointCache.x = vScreenSize.x - 1;
		if (vDroppedFilesPointCache.y >= (int32_t)vScreenSize.y)	vDroppedFilesPointCache.y = vScreenSize.y - 1;
		if (vDroppedFilesPointCache.x < 0) vDroppedFilesPointCache.x = 0;
		if (vDroppedFilesPointCache.y < 0) vDroppedFilesPointCache.y = 0;
		vDroppedFilesCache = vFiles; 
	}

	void PixelGameEngine::v_Reanimate()
	{ bAtomActive = true; }

	bool PixelGameEngine::v_IsRunning()
	{ return bAtomActive; }

	void PixelGameEngine::v_Terminate()
	{ bAtomActive = false; }

	void PixelGameEngine::EngineThread()
	{

		if (platform->ThreadStartUp() == v::FAIL)	return;

		v_PrepareEngine();

		for (auto& ext : vExtensions) ext->OnBeforeUserCreate();
		if (!OnUserCreate()) bAtomActive = false;
		for (auto& ext : vExtensions) ext->OnAfterUserCreate();

		while (bAtomActive)
		{
			
			while (bAtomActive) { v_CoreUpdate(); }

			if (!OnUserDestroy())
			{
				
				bAtomActive = true;
			}
		}

		platform->ThreadCleanUp();
	}

	void PixelGameEngine::v_PrepareEngine()
	{
		
		if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == v::FAIL) return;

		v_ConstructFontSheet();

		CreateLayer();
		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		SetDrawTarget(nullptr);

		m_tp1 = std::chrono::system_clock::now();
		m_tp2 = std::chrono::system_clock::now();
	}

	void PixelGameEngine::v_CoreUpdate()
	{
		
		m_tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
		m_tp1 = m_tp2;

		float fElapsedTime = elapsedTime.count();
		fLastElapsed = fElapsedTime;

		if (bConsoleSuspendTime)
			fElapsedTime = 0.0f;

		platform->HandleSystemEvent();

		auto ScanHardware = [&](HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount)
		{
			for (uint32_t i = 0; i < nKeyCount; i++)
			{
				pKeys[i].bPressed = false;
				pKeys[i].bReleased = false;
				if (pStateNew[i] != pStateOld[i])
				{
					if (pStateNew[i])
					{
						pKeys[i].bPressed = !pKeys[i].bHeld;
						pKeys[i].bHeld = true;
					}
					else
					{
						pKeys[i].bReleased = true;
						pKeys[i].bHeld = false;
					}
				}
				pStateOld[i] = pStateNew[i];
			}
		};

		ScanHardware(pKeyboardState, pKeyOldState, pKeyNewState, 256);
		ScanHardware(pMouseState, pMouseOldState, pMouseNewState, nMouseButtons);

		vMousePos = vMousePosCache;
		nMouseWheelDelta = nMouseWheelDeltaCache;
		nMouseWheelDeltaCache = 0;

		vDroppedFiles = vDroppedFilesCache;
		vDroppedFilesPoint = vDroppedFilesPointCache;
		vDroppedFilesCache.clear();

		if (bTextEntryEnable)
		{
			UpdateTextEntry();
		}

		bool bExtensionBlockFrame = false;		
		for (auto& ext : vExtensions) bExtensionBlockFrame |= ext->OnBeforeUserUpdate(fElapsedTime);
		if (!bExtensionBlockFrame)
		{
			if (!OnUserUpdate(fElapsedTime)) bAtomActive = false;
			
		}
		for (auto& ext : vExtensions) ext->OnAfterUserUpdate(fElapsedTime);

		if (bConsoleShow)
		{
			SetDrawTarget((uint8_t)0);
			UpdateConsole();
		}

		renderer->UpdateViewport(vViewPos, vViewSize);
		renderer->ClearBuffer(v::BLACK, true);

		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		SetDecalMode(DecalMode::NORMAL);
		renderer->PrepareDrawing();

		for (auto layer = vLayers.rbegin(); layer != vLayers.rend(); ++layer)
		{
			if (layer->bShow)
			{
				if (layer->funcHook == nullptr)
				{
					renderer->ApplyTexture(layer->pDrawTarget.Decal()->id);
					if (!bSuspendTextureTransfer && layer->bUpdate)
					{
						layer->pDrawTarget.Decal()->Update();
						layer->bUpdate = false;
					}

					renderer->DrawLayerQuad(layer->vOffset, layer->vScale, layer->tint);

					for (auto& decal : layer->vecDecalInstance)
						renderer->DrawDecal(decal);
					layer->vecDecalInstance.clear();
				}
				else
				{
					
					layer->funcHook();
				}
			}
		}

		renderer->DisplayFrame();

		fFrameTimer += fElapsedTime;
		nFrameCount++;
		if (fFrameTimer >= 1.0f)
		{
			nLastFPS = nFrameCount;
			fFrameTimer -= 1.0f;
			std::string sTitle = "OneLoneCoder.com - Pixel Game Engine - " + sAppName + " - FPS: " + std::to_string(nFrameCount);
			platform->SetWindowTitle(sTitle);
			nFrameCount = 0;
		}
	}

	void PixelGameEngine::v_ConstructFontSheet()
	{
		std::string data;
		data += "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000";
		data += "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400";
		data += "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000";
		data += "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000";
		data += "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000";
		data += "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000";
		data += "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000";
		data += "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000";
		data += "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000";
		data += "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000";
		data += "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000";
		data += "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000";
		data += "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000";
		data += "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0";
		data += "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000";
		data += "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020";

		fontRenderable.Create(128, 48);

		int px = 0, py = 0;
		for (size_t b = 0; b < 1024; b += 4)
		{
			uint32_t sym1 = (uint32_t)data[b + 0] - 48;
			uint32_t sym2 = (uint32_t)data[b + 1] - 48;
			uint32_t sym3 = (uint32_t)data[b + 2] - 48;
			uint32_t sym4 = (uint32_t)data[b + 3] - 48;
			uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

			for (int i = 0; i < 24; i++)
			{
				int k = r & (1 << i) ? 255 : 0;
				fontRenderable.Sprite()->SetPixel(px, py, v::Pixel(k, k, k, k));
				if (++py == 48) { px++; py = 0; }
			}
		}

		fontRenderable.Decal()->Update();

		constexpr std::array<uint8_t, 96> vSpacing = { {
			0x03,0x25,0x16,0x08,0x07,0x08,0x08,0x04,0x15,0x15,0x08,0x07,0x15,0x07,0x24,0x08,
			0x08,0x17,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x24,0x15,0x06,0x07,0x16,0x17,
			0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x17,0x08,0x08,0x17,0x08,0x08,0x08,
			0x08,0x08,0x08,0x08,0x17,0x08,0x08,0x08,0x08,0x17,0x08,0x15,0x08,0x15,0x08,0x08,
			0x24,0x18,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x33,0x17,0x17,0x33,0x18,0x17,0x17,
			0x17,0x17,0x17,0x17,0x07,0x17,0x17,0x18,0x18,0x17,0x17,0x07,0x33,0x07,0x08,0x00, } };

		for (auto c : vSpacing) vFontSpacing.push_back({ c >> 4, c & 15 });

#ifdef v_KEYBOARD_UK
		vKeyboardMap =
		{
			{v::Key::A, "a", "A"}, {v::Key::B, "b", "B"}, {v::Key::C, "c", "C"}, {v::Key::D, "d", "D"}, {v::Key::E, "e", "E"},
			{v::Key::F, "f", "F"}, {v::Key::G, "g", "G"}, {v::Key::H, "h", "H"}, {v::Key::I, "i", "I"}, {v::Key::J, "j", "J"},
			{v::Key::K, "k", "K"}, {v::Key::L, "l", "L"}, {v::Key::M, "m", "M"}, {v::Key::N, "n", "N"}, {v::Key::O, "o", "O"},
			{v::Key::P, "p", "P"}, {v::Key::Q, "q", "Q"}, {v::Key::R, "r", "R"}, {v::Key::S, "s", "S"}, {v::Key::T, "t", "T"},
			{v::Key::U, "u", "U"}, {v::Key::V, "v", "V"}, {v::Key::W, "w", "W"}, {v::Key::X, "x", "X"}, {v::Key::Y, "y", "Y"},
			{v::Key::Z, "z", "Z"},

			{v::Key::K0, "0", ")"}, {v::Key::K1, "1", "!"}, {v::Key::K2, "2", "\""}, {v::Key::K3, "3", "#"},	{v::Key::K4, "4", "$"},
			{v::Key::K5, "5", "%"}, {v::Key::K6, "6", "^"}, {v::Key::K7, "7", "&"}, {v::Key::K8, "8", "*"},	{v::Key::K9, "9", "("},

			{v::Key::NP0, "0", "0"}, {v::Key::NP1, "1", "1"}, {v::Key::NP2, "2", "2"}, {v::Key::NP3, "3", "3"},	{v::Key::NP4, "4", "4"},
			{v::Key::NP5, "5", "5"}, {v::Key::NP6, "6", "6"}, {v::Key::NP7, "7", "7"}, {v::Key::NP8, "8", "8"},	{v::Key::NP9, "9", "9"},
			{v::Key::NP_MUL, "*", "*"}, {v::Key::NP_DIV, "/", "/"}, {v::Key::NP_ADD, "+", "+"}, {v::Key::NP_SUB, "-", "-"},	{v::Key::NP_DECIMAL, ".", "."},

			{v::Key::PERIOD, ".", ">"}, {v::Key::EQUALS, "=", "+"}, {v::Key::COMMA, ",", "<"}, {v::Key::MINUS, "-", "_"}, {v::Key::SPACE, " ", " "},

			{v::Key::OEM_1, ";", ":"}, {v::Key::OEM_2, "/", "?"}, {v::Key::OEM_3, "\'", "@"}, {v::Key::OEM_4, "[", "{"},
			{v::Key::OEM_5, "\\", "|"}, {v::Key::OEM_6, "]", "}"}, {v::Key::OEM_7, "#", "~"}, 

		};
#endif
	}

	void PixelGameEngine::pgex_Register(v::PGEX* pgex)
	{
		if (std::find(vExtensions.begin(), vExtensions.end(), pgex) == vExtensions.end())
			vExtensions.push_back(pgex);			
	}

	PGEX::PGEX(bool bHook) { if(bHook) pge->pgex_Register(this); }
	void PGEX::OnBeforeUserCreate() {}
	void PGEX::OnAfterUserCreate()	{}
	bool PGEX::OnBeforeUserUpdate(float& fElapsedTime) { return false; }
	void PGEX::OnAfterUserUpdate(float fElapsedTime) {}

	std::atomic<bool> PixelGameEngine::bAtomActive{ false };
	v::PixelGameEngine* v::PGEX::pge = nullptr;
	v::PixelGameEngine* v::Platform::ptrPGE = nullptr;
	v::PixelGameEngine* v::Renderer::ptrPGE = nullptr;
	std::unique_ptr<ImageLoader> v::Sprite::loader = nullptr;
};
#pragma endregion 

#pragma region platform_headless
namespace v
{
#if defined(v_GFX_HEADLESS)
	class Renderer_Headless : public v::Renderer
	{
	public:
		virtual void       PrepareDevice() {};
		virtual v::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) { return v::rcode::OK;		}
		virtual v::rcode DestroyDevice() { return v::rcode::OK; }
		virtual void       DisplayFrame() {}
		virtual void       PrepareDrawing() {}
		virtual void	   SetDecalMode(const v::DecalMode& mode) {}
		virtual void       DrawLayerQuad(const v::vf2d& offset, const v::vf2d& scale, const v::Pixel tint) {}
		virtual void       DrawDecal(const v::DecalInstance& decal) {}
		virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height, const bool filtered = false, const bool clamp = true) {return 1;};
		virtual void       UpdateTexture(uint32_t id, v::Sprite* spr) {}
		virtual void       ReadTexture(uint32_t id, v::Sprite* spr) {}
		virtual uint32_t   DeleteTexture(const uint32_t id) {return 1;}
		virtual void       ApplyTexture(uint32_t id) {}
		virtual void       UpdateViewport(const v::vi2d& pos, const v::vi2d& size) {}
		virtual void       ClearBuffer(v::Pixel p, bool bDepth) {}
	};
#endif
#if defined(v_PLATFORM_HEADLESS)
	class Platform_Headless : public v::Platform
	{
	public:
		virtual v::rcode ApplicationStartUp() { return v::rcode::OK; }
		virtual v::rcode ApplicationCleanUp() { return v::rcode::OK; }
		virtual v::rcode ThreadStartUp() { return v::rcode::OK; }
		virtual v::rcode ThreadCleanUp() { return v::rcode::OK; }
		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) { return v::rcode::OK; }
		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) { return v::rcode::OK; }
		virtual v::rcode SetWindowTitle(const std::string& s) { return v::rcode::OK; }
		virtual v::rcode StartSystemEventLoop() { return v::rcode::OK; }
		virtual v::rcode HandleSystemEvent() { return v::rcode::OK; }
	};
#endif
}
#pragma endregion

#pragma region image_stb

#if defined(v_IMAGE_STB)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace v
{
	class ImageLoader_STB : public v::ImageLoader
	{
	public:
		ImageLoader_STB() : ImageLoader()
		{}

		v::rcode LoadImageResource(v::Sprite* spr, const std::string& sImageFile, v::ResourcePack* pack) override
		{
			UNUSED(pack);
			
			spr->pColData.clear();
			
			stbi_uc* bytes = nullptr;
			int w = 0, h = 0, cmp = 0;
			if (pack != nullptr)
			{
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				bytes = stbi_load_from_memory((unsigned char*)rb.vMemory.data(), rb.vMemory.size(), &w, &h, &cmp, 4);
			}
			else
			{
				
				if (!_gfs::exists(sImageFile)) return v::rcode::NO_FILE;
				bytes = stbi_load(sImageFile.c_str(), &w, &h, &cmp, 4);
			}

			if (!bytes) return v::rcode::FAIL;
			spr->width = w; spr->height = h;
			spr->pColData.resize(spr->width * spr->height);
			std::memcpy(spr->pColData.data(), bytes, spr->width * spr->height * 4);
			delete[] bytes;
			return v::rcode::OK;
		}

		v::rcode SaveImageResource(v::Sprite* spr, const std::string& sImageFile) override
		{
			return v::rcode::OK;
		}
	};
}
#endif

#pragma endregion

#if !defined(v_PGE_HEADLESS)

#pragma region renderer_ogl10

#if defined(v_GFX_OPENGL10)

#if defined(v_PLATFORM_WINAPI)
	#include <dwmapi.h>
	#include <GL/gl.h>
	#if !defined(__MINGW32__)
		#pragma comment(lib, "Dwmapi.lib")
	#endif
	typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
	static wglSwapInterval_t* wglSwapInterval = nullptr;
	typedef HDC glDeviceContext_t;
	typedef HGLRC glRenderContext_t;
#endif

#if defined(__linux__) || defined(__FreeBSD__)
	#include <GL/gl.h>
#endif

#if defined(v_PLATFORM_X11)
	namespace X11
	{
		#include <GL/glx.h>
	}
	typedef int(glSwapInterval_t)(X11::Display* dpy, X11::GLXDrawable drawable, int interval);
	static glSwapInterval_t* glSwapIntervalEXT;
	typedef X11::GLXContext glDeviceContext_t;
	typedef X11::GLXContext glRenderContext_t;
#endif

#if defined(__APPLE__)
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

namespace v
{
	class Renderer_OGL10 : public v::Renderer
	{
	private:
#if defined(v_PLATFORM_GLUT)
		bool mFullScreen = false;
#else
		glDeviceContext_t glDeviceContext = 0;
		glRenderContext_t glRenderContext = 0;
#endif

		bool bSync = false;
		v::DecalMode nDecalMode = v::DecalMode(-1); 
		v::DecalStructure nDecalStructure = v::DecalStructure(-1);
#if defined(v_PLATFORM_X11)
		X11::Display* v_Display = nullptr;
		X11::Window* v_Window = nullptr;
		X11::XVisualInfo* v_VisualInfo = nullptr;
#endif

	public:
		void PrepareDevice() override
		{
#if defined(v_PLATFORM_GLUT)
			
			int argc = 0;
			char* argv[1] = { (char*)"" };
			glutInit(&argc, argv);
			glutInitWindowPosition(0, 0);
			glutInitWindowSize(512, 512);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
			
			glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");
			glEnable(GL_TEXTURE_2D); 
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
		}

		v::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) override
		{
#if defined(v_PLATFORM_WINAPI)
			
			glDeviceContext = GetDC((HWND)(params[0]));
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				PFD_MAIN_PLANE, 0, 0, 0, 0
			};

			int pf = 0;
			if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return v::FAIL;
			SetPixelFormat(glDeviceContext, pf, &pfd);

			if (!(glRenderContext = wglCreateContext(glDeviceContext))) return v::FAIL;
			wglMakeCurrent(glDeviceContext, glRenderContext);

			wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
			if (wglSwapInterval && !bVSYNC) wglSwapInterval(0);
			bSync = bVSYNC;
#endif

#if defined(v_PLATFORM_X11)
			using namespace X11;

			v_Display = (X11::Display*)(params[0]);
			v_Window = (X11::Window*)(params[1]);
			v_VisualInfo = (X11::XVisualInfo*)(params[2]);

			glDeviceContext = glXCreateContext(v_Display, v_VisualInfo, nullptr, GL_TRUE);
			glXMakeCurrent(v_Display, *v_Window, glDeviceContext);

			XWindowAttributes gwa;
			XGetWindowAttributes(v_Display, *v_Window, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);

			glSwapIntervalEXT = nullptr;
			glSwapIntervalEXT = (glSwapInterval_t*)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");

			if (glSwapIntervalEXT == nullptr && !bVSYNC)
			{
				printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
				printf("      Don't worry though, things will still work, it's just the\n");
				printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
			}

			if (glSwapIntervalEXT != nullptr && !bVSYNC)
				glSwapIntervalEXT(v_Display, *v_Window, 0);
#endif		

#if defined(v_PLATFORM_GLUT)
			mFullScreen = bFullScreen;
			if (!bVSYNC)
			{
#if defined(__APPLE__)
				GLint sync = 0;
				CGLContextObj ctx = CGLGetCurrentContext();
				if (ctx) CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
#endif
			}
#else
			glEnable(GL_TEXTURE_2D); 
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
			return v::rcode::OK;
		}

		v::rcode DestroyDevice() override
		{
#if defined(v_PLATFORM_WINAPI)
			wglDeleteContext(glRenderContext);
#endif

#if defined(v_PLATFORM_X11)
			glXMakeCurrent(v_Display, None, NULL);
			glXDestroyContext(v_Display, glDeviceContext);
#endif

#if defined(v_PLATFORM_GLUT)
			glutDestroyWindow(glutGetWindow());
#endif
			return v::rcode::OK;
		}

		void DisplayFrame() override
		{
#if defined(v_PLATFORM_WINAPI)
			SwapBuffers(glDeviceContext);
			if (bSync) DwmFlush(); 
#endif	

#if defined(v_PLATFORM_X11)
			X11::glXSwapBuffers(v_Display, *v_Window);
#endif		

#if defined(v_PLATFORM_GLUT)
			glutSwapBuffers();
#endif
		}

		void PrepareDrawing() override
		{

			glEnable(GL_BLEND);
			nDecalMode = DecalMode::NORMAL;
			nDecalStructure = DecalStructure::FAN;
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void SetDecalMode(const v::DecalMode& mode)
		{
			if (mode != nDecalMode)
			{
				switch (mode)
				{
				case v::DecalMode::NORMAL:
				case v::DecalMode::MODEL3D:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case v::DecalMode::ADDITIVE:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					break;
				case v::DecalMode::MULTIPLICATIVE:
					glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case v::DecalMode::STENCIL:
					glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
					break;
				case v::DecalMode::ILLUMINATE:
					glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
					break;
				case v::DecalMode::WIREFRAME:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				}

				nDecalMode = mode;
			}
		}

		void DrawLayerQuad(const v::vf2d& offset, const v::vf2d& scale, const v::Pixel tint) override
		{
			glBegin(GL_QUADS);
			glColor4ub(tint.r, tint.g, tint.b, tint.a);
			glTexCoord2f(0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
			glVertex3f(-1.0f , -1.0f , 0.0f);
			glTexCoord2f(0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
			glVertex3f(-1.0f , 1.0f , 0.0f);
			glTexCoord2f(1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
			glVertex3f(1.0f , 1.0f , 0.0f);
			glTexCoord2f(1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
			glVertex3f(1.0f , -1.0f , 0.0f);
			glEnd();
		}

		void DrawDecal(const v::DecalInstance& decal) override
		{
			SetDecalMode(decal.mode);

			if (decal.decal == nullptr)
				glBindTexture(GL_TEXTURE_2D, 0);
			else
				glBindTexture(GL_TEXTURE_2D, decal.decal->id);
			
			if (nDecalMode == DecalMode::MODEL3D)
			{
#ifdef v_ENABLE_EXPERIMENTAL
				glMatrixMode(GL_PROJECTION); glPushMatrix();
				glMatrixMode(GL_MODELVIEW);  glPushMatrix();

				glEnable(GL_DEPTH_TEST);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1, 1000);

				#pragma comment (lib, "winmm.lib")

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(0, -40, -200);
				glRotatef(float(clock()) * 0.1f, 1, 0, 0);
				glRotatef(float(clock()) * 0.1f * 2, 0, 1, 0);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glBegin(GL_TRIANGLES);

				for (uint32_t n = 0; n < decal.points; n++)
				{
					glColor4ub(decal.tint[n].r, decal.tint[n].g, decal.tint[n].b, decal.tint[n].a);
					glTexCoord2f(decal.uv[n].x, decal.uv[n].y);
					glVertex3f(decal.pos[n].x, decal.pos[n].y, decal.w[n]);
				}

				glEnd();

				glMatrixMode(GL_PROJECTION); glPopMatrix();
				glMatrixMode(GL_MODELVIEW);  glPopMatrix();
				glDisable(GL_DEPTH_TEST);
#endif
			}
			else
			{
				if (nDecalMode == DecalMode::WIREFRAME)
					glBegin(GL_LINE_LOOP);
				else
				{
					if(decal.structure == v::DecalStructure::FAN)
						glBegin(GL_TRIANGLE_FAN);
					else if(decal.structure == v::DecalStructure::STRIP)
						glBegin(GL_TRIANGLE_STRIP);
					else if(decal.structure == v::DecalStructure::LIST)
						glBegin(GL_TRIANGLES);
				}

				for (uint32_t n = 0; n < decal.points; n++)
				{
					glColor4ub(decal.tint[n].r, decal.tint[n].g, decal.tint[n].b, decal.tint[n].a);
					glTexCoord4f(decal.uv[n].x, decal.uv[n].y, 0.0f, decal.w[n]);
					glVertex2f(decal.pos[n].x, decal.pos[n].y);
				}

				glEnd();
			}

		}

		uint32_t CreateTexture(const uint32_t width, const uint32_t height, const bool filtered, const bool clamp) override
		{
			UNUSED(width);
			UNUSED(height);
			uint32_t id = 0;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			if (filtered)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

			if (clamp)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			return id;
		}

		uint32_t DeleteTexture(const uint32_t id) override
		{
			glDeleteTextures(1, &id);
			return id;
		}

		void UpdateTexture(uint32_t id, v::Sprite* spr) override
		{
			UNUSED(id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ReadTexture(uint32_t id, v::Sprite* spr) override
		{
			glReadPixels(0, 0, spr->width, spr->height, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ApplyTexture(uint32_t id) override
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void ClearBuffer(v::Pixel p, bool bDepth) override
		{
			glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
		}

		void UpdateViewport(const v::vi2d& pos, const v::vi2d& size) override
		{
			glViewport(pos.x, pos.y, size.x, size.y);
		}
	};
}
#endif

#pragma endregion

#pragma region renderer_ogl33

#if defined(v_GFX_OPENGL33)

#if defined(v_PLATFORM_WINAPI)
	#include <dwmapi.h>
	
	#if !defined(__MINGW32__)
		#pragma comment(lib, "Dwmapi.lib")
	#endif		
	
	typedef HDC glDeviceContext_t;
	typedef HGLRC glRenderContext_t;
	
	#define OGL_LOAD(t, n) (t*)wglGetProcAddress(#n)
#endif

#if defined(v_PLATFORM_X11)

	typedef X11::GLXContext glDeviceContext_t;
	typedef X11::GLXContext glRenderContext_t;
	
	#define OGL_LOAD(t, n) (t*)glXGetProcAddress((unsigned char*)#n);
#endif

#if defined(v_PLATFORM_EMSCRIPTEN)
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#define GL_GLEXT_PROTOTYPES
	#include <GLES2/gl2ext.h>
	#include <emscripten/emscripten.h>
	#define CALLSTYLE
	typedef EGLBoolean(locSwapInterval_t)(EGLDisplay display, EGLint interval);
	#define GL_CLAMP GL_CLAMP_TO_EDGE
	#define OGL_LOAD(t, n) n;
#endif

namespace v
{

	class Renderer_OGL33 : public v::Renderer
	{
	private:
#if defined(v_PLATFORM_EMSCRIPTEN)
		EGLDisplay v_Display;
		EGLConfig v_Config;
		EGLContext v_Context;
		EGLSurface v_Surface;
#endif

#if defined(v_PLATFORM_GLUT)
		bool mFullScreen = false;
#else
	#if !defined(v_PLATFORM_EMSCRIPTEN)
		glDeviceContext_t glDeviceContext = 0;
		glRenderContext_t glRenderContext = 0;
	#endif
#endif
		bool bSync = false;
		v::DecalMode nDecalMode = v::DecalMode(-1); 
#if defined(v_PLATFORM_X11)
		X11::Display* v_Display = nullptr;
		X11::Window* v_Window = nullptr;
		X11::XVisualInfo* v_VisualInfo = nullptr;
#endif

	private:
		locCreateShader_t* locCreateShader = nullptr;
		locShaderSource_t* locShaderSource = nullptr;
		locCompileShader_t* locCompileShader = nullptr;
		locDeleteShader_t* locDeleteShader = nullptr;
		locCreateProgram_t* locCreateProgram = nullptr;
		locDeleteProgram_t* locDeleteProgram = nullptr;
		locLinkProgram_t* locLinkProgram = nullptr;
		locAttachShader_t* locAttachShader = nullptr;
		locBindBuffer_t* locBindBuffer = nullptr;
		locBufferData_t* locBufferData = nullptr;
		locGenBuffers_t* locGenBuffers = nullptr;
		locVertexAttribPointer_t* locVertexAttribPointer = nullptr;
		locEnableVertexAttribArray_t* locEnableVertexAttribArray = nullptr;
		locUseProgram_t* locUseProgram = nullptr;
		locBindVertexArray_t* locBindVertexArray = nullptr;
		locGenVertexArrays_t* locGenVertexArrays = nullptr;
		locSwapInterval_t* locSwapInterval = nullptr;
		locGetShaderInfoLog_t* locGetShaderInfoLog = nullptr;

		uint32_t m_nFS = 0;
		uint32_t m_nVS = 0;
		uint32_t m_nQuadShader = 0;
		uint32_t m_vbQuad = 0;
		uint32_t m_vaQuad = 0;

		struct locVertex
		{
			float pos[3];
			v::vf2d tex;
			v::Pixel col;
		};

		locVertex pVertexMem[v_MAX_VERTS];

		v::Renderable rendBlankQuad;

	public:
		void PrepareDevice() override
		{
#if defined(v_PLATFORM_GLUT)
			
			int argc = 0;
			char* argv[1] = { (char*)"" };
			glutInit(&argc, argv);
			glutInitWindowPosition(0, 0);
			glutInitWindowSize(512, 512);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
			
			glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");
			glEnable(GL_TEXTURE_2D); 
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
		}

		v::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) override
		{
			
#if defined(v_PLATFORM_WINAPI)
			
			glDeviceContext = GetDC((HWND)(params[0]));
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				PFD_MAIN_PLANE, 0, 0, 0, 0
			};

			int pf = 0;
			if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return v::FAIL;
			SetPixelFormat(glDeviceContext, pf, &pfd);

			if (!(glRenderContext = wglCreateContext(glDeviceContext))) return v::FAIL;
			wglMakeCurrent(glDeviceContext, glRenderContext);

			locSwapInterval = OGL_LOAD(locSwapInterval_t, wglSwapIntervalEXT);
			if (locSwapInterval && !bVSYNC) locSwapInterval(0);
			bSync = bVSYNC;
#endif

#if defined(v_PLATFORM_X11)
			using namespace X11;

			v_Display = (X11::Display*)(params[0]);
			v_Window = (X11::Window*)(params[1]);
			v_VisualInfo = (X11::XVisualInfo*)(params[2]);

			glDeviceContext = glXCreateContext(v_Display, v_VisualInfo, nullptr, GL_TRUE);
			glXMakeCurrent(v_Display, *v_Window, glDeviceContext);

			XWindowAttributes gwa;
			XGetWindowAttributes(v_Display, *v_Window, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);

			locSwapInterval = OGL_LOAD(locSwapInterval_t, glXSwapIntervalEXT);

			if (locSwapInterval == nullptr && !bVSYNC)
			{
				printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
				printf("      Don't worry though, things will still work, it's just the\n");
				printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
			}

			if (locSwapInterval != nullptr && !bVSYNC)
				locSwapInterval(v_Display, *v_Window, 0);
#endif		

#if defined(v_PLATFORM_EMSCRIPTEN)
			EGLint const attribute_list[] = { EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
			EGLint const context_config[] = { EGL_CONTEXT_CLIENT_VERSION , 2, EGL_NONE };
			EGLint num_config;

			v_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			eglInitialize(v_Display, nullptr, nullptr);
			eglChooseConfig(v_Display, attribute_list, &v_Config, 1, &num_config);

			v_Context = eglCreateContext(v_Display, v_Config, EGL_NO_CONTEXT, context_config);
			v_Surface = eglCreateWindowSurface(v_Display, v_Config, NULL, nullptr);
			eglMakeCurrent(v_Display, v_Surface, v_Surface, v_Context);
			
			locSwapInterval = &eglSwapInterval;
			locSwapInterval(v_Display, bVSYNC ? 1 : 0);
#endif

#if defined(v_PLATFORM_GLUT)
			mFullScreen = bFullScreen;
			if (!bVSYNC)
			{
#if defined(__APPLE__)
				GLint sync = 0;
				CGLContextObj ctx = CGLGetCurrentContext();
				if (ctx) CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
#endif
			}
#else
	#if !defined(v_PLATFORM_EMSCRIPTEN)
			glEnable(GL_TEXTURE_2D); 
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	#endif
#endif
			
			locCreateShader = OGL_LOAD(locCreateShader_t, glCreateShader);
			locCompileShader = OGL_LOAD(locCompileShader_t, glCompileShader);
			locShaderSource = OGL_LOAD(locShaderSource_t, glShaderSource);
			locDeleteShader = OGL_LOAD(locDeleteShader_t, glDeleteShader);
			locCreateProgram = OGL_LOAD(locCreateProgram_t, glCreateProgram);
			locDeleteProgram = OGL_LOAD(locDeleteProgram_t, glDeleteProgram);
			locLinkProgram = OGL_LOAD(locLinkProgram_t, glLinkProgram);
			locAttachShader = OGL_LOAD(locAttachShader_t, glAttachShader);
			locBindBuffer = OGL_LOAD(locBindBuffer_t, glBindBuffer);
			locBufferData = OGL_LOAD(locBufferData_t, glBufferData);
			locGenBuffers = OGL_LOAD(locGenBuffers_t, glGenBuffers);
			locVertexAttribPointer = OGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
			locEnableVertexAttribArray = OGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
			locUseProgram = OGL_LOAD(locUseProgram_t, glUseProgram);
			locGetShaderInfoLog = OGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);
#if !defined(v_PLATFORM_EMSCRIPTEN)
			locBindVertexArray = OGL_LOAD(locBindVertexArray_t, glBindVertexArray);
			locGenVertexArrays = OGL_LOAD(locGenVertexArrays_t, glGenVertexArrays);
#else
			locBindVertexArray = glBindVertexArrayOES;
			locGenVertexArrays = glGenVertexArraysOES;
#endif

			m_nFS = locCreateShader(0x8B30);
			const GLchar* strFS =
#if defined(__arm__) || defined(v_PLATFORM_EMSCRIPTEN)
				"#version 300 es\n"
				"precision mediump float;"
#else
				"#version 330 core\n"
#endif
				"out vec4 pixel;\n""in vec2 oTex;\n"
				"in vec4 oCol;\n""uniform sampler2D sprTex;\n""void main(){pixel = texture(sprTex, oTex) * oCol;}";
			locShaderSource(m_nFS, 1, &strFS, NULL);
			locCompileShader(m_nFS);

			m_nVS = locCreateShader(0x8B31);
			const GLchar* strVS =
#if defined(__arm__) || defined(v_PLATFORM_EMSCRIPTEN)
				"#version 300 es\n"
				"precision mediump float;"
#else
				"#version 330 core\n"
#endif
				"layout(location = 0) in vec3 aPos;\n""layout(location = 1) in vec2 aTex;\n"
				"layout(location = 2) in vec4 aCol;\n""out vec2 oTex;\n""out vec4 oCol;\n"
				"void main(){ float p = 1.0 / aPos.z; gl_Position = p * vec4(aPos.x, aPos.y, 0.0, 1.0); oTex = p * aTex; oCol = aCol;}";
			locShaderSource(m_nVS, 1, &strVS, NULL);
			locCompileShader(m_nVS);

			m_nQuadShader = locCreateProgram();
			locAttachShader(m_nQuadShader, m_nFS);
			locAttachShader(m_nQuadShader, m_nVS);
			locLinkProgram(m_nQuadShader);

			locGenBuffers(1, &m_vbQuad);
			locGenVertexArrays(1, &m_vaQuad);
			locBindVertexArray(m_vaQuad);
			locBindBuffer(0x8892, m_vbQuad);

			locVertex verts[v_MAX_VERTS];
			locBufferData(0x8892, sizeof(locVertex) * v_MAX_VERTS, verts, 0x88E0);
			locVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(locVertex), 0); locEnableVertexAttribArray(0);
			locVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(locVertex), (void*)(3 * sizeof(float))); locEnableVertexAttribArray(1);
			locVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(locVertex), (void*)(5 * sizeof(float)));	locEnableVertexAttribArray(2);
			locBindBuffer(0x8892, 0);
			locBindVertexArray(0);

			rendBlankQuad.Create(1, 1);
			rendBlankQuad.Sprite()->GetData()[0] = v::WHITE;
			rendBlankQuad.Decal()->Update();
			return v::rcode::OK;
		}

		v::rcode DestroyDevice() override
		{
#if defined(v_PLATFORM_WINAPI)
			wglDeleteContext(glRenderContext);
#endif

#if defined(v_PLATFORM_X11)
			glXMakeCurrent(v_Display, None, NULL);
			glXDestroyContext(v_Display, glDeviceContext);
#endif

#if defined(v_PLATFORM_GLUT)
			glutDestroyWindow(glutGetWindow());
#endif

#if defined(v_PLATFORM_EMSCRIPTEN)
			eglMakeCurrent(v_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroyContext(v_Display, v_Context);
			eglDestroySurface(v_Display, v_Surface);
			eglTerminate(v_Display);
			v_Display = EGL_NO_DISPLAY;
			v_Surface = EGL_NO_SURFACE;
			v_Context = EGL_NO_CONTEXT;
#endif
			return v::rcode::OK;
		}

		void DisplayFrame() override
		{
#if defined(v_PLATFORM_WINAPI)
			SwapBuffers(glDeviceContext);
			if (bSync) DwmFlush(); 
#endif	

#if defined(v_PLATFORM_X11)
			X11::glXSwapBuffers(v_Display, *v_Window);
#endif		

#if defined(v_PLATFORM_GLUT)
			glutSwapBuffers();
#endif

#if defined(v_PLATFORM_EMSCRIPTEN)
			eglSwapBuffers(v_Display, v_Surface);
#endif
		}

		void PrepareDrawing() override
		{
			glEnable(GL_BLEND);
			nDecalMode = DecalMode::NORMAL;
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			locUseProgram(m_nQuadShader);
			locBindVertexArray(m_vaQuad);

#if defined(v_PLATFORM_EMSCRIPTEN)
			locVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(locVertex), 0); locEnableVertexAttribArray(0);
			locVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(locVertex), (void*)(3 * sizeof(float))); locEnableVertexAttribArray(1);
			locVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(locVertex), (void*)(5 * sizeof(float)));	locEnableVertexAttribArray(2);
#endif
		}

		void SetDecalMode(const v::DecalMode& mode) override
		{
			if (mode != nDecalMode)
			{
				switch (mode)
				{
				case v::DecalMode::NORMAL: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	break;
				case v::DecalMode::ADDITIVE: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
				case v::DecalMode::MULTIPLICATIVE: glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);	break;
				case v::DecalMode::STENCIL: glBlendFunc(GL_ZERO, GL_SRC_ALPHA); break;
				case v::DecalMode::ILLUMINATE: glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);	break;
				case v::DecalMode::WIREFRAME: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	break;
				}

				nDecalMode = mode;
			}
		}

		void DrawLayerQuad(const v::vf2d& offset, const v::vf2d& scale, const v::Pixel tint) override
		{
			locBindBuffer(0x8892, m_vbQuad);
			locVertex verts[4] = {
				{{-1.0f, -1.0f, 1.0}, {0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y}, tint},
				{{+1.0f, -1.0f, 1.0}, {1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y}, tint},
				{{-1.0f, +1.0f, 1.0}, {0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y}, tint},
				{{+1.0f, +1.0f, 1.0}, {1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y}, tint},
			};

			locBufferData(0x8892, sizeof(locVertex) * 4, verts, 0x88E0);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		void DrawDecal(const v::DecalInstance& decal) override
		{
			SetDecalMode(decal.mode);
			if (decal.decal == nullptr)
				glBindTexture(GL_TEXTURE_2D, rendBlankQuad.Decal()->id);
			else
				glBindTexture(GL_TEXTURE_2D, decal.decal->id);

			locBindBuffer(0x8892, m_vbQuad);

			for (uint32_t i = 0; i < decal.points; i++)
				pVertexMem[i] = { { decal.pos[i].x, decal.pos[i].y, decal.w[i] }, { decal.uv[i].x, decal.uv[i].y }, decal.tint[i] };

			locBufferData(0x8892, sizeof(locVertex) * decal.points, pVertexMem, 0x88E0);

			if (nDecalMode == DecalMode::WIREFRAME)
				glDrawArrays(GL_LINE_LOOP, 0, decal.points);
			else
			{
				if (decal.structure == v::DecalStructure::FAN)
					glDrawArrays(GL_TRIANGLE_FAN, 0, decal.points);
				else if (decal.structure == v::DecalStructure::STRIP)
					glDrawArrays(GL_TRIANGLE_STRIP, 0, decal.points);
				else if (decal.structure == v::DecalStructure::LIST)
					glDrawArrays(GL_TRIANGLES, 0, decal.points);
			}
		}

		uint32_t CreateTexture(const uint32_t width, const uint32_t height, const bool filtered, const bool clamp) override
		{
			UNUSED(width);
			UNUSED(height);
			uint32_t id = 0;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			if (filtered)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

			if (clamp)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
#if !defined(v_PLATFORM_EMSCRIPTEN)
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
#endif
			return id;
		}

		uint32_t DeleteTexture(const uint32_t id) override
		{
			glDeleteTextures(1, &id);
			return id;
		}

		void UpdateTexture(uint32_t id, v::Sprite* spr) override
		{
			UNUSED(id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ReadTexture(uint32_t id, v::Sprite* spr) override
		{
			glReadPixels(0, 0, spr->width, spr->height, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ApplyTexture(uint32_t id) override
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void ClearBuffer(v::Pixel p, bool bDepth) override
		{
			glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
		}

		void UpdateViewport(const v::vi2d& pos, const v::vi2d& size) override
		{
			glViewport(pos.x, pos.y, size.x, size.y);
		}
	};
}
#endif

#pragma endregion

#pragma region image_gdi

#if defined(v_IMAGE_GDI)

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)
#include <objidl.h>
#include <gdiplus.h>
#if defined(__MINGW32__) 
	#include <gdiplus/gdiplusinit.h>
#else
	#include <gdiplusinit.h>
#endif
#include <shlwapi.h>
#undef min
#undef max

#if !defined(__MINGW32__)
	#pragma comment(lib, "gdiplus.lib")
	#pragma comment(lib, "Shlwapi.lib")
#endif

namespace v
{

	static class GDIPlusStartup
	{
	public:
		GDIPlusStartup()
		{			
			Gdiplus::GdiplusStartupInput startupInput;
			GdiplusStartup(&token, &startupInput, NULL);
		}

		ULONG_PTR	token;
		
		~GDIPlusStartup()
		{
			
			Gdiplus::GdiplusShutdown(token);
		}
	} gdistartup;

	class ImageLoader_GDIPlus : public v::ImageLoader
	{
	private:
		std::wstring ConvertS2W(std::string s)
		{
#ifdef __MINGW32__
			wchar_t* buffer = new wchar_t[s.length() + 1];
			mbstowcs(buffer, s.c_str(), s.length());
			buffer[s.length()] = L'\0';
#else
			int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
			wchar_t* buffer = new wchar_t[count];
			MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
#endif
			std::wstring w(buffer);
			delete[] buffer;
			return w;
		}

	public:
		ImageLoader_GDIPlus() : ImageLoader()
		{}

		v::rcode LoadImageResource(v::Sprite* spr, const std::string& sImageFile, v::ResourcePack* pack) override
		{
			
			spr->pColData.clear();

			UNUSED(pack);
			Gdiplus::Bitmap* bmp = nullptr;
			if (pack != nullptr)
			{
				
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				bmp = Gdiplus::Bitmap::FromStream(SHCreateMemStream((BYTE*)rb.vMemory.data(), UINT(rb.vMemory.size())));
			}
			else
			{
				
				if (!_gfs::exists(sImageFile)) return v::rcode::NO_FILE;

				bmp = Gdiplus::Bitmap::FromFile(ConvertS2W(sImageFile).c_str());
			}

			if (bmp->GetLastStatus() != Gdiplus::Ok) return v::rcode::FAIL;
			spr->width = bmp->GetWidth();
			spr->height = bmp->GetHeight();

			spr->pColData.resize(spr->width * spr->height);

			for (int y = 0; y < spr->height; y++)
				for (int x = 0; x < spr->width; x++)
				{
					Gdiplus::Color c;
					bmp->GetPixel(x, y, &c);
					spr->SetPixel(x, y, v::Pixel(c.GetRed(), c.GetGreen(), c.GetBlue(), c.GetAlpha()));
				}
			delete bmp;
			return v::rcode::OK;
		}

		v::rcode SaveImageResource(v::Sprite* spr, const std::string& sImageFile) override
		{
			return v::rcode::OK;
		}
	};
}
#endif

#pragma endregion

#pragma region image_libpng

#if defined(v_IMAGE_LIBPNG)
#include <png.h>
namespace v
{
	void pngReadStream(png_structp pngPtr, png_bytep data, png_size_t length)
	{
		png_voidp a = png_get_io_ptr(pngPtr);
		((std::istream*)a)->read((char*)data, length);
	}

	class ImageLoader_LibPNG : public v::ImageLoader
	{
	public:
		ImageLoader_LibPNG() : ImageLoader()
		{}

		v::rcode LoadImageResource(v::Sprite* spr, const std::string& sImageFile, v::ResourcePack* pack) override
		{
			UNUSED(pack);

			spr->pColData.clear();

			png_structp png;
			png_infop info;

			auto loadPNG = [&]()
			{
				png_read_info(png, info);
				png_byte color_type;
				png_byte bit_depth;
				png_bytep* row_pointers;
				spr->width = png_get_image_width(png, info);
				spr->height = png_get_image_height(png, info);
				color_type = png_get_color_type(png, info);
				bit_depth = png_get_bit_depth(png, info);
				if (bit_depth == 16) png_set_strip_16(png);
				if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
				if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)	png_set_expand_gray_1_2_4_to_8(png);
				if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
				if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
					png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
				if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
					png_set_gray_to_rgb(png);
				png_read_update_info(png, info);
				row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * spr->height);
				for (int y = 0; y < spr->height; y++) {
					row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
				}
				png_read_image(png, row_pointers);

				spr->pColData.resize(spr->width * spr->height);
				
				for (int y = 0; y < spr->height; y++)
				{
					png_bytep row = row_pointers[y];
					for (int x = 0; x < spr->width; x++)
					{
						png_bytep px = &(row[x * 4]);
						spr->SetPixel(x, y, Pixel(px[0], px[1], px[2], px[3]));
					}
				}

				for (int y = 0; y < spr->height; y++) 
					free(row_pointers[y]);
				free(row_pointers);
				png_destroy_read_struct(&png, &info, nullptr);
			};

			png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (!png) goto fail_load;

			info = png_create_info_struct(png);
			if (!info) goto fail_load;

			if (setjmp(png_jmpbuf(png))) goto fail_load;

			if (pack == nullptr)
			{
				FILE* f = fopen(sImageFile.c_str(), "rb");
				if (!f) return v::rcode::NO_FILE;
				png_init_io(png, f);
				loadPNG();
				fclose(f);
			}
			else
			{
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				std::istream is(&rb);
				png_set_read_fn(png, (png_voidp)&is, pngReadStream);
				loadPNG();
			}

			return v::rcode::OK;

		fail_load:
			spr->width = 0;
			spr->height = 0;
			spr->pColData.clear();
			return v::rcode::FAIL;
		}

		v::rcode SaveImageResource(v::Sprite* spr, const std::string& sImageFile) override
		{
			return v::rcode::OK;
		}
	};
}
#endif

#pragma endregion

#pragma region platform_windows

#if defined(v_PLATFORM_WINAPI)

#if defined(_WIN32) && !defined(__MINGW32__)
	#pragma comment(lib, "user32.lib")		
	#pragma comment(lib, "gdi32.lib")		
	#pragma comment(lib, "opengl32.lib")	
#endif

namespace v
{
	class Platform_Windows : public v::Platform
	{
	private:
		HWND v_hWnd = nullptr;
		std::wstring wsAppName;

		std::wstring ConvertS2W(std::string s)
		{
#ifdef __MINGW32__
			wchar_t* buffer = new wchar_t[s.length() + 1];
			mbstowcs(buffer, s.c_str(), s.length());
			buffer[s.length()] = L'\0';
#else
			int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
			wchar_t* buffer = new wchar_t[count];
			MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
#endif
			std::wstring w(buffer);
			delete[] buffer;
			return w;
		}

	public:
		virtual v::rcode ApplicationStartUp() override { return v::rcode::OK; }
		virtual v::rcode ApplicationCleanUp() override { return v::rcode::OK; }
		virtual v::rcode ThreadStartUp() override { return v::rcode::OK; }

		virtual v::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			PostMessage(v_hWnd, WM_DESTROY, 0, 0);
			return v::OK;
		}

		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({ v_hWnd }, bFullScreen, bEnableVSYNC) == v::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return v::rcode::OK;
			}
			else
				return v::rcode::FAIL;
		}

		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) override
		{
			WNDCLASS wc;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpfnWndProc = v_WindowEvent;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.lpszMenuName = nullptr;
			wc.hbrBackground = nullptr;
			wc.lpszClassName = vT("v_PIXEL_GAME_ENGINE");
			RegisterClass(&wc);

			DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

			v::vi2d vTopLeft = vWindowPos;

			if (bFullScreen)
			{
				dwExStyle = 0;
				dwStyle = WS_VISIBLE | WS_POPUP;
				HMONITOR hmon = MonitorFromWindow(v_hWnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi = { sizeof(mi) };
				if (!GetMonitorInfo(hmon, &mi)) return v::rcode::FAIL;
				vWindowSize = { mi.rcMonitor.right, mi.rcMonitor.bottom };
				vTopLeft.x = 0;
				vTopLeft.y = 0;
			}

			RECT rWndRect = { 0, 0, vWindowSize.x, vWindowSize.y };
			AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
			int width = rWndRect.right - rWndRect.left;
			int height = rWndRect.bottom - rWndRect.top;

			v_hWnd = CreateWindowEx(dwExStyle, vT("v_PIXEL_GAME_ENGINE"), vT(""), dwStyle,
				vTopLeft.x, vTopLeft.y, width, height, NULL, NULL, GetModuleHandle(nullptr), this);

			DragAcceptFiles(v_hWnd, true);

			mapKeys[0x00] = Key::NONE;
			mapKeys[0x41] = Key::A; mapKeys[0x42] = Key::B; mapKeys[0x43] = Key::C; mapKeys[0x44] = Key::D; mapKeys[0x45] = Key::E;
			mapKeys[0x46] = Key::F; mapKeys[0x47] = Key::G; mapKeys[0x48] = Key::H; mapKeys[0x49] = Key::I; mapKeys[0x4A] = Key::J;
			mapKeys[0x4B] = Key::K; mapKeys[0x4C] = Key::L; mapKeys[0x4D] = Key::M; mapKeys[0x4E] = Key::N; mapKeys[0x4F] = Key::O;
			mapKeys[0x50] = Key::P; mapKeys[0x51] = Key::Q; mapKeys[0x52] = Key::R; mapKeys[0x53] = Key::S; mapKeys[0x54] = Key::T;
			mapKeys[0x55] = Key::U; mapKeys[0x56] = Key::V; mapKeys[0x57] = Key::W; mapKeys[0x58] = Key::X; mapKeys[0x59] = Key::Y;
			mapKeys[0x5A] = Key::Z;

			mapKeys[VK_F1] = Key::F1; mapKeys[VK_F2] = Key::F2; mapKeys[VK_F3] = Key::F3; mapKeys[VK_F4] = Key::F4;
			mapKeys[VK_F5] = Key::F5; mapKeys[VK_F6] = Key::F6; mapKeys[VK_F7] = Key::F7; mapKeys[VK_F8] = Key::F8;
			mapKeys[VK_F9] = Key::F9; mapKeys[VK_F10] = Key::F10; mapKeys[VK_F11] = Key::F11; mapKeys[VK_F12] = Key::F12;

			mapKeys[VK_DOWN] = Key::DOWN; mapKeys[VK_LEFT] = Key::LEFT; mapKeys[VK_RIGHT] = Key::RIGHT; mapKeys[VK_UP] = Key::UP;

			mapKeys[VK_BACK] = Key::BACK; mapKeys[VK_ESCAPE] = Key::ESCAPE; mapKeys[VK_RETURN] = Key::ENTER; mapKeys[VK_PAUSE] = Key::PAUSE;
			mapKeys[VK_SCROLL] = Key::SCROLL; mapKeys[VK_TAB] = Key::TAB; mapKeys[VK_DELETE] = Key::DEL; mapKeys[VK_HOME] = Key::HOME;
			mapKeys[VK_END] = Key::END; mapKeys[VK_PRIOR] = Key::PGUP; mapKeys[VK_NEXT] = Key::PGDN; mapKeys[VK_INSERT] = Key::INS;
			mapKeys[VK_SHIFT] = Key::SHIFT; mapKeys[VK_CONTROL] = Key::CTRL;
			mapKeys[VK_SPACE] = Key::SPACE;

			mapKeys[0x30] = Key::K0; mapKeys[0x31] = Key::K1; mapKeys[0x32] = Key::K2; mapKeys[0x33] = Key::K3; mapKeys[0x34] = Key::K4;
			mapKeys[0x35] = Key::K5; mapKeys[0x36] = Key::K6; mapKeys[0x37] = Key::K7; mapKeys[0x38] = Key::K8; mapKeys[0x39] = Key::K9;

			mapKeys[VK_NUMPAD0] = Key::NP0; mapKeys[VK_NUMPAD1] = Key::NP1; mapKeys[VK_NUMPAD2] = Key::NP2; mapKeys[VK_NUMPAD3] = Key::NP3; mapKeys[VK_NUMPAD4] = Key::NP4;
			mapKeys[VK_NUMPAD5] = Key::NP5; mapKeys[VK_NUMPAD6] = Key::NP6; mapKeys[VK_NUMPAD7] = Key::NP7; mapKeys[VK_NUMPAD8] = Key::NP8; mapKeys[VK_NUMPAD9] = Key::NP9;
			mapKeys[VK_MULTIPLY] = Key::NP_MUL; mapKeys[VK_ADD] = Key::NP_ADD; mapKeys[VK_DIVIDE] = Key::NP_DIV; mapKeys[VK_SUBTRACT] = Key::NP_SUB; mapKeys[VK_DECIMAL] = Key::NP_DECIMAL;

			mapKeys[VK_OEM_1] = Key::OEM_1;			
			mapKeys[VK_OEM_2] = Key::OEM_2;			
			mapKeys[VK_OEM_3] = Key::OEM_3;			
			mapKeys[VK_OEM_4] = Key::OEM_4;			
			mapKeys[VK_OEM_5] = Key::OEM_5;			
			mapKeys[VK_OEM_6] = Key::OEM_6;			
			mapKeys[VK_OEM_7] = Key::OEM_7;			
			mapKeys[VK_OEM_8] = Key::OEM_8;			
			mapKeys[VK_OEM_PLUS] = Key::EQUALS;		
			mapKeys[VK_OEM_COMMA] = Key::COMMA;		
			mapKeys[VK_OEM_MINUS] = Key::MINUS;		
			mapKeys[VK_OEM_PERIOD] = Key::PERIOD;	
			mapKeys[VK_CAPITAL] = Key::CAPS_LOCK;
			return v::OK;
		}

		virtual v::rcode SetWindowTitle(const std::string& s) override
		{
#ifdef UNICODE
			SetWindowText(v_hWnd, ConvertS2W(s).c_str());
#else
			SetWindowText(v_hWnd, s.c_str());
#endif
			return v::OK;
		}

		virtual v::rcode StartSystemEventLoop() override
		{
			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return v::OK;
		}

		virtual v::rcode HandleSystemEvent() override { return v::rcode::FAIL; }

		static LRESULT CALLBACK v_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_MOUSEMOVE:
			{
				
				uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
				int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
				ptrPGE->v_UpdateMouse(ix, iy);
				return 0;
			}
			case WM_SIZE:       ptrPGE->v_UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);	return 0;
			case WM_MOUSEWHEEL:	ptrPGE->v_UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));           return 0;
			case WM_MOUSELEAVE: ptrPGE->v_UpdateMouseFocus(false);                                    return 0;
			case WM_SETFOCUS:	ptrPGE->v_UpdateKeyFocus(true);                                       return 0;
			case WM_KILLFOCUS:	ptrPGE->v_UpdateKeyFocus(false);                                      return 0;
			case WM_KEYDOWN:	ptrPGE->v_UpdateKeyState(mapKeys[wParam], true);                      return 0;
			case WM_KEYUP:		ptrPGE->v_UpdateKeyState(mapKeys[wParam], false);                     return 0;
			case WM_SYSKEYDOWN: ptrPGE->v_UpdateKeyState(mapKeys[wParam], true);						return 0;
			case WM_SYSKEYUP:	ptrPGE->v_UpdateKeyState(mapKeys[wParam], false);						return 0;
			case WM_LBUTTONDOWN:ptrPGE->v_UpdateMouseState(0, true);                                  return 0;
			case WM_LBUTTONUP:	ptrPGE->v_UpdateMouseState(0, false);                                 return 0;
			case WM_RBUTTONDOWN:ptrPGE->v_UpdateMouseState(1, true);                                  return 0;
			case WM_RBUTTONUP:	ptrPGE->v_UpdateMouseState(1, false);                                 return 0;
			case WM_MBUTTONDOWN:ptrPGE->v_UpdateMouseState(2, true);                                  return 0;
			case WM_MBUTTONUP:	ptrPGE->v_UpdateMouseState(2, false);                                 return 0;
			case WM_DROPFILES:
			{
				
				HDROP drop = (HDROP)wParam;
				
				uint32_t nFiles = DragQueryFile(drop, 0xFFFFFFFF, nullptr, 0);
				std::vector<std::string> vFiles;
				for (uint32_t i = 0; i < nFiles; i++)
				{
					TCHAR dfbuffer[256]{};
					uint32_t len = DragQueryFile(drop, i, nullptr, 0);
					DragQueryFile(drop, i, dfbuffer, 256);
#ifdef UNICODE
	#ifdef __MINGW32__
					char* buffer = new char[len + 1];
					wcstombs(buffer, dfbuffer, len);
					buffer[len] = '\0';
	#else
					int count = WideCharToMultiByte(CP_UTF8, 0, dfbuffer, -1, NULL, 0, NULL, NULL);
					char* buffer = new char[count];
					WideCharToMultiByte(CP_UTF8, 0, dfbuffer, -1, buffer, count, NULL, NULL);
	#endif				
					vFiles.push_back(std::string(buffer));
					delete[] buffer;
#else
					vFiles.push_back(std::string(dfbuffer));
#endif
				}

				POINT p; DragQueryPoint(drop, &p);
				ptrPGE->v_DropFiles(p.x, p.y, vFiles);
				DragFinish(drop);
				return 0;
			} 
			break;

			case WM_CLOSE:		ptrPGE->v_Terminate();                                                return 0;
			case WM_DESTROY:	PostQuitMessage(0); DestroyWindow(hWnd);								return 0;
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	};
}
#endif

#pragma endregion 

#pragma region platform_linux

#if defined(v_PLATFORM_X11)
namespace v
{
	class Platform_Linux : public v::Platform
	{
	private:
		X11::Display* v_Display = nullptr;
		X11::Window					 v_WindowRoot;
		X11::Window					 v_Window;
		X11::XVisualInfo* v_VisualInfo;
		X11::Colormap                v_ColourMap;
		X11::XSetWindowAttributes    v_SetWindowAttribs;

	public:
		virtual v::rcode ApplicationStartUp() override
		{
			return v::rcode::OK;
		}

		virtual v::rcode ApplicationCleanUp() override
		{
			XDestroyWindow(v_Display, v_Window);
			return v::rcode::OK;
		}

		virtual v::rcode ThreadStartUp() override
		{
			return v::rcode::OK;
		}

		virtual v::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			return v::OK;
		}

		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({ v_Display, &v_Window, v_VisualInfo }, bFullScreen, bEnableVSYNC) == v::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return v::rcode::OK;
			}
			else
				return v::rcode::FAIL;
		}

		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) override
		{
			using namespace X11;
			XInitThreads();

			v_Display = XOpenDisplay(NULL);
			v_WindowRoot = DefaultRootWindow(v_Display);

			GLint v_GLAttribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
			v_VisualInfo = glXChooseVisual(v_Display, 0, v_GLAttribs);
			v_ColourMap = XCreateColormap(v_Display, v_WindowRoot, v_VisualInfo->visual, AllocNone);
			v_SetWindowAttribs.colormap = v_ColourMap;

			v_SetWindowAttribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
				ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

			v_Window = XCreateWindow(v_Display, v_WindowRoot, vWindowPos.x, vWindowPos.y,
				vWindowSize.x, vWindowSize.y,
				0, v_VisualInfo->depth, InputOutput, v_VisualInfo->visual,
				CWColormap | CWEventMask, &v_SetWindowAttribs);

			Atom wmDelete = XInternAtom(v_Display, "WM_DELETE_WINDOW", true);
			XSetWMProtocols(v_Display, v_Window, &wmDelete, 1);

			XMapWindow(v_Display, v_Window);
			XStoreName(v_Display, v_Window, "OneLoneCoder.com - Pixel Game Engine");

			if (bFullScreen) 
			{
				Atom wm_state;
				Atom fullscreen;
				wm_state = XInternAtom(v_Display, "_NET_WM_STATE", False);
				fullscreen = XInternAtom(v_Display, "_NET_WM_STATE_FULLSCREEN", False);
				XEvent xev{ 0 };
				xev.type = ClientMessage;
				xev.xclient.window = v_Window;
				xev.xclient.message_type = wm_state;
				xev.xclient.format = 32;
				xev.xclient.data.l[0] = (bFullScreen ? 1 : 0);   
				xev.xclient.data.l[1] = fullscreen;             
				xev.xclient.data.l[2] = 0;                      
				xev.xclient.data.l[3] = 0;                      
				XMapWindow(v_Display, v_Window);
				XSendEvent(v_Display, DefaultRootWindow(v_Display), False,
					SubstructureRedirectMask | SubstructureNotifyMask, &xev);
				XFlush(v_Display);
				XWindowAttributes gwa;
				XGetWindowAttributes(v_Display, v_Window, &gwa);
				vWindowSize.x = gwa.width;
				vWindowSize.y = gwa.height;
			}

			mapKeys[0x00] = Key::NONE;
			mapKeys[0x61] = Key::A; mapKeys[0x62] = Key::B; mapKeys[0x63] = Key::C; mapKeys[0x64] = Key::D; mapKeys[0x65] = Key::E;
			mapKeys[0x66] = Key::F; mapKeys[0x67] = Key::G; mapKeys[0x68] = Key::H; mapKeys[0x69] = Key::I; mapKeys[0x6A] = Key::J;
			mapKeys[0x6B] = Key::K; mapKeys[0x6C] = Key::L; mapKeys[0x6D] = Key::M; mapKeys[0x6E] = Key::N; mapKeys[0x6F] = Key::O;
			mapKeys[0x70] = Key::P; mapKeys[0x71] = Key::Q; mapKeys[0x72] = Key::R; mapKeys[0x73] = Key::S; mapKeys[0x74] = Key::T;
			mapKeys[0x75] = Key::U; mapKeys[0x76] = Key::V; mapKeys[0x77] = Key::W; mapKeys[0x78] = Key::X; mapKeys[0x79] = Key::Y;
			mapKeys[0x7A] = Key::Z;

			mapKeys[XK_F1] = Key::F1; mapKeys[XK_F2] = Key::F2; mapKeys[XK_F3] = Key::F3; mapKeys[XK_F4] = Key::F4;
			mapKeys[XK_F5] = Key::F5; mapKeys[XK_F6] = Key::F6; mapKeys[XK_F7] = Key::F7; mapKeys[XK_F8] = Key::F8;
			mapKeys[XK_F9] = Key::F9; mapKeys[XK_F10] = Key::F10; mapKeys[XK_F11] = Key::F11; mapKeys[XK_F12] = Key::F12;

			mapKeys[XK_Down] = Key::DOWN; mapKeys[XK_Left] = Key::LEFT; mapKeys[XK_Right] = Key::RIGHT; mapKeys[XK_Up] = Key::UP;
			mapKeys[XK_KP_Enter] = Key::ENTER; mapKeys[XK_Return] = Key::ENTER;

			mapKeys[XK_BackSpace] = Key::BACK; mapKeys[XK_Escape] = Key::ESCAPE; mapKeys[XK_Linefeed] = Key::ENTER;	mapKeys[XK_Pause] = Key::PAUSE;
			mapKeys[XK_Scroll_Lock] = Key::SCROLL; mapKeys[XK_Tab] = Key::TAB; mapKeys[XK_Delete] = Key::DEL; mapKeys[XK_Home] = Key::HOME;
			mapKeys[XK_End] = Key::END; mapKeys[XK_Page_Up] = Key::PGUP; mapKeys[XK_Page_Down] = Key::PGDN;	mapKeys[XK_Insert] = Key::INS;
			mapKeys[XK_Shift_L] = Key::SHIFT; mapKeys[XK_Shift_R] = Key::SHIFT; mapKeys[XK_Control_L] = Key::CTRL; mapKeys[XK_Control_R] = Key::CTRL;
			mapKeys[XK_space] = Key::SPACE; mapKeys[XK_period] = Key::PERIOD;

			mapKeys[XK_0] = Key::K0; mapKeys[XK_1] = Key::K1; mapKeys[XK_2] = Key::K2; mapKeys[XK_3] = Key::K3; mapKeys[XK_4] = Key::K4;
			mapKeys[XK_5] = Key::K5; mapKeys[XK_6] = Key::K6; mapKeys[XK_7] = Key::K7; mapKeys[XK_8] = Key::K8; mapKeys[XK_9] = Key::K9;

			mapKeys[XK_KP_0] = Key::NP0; mapKeys[XK_KP_1] = Key::NP1; mapKeys[XK_KP_2] = Key::NP2; mapKeys[XK_KP_3] = Key::NP3; mapKeys[XK_KP_4] = Key::NP4;
			mapKeys[XK_KP_5] = Key::NP5; mapKeys[XK_KP_6] = Key::NP6; mapKeys[XK_KP_7] = Key::NP7; mapKeys[XK_KP_8] = Key::NP8; mapKeys[XK_KP_9] = Key::NP9;
			mapKeys[XK_KP_Multiply] = Key::NP_MUL; mapKeys[XK_KP_Add] = Key::NP_ADD; mapKeys[XK_KP_Divide] = Key::NP_DIV; mapKeys[XK_KP_Subtract] = Key::NP_SUB; mapKeys[XK_KP_Decimal] = Key::NP_DECIMAL;

			mapKeys[XK_semicolon] = Key::OEM_1;		
			mapKeys[XK_slash] = Key::OEM_2;			
			mapKeys[XK_asciitilde] = Key::OEM_3;	
			mapKeys[XK_bracketleft] = Key::OEM_4;	
			mapKeys[XK_backslash] = Key::OEM_5;		
			mapKeys[XK_bracketright] = Key::OEM_6;	
			mapKeys[XK_apostrophe] = Key::OEM_7;	
			mapKeys[XK_numbersign] = Key::OEM_8;	
			mapKeys[XK_equal] = Key::EQUALS;		
			mapKeys[XK_comma] = Key::COMMA;			
			mapKeys[XK_minus] = Key::MINUS;			

			mapKeys[XK_Caps_Lock] = Key::CAPS_LOCK;

			return v::OK;
		}

		virtual v::rcode SetWindowTitle(const std::string& s) override
		{
			X11::XStoreName(v_Display, v_Window, s.c_str());
			return v::OK;
		}

		virtual v::rcode StartSystemEventLoop() override
		{
			return v::OK;
		}

		virtual v::rcode HandleSystemEvent() override
		{
			using namespace X11;

			XEvent xev;
			while (XPending(v_Display))
			{
				XNextEvent(v_Display, &xev);
				if (xev.type == Expose)
				{
					XWindowAttributes gwa;
					XGetWindowAttributes(v_Display, v_Window, &gwa);
					ptrPGE->v_UpdateWindowSize(gwa.width, gwa.height);
				}
				else if (xev.type == ConfigureNotify)
				{
					XConfigureEvent xce = xev.xconfigure;
					ptrPGE->v_UpdateWindowSize(xce.width, xce.height);
				}
				else if (xev.type == KeyPress)
				{
					KeySym sym = XLookupKeysym(&xev.xkey, 0);
					ptrPGE->v_UpdateKeyState(mapKeys[sym], true);
					XKeyEvent* e = (XKeyEvent*)&xev; 
					XLookupString(e, NULL, 0, &sym, NULL);
					ptrPGE->v_UpdateKeyState(mapKeys[sym], true);
				}
				else if (xev.type == KeyRelease)
				{
					KeySym sym = XLookupKeysym(&xev.xkey, 0);
					ptrPGE->v_UpdateKeyState(mapKeys[sym], false);
					XKeyEvent* e = (XKeyEvent*)&xev;
					XLookupString(e, NULL, 0, &sym, NULL);
					ptrPGE->v_UpdateKeyState(mapKeys[sym], false);
				}
				else if (xev.type == ButtonPress)
				{
					switch (xev.xbutton.button)
					{
					case 1:	ptrPGE->v_UpdateMouseState(0, true); break;
					case 2:	ptrPGE->v_UpdateMouseState(2, true); break;
					case 3:	ptrPGE->v_UpdateMouseState(1, true); break;
					case 4:	ptrPGE->v_UpdateMouseWheel(120); break;
					case 5:	ptrPGE->v_UpdateMouseWheel(-120); break;
					default: break;
					}
				}
				else if (xev.type == ButtonRelease)
				{
					switch (xev.xbutton.button)
					{
					case 1:	ptrPGE->v_UpdateMouseState(0, false); break;
					case 2:	ptrPGE->v_UpdateMouseState(2, false); break;
					case 3:	ptrPGE->v_UpdateMouseState(1, false); break;
					default: break;
					}
				}
				else if (xev.type == MotionNotify)
				{
					ptrPGE->v_UpdateMouse(xev.xmotion.x, xev.xmotion.y);
				}
				else if (xev.type == FocusIn)
				{
					ptrPGE->v_UpdateKeyFocus(true);
				}
				else if (xev.type == FocusOut)
				{
					ptrPGE->v_UpdateKeyFocus(false);
				}
				else if (xev.type == ClientMessage)
				{
					ptrPGE->v_Terminate();
				}
			}
			return v::OK;
		}
	};
}
#endif

#pragma endregion

#pragma region platform_glut

#if defined(v_PLATFORM_GLUT)
namespace v {

	class Platform_GLUT : public v::Platform
	{
	public:
		static std::atomic<bool>* bActiveRef;

		virtual v::rcode ApplicationStartUp() override {
			return v::rcode::OK;
		}

		virtual v::rcode ApplicationCleanUp() override
		{
			return v::rcode::OK;
		}

		virtual v::rcode ThreadStartUp() override
		{
			return v::rcode::OK;
		}

		virtual v::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			return v::OK;
		}

		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == v::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return v::rcode::OK;
			}
			else
				return v::rcode::FAIL;
		}

		static void ExitMainLoop() {
			if (!ptrPGE->OnUserDestroy()) {
				*bActiveRef = true;
				return;
			}
			platform->ThreadCleanUp();
			platform->ApplicationCleanUp();
			exit(0);
		}

#if defined(__APPLE__)
		static void scrollWheelUpdate(id selff, SEL _sel, id theEvent) {
			static const SEL deltaYSel = sel_registerName("deltaY");

#if defined(__aarch64__) 
			double deltaY = ((double (*)(id, SEL))objc_msgSend)(theEvent, deltaYSel);
#else
			double deltaY = ((double (*)(id, SEL))objc_msgSend_fpret)(theEvent, deltaYSel);
#endif

			for (int i = 0; i < abs(deltaY); i++) {
				if (deltaY > 0) {
					ptrPGE->v_UpdateMouseWheel(-1);
				}
				else if (deltaY < 0) {
					ptrPGE->v_UpdateMouseWheel(1);
				}
			}
		}
#endif
		static void ThreadFunct() {
#if defined(__APPLE__)
			static bool hasEnabledCocoa = false;
			if (!hasEnabledCocoa) {
				
				Class NSApplicationClass = objc_getClass("NSApplication");

				SEL sharedApplicationSel = sel_registerName("sharedApplication");
				id NSApp = ((id(*)(Class, SEL))objc_msgSend)(NSApplicationClass, sharedApplicationSel);
				
				SEL mainWindowSel = sel_registerName("mainWindow");
				id window = ((id(*)(id, SEL))objc_msgSend)(NSApp, mainWindowSel);

				SEL setStyleMaskSel = sel_registerName("setStyleMask:");
				((void (*)(id, SEL, NSUInteger))objc_msgSend)(window, setStyleMaskSel, 7);

				hasEnabledCocoa = true;
			}
#endif
			if (!*bActiveRef) {
				ExitMainLoop();
				return;
			}
			glutPostRedisplay();
		}

		static void DrawFunct() {
			ptrPGE->v_CoreUpdate();
		}

		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) override
		{
#if defined(__APPLE__)
			Class GLUTViewClass = objc_getClass("GLUTView");

			SEL scrollWheelSel = sel_registerName("scrollWheel:");
			bool resultAddMethod = class_addMethod(GLUTViewClass, scrollWheelSel, (IMP)scrollWheelUpdate, "v@:@");
			assert(resultAddMethod);
#endif

			renderer->PrepareDevice();

			if (bFullScreen)
			{
				vWindowSize.x = glutGet(GLUT_SCREEN_WIDTH);
				vWindowSize.y = glutGet(GLUT_SCREEN_HEIGHT);
				glutFullScreen();
			}
			else
			{
				if (vWindowSize.x > glutGet(GLUT_SCREEN_WIDTH) || vWindowSize.y > glutGet(GLUT_SCREEN_HEIGHT))
				{
					perror("ERROR: The specified window dimensions do not fit on your screen\n");
					return v::FAIL;
				}
				glutReshapeWindow(vWindowSize.x, vWindowSize.y - 1);
			}

			mapKeys[0x00] = Key::NONE;
			mapKeys['A'] = Key::A; mapKeys['B'] = Key::B; mapKeys['C'] = Key::C; mapKeys['D'] = Key::D; mapKeys['E'] = Key::E;
			mapKeys['F'] = Key::F; mapKeys['G'] = Key::G; mapKeys['H'] = Key::H; mapKeys['I'] = Key::I; mapKeys['J'] = Key::J;
			mapKeys['K'] = Key::K; mapKeys['L'] = Key::L; mapKeys['M'] = Key::M; mapKeys['N'] = Key::N; mapKeys['O'] = Key::O;
			mapKeys['P'] = Key::P; mapKeys['Q'] = Key::Q; mapKeys['R'] = Key::R; mapKeys['S'] = Key::S; mapKeys['T'] = Key::T;
			mapKeys['U'] = Key::U; mapKeys['V'] = Key::V; mapKeys['W'] = Key::W; mapKeys['X'] = Key::X; mapKeys['Y'] = Key::Y;
			mapKeys['Z'] = Key::Z;

			mapKeys[GLUT_KEY_F1] = Key::F1; mapKeys[GLUT_KEY_F2] = Key::F2; mapKeys[GLUT_KEY_F3] = Key::F3; mapKeys[GLUT_KEY_F4] = Key::F4;
			mapKeys[GLUT_KEY_F5] = Key::F5; mapKeys[GLUT_KEY_F6] = Key::F6; mapKeys[GLUT_KEY_F7] = Key::F7; mapKeys[GLUT_KEY_F8] = Key::F8;
			mapKeys[GLUT_KEY_F9] = Key::F9; mapKeys[GLUT_KEY_F10] = Key::F10; mapKeys[GLUT_KEY_F11] = Key::F11; mapKeys[GLUT_KEY_F12] = Key::F12;

			mapKeys[GLUT_KEY_DOWN] = Key::DOWN; mapKeys[GLUT_KEY_LEFT] = Key::LEFT; mapKeys[GLUT_KEY_RIGHT] = Key::RIGHT; mapKeys[GLUT_KEY_UP] = Key::UP;
			mapKeys[13] = Key::ENTER;

			mapKeys[127] = Key::BACK; mapKeys[27] = Key::ESCAPE;
			mapKeys[9] = Key::TAB;  mapKeys[GLUT_KEY_HOME] = Key::HOME;
			mapKeys[GLUT_KEY_END] = Key::END; mapKeys[GLUT_KEY_PAGE_UP] = Key::PGUP; mapKeys[GLUT_KEY_PAGE_DOWN] = Key::PGDN;    mapKeys[GLUT_KEY_INSERT] = Key::INS;
			mapKeys[32] = Key::SPACE; mapKeys[46] = Key::PERIOD;

			mapKeys[48] = Key::K0; mapKeys[49] = Key::K1; mapKeys[50] = Key::K2; mapKeys[51] = Key::K3; mapKeys[52] = Key::K4;
			mapKeys[53] = Key::K5; mapKeys[54] = Key::K6; mapKeys[55] = Key::K7; mapKeys[56] = Key::K8; mapKeys[57] = Key::K9;

			glutKeyboardFunc([](unsigned char key, int x, int y) -> void {
				switch (glutGetModifiers()) {
				case 0: 
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				case GLUT_ACTIVE_SHIFT:
					ptrPGE->v_UpdateKeyState(Key::SHIFT, true);
					break;
				case GLUT_ACTIVE_CTRL:
					if ('a' <= key && key <= 'z') key -= 32;
					ptrPGE->v_UpdateKeyState(Key::CTRL, true);
					break;
				case GLUT_ACTIVE_ALT:
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				}

				if (mapKeys[key])
					ptrPGE->v_UpdateKeyState(mapKeys[key], true);
				});

			glutKeyboardUpFunc([](unsigned char key, int x, int y) -> void {
				switch (glutGetModifiers()) {
				case 0: 
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				case GLUT_ACTIVE_SHIFT:
					ptrPGE->v_UpdateKeyState(Key::SHIFT, false);
					break;
				case GLUT_ACTIVE_CTRL:
					if ('a' <= key && key <= 'z') key -= 32;
					ptrPGE->v_UpdateKeyState(Key::CTRL, false);
					break;
				case GLUT_ACTIVE_ALT:
					if ('a' <= key && key <= 'z') key -= 32;
					
					break;
				}

				if (mapKeys[key])
					ptrPGE->v_UpdateKeyState(mapKeys[key], false);
				});

			glutSpecialFunc([](int key, int x, int y) -> void {
				if (mapKeys[key])
					ptrPGE->v_UpdateKeyState(mapKeys[key], true);
				});

			glutSpecialUpFunc([](int key, int x, int y) -> void {
				if (mapKeys[key])
					ptrPGE->v_UpdateKeyState(mapKeys[key], false);
				});

			glutMouseFunc([](int button, int state, int x, int y) -> void {
				switch (button) {
				case GLUT_LEFT_BUTTON:
					if (state == GLUT_UP) ptrPGE->v_UpdateMouseState(0, false);
					else if (state == GLUT_DOWN) ptrPGE->v_UpdateMouseState(0, true);
					break;
				case GLUT_MIDDLE_BUTTON:
					if (state == GLUT_UP) ptrPGE->v_UpdateMouseState(2, false);
					else if (state == GLUT_DOWN) ptrPGE->v_UpdateMouseState(2, true);
					break;
				case GLUT_RIGHT_BUTTON:
					if (state == GLUT_UP) ptrPGE->v_UpdateMouseState(1, false);
					else if (state == GLUT_DOWN) ptrPGE->v_UpdateMouseState(1, true);
					break;
				}
				});

			auto mouseMoveCall = [](int x, int y) -> void {
				ptrPGE->v_UpdateMouse(x, y);
			};

			glutMotionFunc(mouseMoveCall);
			glutPassiveMotionFunc(mouseMoveCall);

			glutEntryFunc([](int state) -> void {
				if (state == GLUT_ENTERED) ptrPGE->v_UpdateKeyFocus(true);
				else if (state == GLUT_LEFT) ptrPGE->v_UpdateKeyFocus(false);
				});

			glutDisplayFunc(DrawFunct);
			glutIdleFunc(ThreadFunct);

			return v::OK;
		}

		virtual v::rcode SetWindowTitle(const std::string& s) override
		{
			glutSetWindowTitle(s.c_str());
			return v::OK;
		}

		virtual v::rcode StartSystemEventLoop() override {
			glutMainLoop();
			return v::OK;
		}

		virtual v::rcode HandleSystemEvent() override
		{
			return v::OK;
		}
	};

	std::atomic<bool>* Platform_GLUT::bActiveRef{ nullptr };

	v::rcode PixelGameEngine::Start()
	{
		if (platform->ApplicationStartUp() != v::OK) return v::FAIL;

		if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != v::OK) return v::FAIL;
		v_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		if (platform->ThreadStartUp() == v::FAIL)  return v::FAIL;
		v_PrepareEngine();
		if (!OnUserCreate()) return v::FAIL;
		Platform_GLUT::bActiveRef = &bAtomActive;
		glutWMCloseFunc(Platform_GLUT::ExitMainLoop);
		bAtomActive = true;
		platform->StartSystemEventLoop();

		if (platform->ApplicationCleanUp() != v::OK) return v::FAIL;

		return v::OK;
	}
}

#endif

#pragma endregion 

#pragma region platform_emscripten

#if defined(v_PLATFORM_EMSCRIPTEN)

#include <emscripten/html5.h>
#include <emscripten/key_codes.h>

extern "C" 
{
	EMSCRIPTEN_KEEPALIVE inline int v_OnPageUnload()
	{ v::platform->ApplicationCleanUp(); return 0; }
}

namespace v
{
	class Platform_Emscripten : public v::Platform
	{
	public:

		virtual v::rcode ApplicationStartUp() override 
		{ return v::rcode::OK; }

		virtual v::rcode ApplicationCleanUp() override 
		{ ThreadCleanUp(); return v::rcode::OK; }

		virtual v::rcode ThreadStartUp() override
		{ return v::rcode::OK; }

		virtual v::rcode ThreadCleanUp() override
		{ renderer->DestroyDevice(); return v::OK; }

		virtual v::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const v::vi2d& vViewPos, const v::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == v::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return v::rcode::OK;
			}
			else
				return v::rcode::FAIL;
		}

		virtual v::rcode CreateWindowPane(const v::vi2d& vWindowPos, v::vi2d& vWindowSize, bool bFullScreen) override
		{
			emscripten_set_canvas_element_size("#canvas", vWindowSize.x, vWindowSize.y);

			mapKeys[DOM_PK_UNKNOWN] = Key::NONE;
			mapKeys[DOM_PK_A] = Key::A; mapKeys[DOM_PK_B] = Key::B; mapKeys[DOM_PK_C] = Key::C; mapKeys[DOM_PK_D] = Key::D;
			mapKeys[DOM_PK_E] = Key::E; mapKeys[DOM_PK_F] = Key::F; mapKeys[DOM_PK_G] = Key::G; mapKeys[DOM_PK_H] = Key::H;
			mapKeys[DOM_PK_I] = Key::I; mapKeys[DOM_PK_J] = Key::J; mapKeys[DOM_PK_K] = Key::K; mapKeys[DOM_PK_L] = Key::L;
			mapKeys[DOM_PK_M] = Key::M; mapKeys[DOM_PK_N] = Key::N; mapKeys[DOM_PK_O] = Key::O; mapKeys[DOM_PK_P] = Key::P;
			mapKeys[DOM_PK_Q] = Key::Q; mapKeys[DOM_PK_R] = Key::R; mapKeys[DOM_PK_S] = Key::S; mapKeys[DOM_PK_T] = Key::T;
			mapKeys[DOM_PK_U] = Key::U; mapKeys[DOM_PK_V] = Key::V; mapKeys[DOM_PK_W] = Key::W; mapKeys[DOM_PK_X] = Key::X;
			mapKeys[DOM_PK_Y] = Key::Y; mapKeys[DOM_PK_Z] = Key::Z;
			mapKeys[DOM_PK_0] = Key::K0; mapKeys[DOM_PK_1] = Key::K1; mapKeys[DOM_PK_2] = Key::K2;
			mapKeys[DOM_PK_3] = Key::K3; mapKeys[DOM_PK_4] = Key::K4; mapKeys[DOM_PK_5] = Key::K5;
			mapKeys[DOM_PK_6] = Key::K6; mapKeys[DOM_PK_7] = Key::K7; mapKeys[DOM_PK_8] = Key::K8;
			mapKeys[DOM_PK_9] = Key::K9;
			mapKeys[DOM_PK_F1] = Key::F1; mapKeys[DOM_PK_F2] = Key::F2; mapKeys[DOM_PK_F3] = Key::F3; mapKeys[DOM_PK_F4] = Key::F4;
			mapKeys[DOM_PK_F5] = Key::F5; mapKeys[DOM_PK_F6] = Key::F6; mapKeys[DOM_PK_F7] = Key::F7; mapKeys[DOM_PK_F8] = Key::F8;
			mapKeys[DOM_PK_F9] = Key::F9; mapKeys[DOM_PK_F10] = Key::F10; mapKeys[DOM_PK_F11] = Key::F11; mapKeys[DOM_PK_F12] = Key::F12;
			mapKeys[DOM_PK_ARROW_UP] = Key::UP; mapKeys[DOM_PK_ARROW_DOWN] = Key::DOWN;
			mapKeys[DOM_PK_ARROW_LEFT] = Key::LEFT; mapKeys[DOM_PK_ARROW_RIGHT] = Key::RIGHT;
			mapKeys[DOM_PK_SPACE] = Key::SPACE; mapKeys[DOM_PK_TAB] = Key::TAB;
			mapKeys[DOM_PK_SHIFT_LEFT] = Key::SHIFT; mapKeys[DOM_PK_SHIFT_RIGHT] = Key::SHIFT;
			mapKeys[DOM_PK_CONTROL_LEFT] = Key::CTRL; mapKeys[DOM_PK_CONTROL_RIGHT] = Key::CTRL;
			mapKeys[DOM_PK_INSERT] = Key::INS; mapKeys[DOM_PK_DELETE] = Key::DEL; mapKeys[DOM_PK_HOME] = Key::HOME;
			mapKeys[DOM_PK_END] = Key::END; mapKeys[DOM_PK_PAGE_UP] = Key::PGUP; mapKeys[DOM_PK_PAGE_DOWN] = Key::PGDN;
			mapKeys[DOM_PK_BACKSPACE] = Key::BACK; mapKeys[DOM_PK_ESCAPE] = Key::ESCAPE;
			mapKeys[DOM_PK_ENTER] = Key::ENTER; mapKeys[DOM_PK_NUMPAD_EQUAL] = Key::EQUALS;
			mapKeys[DOM_PK_NUMPAD_ENTER] = Key::ENTER; mapKeys[DOM_PK_PAUSE] = Key::PAUSE;
			mapKeys[DOM_PK_SCROLL_LOCK] = Key::SCROLL;
			mapKeys[DOM_PK_NUMPAD_0] = Key::NP0; mapKeys[DOM_PK_NUMPAD_1] = Key::NP1; mapKeys[DOM_PK_NUMPAD_2] = Key::NP2;
			mapKeys[DOM_PK_NUMPAD_3] = Key::NP3; mapKeys[DOM_PK_NUMPAD_4] = Key::NP4; mapKeys[DOM_PK_NUMPAD_5] = Key::NP5;
			mapKeys[DOM_PK_NUMPAD_6] = Key::NP6; mapKeys[DOM_PK_NUMPAD_7] = Key::NP7; mapKeys[DOM_PK_NUMPAD_8] = Key::NP8;
			mapKeys[DOM_PK_NUMPAD_9] = Key::NP9;
			mapKeys[DOM_PK_NUMPAD_MULTIPLY] = Key::NP_MUL; mapKeys[DOM_PK_NUMPAD_DIVIDE] = Key::NP_DIV;
			mapKeys[DOM_PK_NUMPAD_ADD] = Key::NP_ADD; mapKeys[DOM_PK_NUMPAD_SUBTRACT] = Key::NP_SUB;
			mapKeys[DOM_PK_NUMPAD_DECIMAL] = Key::NP_DECIMAL;
			mapKeys[DOM_PK_PERIOD] = Key::PERIOD; mapKeys[DOM_PK_EQUAL] = Key::EQUALS;
			mapKeys[DOM_PK_COMMA] = Key::COMMA; mapKeys[DOM_PK_MINUS] = Key::MINUS;
			mapKeys[DOM_PK_CAPS_LOCK] = Key::CAPS_LOCK;
			mapKeys[DOM_PK_SEMICOLON] = Key::OEM_1;	mapKeys[DOM_PK_SLASH] = Key::OEM_2; mapKeys[DOM_PK_BACKQUOTE] = Key::OEM_3;
			mapKeys[DOM_PK_BRACKET_LEFT] = Key::OEM_4; mapKeys[DOM_PK_BACKSLASH] = Key::OEM_5; mapKeys[DOM_PK_BRACKET_RIGHT] = Key::OEM_6;
			mapKeys[DOM_PK_QUOTE] = Key::OEM_7; mapKeys[DOM_PK_BACKSLASH] = Key::OEM_8;

			emscripten_set_keydown_callback("#canvas", 0, 1, keyboard_callback);
			emscripten_set_keyup_callback("#canvas", 0, 1, keyboard_callback);

			emscripten_set_wheel_callback("#canvas", 0, 1, wheel_callback);
			emscripten_set_mousedown_callback("#canvas", 0, 1, mouse_callback);
			emscripten_set_mouseup_callback("#canvas", 0, 1, mouse_callback);
			emscripten_set_mousemove_callback("#canvas", 0, 1, mouse_callback);

			emscripten_set_touchstart_callback("#canvas", 0, 1, touch_callback);
			emscripten_set_touchmove_callback("#canvas", 0, 1, touch_callback);
			emscripten_set_touchend_callback("#canvas", 0, 1, touch_callback);

			emscripten_set_blur_callback("#canvas", 0, 1, focus_callback);
			emscripten_set_focus_callback("#canvas", 0, 1, focus_callback);
			
#pragma warning disable format
			EM_ASM( window.onunload = Module._v_OnPageUnload; );

			EM_ASM({

			Module.v_AspectRatio = $0 / $1;

			Module.v_AssumeDefaultShells = (document.querySelectorAll('.emscripten').length >= 3) ? true : false;

			var v_ResizeHandler = function()
			{
				
				let isFullscreen = (document.fullscreenElement != null);

				let width  = (isFullscreen) ? window.innerWidth  : Module.canvas.parentNode.clientWidth;
				let height = (isFullscreen) ? window.innerHeight : Module.canvas.parentNode.clientHeight;

				let viewWidth  = width;
				let viewHeight = width / Module.v_AspectRatio;

				if(viewHeight > height)
				{
					viewWidth  = height * Module.v_AspectRatio;
					viewHeight = height;
				}

				viewWidth  = parseInt(viewWidth);
				viewHeight = parseInt(viewHeight);

				setTimeout(function()
				{
					
					if(Module.v_AssumeDefaultShells)
						Module.canvas.parentNode.setAttribute('style', 'width: 100%; height: 70vh; margin-left: auto; margin-right: auto;');

					Module.canvas.setAttribute('width', viewWidth);
					Module.canvas.setAttribute('height', viewHeight);
					Module.canvas.setAttribute('style', `width: ${viewWidth}px; height: ${viewHeight}px;`);

					Module._v_PGE_UpdateWindowSize(viewWidth, viewHeight);

					Module.canvas.focus();
				}, 200);
			};

			var v_Init = function()
			{
				if(Module.v_AspectRatio === undefined)
				{
					setTimeout(function() { Module.v_Init(); }, 50);
					return;
				}
					
				let resizeObserver = new ResizeObserver(function(entries)
				{
					Module.v_ResizeHandler();
				}).observe(Module.canvas.parentNode);

				let mutationObserver = new MutationObserver(function(mutationsList, observer)
				{
					setTimeout(function() { Module.v_ResizeHandler(); },  200);
				}).observe(Module.canvas.parentNode, { attributes: false, childList: true, subtree: false });

				window.addEventListener('fullscreenchange', function(e)
				{
					setTimeout(function() { Module.v_ResizeHandler();},  200);
				});
			};

			Module.v_ResizeHandler = (Module.v_ResizeHandler != undefined) ? Module.v_ResizeHandler : v_ResizeHandler;
			Module.v_Init          = (Module.v_Init          != undefined) ? Module.v_Init : v_Init;

			Module.v_Init();

			}, vWindowSize.x, vWindowSize.y); 
#pragma warning restore format
			return v::rcode::OK;
		}

		void UpdateWindowSize(int width, int height)
		{
			ptrPGE->v_UpdateWindowSize(width, height);
		}

		static EM_BOOL focus_callback(int eventType, const EmscriptenFocusEvent* focusEvent, void* userData) 
		{
			if (eventType == EMSCRIPTEN_EVENT_BLUR)
			{
				ptrPGE->v_UpdateKeyFocus(false);
				ptrPGE->v_UpdateMouseFocus(false);
			}
			else if (eventType == EMSCRIPTEN_EVENT_FOCUS)
			{
				ptrPGE->v_UpdateKeyFocus(true);
				ptrPGE->v_UpdateMouseFocus(true);
			}

			return 0;
		}

		static EM_BOOL keyboard_callback(int eventType, const EmscriptenKeyboardEvent* e, void* userData)
		{
			if (eventType == EMSCRIPTEN_EVENT_KEYDOWN)
				ptrPGE->v_UpdateKeyState(mapKeys[emscripten_compute_dom_pk_code(e->code)], true);

			if (eventType == EMSCRIPTEN_EVENT_KEYUP)
				ptrPGE->v_UpdateKeyState(mapKeys[emscripten_compute_dom_pk_code(e->code)], false);

			return EM_TRUE;
		}

		static EM_BOOL wheel_callback(int eventType, const EmscriptenWheelEvent* e, void* userData)
		{
			if (eventType == EMSCRIPTEN_EVENT_WHEEL)
				ptrPGE->v_UpdateMouseWheel(-1 * e->deltaY);

			return EM_TRUE;
		}

		static EM_BOOL touch_callback(int eventType, const EmscriptenTouchEvent* e, void* userData)
		{
			
			if (eventType == EMSCRIPTEN_EVENT_TOUCHMOVE)
			{
				ptrPGE->v_UpdateMouse(e->touches->targetX, e->touches->targetY);
			}

			if (eventType == EMSCRIPTEN_EVENT_TOUCHSTART)
			{
				ptrPGE->v_UpdateMouse(e->touches->targetX, e->touches->targetY);
				ptrPGE->v_UpdateMouseState(0, true);
			}

			if (eventType == EMSCRIPTEN_EVENT_TOUCHEND)
			{
				ptrPGE->v_UpdateMouseState(0, false);
			}

			return EM_TRUE;
		}

		static EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent* e, void* userData)
		{
			
			if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE)
				ptrPGE->v_UpdateMouse(e->targetX, e->targetY);

			if (e->button == 0) 
			{
				if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN)
					ptrPGE->v_UpdateMouseState(0, true);
				else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP)
					ptrPGE->v_UpdateMouseState(0, false);
			}

			if (e->button == 2) 
			{
				if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN)
					ptrPGE->v_UpdateMouseState(1, true);
				else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP)
					ptrPGE->v_UpdateMouseState(1, false);

			}

			if (e->button == 1) 
			{
				if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN)
					ptrPGE->v_UpdateMouseState(2, true);
				else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP)
					ptrPGE->v_UpdateMouseState(2, false);

				return EM_TRUE;
			}

			return EM_FALSE;
		}

		virtual v::rcode SetWindowTitle(const std::string& s) override
		{ emscripten_set_window_title(s.c_str()); return v::OK; }

		virtual v::rcode StartSystemEventLoop() override 
		{ return v::OK; }

		virtual v::rcode HandleSystemEvent() override
		{ return v::OK; }

		static void MainLoop()
		{
			v::Platform::ptrPGE->v_CoreUpdate();
			if (!ptrPGE->v_IsRunning())
			{
				if (ptrPGE->OnUserDestroy())
				{
					emscripten_cancel_main_loop();
					platform->ApplicationCleanUp();
				}
				else
				{
					ptrPGE->v_Reanimate();
				}
			}
		}
	};

	v::rcode PixelGameEngine::Start()
	{
		if (platform->ApplicationStartUp() != v::OK) return v::FAIL;

		if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != v::OK) return v::FAIL;
		v_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		if (platform->ThreadStartUp() == v::FAIL)	return v::FAIL;

		v_PrepareEngine();

		bAtomActive = true;

		for (auto& ext : vExtensions) ext->OnBeforeUserCreate();
		if (!OnUserCreate()) bAtomActive = false;
		for (auto& ext : vExtensions) ext->OnAfterUserCreate();

		platform->StartSystemEventLoop();

		emscripten_set_main_loop(&Platform_Emscripten::MainLoop, 0, 1);

		if (platform->ApplicationCleanUp() != v::OK) return v::FAIL;
		return v::OK;
	}
}

extern "C" 
{
	EMSCRIPTEN_KEEPALIVE inline void v_PGE_UpdateWindowSize(int width, int height)
	{
		emscripten_set_canvas_element_size("#canvas", width, height);
		
		((v::Platform_Emscripten*)v::platform.get())->UpdateWindowSize(width, height);
	}
}

#endif

#pragma endregion

#endif 

#pragma region pge_config
namespace v
{
	void PixelGameEngine::v_ConfigureSystem()
	{

		v::Sprite::loader = nullptr;

#if defined(v_IMAGE_GDI)
		v::Sprite::loader = std::make_unique<v::ImageLoader_GDIPlus>();
#endif

#if defined(v_IMAGE_LIBPNG)
		v::Sprite::loader = std::make_unique<v::ImageLoader_LibPNG>();
#endif

#if defined(v_IMAGE_STB)
		v::Sprite::loader = std::make_unique<v::ImageLoader_STB>();
#endif

#if defined(v_IMAGE_CUSTOM_EX)
		v::Sprite::loader = std::make_unique<v_IMAGE_CUSTOM_EX>();
#endif

#if defined(v_PLATFORM_HEADLESS)
		platform = std::make_unique<v::Platform_Headless>();
#endif

#if defined(v_PLATFORM_WINAPI)
		platform = std::make_unique<v::Platform_Windows>();
#endif

#if defined(v_PLATFORM_X11)
		platform = std::make_unique<v::Platform_Linux>();
#endif

#if defined(v_PLATFORM_GLUT)
		platform = std::make_unique<v::Platform_GLUT>();
#endif

#if defined(v_PLATFORM_EMSCRIPTEN)
		platform = std::make_unique<v::Platform_Emscripten>();
#endif

#if defined(v_PLATFORM_CUSTOM_EX)
		platform = std::make_unique<v_PLATFORM_CUSTOM_EX>();
#endif

#if defined(v_GFX_HEADLESS)
		renderer = std::make_unique<v::Renderer_Headless>();
#endif

#if defined(v_GFX_OPENGL10)
		renderer = std::make_unique<v::Renderer_OGL10>();
#endif

#if defined(v_GFX_OPENGL33)
		renderer = std::make_unique<v::Renderer_OGL33>();
#endif

#if defined(v_GFX_OPENGLES2)
		renderer = std::make_unique<v::Renderer_OGLES2>();
#endif

#if defined(v_GFX_DIRECTX10)
		renderer = std::make_unique<v::Renderer_DX10>();
#endif

#if defined(v_GFX_DIRECTX11)
		renderer = std::make_unique<v::Renderer_DX11>();
#endif

#if defined(v_GFX_CUSTOM_EX)
		renderer = std::make_unique<v_RENDERER_CUSTOM_EX>();
#endif

		platform->ptrPGE = this;
		renderer->ptrPGE = this;

	}
}

#pragma endregion

#endif 

