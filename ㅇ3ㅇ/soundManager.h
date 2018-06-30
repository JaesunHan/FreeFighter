#pragma once
#include <map>

#include "inc/fmod.hpp"	//fmod.hpp���� ��Ŭ���
#pragma comment(lib, "lib/fmodex_vc.lib")	//���̺귯�� ���� ���

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
	SoundGroup*		_masterSound; //������ ����׷�
	SoundGroup*		_musicSound; //�뷡 ����׷�
	SoundGroup*		_effectSound; //����Ʈ ����׷�

	Channel**		_channel;
	ChannelGroup*   _masterGroup; //������ ä�α׷�
	ChannelGroup*	_musicGroup;  //�뷡 ä�α׷�
	ChannelGroup*	_effectGroup; //����Ʈ ä�α׷�
	ChannelGroup*	_mp3Group;

	DSP				*dspLowPass = 0;  //��������
	DSP				*dspHighPass = 0; //��������

	arrSounds _mTotalSounds;

	FMOD_TAG Ftag; //�±׸� �޾ƿ��� ���� Ftag

	int _currentMusic;

	int _maxCount;


	float _frequency;//���ļ� ������ ���� ����

public:
	HRESULT init();
	void release();
	void update();


	//DSP���� �ʱ�ȭ
	void addDspLowPass();
	void addDspHighPass();

	// ���� �߰� �Լ�(string Ű��, string ��ι����ϸ�, bgm�ΰ�?, �ݺ�����Ұ��ΰ�?)
	void addSound(wstring keyName, wstring soundName, bool bgm, bool loop);

	//�������(Ű��, ����,bgm=true, effect=false) ������ 0~1.0����
	void play(wstring keyName, float volume = 1.0f, bool isMusic = false);
	void currentPlay();

	//��� �ߴ�(Ű��);
	void stop(wstring keyName);


	//�Ͻ�����(Ű��);
	void pause(wstring keyName);
	//�Ͻ���������(Ű��)
	void resume(wstring keyName);


	//������ΰ�?(Ű��)
	bool isPlaySound(wstring keyName);
	//�Ͻ������ΰ�?(Ű��)
	bool isPauseSound(wstring keyName);
	

	//�����̸����(Ű��),������ string;  ����:������ �±װ� ������ �����ϴ�.
	string getTagTitle(wstring keyName);
	string getTagTitle(bool isPlus);

	//�۰����(Ű��), ������ string; ����:������ �±װ� ������ �����ϴ�.
	string getTagArtist(wstring keyName);

	//������ ���� ��� ������ ����Ƽ� �����Ѵ�.
	float getMasterVolume();
	void setMasterVolume(float volume);

	//��� �ر��̴�!!
	//��� ���� ���� ������� ��ϵ� �뷡�� ������ �����Ѵ�.
	float getMusicVolume();
	void setMusicVolume(float volume);


	//ȿ���� �׷� ���� ���� ȿ�������� ��ϵ� �뷡�� ������ �����Ѵ�.
	float getEffectVolume();
	void setEffectVolume(float volume);


	//ä�ΰ��� ���� ���������� �� ������ ���õ� ������ �����Ѵ�.
	float getVolume(wstring keyName);
	void  setVolume(wstring keyName, float volume);


	//���� �߰��� ����� ��������
	void setMP3Volume(float volume);

	//������ //���̶� ����Ŀ �¿� ������ ġ��ħ �������
	void setPan(wstring keyName, float panValue);  // -1�� �������� �������� 1�� ����� ���� ����������
	void setPan(float panValue);
	//�ݻ��� �⺻����
	void setReverb();

	//�ݻ��� �� ����
	void reverbOn();
	void reverbOff();

	//���ļ� ��������		  (Ű��,			, ����); ���� �� �ѹ� ������ �����ϸ� ������ ������
	void multipleFrequency(wstring keyName, float multiple);
	void setFrequency(float speed);

	//�ƽ�ī��Ʈ ����
	int getMaxCounter() { return _maxCount; }


	//���� ���ļ��� ���(false�� ������ �����)
	void reverseLowPass(bool byPass);
	//���� ���ļ��� ���(false�� ������ �����)
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
	SoundGroup*		_masterSound; //������ ����׷�
	SoundGroup*		_musicSound; //�뷡 ����׷�
	SoundGroup*		_effectSound; //����Ʈ ����׷�

	Channel**		_channel;
	ChannelGroup*   _masterGroup; //������ ä�α׷�
	ChannelGroup*	_musicGroup;  //�뷡 ä�α׷�
	ChannelGroup*	_effectGroup; //����Ʈ ä�α׷�
	ChannelGroup*	_mp3Group;

	DSP				*dspLowPass = 0;  //��������
	DSP				*dspHighPass = 0; //��������

	arrSounds _mTotalSounds;

	FMOD_TAG Ftag; //�±׸� �޾ƿ��� ���� Ftag

	int _currentMusic;

	int _maxCount;


	float _frequency;//���ļ� ������ ���� ����

