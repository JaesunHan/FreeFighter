#pragma once
#include <map>

#include "inc/fmod.hpp"	//fmod.hpp파일 인클루드
#pragma comment(lib, "lib/fmodex_vc.lib")	//라이브러리 파일 등록

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

#define SOUNDMANAGER soundManager::GetInstance()

class soundManager
{
	SINGLETONE(soundManager)

#ifdef UNICODE
private:
	typedef map<wstring, Sound**>				arrSounds;
	typedef map<wstring, Sound**>::iterator		arrSoundsIter;
	typedef map<wstring, Channel**>				arrChannels;
	typedef map<wstring, Channel**>::iterator	arrChannelsIter;


private:
	FMOD_RESULT     result;

	System*			_system;
	
	Sound**			_sound;
	SoundGroup*		_masterSound; //마스터 사운드그룹
	SoundGroup*		_musicSound; //노래 사운드그룹
	SoundGroup*		_effectSound; //이펙트 사운드그룹

	Channel**		_channel;
	ChannelGroup*   _masterGroup; //마스터 채널그룹
	ChannelGroup*	_musicGroup;  //노래 채널그룹
	ChannelGroup*	_effectGroup; //이펙트 채널그룹
	ChannelGroup*	_mp3Group;

	DSP				*dspLowPass = 0;  //낮은음역
	DSP				*dspHighPass = 0; //높은음역

	arrSounds _mTotalSounds;

	FMOD_TAG Ftag; //태그를 받아오기 위한 Ftag

	int _currentMusic;

	int _maxCount;


	float _frequency;//주파수 조절을 위한 변수

public:
	HRESULT init();
	void release();
	void update();


	//DSP영역 초기화
	void addDspLowPass();
	void addDspHighPass();

	// 사운드 추가 함수(string 키값, string 경로및파일명, bgm인가?, 반복재생할것인가?)
	void addSound(wstring keyName, wstring soundName, bool bgm, bool loop);

	//사운드재생(키값, 볼륨,bgm=true, effect=false) 볼륨은 0~1.0까지
	void play(wstring keyName, float volume = 1.0f, bool isMusic = false);
	void currentPlay();

	//재생 중단(키값);
	void stop(wstring keyName);


	//일시중지(키값);
	void pause(wstring keyName);
	//일시중지해제(키값)
	void resume(wstring keyName);


	//재생중인가?(키값)
	bool isPlaySound(wstring keyName);
	//일시중지인가?(키값)
	bool isPauseSound(wstring keyName);
	

	//음악이름얻기(키값),리턴은 string;  주의:음악의 태그가 없으면 터집니다.
	string getTagTitle(wstring keyName);
	string getTagTitle(bool isPlus);

	//작곡가명얻기(키값), 리턴은 string; 주의:음악의 태그가 없으면 터집니다.
	string getTagArtist(wstring keyName);

	//마스터 볼륨 모든 볼륨을 싸잡아서 조정한다.
	float getMasterVolume();
	void setMasterVolume(float volume);

	//요시 해금이닷!!
	//브금 관련 볼륨 브금으로 등록된 노래의 볼륨을 조절한다.
	float getMusicVolume();
	void setMusicVolume(float volume);


	//효과음 그룹 관련 볼륨 효과음으로 등록된 노래의 볼륨을 조절한다.
	float getEffectVolume();
	void setEffectVolume(float volume);


	//채널관련 볼륨 직접적으로 그 볼륨애 관련된 볼륨을 조절한다.
	float getVolume(wstring keyName);
	void  setVolume(wstring keyName, float volume);


	//현재 추가된 곡들의 볼륨조절
	void setMP3Volume(float volume);

	//팬조절 //팬이란 스피커 좌우 음향의 치우침 조절기능
	void setPan(wstring keyName, float panValue);  // -1에 가까울수록 왼쪽으로 1에 가까울 수록 오른쪽으로
	void setPan(float panValue);
	//반사음 기본셋팅
	void setReverb();

	//반사음 온 오프
	void reverbOn();
	void reverbOff();

	//주파수 배율조절		  (키값,			, 배율); 주의 단 한번 배율을 조절하면 끝난다 귀차나
	void multipleFrequency(wstring keyName, float multiple);
	void setFrequency(float speed);

