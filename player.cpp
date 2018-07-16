//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MAX (1)						

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer( int cntPattern );	// 
void SetVertexPlayer(void);					// ���_�̌v�Z����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

//D3DXVECTOR3				g_posPlayer;						// �|���S���̍��W
//D3DXVECTOR3				g_rotPlayer;						// �|���S���̉�]��
//int						g_nCountAnim;						// �A�j���[�V�����J�E���g
//int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

float					g_fRadiusPlayer;					// �|���S���̔��a
float					g_fBaseAnglePlayer;					// �|���S���̊p�x

PLAYER player[PLAYER_MAX];									//�v���C���[�̔z��

//=============================================================================
// ����������
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


	// ���_���̍쐬
	MakeVertexPlayer();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&g_pD3DTexture );					// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if( g_pD3DTexture != NULL )
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *ply = GetPlayerAddress(0);

	// �A�j���[�V����
	ply->nCountAnim++;

	

	// �A�j���[�V����Wait�`�F�b�N
	if( (( ply->nCountAnim) % TIME_ANIMATION ) == 0 )
	{
		// �p�^�[���̐؂�ւ�
		ply->nPatternAnim = ( ply->nPatternAnim + 1 ) % ANIM_PATTERN_NUM;

		// �e�N�X�`�����W��ݒ�
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


	SetVertexPlayer();	// ���_�̌v�Z����
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, g_pD3DTexture );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PLAYER *ply = GetPlayerAddress(0);

	// ���_���W�̐ݒ�	
	SetVertexPlayer();	// ���_�̌v�Z����

	// rhw�̐ݒ�
	g_vertexWk[0].rhw =
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTexturePlayer(ply->nPatternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(void)
{
	PLAYER *ply = GetPlayerAddress(0);

	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = D3DXVECTOR3(ply->pos.x, ply->pos.y, ply->pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3((ply->pos.x)+TEXTURE_PLAYER_SIZE_X, ply->pos.y, ply->pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(ply->pos.x, (ply->pos.y)+TEXTURE_PLAYER_SIZE_Y, ply->pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3((ply->pos.x)+TEXTURE_PLAYER_SIZE_X, (ply->pos.y)+TEXTURE_PLAYER_SIZE_Y, ply->pos.z);
}


PLAYER *GetPlayerAddress(int pno)
{

	return &player[pno];

}