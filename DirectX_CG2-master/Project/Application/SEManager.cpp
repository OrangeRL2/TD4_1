/*
* SEManager.h
* SEの管理
*/

#include "SEManager.h"

SEManager* SEManager::GetInstance() {
	static SEManager instance;

	return &instance;
}

void SEManager::Initialize(SoundManager* soundManager) {
	soundManager_ = soundManager;
}

void SEManager::Finalize() {
	
}

void SEManager::Play(SoundData se, float pitch, float pitchRange) {

	soundManager_->SoundPlayWave(soundManager_->xAudio2.Get(), se, false, 0.2f);
	
	float randPitch = (float)rand() / RAND_MAX * pitchRange;
	if (se.pSourceVoice) {
		se.pSourceVoice->SetFrequencyRatio(pitch + randPitch);
	}

}

void SEManager::PlayBGM(SoundData* se, float vol, float pitch) {

	if (!se->pSourceVoice) {
		soundManager_->SoundPlayWave(soundManager_->xAudio2.Get(), *se, true, 0.1f);
		se->pSourceVoice->SetFrequencyRatio(pitch);
		se->pSourceVoice->SetVolume(vol * 0.1f);
	}
}

void SEManager::Stop(SoundData se) {

	if (se.pSourceVoice) {
		soundManager_->StopWave(se);
	}
}