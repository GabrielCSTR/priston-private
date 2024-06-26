#include "StdAfx.h"

HoMessage	ChatMessage;
BOOL    HoMessage::MessageFrameSelectFlag = TRUE;

//Data Resource甫 佬绢柯促.
HoMessage::HoMessage()
{
}

HoMessage::~HoMessage()
{
}


int HoMessage::Init()
{
	TextStartPosY = 0;

	BoxImage1[0] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox0.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[1] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox1.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[2] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox2.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[3] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox3.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[4] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox4.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[5] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox5.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[6] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox6.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[7] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox7.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage1[8] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox8.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	BoxImage2[0] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox00.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage2[1] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox22.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage2[2] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox66.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage2[3] = CreateTextureMaterial("StartImage\\MessageBox\\NormalBox\\MessageBox88.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	BoxImage3[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[4] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox004.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage3[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBox009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	BoxImage4[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BoxImage4[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\MessageBoxa009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ClanBoxImage[0] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\clanNameBox01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage[1] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\clanNameBox02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage[2] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\clanNameBox03.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ClanBoxImage2[0] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxTopLeft.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[1] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxTopCenter.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[2] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxTopRight.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[3] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxLeft.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[4] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxCenter.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[5] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxRight.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[6] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxBottomLeft.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[7] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxBottomCenter.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ClanBoxImage2[8] = CreateTextureMaterial("StartImage\\MessageBox\\ClanBox\\BoxBottomRight.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ShopBoxByeImage1[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage1[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBox009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ShopBoxByeImage2[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxByeImage2[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\BMessageBoxA009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ShopBoxSellImage1[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage1[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBox009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ShopBoxSellImage2[0] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA000.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[1] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA001.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[2] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA002.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[3] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA003.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[5] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA005.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[6] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA006.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[7] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA007.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[8] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA008.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	ShopBoxSellImage2[9] = CreateTextureMaterial("StartImage\\MessageBox\\ChatBox\\GMessageBoxA009.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	BellaIconImage[0] = CreateTextureMaterial("StartImage\\MessageBox\\BellaBox\\Bella_01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BellaIconImage[1] = CreateTextureMaterial("StartImage\\MessageBox\\BellaBox\\Bella_02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	BellaIconImage[2] = CreateTextureMaterial("StartImage\\MessageBox\\BellaBox\\Bella_03.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	VipIconImage = CreateTextureMaterial("StartImage\\MessageBox\\VipBox\\Vip.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	return TRUE;
}

void HoMessage::DrawMessageBox(int x, int y, char *message, int boxAttrib, int Color)
{
	int messageSize = lstrlen(message);
	int messageWidth = messageSize / 2;
	if (messageWidth < 16)
		messageWidth = 16;

	int messageHeight = 4;

	TextStartPosY = y + 6;
	if (messageWidth == 0)
		return;

	if (x <= 0)
		x = 0;
	if (y <= 0)
		y = 0;

	if (x + 16 * 2 + messageWidth * 12 >= RESOLUTION_WIDTH)
		x = RESOLUTION_WIDTH - messageWidth * 12 - 16 * 2;

	if (y + 16 * 2 + messageHeight * 12 >= RESOLUTION_HEIGHT)
		y = RESOLUTION_HEIGHT - messageHeight * 12 - 16 * 2;


	if (boxAttrib == BOX_ONE)
	{
		dsDrawTexImage(BoxImage1[0], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[2], x + 16 + messageWidth * 12, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[6], x, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[8], x + 16 + messageWidth * 12, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	}
	else if (boxAttrib == BOX_TWO)
	{
		dsDrawTexImage(BoxImage2[0], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[1], x + 16 + messageWidth * 12, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[2], x, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[3], x + 16 + messageWidth * 12, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	}

	int m, n;
	if (boxAttrib == BOX_ONE || boxAttrib == BOX_TWO)
	{
		for (m = 0; m < messageWidth; m++)
		{
			dsDrawTexImage(BoxImage1[1], x + 16 + 12 * m, y, 12, 16, 16, 16, 0, 0, 12, 16, 255);
			dsDrawTexImage(BoxImage1[7], x + 16 + 12 * m, y + 16 + (12 * messageHeight), 12, 16, 16, 16, 0, 0, 12, 16, 255);
		}

		for (m = 0; m < messageHeight; m++)
		{
			dsDrawTexImage(BoxImage1[3], x, y + 16 + (12 * m), 16, 12, 16, 16, 0, 0, 16, 12, 255);
			dsDrawTexImage(BoxImage1[5], x + 16 + 12 * messageWidth, y + 16 + (12 * m), 16, 12, 16, 16, 0, 0, 16, 12, 255);
		}

		for (m = 0; m < messageWidth; m++)
		{
			for (n = 0; n < messageHeight; n++)
				dsDrawTexImage(BoxImage1[4], x + 16 + 12 * m, y + 16 + 12 * n, 12, 12, 32, 32, 0, 0, 12, 12, 255);
		}
	}

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, message, sizeof(message));

	int	textStartPosX;

	Width = messageWidth * 12 + 16 * 2;

	if (messageSize <= 16)
		textStartPosX = Width / 2 - (messageSize / 4) * 12 - 6;
	else
		textStartPosX = Width / 2 - (messageSize / 4) * 12;

	dsTextLineOut(0, x + textStartPosX, TextStartPosY + 16, message, lstrlen(message), Color);

	PosX = x;
	PosY = y;
}
int HoDrawLinearTexImage(int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, DWORD color)
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((x >= clipRight) || (y >= clipBottom) || ((x + texW) <= clipLeft) || ((y + texH) <= clipTop))
		return FALSE;

	float x1 = x - 0.5f;
	float y1 = y - 0.5f;
	float x2 = x1 + w;
	float y2 = y1 + h;

	float texSizeWidth = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Width;
	float texSizeHeight = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Height;

	float u1 = ((float)texX / (float)texSizeWidth);
	float v1 = ((float)texY / (float)texSizeHeight);

	float u2 = ((float)texX + texW) / (float)texSizeWidth;
	float v2 = ((float)texY + texH) / (float)texSizeHeight;

	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	int r, g, b;
	r = color & 0xff;
	g = (color & 0xff00) >> 8;
	b = (color & 0xff0000) >> 16;


	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = D3DCOLOR_RGBA(r, g, b, 255);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = u1;
	tlVertex[0].tv = v1;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = u1;
	tlVertex[1].tv = v2;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = u2;
	tlVertex[2].tv = v1;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = u2;
	tlVertex[3].tv = v2;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;

}


int HoDrawTexImage(int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, int Transp)
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((x >= clipRight) || (y >= clipBottom) || ((x + texW) <= clipLeft) || ((y + texH) <= clipTop))
		return FALSE;

	float x1 = x - 0.5f;
	float y1 = y - 0.5f;
	float x2 = x1 + w;
	float y2 = y1 + h;

	float texSizeWidth = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Width;
	float texSizeHeight = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Height;

	float u1 = ((float)texX / (float)texSizeWidth);
	float v1 = ((float)texY / (float)texSizeHeight);

	float u2 = ((float)texX + texW) / (float)texSizeWidth;
	float v2 = ((float)texY + texH) / (float)texSizeHeight;

	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = u1;
	tlVertex[0].tv = v1;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = u1;
	tlVertex[1].tv = v2;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = u2;
	tlVertex[2].tv = v1;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = u2;
	tlVertex[3].tv = v2;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}

int HoDrawTexImage(int Mat, int x, int y, int w, int h, int texX, int texY, int texW, int texH, int Transp)
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((x >= clipRight) || (y >= clipBottom) || ((x + texW) <= clipLeft) || ((y + texH) <= clipTop))
		return FALSE;

	float x1 = (float)x - 0.5f;
	float y1 = (float)y - 0.5f;
	float x2 = x1 + (float)w;
	float y2 = y1 + (float)h;

	float texSizeWidth = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Width;
	float texSizeHeight = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Height;

	float u1 = ((float)texX / (float)texSizeWidth);
	float v1 = ((float)texY / (float)texSizeHeight);

	float u2 = ((float)texX + texW) / (float)texSizeWidth;
	float v2 = ((float)texY + texH) / (float)texSizeHeight;

	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = u1;
	tlVertex[0].tv = v1;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = u1;
	tlVertex[1].tv = v2;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = u2;
	tlVertex[2].tv = v1;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = u2;
	tlVertex[3].tv = v2;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}

int HoDrawTexImage(int Mat, int x, int y, int texX, int texY, int texW, int texH, int Transp)
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = RESOLUTION_WIDTH;
	clipBottom = RESOLUTION_HEIGHT;

	if ((x >= clipRight) || (y >= clipBottom) || ((x + texW) <= clipLeft) || ((y + texH) <= clipTop))
		return FALSE;

	float x1 = (float)x - 0.5f;
	float y1 = (float)y - 0.5f;
	float x2 = x1 + (float)texW;
	float y2 = y1 + (float)texH;

	float texSizeWidth = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Width;
	float texSizeHeight = (float)smMaterialGroup->smMaterial[Mat].smTexture[0]->Height;

	float u1 = ((float)texX / (float)texSizeWidth);
	float v1 = ((float)texY / (float)texSizeHeight);

	float u2 = ((float)texX + texW) / (float)texSizeWidth;
	float v2 = ((float)texY + texH) / (float)texSizeHeight;

	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = u1;
	tlVertex[0].tv = v1;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = u1;
	tlVertex[1].tv = v2;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = u2;
	tlVertex[2].tv = v1;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = u2;
	tlVertex[3].tv = v2;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}


void HoMessage::DrawClanName(int x, int y, char *clanName)
{
	x = x + 3;
	y = y - 12;

	if (clanName == NULL)
		return;
	int length = lstrlen(clanName);
	if (length < 1)
		return;

	HoDrawTexImage(ClanBoxImage[0], x, y, 16, 14, 0, 0, 16, 14, 255);

	for (int index = 0; index <= length; index++)
		HoDrawTexImage(ClanBoxImage[1], float(x + 16) + (float)index*5.5f, (float)y, 5.5f, 14.f, 0.f, 0.f, 5.5f, 14.f, 255);

	HoDrawTexImage(ClanBoxImage[2], float(x + 16) + (float)(length + 1)*5.5f, (float)y, 16.f, 14.f, 0.f, 0.f, 16.f, 14.f, 255);

	dsTextLineOut(0, x + 15, y + 3, clanName, lstrlen(clanName), D3DCOLOR_XRGB(0, 0, 0));
	dsTextLineOut(0, x + 15, y + 2, clanName, lstrlen(clanName), D3DCOLOR_XRGB(230, 255, 160));
}

void HoMessage::DrawClanMark(smTEXTUREHANDLE *clanMark, char *clanName, int x, int y, BOOL frameFlag)
{
	if (clanMark == NULL)
		return;

	if (frameFlag)
	{
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + 6, y, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + 11, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + 6, y + 5 + 11, 0, 0, 8, 8, 255);

		HoDrawTexImage(BoxImage3[3], x, y + 8, 0, 0, 8, 9, 255);
		HoDrawTexImage(BoxImage3[5], x + 11 + 6, y + 8, 0, 0, 8, 9, 255);

		HoDrawTexImage(BoxImage3[1], x + 8, y, 0, 0, 9, 8, 255);
		HoDrawTexImage(BoxImage3[7], x + 8, y + 8 + 8, 0, 0, 9, 8, 255);
	}

	UI::ImageRender::Render(clanMark->m_pTexture, x + 4, y + 4, 16, 16, 0, 0, -1);

	if (clanName != NULL)
		DrawClanName(x, y, clanName);
}

void HoMessage::DrawTwoLineMessage(int x, int y, char *message1, char *message2, DWORD color1, DWORD color2, smTEXTUREHANDLE *clanMark, BOOL selected, int bellaMarkIndex, int vipIndex)
{
	char MessageOne[64];
	char MessageTwo[64];

	if (message1 != NULL)
		lstrcpy(MessageOne, message1);

	if (message2 != NULL)
		lstrcpy(MessageTwo, message2);

	int messageWidth = 0;
	int messageHeight = 2;

	int messageTempLen1 = lstrlen(MessageOne);
	int messageTempLen2 = lstrlen(MessageTwo);

	int messageLen = messageTempLen2;
	if (messageTempLen1 > messageTempLen2)
		messageLen = messageTempLen1;

	if (clanMark != NULL)
	{
		if (messageLen < messageTempLen1 + 3)
			messageLen += 3;
	}

	int lineSize = messageLen;
	messageWidth = lineSize;
	x -= messageWidth / 2 * 6 + 18 / 2;
	y -= messageHeight * 14 + 8 * 2 + 8;

	DrawCharacterMessageFrame(x, y, messageWidth, messageHeight, false, selected);

	if (bellaMarkIndex > 0 && vipIndex > 0)
	{
		DrawBellaIcon(x + messageWidth - 6, y - 30, bellaMarkIndex);
		DrawVipIcon(x + messageWidth - 6 + 32, y - 30, vipIndex);
	}
	else if (bellaMarkIndex > 0)
	{
		DrawBellaIcon(x + 3 * messageWidth - 6, y - 30, bellaMarkIndex);
	}
	else if (vipIndex > 0)
	{
		DrawVipIcon(x + 3 * messageWidth - 6, y - 30, vipIndex);
	}

	DWORD Color;

	if (color1 == 0)
		Color = D3DCOLOR_XRGB(255, 255, 255);
	else
		Color = color1;

	if (messageTempLen1 > 1)
	{
		if (clanMark == NULL)
			dsTextLineOut(0, x + 9 + messageWidth * 6 / 2 - messageTempLen1 * 6 / 2, y + 5 + 2, MessageOne, messageTempLen1, Color);
		else
			dsTextLineOut(0, x + 9 + 6 * 3, y + 5 + 2, MessageOne, messageTempLen1, Color);
	}

	if (color2 == 0)
		Color = D3DCOLOR_XRGB(255, 255, 255);
	else
		Color = color2;

	if (messageTempLen2 > 0)
		dsTextLineOut(0, x + 9 + messageWidth * 6 / 2 - messageTempLen2 * 6 / 2, y + 5 + 2 + 16, MessageTwo, messageTempLen2, Color);

	if (clanMark != NULL)
	{
		if (MessageFrameSelectFlag)
			DrawClanMark(clanMark, NULL, x + 3, y);
		else
			DrawClanMark(clanMark, NULL, x + 7, y + 1);
	}
}

void HoMessage::DrawBellaIcon(int x, int y, int bellaIndex)
{
	switch (bellaIndex)
	{
	case 1:
		HoDrawTexImage(BellaIconImage[0], x, y, 0, 0, 32, 32, 255);
		break;
	case 2:
		HoDrawTexImage(BellaIconImage[1], x, y, 0, 0, 32, 32, 255);
		break;
		HoDrawTexImage(BellaIconImage[2], x, y, 0, 0, 32, 32, 255);
	case 3:
		break;
	}
}
void HoMessage::DrawVipIcon(int x, int y, int vipIndex)
{
	switch (vipIndex)
	{
	case 1:
		HoDrawTexImage(VipIconImage, x, y, 0, 0, 32, 32, 255);
		break;
	}
}
void HoMessage::DrawClanMessageFrame(int x, int y, int messageWidth, int messageHeight)
{
	HoDrawTexImage(ClanBoxImage2[0], x, y, 0, 0, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[2], x + 11 + messageWidth * 6, y, 5, 0, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[6], x, y + 13 + (messageHeight - 1) * 14 + 14, 0, 3, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[8], x + 11 + messageWidth * 6, y + 13 + (messageHeight - 1) * 14 + 14, 5, 3, 11, 13, 255);

	for (int m = 0; m < messageHeight; m++)
	{
		HoDrawTexImage(ClanBoxImage2[3], x, y + 13 + (14 * m), 0, 0, 11, 14, 255);
		HoDrawTexImage(ClanBoxImage2[5], x + 11 + messageWidth * 6, y + 13 + (14 * m), 5, 0, 11, 14, 255);
	}

	for (int m = 0; m < messageWidth; m++)
	{
		HoDrawTexImage(ClanBoxImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 13, 255);
		HoDrawTexImage(ClanBoxImage2[7], x + 11 + 6 * m, y + 13 + (14 * (messageHeight - 1)) + 14, 0, 3, 6, 13, 255);
	}
	for (int n = 0; n < messageHeight; n++)
	{
		for (int m = 0; m < messageWidth; m++)
		{
			if (n == 0)
				HoDrawTexImage(ClanBoxImage2[4], x + 11 + m * 6, y + 13, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(ClanBoxImage2[4], x + 11 + m * 6, y + 13 + (n - 1) * 14 + 14, 0, 0, 6, 14, 255);
		}
	}
}

void HoMessage::DrawCharacterMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(BoxImage4[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(BoxImage4[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(BoxImage4[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(BoxImage4[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		}
		for (int m = 0; m < messageHeight; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5, 0, 0, 8, 14, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}

		for (int m = 0; m < messageWidth; m++)
		{

			if (tailFlag)
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == messageWidth / 2 - 1)
				{

					HoDrawTexImage(BoxImage3[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(BoxImage4[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}
	for (int n = 0; n < messageHeight; n++)
	{
		for (int m = 0; m < messageWidth; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5 + (n - 1) * 16 + 14, 0, 0, 6, 16, 255);
		}
	}
}

void HoMessage::DrawCharacterMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(BoxImage4[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(BoxImage4[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(BoxImage4[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(BoxImage4[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		}

		for (int m = 0; m < linecount; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5, 0, 0, 8, 14, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}
		for (int m = 0; m < (messageWidth / 6) + 1; m++)
		{
			if (tailFlag)
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != ((messageWidth / 6 + 1) / 2 - 1) && m != ((messageWidth / 6 + 1) / 2))
				{
					HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == (messageWidth / 6 + 1) / 2 - 1)
				{

					HoDrawTexImage(BoxImage3[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(BoxImage4[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}
	for (int n = 0; n < linecount; n++)
	{
		for (int m = 0; m < messageWidth + 1; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5 + (n - 1)*messageHeight + 14, 0, 0, 6, 16, 255);
		}
	}
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(BoxImage4[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(BoxImage4[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(BoxImage4[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(BoxImage4[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		}
	}
}
int HoMessage::textarrange(char *teststr, bool clanm)
{
	int		len = 0;
	int		array1 = 0;
	int		array2 = 0;
	int		array3 = 0;
	BOOL	check = 0;

	ZeroMemory(textdata, sizeof(char) * 12 * 64);
	if (clanm)
	{
		textdata[0][0] = 0x20;
		textdata[0][1] = 0x20;
		textdata[0][2] = 0x20;
		textdata[0][3] = 0x20;
		array2 = 4;
	}
	len = (int)strlen(teststr);

	for (int i = 0; i < len; i++)
	{
		textdata[array1][array2] = teststr[i];
		if (array2 >= 30 || i == len - 1)
		{
			if (i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 1 && teststr[i] == 0x20) array2 = -1;
			else if (i != (len - 1) && CheckCode_2Byte(&teststr[i + 1]) == 1 && teststr[i + 1] == 0x20) array2 = -1;
			else if (i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 1 && teststr[i] != 0x20)
			{
				for (array3 = 0; array3 < 6; array3++)
				{
					check = 1;
					if (teststr[i - array3] == 0x20 && CheckCode_2Byte(&teststr[i - array3]) == 1) break;
					check = 0;
				}
				if (check)
				{
					memcpy(textdata[array1 + 1], teststr + (i - (array3 - 1)), array3);
					for (int z = 0; z < array3; z++) textdata[array1][array2 - z] = 0x20;
					array2 = (array3 - 1);
				}
				else
				{
					if (textdata[array1][array2] >= 65 && textdata[array1][array2] <= 90 || textdata[array1][array2] >= 97 && textdata[array1][array2] <= 122)
					{
						textdata[array1 + 1][0] = textdata[array1][array2];
						textdata[array1][array2] = '-';
						array2 = 0;
					}
					else array2 = -1;
				}
			}
			else if (i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 2)
			{
				if (CheckCode_2Byte(&teststr[i + 1]) == 1 && teststr[i + 1] == 0x20) array2 = -1;
				else
				{
					for (array3 = 0; array3 < 6; array3++)
					{
						check = 1;
						if (teststr[i - array3] == 0x20 && CheckCode_2Byte(&teststr[i - array3]) == 1) break;
						check = 0;
					}
					if (check)
					{
						memcpy(textdata[array1 + 1], teststr + (i - (array3 - 1)), array3);
						for (int z = 0; z < array3; z++) textdata[array1][array2 - z] = 0x20;
						array2 = (array3 - 1);
					}
					else
					{
						if (textdata[array1][array2] >= 65 && textdata[array1][array2] <= 90 ||
							textdata[array1][array2] >= 97 && textdata[array1][array2] <= 122)
						{
							textdata[array1 + 1][0] = textdata[array1][array2];
							textdata[array1][array2] = '-';
							array2 = 0;
						}
						else array2 = -1;
					}
				}
			}
			array1++;
		}
		array2++;
	}
	return array1;
}

void HoMessage::DrawClanMessage(int x, int y, char *message, int lineSize, DWORD color)
{
	int messageLen = strlen(message);

	int messageWidth = 0;
	int messageHeight = 1;

	if (lineSize != 0 && messageLen > lineSize)
	{
		messageHeight = messageLen / lineSize;
		if (messageHeight%lineSize)
			messageHeight += 1;

		messageWidth = lineSize;
	}
	else
		messageWidth = messageLen;

	if (messageWidth != 0)
		x -= messageWidth * 6 + 20;

	DrawClanMessageFrame(x, y, messageWidth, messageHeight);

	//测试
	if (lineSize > 10)
	{
		lineSize--;
		if (lineSize < messageWidth)
		{
			messageWidth--;
			lineSize++;
		}

	}
	////////

	char buffer[1024];

	if (lineSize != 0)
	{
		int start = 0;
		int end = 0;
		int lineCount = 0;

		for (int m = 0; m < messageHeight; m++)
		{
			memset(buffer, 0, sizeof(buffer));
			while (1)
			{
				if (message[end] == NULL)
					break;

				if (CheckCode_2Byte(&message[end]) == 2)
				{
					if ((lineCount + 2) > messageWidth)
						break;
					lineCount += 2;
					end += 2;

				}
				else
				{
					if ((lineCount + 1) > messageWidth)
						break;

					lineCount += 1;
					end += 1;

				}
			}
			memcpy(buffer, &message[start], end - start);

			dsTextLineOut(0, x + 11, y + 13 + m * 14, buffer, lstrlen(buffer), color);

			if (message[end] != NULL)
			{
				start = end;
				lineCount = 0;
			}
			else
				break;
		}
	}
	else
		dsTextLineOut(0, x + 11, y + 13, message, lstrlen(message), color);
}
void HoMessage::DrawCharacterMessage(int x, int y, char *message, int lineSize, smTEXTUREHANDLE *clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex, int vipIndex)
{
	bool CharNameFlag = false;
	bool MessageFlag = false;
	bool ClanMarkFlag = false;

	if (clanMark != NULL)
		ClanMarkFlag = true;

	char	cname[256];
	int linesize = 0;
	ZeroMemory(cname, sizeof(char) * 256);
	linesize = textarrange(message, ClanMarkFlag);

	if (message != NULL)
	{
		int searchCount = 0;
		if (lstrlen(message) > 20)
			searchCount = 20;
		else
			searchCount = strlen(message);
		bool succeed = false;
		for (int index = 0; index < searchCount; index++)
		{
			if (message[index] == ':')
			{
				succeed = true;

				memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));
				memset(DrawMessageBuffer, 32, sizeof(DrawMessageBuffer));
				if (ClanMarkFlag == false)
				{
					lstrcpy(&DrawMessageBuffer[index + 1], &message[index + 1]);
					memcpy(cname, message, index + 1);
				}
				else
				{
					lstrcpy(&DrawMessageBuffer[index + 4], &message[index + 1]);
					memcpy(cname, message, index + 1);
					memcpy(cname + 4, message, index + 1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
				}

				memset(DrawCharacterNameBuffer, 0, sizeof(DrawCharacterNameBuffer));
				memcpy(DrawCharacterNameBuffer, message, index + 1);
				break;
			}
		}
		if (succeed)
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			MessageFlag = true;
			memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));
			if (ClanMarkFlag == false)
			{
				lstrcpy(DrawMessageBuffer, message);
			}
			else
			{
				memset(DrawMessageBuffer, 32, lstrlen(message) + 2);
				lstrcpy(&DrawMessageBuffer[2 + 1], message);
			}

		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

	for (int i = 0; i < linesize; i++)
	{
		int w = GetTextWidth(0, textdata[i]);
		int h = GetTextHeight(0, textdata[i]);

		if (textsize.x < w)
			textsize.x = w;
		if (textsize.y < h)
			textsize.y = h;
	}

	if (MessageFlag || CharNameFlag)
	{
		int messageLen = lstrlen(DrawMessageBuffer);

		if (lineSize != 0 && messageLen > lineSize)
		{
			messageHeight = messageLen / lineSize;
			if (messageHeight%lineSize)
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if (messageWidth != 0)
			x -= messageWidth / 2 * 6 + 18 / 2;
		if (messageHeight != 0)
			y -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 12;

		if (x < 0 || y < 0 || (x + 18 + messageWidth * 6) >= RESOLUTION_WIDTH || (y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= RESOLUTION_HEIGHT))
			return;

		/*if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame(x-2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);*/

		if (MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x - 2, y, textsize.x, textsize.y, linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y, linesize, CharNameFlag, selected);
	}

	if (bellaMarkIndex > 0 && vipIndex > 0)
	{
		DrawBellaIcon(x + messageWidth - 6, y - 30, bellaMarkIndex);
		DrawVipIcon(x + messageWidth - 6 + 32, y - 30, vipIndex);
	}
	else if (bellaMarkIndex > 0)
	{
		DrawBellaIcon(x + 3 * messageWidth - 6, y - 30, bellaMarkIndex);
	}
	else if (vipIndex > 0)
	{
		DrawVipIcon(x + 3 * messageWidth - 6, y - 30, vipIndex);
	}

	if (ClanMarkFlag)
	{
		int clanX = x;
		int clanY = y;

		if (MessageFlag == false && CharNameFlag == false)
		{
			messageWidth = 1;
			if (messageWidth != 0)
				clanX -= messageWidth / 2 * 6 + 13;
			if (messageHeight != 0)
				clanY -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 8;
		}
		if (CharNameFlag == false && MessageFlag == false)
			DrawClanMark(clanMark, clanName, clanX + 3, clanY, true);
		else
			DrawClanMark(clanMark, clanName, clanX + 3, clanY);
	}

	DWORD Color;

	if (CharNameFlag == false)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 255, 255);
		else
			Color = color1;
	}
	else
		Color = D3DCOLOR_XRGB(255, 255, 255);

	if (MessageFlag)
	{
		for (int m = 0; m < linesize; m++)
			dsTextLineOut(0, x + 9, y + 5 + m * textsize.y + 2, textdata[m], lstrlen(textdata[m]), Color, TRUE);

		/*if (lineSize>10)
		{
			lineSize--;

			if (lineSize<messageWidth)
			{
				messageWidth--;
				lineSize++;
			}
		}
		char buffer[1024];
		if(lineSize != 0)
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for(int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while(DrawMessageBuffer[end] != NULL)
				{
					if( CheckCode_2Byte( &DrawMessageBuffer[end] )==2 )
					{
						if( (lineCount+2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;
					}
					else
					{
						if( (lineCount+1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;

					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end-start);

				if (DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ')
					lstrcat( buffer , "-" );

				if (DrawMessageBuffer[end+1]==0)
					buffer[end-start] = DrawMessageBuffer[end];

				dsTextLineOut(0, x+9, y+5+m*16+2, buffer, lstrlen(buffer),Color,TRUE);

				if(DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			dsTextLineOut(0, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer),Color,TRUE);*/
	}
	if (CharNameFlag)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 220, 100);
		else
			Color = color1;

		dsTextLineOut(0, x + 9, y + 5 + 2, cname, lstrlen(cname), Color, TRUE);

		/*if(ClanMarkFlag == false)
			dsTextLineOut(0, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer),Color,TRUE);
		else
			dsTextLineOut(0, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer),Color,TRUE);*/
	}
}

void HoMessage::DrawShopSellMessage(int x, int y, char *message, int lineSize, smTEXTUREHANDLE *clanMark, DWORD color1, BOOL selected)
{
	bool CharNameFlag = false;
	bool MessageFlag = false;
	bool ClanMarkFlag = false;

	if (clanMark != NULL)
		ClanMarkFlag = true;

	if (message != NULL)
	{
		int searchCount = 0;

		if (lstrlen(message) > 20)
			searchCount = 20;
		else
			searchCount = lstrlen(message);
		bool succeed = false;
		for (int index = 0; index < searchCount; index++)
		{
			if (message[index] == ':')
			{
				succeed = true;

				memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));
				memset(DrawMessageBuffer, 32, sizeof(DrawMessageBuffer));

				if (ClanMarkFlag == false)
					lstrcpy(&DrawMessageBuffer[index + 1], &message[index + 1]);
				else
					lstrcpy(&DrawMessageBuffer[index + 4], &message[index + 1]);

				memset(DrawCharacterNameBuffer, 0, sizeof(DrawCharacterNameBuffer));
				memcpy(DrawCharacterNameBuffer, message, index + 1);
				break;
			}
		}
		if (succeed)
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			MessageFlag = true;
			memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));

			if (ClanMarkFlag == false)
				lstrcpy(DrawMessageBuffer, message);
			else
			{
				memset(DrawMessageBuffer, 32, lstrlen(message) + 2);
				lstrcpy(&DrawMessageBuffer[2 + 1], message);
			}
		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

	if (MessageFlag || CharNameFlag)
	{
		int messageLen = lstrlen(DrawMessageBuffer);
		if (lineSize != 0 && messageLen > lineSize)
		{
			messageHeight = messageLen / lineSize;
			if (messageHeight%lineSize)
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if (messageWidth != 0)
			x -= messageWidth / 2 * 6 + 18 / 2;
		if (messageHeight != 0)
			y -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 12;

		if (x < 0 || y < 0 || (x + 18 + messageWidth * 6) >= (int)RESOLUTION_WIDTH || (y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= RESOLUTION_HEIGHT))
			return;

		if (MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame(x - 2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);
	}
	if (ClanMarkFlag)
	{
		int clanX = x;
		int clanY = y;

		if (MessageFlag == false && CharNameFlag == false)
		{
			messageWidth = 1;

			if (messageWidth != 0)
				clanX -= messageWidth / 2 * 6 + 13;
			if (messageHeight != 0)
				clanY -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 8;
		}

		DrawClanMark(clanMark, NULL, clanX + 3, clanY);
	}

	DWORD Color;

	if (CharNameFlag == false)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 255, 255);
		else
			Color = color1;
	}
	else
		Color = D3DCOLOR_XRGB(255, 255, 255);

	if (MessageFlag)
	{
		char buffer[1024];
		if (lineSize != 0)
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for (int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while (1)
				{
					if (DrawMessageBuffer[end] == NULL)
						break;

					if (CheckCode_2Byte(&DrawMessageBuffer[end]) == 2)
					{
						if ((lineCount + 2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;

					}
					else
					{
						if ((lineCount + 1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;

					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end - start);

				dsTextLineOut(0, x + 9, y + 5 + m * 16 + 2, buffer, lstrlen(buffer), Color);

				if (DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			dsTextLineOut(0, x + 9, y + 5 + 2, DrawMessageBuffer, lstrlen(DrawMessageBuffer), Color);
	}
	if (CharNameFlag)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 220, 100);
		else
			Color = color1;

		if (ClanMarkFlag == false)
			dsTextLineOut(0, x + 9, y + 5 + 2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer), Color);
		else
			dsTextLineOut(0, x + 9 + 6 * 3, y + 5 + 2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer), Color);
	}
}
void HoMessage::DrawShopSellMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(ShopBoxSellImage1[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(ShopBoxSellImage2[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		}
		for (int m = 0; m < linecount; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(ShopBoxSellImage1[3], x, y + 5, 0, 0, 8, 14, 255); //哭率 坷弗率..
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255); //东户
				HoDrawTexImage(ShopBoxSellImage1[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(ShopBoxSellImage1[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255); //哭率 坷弗率..
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255); //东户
				HoDrawTexImage(ShopBoxSellImage1[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(ShopBoxSellImage2[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(ShopBoxSellImage2[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(ShopBoxSellImage2[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(ShopBoxSellImage2[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}
		for (int m = 0; m < (messageWidth / 6) + 1; m++)
		{
			if (tailFlag)
			{
				HoDrawTexImage(ShopBoxSellImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(ShopBoxSellImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(ShopBoxSellImage1[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(ShopBoxSellImage2[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == ((messageWidth / 6) + 1) / 2 - 1)
				{

					HoDrawTexImage(ShopBoxSellImage1[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(ShopBoxSellImage2[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(ShopBoxSellImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(ShopBoxSellImage1[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(ShopBoxSellImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(ShopBoxSellImage2[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}

	for (int n = 0; n < linecount; n++)
	{
		for (int m = 0; m < messageWidth + 1; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5 + (n - 1)*messageHeight + 14, 0, 0, 6, 16, 255);
		}
	}
}
void HoMessage::DrawShopByeMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(ShopBoxByeImage1[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(ShopBoxByeImage2[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[2], x + 11 + messageWidth, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[6], x, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[8], x + 11 + messageWidth, y + 5 + (messageHeight*(linecount - 1)) + 14, 9, 3, 7, 5, 255);
		}

		for (int m = 0; m < linecount; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(ShopBoxByeImage1[3], x, y + 5, 0, 0, 8, 14, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255);
				HoDrawTexImage(ShopBoxByeImage1[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(ShopBoxByeImage1[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255);
				HoDrawTexImage(ShopBoxByeImage1[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(ShopBoxByeImage2[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(ShopBoxByeImage2[5], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(ShopBoxByeImage2[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(ShopBoxByeImage2[5], x + 11 + messageWidth, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}

		for (int m = 0; m < (messageWidth / 6) + 1; m++)
		{
			if (tailFlag)
			{
				HoDrawTexImage(ShopBoxByeImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(ShopBoxByeImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(ShopBoxByeImage1[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(ShopBoxByeImage2[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == ((messageWidth / 6) + 1) / 2 - 1)
				{

					HoDrawTexImage(ShopBoxByeImage1[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(ShopBoxByeImage2[9], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(ShopBoxByeImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(ShopBoxByeImage1[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(ShopBoxByeImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(ShopBoxByeImage2[7], x + 11 + 6 * m, y + 5 + (messageHeight*(linecount - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}
	for (int n = 0; n < linecount; n++)
	{
		for (int m = 0; m < messageWidth + 1; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m, y + 5 + (n - 1)*messageHeight + 14, 0, 0, 6, 16, 255);
		}
	}
}
void HoMessage::DrawShopSellMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(ShopBoxSellImage1[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(ShopBoxSellImage1[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(ShopBoxSellImage2[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(ShopBoxSellImage2[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		}
		for (int m = 0; m < messageHeight; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(ShopBoxSellImage1[3], x, y + 5, 0, 0, 8, 14, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255);
				HoDrawTexImage(ShopBoxSellImage1[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(ShopBoxSellImage1[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255);
				HoDrawTexImage(ShopBoxSellImage1[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(ShopBoxSellImage2[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(ShopBoxSellImage2[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(ShopBoxSellImage2[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(ShopBoxSellImage2[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}

		for (int m = 0; m < messageWidth; m++)
		{
			if (tailFlag)
			{
				HoDrawTexImage(ShopBoxSellImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(ShopBoxSellImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(ShopBoxSellImage1[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(ShopBoxSellImage2[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == messageWidth / 2 - 1)
				{

					HoDrawTexImage(ShopBoxSellImage1[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(ShopBoxSellImage2[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(ShopBoxSellImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(ShopBoxSellImage1[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(ShopBoxSellImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(ShopBoxSellImage2[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}

	for (int n = 0; n < messageHeight; n++)
	{
		for (int m = 0; m < messageWidth; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5 + (n - 1) * 16 + 14, 0, 0, 6, 16, 255);
		}
	}
}

void HoMessage::DrawShopByeMessage(int x, int y, char *message, int lineSize, smTEXTUREHANDLE *clanMark, DWORD color1, BOOL selected)
{
	bool CharNameFlag = false;
	bool MessageFlag = false;
	bool ClanMarkFlag = false;

	if (clanMark != NULL)
		ClanMarkFlag = true;

	char	cname[256];
	int linesize = 0;
	ZeroMemory(cname, sizeof(char) * 256);
	linesize = textarrange(message, ClanMarkFlag);

	if (message != NULL)
	{
		int searchCount = 0;
		if (lstrlen(message) > 20)
			searchCount = 20;
		else
			searchCount = lstrlen(message);
		bool succeed = false;
		for (int index = 0; index < searchCount; index++)
		{
			if (message[index] == ':')
			{
				succeed = true;

				memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));
				memset(DrawMessageBuffer, 32, sizeof(DrawMessageBuffer));
				if (ClanMarkFlag == false)
				{
					lstrcpy(&DrawMessageBuffer[index + 1], &message[index + 1]);
					memcpy(cname, message, index + 1);
				}
				else
				{
					lstrcpy(&DrawMessageBuffer[index + 4], &message[index + 1]);

					memcpy(cname, message, index + 1);
					memcpy(cname + 4, message, index + 1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
				}

				memset(DrawCharacterNameBuffer, 0, sizeof(DrawCharacterNameBuffer));
				memcpy(DrawCharacterNameBuffer, message, index + 1);
				break;
			}
		}
		if (succeed)
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			MessageFlag = true;

			memset(DrawMessageBuffer, 0, sizeof(DrawMessageBuffer));
			if (ClanMarkFlag == false)
				lstrcpy(DrawMessageBuffer, message);
			else
			{
				memset(DrawMessageBuffer, 32, lstrlen(message) + 2);
				lstrcpy(&DrawMessageBuffer[2 + 1], message);
			}
		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

	for (int i = 0; i < linesize; i++)
	{
		int w = GetTextWidth(0, textdata[i]);
		int h = GetTextHeight(0, textdata[i]);

		if (textsize.x < w)
			textsize.x = w;
		if (textsize.y < h)
			textsize.y = h;
	}

	if (MessageFlag || CharNameFlag)
	{
		int messageLen = lstrlen(DrawMessageBuffer);
		if (lineSize != 0 && messageLen > lineSize)
		{
			messageHeight = messageLen / lineSize;

			if (messageHeight%lineSize)
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if (messageWidth != 0)
			x -= messageWidth / 2 * 6 + 18 / 2;
		if (messageHeight != 0)
			y -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 12;

		if (x < 0 || y < 0 || (x + 18 + messageWidth * 6) >= RESOLUTION_WIDTH || (y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= RESOLUTION_HEIGHT))
			return;

		/*if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame(x-2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);*/

		if (MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x - 2, y, textsize.x, textsize.y, linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y, linesize, CharNameFlag, selected);
	}

	if (ClanMarkFlag)
	{
		int clanX = x;
		int clanY = y;

		if (MessageFlag == false && CharNameFlag == false)
		{
			messageWidth = 1;
			if (messageWidth != 0)
				clanX -= messageWidth / 2 * 6 + 13;
			if (messageHeight != 0)
				clanY -= (messageHeight - 1) * 16 + 14 + 5 * 2 + 8;
		}

		DrawClanMark(clanMark, NULL, clanX + 3, clanY);
	}

	DWORD Color;

	if (CharNameFlag == false)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 255, 255);
		else
			Color = color1;
	}
	else
		Color = D3DCOLOR_XRGB(255, 255, 255);

	if (MessageFlag)
	{

		for (int m = 0; m < linesize; m++)
			dsTextLineOut(0, x + 9, y + 5 + m * textsize.y + 2, textdata[m], lstrlen(textdata[m]), Color);

		/*char buffer[1024];

		if(lineSize != 0)
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for(int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while(DrawMessageBuffer[end] != NULL)
				{
					if( CheckCode_2Byte(&DrawMessageBuffer[end]) == 2)
					{
						if( (lineCount+2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;
					}
					else
					{
						if( (lineCount+1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;
					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end-start);

				dsTextLineOut(0, x+9, y+5+m*16+2, buffer, lstrlen(buffer),Color);

				if(DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			dsTextLineOut(0, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer),Color);*/
	}

	if (CharNameFlag)
	{
		if (color1 == D3DCOLOR_XRGB(0, 0, 0))
			Color = D3DCOLOR_XRGB(255, 220, 100);
		else
			Color = color1;

		dsTextLineOut(0, x + 9, y + 5 + 2, cname, lstrlen(cname), Color);

		/*if(ClanMarkFlag == false)
			dsTextLineOut(0, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer),Color);
		else
			dsTextLineOut(0, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer),Color);*/
	}
}

void HoMessage::DrawShopByeMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected)
{
	if (MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(ShopBoxByeImage1[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(ShopBoxByeImage1[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		if (selected)
		{
			HoDrawTexImage(ShopBoxByeImage2[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(ShopBoxByeImage2[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		}


		for (int m = 0; m < messageHeight; m++)
		{
			if (m == 0)
			{
				HoDrawTexImage(ShopBoxByeImage1[3], x, y + 5, 0, 0, 8, 14, 255); //哭率 坷弗率..
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255); //东户
				HoDrawTexImage(ShopBoxByeImage1[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(ShopBoxByeImage1[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255); //哭率 坷弗率..
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255); //东户
				HoDrawTexImage(ShopBoxByeImage1[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if (selected)
			{
				if (m == 0)
				{
					HoDrawTexImage(ShopBoxByeImage2[3], x, y + 5, 0, 0, 8, 14, 255);
					HoDrawTexImage(ShopBoxByeImage2[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(ShopBoxByeImage2[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
					HoDrawTexImage(ShopBoxByeImage2[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}
		for (int m = 0; m < messageWidth; m++)
		{
			if (tailFlag)
			{
				HoDrawTexImage(ShopBoxByeImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if (selected)
					HoDrawTexImage(ShopBoxByeImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if (m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(ShopBoxByeImage1[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
					if (selected)
						HoDrawTexImage(ShopBoxByeImage2[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
				if (m == messageWidth / 2 - 1)
				{

					HoDrawTexImage(ShopBoxByeImage1[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
					if (selected)
						HoDrawTexImage(ShopBoxByeImage2[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(ShopBoxByeImage1[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(ShopBoxByeImage1[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);

				if (selected)
				{
					HoDrawTexImage(ShopBoxByeImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(ShopBoxByeImage2[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}

	for (int n = 0; n < messageHeight; n++)
	{
		for (int m = 0; m < messageWidth; m++)
		{
			if (n == 0)
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255);
			else
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5 + (n - 1) * 16 + 14, 0, 0, 6, 16, 255);
		}
	}
}
void HoMessage::DrawDayNightMessage(int x, int y, char *message1, char *message2)
{
	int messageWidth = lstrlen(message1);
	int messageHeight = 3;

	if (x < 0 || y < 0 || (x + 16 * 2 + messageWidth * 6) >= RESOLUTION_WIDTH || y < 0 || x < 0 || (y + 16 * 2 + messageHeight * 6) >= RESOLUTION_WIDTH || (x + 16 * 2 + messageWidth * 6) >= RESOLUTION_HEIGHT || (y + 16 * 2 + messageHeight * 6) >= RESOLUTION_HEIGHT)
		return;

	int sx = x;
	int sy = y;

	dsGetDrawOffset(&x, &y);

	dsDrawTexImage(BoxImage1[0], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	dsDrawTexImage(BoxImage1[2], x + messageWidth * 6 + 16, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	dsDrawTexImage(BoxImage1[6], x, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	dsDrawTexImage(BoxImage1[8], x + messageWidth * 6 + 16, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255);

	int m, n;

	for (m = 0; m < messageWidth; m++)
	{
		dsDrawTexImage(BoxImage1[1], x + 16 + 6 * m, y, 6, 16, 16, 16, 0, 0, 6, 16, 255);
		dsDrawTexImage(BoxImage1[7], x + 16 + 6 * m, y + 16 + (14 * messageHeight), 6, 16, 16, 16, 0, 0, 6, 16, 255);
	}

	for (m = 0; m < messageHeight; m++)
	{
		dsDrawTexImage(BoxImage1[3], x, y + 16 + (14 * m), 16, 14, 16, 16, 0, 0, 16, 12, 255);
		dsDrawTexImage(BoxImage1[5], x + 16 + 6 * messageWidth, y + 16 + (14 * m), 16, 14, 16, 16, 0, 0, 16, 12, 255);
	}
	for (m = 0; m < messageWidth; m++)
	{
		for (n = 0; n < messageHeight; n++)
			dsDrawTexImage(BoxImage1[4], x + 16 + 6 * m, y + 16 + 14 * n, 6, 14, 32, 32, 0, 0, 12, 12, 255);
	}

	dsTextLineOut(0, sx + 17, sy + 16, message1, lstrlen(message1), D3DCOLOR_XRGB(255, 255, 255));

	messageWidth = messageWidth / 2;
	messageWidth = messageWidth - lstrlen(message2) / 2;
	messageWidth = messageWidth * 6 + 16;

	dsTextLineOut(1, sx + messageWidth, sy + 38, message2, lstrlen(message2), D3DCOLOR_XRGB(255, 220, 100));

}
// 消息渲染
void HoMessage::Draw(int x, int y, char *message, int lineSize, int addLine, int boxAttrib)
{
	int messageSize = lstrlen(message);
	int messageWidth = 0;
	int messageHeight = 1;

	if (lineSize != 0 && messageSize > lineSize)
	{
		messageHeight = messageSize / lineSize;

		if (messageHeight % (lineSize))
			messageHeight += 1;

		messageWidth = lineSize;
	}
	else
	{
		messageWidth = messageSize;

		if (messageWidth % 2)
			messageWidth++;
	}

	if (messageWidth == 0)
		return;

	messageHeight += addLine;

	if (boxAttrib == BOX_ONE || boxAttrib == BOX_TWO)
	{
		if (x < 0 || y < 0 || (x + 16 * 2 + messageWidth * 6) >= RESOLUTION_WIDTH || y < 0 || x < 0 || (y + 16 * 2 + messageHeight * 6) >= RESOLUTION_HEIGHT || (x + 16 * 2 + messageWidth * 6) >= RESOLUTION_WIDTH || (y + 16 * 2 + messageHeight * 6) >= RESOLUTION_HEIGHT)
			return;
	}
	if (boxAttrib == BOX_ONE)
	{
		dsDrawTexImage(BoxImage1[0], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[2], x + messageWidth * 6 + 16, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[6], x, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage1[8], x + messageWidth * 6 + 16, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	}
	else if (boxAttrib == BOX_TWO)
	{
		dsDrawTexImage(BoxImage2[0], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[1], x + 16 + messageWidth * 6, y, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[2], x, y + 16 + messageHeight * 14, 16, 16, 16, 16, 0, 0, 16, 16, 255);
		dsDrawTexImage(BoxImage2[3], x + 16 + messageWidth * 6, y + 16 + messageHeight * 14, 16, 16, 16, 16, 0, 0, 16, 16, 255);
	}

	int m, n;

	if (boxAttrib == BOX_ONE || boxAttrib == BOX_TWO)
	{
		for (m = 0; m < messageWidth; m++)
		{
			dsDrawTexImage(BoxImage1[1], x + 16 + 6 * m, y, 6, 16, 16, 16, 0, 0, 6, 16, 255);
			dsDrawTexImage(BoxImage1[7], x + 16 + 6 * m, y + 16 + (14 * messageHeight), 6, 16, 16, 16, 0, 0, 6, 16, 255);
		}

		for (m = 0; m < messageHeight; m++)
		{
			dsDrawTexImage(BoxImage1[3], x, y + 16 + (14 * m), 16, 14, 16, 16, 0, 0, 16, 12, 255);
			dsDrawTexImage(BoxImage1[5], x + 16 + 6 * messageWidth, y + 16 + (14 * m), 16, 14, 16, 16, 0, 0, 16, 12, 255);
		}
		for (m = 0; m < messageWidth; m++)
		{
			for (n = 0; n < messageHeight; n++)
				dsDrawTexImage(BoxImage1[4], x + 16 + 6 * m, y + 16 + 14 * n, 6, 14, 32, 32, 0, 0, 12, 12, 255);
		}
	}

	messageWidth = messageWidth / 2;

	TextStartPosY = y;
	messageHeight = messageHeight - addLine;

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	char buffer[1024];

	if (lineSize != 0)
	{
		int start = 0;
		int end = 0;
		int lineCount = 0;

		for (m = 0; m < messageHeight; m++)
		{
			memset(buffer, 0, sizeof(buffer));

			while (message[end] != NULL)
			{
				if (message[end] & 0x80)
				{
					lineCount += 2;
					end += 2;
				}
				else
				{
					lineCount += 1;
					end += 1;
				}

				if (lineCount > messageWidth * 2 - 1)
					break;
			}

			memcpy(buffer, &message[start], end - start);

			dsTextLineOut(0, x + 17, TextStartPosY + 16 + m * 15, buffer, lstrlen(buffer), Color);

			if (message[end] != NULL)
			{
				if (message[end] == ' ')
					end += 1;

				start = end;
				lineCount = 0;
			}
			else
				break;
		}
	}
	else
		dsTextLineOut(0, x + 17, y + 16, message, lstrlen(message), Color);

	Width = messageWidth * 12 + 16 * 2;
}

int DrawCharacterShopSellMessage(int x, int y, char*message, int lineSize, smTEXTUREHANDLE *clanMark, DWORD charColor, BOOL selected)
{
	ChatMessage.DrawShopSellMessage(x, y, message, lineSize, clanMark, charColor, selected);
	return TRUE;
}
int DrawDayNightMessage(int x, int y, char *message1, char *message2)
{
	ChatMessage.DrawDayNightMessage(x, y, message1, message2);
	return TRUE;
}
int DrawCharacterShopByeMessage(int x, int y, char*message, int lineSize, smTEXTUREHANDLE *clanMark, DWORD charColor, BOOL selected)
{
	ChatMessage.DrawShopByeMessage(x, y, message, lineSize, clanMark, charColor, selected);
	return TRUE;
}

int DrawCharacterMessage(int x, int y, char *message, int lineSize, smTEXTUREHANDLE *clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex, int vipIndex)
{
	ChatMessage.DrawCharacterMessage(x, y, message, lineSize, clanMark, clanName, color1, selected, bellaMarkIndex, vipIndex);
	return TRUE;
}

int DrawTwoLineMessage(int x, int y, char *messageOne, char *messageTwo, DWORD color1, DWORD color2, smTEXTUREHANDLE *clanMark, BOOL selected, int bellaMarkIndex, int vipIndex)
{
	ChatMessage.DrawTwoLineMessage(x, y, messageOne, messageTwo, color1, color2, clanMark, selected, bellaMarkIndex, vipIndex);
	return TRUE;
}

int DrawClanMessage(int x, int y, char *message, int lineSize, DWORD color)
{
	ChatMessage.DrawClanMessage(x, y, message, lineSize, color);
	return TRUE;
}
int DrawMessage(int x, int y, char *message, int lineSize, int boxAttrib)
{
	ChatMessage.Draw(x, y, message, lineSize, 0, boxAttrib);
	return TRUE;
}
void	SetMessageFrameSelect(BOOL flag)
{
	ChatMessage.SetMessageFrameSelect(flag);
}

int InitMessageBox()
{
	ChatMessage.Init();
	return TRUE;
}

BOOL	HoButton::ButtonUseFlag = FALSE;
HoButton::HoButton()
{
	ButtonInDownFlag = FALSE;
	State = BUTTON_STATE_NONE;
	SizeWidth = 64;
	SizeHeight = 32;

}

HoButton::~HoButton()
{

}

void HoButton::Init(char *stateFirstIamge, char *stateThirdImage)
{
	StateFirstImage = CreateTextureMaterial(stateFirstIamge, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void HoButton::InitCrashRect(int left, int top, int right, int bottom)
{
	CrashRect.left = left;
	CrashRect.top = top;
	CrashRect.right = right;
	CrashRect.bottom = bottom;
}

void HoButton::Init(char *stateFirstImage, int sizeWidth, int sizeHeight)
{
	StateFirstImage = CreateTextureMaterial(stateFirstImage, 0, 0, 0, SMMAT_BLEND_ALPHA);
	SizeWidth = sizeWidth;
	SizeHeight = sizeHeight;

	CrashRect.left = 0;
	CrashRect.top = 0;
	CrashRect.right = SizeWidth;
	CrashRect.bottom = SizeHeight;
}
BOOL HoButton::Draw(int x, int y, int BlendFlag)
{
	PosX = x;
	PosY = y;

	if (BlendFlag < 255)
		dsDrawTexImage(StateFirstImage, x, y, SizeWidth, SizeHeight, BlendFlag);
	else
	{
		if (State == 0)
			dsDrawTexImage(StateFirstImage, x, y, SizeWidth, SizeHeight, 255);

		else if (State == 1)
		{
			dsDrawTexImage(StateFirstImage, x, y, SizeWidth, SizeHeight, 255, 40);
			return TRUE;
		}
		else if (State == 2)
			dsDrawTexImage(StateFirstImage, x + 1, y + 1, SizeWidth, SizeHeight, 255, 40);
	}
	return FALSE;
}

BOOL HoButton::Main(int mouseX, int mouseY, int downFlag)
{
	if (mouseX > (PosX + CrashRect.left) && mouseX < PosX + (CrashRect.right) && mouseY >(PosY + CrashRect.top) && mouseY < PosY + (CrashRect.bottom))
	{
		if (ButtonUseFlag == FALSE)
		{
			State = BUTTON_STATE_IN;

			if (downFlag)
			{
				ButtonUseFlag = TRUE;
				ButtonInDownFlag = TRUE;
				State = BUTTON_STATE_DOWN;
			}

			if (ButtonInDownFlag && downFlag == FALSE)
			{
				ButtonInDownFlag = FALSE;
				State = BUTTON_STATE_NONE;
				return TRUE;
			}
		}
	}
	else
	{
		if (ButtonInDownFlag == TRUE)
			State = BUTTON_STATE_IN;
		else
			State = BUTTON_STATE_NONE;

		if (downFlag == FALSE)
			ButtonInDownFlag = FALSE;
	}

	if (downFlag == FALSE)
		ButtonUseFlag = FALSE;
	return FALSE;
}

HoMessageBox::HoMessageBox()
{
	Flag = FALSE;
}

HoMessageBox::~HoMessageBox()
{

}
BOOL HoMessageBox::Main(int mouseX, int mouseY, int downFlag)
{
	if (Flag)
	{
		if (Button[0].Main(mouseX, mouseY, downFlag))
		{
			Flag = FALSE;
			return 1;
		}

		if (Button[1].Main(mouseX, mouseY, downFlag))
		{
			Flag = FALSE;
			return 2;
		}
	}
	return FALSE;
}

BOOL HoMessageBox::Draw(int x, int y, char *message, int Color)
{
	if (Flag)
	{
		Message.DrawMessageBox(x, y, message, BOX_ONE, Color);
		int messageWidth = Message.GetWidth();
		x = Message.PosX;
		y = Message.PosY;

		Button[0].Draw(x + messageWidth / 2 - 54 - 13, 40 + y);
		Button[1].Draw(x + messageWidth / 2 + 7, 40 + y);
	}
	return TRUE;
}

void HoMessageBox::Init()
{
	Button[0].Init("StartImage\\Login\\CharSelect\\Bt_ok.tga", 64, 32);
	Button[1].Init("StartImage\\Login\\CharSelect\\Bt_cancel.tga", 64, 32);
	Message.Init();
}

