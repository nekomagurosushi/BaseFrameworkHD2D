#include "Scene.h"

void Scene::Init()
{


}

void Scene::Release()
{
}

void Scene::PostUpdate()
{
	for (shared_ptr<Object> sp_object : *m_objectList)
	{
		if (sp_object == nullptr)continue;
		sp_object->PostUpdate();
	}
}

void Scene::DrawLit() const
{
	for (weak_ptr<Object> wp_object : *m_objectList)
	{
		shared_ptr<Object> sp_object = wp_object.lock();
		//オブジェクトにデータが入っていないか光源フラグがオンであれば飛ばして次のオブジェクトへ
		if (sp_object == nullptr || sp_object->GetBrightFlg() != false)continue;
		sp_object->DrawLit();
	}
}

void Scene::DrawUnLit() const
{
	for (weak_ptr<Object> wp_object : *m_objectList)
	{
		shared_ptr<Object> sp_object = wp_object.lock();

		//オブジェクトにデータが入っていないか光源フラグがオンであれば飛ばして次のオブジェクトへ
		if (sp_object == nullptr || sp_object->GetBrightFlg() != false)continue;
		sp_object->DrawUnLit();
	}
}

void Scene::DrawBright() const
{
	for (weak_ptr<Object> wp_object : *m_objectList)
	{
		shared_ptr<Object> sp_object = wp_object.lock();

		//オブジェクトにデータが入っていないか光源フラグがオフであれば飛ばして次のオブジェクトへ
		if (sp_object == nullptr || sp_object->GetBrightFlg() != true)continue;
		sp_object->DrawBright();
	}
}

void Scene::DrawSprite() const
{
	for (weak_ptr<Object> wp_object : *m_objectList)
	{
		shared_ptr<Object> sp_object = wp_object.lock();

		//オブジェクトにデータが入っていないか光源フラグがオンであれば飛ばして次のオブジェクトへ
		if (sp_object == nullptr)continue;
		sp_object->DrawSprite();
	}
	//for (shared_ptr<KdCollider::SphereInfo> sp_collider : *m_colliderList)
	//{
	//	if (sp_collider == nullptr)continue;

	//	Math::Vector3 resultPos = Math::Vector3::Zero;
	//	KdDirect3D::Instance().ConvertWorldToScreenDetail(*m_camera->WorkCamera(), sp_collider->m_sphere.Center, resultPos);
	//	//KdShaderManager::Instance().m_HD2DShader.DrawPolygon(*m_spPoly, m_mWorld);
	//	if (resultPos.z > 0)
	//	{
	//		/*KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y, 10, &kRedColor);*/
	//		KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y, sp_collider->m_sphere.Radius*40, &kRedColor);
	//	}
	//}
}

