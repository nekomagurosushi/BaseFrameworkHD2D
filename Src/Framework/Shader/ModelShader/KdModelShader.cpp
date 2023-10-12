#include "Framework/KdFramework.h"

#include "KdModelShader.h"

bool KdModelShader::Init()
{
	//=========================================
	//���_�V�F�[�_�[
	//=========================================

	{
		//�R���p�C���ς݂̃V�F�[�_�[�w�b�_�[�t�@�C�����s�����[�h
#include "KdModelShader_VS.shaderInc"

		//���_�V�F�[�_�[�쐬
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS)))
		{
			assert(0 && "���_�V�F�[�_�[�쐬���s");
			Release();
			return false;
		}

		//1���_�̏ڍׂȏ��
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		//���_���̓��C�A�E�g�쐬
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateInputLayout(
			&layout[0],	//���̓G�������g�擪�A�h���X
			layout.size(),	//���̓G�������g��
			&compiledBuffer[0],	//���_�o�b�t�@�̃o�C�i���f�[�^
			sizeof(compiledBuffer),		//��L�̃o�b�t�@�T�C�Y
			&m_inputlayout))
			) {
			assert(0 && "CreateInputLayout���s");
			Release();
			return false;
		}
	}

	//=========================================
	//�s�N�Z���V�F�[�_�[
	//=========================================
	{
		//�R���p�C���ς݂̃w�b�_�[�t�@�C�����C���N���[�h
#include "KdModelShader_VS_Skin.shaderinc"

//���_�V�F�[�_�[�쐬
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS_Skin)))
		{
			assert(0 && "(�X�L�����b�V��)���_�V�F�[�_�[�쐬���s");
			Release();
			return false;
		}

		// �P���_�̏ڍׂȏ��
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 20,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 24,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 36,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SKININDEX",	0, DXGI_FORMAT_R16G16B16A16_UINT,	0, 48,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SKINWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 56,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		//���_���̓��C�A�E�g�쐬
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateInputLayout(
			&layout[0],	//���̓G�������g�擪�A�h���X
			layout.size(),	//���̓G�������g��
			&compiledBuffer[0],	//���_�o�b�t�@�̃o�C�i���f�[�^
			sizeof(compiledBuffer),		//��L�̃o�b�t�@�T�C�Y
			&m_inputlayout_Skin))
			) {
			assert(0 && "�i�X�L�����b�V���jCreateInputLayout���s");
			Release();
			return false;
		}
	}

	//=========================================
	//�s�N�Z���V�F�[�_�[
	//=========================================
	{
		//�R���p�C���ς݂̃V�F�[�_�[�w�b�_�[�t�@�C�����C���N���[�h
#include "KdModelShader_PS.shaderInc"

		if (FAILED(KdDirect3D::Instance().WorkDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_PS)))
		{
			assert(0 && "�s�N�Z���V�F�[�_�[�쐬���s");
			Release();
			return false;
		}
	}
	//=========================================
	//�֊s�p�@���_�V�F�[�_�[
	//=========================================
	//���_�V�F�[�_�[�쐬
	{
#include "KdModelShader_OutlineVS.shaderInc"
		if (FAILED(KdDirect3D::Instance().WorkDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_outlineVS)))
		{
			assert(0 && "���_�V�F�[�_�[�쐬���s");
			Release();
			return false;
		}
	}

	//=========================================
	//�֊s�p�@�s�N�Z���V�F�[�_�[
	//=========================================
	{
		//�R���p�C���ς݂̃V�F�[�_�[�w�b�_�[�t�@�C�����C���N���[�h
#include "KdModelShader_OutlinePS.shaderInc"

		if (FAILED(KdDirect3D::Instance().WorkDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_outlinePS)))
		{
			assert(0 && "�s�N�Z���V�F�[�_�[�쐬���s");
			Release();
			return false;
		}
	}
	//=========================================
	//�萔�o�b�t�@�쐬
	//=========================================
	m_cb0.Create();
	m_cb1_Mesh.Create();
	m_cb2_Material.Create();
	m_cb3_Bone.Create();

	//=========================================
	//�e�N�X�`���Ǎ�
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
	////�萔�o�b�t�@���Z�b�g
	////=========================================
	//
	////�I�u�W�F�N�g�萔�o�b�t�@�i0�ԖڂɃZ�b�g���Ă���j
	//KdShaderManager::Instance().SetVSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetVSConstantBuffer(1, m_cb1_Mesh.GetAddress());
	//KdShaderManager::Instance().SetVSConstantBuffer(3, m_cb3_Bone.GetAddress());

	////�}�e���A���萔�o�b�t�@�i1�ԖڂɃZ�b�g���Ă���j
	//KdShaderManager::Instance().SetPSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetPSConstantBuffer(2, m_cb2_Material.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetShader(m_PS, 0, 0);

	// �萔�o�b�t�@���Z�b�g
	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(0, 1, m_cb0.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetConstantBuffers(0, 1, m_cb0.GetAddress());

	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(1, 1, m_cb1_Mesh.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->PSSetConstantBuffers(2, 1, m_cb2_Material.GetAddress());
	KdDirect3D::Instance().WorkDevContext()->VSSetConstantBuffers(3, 1, m_cb3_Bone.GetAddress());

}

void KdModelShader::DrawMesh(const KdMesh* mesh, const std::vector<KdMaterial>& materials, Math::Matrix mWorld)
{
	if (mesh == nullptr)return;


	// �s��Z�b�g
	SetWorldMatrix(mWorld);
	// ����Ŏ��ۂ�GPU���̃o�b�t�@�֏������܂�V�F�[�_�[�Ŏg�p�ł���悤�ɂȂ�
	m_cb1_Mesh.Write();
	//���_�V�F�[�_�[���Z�b�g
	if (mesh->IsSkinMesh())
	{
		// SkinMesh�p�̒��_�V�F�[�_�[���Z�b�g
		if (KdShaderManager::Instance().SetVertexShader(m_VS_Skin))
		{
			// ���_���C�A�E�g���Z�b�g
			KdDirect3D::Instance().WorkDevContext()->IASetInputLayout(m_inputlayout_Skin);
		}
	}
	else
	{
		// StaticMesh�p�̒��_�V�F�[�_�[���Z�b�g
		if (KdShaderManager::Instance().SetVertexShader(m_VS))
		{
			// ���_���C�A�E�g���Z�b�g
			KdDirect3D::Instance().WorkDevContext()->IASetInputLayout(m_inputlayout);
		}
	}

	//���b�V�������Z�b�g
	mesh->SetToDevice();

	//�S�T�u�Z�b�g
	for (UINT subi = 0; subi < mesh->GetSubsets().size(); subi++)
	{
		//�ʂ�1�����Ȃ��ꍇ�̓X�L�b�v
		if (mesh->GetSubsets()[subi].FaceCount == 0)continue;
		//�}�e���A��
		const KdMaterial& material = materials[mesh->GetSubsets()[subi].MaterialNo];

		////=========================================
		////�萔�o�b�t�@���Z�b�g
		////=========================================
		////��{�F
		//m_cb2_Material.Work().BaseColor = material.m_baseColorRate;
		////�����F
		//m_cb2_Material.Work().Emlssive = material.m_emissiveRate;
		////�����x
		//m_cb2_Material.Work().Metallic = material.m_metallicRate;
		////�e��
		//m_cb2_Material.Work().Roughness = material.m_roughnessRate;
		////GPU�֓]��


		////=========================================
		////�e�N�X�`���Z�b�g
		////=========================================
		////�������̃e�N�X�`������C�ɓn���悤�ɁA�z���p��
		//ID3D11ShaderResourceView* srvs[3] = {};

		////BaseColor�e�N�X�`��
		//srvs[0] = material.m_baseColorTex ? material.m_baseColorTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////Emissive�e�N�X�`��
		//srvs[1] = srvs[2] = material.m_emissiveTex ? material.m_emissiveTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////Metallic Roughness
		//srvs[2] = material.m_metallicRoughnessTex ? material.m_metallicRoughnessTex->WorkSRView() : KdDirect3D::Instance().GetWhiteTex()->WorkSRView();
		////NormalMap
		////srvs[3] = material.m_normalTex ? material.m_normalTex->WorkSRView() : KdDirect3D::Instance().GetNormalTex()->WorkSRView();

		//// �Z�b�g
		//KdDirect3D::Instance().WorkDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);
		SetMaterial(material);
		m_cb2_Material.Write();
		//�T�u�Z�b�g�`��
		mesh->DrawSubset(subi);
	}
}

void KdModelShader::DrawModel(const KdModelData& rModel, const Math::Matrix mWorld)
{

	auto& dataNodes = rModel.GetOriginalNodes();


	// �X�L�����b�V�����f���̏ꍇ�F�{�[��������������
	if (rModel.IsSkinMesh())
	{
		// �m�[�h������{�[�������擾
		for (auto&& nodeIdx : rModel.GetBoneNodeIndices())
		{
			if (nodeIdx >= KdModelShader::maxBoneBufferSize) { assert(0 && "�]���ł���{�[���̏�����𒴂��܂���"); return; }

			auto& dataNode = dataNodes[nodeIdx];

			// �{�[����񂩂�GPU�ɓn���s��̌v�Z
			BoneCB().Work().mat[dataNode.m_boneIndex] = dataNode.m_boneInverseWorldMatrix;

			BoneCB().Write();
		}
	}

	//m_cb0.Write();
	// �S�`��p���b�V���m�[�h��`��
	for (auto& nodeIdx : rModel.GetMeshNodeIndices())
	{
		auto& rDataNode = dataNodes[nodeIdx];

		// �`��
		DrawMesh(rDataNode.m_spMesh.get(), rModel.GetMaterials(), rDataNode.m_worldTransform * mWorld);

		// �`��
		//DrawMesh(dataNodes[nodeIdx].m_spMesh.get(),rModel.GetMaterials(), dataNodes[nodeIdx].m_worldTransform * mWorld);
	}
}

void KdModelShader::DrawModel(KdModelWork& rModel, const Math::Matrix mWorld)
{
	if (!rModel.IsEnable()) { return; }

	//m_cb0.Write();

	const std::shared_ptr<KdModelData>& data = rModel.GetData();

	// �f�[�^���Ȃ��Ƃ��̓X�L�b�v
	if (data == nullptr) { return; }

	auto& workNodes = rModel.GetNodes();
	auto& dataNodes = data->GetOriginalNodes();

	/*if (rModel.NeedCalcNodeMatrices())
	{
		rModel.CalcNodeMatrices();

	}*/

	// �X�L�����b�V�����f���̏ꍇ�F�{�[��������������
	if (data->IsSkinMesh())
	{
		// �m�[�h������{�[�������擾
		for (auto&& nodeIdx : data->GetBoneNodeIndices())
		{
			if (nodeIdx >= KdModelShader::maxBoneBufferSize) { assert(0 && "�]���ł���{�[���̏�����𒴂��܂���"); return; }

			auto& dataNode = dataNodes[nodeIdx];
			auto& workNode = workNodes[nodeIdx];

			// �{�[����񂩂�GPU�ɓn���s��̌v�Z
			BoneCB().Work().mat[dataNode.m_boneIndex] = dataNode.m_boneInverseWorldMatrix * workNode.m_worldTransform;

			BoneCB().Write();
		}
	}

	//int i = 0;
	//// �S�`��p���b�V���m�[�h��`��
	//for (auto& node :workNodes)
	//{
	//	//=========================================
	//	//�{�[���X�L�j���O�s��p�̍\�����o�b�t�@���Z�b�g����
	//	//=========================================
	//	if (data->GetBoneNodeIndices().size() >= 1)
	//	{
	//		m_cb3_Bone.Work().mat[i]=node.m_worldTransform;
	//		//GPU�֓]��
	//		m_cb3_Bone.Write();
	//	}
	//	i++;
	//}
	// �S�`��p���b�V���m�[�h��`��
	for (auto& nodeIdx : data->GetMeshNodeIndices())
	{
		//=========================================
		//�{�[���X�L�j���O�s��p�̍\�����o�b�t�@���Z�b�g����
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
		// �`��
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
	//�萔�o�b�t�@���Z�b�g
	//=========================================

	//�I�u�W�F�N�g�萔�o�b�t�@�i0�ԖڂɃZ�b�g���Ă���j
	KdShaderManager::Instance().SetVSConstantBuffer(0, m_cb0.GetAddress());
	KdShaderManager::Instance().SetVSConstantBuffer(1, m_cb1_Mesh.GetAddress());
	//�}�e���A���萔�o�b�t�@�i1�ԖڂɃZ�b�g���Ă���j
	KdShaderManager::Instance().SetPSConstantBuffer(0, m_cb0.GetAddress());
	//KdShaderManager::Instance().SetPSConstantBuffer(2, m_cb2_Material.GetAddress());

}

void KdModelShader::DrawMesh_Outline(const KdMesh* mesh, const std::vector<KdMaterial>& materails, Math::Matrix mWorld)
{
	if (mesh == nullptr)return;

	//���b�V�������Z�b�g
	mesh->SetToDevice();
	//�萔�o�b�t�@�Ƀf�[�^���������ށi�܂�GPU�ɂ͏������܂�Ă��Ȃ��j
	m_cb1_Mesh.Work().mW = mWorld;
	// ����Ŏ��ۂ�GPU���̃o�b�t�@�֏������܂�V�F�[�_�[�Ŏg�p�ł���悤�ɂȂ�
	m_cb1_Mesh.Write();
	//�S�T�u�Z�b�g
	for (UINT subi = 0; subi < mesh->GetSubsets().size(); subi++)
	{
		//�ʂ�1�����Ȃ��ꍇ�̓X�L�b�v
		if (mesh->GetSubsets()[subi].FaceCount == 0)continue;

		//�T�u�Z�b�g�`��
		mesh->DrawSubset(subi);
	}
}

void KdModelShader::DrawModel_Outline(const KdModelData& rModel, const Math::Matrix mWorld)
{
	auto& dataNodes = rModel.GetOriginalNodes();
	//m_cb0.Write();
	// �S�`��p���b�V���m�[�h��`��
	for (auto& nodeIdx : rModel.GetMeshNodeIndices())
	{
		// �`��
		DrawMesh_Outline(dataNodes[nodeIdx].m_spMesh.get(), rModel.GetMaterials(), dataNodes[nodeIdx].m_worldTransform * mWorld);
	}
}

void KdModelShader::SetMaterial(const KdMaterial& material)
{
	//-----------------------
	// �}�e���A������萔�o�b�t�@�֏�������
	//-----------------------
	m_cb2_Material.Work().BaseColor = material.m_baseColorRate;
	m_cb2_Material.Work().Emissive = material.m_emissiveRate;
	m_cb2_Material.Work().Metallic = material.m_metallicRate;
	m_cb2_Material.Work().Roughness = material.m_roughnessRate;

	//-----------------------
	// �e�N�X�`���Z�b�g
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


	// �Z�b�g
	KdDirect3D::Instance().WorkDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);

}
