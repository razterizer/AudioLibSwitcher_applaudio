//
//  AudioLibSwitcher_applaudio.h
//  AudioLibSwitcher_applaudio
//
//  Created by Rasmus Anthin on 2025-09-15.
//

#pragma once
#include "../../AudioLibSwitcher/include/AudioLibSwitcher/IAudioLibSwitcher.h"
#include <applaudio/AudioEngine.h>
#include <memory>

namespace audio
{
  
  class AudioLibSwitcher_applaudio : public IAudioLibSwitcher
  {
  private:
    std::unique_ptr<applaudio::AudioEngine> engine;
    bool initialized = false;
    
  public:
    AudioLibSwitcher_applaudio() = default;
    ~AudioLibSwitcher_applaudio() override
    {
      finish();
    }
    
    virtual void init() override
    {
      if (initialized)
        return;
      
      engine = std::make_unique<applaudio::AudioEngine>();
      if (engine->startup())
        initialized = true;
    }
    
    virtual void finish() override
    {
      if (engine && initialized)
        engine->shutdown();
      initialized = false;
      engine.reset();
    }
    
    virtual unsigned int create_source() override
    {
      if (!initialized)
        return 0;
      return engine->create_source();
    }
    
    virtual void destroy_source(unsigned int src_id) override
    {
      if (initialized)
        engine->destroy_source(src_id);
    }
    
    virtual unsigned int create_buffer() override
    {
      if (!initialized)
        return 0;
      return engine->create_buffer();
    }
    
    virtual void destroy_buffer(unsigned int buf_id) override
    {
      if (initialized)
        engine->destroy_buffer(buf_id);
    }
    
    virtual void play_source(unsigned int src_id) override
    {
      if (initialized)
        engine->play_source(src_id);
    }
    
    virtual bool is_source_playing(unsigned int src_id) override
    {
      if (!initialized)
        return false;
      return engine->is_source_playing(src_id);
    }
    
    virtual void pause_source(unsigned int src_id) override
    {
      if (initialized)
        engine->pause_source(src_id);
    }
    
    virtual void stop_source(unsigned int src_id) override
    {
      if (initialized)
        engine->stop_source(src_id);
    }
    
    virtual void set_source_volume(unsigned int src_id, float vol) override
    {
      if (initialized)
        engine->set_source_volume(src_id, vol);
    }
    
    virtual void set_source_pitch(unsigned int src_id, float pitch) override
    {
      if (initialized)
        engine->set_source_pitch(src_id, pitch);
    }
    
    virtual void set_source_looping(unsigned int src_id, bool loop) override
    {
      if (initialized)
        engine->set_source_looping(src_id, loop);
    }
    
    virtual void set_source_standard_params(unsigned int src_id) override
    {
      if (initialized)
      {
        // Set standard parameters using your existing interface
        set_source_pitch(src_id, 1.0f);
        set_source_volume(src_id, 1.0f);
        set_source_looping(src_id, false);
      }
    }
    
    virtual void set_buffer_data_mono_16(unsigned int buf_id, const std::vector<short>& buffer, int sample_rate) override
    {
      if (!initialized)
        return;
        
      engine->set_buffer_data(buf_id, buffer, 1, sample_rate);
    }
    
    virtual void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) override
    {
      if (initialized)
        engine->attach_buffer_to_source(src_id, buf_id);
    }
    
    virtual void detach_buffer_from_source(unsigned int src_id) override
    {
      if (initialized)
        engine->detach_buffer_from_source(src_id);
    }
    
    virtual std::string check_error() override
    {
      // For applaudio, you might want to add error tracking
      // For now, return empty string meaning "no error"
      return "";
    }
    
    // Optional: Add method to configure sample rate
    void set_sample_rate(int rate)
    {
      sample_rate = rate;
      // You might need to restart the engine if sample rate changes
    }
    
  };

}