public:
	HRESULT init();
	void release();
	void update();


	//DSP���� �ʱ�ȭ
	void addDspLowPass();
	void addDspHighPass();

	// ���� �߰� �Լ�(string Ű��, string ��ι����ϸ�, bgm�ΰ�?, �ݺ�����Ұ��ΰ�?)
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//�������(Ű��, ����,bgm=true, effect=false) ������ 0~1.0����
	void play(string keyName, float volume = 1.0f, bool isMusic = false);
	void currentPlay();

	//��� �ߴ�(Ű��);
	void stop(string keyName);


	//�Ͻ�����(Ű��);
	void pause(string keyName);
	//�Ͻ���������(Ű��)
	void resume(string keyName);


	//������ΰ�?(Ű��)
	bool isPlaySound(string keyName);
	//�Ͻ������ΰ�?(Ű��)
	bool isPauseSound(string keyName);


	//�����̸����(Ű��),������ string;  ����:������ �±װ� ������ �����ϴ�.
	string getTagTitle(string keyName);
	string getTagTitle(bool isPlus);

	//�۰����(Ű��), ������ string; ����:������ �±װ� ������ �����ϴ�.
	string getTagArtist(string keyName);

	//������ ���� ��� ������ ����Ƽ� �����Ѵ�.
	float getMasterVolume();
	void setMasterVolume(float volume);

	//��� �ر��̴�!!
	//��� ���� ���� ������� ��ϵ� �뷡�� ������ �����Ѵ�.
	float getMusicVolume();
	void setMusicVolume(float volume);


	//ȿ���� �׷� ���� ���� ȿ�������� ��ϵ� �뷡�� ������ �����Ѵ�.
	float getEffectVolume();
	void setEffectVolume(float volume);


	//ä�ΰ��� ���� ���������� �� ������ ���õ� ������ �����Ѵ�.
	float getVolume(string keyName);
	void  setVolume(string keyName, float volume);


	//���� �߰��� ����� ��������
	void setMP3Volume(float volume);

	//������ //���̶� ����Ŀ �¿� ������ ġ��ħ �������
	void setPan(string keyName, float panValue);  // -1�� �������� �������� 1�� ����� ���� ����������
	void setPan(float panValue);
	//�ݻ��� �⺻����
	void setReverb();

	//�ݻ��� �� ����
	void reverbOn();
	void reverbOff();

	//���ļ� ��������		  (Ű��,			, ����); ���� �� �ѹ� ������ �����ϸ� ������ ������
	void multipleFrequency(string keyName, float multiple);
	void setFrequency(float speed);

	//�ƽ�ī��Ʈ ����
	int getMaxCounter() { return _maxCount; }


	//���� ���ļ��� ���(false�� ������ �����)
	void reverseLowPass(bool byPass);
	//���� ���ļ��� ���(false�� ������ �����)
	void reverseHighPass(bool byPass);
#endif
};