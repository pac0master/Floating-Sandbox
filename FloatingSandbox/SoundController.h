/***************************************************************************************
* Original Author:		Gabriele Giuseppini
* Created:				2018-03-08
* Copyright:			Gabriele Giuseppini  (https://github.com/GabrieleGiuseppini)
***************************************************************************************/
#pragma once

#include <GameLib/GameRandomEngine.h>
#include <GameLib/IGameEventHandler.h>
#include <GameLib/ResourceLoader.h>
#include <GameLib/TupleKeys.h>
#include <GameLib/Utils.h>

#include <SFML/Audio.hpp>

#include <chrono>
#include <memory>
#include <limits>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class SoundController : public IGameEventHandler
{
public:

    SoundController(
        std::shared_ptr<ResourceLoader> resourceLoader,
        ProgressCallback const & progressCallback);

	virtual ~SoundController();

    //
    // Controlling
    //

    void SetPaused(bool isPaused);

    void SetMute(bool isMute);

    void SetVolume(float volume);

    bool GetPlaySinkingMusic() const
    {
        return mPlaySinkingMusic;
    }

    void SetPlaySinkingMusic(bool playSinkingMusic);

    void PlayDrawSound(bool isUnderwater);
    void StopDrawSound();

    void PlaySawSound(bool isUnderwater);
    void StopSawSound();

    void PlaySwirlSound(bool isUnderwater);
    void StopSwirlSound();

    //
    // Updating
    //

    void Update();

    void LowFrequencyUpdate();

    void Reset();

public:

    //
    // Game event handlers
    //

    virtual void OnDestroy(
        Material const * material,
        bool isUnderwater,
        unsigned int size) override;
    
    virtual void OnPinToggled(
        bool isPinned,
        bool isUnderwater) override;

    virtual void OnStress(
        Material const * material,
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnBreak(
        Material const * material,
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnSinkingBegin(unsigned int shipId) override;

    virtual void OnLightFlicker(
        DurationShortLongType duration,
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnWaterTaken(float waterTaken) override;

    virtual void OnWaterSplashed(float waterSplashed) override;

    virtual void OnBombPlaced(
        ObjectId bombId,
        BombType bombType,
        bool isUnderwater) override;

    virtual void OnBombRemoved(
        ObjectId bombId,
        BombType bombType,
        std::optional<bool> isUnderwater) override;

    virtual void OnBombExplosion(
        BombType bombType,
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnRCBombPing(
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnTimerBombFuse(
        ObjectId bombId,
        std::optional<bool> isFast) override;

    virtual void OnTimerBombDefused(
        bool isUnderwater,
        unsigned int size) override;

    virtual void OnAntiMatterBombContained(
        ObjectId bombId,
        bool isContained) override;

    virtual void OnAntiMatterBombPreImploding() override;

    virtual void OnAntiMatterBombImploding() override;

private:

    enum class SoundType
    {
        Break,
        Destroy,
        Draw,
        Saw,
        Swirl,
        PinPoint,
        UnpinPoint,
        Stress,
        LightFlicker,
        WaterRush,
        WaterSplash,
        BombAttached,
        BombDetached,
        BombExplosion,
        RCBombPing,
        TimerBombSlowFuse,
        TimerBombFastFuse,
        TimerBombDefused,
        AntiMatterBombContained,
        AntiMatterBombPreImplosion,
        AntiMatterBombImplosion,
        AntiMatterBombExplosion,        
        Wave
    };

    static SoundType StrToSoundType(std::string const & str)
    {
        if (Utils::CaseInsensitiveEquals(str, "Break"))
            return SoundType::Break;
        else if (Utils::CaseInsensitiveEquals(str, "Destroy"))
            return SoundType::Destroy;
        else if (Utils::CaseInsensitiveEquals(str, "Draw"))
            return SoundType::Draw;
        else if (Utils::CaseInsensitiveEquals(str, "Saw"))
            return SoundType::Saw;
        else if (Utils::CaseInsensitiveEquals(str, "Swirl"))
            return SoundType::Swirl;
        else if (Utils::CaseInsensitiveEquals(str, "PinPoint"))
            return SoundType::PinPoint;
        else if (Utils::CaseInsensitiveEquals(str, "UnpinPoint"))
            return SoundType::UnpinPoint;
        else if (Utils::CaseInsensitiveEquals(str, "Stress"))
            return SoundType::Stress;
        else if (Utils::CaseInsensitiveEquals(str, "LightFlicker"))
            return SoundType::LightFlicker;
        else if (Utils::CaseInsensitiveEquals(str, "WaterRush"))
            return SoundType::WaterRush;
        else if (Utils::CaseInsensitiveEquals(str, "WaterSplash"))
            return SoundType::WaterSplash;
        else if (Utils::CaseInsensitiveEquals(str, "BombAttached"))
            return SoundType::BombAttached;
        else if (Utils::CaseInsensitiveEquals(str, "BombDetached"))
            return SoundType::BombDetached;
        else if (Utils::CaseInsensitiveEquals(str, "BombExplosion"))
            return SoundType::BombExplosion;
        else if (Utils::CaseInsensitiveEquals(str, "RCBombPing"))
            return SoundType::RCBombPing;
        else if (Utils::CaseInsensitiveEquals(str, "TimerBombSlowFuse"))
            return SoundType::TimerBombSlowFuse;
        else if (Utils::CaseInsensitiveEquals(str, "TimerBombFastFuse"))
            return SoundType::TimerBombFastFuse;
        else if (Utils::CaseInsensitiveEquals(str, "TimerBombDefused"))
            return SoundType::TimerBombDefused;
        else if (Utils::CaseInsensitiveEquals(str, "AntiMatterBombContained"))
            return SoundType::AntiMatterBombContained;
        else if (Utils::CaseInsensitiveEquals(str, "AntiMatterBombPreImplosion"))
            return SoundType::AntiMatterBombPreImplosion;
        else if (Utils::CaseInsensitiveEquals(str, "AntiMatterBombImplosion"))
            return SoundType::AntiMatterBombImplosion;
        else if (Utils::CaseInsensitiveEquals(str, "AntiMatterBombExplosion"))
            return SoundType::AntiMatterBombExplosion;
        else if (Utils::CaseInsensitiveEquals(str, "Wave"))
            return SoundType::Wave;
        else
            throw GameException("Unrecognized SoundType \"" + str + "\"");
    }

    enum class SizeType : int
    {
        Min = 0,

        Small = 0,
        Medium = 1,
        Large = 2,

        Max = 2
    };

    static SizeType StrToSizeType(std::string const & str)
    {
        std::string lstr = Utils::ToLower(str);

        if (lstr == "small")
            return SizeType::Small;
        else if (lstr == "medium")
            return SizeType::Medium;
        else if (lstr == "large")
            return SizeType::Large;
        else
            throw GameException("Unrecognized SizeType \"" + str + "\"");
    }

private:

    struct ContinuousSound
    {
        ContinuousSound()
            : mSoundBuffer()
            , mSound()
            , mCurrentPauseState(false)
            , mDesiredPlayingState(false)
        {
        }

        explicit ContinuousSound(std::unique_ptr<sf::SoundBuffer> soundBuffer)
            : ContinuousSound()
        {
            Initialize(std::move(soundBuffer));
        }

        void Initialize(std::unique_ptr<sf::SoundBuffer> soundBuffer)
        {
            assert(!mSoundBuffer && !mSound);

            mSoundBuffer = std::move(soundBuffer);
            mSound = std::make_unique<sf::Sound>();
            mSound->setBuffer(*mSoundBuffer);
            mSound->setLoop(true);
        }

        void SetVolume(float volume)
        {
            if (!!mSound)
            {
                mSound->setVolume(volume);
            }
        }

        void Start()
        {
            if (!!mSound)
            {
                if (!mCurrentPauseState
                    && sf::Sound::Status::Playing != mSound->getStatus())
                {
                    mSound->play();
                }
            }

            // Remember we want to play when we resume
            mDesiredPlayingState = true;
        }

        void SetPaused(bool isPaused)
        {
            if (!!mSound)
            {
                if (isPaused)
                {
                    // Pausing
                    if (sf::Sound::Status::Playing == mSound->getStatus())
                        mSound->pause();
                }
                else
                {
                    // Resuming - look at the desired playing state
                    if (mDesiredPlayingState)
                        mSound->play();
                }
            }

            mCurrentPauseState = isPaused;
        }

        void Stop()
        {
            if (!!mSound)
            {
                // We stop regardless of the pause state, even if we're paused
                if (sf::Sound::Status::Stopped != mSound->getStatus())
                    mSound->stop();
            }

            // Remember we want to stay stopped when we resume
            mDesiredPlayingState = false;
        }

        void AggregateUpdate(size_t count)
        {
            if (count == 0)
            {
                // Stop it
                Stop();
            }
            else
            {
                float volume = 100.0f * (1.0f - exp(-0.3f * static_cast<float>(count)));
                SetVolume(volume);
                Start();
            }
        }

    private:
        std::unique_ptr<sf::SoundBuffer> mSoundBuffer;
        std::unique_ptr<sf::Sound> mSound;

        // True/False if we are paused/not paused
        bool mCurrentPauseState;

        // The play state we want to be after resuming from a pause:
        // - true: we want to play
        // - false: we want to stop
        bool mDesiredPlayingState;
    };

    struct OneShotMultipleChoiceSound
    {
        std::vector<std::unique_ptr<sf::SoundBuffer>> SoundBuffers;
        size_t LastPlayedSoundIndex;

        OneShotMultipleChoiceSound()
            : SoundBuffers()
            , LastPlayedSoundIndex(0u)
        {
        }
    };    

    struct OneShotSingleChoiceSound
    {
        std::unique_ptr<sf::SoundBuffer> SoundBuffer;

        OneShotSingleChoiceSound()
            : SoundBuffer()
        {
        }
    };

    struct ContinuousMultipleChoiceSound
    {
    public:

        ContinuousMultipleChoiceSound()
            : mSoundAlternatives()
            , mSoundAlternativePlayCounts()
            , mAlternativesByObject()
            , mLastChosenAlternative(std::numeric_limits<size_t>::max())
        {}

        void AddAlternative(std::unique_ptr<sf::SoundBuffer> soundBuffer)
        {
            mSoundAlternatives.emplace_back(std::move(soundBuffer));
            mSoundAlternativePlayCounts.emplace_back(0);
        }

        void Reset()
        {
            Stop();

            std::fill(
                mSoundAlternativePlayCounts.begin(),
                mSoundAlternativePlayCounts.end(),
                0);

            mAlternativesByObject.clear();
        }

        void StartSoundAlternativeForObject(ObjectId objectId)
        {
            // Choose alternative
            mLastChosenAlternative = GameRandomEngine::GetInstance().ChooseNew(
                mSoundAlternatives.size(),
                mLastChosenAlternative);

            // Remember how many objects are playing this alternative
            ++mSoundAlternativePlayCounts[mLastChosenAlternative];

            // Remember object<->alternative mapping
            assert(mAlternativesByObject.count(objectId) == 0);
            mAlternativesByObject[objectId] = mLastChosenAlternative;

            // Update continuous sound
            mSoundAlternatives[mLastChosenAlternative].AggregateUpdate(mSoundAlternativePlayCounts[mLastChosenAlternative]);
        }

        void StopSoundAlternativeForObject(ObjectId objectId)
        {
            // Get alternative we had for this object
            assert(mAlternativesByObject.count(objectId) == 1);
            size_t alternative = mAlternativesByObject[objectId];

            // Update number ofobjects that are playing this alternative
            --mSoundAlternativePlayCounts[alternative];

            // Remove object<->alternative mapping
            mAlternativesByObject.erase(objectId);

            // Update continuous sound
            mSoundAlternatives[alternative].AggregateUpdate(mSoundAlternativePlayCounts[alternative]);
        }

        void SetPaused(bool isPaused)
        {
            std::for_each(
                mSoundAlternatives.begin(),
                mSoundAlternatives.end(),
                [&isPaused](auto & s)
                {
                    s.SetPaused(isPaused);
                });
        }

        void Stop()
        {
            std::for_each(
                mSoundAlternatives.begin(),
                mSoundAlternatives.end(),
                [](auto & s)
                {
                    s.Stop();
                });
        }

    private:

        std::vector<ContinuousSound> mSoundAlternatives;
        std::vector<size_t> mSoundAlternativePlayCounts;
        std::unordered_map<ObjectId, size_t> mAlternativesByObject;
        size_t mLastChosenAlternative;
    };

    struct ContinuousSingleChoiceSound
    {
        ContinuousSingleChoiceSound()
            : mSound()
            , mObjectsPlayingSound()
        {}

        void Initialize(std::unique_ptr<sf::SoundBuffer> soundBuffer)
        {
            mSound.Initialize(std::move(soundBuffer));
        }

        void Reset()
        {
            mSound.Stop();
            mObjectsPlayingSound.clear();
        }

        void StartSoundForObject(ObjectId objectId)
        {
            // Remember that this object is playing this sound
            assert(mObjectsPlayingSound.count(objectId) == 0);
            mObjectsPlayingSound.insert(objectId);

            // Update continuous sound
            mSound.AggregateUpdate(mObjectsPlayingSound.size());
        }

        bool StopSoundForObject(ObjectId objectId)
        {
            // Remove the object tracking, if any
            bool objectWasPlayingSound = (mObjectsPlayingSound.erase(objectId) != 0);

            if (objectWasPlayingSound)
            {
                // Update continuous sound
                mSound.AggregateUpdate(mObjectsPlayingSound.size());
            }

            return objectWasPlayingSound;
        }

        void SetVolume(float volume)
        {
            mSound.SetVolume(volume);
        }

        void Start()
        {
            mSound.Start();
        }

        void SetPaused(bool isPaused)
        {
            mSound.SetPaused(isPaused);
        }

        void Stop()
        {
            mSound.Stop();
        }

    private:

        ContinuousSound mSound;
        std::set<ObjectId> mObjectsPlayingSound;
    };

    struct PlayingSound
    {
        SoundType Type;
        std::unique_ptr<sf::Sound> Sound;
        std::chrono::steady_clock::time_point StartedTimestamp;

        PlayingSound(
            SoundType type,
            std::unique_ptr<sf::Sound> sound,
            std::chrono::steady_clock::time_point startedTimestamp)
            : Type(type)
            , Sound(std::move(sound))
            , StartedTimestamp(startedTimestamp)
        {
        }
    };

private:

    void PlayMSUOneShotMultipleChoiceSound(
        SoundType soundType,
        Material const * material,
        unsigned int size,
        bool isUnderwater,
        float volume);

    void PlayDslUOneShotMultipleChoiceSound(
        SoundType soundType,
        DurationShortLongType duration,
        bool isUnderwater,
        float volume);

    void PlayUOneShotMultipleChoiceSound(
        SoundType soundType,
        bool isUnderwater,
        float volume);

    void PlayOneShotMultipleChoiceSound(
        SoundType soundType,
        float volume);

    void ChooseAndPlayOneShotMultipleChoiceSound(
        SoundType soundType,
        OneShotMultipleChoiceSound & sound,
        float volume);

    void PlayOneShotSound(
        SoundType soundType,
        sf::SoundBuffer * soundBuffer,
        float volume);

    void ScavengeStoppedSounds();

    void ScavengeOldestSound(SoundType soundType);    

private:

    std::shared_ptr<ResourceLoader> mResourceLoader;


    //
    // State
    //

    float mCurrentVolume;
    bool mPlaySinkingMusic;

    float mLastWaterSplashed;
    float mCurrentWaterSplashedTrigger;


    //
    // One-Shot sounds
    //

    static constexpr size_t MaxPlayingSounds{ 100 };
    static constexpr std::chrono::milliseconds MinDeltaTimeSound{ 100 };

    unordered_tuple_map<
        std::tuple<SoundType, Material::SoundProperties::SoundElementType, SizeType, bool>,
        OneShotMultipleChoiceSound> mMSUOneShotMultipleChoiceSounds;

    unordered_tuple_map<
        std::tuple<SoundType, DurationShortLongType, bool>,
        OneShotMultipleChoiceSound> mDslUOneShotMultipleChoiceSounds;

    unordered_tuple_map<
        std::tuple<SoundType, bool>,
        OneShotMultipleChoiceSound> mUOneShotMultipleChoiceSounds;

    unordered_tuple_map<
        std::tuple<SoundType>,
        OneShotMultipleChoiceSound> mOneShotMultipleChoiceSounds;

    std::vector<PlayingSound> mCurrentlyPlayingOneShotSounds;

    //
    // Continuous sounds
    //

    ContinuousSingleChoiceSound mSawAbovewaterSound;
    ContinuousSingleChoiceSound mSawUnderwaterSound;
    ContinuousSingleChoiceSound mDrawSound;
    ContinuousSingleChoiceSound mSwirlSound;

    ContinuousSingleChoiceSound mWaterRushSound;
    ContinuousSingleChoiceSound mWaterSplashSound;
    ContinuousSingleChoiceSound mTimerBombSlowFuseSound;
    ContinuousSingleChoiceSound mTimerBombFastFuseSound;
    ContinuousMultipleChoiceSound mAntiMatterBombContainedSounds;

    //
    // Music
    //

    sf::Music mSinkingMusic;
};
