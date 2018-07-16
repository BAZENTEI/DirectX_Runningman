//=============================================================================
//
// bullet処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "player.h"

//#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX	(1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(void);
void SetTextureBullet(int cntPattern);	// 
void SetVertexBullet(void);				// 頂点の計算処理




//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

//static D3DXVECTOR3				g_posPlayer;						// ポリゴンの座標
//static D3DXVECTOR3				g_rotPlayer;						// ポリゴンの回転量
//static int						g_nCountAnim;						// アニメーションカウント
//static int						g_nPatternAnim;						// アニメーションパターンナンバー

float					g_fRadiusBullet;					// ポリゴンの半径
float					g_fBaseAngleBullet;					// ポリゴンの角度

BULLET bullet[BULLET_MAX];				//エネミーの配列

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BULLET *blt = GetBulletAddress(0);

	blt->pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);	//ポリゴンの座標の初期化
	blt->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	blt->nCountAnim = 0;						//アニメーションパターンの初期化
	blt->nPatternAnim = 0;						// アニメーションの切り替わるカウントの初期化

	blt->use = false;

	// 頂点情報の作成
	MakeVertexBullet();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_BULLET_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	if (g_pD3DTexture != NULL)
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	BULLET *blt = GetBulletAddress(0);

	// アニメーション
	blt->nCountAnim++;

	if (blt->use == true)
	{
		blt->pos.x += 3.0f;
		SetVertexBullet();	// 頂点の計算処理
	}

	if (blt->pos.x > SCREEN_WIDTH + TEXTURE_BULLET_SIZE_Y)
	{
		blt->pos.x = -100.0f;
		blt->pos.y =  100.0f;
		blt->use = false;

	}
	

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	BULLET *blt = GetBulletAddress(0);
	if (blt->use == false)
	{
		return;
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *blt = GetBulletAddress(0);

	// 頂点座標の設定	
	SetVertexBullet();	// 頂点の計算処理

	g_vertexWk[0].rhw =	// rhwの設定
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	SetTextureBullet(blt->nPatternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet(int cntPattern)
{
	
	g_vertexWk[0].tex = D3DXVECTOR2(0.0f , 0.0f);
	g_vertexWk[1].tex = D3DXVECTOR2(1.0f , 0.0f);
	g_vertexWk[2].tex = D3DXVECTOR2(0.0f , 1.0f);
	g_vertexWk[3].tex = D3DXVECTOR2(1.0f,  1.0f);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet(void)
{
	BULLET *blt = GetBulletAddress(0);

	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(blt->pos.x, blt->pos.y, blt->pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(blt->pos.x + TEXTURE_BULLET_SIZE_X, blt->pos.y, blt->pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(blt->pos.x, blt->pos.y + TEXTURE_BULLET_SIZE_Y, blt->pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(blt->pos.x + TEXTURE_BULLET_SIZE_X, blt->pos.y + TEXTURE_BULLET_SIZE_Y, blt->pos.z);
}

BULLET *GetBulletAddress(int pno)
{
	return &bullet[pno];

}


void SetBullet(D3DXVECTOR3 pos)
{
	if (bullet->use == false)							//もし使用されていない場合、関数を使う
	{
		BULLET *blt = GetBulletAddress(0);

		blt->pos = D3DXVECTOR3(pos.x + (TEXTURE_PLAYER_SIZE_X / 2 - TEXTURE_BULLET_SIZE_X / 2), pos.y + (TEXTURE_PLAYER_SIZE_Y / 2 - TEXTURE_BULLET_SIZE_Y / 2), 0.0f);

		SetVertexBullet();

		bullet->use = true;								//使用中
	}
		

}


