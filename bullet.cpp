//=============================================================================
//
// bullet���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "player.h"

//#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX	(1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(void);
void SetTextureBullet(int cntPattern);	// 
void SetVertexBullet(void);				// ���_�̌v�Z����




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

//static D3DXVECTOR3				g_posPlayer;						// �|���S���̍��W
//static D3DXVECTOR3				g_rotPlayer;						// �|���S���̉�]��
//static int						g_nCountAnim;						// �A�j���[�V�����J�E���g
//static int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

float					g_fRadiusBullet;					// �|���S���̔��a
float					g_fBaseAngleBullet;					// �|���S���̊p�x

BULLET bullet[BULLET_MAX];				//�G�l�~�[�̔z��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BULLET *blt = GetBulletAddress(0);

	blt->pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);	//�|���S���̍��W�̏�����
	blt->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	blt->nCountAnim = 0;						//�A�j���[�V�����p�^�[���̏�����
	blt->nPatternAnim = 0;						// �A�j���[�V�����̐؂�ւ��J�E���g�̏�����

	blt->use = false;

	// ���_���̍쐬
	MakeVertexBullet();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_BULLET_SAMPLE00,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if (g_pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	BULLET *blt = GetBulletAddress(0);

	// �A�j���[�V����
	blt->nCountAnim++;

	if (blt->use == true)
	{
		blt->pos.x += 3.0f;
		SetVertexBullet();	// ���_�̌v�Z����
	}

	if (blt->pos.x > SCREEN_WIDTH + TEXTURE_BULLET_SIZE_Y)
	{
		blt->pos.x = -100.0f;
		blt->pos.y =  100.0f;
		blt->use = false;

	}
	

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	BULLET *blt = GetBulletAddress(0);
	if (blt->use == false)
	{
		return;
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *blt = GetBulletAddress(0);

	// ���_���W�̐ݒ�	
	SetVertexBullet();	// ���_�̌v�Z����

	g_vertexWk[0].rhw =	// rhw�̐ݒ�
	g_vertexWk[1].rhw =
	g_vertexWk[2].rhw =
	g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTextureBullet(blt->nPatternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(int cntPattern)
{
	
	g_vertexWk[0].tex = D3DXVECTOR2(0.0f , 0.0f);
	g_vertexWk[1].tex = D3DXVECTOR2(1.0f , 0.0f);
	g_vertexWk[2].tex = D3DXVECTOR2(0.0f , 1.0f);
	g_vertexWk[3].tex = D3DXVECTOR2(1.0f,  1.0f);
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(void)
{
	BULLET *blt = GetBulletAddress(0);

	// ���_���W�̐ݒ�
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
	if (bullet->use == false)							//�����g�p����Ă��Ȃ��ꍇ�A�֐����g��
	{
		BULLET *blt = GetBulletAddress(0);

		blt->pos = D3DXVECTOR3(pos.x + (TEXTURE_PLAYER_SIZE_X / 2 - TEXTURE_BULLET_SIZE_X / 2), pos.y + (TEXTURE_PLAYER_SIZE_Y / 2 - TEXTURE_BULLET_SIZE_Y / 2), 0.0f);

		SetVertexBullet();

		bullet->use = true;								//�g�p��
	}
		

}


