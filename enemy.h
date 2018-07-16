//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define TEXTURE_ENEMY_SAMPLE00	_T("data/TEXTURE/runningman002.png")	// サンプル用画像
#define TEXTURE_ENEMY_SIZE_X	(100)	// テクスチャサイズ
#define TEXTURE_ENEMY_SIZE_Y	(200)	

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量


#define	NUM_ENEMY		(2)				    // polygon数



//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	 D3DXVECTOR3				pos;						// ポリゴンの座標
	 D3DXVECTOR3				rot;						// ポリゴンの回転量
	 int						nCountAnim;					// アニメーションカウント
	 int						nPatternAnim;				// アニメーションパターンナンバー7
	 bool                    use;						    //使用flag
}ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);


ENEMY *GetEnemyAddress(int pno);

#endif
