#include "main.h"

//#include "GameObject/Camera/TrackingCamera/TrackingCamera.h"
//#include "GameObject/Camera/FpsCamera.h"
//#include "GameObject/Camera/TpsCamera.h"
//#include "GameObject/Character/HamuHamu.h"
//
//#include "GameObject/Terrain/Terrain.h"
//#include "GameObject/Terrain/Lift/Lift.h"

#include "Application/Scene/SceneController.h"

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// エントリーポイント
// アプリケーションはこの関数から進行する
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
int WINAPI WinMain(HINSTANCE, HINSTANCE , LPSTR , int )
{
	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		CoUninitialize();

		return 0;
	}

	// mbstowcs_s関数で日本語対応にするために呼ぶ
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// 実行
	//===================================================================
	Application::Instance().Execute();

	// COM解放
	CoUninitialize();

	return 0;
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新の前処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PreUpdate()
{
	// 入力状況の更新
	KdInputManager::Instance().Update();

	KdShaderManager::Instance().WorkAmbientController().PreUpdate();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Update()
{
	m_sceneController->SceneUpdate();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新の後処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PostUpdate()
{
	m_sceneController->PostUpdate();
	// 3DSoundListnerの行列を更新
	KdAudioManager::Instance().SetListnerMatrix(KdShaderManager::Instance().GetCameraCB().mView.Invert());
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画の前処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PreDraw()
{
	KdDirect3D::Instance().ClearBackBuffer();

	KdShaderManager::Instance().WorkAmbientController().PreDraw();

	KdShaderManager::Instance().m_postProcessShader.PreDraw();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Draw()
{
	
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光を遮るオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight();
	{
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginLit();
	{
		/*for (std::shared_ptr<KdGameObject> pGameObj : m_spGameObjectList)
		{
			pGameObj->DrawLit();
		}*/
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{
		m_sceneController->DrawUnLit();
	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光源オブジェクト(自ら光るオブジェクトやエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
	}
	KdShaderManager::Instance().m_postProcessShader.EndBright();

	KdShaderManager::Instance().m_modelShader.SetToDevice();
	m_sceneController->DrawLit();
	

	//=========================================
	//テスト描画
	//=========================================
	
	//static bool init = true;
	//static std::unique_ptr<KdModelData> terra = std::make_unique<KdModelData>();
	//if (init)terra->Load("Asset/Data/Sample/Terrain/StageMap_roughness.gltf");

	////chara.Load("Asset/Data/Sample/Terrain/StageMap_roughness.gltf");

	///*static std::shared_ptr<KdModelData> bird = std::make_shared<KdModelData>();
	//if (init)bird->Load("Asset/Data/Samlpe/Character/player_original_6.gltf");
	//*/
	//static std::unique_ptr<KdModelWork> birdWork = std::make_unique<KdModelWork>();
	//if (init)birdWork->SetModelData("Asset/Data/Sample/Character/player_original_6.gltf");
	////player.SetModelData("Asset/Data/Sample/Character/player_original_6.gltf");

	//static KdAnimator animator;
	//if (init)
	//{
	//	animator.SetAnimation(birdWork->GetAnimation("Run"));
	//}
	//init = false;
	//
	//animator.AdvanceTime(birdWork->WorkNodes());

	//birdWork->CalcNodeMatrices();

	//KdShaderManager::Instance().m_modelShader.SetToDevice();

	///*Math::Matrix playerTransMat = Math::Matrix::CreateTranslation(0, 0, 0);
	//Math::Matrix playerScaleMat = Math::Matrix::CreateScale(1);
	//Math::Matrix playerRotateMat = Math::Matrix::CreateRotationZ(0);
	//Math::Matrix playerMat = playerScaleMat*playerRotateMat * playerTransMat;*/
	//KdShaderManager::Instance().m_modelShader.DrawModel(*birdWork, Math::Matrix::Identity);

	/**Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationZ(0);
	Math::Matrix mat = rotateMat * transMat;*/
	

	////=========================================
	////輪郭描画
	////=========================================
	////裏面をカリング（非表示）にするラスタライザーステートをセット

	//KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullFront);

	//////描画
	//KdShaderManager::Instance().m_modelShader.SetToDevice_Outline();
	//KdShaderManager::Instance().m_modelShader.DrawModel_Outline(*terra, Math::Matrix::Identity);

	//KdShaderManager::Instance().m_modelShader.DrawModel(*terra, Math::Matrix::Identity);
	//KdShaderManager::Instance().UndoRasterizerState();
	

	//	static std::unique_ptr<KdModelData> terra = std::make_unique<KdModelData>();
	//	if (init)terra->Load("Asset/SampleTerrain.gltf");

	//	static std::shared_ptr<KdModelData> bird = std::make_shared<KdModelData>();
	//	if (init)bird->Load("Asset/player_original_6.gltf");


	//	static std::unique_ptr<KdModelWork> birdWork = std::make_unique<KdModelWork>();
	//	if (init)birdWork->SetModelData(bird);

	//	KdShaderManager::Instance().m_modelShader.SetToDevice();
	//	KdShaderManager::Instance().m_modelShader.DrawModel(*birdWork, Math::Matrix::Identity);
	//	KdShaderManager::Instance().m_modelShader.DrawModel(*terra, Math::Matrix::Identity);
	//	//KdShaderManager::Instance().m_standardShader.SetToDevice();
	//	//KdShaderManager::Instance().m_standardShader.DrawModel(*terra, Math::Matrix::Identity);
	//	//KdShaderManager::Instance().m_standardShader.DrawModel(*birdWork, Math::Matrix::Identity);


	//確認用Imgui更新
	static int frame=0;
	frame++;
	if (ImGui::Begin("WindowName"),true, ImGuiWindowFlags_NoCollapse)
	{
		ImGui::LabelText(u8"fps","fps:%d", GetNowFPS());
		////ウィンドウを折りたたんでいない状態だと、この中が実行される。
		//ImGui::SliderFloat(u8"playerサイズ", &size, 0.1f, 30.0f);
		//{

		//}
	}
	ImGui::End();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画の後処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PostDraw()
{
	// 画面のぼかしや被写界深度処理の実施
	KdShaderManager::Instance().m_postProcessShader.PostEffectProcess();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// 2Dスプライトの描画
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::DrawSprite()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 2Dの描画はこの間で行う
	KdShaderManager::Instance().m_spriteShader.Begin();
	{/*
		for (std::shared_ptr<KdGameObject> pGameObj : m_spGameObjectList)
		{
			pGameObj->DrawSprite();
		}*/
		m_sceneController->DrawSprite();
	}
	KdShaderManager::Instance().m_spriteShader.End();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション初期設定
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
bool Application::Init(int w, int h)
{
	//===================================================================
	// ウィンドウ作成
	//===================================================================
	if (m_window.Create(w, h, "3D GameProgramming", "Window") == false) {
		MessageBoxA(nullptr, "ウィンドウ作成に失敗", "エラー", MB_OK);
		return false;
	}

	//===================================================================
	// フルスクリーン確認
	//===================================================================
	bool bFullScreen = false;
	if (MessageBoxA(m_window.GetWndHandle(), "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}

	//===================================================================
	// Direct3D初期化
	//===================================================================

	// デバイスのデバッグモードを有効にする
	bool deviceDebugMode = false;
#ifdef _DEBUG
	deviceDebugMode = true;
#endif

	// Direct3D初期化
	std::string errorMsg;
	if (KdDirect3D::Instance().Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	// フルスクリーン設定
	if (bFullScreen) {
		KdDirect3D::Instance().WorkSwapChain()->SetFullscreenState(TRUE, 0);
	}

	//===================================================================
	// imgui初期化
	//===================================================================
	//Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//SetUp Dear ImGui style
	//ImGui::StyleColorDark
	ImGui::StyleColorsClassic();
	//SetUp PlatForm/Renderer bindings
	ImGui_ImplWin32_Init(m_window.GetWndHandle());
	ImGui_ImplDX11_Init(KdDirect3D::Instance().WorkDev(), KdDirect3D::Instance().WorkDevContext());

	#include "imgui/ja_glyph_ranges.h" 

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();
	//日本語対応
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);

	//===================================================================
	// シェーダー初期化
	//===================================================================
	KdShaderManager::Instance().Init();

	//===================================================================
	// サウンド初期化
	//===================================================================
	KdAudioManager::Instance().Init();

	m_sceneController = make_shared<SceneController>();
	m_sceneController->Init();

	////===================================================================
	//// カメラ初期化
	////===================================================================
	//std::shared_ptr<FpsCamera> camera = std::make_shared<FpsCamera>();
	//camera->Init();
	//camera->SetTarget(hamu);
	//hamu->SetCamera(camera);
	//m_spGameObjectList.push_back(camera);
	//return true;
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション実行
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Execute()
{
	KdCSVData windowData("Asset/Data/WindowSettings.csv");
	const std::vector<std::string>& sizeData = windowData.GetLine(0);

	//===================================================================
	// 初期設定(ウィンドウ作成、Direct3D初期化など)
	//===================================================================
	if (Application::Instance().Init(atoi(sizeData[0].c_str()), atoi(sizeData[1].c_str())) == false) {
		return;
	}

	//===================================================================
	// ゲームループ
	//===================================================================

	// 時間
	m_fpsController.Init();

	// ループ
	while (1)
	{
		// 処理開始時間Get
		m_fpsController.UpdateStartTime();

		// ゲーム終了指定があるときはループ終了
		if (m_endFlag)
		{
			break;
		}

		//=========================================
		//
		// ウィンドウ関係の処理
		//
		//=========================================

		// ウィンドウのメッセージを処理する
		m_window.ProcessMessage();

		// ウィンドウが破棄されてるならループ終了
		if (m_window.IsCreated() == false)
		{
			break;
		}
		
		if (GetAsyncKeyState(VK_ESCAPE))
		{
//			if (MessageBoxA(m_window.GetWndHandle(), "本当にゲームを終了しますか？",
//				"終了確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
			{
				End();
			}
		}

		//ImGui開始
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//ImGui Demo ウィンドウ表示　（注）すごく参考になるウィンドウです。imgui_demo.cpp参照
		ImGui::ShowDemoWindow(nullptr);

		//=========================================
		//
		// アプリケーション更新処理
		//
		//=========================================
		PreUpdate();

		Update();

		PostUpdate();

		//=========================================
		//
		// アプリケーション描画処理
		//
		//=========================================
		PreDraw();

		Draw();

		PostDraw();

		DrawSprite();

		//Imguiのレンダリング：ココより上にImGuiの描画はする事
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		// BackBuffer -> 画面表示
		KdDirect3D::Instance().WorkSwapChain()->Present(0, 0);

		//=========================================
		//
		// フレームレート制御
		//
		//=========================================

		m_fpsController.Update();
	}

	//===================================================================
	// アプリケーション解放
	//===================================================================
	Release();
}

// アプリケーション終了
void Application::Release()
{
	KdInputManager::Instance().Release();

	KdShaderManager::Instance().Release();

	KdAudioManager::Instance().Release();

	KdDirect3D::Instance().Release();

	// ウィンドウ削除
	m_window.Release();
}