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
    int sample_rate = 44100; // Default sample rate
    
  public:
    AudioLibSwitcher_applaudio() = default;
    ~AudioLibSwitcher_applaudio() override
    {
      finish();
    }
    
    void init() override
    {
      if (initialized)
        return;
      
      engine = std::make_unique<applaudio::AudioEngine>();
      if (engine->startup(sample_rate, 1, false))
        initialized = true;
    }
    
    void finish() override
    {
      if (engine && initialized)
        engine->shutdown();
      initialized = false;
      engine.reset();
    }
    
    unsigned int create_source() override
    {
      if (!initialized)
        return 0;
      return engine->create_source();
    }
    
    void destroy_source(unsigned int src_id) override
    {
      if (initialized)
        engine->destroy_source(src_id);
    }
    
    unsigned int create_buffer() override
    {
      if (!initialized)
        return 0;
      return engine->create_buffer();
    }
    
    void destroy_buffer(unsigned int buf_id) override
    {
      if (initialized)
        engine->destroy_buffer(buf_id);
    }
    
    void play_source(unsigned int src_id) override
    {
      if (initialized)
        engine->play_source(src_id);
    }
    
    bool is_source_playing(unsigned int src_id) override
    {
      if (!initialized)
        return false;
      return engine->is_source_playing(src_id);
    }
    
    void pause_source(unsigned int src_id) override
    {
      if (initialized)
        engine->pause_source(src_id);
    }
    
    void stop_source(unsigned int src_id) override
    {
      if (initialized)
        engine->stop_source(src_id);
    }
    
    void set_source_volume(unsigned int src_id, float vol) override
    {
      if (initialized)
        engine->set_source_volume(src_id, vol);
    }
    
    void set_source_pitch(unsigned int src_id, float pitch) override
    {
      if (initialized)
        engine->set_source_pitch(src_id, pitch);
    }
    
    void set_source_looping(unsigned int src_id, bool loop) override
    {
      if (initialized)
        engine->set_source_looping(src_id, loop);
    }
    
    void detach_source(unsigned int src_id) override
    {
      // For applaudio, detaching means setting buffer_id to 0
      if (initialized)
      {
        // You might need to add this method to AudioEngine:
        // engine->attach_buffer_to_source(src_id, 0);
      }
    }
    
    void set_source_standard_params(unsigned int src_id) override
    {
      if (initialized)
      {
        // Set standard parameters using your existing interface
        set_source_pitch(src_id, 1.0f);
        set_source_volume(src_id, 1.0f);
        set_source_looping(src_id, false);
      }
    }
    
    void set_buffer_data_mono_16(unsigned int buf_id, const std::vector<short>& buffer, int sample_rate) override
    {
      if (!initialized)
        return;
      
      // Store the sample rate for potential resampling
      this->sample_rate = sample_rate;
      
      // Convert mono to stereo if needed (applaudio expects stereo)
      std::vector<short> stereo_buffer;
      if (engine->get_channel_count() == 2)
      {
        stereo_buffer.reserve(buffer.size() * 2);
        for (short sample : buffer)
        {
          stereo_buffer.push_back(sample); // Left channel
          stereo_buffer.push_back(sample); // Right channel
        }
        engine->set_buffer_data(buf_id, stereo_buffer);
      }
      else
        engine->set_buffer_data(buf_id, buffer);
    }
    
    void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) override
    {
      if (initialized)
        engine->attach_buffer_to_source(src_id, buf_id);
    }
    
    std::string check_error() override
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
    
  }
