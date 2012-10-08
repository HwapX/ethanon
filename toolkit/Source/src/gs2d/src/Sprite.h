/*--------------------------------------------------------------------------------------
 Ethanon Engine (C) Copyright 2008-2012 Andre Santee
 http://www.asantee.net/ethanon/

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so, subject to the
	following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--------------------------------------------------------------------------------------*/

#ifndef GS2D_SPRITE_H_
#define GS2D_SPRITE_H_

#include "Texture.h"
#include <boost/shared_array.hpp>

namespace gs2d {

// TO-DO: move following enums into Sprite class
enum GS_ENTITY_ORIGIN
{
	GSEO_DEFAULT = 0,
	GSEO_CENTER = 1,
	GSEO_CENTER_BOTTOM = 2,
	GSEO_CENTER_TOP = 3,
	GSEO_RECT_CENTER = 4,
	GSEO_RECT_CENTER_BOTTOM = 5,
	GSEO_RECT_CENTER_TOP = 6,
};

enum GS_RECT_MODE
{
	GSRM_TWO_TRIANGLES = 0,
	GSRM_THREE_TRIANGLES = 1,
	GSRM_FOUR_TRIANGLES,
};

/**
 * \brief Draws and manages sprites
 *
 * This class encapsulates all the math and API calls behind
 * sprite drawing. It stores a bitmap buffer and is capable of rendering
 * it as a sprite as many times as necessary and at different places
 * and shapes.
 */
class Sprite
{
public:
	enum TYPE
	{
		T_NOT_LOADED = 0,
		T_BITMAP = 1,
		T_TARGET = 2,
		T_RELOAD = 3,
	};
	Sprite();

	virtual bool LoadSprite(
		VideoWeakPtr video,
		GS_BYTE* pBuffer,
		const unsigned int bufferLength,
		Color mask = constant::ZERO,
		const unsigned int width = 0,
		const unsigned int height = 0) = 0;

	virtual bool LoadSprite(
		VideoWeakPtr video,
		const str_type::string& fileName,
		Color mask = constant::ZERO,
		const unsigned int width = 0,
		const unsigned int height = 0) = 0;

	virtual bool CreateRenderTarget(
		VideoWeakPtr video,
		const unsigned int width,
		const unsigned int height,
		const GS_TARGET_FORMAT format = GSTF_DEFAULT) = 0;

	virtual bool Draw(
		const math::Vector2& v2Pos,
		const Color& color = constant::WHITE,
		const float angle = 0.0f,
		const math::Vector2& v2Scale = math::Vector2(1.0f,1.0f)) = 0;

	virtual bool DrawShaped(
		const math::Vector2 &v2Pos,
		const math::Vector2 &v2Size,
		const Color& color0,
		const Color& color1,
		const Color& color2,
		const Color& color3,
		const float angle = 0.0f) = 0;

	virtual bool SaveBitmap(
		const wchar_t* wcsName,
		const GS_BITMAP_FORMAT fmt,
		math::Rect2D* pRect = 0) = 0;

	virtual bool DrawShapedFast(const math::Vector2 &v2Pos, const math::Vector2 &v2Size, const Color& color) = 0;

	virtual bool DrawOptimal(
		const math::Vector2 &v2Pos,
		const Color& color = constant::WHITE,
		const float angle = 0.0f,
		const math::Vector2 &v2Size = math::Vector2(-1,-1)) = 0;

	virtual void BeginFastRendering() = 0;
	virtual void EndFastRendering() = 0;

	virtual TextureWeakPtr GetTexture() = 0;

	virtual Texture::PROFILE GetProfile() const = 0;
	virtual math::Vector2i GetBitmapSize() const = 0;
	virtual math::Vector2 GetBitmapSizeF() const = 0;

	virtual void FlipX(const bool flip) = 0;
	virtual void FlipY(const bool flip) = 0;
	virtual void FlipX() = 0;
	virtual void FlipY() = 0;
	virtual bool GetFlipX() const = 0;
	virtual bool GetFlipY() const = 0;

	virtual void SetScroll(const math::Vector2 &v2Scroll) = 0;
	virtual math::Vector2 GetScroll() const = 0;

	virtual void SetMultiply(const math::Vector2 &v2Multiply) = 0;
	virtual math::Vector2 GetMultiply() const = 0;

	virtual TYPE GetType() const = 0;
	virtual boost::any GetTextureObject() = 0;

	virtual void GenerateBackup() = 0;
	virtual bool SetAsTexture(const unsigned int passIdx) = 0;

	/// Used on API's that must handle lost devices
	virtual void OnLostDevice() = 0;

	/// Used on API's that must handle lost devices
	virtual void RecoverFromBackup() = 0;

	virtual void SetSpriteDensityValue(const float value) = 0;
	virtual float GetSpriteDensityValue() const = 0;

	// Non pure virtual functions:
	virtual void SetRectMode(const GS_RECT_MODE mode);
	virtual GS_RECT_MODE GetRectMode() const;
	virtual bool SetupSpriteRects(const unsigned int columns, const unsigned int rows);
	virtual bool SetRect(const unsigned int column, const unsigned int row);
	virtual bool SetRect(const unsigned int rect);
	virtual void SetRect(const math::Rect2Df& rect);
	virtual void UnsetRect();
	virtual unsigned int GetNumRects() const;
	virtual math::Rect2Df GetRect() const;
	virtual math::Rect2Df GetRect(const unsigned int rect) const;
	virtual unsigned int GetRectIndex() const;
	virtual unsigned int GetNumRows() const;
	virtual unsigned int GetNumColumns() const;
	virtual math::Vector2 GetFrameSize() const;

	virtual bool Stretch(
		const math::Vector2 &a,
		const math::Vector2 &b,
		const float width,
		const Color& color0 = constant::WHITE,
		const Color& color1 = constant::WHITE);

	virtual void SetOrigin(const GS_ENTITY_ORIGIN origin);
	virtual void SetOrigin(const math::Vector2& v2Custom);
	virtual math::Vector2 GetOrigin() const;

protected:
	unsigned int  m_currentRect;
	boost::shared_array<math::Rect2Df> m_rects;
	math::Rect2Df m_rect;
	unsigned int m_nColumns, m_nRows;
	GS_RECT_MODE m_rectMode;
	float m_densityValue;
	math::Vector2 m_normalizedOrigin;
};

} // namespace gs2d

#endif
