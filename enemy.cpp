//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
//#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX	(1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(void);
void SetTextureEnemy(int cntPattern);	// 
void SetVertexEnemy(void);				// 頂点の計算処理




//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

//static D3DXVECTOR3				g_posPlayer;						// ポリゴンの座標
//static D3DXVECTOR3				g_rotPlayer;						// ポリゴンの回転量
//static int						g_nCountAnim;						// アニメーションカウント
//static int						g_nPatternAnim;						// アニメーションパターンナンバー

float					g_fRadiusEnemy;					// ポリゴンの半径
float					g_fBaseAngleEnemy;					// ポリゴンの角度

ENEMY enemy[PLAYER_MAX];				//エネミーの配列

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	ENEMY *emy = GetEnemyAddress(0); 

	emy->pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	emy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	emy->nCountAnim = 0;
	emy->nPatternAnim = 0;

	emy->use = true;

	// 頂点情報の作成
	MakeVertexEnemy();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_ENEMY_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
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
void UpdateEnemy(void)
{
	ENEMY *emy = GetEnemyAddress(0);

	// アニメーション
	emy->nCountAnim++;

	// アニメーションWaitチェック
	if ((emy->nCountAnim % TIME_ANIMATION) == 0)
	{
		// パターンの切り替え
		emy->nPatternAnim = (emy->nPatternAnim + 1) % ANIM_PATTERN_NUM;

		// テクスチャ座標を設定
		SetTextureEnemy(emy->nPatternAnim);
	}




	//SetVertexEnemy();	// 頂点の計算処理

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY *emy = GetEnemyAddress(0);
	if (emy->use == false)
	{
		return;
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY *emy = GetEnemyAddress(0);

	// 頂点座標の設定	
	SetVertexEnemy();	// 頂点の計算処理
						
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
	SetTextureEnemy(emy->nPatternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(int cntPattern)
{
	// テクスチャ座標の設定(UV)
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy(void)
{
	ENEMY *emy = GetEnemyAddress(0);

	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(emy->pos.x, emy->pos.y, emy->pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(emy->pos.x + TEXTURE_ENEMY_SIZE_X, emy->pos.y, emy->pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(emy->pos.x, emy->pos.y + TEXTURE_ENEMY_SIZE_Y, emy->pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(emy->pos.x + TEXTURE_ENEMY_SIZE_X, emy->pos.y + TEXTURE_ENEMY_SIZE_Y, emy->pos.z);
}





ENEMY *GetEnemyAddress(int pno)
{
	return &enemy[pno];

}
