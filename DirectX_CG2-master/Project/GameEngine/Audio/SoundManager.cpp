/*
* SoundManager.cpp
* 音声関連の処理
*/

#include "SoundManager.h"
#include <string>

void SoundManager::Initialize()
{
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	result = xAudio2->CreateMasteringVoice(&masterVoice);
}

//音声データの読み込み
SoundData SoundManager::SoundLoadWave(const std::string& filename) {

	//-------①ファイルオープン-------//
	const std::string& directoryPath = "Resources/Sounds/" + filename;
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(directoryPath, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

	//-------②.wavデータ読み込み-------//

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));

	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};

	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));

	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK ", 4) == 0) {
		//読み込み位置をJUNKチャンクの終わるまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	//Waveファイルを閉じる
	file.close();

	//-------③読み込んだ音声データをreturn-------//

	//returnする為の音声データ
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	return soundData;

}

//-------音声データの解放-------//
void SoundManager::SoundUnload(SoundData& soundData) {
	//バッファのメモリを解放
	delete[] soundData.pBuffer;

	soundData.pBuffer = 0;
	soundData.bufferSize = 0;
	soundData.wfex = {};
}

//------サウンドの再生-------//

//音声再生(はじめから)
void SoundManager::SoundPlayWave(IXAudio2* audio, SoundData& soundData, bool loop, float volume) {
	////波形フォーマットを元にSourceVoiceの生成
	//IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = audio->CreateSourceVoice(&soundData.pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	if (loop)
	{
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	buf.Flags = XAUDIO2_END_OF_STREAM;

	//波形データの再生
	result = soundData.pSourceVoice->SetVolume(volume);
	result = soundData.pSourceVoice->SetOutputMatrix(soundData.pSourceVoice, 1, 2, outputMatrix);
	result = soundData.pSourceVoice->SubmitSourceBuffer(&buf);
	result = soundData.pSourceVoice->Start();

}

//音声停止
void SoundManager::StopWave(const SoundData& soundData)
{
	//波形フォーマットを元にSourceVoiceの生成
	//IXAudio2SourceVoice* pSourceVoice = nullptr;
	//result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;

	buf.Flags = XAUDIO2_END_OF_STREAM;

	if (soundData.pSourceVoice != nullptr) {
		result = soundData.pSourceVoice->Stop(0);
		result = soundData.pSourceVoice->FlushSourceBuffers();
		result = soundData.pSourceVoice->SubmitSourceBuffer(&buf);
	}

}