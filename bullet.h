//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_


// マクロ定義
#define TEXTURE_BULLET_SAMPLE00	_T("data/TEXTURE/ddon.png")	// サンプル用画像
#define TEXTURE_BULLET_SIZE_X	(50)	// テクスチャサイズ
#define TEXTURE_BULLET_SIZE_Y	(50)	// 

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量


#define	NUM_BULLET		(2)				    // polygon数


//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3				pos;						// ポリゴンの座標
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	int						nCountAnim;					// アニメーションカウント
	int						nPatternAnim;				// アニメーションパターンナンバー
	bool                    use;						//使用flag

}BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos);
BULLET *GetBulletAddress(int pno);
#endif