	//맥스카운트 겟터
	int getMaxCounter() { return _maxCount; }


	//낮은 주파수만 통과(false면 나머지 불통과)
	void reverseLowPass(bool byPass);
	//높은 주파수만 통과(false면 나머지 불통과)
	void reverseHighPass(bool byPass);
#else
private:
	typedef map<string, Sound**>				arrSounds;
	typedef map<string, Sound**>::iterator		arrSoundsIter;
	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelsIter;


private:
	FMOD_RESULT     result;

	System*			_system;

	Sound**			_sound;
	SoundGroup*		_masterSound; //마스터 사운드그룹
	SoundGroup*		_musicSound; //노래 사운드그룹
	SoundGroup*		_effectSound; //이펙트 사운드그룹

	Channel**		_channel;
	ChannelGroup*   _masterGroup; //마스터 채널그룹
	ChannelGroup*	_musicGroup;  //노래 채널그룹
	ChannelGroup*	_effectGroup; //이펙트 채널그룹
	ChannelGroup*	_mp3Group;

	DSP				*dspLowPass = 0;  //낮은음역
	DSP				*dspHighPass = 0; //높은음역

	arrSounds _mTotalSounds;

	FMOD_TAG Ftag; //태그를 받아오기 위한 Ftag

	int _currentMusic;

	int _maxCount;


	float _frequency;//주파수 조절을 위한 변수

public:
	HRESULT init();
	void release();
	void update();


	//DSP영역 초기화
	void addDspLowPass();
	void addDspHighPass();

	// 사운드 추가 함수(string 키값, string 경로및파일명, bgm인가?, 반복재생할것인가?)
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//사운드재생(키값, 볼륨,bgm=true, effect=false) 볼륨은 0~1.0까지
	void play(string keyName, float volume = 1.0f, bool isMusic = false);
	void currentPlay();

	//재생 중단(키값);
	void stop(string keyName);


	//일시중지(키값);
	void pause(string keyName);
	//일시중지해제(키값)
	void resume(string keyName);


	//재생중인가?(키값)
	bool isPlaySound(string keyName);
	//일시중지인가?(키값)
	bool isPauseSound(string keyName);


	//음악이름얻기(키값),리턴은 string;  주의:음악의 태그가 없으면 터집니다.
	string getTagTitle(string keyName);
	string getTagTitle(bool isPlus);

	//작곡가명얻기(키값), 리턴은 string; 주의:음악의 태그가 없으면 터집니다.
	string getTagArtist(string keyName);

	//마스터 볼륨 모든 볼륨을 싸잡아서 조정한다.
	float getMasterVolume();
	void setMasterVolume(float volume);

	//요시 해금이닷!!
	//브금 관련 볼륨 브금으로 등록된 노래의 볼륨을 조절한다.
	float getMusicVolume();
	void setMusicVolume(float volume);


	//효과음 그룹 관련 볼륨 효과음으로 등록된 노래의 볼륨을 조절한다.
	float getEffectVolume();
	void setEffectVolume(float volume);


	//채널관련 볼륨 직접적으로 그 볼륨애 관련된 볼륨을 조절한다.
	float getVolume(string keyName);
	void  setVolume(string keyName, float volume);


	//현재 추가된 곡들의 볼륨조절
	void setMP3Volume(float volume);

	//팬조절 //팬이란 스피커 좌우 음향의 치우침 조절기능
	void setPan(string keyName, float panValue);  // -1에 가까울수록 왼쪽으로 1에 가까울 수록 오른쪽으로
	void setPan(float panValue);
	//반사음 기본셋팅
	void setReverb();

	//반사음 온 오프
	void reverbOn();
	void reverbOff();

	//주파수 배율조절		  (키값,			, 배율); 주의 단 한번 배율을 조절하면 끝난다 귀차나
	void multipleFrequency(string keyName, float multiple);
	void setFrequency(float speed);

	//맥스카운트 겟터
	int getMaxCounter() { return _maxCount; }


	//낮은 주파수만 통과(false면 나머지 불통과)
	void reverseLowPass(bool byPass);
	//높은 주파수만 통과(false면 나머지 불통과)
	void reverseHighPass(bool byPass);
#endif
};