

//D3D�� TLVERTEX ��Ƽ �ؽ��� ����
struct D3DTLVERTEX8 {
    D3DVALUE sx, sy, sz;
    D3DVALUE rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
    D3DVALUE tu1, tv1;
    D3DVALUE tu2, tv2;
    D3DVALUE tu3, tv3;
    D3DVALUE tu4, tv4;
    D3DVALUE tu5, tv5;
    D3DVALUE tu6, tv6;
    D3DVALUE tu7, tv7;
    D3DVALUE tu8, tv8;
};

#define D3DFVF_TLVERTEX0		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX0
#define D3DFVF_TLVERTEX1		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX1
#define D3DFVF_TLVERTEX2		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX2
#define D3DFVF_TLVERTEX3		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX3
#define D3DFVF_TLVERTEX4		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX4
#define D3DFVF_TLVERTEX5		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX5
#define D3DFVF_TLVERTEX6		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX6
#define D3DFVF_TLVERTEX7		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX7
#define D3DFVF_TLVERTEX8		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX8



#define RENDER_FACE_MAX		20000
#define RENDER_VERTEX_MAX	20000
#define TEMPTEXLINK_MAX		20000
#define REND_LIGHT_MAX		64

#define RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH		64
#define RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT			(int)( ((float)3.36) * fONE )
#define RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT		(int)( ((float)2.68) * fONE )


#define smRENDER_TYPE_ICE			0x01


class smRENDER3D 
{

public:
	DWORD		m_dwRenderType;
	int			m_FogIsRend;
	int			m_FogMode;
	float		m_fFogStNum;
	float		m_fFogEndNum;
	DWORD		m_dwFogColor;
	int				m_GameFieldView;
	int				m_GameFieldViewStep;
	
	smRENDVERTEX   *RendVertex;
	smRENDFACE	   *RendFace;

	smTEXLINK		TempTexLink[ TEMPTEXLINK_MAX ];
	smRENDMATRIAL	RendMatrial[ MATRIAL_MAX ];

	DWORD			RendMatrialList[ MATRIAL_MAX ];

	smMATERIAL		*smRendMaterial;
	int				nMaterial;

	DWORD			dwMatDispMask;
	DWORD			DeviceRendMode;

	int RMatListCnt;
	int RMatListRearCnt;

	int nRendVertex;
	int nRendFace;
	int nTempTexLink;

	int	SMSHIFT_PERSPECTIVE_WIDTH;
	int	SMMULT_PERSPECTIVE_HEIGHT;

	smSTAGE_VERTEX	*Vertex;
	smSTAGE_FACE	*Face;
	smTEXLINK		*TexLink;

	smRENDLIGHT		smRendObjLight[REND_LIGHT_MAX];
	int				nRendObjLight;

	int				bApplyRendObjLight;

	smRENDLIGHT		smRendLight[REND_LIGHT_MAX];
	int	nRendLight;	


	DWORD SumCount;

	int		CameraPosiMask;

	smMATRIX	mCamera;

	Point3D m_sCameraPosition;
	Point3D m_sCameraAngle;
	//int		CameraAngX , CameraAngY , CameraAngZ;

	int		TexPosiX,TexPosiY,TexPosiZ;
	int		TexSizeX,TexSizeY,TexSizeZ;

	DWORD	ClipStates;
	DWORD	RendStatTime;

	int		Color_R, Color_G , Color_B , Color_A ;

	int		TextureFormState[8];

	DWORD	AlphaTestDepth;

	int RendAlphaFlag;

	int	ObjectVertexScale;
	int	ZWriteAuto;

	int	DistortionMesh;

	smRENDER3D();
	~smRENDER3D();

