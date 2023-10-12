#include "Framework/KdFramework.h"

#include "KdModelShader.h"

bool KdModelShader::Init()
{
	//=========================================
	//頂点シェーダー
	//=========================================

	{
		//コンパイル済みのシェーダーヘッダーファイルを行くルード
#include "KdModelShader_VS.shaderInc"

		//頂点シェーダー作成
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS)))
		{
			assert(0 && "頂点シェーダー作成失敗");
			Release();
			return false;
		}

		//1頂点の詳細な情報
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		//頂点入力レイアウト作成
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateInputLayout(
			&layout[0],	//入力エレメント先頭アドレス
			layout.size(),	//入力エレメント数
			&compiledBuffer[0],	//頂点バッファのバイナリデータ
			sizeof(compiledBuffer),		//上記のバッファサイズ
			&m_inputlayout))
			) {
			assert(0 && "CreateInputLayout失敗");
			Release();
			return false;
		}
	}

	//=========================================
	//ピクセルシェーダー
	//=========================================
	{
		//コンパイル済みのヘッダーファイルをインクルード
#include "KdModelShader_VS_Skin.shaderinc"

//頂点シェーダー作成
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS_Skin)))
		{
			assert(0 && "(スキンメッシュ)頂点シェーダー作成失敗");
			Release();
			return false;
		}

		// １頂点の詳細な情報
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 20,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 24,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 36,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SKININDEX",	0, DXGI_FORMAT_R16G16B16A16_UINT,	0, 48,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SKINWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 56,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		//頂点入力レイアウト作成
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateInputLayout(
			&layout[0],	//入力エレメント先頭アドレス
			layout.size(),	//入力エレメント数
			&compiledBuffer[0],	//頂点バッファのバイナリデータ
			sizeof(compiledBuffer),		//上記のバッファサイズ
			&m_inputlayout_Skin))
			) {
			assert(0 && "（スキンメッシュ）CreateInputLayout失敗");
			Release();
			return false;
		}
	}

	//=========================================
	//ピクセルシェーダー
	//=========================================
	{
		//コンパイル済みのシェーダーヘッダーファイルをインクルード
#include "KdModelShader_PS.shaderInc"

		if (FAILED(KdDirect3D::Instance().WorkDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_PS)))
		{
			assert(0 && "ピクセルシェーダー作成失敗");
			Release();
			return false;
		}
	}
	//=========================================
	//輪郭用　頂点シェーダー
	//=========================================
	//頂点シェーダー作成
	{
#include "KdModelShader_OutlineVS.shaderInc"
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_outlineVS)))
		{
			assert(0 && "頂点シェーダー作成失敗");
			Release();
			return false;
		}
	}

	//=========================================
	//輪郭用　ピクセルシェーダー
	//=========================================
	{
		//コンパイル済みのシェーダーヘッダーファイルをインクルード
#include "KdModelShader_OutlinePS.shaderInc"

		if (FAILED(KdDirect3D::Instance().WorkDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_outlinePS)))
		{
			assert(0 && "ピクセルシェーダー作成失敗");
			Release();
			return false;
		}
	}
	//=========================================
	//定数バッファ作成
	//=========================================
	m_cb0.Create();
	m_cb1_Mesh.Create();
	m_cb2_Material.Create();
	m_cb3_Bone.Create();

	//=========================================
	//テクスチャ読込
	//=========================================
	return true;
}

void KdModelShader::Release()
{
	KdSafeRelease(m_VS);
	KdSafeRelease(m_inputlayout);

	KdSafeRelease(m_PS);

	KdSafeRelease(m_VS_Skin);
	KdSafeRelease(m_inputlayout_Skin);

	KdSafeRelease(m_outlineVS);
	KdSafeRelease(m_outlinePS);

	m_cb0.Release();
	m_cb1_Mesh.Release();
	m_cb2_Material.Release();
	m_cb3_Bone.Release();

}

