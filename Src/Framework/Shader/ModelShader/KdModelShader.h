#pragma once
class KdModelShader
{

	struct cbBones;
public:
	// ワールド行列セット
	void SetWorldMatrix(const Math::Matrix& m)
	{
		m_cb1_Mesh.Work().mW = m;
	}

	// bone用定数バッファをそのまま返す
	KdConstantBuffer<cbBones>& BoneCB()
	{
		return m_cb3_Bone;
	}

	//=========================================
	//初期化・解放
	//=========================================

	//初期化
	bool Init();

	//解放
	void Release();

	//デストラクタで自動で解放するようにする
	~KdModelShader() { Release(); }

	//=========================================
	//描画
	//=========================================

	//このシェーダーを使用できるようにデバイスへセット
	void SetToDevice();

	//1つのメッシュを描画
	//・mesh			・・・描画するメッシュ
	//・materials		・・・使用する材質配列
	void DrawMesh(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld);

	//ノードアウトライナー内のすべてのメッシュを描画する
	//また、DrawMeshとは遠い関数内でSetWorldMatrixも実行される
	//1:nodeOL			描画するアウトライナー
	//2:materials		描画に使用するマテリアル配列
	//3:mWorld			ワールド変換行列　各ノードはこの行列基準で変換され描画する
	//rModel等が1＆2を渡してくれる役割を担っている？

	//アニメーションなし
	void DrawModel(const KdModelData& rModel, const Math::Matrix mWorld);
	//アニメーションあり（今は使わないがスキンメッシュアニメーションが最終目標なので入れておく）
	void DrawModel(KdModelWork& rModel, const Math::Matrix mWorld);


	//=========================================
	//輪郭描画
	//=========================================
	//輪郭描画としてデバイスへセット
	void SetToDevice_Outline();
	//1つのメッシュを描画
	void DrawMesh_Outline(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld);
	// 1つのメッシュを描画
	void DrawModel_Outline(const KdModelData& rModel, const Math::Matrix mWorld);

	static const int maxBoneBufferSize = 300;
private:
	void SetMaterial(const KdMaterial& material);

	ID3D11VertexShader* m_VS = nullptr; //頂点シェーダー
	ID3D11InputLayout* m_inputlayout = nullptr; //頂点入力レイアウト
	ID3D11VertexShader* m_VS_Skin = nullptr; //（スキンメッシュ）頂点シェーダー
	ID3D11InputLayout* m_inputlayout_Skin = nullptr; //(スキンメッシュ)頂点入力レイアウト

	ID3D11PixelShader* m_PS = nullptr; //ピクセルシェーダー

	//輪郭描画用
	ID3D11VertexShader* m_outlineVS = nullptr; //頂点シェーダー
	ID3D11PixelShader* m_outlinePS = nullptr; //ピクセルシェーダー


	//定数バッファ用の構造体
	struct cbObject
	{
		// UV操作
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };

	};
	//定数バッファ
	KdConstantBuffer<cbObject> m_cb0;

	// 定数バッファ(メッシュ単位更新)
	struct cbMesh
	{
		Math::Matrix	mW;//ワールド行列
	};
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;

	//定数バッファ（マテリアル単位更新）
	struct cbMaterial
	{
		Math::Vector4 BaseColor;
		Math::Vector3 Emissive;
		float Metallic;
		float Roughness;

		float tmp[3];
	};
	KdConstantBuffer<cbMaterial> m_cb2_Material;



	// 定数バッファ(ボーン単位更新)
	struct cbBones
	{
		Math::Matrix	mat[300];//ワールド行列
	};
	KdConstantBuffer<cbBones>		m_cb3_Bone;
};