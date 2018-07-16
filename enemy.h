//=============================================================================
//
// �v���C���[���� [Player.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define TEXTURE_ENEMY_SAMPLE00	_T("data/TEXTURE/runningman002.png")	// �T���v���p�摜
#define TEXTURE_ENEMY_SIZE_X	(100)	// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(200)	

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���


#define	NUM_ENEMY		(2)				    // polygon��



//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	 D3DXVECTOR3				pos;						// �|���S���̍��W
	 D3DXVECTOR3				rot;						// �|���S���̉�]��
	 int						nCountAnim;					// �A�j���[�V�����J�E���g
	 int						nPatternAnim;				// �A�j���[�V�����p�^�[���i���o�[7
	 bool                    use;						    //�g�pflag
}ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);


ENEMY *GetEnemyAddress(int pno);

#endif
