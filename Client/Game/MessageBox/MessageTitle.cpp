#include "StdAfx.h"
#include "MessageBoxTitle.h"

namespace MESSAGEBOX
{
	Title::Title()
	{

	}
	Title::~Title()
	{

	}
	void Title::Init()
	{
		m_pFontHeigh = FONTHANDLE->MakeFont("Frutiger LT 55 Roman", 24, 0, FALSE, FALSE);
		m_pFont = FONTHANDLE->MakeFont("Arial", 16, 0, FALSE, FALSE);

		m_pImageLeft = UI::ImageLoader::LoadImage_("Resources\\UI\\Title\\Left.png");
		m_pImageCenter = UI::ImageLoader::LoadImage_("Resources\\UI\\Title\\Center.png");
		m_pImageRight = UI::ImageLoader::LoadImage_("Resources\\UI\\Title\\Right.png");
	}
	void Title::AddText(const char *pszText)
	{
		pszText ? AddTitle(sTitle(Point2D(0, 180), trim(std::string(pszText)), D3DXCOLOR(255, 185, 50, 255), MAX_DURATION_TITLEBOX)) : 0;
	}
	void Title::AddTitle(sTitle t)
	{
		BOOL bFound = FALSE;

		for (auto &v : m_vTitles)
		{
			if (v.strText.compare(t.strText) == 0)
			{
				bFound = TRUE;
				break;
			}
		}

		if (!bFound)
		{
			m_vTitles.insert(m_vTitles.begin(), t);

			for (auto &v : m_vTitles)
			{
				if (!v.strText.empty())
					v.bMoveToDown = TRUE;
			}

			if (m_vTitles.size() > MAX_MESSAGES)
				m_vTitles.pop_back();
		}
	}
	void Title::Reader()
	{
		int i = 0;

		for (auto &v : m_vTitles)
		{
			if (i == 1)
				v.d3dColor.a = 127;
			else if (i == 2)
				v.d3dColor.a = 70;

			v.iOpacity = (int)(float)(v.d3dColor.a * 1.0f);

			m_pFontHeigh ? m_pFontHeigh->Draw(RECT{ 0, v.sPosition.iY + 2, GRAPHICENGINE->GetBackWidth(), 24 }, v.strText, DT_CENTER | DT_EXPANDTABS | DT_NOCLIP, D3DCOLOR_ARGB((int)v.iOpacity, 0, 0, 0)) : 0;
			m_pFontHeigh ? m_pFontHeigh->Draw(RECT{ 0, v.sPosition.iY, GRAPHICENGINE->GetBackWidth(), 24 }, v.strText, DT_CENTER | DT_EXPANDTABS | DT_NOCLIP, D3DCOLOR_ARGB((int)v.iOpacity, (int)v.d3dColor.r, (int)v.d3dColor.g, (int)v.d3dColor.b)) : 0;

			i++;
		}
	}
	void Title::RenderTextMiddle(const char *pszText)
	{
		std::string str = trim((std::string)pszText);

		int iW = m_pFont ? m_pFont->GetWidthText(str.c_str()) : 0;
		int iH = m_pImageLeft->GetHeight();

		int iX = (GRAPHICENGINE->GetBackWidth() >> 1) - ((iW + 64) >> 1);
		int iY = (GRAPHICENGINE->GetBackHeight() >> 1) - (m_pImageLeft->GetHeight() >> 1);

		UI::ImageRender::Render(m_pImageLeft, iX, iY, m_pImageLeft->GetWidth(), m_pImageLeft->GetHeight(), -1);
		UI::ImageRender::Render(m_pImageCenter, iX + 32, iY, iW, m_pImageLeft->GetHeight(), -1);
		UI::ImageRender::Render(m_pImageRight, iX + 32 + iW, iY, m_pImageLeft->GetWidth(), m_pImageLeft->GetHeight(), -1);

		m_pFont ? m_pFont->Draw(RECT{ iX + 32,iY + 32,iW,iH }, str, 0, -1) : 0;
	}
	void Title::Update(float fTime)
	{
		int i = 0;

		for (auto &v : m_vTitles)
		{
			if (v.bMoveToDown)
			{
				float fTimeUpdate = v.fTime / MAX_DURATION_ANIM;
				float f = X3D::easeInOutCircf(fTimeUpdate, 0.0f, 1.0f, 1.0f);

				if (v.iBasePositionY == 0)
					v.iBasePositionY = v.sPosition.iY;

				if (i == 0)
					v.sPosition.iY = (int)(v.iBasePositionY * (1.0f - f));
				else
					v.sPosition.iY = (int)(v.iBasePositionY + (24 * (1.0f - f)));
			}

			if (v.fTime > 0.0f)
				v.fTime -= fTime;
			else
			{
				v.bMoveToDown = FALSE;
				v.fTime = 100.0f;
				v.iBasePositionY = 0;
			}

			i++;
		}
	}
	void Title::Tick()
	{
		for (auto &v : m_vTitles)
		{
			v.sDuration--;

			if (v.sDuration <= 3 && !v.bCanHide)
			{
				v.bCanHide = TRUE;
				v.fTime = 100.0f;
			}
			if (v.sDuration <= 0)
				m_vTitles.pop_back();
		}
	}
}