/*
* SoundManager.h
* 音声関連の処理
*/

#pragma once
#include "DirectXCommon.h"
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <fstream>
#include <array>
#include <cstdint>
#include <set>
#include <string>
#include <map>
#include <combaseapi.h>
#include <Windows.h>
#include <cassert>
#include <iterator>

//チャンクヘッダ
struct ChunkHeader {
	char id[4];		//チャンク毎のID
	int32_t size;	//チャンクサイズ
};

//RIFFヘッダチャンク
struct RiffHeader {
	ChunkHeader chunk;	//"RIFF"
	char type[4];		//"WAVE"
};

//FMTチャンク
struct FormatChunk {
	ChunkHeader chunk;	//"fmt"
	WAVEFORMATEX fmt;	//波形フォーマット
};

//音声データ
struct SoundData {
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭アドレス
	BYTE* pBuffer;
	//バッファサイズ
	unsigned int bufferSize;
	//波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice;
};

class SoundManager
{
public:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;

	static const int kMaxSoundData = 256;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 音声読み込み
	/// </summary>
	SoundData SoundLoadWave(const std::string& filename);

	/// <summary>
	/// 音声再生(はじめから)
	/// </summary>
	void SoundPlayWave(IXAudio2* xAudio2, SoundData& soundData, bool loop = false, float volume = 0.0f);

	/// <summary>
	/// 音声停止
	/// </summary>
	void StopWave(const SoundData& soundData);

	/// <summary>
	/// 音声解放
	/// </summary>
	void SoundUnload(SoundData& soundData);

private:
	std::map<std::string, SoundData> soundDatas_;
	//波形フォーマットからSourceVoiceの生成
	IXAudio2SourceVoice* sourceVoice = nullptr;
	HRESULT result;

	float outputMatrix[2] = { 1.0f,0.05f };


};