	void CreateRenderBuff( int FieldViewType );
	void SetGameFieldViewStep(void);
	int SetCameraPosi ( int x, int y, int z, int angX, int angY, int angZ );
	int SetCameraPosi ( int x, int y, int z, smEMATRIX *lpeMatrix );
	int OpenCameraPosi ( int x, int y, int z, smEMATRIX *lpeMatrix );
	int CloseCameraPosi();
	int	AddDynamicLight( int type, int x, int y, int z, int r, int g, int b, int a, int Range );
	int ClearObjLight();
	int	AddDynamicLight( int x, int y, int z, int r, int g, int b, int a, int Range );
	int ClearLight();
	int GetRect2D ( int x, int y, int z, int width, int height, RECT *Rect , POINT *Pos=0 );
	int GetDepthZ ( int x, int y, int z );
	int InitStageMesh ( smSTAGE_VERTEX *StageVertex , DWORD sum );
	int Init();
	BOOL GetCameraCoord(Point3D &sPosition,BOOL b = FALSE);
	int SetClipStates( DWORD States );
	int SetMaterialGroup( smMATERIAL_GROUP *MatGroup );
	int AddRendTempTexLink( smRENDFACE *lpRendFace , DWORD *hTex ,float u0 , float v0 , float u1 , float v1 , float u2 , float v2 );
	
	smRENDVERTEX *AddStageVertex ( smSTAGE_VERTEX *sv , smMATERIAL *lpMaterial  );
	smRENDFACE *AddStageFace ( smSTAGE_FACE *face );
	smRENDVERTEX *AddObjectVertex( smVERTEX *sv, DWORD dwObjHead=0 );
	smRENDFACE *AddObjectFace ( smFACE *face );
	smRENDFACE *AddFace2D ( smFACE2D *face );
	smRENDFACE *AddFace2D ( smFACE2D *face , int angle );
	smRENDFACE *AddFace2D_Direct ( smFACE2D *face );
	smRENDVERTEX *AddRendVertex ( int x, int y, int z, short *pLight, int nx=0, int ny=0, int nz=0 );
	smRENDFACE *AddRendFace ( smRENDVERTEX *v0 , smRENDVERTEX *v1, smRENDVERTEX *v2 ,DWORD matrial , smTEXLINK *lpTexLink );
	int GetFaceSide( smRENDFACE *rendface );
	int AddRendFaceClip( smRENDFACE *rendface , DWORD dwClipMode );
	int AddRendFaceTextureClip( smRENDFACE *rendface );
	int AddRendMaterialList( int MatNum );
	int SetDynamicObjLight( smRENDVERTEX *sv, int z );
	int SetDynamicLight( smRENDVERTEX *sv , int z );
	int SetColorZclip( smRENDVERTEX *sv , int z );
	int ShiftLight( smRENDVERTEX *sv , int lev , int r,int g,int b, int a );
	int AddLight( smRENDVERTEX *sv, int r,int g,int b , int a);
	int SetRendColor( smRENDVERTEX *sv );
	int ClipRendFace();
	int GeomVertex2D( int ColorEffect=TRUE );
	smRENDVERTEX * AddRendVertex_ClipLeft( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipRight( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipTop( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipBottom( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipNearZ( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipFarZ( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	smRENDVERTEX * AddRendVertex_ClipTexture( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	int SetD3DRendBuff( D3DVALUE *RenderBuff , int matrial , int TexClip );
	int SetD3DRendBuff2( D3DVALUE *RenderBuff , int matrial , int TexClip );
	int SetD3DRendBuff3( D3DVALUE *RenderBuff , int matrial , int TexClip, short sColors[4] );
	int SetItem2PassD3DRendState( smMATERIAL *lpMaterial );
	int SetD3DRendState( smMATERIAL *lpMaterial , int TexClip );
	int SetD3DRendStateOnlyAlpha( smMATERIAL *lpMaterial , int TexClip );
	int RenderD3D( int MatNum );
	int RenderD3D();
	// ��Ⱦ��ʽ
	void RenderType(int Type);
	protected:
		BOOL GetCameraCoord64(Point3D &sPosition, BOOL b = FALSE);
		DWORD GetClipStatus(Point3D sPosition);

};

extern smRENDER3D	smRender;


void smSetRendLightVect( int x, int y, int z );


extern int   g_IsDxProjectZoomIn;
extern float g_fZoomInAdd_x;
extern float g_fZoomInAdd_y;
extern float g_fZoomInDiv_x;
extern float g_fZoomInDiv_y;

extern void SetDxProjection( float radians, int SizeX, int SizeY, float near_z, float far_z );
extern void DxProjectionWork( smRENDVERTEX *lpRendVer );

extern int  CreateItem2PassTexture(void);
extern void SetItem2PassTexture( int TexHandleNum, int TexFormState = smTEXSTATE_FS_SCROLL10 );