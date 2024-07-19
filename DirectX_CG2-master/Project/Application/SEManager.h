/*
* SEManager.h
* SEの管理
*/

#pragma once
#include "SoundManager.h"

class SEManager final
{
private:
	//コンストラクタ
	SEManager() {};
	//デストラクタ
	~SEManager() {};

public:
	//コピーコンストラクタ無効
	SEManager(const SEManager& se) = delete;
	//代入演算子無効
	SEManager& operator=(const SEManager& se) = delete;

public:

	static SEManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SoundManager* soundManager);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 再生
	/// </summary>
	void Play(SoundData se, float pitch, float pitchRange);

	void PlayBGM(SoundData* se, float vol, float pitch);

	/// <summary>
	/// 停止
	/// </summary>
	void Stop(SoundData se);

	//音声データ
	SoundData Decision() { return decision; }

private:
	SoundData se_;
	SoundManager* soundManager_ = nullptr;

	SoundData decision = soundManager_->SoundLoadWave("decision.wav");
};

