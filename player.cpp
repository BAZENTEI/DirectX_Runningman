//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX (1)						

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer( int cntPattern );	// 
void SetVertexPlayer(void);					// 頂点の計算処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

//D3DXVECTOR3				g_posPlayer;						// ポリゴンの座標
//D3DXVECTOR3				g_rotPlayer;						// ポリゴンの回転量
//int						g_nCountAnim;						// アニメーションカウント
//int						g_nPatternAnim;						// アニメーションパターンナンバー

float					g_fRadiusPlayer;					// ポリゴンの半径
float					g_fBaseAnglePlayer;					// ポリゴンの角度

PLAYER player[PLAYER_MAX];									//プレイヤーの配列

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	PLAYER *ply = GetPlayerAddress(0);

	ply->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ply->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ply->nCountAnim = 0;
	ply->nPatternAnim = 0;
	ply->use = false;


	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture );					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if( g_pD3DTexture != NULL )
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *ply = GetPlayerAddress(0);

	// アニメーション
	ply->nCountAnim++;

	

	// アニメーションWaitチェック
	if( (( ply->nCountAnim) % TIME_ANIMATION ) == 0 )
	{
		// パターンの切り替え
		ply->nPatternAnim = ( ply->nPatternAnim + 1 ) % ANIM_PATTERN_NUM;

		// テクスチャ座標を設定
		SetTexturePlayer( ply->nPatternAnim );
	}

	if (GetKeyboardPress(DIK_UP) )
	{

		ply->pos.y -= 2.0f;

	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		ply->pos.y += 2.0f;
	}


	if (GetKeyboardPress(DIK_LEFT))
	{
		ply->pos.x -= 2.0f;
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		ply->pos.x += 2.0f;
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		SetBullet(ply->pos);
	}


	SetVertexPlayer();	// 頂点の計算処理
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture( 0, g_pD3DTexture );

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PLAYER *ply = GetPlayerAddress(0);

	// 頂点座標の設定	
	SetVertexPlayer();	// 頂点の計算処理

	// rhwの設定
	g_vertexWk[0].rhw =
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	SetTexturePlayer(ply->nPatternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	g_vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	g_vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	g_vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(void)
{
	PLAYER *ply = GetPlayerAddress(0);

	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(ply->pos.x, ply->pos.y, ply->pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3((ply->pos.x)+TEXTURE_PLAYER_SIZE_X, ply->pos.y, ply->pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(ply->pos.x, (ply->pos.y)+TEXTURE_PLAYER_SIZE_Y, ply->pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3((ply->pos.x)+TEXTURE_PLAYER_SIZE_X, (ply->pos.y)+TEXTURE_PLAYER_SIZE_Y, ply->pos.z);
}


PLAYER *GetPlayerAddress(int pno)
{

	return &player[pno];

}