void KdModelShader::SetToDevice()
{

	///*KdShaderManager::Instance().SetVertexShader(m_VS);
	//KdShaderManager::Instance().SetInputLayout(m_inputlayout);*/

	//KdShaderManager::Instance().SetPixelShader(m_PS);

	////=========================================
	////定数バッファをセット
	////=========================================
	//
	////オブジェクト定数バッファ（0番目にセットしている）
	//KdShaderManager::Instance().SetVSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetVSConstantBuffer(1, m_cb1_Mesh.GetAddress());
	//KdShaderManager::Instance().SetVSConstantBuffer(3, m_cb3_Bone.GetAddress());

	////マテリアル定数バッファ（1番目にセットしている）
	//KdShaderManager::Instance().SetPSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetPSConstantBuffer(2, m_cb2_Material.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetShader(m_PS, 0, 0);

	// 定数バッファをセット
	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(0, 1, m_cb0.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetConstantBuffers(0, 1, m_cb0.GetAddress());

	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(1, 1, m_cb1_Mesh.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetConstantBuffers(2, 1, m_cb2_Material.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(3, 1, m_cb3_Bone.GetAddress());

}

void KdModelShader::DrawMesh(const KdMesh* mesh, const std::vector<KdMaterial>& materials, Math::Matrix mWorld)
{
	if (mesh == nullptr)return;


	// 行列セット
	SetWorldMatrix(mWorld);
	// これで実際にGPU側のバッファへ書き込まれシェーダーで使用できるようになる
	m_cb1_Mesh.Write();
	//頂点シェーダーをセット
	if (mesh->IsSkinMesh())
	{
		// SkinMesh用の頂点シェーダーをセット
		if (KdShaderManager::Instance().SetVertexShader(m_VS_Skin))
		{
			// 頂点レイアウトをセット
			KdDirect3D::Instance().WorkDevContext()->IASetInputLayout(m_inputlayout_Skin);
		}
	}
	else
	{
		// StaticMesh用の頂点シェーダーをセット
		if (KdShaderManager::Instance().SetVertexShader(m_VS))
		{
			// 頂点レイアウトをセット
			KdDirect3D::Instance().WorkDevContext()->IASetInputLayout(m_inputlayout);
		}
	}

	//メッシュ情報をセット
	mesh->SetToDevice();

	//全サブセット
	for (UINT subi = 0; subi < mesh->GetSubsets().size(); subi++)
	{
		//面が1枚もない場合はスキップ
		if (mesh->GetSubsets()[subi].FaceCount == 0)continue;
		//マテリアル
		const KdMaterial& material = materials[mesh->GetSubsets()[subi].MaterialNo];

		////=========================================
		////定数バッファをセット
		////=========================================
		////基本色
		//m_cb2_Material.Work().BaseColor = material.m_baseColorRate;
		////発光色
		//m_cb2_Material.Work().Emlssive = material.m_emissiveRate;
		////金属度
		//m_cb2_Material.Work().Metallic = material.m_metallicRate;
		////粗さ
		//m_cb2_Material.Work().Roughness = material.m_roughnessRate;
		////GPUへ転送


		////=========================================
		////テクスチャセット
		////=========================================
		////複数毎のテクスチャを一気に渡すように、配列を用意
		//ID3D11ShaderResourceView* srvs[3] = {};

		////BaseColorテクスチャ
		//srvs[0] = material.m_baseColorTex ? material.m_baseColorTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////Emissiveテクスチャ
		//srvs[1] = srvs[2] = material.m_emissiveTex ? material.m_emissiveTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////Metallic Roughness
		//srvs[2] = material.m_metallicRoughnessTex ? material.m_metallicRoughnessTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////NormalMap
		////srvs[3] = material.m_normalTex ? material.m_normalTex->WorkSRView() : KdDirect3D::Instance().GetNormalTex()->WorkSRView();

		//// セット
		//KdDirect3D::Instance().WorkDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);
		SetMaterial(material);
		m_cb2_Material.Write();
		//サブセット描画
		mesh->DrawSubset(subi);
	}
}

void KdModelShader::DrawModel(const KdModelData& rModel, const Math::Matrix mWorld)
{

	auto& dataNodes = rModel.GetOriginalNodes();


	// スキンメッシュモデルの場合：ボーン情報を書き込み
	if (rModel.IsSkinMesh())
	{
		// ノード内からボーン情報を取得
		for (auto&& nodeIdx : rModel.GetBoneNodeIndices())
		{
			if (nodeIdx >= KdModelShader::maxBoneBufferSize) { assert(0 && "転送できるボーンの上限数を超えました"); return; }

			auto& dataNode = dataNodes[nodeIdx];

			// ボーン情報からGPUに渡す行列の計算
			BoneCB().Work().mat[dataNode.m_boneIndex] = dataNode.m_boneInverseWorldMatrix;

			BoneCB().Write();
		}
	}

	//m_cb0.Write();
	// 全描画用メッシュノードを描画
	for (auto& nodeIdx : rModel.GetMeshNodeIndices())
	{
		auto& rDataNode = dataNodes[nodeIdx];

		// 描画
		DrawMesh(rDataNode.m_spMesh.get(), rModel.GetMaterials(), rDataNode.m_worldTransform * mWorld);

		// 描画
		//DrawMesh(dataNodes[nodeIdx].m_spMesh.get(),rModel.GetMaterials(), dataNodes[nodeIdx].m_worldTransform * mWorld);
	}
}

void KdModelShader::DrawModel(KdModelWork& rModel, const Math::Matrix mWorld)
{
	if (!rModel.IsEnable()) { return; }

	//m_cb0.Write();

	const std::shared_ptr<KdModelData>& data = rModel.GetData();

	// データがないときはスキップ
	if (data == nullptr) { return; }

	auto& workNodes = rModel.GetNodes();
	auto& dataNodes = data->GetOriginalNodes();

	/*if (rModel.NeedCalcNodeMatrices())
	{
		rModel.CalcNodeMatrices();

	}*/

	// スキンメッシュモデルの場合：ボーン情報を書き込み
	if (data->IsSkinMesh())
	{
		// ノード内からボーン情報を取得
		for (auto&& nodeIdx : data->GetBoneNodeIndices())
		{
			if (nodeIdx >= KdModelShader::maxBoneBufferSize) { assert(0 && "転送できるボーンの上限数を超えました"); return; }

			auto& dataNode = dataNodes[nodeIdx];
			auto& workNode = workNodes[nodeIdx];

			// ボーン情報からGPUに渡す行列の計算
			BoneCB().Work().mat[dataNode.m_boneIndex] = dataNode.m_boneInverseWorldMatrix * workNode.m_worldTransform;

			BoneCB().Write();
		}
	}

	//int i = 0;
	//// 全描画用メッシュノードを描画
	//for (auto& node :workNodes)
	//{
	//	//=========================================
	//	//ボーンスキニング行列用の構造化バッファをセットする
	//	//=========================================
	//	if (data->GetBoneNodeIndices().size() >= 1)
	//	{
	//		m_cb3_Bone.Work().mat[i]=node.m_worldTransform;
	//		//GPUへ転送
	//		m_cb3_Bone.Write();
	//	}
	//	i++;
	//}
	// 全描画用メッシュノードを描画
	for (auto& nodeIdx : data->GetMeshNodeIndices())
	{
		//=========================================
		//ボーンスキニング行列用の構造化バッファをセットする
		//=========================================

		//if (data->GetBoneNodeIndices().size() >= 1)
		//{
		//	/*ID3D11ShaderResourceView* srvs[1];
		//	srvs[0] = workNodes[nodeIdx].m_worldTransform.;*/
		//	KdDirect3D::Instance().WorkDevContext()->VSSetShaderResources(

		//		100,
		//		1,
		//		//???
		//	);
		//}
		// 描画
		auto& rWorkNode = workNodes[nodeIdx];

		const std::shared_ptr<KdMesh>& spMesh = rModel.GetMesh(nodeIdx);

		DrawMesh(spMesh.get(), data->GetMaterials(), rWorkNode.m_worldTransform * mWorld);
	}
}

void KdModelShader::SetToDevice_Outline()
{
	KdShaderManager::Instance().SetVertexShader(m_outlineVS);
	KdShaderManager::Instance().SetInputLayout(m_inputlayout);

	KdShaderManager::Instance().SetPixelShader(m_outlinePS);

	//=========================================
	//定数バッファをセット
	//=========================================

	//オブジェクト定数バッファ（0番目にセットしている）
	KdShaderManager::Instance().SetVSConstantBuffer(0, m_cb0.GetAddress());
	KdShaderManager::Instance().SetVSConstantBuffer(1, m_cb1_Mesh.GetAddress());
	//マテリアル定数バッファ（1番目にセットしている）
	KdShaderManager::Instance().SetPSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetPSConstantBuffer(2, m_cb2_Material.GetAddress());

}

void KdModelShader::DrawMesh_Outline(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld)
{
	if (mesh == nullptr)return;

	//メッシュ情報をセット
	mesh->SetToDevice();
	//定数バッファにデータを書き込む（まだGPUには書き込まれていない）
	m_cb1_Mesh.Work().mW = mWorld;
	// これで実際にGPU側のバッファへ書き込まれシェーダーで使用できるようになる
	m_cb1_Mesh.Write();
	//全サブセット
	for (UINT subi = 0; subi < mesh->GetSubsets().size(); subi++)
	{
		//面が1枚もない場合はスキップ
		if (mesh->GetSubsets()[subi].FaceCount == 0)continue;

		//サブセット描画
		mesh->DrawSubset(subi);
	}
}

void KdModelShader::DrawModel_Outline(const KdModelData& rModel, const Math::Matrix mWorld)
{
	auto& dataNodes = rModel.GetOriginalNodes();
	//m_cb0.Write();
	// 全描画用メッシュノードを描画
	for (auto& nodeIdx : rModel.GetMeshNodeIndices())
	{
		// 描画
		DrawMesh_Outline(dataNodes[nodeIdx].m_spMesh.get(), rModel.GetMaterials(), dataNodes[nodeIdx].m_worldTransform * mWorld);
	}
}

void KdModelShader::SetMaterial(const KdMaterial& material)
{
	//-----------------------
	// マテリアル情報を定数バッファへ書き込む
	//-----------------------
	m_cb2_Material.Work().BaseColor = material.m_baseColorRate;
	m_cb2_Material.Work().Emissive = material.m_emissiveRate;
	m_cb2_Material.Work().Metallic = material.m_metallicRate;
	m_cb2_Material.Work().Roughness = material.m_roughnessRate;

	//-----------------------
	// テクスチャセット
	//-----------------------
	ID3D11ShaderResourceView* srvs[4] = {};

	// BaseColor
	srvs[0] = material.m_baseColorTex ? material.m_baseColorTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
	// Emissive
	srvs[1] = srvs[2] = material.m_emissiveTex ? material.m_emissiveTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
	// Metallic Roughness
	srvs[2] = material.m_metallicRoughnessTex ? material.m_metallicRoughnessTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
	// Normal
	srvs[3] = material.m_normalTex ? material.m_normalTex->WorkSRView() : KdDirect3D::Instance().GetNormalTex()->WorkSRView();


	// セット
	KdDirect3D::Instance().WorkDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);

}
