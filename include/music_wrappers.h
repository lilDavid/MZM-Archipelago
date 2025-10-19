#ifndef MUSIC_WRAPPERS_H
#define MUSIC_WRAPPERS_H

#include "structs/audio.h"

void DMA2IntrCode(void);
void RestartSound(void);
void ClearSoundData(void);
void unk_34ac(u8 param_1);
void unk_35d0(u8 param_1);
void CheckSetNewMusicTrack(Sound musicTrack);
void unk_378c(Sound musicTrack);
void CheckPlayTransitionMusicTrack(void);
void unk_38d8(void);
void UpdateMusicAfterAlarmDisable(void);
u32 DetermineNewMusicTrack(Sound musicTrack);
void unk_39c8(void);
void PlayMusic(Sound musicTrack, u8 priority);
void unk_3a6c(void);
void FadeMusic(u16 timer);
void FadeMusicForDemo(u16 timer);
void FadeCurrentMusicAndQueueNextMusic(u16 timer, Sound musicTrack, u8 priority);
void FadeCurrentInsertMusicQueueCurrent(u16 timer, Sound musicTrack, u8 priority);
void unk_3bd0(Sound musicTrack, u16 timer);
void CheckPlayFadingMusic(Sound musicTrack, u16 timer, u8 priority);
void InsertMusicAndQueueCurrent(Sound musicTrack, u8 isNotInterrupting);
void ReplayQueuedMusic(u8 queueFlags);
void unk_3e24(u16 timer);
void UpdateMusicPriority(u8 priority);
void PlayCurrentMusicTrack(void);
void DecreaseMusicVolume(void);
void ResetMusicVolume(void);
void QueueSound(u16 sound, u16 timer);
void StopOrFadeSound(u16 sound, u16 timer);
void Music_Empty_1(void);
void Music_Empty_2(void);
void BackupTrackData2SoundChannels(void);
void RetrieveTrackData2SoundChannels(void);
void DelayMusicStart(struct TrackData* pTrack, u16 delay);
void PlaySoundTest(Sound musicTrack);
void ReplaySoundTest(Sound musicTrack);
void CheckReplayFileSelectMusic(u16 timer);
void unk_42bc(Sound musicTrack);

#endif /* MUSIC_WRAPPERS_H */
